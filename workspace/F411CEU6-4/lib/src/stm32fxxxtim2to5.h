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
#include "stm32f411ceu6.h"
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
typedef struct
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
}STM32FXXX_TIM2, STM32FXXX_TIM5;
// ( 3 and 4 ) TIM
typedef struct
{
	/*** Clock and Nvic ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
	/*** Other ***/
	void (*start)(void);
	void (*stop)(void);
	tim2to5_callback* callback;
}STM32FXXX_TIM3, STM32FXXX_TIM4;

void tim2_enable(void); STM32FXXX_TIM2* tim2(void);
void tim3_enable(void); STM32FXXX_TIM3* tim3(void);
void tim4_enable(void); STM32FXXX_TIM4* tim4(void);
void tim5_enable(void); STM32FXXX_TIM5* tim5(void);

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

