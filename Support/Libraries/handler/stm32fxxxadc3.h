/******************************************************************************
	STM32 XXX ADC3
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 28022024
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXADC3_H_
	#define _STM32FXXXADC3_H_
/*** Library ***/
#include "stm32fxxxinstance.h"
/*** ADC TypeDef ***/
// ADC -> ADC3
typedef struct
{
	/*** BitField Mapping ***/
	ADC_TypeDef* instance;
	ADC_Common_TypeDef* common_instance;
	/*** Other ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
}STM32FXXX_ADC3;

// INIC
void adc3_enable(void);
STM32FXXX_ADC3* adc3(void);

/***** ADC3 Procedure & Function Header ******/
void STM32FXXXAdc3Clock(uint8_t state);
void STM32FXXXAdc3Nvic(uint8_t state);

#endif

/*** EOF ***/

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

