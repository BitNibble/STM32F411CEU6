/******************************************************************************
	STM32 FXXX RCC
Author: <sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-FXXX
Date: 21102025
*******************************************************************************/
#ifndef STM32FXXXRCC_H
	#define STM32FXXXRCC_H
/*** Library ***/
#if defined (STM32F411xE)
	#include "stm32f411ceu6.h"
#elif defined(STM32F446xx)
	#include "stm32f446re.h"
#else
	void* dev(void){ return NULL; }
#endif
/*** RCC_Common TypeDef ***/
// RCC -> PLL
typedef struct
{
	void (*division)(uint8_t pllm, uint16_t plln, uint8_t pllp, uint8_t pllq);
	void (*enable)(void);
}STM32FXXX_RCC_PLL;
// RCC -> PLLI2S
typedef struct
{
	void (*enable)(void);
}STM32FXXX_RCC_PLL_I2S;
// RCC -> PLLSAI
typedef struct
{
	void (*enable)(void);
}STM32FXXX_RCC_PLL_SAI;
/*** RCC TypeDef ***/
typedef const struct
{
	/*** Bit Mapping ***/
	void (*prescaler)(uint16_t ahbpre, uint8_t ppre1, uint8_t ppre2, uint8_t rtcpre);
	/*** Extended ***/
	STM32FXXX_RCC_PLL* pll;
	STM32FXXX_RCC_PLL_I2S* pll_i2s;
	STM32FXXX_RCC_PLL_SAI* pll_sai;
	/*** Other ***/
	void (*inic)(void);
	void (*henable)(uint8_t hclock);
	void (*hselect)(uint8_t sysclk);
	void (*lenable)(uint8_t lclock);
	void (*lselect)(uint8_t lclock);
	/*** NVIC ***/
	void (*nvic)(uint8_t state);
	/*** Device ***/
	#if defined(STM32F411CEU6_H)
		STM32F411CEU6_Instance* (*dev)(void);
	#elif defined(STM32F446RE_H)
		STM32F446RE_Instance* (*dev)(void);
	#else
		void* (*dev)(void);
	#endif
}STM32FXXX_RCC_HANDLER;

STM32FXXX_RCC_HANDLER* rcc(void);

/*** Procedure & Function Header ***/
void STM32FXXX_RCC_nvic(uint8_t state);
/*** RCC Procedure & Function Header ***/
// PLL
void STM32FXXX_PLL_Division(uint8_t pllm, uint16_t plln, uint8_t pllp, uint8_t pllq);
void STM32FXXX_Rcc_PLL_CLK_Enable(void);
void STM32FXXX_Rcc_PLL_I2S_Enable(void);
void STM32FXXX_Rcc_PLL_SAI_Enable(void);
// RCC
void rcc_start(void);
void STM32FXXX_Rcc_HEnable(uint8_t hclock);
void STM32FXXX_Rcc_HSelect(uint8_t hclock);
void STM32FXXX_Rcc_LEnable(uint8_t lclock);
void STM32FXXX_Rcc_LSelect(uint8_t lclock);
void STM32FXXX_Prescaler(uint16_t ahbpre, uint8_t ppre1, uint8_t ppre2, uint8_t rtcpre);

/*** INTERRUPT HEADER ***/
void RCC_IRQHandler(void);

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
******/

