/******************************************************************************
	STM32 XXX ADC2
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 28022024
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxadc2.h"

#define ON 1
#define OFF 0
/*** File Variables ***/
//#ifdef STM32F446xx
// ADC2
static STM32FXXX_ADC2 stm32fxxx_adc2 = {0};
/*** File Procedure & Function Header ***/
/*** ADC2 ***/
#ifdef STM32F446xx
void STM32FXXXAdc2Clock(uint8_t state)
{
	if(bool){ rcc_instance()->apb2enr.par.adc2en = 1; }else{ rcc_instance()->apb2enr.par.adc2en = 0; }
}
void STM32FXXXAdc2Nvic(uint8_t state)
{
	if(bool){ set_bit_block(NVIC->ISER, 1, ADC_IRQn, 1); } else{ set_bit_block(NVIC->ICER, 1, ADC_IRQn, 1); }
}
#endif
/*** ADC2 INIC Procedure & Function Definition ***/
void adc2_enable(void)
{
	#ifdef STM32F446xx
		/*** ADC2 Clock ***/
		STM32FXXXAdc2Clock(ON);
		/*** ADC2 TypeDef ***/
		stm32fxxx_adc2.instance = ADC2;
		stm32fxxx_adc2.common_instance = ADC123_COMMON;
	#endif
	// Other
	stm32fxxx_adc2.clock = STM32FXXXAdc2Clock;
	stm32fxxx_adc2.nvic = STM32FXXXAdc2Nvic;
	//return &stm32fxxx_adc2;
}

STM32FXXX_ADC2* adc2(void){ return (STM32FXXX_ADC2*) &stm32fxxx_adc2; }

//#endif

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

