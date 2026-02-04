/******************************************************************************
	STM32 XXX CRC
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     19062023
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXCRC_H_
	#define _STM32FXXXCRC_H_

/*** Library ***/
//#if defined (STM32F411xE)
	#include "stm32f411ceu6.h"
//#elif defined(STM32F446xx)
//	#include "stm32f446re.h"
//#endif
/*** CRC TypeDef ***/
typedef const struct
{
	/*** Bit Mapping ***/
	void (*dr)(uint32_t value);
	uint32_t (*get_dr)(void);
	void (*idr)(uint8_t value);
	uint8_t (*get_idr)(void);
	void (*reset)(void);
	/*** Clock and Nvic ***/
	void (*clock)(uint8_t state);

#if defined(STM32F411CEU6_H)
	STM32F411CEU6_Instance* (*dev)(void);
#elif defined(STM32F446RE_H)
	STM32F446RE_Instance* (*dev)(void);
#else
	void* (*dev)(void);
#endif
}STM32FXXX_CRC_Handler;

STM32FXXX_CRC_Handler* crc(void);

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

