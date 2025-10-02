/******************************************************************************
	STM32 XXX ADC2
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     28022024
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXADC2_H_
	#define _STM32FXXXADC2_H_

/*** Library ***/
#include "stm32f411ceu6.h"
/*** ADC TypeDef ***/
// ADC -> ADC2
typedef struct
{
	/*** Clock and Nvic ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
	/*** Other ***/
	void (*start)(void);
	void (*stop)(void);
}STM32FXXX_ADC2;

// INIC
void adc2_enable(void); STM32FXXX_ADC2* adc2(void);

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

