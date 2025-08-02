/******************************************************************************
	STM32 XXX TIM 2 to 5
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 22062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxtim2to5.h"

#define ON 1
#define OFF 0
/*** File Variables ***/
static STM32FXXX_TIM2 stm32fxxx_tim2 = {0};
static STM32FXXX_TIM3 stm32fxxx_tim3 = {0};
static STM32FXXX_TIM4 stm32fxxx_tim4 = {0};
static STM32FXXX_TIM5 stm32fxxx_tim5 = {0};
/*** TIMER Procedure & Function Definition ***/
/************/
/*** TIM2 ***/
/************/
void STM32FXXXTim2Clock(uint8_t state)
{
	if(state){RCC->APB1ENR |= (1 << 0);}else{RCC->APB1ENR &= ~(1 << 0);}
}
void STM32FXXXTim2Nvic(uint8_t state)
{ // 28
	if(state){set_bit_block(NVIC->ISER, 1, TIM2_IRQn, 1);} else{set_bit_block(NVIC->ICER, 1, TIM2_IRQn, 1);}
}
/************/
/*** TIM3 ***/
/************/
void STM32FXXXTim3Clock(uint8_t state)
{
	if(state){RCC->APB1ENR |= (1 << 1);}else{RCC->APB1ENR &= ~(1 << 1);}
}
void STM32FXXXTim3Nvic(uint8_t state)
{ // 29
	if(state){set_bit_block(NVIC->ISER, 1, TIM3_IRQn, 1);} else{set_bit_block(NVIC->ICER, 1, TIM3_IRQn, 1);}
}
/************/
/*** TIM4 ***/
/************/
void STM32FXXXTim4Clock(uint8_t state)
{
	if(state){RCC->APB1ENR |= (1 << 2);}else{RCC->APB1ENR &= ~(1 << 2);}
}
void STM32FXXXTim4Nvic(uint8_t state)
{ // 30
	if(state){set_bit_block(NVIC->ISER, 1, TIM4_IRQn, 1);} else{set_bit_block(NVIC->ICER, 1, TIM4_IRQn, 1);}
}
/************/
/*** TIM5 ***/
/************/
void STM32FXXXTim5Clock(uint8_t state)
{
	if(state){RCC->APB1ENR |= (1 << 3);}else{RCC->APB1ENR &= ~(1 << 3);}
}
void STM32FXXXTim5Nvic(uint8_t state)
{ // 50
	if(state){set_bit_block(NVIC->ISER, 1, TIM5_IRQn, 1);} else{set_bit_block(NVIC->ICER, 1, TIM5_IRQn, 1);}
}
/*** TIM2 INIC Procedure & Function Definition ***/
void tim2_enable(void)
{
	STM32FXXXTim2Clock(ON);
	/*** TIM2 Bit Mapping Link ***/
	stm32fxxx_tim2.instance = TIM2;
	// CLOCK
	stm32fxxx_tim2.clock = STM32FXXXTim2Clock;
	// NVIC
	stm32fxxx_tim2.nvic = STM32FXXXTim2Nvic;

	//return &stm32fxxx_tim2;
}

STM32FXXX_TIM2* tim2(void){ return (STM32FXXX_TIM2*) &stm32fxxx_tim2; }

/*** TIM3 INIC Procedure & Function Definition ***/
void tim3_enable(void)
{
	STM32FXXXTim3Clock(ON);
	/*** TIM3 Bit Mapping Link ***/
	stm32fxxx_tim3.instance = TIM3;
	// CLOCK
	stm32fxxx_tim3.clock = STM32FXXXTim3Clock;
	// NVIC
	stm32fxxx_tim3.nvic = STM32FXXXTim3Nvic;

	//return &stm32fxxx_tim3;
}

STM32FXXX_TIM3* tim3(void){ return (STM32FXXX_TIM3*) &stm32fxxx_tim3; }

/*** TIM4 INIC Procedure & Function Definition ***/
void tim4_enable(void)
{
	STM32FXXXTim4Clock(ON);
	/*** TIM4 Bit Mapping Link ***/
	stm32fxxx_tim4.instance = TIM4;
	// CLOCK
	stm32fxxx_tim4.clock = STM32FXXXTim4Clock;
	// NVIC
	stm32fxxx_tim4.nvic = STM32FXXXTim4Nvic;

	//return &stm32fxxx_tim4;
}

STM32FXXX_TIM4* tim4(void){ return (STM32FXXX_TIM4*) &stm32fxxx_tim4; }

/*** TIM5 INIC Procedure & Function Definition ***/
void tim5_enable(void)
{
	STM32FXXXTim5Clock(ON);
	/*** TIM5 Bit Mapping Link ***/
	stm32fxxx_tim5.instance = TIM5;
	// CLOCK
	stm32fxxx_tim5.clock = STM32FXXXTim5Clock;
	// NVIC
	stm32fxxx_tim5.nvic = STM32FXXXTim5Nvic;

	//return &stm32fxxx_tim5;
}

STM32FXXX_TIM5* tim5(void){ return (STM32FXXX_TIM5*) &stm32fxxx_tim5; }

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

