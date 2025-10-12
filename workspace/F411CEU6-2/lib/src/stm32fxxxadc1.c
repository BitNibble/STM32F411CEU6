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
void ADC1_StartConversion(void) {
	set_reg_Msk(&ADC1->CR2, ADC_CR2_SWSTART, 1);
}
void ADC1_WaitEndOfConversion(void) {
	for (volatile uint32_t time_out = END_OF_CONVERSION_TIME_OUT; !get_reg_Msk(ADC1->SR, ADC_SR_EOC) && time_out; time_out-- );
}
void ADC1_Start(void) {
	set_reg_Msk(&ADC1->CR2, ADC_CR2_ADON, 1);
	for(volatile uint8_t countdown = ADC_STAB_DELAY; countdown; countdown--); // Stabilization delay
}
void ADC1_Stop(void) {
	set_reg_Msk(&ADC1->CR2, ADC_CR2_ADON, 0);
}
void ADC1_TemperatureSetup(void) {
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
uint16_t ADC1_ReadTemperature(void) {
	uint16_t adc_value;
	ADC1_StartConversion();
	ADC1_WaitEndOfConversion();
    adc_value = ADC1->DR;
    return adc_value;
}

/*** ADC1 ***/
static ADC1_Callback ADC1_callback_setup = {0};

static STM32FXXX_ADC1 stm32fxxx_adc1_setup = {
	.clock = ADC1_Clock,
	.nvic = ADC1_Nvic,
	.startconversion = ADC1_StartConversion,
	.waitendofconversion = ADC1_WaitEndOfConversion,
	.start = ADC1_Start,
	.stop = ADC1_Stop,
	.temperaturesetup = ADC1_TemperatureSetup,
	.readtemperature = ADC1_ReadTemperature,
	.callback = &ADC1_callback_setup
};

STM32FXXX_ADC1* adc1(void){ return (STM32FXXX_ADC1*) &stm32fxxx_adc1_setup; }

/*** INTERRUPT ***/
void ADC_IRQHandler(void)
{
	ADC1_Callback* cb = adc1()->callback;
    uint32_t status = stm32f411ceu6()->adc1->SR;   // Read status register
    uint32_t value  = 0;

    /*** 1. End of Conversion (EOC) ***/
    if (status & (1 << 1))  // EOC flag
    {
        value = stm32f411ceu6()->adc1->DR;  // Read result clears EOC
        if (cb->on_conversion_complete)
            cb->on_conversion_complete((uint16_t)value);
    }

    /*** 2. End of Injected Conversion (JEOC) ***/
    if (status & (1 << 2))  // JEOC flag
    {
        // Read injected data register if used
        // For now just trigger callback for injected channel done
        if (cb->on_conversion_complete)
            cb->on_conversion_complete((uint16_t)stm32f411ceu6()->adc1->DR);
        stm32f411ceu6()->adc1->SR &= ~(1 << 2);  // Clear JEOC manually
    }

    /*** 3. Analog Watchdog (AWD) ***/
    if (status & (1 << 0))  // AWD flag
    {
        if (cb->on_error)
            cb->on_error(0xA0);  // Custom code for AWD
        stm32f411ceu6()->adc1->SR &= ~(1 << 0);  // Clear AWD
    }

    /*** 4. Overrun Error (OVR) ***/
    if (status & (1 << 5))  // OVR flag
    {
        if (cb->on_error)
            cb->on_error(0xE0);  // Custom code for overrun
        stm32f411ceu6()->adc1->SR &= ~(1 << 5);  // Clear OVR
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

