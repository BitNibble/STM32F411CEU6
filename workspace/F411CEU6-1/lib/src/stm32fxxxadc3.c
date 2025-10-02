/******************************************************************************
	STM32 XXX ADC3
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     28022024
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxadc3.h"

/*** Define and Macro ***/
#define ADC_STAB_DELAY 15
#define END_OF_CONVERSION_TIME_OUT 100
/*** File Variables ***/
#ifdef STM32F446xx
// ADC3
static STM32FXXX_ADC3 stm32fxxx_adc3 = {0};
/*** File Procedure & Function Header ***/
/*** ADC3 ***/
void ADC3_Clock(uint8_t state) {
	if(state){ RCC->APB2ENR |= RCC_APB2ENR_ADC3EN; }else{ RCC->APB2ENR &= ~RCC_APB2ENR_ADC3EN; }
}
void ADC3_Nvic(uint8_t state) {
	if(state){ set_bit_block(NVIC->ISER, 1, ADC_IRQn, 1); } else{ set_bit_block(NVIC->ICER, 1, ADC_IRQn, 1); }
}
void ADC3_start(void) {
	set_reg_Msk(&ADC3->CR2, ADC_CR2_ADON, ADC_CR2_ADON_Pos, ON);
}
void ADC3_stop(void) {
	set_reg_Msk(&ADC3->CR2, ADC_CR2_ADON, ADC_CR2_ADON_Pos, OFF);
}
/*** ADC3 INIC Procedure & Function Definition ***/
void adc3_enable(void)
{
	/*** ADC3 Clock ***/
	ADC3_Clock(ON);
	/*** Clock and Nvic ***/
	stm32fxxx_adc3.clock = ADC3_Clock;
	stm32fxxx_adc3.nvic = ADC3_Nvic;
	/*** Procedures ***/
	/*** Other ***/

	//return &stm32fxxx_adc3;
}

STM32FXXX_ADC3* adc3(void){ return (STM32FXXX_ADC3*) &stm32fxxx_adc3; }

#endif

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

