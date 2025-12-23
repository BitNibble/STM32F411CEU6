/******************************************************************************
	STM32 XXX TIM 9 to 14
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     22062023
*******************************************************************************/
#ifndef _STM32FXXXTIM9TO14_H_
	#define _STM32FXXXTIM9TO14_H_

/*** Library ***/
#if defined (STM32F411xE)
	#include "stm32f411ceu6.h"
#elif defined(STM32F446xx)
	#include "stm32f446re.h"
#else
	void* dev(void){ return NULL; }
#endif
/*** TIMER 9 TO 14 TypeDef***/
typedef struct{
	void (*b)(void);
	void (*u)(void);
	void (*t)(void);
	void (*cc1)(void);
	void (*cc2)(void);
	void (*cc3)(void);
	void (*cc4)(void);
} tim9to14_callback;
// ( 9/12 ) TIM
typedef const struct
{
	/*** Clock and Nvic ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
	/*** Other ***/
	void (*start)(void);
	void (*stop)(void);
	tim9to14_callback* callback;

#if defined(STM32F411CEU6_H)
	STM32F411CEU6_Instance* (*dev)(void);
#elif defined(STM32F446RE_H)
	STM32F446RE_Instance* (*dev)(void);
#else
	void* (*dev)(void);
#endif
}STM32FXXX_TIM9_Handler, STM32FXXX_TIM12_Handler;
// ( 10/11/13/14 ) TIM
typedef const struct
{
	/*** Clock and Nvic ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
	/*** Other ***/
	void (*start)(void);
	void (*stop)(void);
	tim9to14_callback* callback;

#if defined(STM32F411CEU6_H)
	STM32F411CEU6_Instance* (*dev)(void);
#elif defined(STM32F446RE_H)
	STM32F446RE_Instance* (*dev)(void);
#else
	void* (*dev)(void);
#endif
}STM32FXXX_TIM10_Handler, STM32FXXX_TIM11_Handler, STM32FXXX_TIM13_Handler, STM32FXXX_TIM14_Handler;

STM32FXXX_TIM9_Handler* tim9(void);
STM32FXXX_TIM10_Handler* tim10(void);
STM32FXXX_TIM11_Handler* tim11(void);
STM32FXXX_TIM12_Handler* tim12(void);
STM32FXXX_TIM13_Handler* tim13(void);
STM32FXXX_TIM14_Handler* tim14(void);

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

