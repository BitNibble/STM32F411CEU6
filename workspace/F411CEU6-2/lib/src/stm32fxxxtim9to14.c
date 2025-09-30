/******************************************************************************
	STM32 XXX TIM 9 to 14
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     22062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxtim9to14.h"

/*** File Variable ***/
static STM32FXXX_TIM9 stm32fxxx_tim9 = {0};
static STM32FXXX_TIM10 stm32fxxx_tim10 = {0};
static STM32FXXX_TIM11 stm32fxxx_tim11 = {0};
static STM32FXXX_TIM12 stm32fxxx_tim12 = {0};
static STM32FXXX_TIM13 stm32fxxx_tim13 = {0};
static STM32FXXX_TIM14 stm32fxxx_tim14 = {0};
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
#endif
/*** TIM9 Procedure & Function Definition ***/
void tim9_enable(void)
{
	TIM9_Clock(1);
	/*** TIM9 Bit Mapping Link ***/
	stm32fxxx_tim9.instance = TIM9;
	// CLOCK
	stm32fxxx_tim9.clock = TIM9_Clock;
	// NVIC
	stm32fxxx_tim9.nvic = TIM9_Nvic;
	/*** Procedures ***/
	/*** Other ***/
	stm32fxxx_tim9.start = TIM9_start;
	stm32fxxx_tim9.stop = TIM9_stop;
	//return &stm32fxxx_tim9;
}

STM32FXXX_TIM9* tim9(void){ return (STM32FXXX_TIM9*) &stm32fxxx_tim9; }

/*** TIM10 Procedure & Function Definition***/
void tim10_enable(void)
{
	TIM10_Clock(1);
	/*** TIM10 Bit Mapping Link ***/
	stm32fxxx_tim10.instance = TIM10;
	// CLOCK
	stm32fxxx_tim10.clock = TIM10_Clock;
	// NVIC
	stm32fxxx_tim10.nvic = TIM10_Nvic;
	/*** Procedures ***/
	/*** Other ***/
	stm32fxxx_tim10.start = TIM10_start;
	stm32fxxx_tim10.stop = TIM10_stop;
	//return &stm32fxxx_tim10;
}

STM32FXXX_TIM10* tim10(void){ return (STM32FXXX_TIM10*) &stm32fxxx_tim10; }

/*** TIM11 Procedure & Function Definition***/
void tim11_enable(void)
{
	TIM11_Clock(1);
	/*** TIM11 Bit Mapping Link ***/
	stm32fxxx_tim11.instance = TIM11;
	// CLOCK
	stm32fxxx_tim11.clock = TIM11_Clock;
	// NVIC
	stm32fxxx_tim11.nvic = TIM11_Nvic;
	/*** Procedures ***/
	/*** Other ***/
	stm32fxxx_tim11.start = TIM11_start;
	stm32fxxx_tim11.stop = TIM11_stop;
	//return &stm32fxxx_tim11;
}

STM32FXXX_TIM11* tim11(void){ return (STM32FXXX_TIM11*) &stm32fxxx_tim11; }

/*** TIM12 Procedure & Function Definition***/
void tim12_enable(void)
{
	#ifdef STM32F446xx
		TIM12_Clock(ON);
		stm32fxxx_tim12.instance = TIM12;
	// CLOCK
	stm32fxxx_tim12.clock = TIM12_Clock;
	// NVIC
	stm32fxxx_tim12.nvic = TIM12_Nvic;
	/*** Procedures ***/
	/*** Other ***/
	stm32fxxx_tim12.start = TIM12_start;
	stm32fxxx_tim12.stop = TIM12_stop;
	#endif
	//return &stm32fxxx_tim12;
}

STM32FXXX_TIM12* tim12(void){ return (STM32FXXX_TIM12*) &stm32fxxx_tim12; }

/*** TIM13 Procedure & Function Definition***/
void tim13_enable(void)
{
	#ifdef STM32F446xx
		TIM13_Clock(ON);
		stm32fxxx_tim13.instance = TIM13;
	// CLOCK
	stm32fxxx_tim13.clock = TIM13_Clock;
	// NVIC
	stm32fxxx_tim13.nvic = TIM13_Nvic;
	/*** Procedures ***/
	/*** Other ***/
	stm32fxxx_tim13.start = TIM13_start;
	stm32fxxx_tim13.stop = TIM13_stop;
	#endif
	//return &stm32fxxx_tim13;
}

STM32FXXX_TIM13* tim13(void){ return (STM32FXXX_TIM13*) &stm32fxxx_tim13; }

/*** TIM14 Procedure & Function Definition ***/
void tim14_enable(void)
{
	#ifdef STM32F446xx
		TIM14_Clock(ON);
		stm32fxxx_tim14.instance = TIM14;
	// CLOCK
	stm32fxxx_tim14.clock = TIM14_Clock;
	// NVIC
	stm32fxxx_tim14.nvic = TIM14_Nvic;
	/*** Procedures ***/
	/*** Other ***/
	stm32fxxx_tim14.start = TIM14_start;
	stm32fxxx_tim14.stop = TIM14_stop;
	#endif
	//return &stm32fxxx_tim14;
}

STM32FXXX_TIM14* tim14(void){ return (STM32FXXX_TIM14*) &stm32fxxx_tim14; }

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

