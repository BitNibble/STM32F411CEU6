/******************************************************************************
	STM32 XXX ADC3
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 28022024
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxadc3.h"

#define ON 1
#define OFF 0
/*** File Variables ***/
// ADC3
static STM32FXXX_ADC3 stm32fxxx_adc3 = {0};
/*** File Procedure & Function Header ***/
/*** ADC3 ***/
#ifdef STM32F446xx
void STM32FXXXAdc3Clock(uint8_t state)
{
	if(bool){ rcc_instance()->apb2enr.par.adc3en = 1; }else{ rcc_instance()->apb2enr.par.adc3en = 0; }
}
void STM32FXXXAdc3Nvic(uint8_t state)
{
	if(bool){ set_bit_block(NVIC->ISER, 1, ADC_IRQn, 1); } else{ set_bit_block(NVIC->ICER, 1, ADC_IRQn, 1); }
}
#endif
/*** ADC3 INIC Procedure & Function Definition ***/
void adc3_enable(void)
{
	#ifdef STM32F446xx
		/*** ADC3 Clock ***/
		STM32FXXXAdc3Clock(ON);
		/*** ADC3 TypeDef ***/
		stm32fxxx_adc3.instance = ADC3;
		stm32fxxx_adc3.common_instance = ADC123_COMMON;
	#endif
	// Other
	stm32fxxx_adc3.clock = STM32FXXXAdc3Clock;
	stm32fxxx_adc3.nvic = STM32FXXXAdc3Nvic;
	//return &stm32fxxx_adc3;
}

STM32FXXX_ADC3* adc3(void){ return (STM32FXXX_ADC3*) &stm32fxxx_adc3; }

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

