/******************************************************************************
	STM32 XXX TIM 1 and 8
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 2262023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxtim1and8.h"
#include "stm32fxxxnvic.h"
#include "stm32fxxxrcc.h"

#define ON 1
#define OFF 0
/*** File Variables ***/
static STM32FXXX_TIM1 stm32fxxx_tim1 = {0};
static STM32FXXX_TIM8 stm32fxxx_tim8 = {0};

/************/
/*** TIM1 ***/
/************/
void STM32FXXXTim1Clock(uint8_t state)
{
	//if(state){RCC->APB2ENR |= (1 << 0);}else{RCC->APB2ENR &= ~(1 << 0);}
	if(state){
		set_reg_Msk(&RCC->APB2ENR , RCC_APB2ENR_TIM1EN_Msk, RCC_APB2ENR_TIM1EN_Pos, 1);
	}else{
		set_reg_Msk(&RCC->APB2ENR , RCC_APB2ENR_TIM1EN_Msk, RCC_APB2ENR_TIM1EN_Pos, 0);
	}
}
void STM32FXXXTim1Nvic(uint8_t value)
{ // 24, 25, 26, 27
	nvic_enable();
	switch(value){
		case 0b1000:
			//set_bit_block(NVIC->ISER, 1, TIM1_BRK_TIM9_IRQn, 1);
			nvic()->set_enable(TIM1_BRK_TIM9_IRQn);
		break;
		case 0b0100:
			//set_bit_block(NVIC->ISER, 1, TIM1_UP_TIM10_IRQn, 1);
			nvic()->set_enable(TIM1_UP_TIM10_IRQn);
		break;
		case 0b0010:
			//set_bit_block(NVIC->ISER, 1, TIM1_TRG_COM_TIM11_IRQn, 1);
			nvic()->set_enable(TIM1_TRG_COM_TIM11_IRQn);
		break;
		case 0b0001:
			//set_bit_block(NVIC->ISER, 1, TIM1_CC_IRQn, 1);
			nvic()->set_enable(TIM1_CC_IRQn);
		break;
		case 0b11000:
			//set_bit_block(NVIC->ICER, 1, TIM1_BRK_TIM9_IRQn, 1);
			nvic()->clear_enable(TIM1_BRK_TIM9_IRQn);
		break;
		case 0b10100:
			//set_bit_block(NVIC->ICER, 1, TIM1_UP_TIM10_IRQn, 1);
			nvic()->clear_enable(TIM1_UP_TIM10_IRQn);
		break;
		case 0b10010:
			//set_bit_block(NVIC->ICER, 1, TIM1_TRG_COM_TIM11_IRQn, 1);
			nvic()->clear_enable(TIM1_TRG_COM_TIM11_IRQn);
		break;
		case 0b10001:
			//set_bit_block(NVIC->ICER, 1, TIM1_CC_IRQn, 1);
			nvic()->clear_enable(TIM1_CC_IRQn);
		break;
	default:
	break;
	}
}
#ifdef STM32F446xx
/************/
/*** TIM8 ***/
/************/
void STM32FXXXTim8Clock(uint8_t state)
{
	if(state){RCC->APB2ENR |= (1 << 1);}else{RCC->APB2ENR &= ~(1 << 1);}
}
void STM32FXXXTim8Nvic(uint8_t value)
{ // 43, 44, 45, 46
	switch(value){
		case 0b1000:
			set_bit_block(NVIC->ISER, 1, TIM8_BRK_TIM12_IRQn, 1);
		break;
		case 0b0100:
			set_bit_block(NVIC->ISER, 1, TIM8_UP_TIM13_IRQn, 1);
		break;
		case 0b0010:
			set_bit_block(NVIC->ISER, 1, TIM8_TRG_COM_TIM14_IRQn, 1);
		break;
		case 0b0001:
			set_bit_block(NVIC->ISER, 1, TIM8_CC_IRQn, 1);
		break;
		case 0b11000:
			set_bit_block(NVIC->ICER, 1, TIM8_BRK_TIM12_IRQn, 1);
		break;
		case 0b10100:
			set_bit_block(NVIC->ICER, 1, TIM8_UP_TIM13_IRQn, 1);
		break;
		case 0b10010:
			set_bit_block(NVIC->ICER, 1, TIM8_TRG_COM_TIM14_IRQn, 1);
		break;
		case 0b10001:
			set_bit_block(NVIC->ICER, 1, TIM8_CC_IRQn, 1);
		break;
	default:
	break;
	}
}

#endif

/*** TIM1 INIC Procedure & Function Definition ***/
void tim1_enable(void)
{
	STM32FXXXTim1Clock(ON);
	/*** TIM1 Bit Field ***/
	stm32fxxx_tim1.instance = TIM1;
	// CLOCK
	stm32fxxx_tim1.clock = STM32FXXXTim1Clock;
	// NVIC
	stm32fxxx_tim1.nvic = STM32FXXXTim1Nvic;

	//return &stm32fxxx_tim1;
}

STM32FXXX_TIM1* tim1(void){ return (STM32FXXX_TIM1*) &stm32fxxx_tim1;}

/*** TIM8 INIC Procedure & Function Definition ***/
void tim8_enable(void)
{
	#ifdef STM32F446xx
		STM32FXXXTim8Clock(ON);
		stm32fxxx_tim8.instance = TIM8;
	#endif
	// CLOCK
	stm32fxxx_tim8.clock = STM32FXXXTim8Clock;
	// NVIC
	stm32fxxx_tim8.nvic = STM32FXXXTim8Nvic;

	//return &stm32fxxx_tim8;
}

STM32FXXX_TIM8* tim8(void){ return (STM32FXXX_TIM8*) &stm32fxxx_tim8; }

/*** TIM1 CC IRQ Request ***/
void TIM1_CC_IRQHandler(void){

	if(get_reg_Msk(TIM1->SR , TIM_SR_UIF_Msk, TIM_SR_UIF_Pos)){
		tim1_u_callback();
		set_reg_Msk(&TIM1->SR , TIM_SR_UIF_Msk, TIM_SR_UIF_Pos, 0);
	}
	if(get_reg_Msk(TIM1->SR , TIM_SR_CC1IF_Msk, TIM_SR_CC1IF_Pos)){
		tim1_cc1_callback();
		set_reg_Msk(&TIM1->SR , TIM_SR_CC1IF_Msk, TIM_SR_CC1IF_Pos, 0);
	}
	if(get_reg_Msk(TIM1->SR , TIM_SR_CC2IF_Msk, TIM_SR_CC2IF_Pos)){
		tim1_cc2_callback();
		set_reg_Msk(&TIM1->SR , TIM_SR_CC2IF_Msk, TIM_SR_CC2IF_Pos, 0);
	}
	if(get_reg_Msk(TIM1->SR , TIM_SR_TIF_Msk, TIM_SR_TIF_Pos)){
		tim1_t_callback();
		set_reg_Msk(&TIM1->SR , TIM_SR_TIF_Msk, TIM_SR_TIF_Pos, 0);
	}
	if(get_reg_Msk(TIM1->SR , TIM_SR_COMIF_Msk, TIM_SR_COMIF_Pos)){
		tim1_com_callback();
		set_reg_Msk(&TIM1->SR , TIM_SR_COMIF_Msk, TIM_SR_COMIF_Pos, 0);
	}
	if(get_reg_Msk(TIM1->SR , TIM_SR_BIF_Msk, TIM_SR_BIF_Pos)){
		tim1_b_callback();
		set_reg_Msk(&TIM1->SR , TIM_SR_BIF_Msk, TIM_SR_BIF_Pos, 0);
	}
}
/***/

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

