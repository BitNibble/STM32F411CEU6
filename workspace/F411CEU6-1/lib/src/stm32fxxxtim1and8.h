/******************************************************************************
	STM32 XXX TIM 1 and 8
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     22062023
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXTIM1AND8_H_
	#define _STM32FXXXTIM1AND8_H_

/*** Library ***/
#include "stm32f411ceu6.h"
#include "timer_irq.h"
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

typedef struct
{
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t value);
	void (*start)(void);
	void (*stop)(void);
	tim1and8_callback callback;
}STM32FXXX_TIM1, STM32FXXX_TIM8;

void tim1_enable(void); STM32FXXX_TIM1* tim1(void);
void tim8_enable(void); STM32FXXX_TIM8* tim8(void);

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

