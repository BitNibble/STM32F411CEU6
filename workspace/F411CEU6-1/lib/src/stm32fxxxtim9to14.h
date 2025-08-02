/******************************************************************************
	STM32 XXX TIM 9 to 14
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     22062023
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXTIM9TO14_H_
	#define _STM32FXXXTIM9TO14_H_

/*** Library ***/
#include "stm32fxxxinstance.h"
#include "timer_irq.h"
/*** TIMER 9 TO 14 TypeDef***/
// ( 9/12 ) TIM
typedef struct
{
	/*** Bit Field ***/
	TIM_TypeDef* instance;
	/*** Clock and Nvic ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
	/*** Other ***/
	void (*start)(void);
	void (*stop)(void);
}STM32FXXX_TIM9, STM32FXXX_TIM12;
// ( 10/11/13/14 ) TIM
typedef struct
{
	/*** Bit Field ***/
	TIM_TypeDef* instance;
	/*** Clock and Nvic ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
	/*** Other ***/
	void (*start)(void);
	void (*stop)(void);
}STM32FXXX_TIM10, STM32FXXX_TIM11, STM32FXXX_TIM13, STM32FXXX_TIM14;

void tim9_enable(void); STM32FXXX_TIM9* tim9(void);
void tim10_enable(void); STM32FXXX_TIM10* tim10(void);
void tim11_enable(void); STM32FXXX_TIM11* tim11(void);
void tim12_enable(void); STM32FXXX_TIM12* tim12(void);
void tim13_enable(void); STM32FXXX_TIM13* tim13(void);
void tim14_enable(void); STM32FXXX_TIM14* tim14(void);

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

