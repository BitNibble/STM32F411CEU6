/******************************************************************************
	STM32 XXX SRAM
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     19062023
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXSRAM_H_
	#define _STM32FXXXSRAM_H_

/*** Library ***/
#include "stm32f411ceu6.h"
/*** SRAM TypeDef ***/
typedef struct
{
	/*** Bit Mapping ***/
	/*** Other ***/
	void (*access)(void);
}STM32FXXX_SRAM;

void sram_enable(void); STM32FXXX_SRAM* sram(void);

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

