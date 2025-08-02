/******************************************************************************
	STM32 XXX TIM 2 to 5
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 22062023
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXTIM2TO5_H_
	#define _STM32FXXXTIM2TO5_H_
/*** Library ***/
#include "stm32fxxxinstance.h"
/*** TIMER 2 to 5 TypeDef ***/
// ( 2 and 5 ) TIM
typedef struct
{
	/*** Bit Mapping ***/
	TIM_TypeDef* instance;
	/*** Other ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
}STM32FXXX_TIM2, STM32FXXX_TIM5;
// ( 3 and 4 ) TIM
typedef struct
{

	/*** Bit Mapping ***/
	TIM_TypeDef* instance;
	/*** Other ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
}STM32FXXX_TIM3, STM32FXXX_TIM4;
/***********************/
/*** INIC TIM 2 to 5 ***/
/***********************/
void tim2_enable(void);
STM32FXXX_TIM2* tim2(void);
void tim3_enable(void);
STM32FXXX_TIM3* tim3(void);
void tim4_enable(void);
STM32FXXX_TIM4* tim4(void);
void tim5_enable(void);
STM32FXXX_TIM5* tim5(void);
/****************************************/
/*** TIM2 Procedure & Function Header ***/
/****************************************/
void STM32FXXXTim2Clock(uint8_t state);
void STM32FXXXTim2Nvic(uint8_t state);
/****************************************/
/*** TIM3 Procedure & Function Header ***/
/****************************************/
void STM32FXXXTim3Clock(uint8_t state);
void STM32FXXXTim3Nvic(uint8_t state);
/****************************************/
/*** TIM4 Procedure & Function Header ***/
/****************************************/
void STM32FXXXTim4Clock(uint8_t state);
void STM32FXXXTim4Nvic(uint8_t state);
/****************************************/
/*** TIM5 Procedure & Function Header ***/
/****************************************/
void STM32FXXXTim5Clock(uint8_t state);
void STM32FXXXTim5Nvic(uint8_t state);
/*** TIM5 Bit Mapping Header ***/
// CNT
void STM32FXXXTim5_cnt(uint32_t value);
uint32_t STM32FXXXTim5_get_cnt(void);
// PSC
void STM32FXXXTim5_psc(uint16_t value);
// ARR
void STM32FXXXTim5_arr(uint32_t value);
// CCR1
void STM32FXXXTim5_ccr1(uint32_t value);
// CCR2
void STM32FXXXTim5_ccr2(uint32_t value);
// CCR3
void STM32FXXXTim5_ccr3(uint32_t value);
// CCR4
void STM32FXXXTim5_ccr4(uint32_t value);
// DMAR
void STM32FXXXTim5_dmab(uint16_t value);
uint16_t STM32FXXXTim5_get_dmab(void);
// OR
void STM32FXXXTim5_ti4_rmp(uint8_t value);

/*** INTERRUPT HEADER ***/
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void TIM5_IRQHandler(void);

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

