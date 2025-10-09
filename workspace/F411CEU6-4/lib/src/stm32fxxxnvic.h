/******************************************************************************
	STM32FXXX NVIC
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     19062023
Comment:
	Interrupt Vector
*******************************************************************************/
#ifndef STM32FXXXNVIC_H
	#define STM32FXXXNVIC_H

/*** Library ***/
#include "stm32f411ceu6.h"
/*** NVIC TypeDef ***/
typedef struct
{
	/*** Bit Mapping ***/
	void (*set_enable)( uint8_t IRQn );
	void (*clear_enable)( uint8_t IRQn );
	void (*set_clear)(uint8_t irq_num, uint8_t state);
	void (*set_pending)( uint8_t IRQn );
	void (*clear_pending)( uint8_t IRQn );
	uint8_t (*active)( uint8_t IRQn );
	void (*priority)(uint32_t IRQn, uint32_t priority);
	void (*trigger)(uint32_t IRQn);
	/*** Other ***/
}STM32FXXX_NVIC;

STM32FXXX_NVIC* nvic(void);

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

