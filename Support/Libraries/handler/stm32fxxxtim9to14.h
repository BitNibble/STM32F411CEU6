/******************************************************************************
	STM32 XXX TIM 9 to 14
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 22062023
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXTIM9TO14_H_
	#define _STM32FXXXTIM9TO14_H_
/*** Library ***/
#include "stm32fxxxinstance.h"
/*** TIMER 9 TO 14 TypeDef***/
// ( 9/12 ) TIM
typedef struct
{
	/*** Bit Field ***/
	TIM_TypeDef* instance;
	/*** Other ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
}STM32FXXX_TIM9, STM32FXXX_TIM12;
// ( 10/11/13/14 ) TIM
typedef struct
{
	/*** Bit Field ***/
	TIM_TypeDef* instance;
	/*** Other ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
}STM32FXXX_TIM10, STM32FXXX_TIM11, STM32FXXX_TIM13, STM32FXXX_TIM14;
/************************/
/*** INIC TIM 9 to 14 ***/
/************************/
void tim9_enable(void);
STM32FXXX_TIM9* tim9(void);
void tim10_enable(void);
STM32FXXX_TIM10* tim10(void);
void tim11_enable(void);
STM32FXXX_TIM11* tim11(void);
void tim12_enable(void);
STM32FXXX_TIM12* tim12(void);
void tim13_enable(void);
STM32FXXX_TIM13* tim13(void);
void tim14_enable(void);
STM32FXXX_TIM14* tim14(void);
/****************************************/
/*** TIM9 Procedure & Function Header ***/
/****************************************/
void STM32FXXXTim9Clock(uint8_t state);
void STM32FXXXTim9Nvic(uint8_t state);
/*****************************************/
/*** TIM10 Procedure & Function Header ***/
/*****************************************/
void STM32FXXXTim10Clock(uint8_t state);
void STM32FXXXTim10Nvic(uint8_t state);
/*****************************************/
/*** TIM11 Procedure & Function Header ***/
/*****************************************/
void STM32FXXXTim11Clock(uint8_t state);
void STM32FXXXTim11Nvic(uint8_t state);
/*****************************************/
/*** TIM12 Procedure & Function Header ***/
/*****************************************/
void STM32FXXXTim12Clock(uint8_t state);
void STM32FXXXTim12Nvic(uint8_t state);
/*****************************************/
/*** TIM13 Procedure & Function Header ***/
/*****************************************/
void STM32FXXXTim13Clock(uint8_t state);
void STM32FXXXTim13Nvic(uint8_t state);
/*****************************************/
/*** TIM14 Procedure & Function Header ***/
/*****************************************/
void STM32FXXXTim14Clock(uint8_t state);
void STM32FXXXTim14Nvic(uint8_t state);
/*** INTERRUPT HEADER ***/
void TIM1_BRK_TIM9_IRQHandler(void);
void TIM1_UP_TIM10_IRQHandler(void);
void TIM1_TRG_COM_TIM11_IRQHandler(void);
void TIM8_BRK_TIM12_IRQHandler(void);
void TIM8_UP_TIM13_IRQHandler(void);
void TIM8_TRG_COM_TIM14_IRQHandler(void);

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

