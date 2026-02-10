/******************************************************************************
	STM32 XXX TIM 6 and 7
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     22062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxtim6and7.h"
#include "stm32fxxxnvic.h"

#ifdef STM32F446xx
/************/
/*** TIM6 ***/
/************/
void TIM6_Clock(uint8_t state)
{
	if(state){RCC->APB1ENR |= (1 << RCC_APB1ENR_TIM6EN_Pos);}else{RCC->APB1ENR &= ~(1 << RCC_APB1ENR_TIM6EN_Pos);}
}
void TIM6_Nvic(uint8_t state)
{ // 54
	if(state){set_bit_block(NVIC->ISER, 1, TIM6_DAC_IRQn, 1);}else{set_bit_block(NVIC->ICER, 1, TIM6_DAC_IRQn, 1);}
}
void TIM6_start(void){ set_reg_Msk_Pos(&TIM6->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, 1); }
void TIM6_stop(void){ set_reg_Msk_Pos(&TIM6->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, 0); }

/*** TIM6 INIC Procedure & Function Definition ***/
static tim6and7_callback tim6_callback_setup = {0};

static STM32FXXX_TIM6_Handler stm32fxxx_tim6_setup = {
	.clock = TIM6_Clock,
	.nvic = TIM6_Nvic,
	.start = TIM6_start,
	.stop = TIM6_stop,
	.callback = &tim6_callback_setup,
	.dev = dev
};

STM32FXXX_TIM6_Handler* tim6(void){ return (STM32FXXX_TIM6_Handler*) &stm32fxxx_tim6_setup;}

/************/
/*** TIM7 ***/
/************/
void TIM7_Clock(uint8_t state)
{
	if(state){RCC->APB1ENR |= (1 << RCC_APB1ENR_TIM7EN_Pos);}else{RCC->APB1ENR &= ~(1 << RCC_APB1ENR_TIM7EN_Pos);}
}
void TIM7_Nvic(uint8_t state)
{ // 55
	if(state){set_bit_block(NVIC->ISER, 1, TIM7_IRQn, 1);}else{set_bit_block(NVIC->ICER, 1, TIM7_IRQn, 1);}
}
void TIM7_start(void){ set_reg_Msk_Pos(&TIM7->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, 1); }
void TIM7_stop(void){ set_reg_Msk_Pos(&TIM7->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, 0); }

/*** TIM7 INIC Procedure & Function Definition ***/
static tim6and7_callback tim7_callback_setup = {0};

static STM32FXXX_TIM7_Handler stm32fxxx_tim7_setup = {
	.clock = TIM7_Clock,
	.nvic = TIM7_Nvic,
	.start = TIM7_start,
	.stop = TIM7_stop,
	.callback = &tim7_callback_setup,
	.dev = dev
};

STM32FXXX_TIM7_Handler* tim7(void){ return (STM32FXXX_TIM7_Handler*) &stm32fxxx_tim7_setup;}

#endif
/*** EOF ***/

