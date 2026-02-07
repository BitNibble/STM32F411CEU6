/******************************************************************************
	STM32 XXX TIM 1 and 8
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     22062023
Comment:
	
*******************************************************************************/
#ifndef STM32FXXXTIM1AND8_H
	#define STM32FXXXTIM1AND8_H

/*** Library ***/
#include "stm32f411ceu6.h"

/*************************/
/*** TIMER1and8 TypeDef***/
/*************************/
typedef struct{
	void (*b)(void);
	void (*u)(void);
	void (*t)(void);
	void (*cc1)(void);
	void (*cc2)(void);
	void (*cc3)(void);
	void (*cc4)(void);
} tim1and8_callback;

typedef const struct
{
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t value);
	void (*start)(void);
	void (*stop)(void);
	tim1and8_callback* callback;

#if defined(STM32F411CEU6_H)
	STM32F411CEU6_Instance* (*dev)(void);
#elif defined(STM32F446RE_H)
	STM32F446RE_Instance* (*dev)(void);
#else
	void* (*dev)(void);
#endif
}STM32FXXX_TIM1_Handler, STM32FXXX_TIM8_Handler;

STM32FXXX_TIM1_Handler* tim1(void);
STM32FXXX_TIM8_Handler* tim8(void);

#endif
/*** EOF ***/



