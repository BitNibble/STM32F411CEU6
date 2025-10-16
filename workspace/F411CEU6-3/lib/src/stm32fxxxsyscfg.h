/******************************************************************************
	STM32 XXX SYSCFG
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     23062023
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXSYSCFG_H_
	#define _STM32FXXXSYSCFG_H_

/*** File Library ***/
#include "stm32f411ceu6.h"
/***************************************/
/***** SYSCFG Bit Mapping TypeDef ****/
/***************************************/
typedef struct
{
	void (*swp_fmc)(uint8_t value);
	void (*mem_mode)(uint8_t value);
}SYSCFG_memrmp;
typedef struct
{
	void (*adcxdc2)(uint8_t value);
	void (*adc1dc2)(uint8_t state);
	void (*adc2dc2)(uint8_t state);
	void (*adc3dc2)(uint8_t state);
}SYSCFG_pmc;
typedef struct
{
	void (*exti3)(uint8_t value);
	void (*exti2)(uint8_t value);
	void (*exti1)(uint8_t value);
	void (*exti0)(uint8_t value);
}SYSCFG_exticr1;
typedef struct
{
	void (*exti7)(uint8_t value);
	void (*exti6)(uint8_t value);
	void (*exti5)(uint8_t value);
	void (*exti4)(uint8_t value);
}SYSCFG_exticr2;
typedef struct
{
	void (*exti11)(uint8_t value);
	void (*exti10)(uint8_t value);
	void (*exti9)(uint8_t value);
	void (*exti8)(uint8_t value);
}SYSCFG_exticr3;
typedef struct
{
	void (*exti15)(uint8_t value);
	void (*exti14)(uint8_t value);
	void (*exti13)(uint8_t value);
	void (*exti12)(uint8_t value);
}SYSCFG_exticr4;
typedef struct
{
	uint8_t (*ready)(void);
	void (*cmp_pd)(uint8_t state);
}SYSCFG_cmpcr;
typedef struct
{
	void (*fmpi2c1_sda)(uint8_t value);
	void (*fmpi2c1_scl)(uint8_t value);
}SYSCFG_cfgr;
/***************************************/
/********** SYSCFG TypeDef **********/
/***************************************/
typedef struct
{
	/*** Bit Mapping ***/
	SYSCFG_memrmp* memrmp;
	SYSCFG_pmc* pmc;
	SYSCFG_exticr1* exticr1;
	SYSCFG_exticr2* exticr2;
	SYSCFG_exticr3* exticr3;
	SYSCFG_exticr4* exticr4;
	SYSCFG_cmpcr* cmpcr;
	SYSCFG_cfgr* cfgr;
	/*** Clock and Nvic ***/
	void (*clock)(uint8_t state);

#if defined(STM32F411CEU6_H)
	STM32F411CEU6_Handler* (*dev)(void);
#endif
}STM32FXXX_SYSCFG_Handler;

STM32FXXX_SYSCFG_Handler* syscfg(void);

/*** INTERRUPT HEADER ***/
void PVD_IRQHandler(void);
void TAMP_STAMP_IRQHandler(void);
void RTC_WKUP_IRQHandler(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

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

