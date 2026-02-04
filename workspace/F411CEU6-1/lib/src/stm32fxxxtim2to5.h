/******************************************************************************
	STM32 XXX TIM 2 to 5
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     22062023
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXTIM2TO5_H_
	#define _STM32FXXXTIM2TO5_H_

/*** Library ***/
//#if defined (STM32F411xE)
	#include "stm32f411ceu6.h"
//#elif defined(STM32F446xx)
//	#include "stm32f446re.h"
//#else
//	void* dev(void){ return NULL; }
//#endif
/*** TIMER 2 to 5 TypeDef ***/
typedef struct{
	void (*b)(void);
	void (*u)(void);
	void (*t)(void);
	void (*cc1)(void);
	void (*cc2)(void);
	void (*cc3)(void);
	void (*cc4)(void);
} tim2to5_callback;
// ( 2 and 5 ) TIM
typedef const struct
{
	/*** Bit Mapping ***/
	TIM_TypeDef* instance;
	/*** Clock and Nvic ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
	/*** Other ***/
	void (*start)(void);
	void (*stop)(void);
	tim2to5_callback* callback;

#if defined(STM32F411CEU6_H)
	STM32F411CEU6_Instance* (*dev)(void);
#elif defined(STM32F446RE_H)
	STM32F446RE_Instance* (*dev)(void);
#else
	void* (*dev)(void);
#endif
}STM32FXXX_TIM2_Handler, STM32FXXX_TIM5_Handler;
// ( 3 and 4 ) TIM
typedef const struct
{
	/*** Clock and Nvic ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
	/*** Other ***/
	void (*start)(void);
	void (*stop)(void);
	tim2to5_callback* callback;

#if defined(STM32F411CEU6_H)
	STM32F411CEU6_Instance* (*dev)(void);
#elif defined(STM32F446RE_H)
	STM32F446RE_Instance* (*dev)(void);
#else
	void* (*dev)(void);
#endif
}STM32FXXX_TIM3_Handler, STM32FXXX_TIM4_Handler;

STM32FXXX_TIM2_Handler* tim2(void);
STM32FXXX_TIM3_Handler* tim3(void);
STM32FXXX_TIM4_Handler* tim4(void);
STM32FXXX_TIM5_Handler* tim5(void);

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

