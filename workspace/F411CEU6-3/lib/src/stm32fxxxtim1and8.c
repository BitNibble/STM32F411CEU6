/******************************************************************************
	STM32 XXX TIM 1 and 8
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     2262023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxtim1and8.h"
#include "stm32fxxxnvic.h"

/************/
/*** TIM1 ***/
/************/
void TIM1_Clock(uint8_t state)
{
	//if(state){RCC->APB2ENR |= (1 << 0);}else{RCC->APB2ENR &= ~(1 << 0);}
	if(state){
		set_reg_Msk(&RCC->APB2ENR , RCC_APB2ENR_TIM1EN_Msk, 1);
	}else{
		set_reg_Msk(&RCC->APB2ENR , RCC_APB2ENR_TIM1EN_Msk, 0);
	}
}
void TIM1_Nvic(uint8_t value)
{ // 24, 25, 26, 27
	switch(value){
		case 0b1000:
			//set_bit_block(NVIC->ISER, 1, TIM1_BRK_TIM9_IRQn, 1);
			set_reg_Msk(&TIM1->DIER, TIM_DIER_BIE_Msk, 1);
			nvic()->set_enable(TIM1_BRK_TIM9_IRQn);
		break;
		case 0b0100:
			//set_bit_block(NVIC->ISER, 1, TIM1_UP_TIM10_IRQn, 1);
			set_reg_Msk(&TIM1->DIER, TIM_DIER_UIE_Msk, 1);
			nvic()->set_enable(TIM1_UP_TIM10_IRQn);
		break;
		case 0b0010:
			//set_bit_block(NVIC->ISER, 1, TIM1_TRG_COM_TIM11_IRQn, 1);
			set_reg_Msk(&TIM1->DIER, TIM_DIER_TIE_Msk, 1);
			nvic()->set_enable(TIM1_TRG_COM_TIM11_IRQn);
		break;
		case 0b0001:
			//set_bit_block(NVIC->ISER, 1, TIM1_CC_IRQn, 1);
			set_reg_Msk(&TIM1->DIER, TIM_DIER_CC1IE_Msk, 1);
			set_reg_Msk(&TIM1->DIER, TIM_DIER_CC2IE_Msk, 1);
			nvic()->set_enable(TIM1_CC_IRQn);
		break;
		case 0b11000:
			//set_bit_block(NVIC->ICER, 1, TIM1_BRK_TIM9_IRQn, 1);
			set_reg_Msk(&TIM1->DIER, TIM_DIER_BIE_Msk, 0);
			nvic()->clear_enable(TIM1_BRK_TIM9_IRQn);
		break;
		case 0b10100:
			//set_bit_block(NVIC->ICER, 1, TIM1_UP_TIM10_IRQn, 1);
			set_reg_Msk(&TIM1->DIER, TIM_DIER_UIE_Msk, 0);
			nvic()->clear_enable(TIM1_UP_TIM10_IRQn);
		break;
		case 0b10010:
			//set_bit_block(NVIC->ICER, 1, TIM1_TRG_COM_TIM11_IRQn, 1);
			set_reg_Msk(&TIM1->DIER, TIM_DIER_TIE_Msk, 0);
			nvic()->clear_enable(TIM1_TRG_COM_TIM11_IRQn);
		break;
		case 0b10001:
			//set_bit_block(NVIC->ICER, 1, TIM1_CC_IRQn, 1);
			set_reg_Msk(&TIM1->DIER, TIM_DIER_CC1IE_Msk, 0);
			set_reg_Msk(&TIM1->DIER, TIM_DIER_CC2IE_Msk, 0);
			nvic()->clear_enable(TIM1_CC_IRQn);
		break;
	default:
	break;
	}
}
void TIM1_start(void) {
	set_reg_Msk(&TIM1->CR1, TIM_CR1_CEN_Msk, 1);
}
void TIM1_stop(void) {
	set_reg_Msk(&TIM1->CR1, TIM_CR1_CEN_Msk, 0);
}

/*** TIM1 INIC Procedure & Function Definition ***/
static STM32FXXX_TIM1 stm32fxxx_tim1_setup = {
	.clock = TIM1_Clock,
	.nvic = TIM1_Nvic,
	.start = TIM1_start,
	.stop = TIM1_stop,
	.callback = {0}
};

STM32FXXX_TIM1* tim1(void){ return (STM32FXXX_TIM1*) &stm32fxxx_tim1_setup;}

#ifdef STM32F446xx
/************/
/*** TIM8 ***/
/************/
void TIM8_Clock(uint8_t state)
{
	if(state){RCC->APB2ENR |= (1 << RCC_APB2ENR_TIM8EN_Pos);}else{RCC->APB2ENR &= ~(1 << RCC_APB2ENR_TIM8EN_Pos);}
}
void TIM8_Nvic(uint8_t value)
{ // 43, 44, 45, 46
	switch(value){
		case 0b1000:
			set_reg_Msk(&TIM8->DIER, TIM_DIER_BIE_Msk, TIM_DIER_BIE_Pos, ON);
			set_bit_block(NVIC->ISER, 1, TIM8_BRK_TIM12_IRQn, 1);
		break;
		case 0b0100:
			set_reg_Msk(&TIM8->DIER, TIM_DIER_UIE_Msk, TIM_DIER_UIE_Pos, ON);
			set_bit_block(NVIC->ISER, 1, TIM8_UP_TIM13_IRQn, 1);
		break;
		case 0b0010:
			set_reg_Msk(&TIM8->DIER, TIM_DIER_TIE_Msk, TIM_DIER_TIE_Pos, ON);
			set_bit_block(NVIC->ISER, 1, TIM8_TRG_COM_TIM14_IRQn, 1);
		break;
		case 0b0001:
			set_reg_Msk(&TIM8->DIER, TIM_DIER_CC1IE_Msk, TIM_DIER_CC1IE_Pos, ON);
			set_reg_Msk(&TIM8->DIER, TIM_DIER_CC2IE_Msk, TIM_DIER_CC2IE_Pos, ON);
			set_bit_block(NVIC->ISER, 1, TIM8_CC_IRQn, 1);
		break;
		case 0b11000:
			set_reg_Msk(&TIM8->DIER, TIM_DIER_BIE_Msk, TIM_DIER_BIE_Pos, OFF);
			set_bit_block(NVIC->ICER, 1, TIM8_BRK_TIM12_IRQn, 1);
		break;
		case 0b10100:
			set_reg_Msk(&TIM8->DIER, TIM_DIER_UIE_Msk, TIM_DIER_UIE_Pos, OFF);
			set_bit_block(NVIC->ICER, 1, TIM8_UP_TIM13_IRQn, 1);
		break;
		case 0b10010:
			set_reg_Msk(&TIM8->DIER, TIM_DIER_TIE_Msk, TIM_DIER_TIE_Pos, OFF);
			set_bit_block(NVIC->ICER, 1, TIM8_TRG_COM_TIM14_IRQn, 1);
		break;
		case 0b10001:
			set_reg_Msk(&TIM8->DIER, TIM_DIER_CC1IE_Msk, TIM_DIER_CC1IE_Pos, OFF);
			set_reg_Msk(&TIM8->DIER, TIM_DIER_CC2IE_Msk, TIM_DIER_CC2IE_Pos, OFF);
			set_bit_block(NVIC->ICER, 1, TIM8_CC_IRQn, 1);
		break;
	default:
	break;
	}
}
void TIM8_start(void) {
	set_reg_Msk(&TIM8->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, ON);
}
void TIM8_stop(void) {
	set_reg_Msk(&TIM8->CR1, TIM_CR1_CEN_Msk, TIM_CR1_CEN_Pos, OFF);
}

/*** TIM1 INIC Procedure & Function Definition ***/
static STM32FXXX_TIM8 stm32fxxx_tim8_setup = {
	.clock = TIM8_Clock,
	.nvic = TIM8_Nvic,
	.start = TIM8_start,
	.stop = TIM8_stop,
	.callback = {0}
};

STM32FXXX_TIM8* tim8(void){ return (STM32FXXX_TIM8*) &stm32fxxx_tim8_setup;}

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
Instance->Reg->Par
******/

