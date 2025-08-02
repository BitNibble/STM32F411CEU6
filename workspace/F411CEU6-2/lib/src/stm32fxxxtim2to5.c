/******************************************************************************
	STM32 XXX TIM 2 to 5
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     22062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxtim2to5.h"

/*** File Variables ***/
static STM32FXXX_TIM2 stm32fxxx_tim2 = {0};
static STM32FXXX_TIM3 stm32fxxx_tim3 = {0};
static STM32FXXX_TIM4 stm32fxxx_tim4 = {0};
static STM32FXXX_TIM5 stm32fxxx_tim5 = {0};
/************/
/*** TIM2 ***/
/************/
void TIM2_Clock(uint8_t state)
{
	if(state){RCC->APB1ENR |= (1 << RCC_APB1ENR_TIM2EN_Pos);}else{RCC->APB1ENR &= ~(1 << RCC_APB1ENR_TIM2EN_Pos);}
}
void TIM2_Nvic(uint8_t state)
{ // 28
	if(state){set_bit_block(NVIC->ISER, 1, TIM2_IRQn, 1);} else{set_bit_block(NVIC->ICER, 1, TIM2_IRQn, 1);}
}
void TIM2_start(void){ set_reg_Msk(&TIM2->CR1, TIM_CR1_CEN_Msk, ON); }
void TIM2_stop(void){ set_reg_Msk(&TIM2->CR1, TIM_CR1_CEN_Msk, OFF); }
/************/
/*** TIM3 ***/
/************/
void TIM3_Clock(uint8_t state)
{
	if(state){RCC->APB1ENR |= (1 << RCC_APB1ENR_TIM3EN_Pos);}else{RCC->APB1ENR &= ~(1 << RCC_APB1ENR_TIM3EN_Pos);}
}
void TIM3_Nvic(uint8_t state)
{ // 29
	if(state){set_bit_block(NVIC->ISER, 1, TIM3_IRQn, 1);} else{set_bit_block(NVIC->ICER, 1, TIM3_IRQn, 1);}
}
void TIM3_start(void){ set_reg_Msk(&TIM3->CR1, TIM_CR1_CEN_Msk, ON); }
void TIM3_stop(void){ set_reg_Msk(&TIM3->CR1, TIM_CR1_CEN_Msk, OFF); }
/************/
/*** TIM4 ***/
/************/
void TIM4_Clock(uint8_t state)
{
	if(state){RCC->APB1ENR |= (1 << RCC_APB1ENR_TIM4EN_Pos);}else{RCC->APB1ENR &= ~(1 << RCC_APB1ENR_TIM4EN_Pos);}
}
void TIM4_Nvic(uint8_t state)
{ // 30
	if(state){set_bit_block(NVIC->ISER, 1, TIM4_IRQn, 1);} else{set_bit_block(NVIC->ICER, 1, TIM4_IRQn, 1);}
}
void TIM4_start(void){ set_reg_Msk(&TIM4->CR1, TIM_CR1_CEN_Msk, ON); }
void TIM4_stop(void){ set_reg_Msk(&TIM4->CR1, TIM_CR1_CEN_Msk, OFF); }
/************/
/*** TIM5 ***/
/************/
void TIM5_Clock(uint8_t state)
{
	if(state){RCC->APB1ENR |= (1 << RCC_APB1ENR_TIM5EN_Pos);}else{RCC->APB1ENR &= ~(1 << RCC_APB1ENR_TIM5EN_Pos);}
}
void TIM5_Nvic(uint8_t state)
{ // 50
	if(state){set_bit_block(NVIC->ISER, 1, TIM5_IRQn, 1);} else{set_bit_block(NVIC->ICER, 1, TIM5_IRQn, 1);}
}
void TIM5_start(void){ set_reg_Msk(&TIM5->CR1, TIM_CR1_CEN_Msk, ON); }
void TIM5_stop(void){ set_reg_Msk(&TIM5->CR1, TIM_CR1_CEN_Msk, OFF); }
/*** TIM2 INIC Procedure & Function Definition ***/
void tim2_enable(void)
{
	TIM2_Clock(ON);
	/*** TIM2 Bit Mapping Link ***/
	stm32fxxx_tim2.instance = TIM2;
	// CLOCK
	stm32fxxx_tim2.clock = TIM2_Clock;
	// NVIC
	stm32fxxx_tim2.nvic = TIM2_Nvic;
	/*** Procedures ***/
	/*** Other ***/
	stm32fxxx_tim2.start = TIM2_start;
	stm32fxxx_tim2.stop = TIM2_stop;
	//return &stm32fxxx_tim2;
}

STM32FXXX_TIM2* tim2(void){ return (STM32FXXX_TIM2*) &stm32fxxx_tim2; }

/*** TIM3 INIC Procedure & Function Definition ***/
void tim3_enable(void)
{
	TIM3_Clock(ON);
	/*** TIM3 Bit Mapping Link ***/
	stm32fxxx_tim3.instance = TIM3;
	// CLOCK
	stm32fxxx_tim3.clock = TIM3_Clock;
	// NVIC
	stm32fxxx_tim3.nvic = TIM3_Nvic;
	/*** Procedures ***/
	/*** Other ***/
	stm32fxxx_tim3.start = TIM3_start;
	stm32fxxx_tim3.stop = TIM3_stop;
	//return &stm32fxxx_tim3;
}

STM32FXXX_TIM3* tim3(void){ return (STM32FXXX_TIM3*) &stm32fxxx_tim3; }

/*** TIM4 INIC Procedure & Function Definition ***/
void tim4_enable(void)
{
	TIM4_Clock(ON);
	/*** TIM4 Bit Mapping Link ***/
	stm32fxxx_tim4.instance = TIM4;
	// CLOCK
	stm32fxxx_tim4.clock = TIM4_Clock;
	// NVIC
	stm32fxxx_tim4.nvic = TIM4_Nvic;
	/*** Procedures ***/
	/*** Other ***/
	stm32fxxx_tim4.start = TIM4_start;
	stm32fxxx_tim4.stop = TIM4_stop;
	//return &stm32fxxx_tim4;
}

STM32FXXX_TIM4* tim4(void){ return (STM32FXXX_TIM4*) &stm32fxxx_tim4; }

/*** TIM5 INIC Procedure & Function Definition ***/
void tim5_enable(void)
{
	TIM5_Clock(ON);
	/*** TIM5 Bit Mapping Link ***/
	stm32fxxx_tim5.instance = TIM5;
	// CLOCK
	stm32fxxx_tim5.clock = TIM5_Clock;
	// NVIC
	stm32fxxx_tim5.nvic = TIM5_Nvic;
	/*** Procedures ***/
	/*** Other ***/
	stm32fxxx_tim5.start = TIM5_start;
	stm32fxxx_tim5.stop = TIM5_stop;
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

