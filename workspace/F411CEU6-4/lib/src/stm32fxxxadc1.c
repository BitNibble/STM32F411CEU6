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
	for (uint32_t time_out = END_OF_CONVERSION_TIME_OUT; !get_reg_Msk(ADC1->SR, ADC_SR_EOC) && time_out; time_out-- );
}
void ADC1_Start(void) {
	set_reg_Msk(&ADC1->CR2, ADC_CR2_ADON, 1);
	for(uint8_t countdown = ADC_STAB_DELAY; countdown; countdown--); // Stabilization delay
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
static STM32FXXX_ADC1 stm32fxxx_adc1 = {
	.clock = ADC1_Clock,
	.nvic = ADC1_Nvic,
	.startconversion = ADC1_StartConversion,
	.waitendofconversion = ADC1_WaitEndOfConversion,
	.start = ADC1_Start,
	.stop = ADC1_Stop,
	.temperaturesetup = ADC1_TemperatureSetup,
	.readtemperature = ADC1_ReadTemperature
};

STM32FXXX_ADC1* adc1(void){ return (STM32FXXX_ADC1*) &stm32fxxx_adc1; }

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

