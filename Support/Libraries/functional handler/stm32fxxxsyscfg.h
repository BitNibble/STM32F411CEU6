/******************************************************************************
	STM32 XXX SYSCFG
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 23062023
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXSYSCFG_H_
	#define _STM32FXXXSYSCFG_H_
/*** File Library ***/
#include "stm32fxxxinstance.h"
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
	SYSCFG_TypeDef* instance;
	/*** Bit Mapping ***/
	SYSCFG_memrmp* memrmp;
	SYSCFG_pmc* pmc;
	SYSCFG_exticr1* exticr1;
	SYSCFG_exticr2* exticr2;
	SYSCFG_exticr3* exticr3;
	SYSCFG_exticr4* exticr4;
	SYSCFG_cmpcr* cmpcr;
	SYSCFG_cfgr* cfgr;
	/*** Other ***/
	void (*clock)(uint8_t state);
}STM32FXXX_SYSCFG;
/*************************************/
/************ INIC SYSCFG ************/
/*************************************/
void syscfg_enable(void);
STM32FXXX_SYSCFG* syscfg(void);
/***********************************************/
/********* Procedure & Function Header *********/
/***********************************************/
void SYSCFG_Clock(uint8_t state);
// memrmp
void SYSCFG_memrmp_swp_fmc(uint8_t value);
void SYSCFG_memrmp_mem_mode(uint8_t value);
// pmc
void SYSCFG_pmc_adcxdc2(uint8_t value);
void SYSCFG_pmc_adc1dc2(uint8_t state);
void SYSCFG_pmc_adc2dc2(uint8_t state);
void SYSCFG_pmc_adc3dc2(uint8_t state);
// exticr1
void SYSCFG_exticr1_exti3(uint8_t value);
void SYSCFG_exticr1_exti2(uint8_t value);
void SYSCFG_exticr1_exti1(uint8_t value);
void SYSCFG_exticr1_exti0(uint8_t value);
// exticr2
void SYSCFG_exticr2_exti7(uint8_t value);
void SYSCFG_exticr2_exti6(uint8_t value);
void SYSCFG_exticr2_exti5(uint8_t value);
void SYSCFG_exticr2_exti4(uint8_t value);
// exticr3
void SYSCFG_exticr3_exti11(uint8_t value);
void SYSCFG_exticr3_exti10(uint8_t value);
void SYSCFG_exticr3_exti9(uint8_t value);
void SYSCFG_exticr3_exti8(uint8_t value);
// exticr4
void SYSCFG_exticr4_exti15(uint8_t value);
void SYSCFG_exticr4_exti14(uint8_t value);
void SYSCFG_exticr4_exti13(uint8_t value);
void SYSCFG_exticr4_exti12(uint8_t value);
// cmpcr
uint8_t SYSCFG_cmpcr_ready(void);
void SYSCFG_cmpcr_cmp_pd(uint8_t state);
// cfgr
void SYSCFG_cfgr_fmpi2c1_sda(uint8_t state);
void SYSCFG_cfgr_fmpi2c1_scl(uint8_t state);
/***********************************************/
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

