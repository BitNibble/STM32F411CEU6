/******************************************************************************
	STM32 XXX TIM 1 and 8
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 22062023
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXTIM1AND8_H_
	#define _STM32FXXXTIM1AND8_H_
/*** Library ***/
#include "stm32fxxxinstance.h"
/*************************/
/*** TIMER1and8 TypeDef***/
/*************************/
typedef struct
{
	/*** Bit Field ***/
	TIM_TypeDef* instance;
	/*** Other ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t value);
}STM32FXXX_TIM1, STM32FXXX_TIM8;
/*******************/
/*** INIC 1 and 8 ***/
/*******************/
void tim1_enable(void);
STM32FXXX_TIM1* tim1(void);
void tim8_enable(void);
STM32FXXX_TIM8* tim8(void);
/****************************************/
/*** TIM1 Procedure & Function Header ***/
/****************************************/
void STM32FXXXTim1Clock(uint8_t state);
void STM32FXXXTim1Nvic(uint8_t value);
/****************************************/
/*** TIM8 Procedure & Function Header ***/
/****************************************/
void STM32FXXXTim8Clock(uint8_t state);
void STM32FXXXTim8Nvic(uint8_t value);
/****************************************/
/*** INTERRUPT TIM1 CC CALLBACK HEADER ***/
void tim1_u_callback(void)__attribute__((weak));
void tim1_cc1_callback(void)__attribute__((weak));
void tim1_cc2_callback(void)__attribute__((weak));
void tim1_t_callback(void)__attribute__((weak));
void tim1_com_callback(void)__attribute__((weak));
void tim1_b_callback(void)__attribute__((weak));
/*** INTERRUPT HEADER ***/
void TIM1_BRK_TIM9_IRQHandler(void);
void TIM1_UP_TIM10_IRQHandler(void);
void TIM1_TRG_COM_TIM11_IRQHandler(void);
void TIM1_CC_IRQHandler(void);
void TIM8_BRK_TIM12_IRQHandler(void);
void TIM8_UP_TIM13_IRQHandler(void);
void TIM8_TRG_COM_TIM14_IRQHandler(void);
void TIM8_CC_IRQHandler(void);

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

