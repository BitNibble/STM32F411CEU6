/******************************************************************************
	STM32 XXX ADC3
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     28022024
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXADC3_H_
	#define _STM32FXXXADC3_H_

/*** Library ***/
#include "stm32f411ceu6.h"
/*** ADC TypeDef ***/
// ADC -> ADC3
typedef struct
{
	/*** BitField Mapping ***/
	ADC_TypeDef* instance;
	ADC_Common_TypeDef* common_instance;
	/*** Clock and Nvic ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
	/*** Other ***/
	void (*start)(void);
	void (*stop)(void);
}STM32FXXX_ADC3;

// INIC
void adc3_enable(void); STM32FXXX_ADC3* adc3(void);

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

