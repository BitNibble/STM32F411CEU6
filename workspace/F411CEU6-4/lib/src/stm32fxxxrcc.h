/******************************************************************************
	STM32 FXXX RCC
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-FXXX
Date:     07032024
*******************************************************************************/
#ifndef _STM32FXXXRCC_H_
	#define _STM32FXXXRCC_H_

/*** Library ***/
#include "stm32f411ceu6.h"

typedef struct {
    void (*lsi_ready)(void);
    void (*lse_ready)(void);
    void (*hsi_ready)(void);
    void (*hse_ready)(void);
    void (*pll_ready)(void);
    void (*plli2s_ready)(void);
    void (*css_fault)(void);
} RCC_Callback;
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
}STM32FXXX_RCC_PLLI2S;
// RCC -> PLLSAI
typedef struct
{
	void (*enable)(void);
}STM32FXXX_RCC_PLLSAI;
/*** RCC TypeDef ***/
typedef struct
{
	/*** Bit Mapping ***/
	void (*inic)(void);
	void (*prescaler)(uint16_t ahbpre, uint8_t ppre1, uint8_t ppre2, uint8_t rtcpre);
	/*** Extended ***/
	STM32FXXX_RCC_PLL* pll;
	STM32FXXX_RCC_PLLI2S* plli2s;
	STM32FXXX_RCC_PLLSAI* pllsai;
	/*** Other ***/
	void (*h_enable)(uint8_t hclock);
	void (*h_select)(uint8_t sysclk);
	void (*l_enable)(uint8_t lclock);
	void (*l_select)(uint8_t lclock);
	void (*nvic)(uint8_t state);
	RCC_Callback* callback;

#if defined(STM32F411CEU6_H)
	STM32F411CEU6_Handler* (*dev)(void);
#endif
}STM32FXXX_RCC_Handler;

STM32FXXX_RCC_Handler* rcc(void);

/*** INTERRUPT ***/
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

