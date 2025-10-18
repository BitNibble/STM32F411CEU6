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
#include "stm32fxxxnvic.h"

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
void TIM2_start(void){ set_reg_Msk(&TIM2->CR1, TIM_CR1_CEN_Msk, 1); }
void TIM2_stop(void){ set_reg_Msk(&TIM2->CR1, TIM_CR1_CEN_Msk, 0); }

/*** TIM2 INIC Procedure & Function Definition ***/
static tim2to5_callback tim2_callback_setup = {0};

static STM32FXXX_TIM2_Handler stm32fxxx_tim2_setup = {
	.clock = TIM2_Clock,
	.nvic = TIM2_Nvic,
	.start = TIM2_start,
	.stop = TIM2_stop,
	.callback = &tim2_callback_setup,

#if defined(STM32F411CEU6_H)
	.dev = dev
#endif
};

STM32FXXX_TIM2_Handler* tim2(void){ return (STM32FXXX_TIM2_Handler*) &stm32fxxx_tim2_setup;}

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
void TIM3_start(void){ set_reg_Msk(&TIM3->CR1, TIM_CR1_CEN_Msk, 1); }
void TIM3_stop(void){ set_reg_Msk(&TIM3->CR1, TIM_CR1_CEN_Msk, 0); }

/*** TIM3 INIC Procedure & Function Definition ***/
static tim2to5_callback tim3_callback_setup = {0};

static STM32FXXX_TIM3_Handler stm32fxxx_tim3_setup = {
	.clock = TIM3_Clock,
	.nvic = TIM3_Nvic,
	.start = TIM3_start,
	.stop = TIM3_stop,
	.callback = &tim3_callback_setup,

#if defined(STM32F411CEU6_H)
	.dev = dev
#endif
};

STM32FXXX_TIM3_Handler* tim3(void){ return (STM32FXXX_TIM3_Handler*) &stm32fxxx_tim3_setup;}

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
void TIM4_start(void){ set_reg_Msk(&TIM4->CR1, TIM_CR1_CEN_Msk, 1); }
void TIM4_stop(void){ set_reg_Msk(&TIM4->CR1, TIM_CR1_CEN_Msk, 0); }

/*** TIM4 INIC Procedure & Function Definition ***/
static tim2to5_callback tim4_callback_setup = {0};

static STM32FXXX_TIM4_Handler stm32fxxx_tim4_setup = {
	.clock = TIM4_Clock,
	.nvic = TIM4_Nvic,
	.start = TIM4_start,
	.stop = TIM4_stop,
	.callback = &tim4_callback_setup,

#if defined(STM32F411CEU6_H)
	.dev = dev
#endif
};

STM32FXXX_TIM4_Handler* tim4(void){ return (STM32FXXX_TIM4_Handler*) &stm32fxxx_tim4_setup;}

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
void TIM5_start(void){ set_reg_Msk(&TIM5->CR1, TIM_CR1_CEN_Msk, 1); }
void TIM5_stop(void){ set_reg_Msk(&TIM5->CR1, TIM_CR1_CEN_Msk, 0); }

/*** TIM5 INIC Procedure & Function Definition ***/
static tim2to5_callback tim5_callback_setup = {0};

static STM32FXXX_TIM5_Handler stm32fxxx_tim5_setup = {
	.clock = TIM5_Clock,
	.nvic = TIM5_Nvic,
	.start = TIM5_start,
	.stop = TIM5_stop,
	.callback = &tim5_callback_setup,

#if defined(STM32F411CEU6_H)
	.dev = dev
#endif
};

STM32FXXX_TIM5_Handler* tim5(void){ return (STM32FXXX_TIM5_Handler*) &stm32fxxx_tim5_setup;}

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

