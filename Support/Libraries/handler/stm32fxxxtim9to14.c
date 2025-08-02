/******************************************************************************
	STM32 XXX TIM 9 to 14
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 22062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxtim9to14.h"

#define ON 1
#define OFF 0
/*** File Variable ***/
static STM32FXXX_TIM9 stm32fxxx_tim9 = {0};
static STM32FXXX_TIM10 stm32fxxx_tim10 = {0};
static STM32FXXX_TIM11 stm32fxxx_tim11 = {0};
static STM32FXXX_TIM12 stm32fxxx_tim12 = {0};
static STM32FXXX_TIM13 stm32fxxx_tim13 = {0};
static STM32FXXX_TIM14 stm32fxxx_tim14 = {0};
/*** TIMER 9 to 14 Procedure & Function Definition ***/
/************/
/*** TIM9 ***/
/************/
void STM32FXXXTim9Clock(uint8_t state)
{
	if(state){RCC->APB2ENR |= (1 << 16);}else{RCC->APB2ENR &= ~(1 << 16);}
}
void STM32FXXXTim9Nvic(uint8_t state)
{ // 24
	if(state){set_bit_block(NVIC->ISER, 1, TIM1_BRK_TIM9_IRQn, 1);}else{set_bit_block(NVIC->ICER, 1, TIM1_BRK_TIM9_IRQn, 1);}
}
/*************/
/*** TIM10 ***/
/*************/
void STM32FXXXTim10Clock(uint8_t state)
{
	if(state){RCC->APB2ENR |= (1 << 17);}else{RCC->APB2ENR &= ~(1 << 17);}
}
void STM32FXXXTim10Nvic(uint8_t state)
{ // 25
	if(state){set_bit_block(NVIC->ISER, 1, TIM1_UP_TIM10_IRQn, 1);} else{set_bit_block(NVIC->ICER, 1, TIM1_UP_TIM10_IRQn, 1);}
}
/*************/
/*** TIM11 ***/
/*************/
void STM32FXXXTim11Clock(uint8_t state)
{
	if(state){RCC->APB2ENR |= (1 << 18);}else{RCC->APB2ENR &= ~(1 << 18);}
}
void STM32FXXXTim11Nvic(uint8_t state)
{ // 26
	if(state){set_bit_block(NVIC->ISER, 1, TIM1_TRG_COM_TIM11_IRQn, 1);} else{set_bit_block(NVIC->ICER, 1, TIM1_TRG_COM_TIM11_IRQn, 1);}
}
#ifdef STM32F446xx
/*************/
/*** TIM12 ***/
/*************/
void STM32FXXXTim12Clock(uint8_t state)
{
	if(state){RCC->APB1ENR |= (1 << 6);}else{RCC->APB1ENR &= ~(1 << 6);}
}
void STM32FXXXTim12Nvic(uint8_t state)
{ // 43
	if(state){set_bit_block(NVIC->ISER, 1, TIM8_BRK_TIM12_IRQn, 1);}else{set_bit_block(NVIC->ICER, 1, TIM8_BRK_TIM12_IRQn, 1);}
}
/*************/
/*** TIM13 ***/
/*************/
void STM32FXXXTim13Clock(uint8_t state)
{
	if(state){
		RCC->APB1ENR |= (1 << 7); // timer 13 clock enabled
	}else{
		RCC->APB1ENR &= ~(1 << 7); //timer 13 clock disabled
	}
}
void STM32FXXXTim13Nvic(uint8_t state)
{ // 44
	if(state){set_bit_block(NVIC->ISER, 1, TIM8_UP_TIM13_IRQn, 1);}else{set_bit_block(NVIC->ICER, 1, TIM8_UP_TIM13_IRQn, 1);}
}
/*************/
/*** TIM14 ***/
/*************/
void STM32FXXXTim14Clock(uint8_t state)
{
	if(state){RCC->APB1ENR |= (1 << 8);}else{RCC->APB1ENR &= ~(1 << 8);}
}
void STM32FXXXTim14Nvic(uint8_t state)
{ // 45
	if(state){set_bit_block(NVIC->ISER, 1, TIM8_TRG_COM_TIM14_IRQn, 1);}else{set_bit_block(NVIC->ICER, 1, TIM8_TRG_COM_TIM14_IRQn, 1);}
}
#endif
/*** TIM9 Procedure & Function Definition ***/
void tim9_enable(void)
{
	STM32FXXXTim9Clock(ON);
	/*** TIM9 Bit Mapping Link ***/
	stm32fxxx_tim9.instance = TIM9;
	// CLOCK
	stm32fxxx_tim9.clock = STM32FXXXTim9Clock;
	// NVIC
	stm32fxxx_tim9.nvic = STM32FXXXTim9Nvic;

	//return &stm32fxxx_tim9;
}

STM32FXXX_TIM9* tim9(void){ return (STM32FXXX_TIM9*) &stm32fxxx_tim9; }

/*** TIM10 Procedure & Function Definition***/
void tim10_enable(void)
{
	STM32FXXXTim10Clock(ON);
	/*** TIM10 Bit Mapping Link ***/
	stm32fxxx_tim10.instance = TIM10;
	// CLOCK
	stm32fxxx_tim10.clock = STM32FXXXTim10Clock;
	// NVIC
	stm32fxxx_tim10.nvic = STM32FXXXTim10Nvic;

	//return &stm32fxxx_tim10;
}

STM32FXXX_TIM10* tim10(void){ return (STM32FXXX_TIM10*) &stm32fxxx_tim10; }

/*** TIM11 Procedure & Function Definition***/
void tim11_enable(void)
{
	STM32FXXXTim11Clock(ON);
	/*** TIM11 Bit Mapping Link ***/
	stm32fxxx_tim11.instance = TIM11;
	// CLOCK
	stm32fxxx_tim11.clock = STM32FXXXTim11Clock;
	// NVIC
	stm32fxxx_tim11.nvic = STM32FXXXTim11Nvic;

	//return &stm32fxxx_tim11;
}

STM32FXXX_TIM11* tim11(void){ return (STM32FXXX_TIM11*) &stm32fxxx_tim11; }

/*** TIM12 Procedure & Function Definition***/
void tim12_enable(void)
{
	#ifdef STM32F446xx
		STM32FXXXTim12Clock(ON);
		stm32fxxx_tim12.instance = TIM12;
	#endif
	// CLOCK
	stm32fxxx_tim12.clock = STM32FXXXTim12Clock;
	// NVIC
	stm32fxxx_tim12.nvic = STM32FXXXTim12Nvic;

	//return &stm32fxxx_tim12;
}

STM32FXXX_TIM12* tim12(void){ return (STM32FXXX_TIM12*) &stm32fxxx_tim12; }

/*** TIM13 Procedure & Function Definition***/
void tim13_enable(void)
{
	#ifdef STM32F446xx
		STM32FXXXTim13Clock(ON);
		stm32fxxx_tim13.instance = TIM13;
	#endif
	// CLOCK
	stm32fxxx_tim13.clock = STM32FXXXTim13Clock;
	// NVIC
	stm32fxxx_tim13.nvic = STM32FXXXTim13Nvic;

	//return &stm32fxxx_tim13;
}

STM32FXXX_TIM13* tim13(void){ return (STM32FXXX_TIM13*) &stm32fxxx_tim13; }

/*** TIM14 Procedure & Function Definition ***/
void tim14_enable(void)
{
	#ifdef STM32F446xx
		STM32FXXXTim14Clock(ON);
		stm32fxxx_tim14.instance = TIM14;
	#endif
	// CLOCK
	stm32fxxx_tim14.clock = STM32FXXXTim14Clock;
	// NVIC
	stm32fxxx_tim14.nvic = STM32FXXXTim14Nvic;

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

