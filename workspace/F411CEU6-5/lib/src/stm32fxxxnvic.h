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
typedef const struct
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

#if defined(STM32F411CEU6_H)
	STM32F411CEU6_Instance* (*dev)(void);
#elif defined(STM32F446RE_H)
	STM32F446RE_Instance* (*dev)(void);
#else
	void* (*dev)(void);
#endif
}STM32FXXX_NVIC_Handler;

STM32FXXX_NVIC_Handler* nvic(void);

#endif
/*** EOF ***/



