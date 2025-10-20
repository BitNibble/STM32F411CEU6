/******************************************************************************
	STM32 XXX SYSCFG
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     23062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxsyscfg.h"

/***********************************************/
/******* Procedure & Function Definition *******/
/***********************************************/
// memrmp
void SYSCFG_memrmp_swp_fmc(uint8_t value)
{
	set_reg_block(&SYSCFG->MEMRMP, 2, 10, value);
}
void SYSCFG_memrmp_mem_mode(uint8_t value)
{
	set_reg_block(&SYSCFG->MEMRMP, 3, 0, value);
}
// pmc
void SYSCFG_pmc_adcxdc2(uint8_t value)
{
	set_reg_block(&SYSCFG->PMC, 3, 16, value);
}
void SYSCFG_pmc_adc1dc2(uint8_t state)
{
	set_reg_block(&SYSCFG->PMC, 1, 16, state);
}
void SYSCFG_pmc_adc2dc2(uint8_t state)
{
	set_reg_block(&SYSCFG->PMC, 1, 17, state);
}
void SYSCFG_pmc_adc3dc2(uint8_t state)
{
	set_reg_block(&SYSCFG->PMC, 1, 18, state);
}
// exticr1
void SYSCFG_exticr1_exti3(uint8_t value)
{
	set_reg_block(&SYSCFG->EXTICR[0], 4, 12, value);
}
void SYSCFG_exticr1_exti2(uint8_t value)
{
	set_reg_block(&SYSCFG->EXTICR[0], 4, 8, value);
}
void SYSCFG_exticr1_exti1(uint8_t value)
{
	set_reg_block(&SYSCFG->EXTICR[0], 4, 4, value);
}
void SYSCFG_exticr1_exti0(uint8_t value)
{
	set_reg_block(&SYSCFG->EXTICR[0], 4, 0, value);
}
// exticr2
void SYSCFG_exticr2_exti7(uint8_t value)
{
	set_reg_block(&SYSCFG->EXTICR[1], 4, 12, value);
}
void SYSCFG_exticr2_exti6(uint8_t value)
{
	set_reg_block(&SYSCFG->EXTICR[1], 4, 8, value);
}
void SYSCFG_exticr2_exti5(uint8_t value)
{
	set_reg_block(&SYSCFG->EXTICR[1], 4, 4, value);
}
void SYSCFG_exticr2_exti4(uint8_t value)
{
	set_reg_block(&SYSCFG->EXTICR[1], 4, 0, value);
}
// exticr3
void SYSCFG_exticr3_exti11(uint8_t value)
{
	set_reg_block(&SYSCFG->EXTICR[2], 4, 12, value);
}
void SYSCFG_exticr3_exti10(uint8_t value)
{
	set_reg_block(&SYSCFG->EXTICR[2], 4, 8, value);
}
void SYSCFG_exticr3_exti9(uint8_t value)
{
	set_reg_block(&SYSCFG->EXTICR[2], 4, 4, value);
}
void SYSCFG_exticr3_exti8(uint8_t value)
{
	set_reg_block(&SYSCFG->EXTICR[2], 4, 0, value);
}
// exticr4
void SYSCFG_exticr4_exti15(uint8_t value)
{
	set_reg_block(&SYSCFG->EXTICR[3], 4, 12, value);
}
void SYSCFG_exticr4_exti14(uint8_t value)
{
	set_reg_block(&SYSCFG->EXTICR[3], 4, 8, value);
}
void SYSCFG_exticr4_exti13(uint8_t value)
{
	set_reg_block(&SYSCFG->EXTICR[3], 4, 4, value);
}
void SYSCFG_exticr4_exti12(uint8_t value)
{
	set_reg_block(&SYSCFG->EXTICR[3], 4, 0, value);
}
// cmpcr
uint8_t SYSCFG_cmpcr_ready(void)
{
	return get_reg_block(SYSCFG->CMPCR, 1, 8);
}
void SYSCFG_cmpcr_cmp_pd(uint8_t state)
{
	set_reg_block(&SYSCFG->CMPCR, 1, 0, state);
}
// cfgr
#ifdef STM32F446xx
void SYSCFG_cfgr_fmpi2c1_sda(uint8_t state)
{
	set_reg_block(&SYSCFG->CFGR, 1, 1, state);
}
void SYSCFG_cfgr_fmpi2c1_scl(uint8_t state)
{
	set_reg_block(&SYSCFG->CFGR, 1, 0, state);
}
#endif
/***********************************************/
/**** LINK Procedure & Function Definition *****/
/***********************************************/
/*** File Variables ***/
static SYSCFG_memrmp SYSCFG_memrmp_setup = {
	.swp_fmc = SYSCFG_memrmp_swp_fmc,
	.mem_mode = SYSCFG_memrmp_mem_mode
};
/*** File Variables ***/
static SYSCFG_pmc SYSCFG_pmc_setup = {
	.adcxdc2 = SYSCFG_pmc_adcxdc2,
	.adc1dc2 = SYSCFG_pmc_adc1dc2,
	.adc2dc2 = SYSCFG_pmc_adc2dc2,
	.adc3dc2 = SYSCFG_pmc_adc3dc2
};
/*** File Variables ***/
static SYSCFG_exticr1 SYSCFG_exticr1_setup = {
	.exti3 = SYSCFG_exticr1_exti3,
	.exti2 = SYSCFG_exticr1_exti2,
	.exti1 = SYSCFG_exticr1_exti1,
	.exti0 = SYSCFG_exticr1_exti0
};
/*** File Variables ***/
static SYSCFG_exticr2 SYSCFG_exticr2_setup = {
	.exti7 = SYSCFG_exticr2_exti7,
	.exti7 = SYSCFG_exticr2_exti6,
	.exti5 = SYSCFG_exticr2_exti5,
	.exti4 = SYSCFG_exticr2_exti4
};
/*** File Variables ***/
static SYSCFG_exticr3 SYSCFG_exticr3_setup = {
	.exti11 = SYSCFG_exticr3_exti11,
	.exti10 = SYSCFG_exticr3_exti10,
	.exti9 = SYSCFG_exticr3_exti9,
	.exti8 = SYSCFG_exticr3_exti8
};
/*** File Variables ***/
static SYSCFG_exticr4 SYSCFG_exticr4_setup = {
	.exti15 = SYSCFG_exticr4_exti15,
	.exti14 = SYSCFG_exticr4_exti14,
	.exti13 = SYSCFG_exticr4_exti13,
	.exti12 = SYSCFG_exticr4_exti12
};
/*** File Variables ***/
static SYSCFG_cmpcr SYSCFG_cmpcr_setup = {
	.ready = SYSCFG_cmpcr_ready,
	.cmp_pd = SYSCFG_cmpcr_cmp_pd
};
/*** File Variables ***/
#ifdef STM32F446xx
static SYSCFG_cfgr SYSCFG_cfgr_setup = {
	.fmpi2c1_sda = SYSCFG_cfgr_fmpi2c1_sda,
	.fmpi2c1_scl = SYSCFG_cfgr_fmpi2c1_scl
};
#else
static SYSCFG_cfgr SYSCFG_cfgr_setup = {
	.fmpi2c1_sda = NULL,
	.fmpi2c1_scl = NULL
};
#endif
/*** Other ***/
void SYSCFG_Clock(uint8_t state)
{
	if(state){ RCC->APB2ENR |= (1 << RCC_APB2ENR_SYSCFGEN_Pos); } else{ RCC->APB2ENR &= ~(1 << RCC_APB2ENR_SYSCFGEN_Pos); }

}
/************************************************/
/**** SYSCFG Procedure & Function Definition ****/
/************************************************/
static STM32FXXX_SYSCFG_Handler stm32fxxx_syscfg_setup = {
	/*** LINK ***/
	.memrmp = &SYSCFG_memrmp_setup,
	.pmc = &SYSCFG_pmc_setup,
	.exticr1 = &SYSCFG_exticr1_setup,
	.exticr2 = &SYSCFG_exticr2_setup,
	.exticr3 = &SYSCFG_exticr3_setup,
	.exticr4 = &SYSCFG_exticr4_setup,
	.cmpcr = &SYSCFG_cmpcr_setup,
	.cfgr = &SYSCFG_cfgr_setup,
	/*** Clock and Nvic ***/
	.clock = SYSCFG_Clock,
	.dev = dev
};

STM32FXXX_SYSCFG_Handler* syscfg(void){ return (STM32FXXX_SYSCFG_Handler*) &stm32fxxx_syscfg_setup; }

/*** EOF ***/

