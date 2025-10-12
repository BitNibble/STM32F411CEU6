/******************************************************************************
	STM32 XXX TIM 9 to 14
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     22062023
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxtim9to14.h"
#include "stm32fxxxnvic.h"

/************/
/*** TIM9 ***/
/************/
void TIM9_Clock(uint8_t state)
{
	if(state){RCC->APB2ENR |= (1 << RCC_APB2ENR_TIM9EN_Pos);}else{RCC->APB2ENR &= ~(1 << RCC_APB2ENR_TIM9EN_Pos);}
}
void TIM9_Nvic(uint8_t state)
{ // 24
	if(state){set_bit_block(NVIC->ISER, 1, TIM1_BRK_TIM9_IRQn, 1);}else{set_bit_block(NVIC->ICER, 1, TIM1_BRK_TIM9_IRQn, 1);}
}
void TIM9_start(void){ set_reg_Msk(&TIM9->CR1, TIM_CR1_CEN_Msk, 1); }
void TIM9_stop(void){ set_reg_Msk(&TIM9->CR1, TIM_CR1_CEN_Msk, 0); }

/*** TIM9 INIC Procedure & Function Definition ***/
static tim9to14_callback tim9_callback_setup = {0};

static STM32FXXX_TIM9 stm32fxxx_tim9_setup = {
	.clock = TIM9_Clock,
	.nvic = TIM9_Nvic,
	.start = TIM9_start,
	.stop = TIM9_stop,
	.callback = &tim9_callback_setup
};

STM32FXXX_TIM9* tim9(void){ return (STM32FXXX_TIM9*) &stm32fxxx_tim9_setup;}

/*************/
/*** TIM10 ***/
/*************/
void TIM10_Clock(uint8_t state)
{
	if(state){RCC->APB2ENR |= (1 << RCC_APB2ENR_TIM10EN_Pos);}else{RCC->APB2ENR &= ~(1 << RCC_APB2ENR_TIM10EN_Pos);}
}
void TIM10_Nvic(uint8_t state)
{ // 25
	if(state){set_bit_block(NVIC->ISER, 1, TIM1_UP_TIM10_IRQn, 1);} else{set_bit_block(NVIC->ICER, 1, TIM1_UP_TIM10_IRQn, 1);}
}
void TIM10_start(void){ set_reg_Msk(&TIM10->CR1, TIM_CR1_CEN_Msk, 1); }
void TIM10_stop(void){ set_reg_Msk(&TIM10->CR1, TIM_CR1_CEN_Msk, 0); }

/*** TIM10 INIC Procedure & Function Definition ***/
static tim9to14_callback tim10_callback_setup = {0};

static STM32FXXX_TIM10 stm32fxxx_tim10_setup = {
	.clock = TIM10_Clock,
	.nvic = TIM10_Nvic,
	.start = TIM10_start,
	.stop = TIM10_stop,
	.callback = &tim10_callback_setup
};

STM32FXXX_TIM10* tim10(void){ return (STM32FXXX_TIM10*) &stm32fxxx_tim10_setup;}

/*************/
/*** TIM11 ***/
/*************/
void TIM11_Clock(uint8_t state)
{
	if(state){RCC->APB2ENR |= (1 << RCC_APB2ENR_TIM11EN_Pos);}else{RCC->APB2ENR &= ~(1 << RCC_APB2ENR_TIM11EN_Pos);}
}
void TIM11_Nvic(uint8_t state)
{ // 26
	if(state){set_bit_block(NVIC->ISER, 1, TIM1_TRG_COM_TIM11_IRQn, 1);} else{set_bit_block(NVIC->ICER, 1, TIM1_TRG_COM_TIM11_IRQn, 1);}
}
void TIM11_start(void){ set_reg_Msk(&TIM11->CR1, TIM_CR1_CEN_Msk, 1); }
void TIM11_stop(void){ set_reg_Msk(&TIM11->CR1, TIM_CR1_CEN_Msk, 0); }

/*** TIM11 INIC Procedure & Function Definition ***/
static tim9to14_callback tim11_callback_setup = {0};

static STM32FXXX_TIM11 stm32fxxx_tim11_setup = {
	.clock = TIM11_Clock,
	.nvic = TIM11_Nvic,
	.start = TIM11_start,
	.stop = TIM11_stop,
	.callback = &tim11_callback_setup
};

STM32FXXX_TIM11* tim11(void){ return (STM32FXXX_TIM11*) &stm32fxxx_tim11_setup;}

#ifdef STM32F446xx
/*************/
/*** TIM12 ***/
/*************/
void TIM12_Clock(uint8_t state)
{
	if(state){RCC->APB1ENR |= (1 << RCC_APB1ENR_TIM12EN_Pos);}else{RCC->APB1ENR &= ~(1 << RCC_APB1ENR_TIM12EN_Pos);}
}
void TIM12_Nvic(uint8_t state)
{ // 43
	if(state){set_bit_block(NVIC->ISER, 1, TIM8_BRK_TIM12_IRQn, 1);}else{set_bit_block(NVIC->ICER, 1, TIM8_BRK_TIM12_IRQn, 1);}
}
void TIM12_start(void){ set_reg_Msk(&TIM12->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, 1); }
void TIM12_stop(void){ set_reg_Msk(&TIM12->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, 0); }

/*** TIM12 INIC Procedure & Function Definition ***/
static tim9to14_callback tim12_callback_setup = {0};

static STM32FXXX_TIM12 stm32fxxx_tim12_setup = {
	.clock = TIM12_Clock,
	.nvic = TIM12_Nvic,
	.start = TIM12_start,
	.stop = TIM12_stop,
	.callback = &tim12_callback_setup
};

STM32FXXX_TIM12* tim12(void){ return (STM32FXXX_TIM12*) &stm32fxxx_tim12_setup;}

/*************/
/*** TIM13 ***/
/*************/
void TIM13_Clock(uint8_t state)
{
	if(state){
		RCC->APB1ENR |= (1 << RCC_APB1ENR_TIM13EN_Pos); // timer 13 clock enabled
	}else{
		RCC->APB1ENR &= ~(1 << RCC_APB1ENR_TIM13EN_Pos); //timer 13 clock disabled
	}
}
void TIM13_Nvic(uint8_t state)
{ // 44
	if(state){set_bit_block(NVIC->ISER, 1, TIM8_UP_TIM13_IRQn, 1);}else{set_bit_block(NVIC->ICER, 1, TIM8_UP_TIM13_IRQn, 1);}
}
void TIM13_start(void){ set_reg_Msk(&TIM13->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, ON); }
void TIM13_stop(void){ set_reg_Msk(&TIM13->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, OFF); }

/*** TIM13 INIC Procedure & Function Definition ***/
static tim9to14_callback tim13_callback_setup = {0};

static STM32FXXX_TIM13 stm32fxxx_tim13_setup = {
	.clock = TIM13_Clock,
	.nvic = TIM13_Nvic,
	.start = TIM13_start,
	.stop = TIM13_stop,
	.callback = &tim13_callback_setup
};

STM32FXXX_TIM13* tim13(void){ return (STM32FXXX_TIM13*) &stm32fxxx_tim13_setup;}

/*************/
/*** TIM14 ***/
/*************/
void TIM14_Clock(uint8_t state)
{
	if(state){RCC->APB1ENR |= (1 << RCC_APB1ENR_TIM14EN_Pos);}else{RCC->APB1ENR &= ~(1 << RCC_APB1ENR_TIM14EN_Pos);}
}
void TIM14_Nvic(uint8_t state)
{ // 45
	if(state){set_bit_block(NVIC->ISER, 1, TIM8_TRG_COM_TIM14_IRQn, 1);}else{set_bit_block(NVIC->ICER, 1, TIM8_TRG_COM_TIM14_IRQn, 1);}
}
void TIM14_start(void){ set_reg_Msk(&TIM14->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, ON); }
void TIM14_stop(void){ set_reg_Msk(&TIM14->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, OFF); }

/*** TIM14 INIC Procedure & Function Definition ***/
static tim9to14_callback tim14_callback_setup = {0};

static STM32FXXX_TIM14 stm32fxxx_tim14_setup = {
	.clock = TIM14_Clock,
	.nvic = TIM14_Nvic,
	.start = TIM14_start,
	.stop = TIM14_stop,
	.callback = &tim14_callback_setup
};

STM32FXXX_TIM14* tim14(void){ return (STM32FXXX_TIM14*) &stm32fxxx_tim14_setup;}

#endif

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

/*** EOF ***/

