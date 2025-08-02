/******************************************************************************
	STM32 XXX ADC2
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     28022024
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxadc2.h"

#define ADC_STAB_DELAY 15
#define END_OF_CONVERSION_TIME_OUT 100
/*** File Variables ***/
#ifdef STM32F446xx
// ADC2
static STM32FXXX_ADC2 stm32fxxx_adc2 = {0};
/*** File Procedure & Function Header ***/
/*** ADC2 ***/
void ADC2_Clock(uint8_t state)
{
	if(state){ RCC->APB2ENR |= RCC_APB2ENR_ADC2EN; }else{ RCC->APB2ENR &= ~RCC_APB2ENR_ADC2EN; }
}
void ADC2_Nvic(uint8_t state)
{
	if(state){ set_bit_block(NVIC->ISER, 1, ADC_IRQn, 1); } else{ set_bit_block(NVIC->ICER, 1, ADC_IRQn, 1); }
}
void ADC2_start(void){
	set_reg_Msk(&ADC2->CR2, ADC_CR2_ADON, ADC_CR2_ADON_Pos, ON);
}
void ADC2_stop(void){
	set_reg_Msk(&ADC2->CR2, ADC_CR2_ADON, ADC_CR2_ADON_Pos, OFF);
}
/*** ADC2 INIC Procedure & Function Definition ***/
void adc2_enable(void)
{
	/*** ADC2 Clock ***/
	ADC2_Clock(ON);
	/*** ADC2 TypeDef ***/
	stm32fxxx_adc2.instance = ADC2;
	stm32fxxx_adc2.common_instance = ADC123_COMMON;
	/*** Clock and Nvic ***/
	stm32fxxx_adc2.clock = ADC2_Clock;
	stm32fxxx_adc2.nvic = ADC2_Nvic;
	/*** Procedures ***/
	/*** Other ***/

	//return &stm32fxxx_adc2;
}

STM32FXXX_ADC2* adc2(void){ return (STM32FXXX_ADC2*) &stm32fxxx_adc2; }

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

