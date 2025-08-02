/******************************************************************************
	STM32 XXX TIM 6 and 7
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     22062023
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXTIM6AND7_H_
	#define _STM32FXXXTIM6AND7_H_

/*** Library ***/
#include "stm32fxxxinstance.h"
#include "timer_irq.h"
/*** TIMER TypeDef***/
// ( 6 and 7 ) TIM 
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
}STM32FXXX_TIM6, STM32FXXX_TIM7;

void tim6_enable(void); STM32FXXX_TIM6* tim6(void);
void tim7_enable(void); STM32FXXX_TIM7* tim7(void);

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

