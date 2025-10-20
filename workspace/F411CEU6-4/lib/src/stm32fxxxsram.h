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
#if defined (STM32F411xE)
	#include "stm32f411ceu6.h"
#elif defined(STM32F446xx)
	#include "stm32f446re.h"
else
	void* dev(void){ return NULL; }
#endif
/*** SRAM TypeDef ***/
typedef struct
{
	/*** Bit Mapping ***/
	/*** Other ***/
	void (*access)(void);

#if defined(STM32F411CEU6_H)
	STM32F411CEU6_Handler* (*dev)(void);
#elif defined(STM32F446RE_H)
	STM32F446RE_Handler* (*dev)(void);
else
	void* (*dev)(void);
#endif
}STM32FXXX_SRAM_Handler;

STM32FXXX_SRAM_Handler* sram(void);

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

