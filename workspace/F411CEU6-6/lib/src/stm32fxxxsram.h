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
typedef const struct
{
	/*** Bit Mapping ***/
	/*** Other ***/
	void (*access)(void);

#if defined(STM32F411CEU6_H)
	STM32F411CEU6_Instance* (*dev)(void);
#elif defined(STM32F446RE_H)
	STM32F446RE_Instance* (*dev)(void);
#else
	void* (*dev)(void);
#endif
}STM32FXXX_SRAM_Handler;

STM32FXXX_SRAM_Handler* sram(void);

#endif
/*** EOF ***/



