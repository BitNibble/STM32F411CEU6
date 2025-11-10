/******************************************************************************
	STM32 XXX ADC1
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     28022024
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxadc1.h"
#include "stm32fxxxnvic.h"
#include <stdarg.h>

/*** Define and Macro ***/
#define ADC_STAB_DELAY 15 // 15
#define END_OF_CONVERSION_TIME_OUT 100

/*** File Procedure & Function Header ***/
/*** ADC1 ***/
void ADC1_Clock(uint8_t state)
{
	if(state){ set_reg_Msk(&RCC->APB2ENR , RCC_APB2ENR_ADC1EN_Msk, 1); }
	else{ set_reg_Msk(&RCC->APB2ENR , RCC_APB2ENR_ADC1EN_Msk, 0); }

}
void ADC1_Nvic(uint8_t state) {
	if(state){ set_bit_block(NVIC->ISER, 1, ADC_IRQn, 1); } else{ set_bit_block(NVIC->ICER, 1, ADC_IRQn, 1); }
}

/*
* Auto-handling version of adc_set_sequence()
* - Detects internal channels 16/17/18
* - Enables TSVREFE and VBATE
* - Ensures long sampling times
*/
static inline void adc_set_sequence_auto(ADC_TypeDef *adc, uint8_t count, ...)
{
	if (count == 0 || count > 16) return;

	/* Clear existing sequence */
	adc->SQR1 &= ~(0xF << 20);
	adc->SQR1 &= ~0x000FFFFF;
	adc->SQR2 = 0;
	adc->SQR3 = 0;

	/* Set sequence length */
	adc->SQR1 |= ((count - 1) & 0x0F) << 20;

	va_list args;
	va_start(args, count);

	for (uint8_t i = 0; i < count; i++)
	{
		uint8_t ch = (uint8_t)va_arg(args, int);

		/* Auto-enable internal channels */
		if (ch == 16 || ch == 17)
		{
			ADC->CCR |= ADC_CCR_TSVREFE; /* Temp + Vref */
		}
		if (ch == 18)
		{
			ADC->CCR |= ADC_CCR_VBATE;
		}

		/* Assign channel to SQRx */
		if (i < 6)
			adc->SQR3 |= (ch & 0x1F) << (5 * i);
		else if (i < 12)
			adc->SQR2 |= (ch & 0x1F) << (5 * (i - 6));
		else
			adc->SQR1 |= (ch & 0x1F) << (5 * (i - 12));

		/* Auto-set sampling time: long sample for internal channels */
		uint32_t smp_bits = 0; /* default: fast sampling */

		if (ch >= 16) /* internal channels */
			smp_bits = 7; /* 480 cycles */

		if (ch <= 9)
		{
			adc->SMPR2 &= ~(7 << (3 * ch));
			adc->SMPR2 |= (smp_bits << (3 * ch));
		}
		else
		{
			uint8_t c = ch - 10;
			adc->SMPR1 &= ~(7 << (3 * c));
			adc->SMPR1 |= (smp_bits << (3 * c));
	}
}

va_end(args);
}

void ADC1_Start_Conversion(void) {
	set_reg_Msk(&ADC1->CR2, ADC_CR2_SWSTART, 1);
}
void ADC1_Wait_End_Of_Conversion(void) {
	for (volatile uint32_t time_out = END_OF_CONVERSION_TIME_OUT; !get_reg_Msk(ADC1->SR, ADC_SR_EOC) && time_out; time_out-- );
}
void ADC1_Start(void) {
	set_reg_Msk(&ADC1->CR2, ADC_CR2_ADON, 1);
	for(volatile uint8_t countdown = ADC_STAB_DELAY; countdown; countdown--); // Stabilization delay
}
void ADC1_Stop(void) {
	set_reg_Msk(&ADC1->CR2, ADC_CR2_ADON, 0);
}
void ADC1_Temperature_Setup(void) {
    // Enable ADC1 clock
    ADC1_Clock(1);

    // Configure ADC1 parameters
    ADC1->CR1 = 0; // Clear control register
    set_reg_Msk(&ADC1->SQR1, ADC_SQR1_L, 0);
    set_reg_Msk(&ADC1->SQR3, ADC_SQR3_SQ1, 18);
    set_reg_Msk(&ADC1->SMPR1, ADC_SMPR1_SMP18, 3);

    // Enable temperature sensor
    set_reg_Msk(&ADC->CCR, ADC_CCR_TSVREFE, 1);
    ADC1_Start();
}
uint16_t ADC1_Read_Temperature(void) {
	uint16_t adc_value;
	ADC1_Start_Conversion();
	ADC1_Wait_End_Of_Conversion();
    adc_value = ADC1->DR;
    return adc_value;
}

/*** ADC1 ***/
static ADC1_Callback ADC1_callback_setup = {0};

static STM32FXXX_ADC1_Handler stm32fxxx_adc1_setup = {
	.clock = ADC1_Clock,
	.nvic = ADC1_Nvic,
	.start_conversion = ADC1_Start_Conversion,
	.wait_end_of_conversion = ADC1_Wait_End_Of_Conversion,
	.start = ADC1_Start,
	.stop = ADC1_Stop,
	.temperature_setup = ADC1_Temperature_Setup,
	.read_temperature = ADC1_Read_Temperature,
	.callback = &ADC1_callback_setup,
	.dev = dev
};

STM32FXXX_ADC1_Handler* adc1(void){ return (STM32FXXX_ADC1_Handler*) &stm32fxxx_adc1_setup; }

/*** INTERRUPT ***/
void ADC_IRQHandler(void)
{
	ADC1_Callback* cb = adc1()->callback;
    uint32_t status = dev()->adc1->SR;   // Read status register
    uint32_t value  = 0;

    /*** 1. End of Conversion (EOC) ***/
    if (status & (1 << 1))  // EOC flag
    {
        value = dev()->adc1->DR;  // Read result clears EOC
        if (cb->on_conversion_complete)
            cb->on_conversion_complete((uint16_t)value);
    }

    /*** 2. End of Injected Conversion (JEOC) ***/
    if (status & (1 << 2))  // JEOC flag
    {
        // Read injected data register if used
        // For now just trigger callback for injected channel done
        if (cb->on_conversion_complete)
            cb->on_conversion_complete((uint16_t)dev()->adc1->DR);
        dev()->adc1->SR &= ~(1 << 2);  // Clear JEOC manually
    }

    /*** 3. Analog Watchdog (AWD) ***/
    if (status & (1 << 0))  // AWD flag
    {
        if (cb->on_error)
            cb->on_error(0xA0);  // Custom code for AWD
        dev()->adc1->SR &= ~(1 << 0);  // Clear AWD
    }

    /*** 4. Overrun Error (OVR) ***/
    if (status & (1 << 5))  // OVR flag
    {
        if (cb->on_error)
            cb->on_error(0xE0);  // Custom code for overrun
        dev()->adc1->SR &= ~(1 << 5);  // Clear OVR
    }

    /*** 5. Start/Stop notification (optional custom hooks) ***/
    if (cb->on_start)
    {
        // Could trigger when ADC_CR2.ADON set, handled elsewhere if desired
        // adc1()->callback.on_start();
    }

    if (cb->on_stop)
    {
        // Could trigger when ADC_CR2.ADON cleared, handled elsewhere if desired
        // adc1()->callback.on_stop();
    }
}

/******
1º Sequence
2º Scope
	- Library Scope
	- File Scope
	- Function Scope
	- Precedence Scope
3º Pointer and Variable
4º Casting
******/

/*** EOF ***/

