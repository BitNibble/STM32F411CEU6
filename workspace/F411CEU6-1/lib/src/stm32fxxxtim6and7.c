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

/*** File Variable ***/
static STM32FXXX_TIM6 stm32fxxx_tim6 = {0};
static STM32FXXX_TIM7 stm32fxxx_tim7 = {0};
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
void TIM6_start(void){ set_reg_Msk(&TIM6->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, ON); }
void TIM6_stop(void){ set_reg_Msk(&TIM6->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, OFF); }
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
void TIM7_start(void){ set_reg_Msk(&TIM7->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, ON); }
void TIM7_stop(void){ set_reg_Msk(&TIM7->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, OFF); }
#endif
/*** TIM6 INIC Procedure & Function Definition ***/
void tim6_enable(void)
{
	#ifdef STM32F446xx
			TIM6_Clock(ON);
			stm32fxxx_tim6.instance = TIM6;
	// CLOCK
	stm32fxxx_tim6.clock = TIM6_Clock;
	// NVIC
	stm32fxxx_tim6.nvic = TIM6_Nvic;
	/*** Procedures ***/
	/*** Other ***/
	stm32fxxx_tim6.start = TIM6_start;
	stm32fxxx_tim6.stop = TIM6_stop;
	#endif
	//return &stm32fxxx_tim6;
}
STM32FXXX_TIM6* tim6(void){ return (STM32FXXX_TIM6*) &stm32fxxx_tim6; }
/*** TIM7 INIC Procedure & Function Definition ***/
void tim7_enable(void)
{
	#ifdef STM32F446xx
		TIM7_Clock(ON);
		stm32fxxx_tim7.instance = TIM7;
	// CLOCK
	stm32fxxx_tim7.clock = TIM7_Clock;
	// NVIC
	stm32fxxx_tim7.nvic = TIM7_Nvic;
	/*** Procedures ***/
	/*** Other ***/
	stm32fxxx_tim7.start = TIM7_start;
	stm32fxxx_tim7.stop = TIM7_stop;
	#endif
	//return &stm32fxxx_tim7;
}
STM32FXXX_TIM7* tim7(void) { return (STM32FXXX_TIM7*) &stm32fxxx_tim7; }

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

