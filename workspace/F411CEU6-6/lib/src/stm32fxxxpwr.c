/******************************************************************************
	STM32 XXX PWR
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     19062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxpwr.h"

/*** PWR Bit Mapping ***/
// CR
void PWR_cr_fissr(uint8_t state)
{
	set_reg_block(&PWR->CR, 1, 21, state);
}
void PWR_cr_fmssr(uint8_t state)
{
	set_reg_block(&PWR->CR, 1, 20, state);
}
void PWR_cr_uden(uint8_t value)
{
	set_reg_block(&PWR->CR, 2, 18, value);
}
void PWR_cr_odswen(uint8_t state)
{
	set_reg_block(&PWR->CR, 1, 17, state);
}
void PWR_cr_oden(uint8_t state)
{
	set_reg_block(&PWR->CR, 1, 16, state);
}
void PWR_cr_vos(uint8_t value)
{
	set_reg_block(&PWR->CR, 2, 14, value);
}
void PWR_cr_adcdc1(uint8_t state)
{
	set_reg_block(&PWR->CR, 1, 13, state);
}
void PWR_cr_mruds(uint8_t state)
{
	set_reg_block(&PWR->CR, 1, 11, state);
}
void PWR_cr_lpuds(uint8_t state)
{
	set_reg_block(&PWR->CR, 1, 10, state);
}
void PWR_cr_fpds(uint8_t state)
{
	set_reg_block(&PWR->CR, 1, 9, state);
}
void PWR_cr_dbp(uint8_t state)
{
	set_reg_block(&PWR->CR, 1, 8, state);
}
void PWR_cr_pls(uint8_t value)
{
	set_reg_block(&PWR->CR, 3, 5, value);
}
uint8_t PWR_cr_get_pls(void)
{
	return get_reg_block(PWR->CR, 3, 5);
}
void PWR_cr_pvde(uint8_t state)
{
	set_reg_block(&PWR->CR, 1, 4, state);
}
void PWR_cr_clear_csbf(void)
{
	set_reg_block(&PWR->CR, 1, 3, 1);
}
void PWR_cr_clear_cwuf(void)
{
	set_reg_block(&PWR->CR, 1, 2, 1);
}
void PWR_cr_pdds(uint8_t state)
{
	set_reg_block(&PWR->CR, 1, 1, state);
}
void PWR_cr_lpds(uint8_t state)
{
	set_reg_block(&PWR->CR, 1, 0, state);
}
// CSR
uint8_t PWR_udrdy(void)
{
	return get_reg_block(PWR->CSR, 2, 18);
}
void PWR_csr_clear_udrdy(void)
{
	set_reg_block(&PWR->CSR, 2, 18, 3);
}
uint8_t PWR_csr_odswrdy(void)
{
	return get_reg_block(PWR->CSR, 1, 17);
}
uint8_t PWR_csr_odrdy(void)
{
	return get_reg_block(PWR->CSR, 1, 16);
}
uint8_t PWR_csr_vosrdy(void)
{
	return get_reg_block(PWR->CSR, 1, 14);
}
void PWR_csr_bre(uint8_t state)
{
	set_reg_block(&PWR->CSR, 1, 9, state);
}
void PWR_csr_ewup1(uint8_t state)
{
	set_reg_block(&PWR->CSR, 1, 8, state);
}
void PWR_csr_ewup2(uint8_t state)
{
	set_reg_block(&PWR->CSR, 1, 7, state);
}
uint8_t PWR_csr_brr(void)
{
	return get_reg_block(PWR->CSR, 1, 3);
}
uint8_t PWR_csr_pvdo(void)
{
	return get_reg_block(PWR->CSR, 1, 2);
}
uint8_t PWR_csr_sbf(void)
{
	return get_reg_block(PWR->CSR, 1, 1);
}
uint8_t PWR_csr_wuf(void)
{
	return get_reg_block(PWR->CSR, 1, 0);
}
/*** Other ***/
void PWR_clock(uint8_t state)
{
	if(state){ RCC->APB1ENR |= (1 << RCC_APB1ENR_PWREN_Pos); }
	else{ RCC->APB1ENR &= ~(1 << RCC_APB1ENR_PWREN_Pos); }
}
/*** Auxiliar ***/
static STM32FXXX_PWR_cr stm32fxxx_pwr_cr_setup = {
	// CR
	.fissr = PWR_cr_fissr,
	.fmssr = PWR_cr_fmssr,
	.uden = PWR_cr_uden,
	.odswen = PWR_cr_odswen,
	.oden = PWR_cr_oden,
	.vos = PWR_cr_vos,
	.adcdc1 = PWR_cr_adcdc1,
	.mruds = PWR_cr_mruds,
	.lpuds = PWR_cr_lpuds,
	.fpds = PWR_cr_fpds,
	.dbp = PWR_cr_dbp,
	.pls = PWR_cr_pls,
	.get_pls = PWR_cr_get_pls,
	.pvde = PWR_cr_pvde,
	.clear_csbf = PWR_cr_clear_csbf,
	.clear_cwuf = PWR_cr_clear_cwuf,
	.pdds =PWR_cr_pdds,
	.lpds = PWR_cr_lpds
};
static STM32FXXX_PWR_csr stm32fxxx_pwr_csr_setup = {
	// CSR
	.udrdy = PWR_udrdy,
	.clear_udrdy = PWR_csr_clear_udrdy,
	.odswrdy = PWR_csr_odswrdy,
	.odrdy = PWR_csr_odrdy,
	.vosrdy = PWR_csr_vosrdy,
	.bre = PWR_csr_bre,
	.ewup1 = PWR_csr_ewup1,
	.ewup2 = PWR_csr_ewup2,
	.brr = PWR_csr_brr,
	.pvdo = PWR_csr_pvdo,
	.sbf = PWR_csr_sbf,
	.wuf = PWR_csr_wuf
};
/*** INIC Procedure & Function Definition ***/
static STM32FXXX_PWR_Handler stm32fxxx_pwr_setup = {
	/*** PWR Bit Mapping Link ***/
	.cr = &stm32fxxx_pwr_cr_setup,
	.csr = &stm32fxxx_pwr_csr_setup,
	/*** Clock and Nvic ***/
	.clock = PWR_clock,
	.dev = dev
};

STM32FXXX_PWR_Handler* pwr(void){ return (STM32FXXX_PWR_Handler*) &stm32fxxx_pwr_setup; }

/*** EOF ***/



