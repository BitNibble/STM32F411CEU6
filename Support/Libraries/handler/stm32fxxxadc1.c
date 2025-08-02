/******************************************************************************
	STM32 XXX ADC1
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 28022024
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxadc1.h"

#define ON 1
#define OFF 0
#define ADC_STAB_DELAY 15

/*** File Variables ***/
// ADC1
static STM32FXXX_ADC1 stm32fxxx_adc1 = {0};
/*** File Procedure & Function Header ***/
/*** ADC1 ***/
void STM32FXXXAdc1Clock(uint8_t state)
{
	if(state){ set_reg_Msk(&RCC->APB2ENR , RCC_APB2ENR_ADC1EN_Msk, RCC_APB2ENR_ADC1EN_Pos, 1); }
	else{ set_reg_Msk(&RCC->APB2ENR , RCC_APB2ENR_ADC1EN_Msk, RCC_APB2ENR_ADC1EN_Pos, 0); }

}
void STM32FXXXAdc1Nvic(uint8_t state)
{
	if(state){ set_bit_block(NVIC->ISER, 1, ADC_IRQn, 1); } else{ set_bit_block(NVIC->ICER, 1, ADC_IRQn, 1); }
}
/*** ADC1 INIC Procedure & Function Definition ***/
void adc1_enable(void)
{
	/*** ADC1 Clock ***/
	STM32FXXXAdc1Clock(ON);
	/*** ADC1 TypeDef ***/
	stm32fxxx_adc1.instance = ADC1;
	stm32fxxx_adc1.common_instance = ADC1_COMMON;
	/*** Other ***/
	stm32fxxx_adc1.clock = STM32FXXXAdc1Clock;
	stm32fxxx_adc1.nvic = STM32FXXXAdc1Nvic;
	//return &stm32fxxx_adc1;
}

STM32FXXX_ADC1* adc1(void){ return (STM32FXXX_ADC1*) &stm32fxxx_adc1; }

/****** MISCELLANEOUS ******/
void ADC_TemperatureSetup(void) {
    uint8_t countdown;

    // Enable ADC1 clock
    STM32FXXXAdc1Clock(ON);

    // Configure ADC1 parameters
    ADC1->CR1 = 0; // Clear control register
    set_reg_Msk(&ADC1->SQR1, ADC_SQR1_L, ADC_SQR1_L_Pos, 0);
    set_reg_Msk(&ADC1->SQR3, ADC_SQR3_SQ1, ADC_SQR3_SQ1_Pos, 18);
    set_reg_Msk(&ADC1->SMPR1, ADC_SMPR1_SMP18, ADC_SMPR1_SMP18_Pos, 3);

    // Enable temperature sensor
    set_reg_Msk(&ADC->CCR, ADC_CCR_TSVREFE, ADC_CCR_TSVREFE_Pos, ON);
    set_reg_Msk(&ADC1->CR2, ADC_CR2_ADON, ADC_CR2_ADON_Pos, ON);

    // Stabilization delay
    for(countdown = ADC_STAB_DELAY; countdown; countdown--);
}
uint16_t ADC_ReadTemperature(void) {
	uint16_t adc_value;
    set_reg_Msk(&ADC1->CR2, ADC_CR2_SWSTART, ADC_CR2_SWSTART_Pos, ON);
    while (!get_reg_Msk(ADC1->SR, ADC_SR_EOC, ADC_SR_EOC_Pos));
    adc_value = ADC1->DR;
    return adc_value;
}
float CalculateTemperature(uint16_t adc_value) {
    const float V_25 = 0.76f;  // Voltage at 25°C (in volts)
    const float Avg_slope = 0.0025f;  // Average slope (in volts/°C)
    const float V_ref = 3.3f;  // Reference voltage, typically 3.0V or 3.3V

    float V_sense = ((float)adc_value / 4096) * V_ref;
    float temperature = ((V_sense - V_25) / Avg_slope) + 25.0f;

    return temperature;
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

