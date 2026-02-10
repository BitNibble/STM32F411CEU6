/******************************************************************************
	STM32 XXX FLASH
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     19062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxflash.h"

/*** FLASH Bit Mapping ***/
// ACR
void FLASH_acr_dcrst(uint8_t state)
{
	set_reg_block(&FLASH->ACR, 1, 12, state);
}
void FLASH_acr_icrst(uint8_t state)
{
	set_reg_block(&FLASH->ACR, 1, 11, state);
}
void FLASH_acr_dcen(uint8_t state)
{
	set_reg_block(&FLASH->ACR, 1, 10, state);
}
void FLASH_acr_icen(uint8_t state)
{
	set_reg_block(&FLASH->ACR, 1, 9, state);
}
void FLASH_acr_prften(uint8_t state)
{
	set_reg_block(&FLASH->ACR, 1, 8, state);
}
void FLASH_acr_latency(uint8_t value)
{
	set_reg_block(&FLASH->ACR, 4, 0, value);
}
// KEYR
void FLASH_keyr_key(uint32_t value)
{
	FLASH->KEYR = value;
}
// OPTKEYR
void FLASH_optkeyr_optkey(uint32_t value)
{
	FLASH->OPTKEYR = value;
}
// SR
uint8_t FLASH_sr_bsy(void)
{
	return get_reg_block(FLASH->SR, 1, 16);
}
uint8_t FLASH_sr_rderr(void)
{
	return get_reg_block(FLASH->SR, 1, 8);
}
void FLASH_sr_clear_rderr(void)
{
	set_reg_block(&FLASH->SR, 1, 8, 1);
}
uint8_t FLASH_sr_pgserr(void)
{
	return get_reg_block(FLASH->SR, 1, 7);
}
void FLASH_sr_clear_pgserr(void)
{
	set_reg_block(&FLASH->SR, 1, 7, 1);
}
uint8_t FLASH_sr_pgperr(void)
{
	return get_reg_block(FLASH->SR, 1, 6);
}
void FLASH_sr_clear_pgperr(void)
{
	set_reg_block(&FLASH->SR, 1, 6, 1);
}
uint8_t FLASH_sr_pgaerr(void)
{
	return get_reg_block(FLASH->SR, 1, 5);
}
void FLASH_sr_clear_pgaerr(void)
{
	set_reg_block(&FLASH->SR, 1, 5, 1);
}
uint8_t FLASH_sr_wrperr(void)
{
	return get_reg_block(FLASH->SR, 1, 4);
}
void FLASH_sr_clear_wrperr(void)
{
	set_reg_block(&FLASH->SR, 1, 4, 1);
}
uint8_t FLASH_sr_operr(void)
{
	return get_reg_block(FLASH->SR, 1, 1);
}
void FLASH_sr_clear_operr(void)
{
	set_reg_block(&FLASH->SR, 1, 1, 1);
}
uint8_t FLASH_sr_eop(void)
{
	return get_reg_block(FLASH->SR, 1, 0);
}
void FLASH_sr_clear_eop(void)
{
	set_reg_block(&FLASH->SR, 1, 0, 1);
}
// CR
void FLASH_cr_lock(void)
{
	set_reg_block(&FLASH->CR, 1, 31, 1);
}
void FLASH_cr_errie(uint8_t state)
{
	set_reg_block(&FLASH->CR, 1, 25, state);
}
void FLASH_cr_eopie(uint8_t state)
{
	set_reg_block(&FLASH->CR, 1, 24, state);
}
void FLASH_cr_strt(void)
{
	set_reg_block(&FLASH->CR, 1, 16, 1);
}
void FLASH_cr_psize(uint8_t value)
{
	set_reg_block(&FLASH->CR, 2, 8, value);
}
void FLASH_cr_snb(uint8_t value)
{
	set_reg_block(&FLASH->CR, 4, 3, value);
}
void FLASH_cr_mer(uint8_t state)
{
	set_reg_block(&FLASH->CR, 1, 2, state);
}
void FLASH_cr_ser(uint8_t state)
{
	set_reg_block(&FLASH->CR, 1, 1, state);
}
void FLASH_cr_pg(uint8_t state)
{
	set_reg_block(&FLASH->CR, 1, 0, state);
}
// OPTCR
void FLASH_optcr_sprmod(uint8_t state)
{
	set_reg_block(&FLASH->OPTCR, 1, 31, state);
}
void FLASH_optcr_n_wrp(uint8_t value)
{
	set_reg_block(&FLASH->OPTCR, 8, 16, value);
}
uint8_t FLASH_optcr_get_n_wrp(void)
{
	return get_reg_block(FLASH->OPTCR, 8, 16);
}
void FLASH_optcr_rdp(uint8_t value)
{ // Do not permit Blocking Chip !!
	if(value != 0xCC){ set_reg_block(&FLASH->OPTCR, 8, 8, value);}
}
uint8_t FLASH_optcr_get_rdp(void)
{
	return get_reg_block(FLASH->OPTCR, 8, 8);
}
void FLASH_optcr_nrst_stdby(uint8_t state)
{
	set_reg_block(&FLASH->OPTCR, 1, 7, state);
}
void FLASH_optcr_nrst_stop(uint8_t state)
{
	set_reg_block(&FLASH->OPTCR, 1, 6, state);
}
void FLASH_optcr_wdg_sw(uint8_t state)
{
	set_reg_block(&FLASH->OPTCR, 1, 5, state);
}
void FLASH_optcr_bor_lev(uint8_t value)
{
	set_reg_block(&FLASH->OPTCR, 2, 2, value);
}
void FLASH_optcr_optstrt(uint8_t state)
{
	set_reg_block(&FLASH->OPTCR, 1, 1, state);
}
void FLASH_optcr_optlock(uint8_t state)
{
	set_reg_block(&FLASH->OPTCR, 1, 0, state);
}
/*** Other ***/
void FLASH_nvic(uint8_t state)
{
	if(state){ set_bit_block(NVIC->ISER, 1, FLASH_IRQn, 1); } else{ set_bit_block(NVIC->ICER, 1, FLASH_IRQn, 1); }
}
/*** FLASH Auxiliar ***/
static STM32FXXX_FLASH_acr stm32fxxx_flash_acr_setup = {
	// ACR
	.dcrst = FLASH_acr_dcrst,
	.icrst = FLASH_acr_icrst,
	.dcen = FLASH_acr_dcen,
	.icen = FLASH_acr_icen,
	.prften = FLASH_acr_prften,
	.latency = FLASH_acr_latency
};
static STM32FXXX_FLASH_sr stm32fxxx_flash_sr_setup = {
	// SR
	.bsy = FLASH_sr_bsy,
	.rderr = FLASH_sr_rderr,
	.clear_rderr = FLASH_sr_clear_rderr,
	.pgserr = FLASH_sr_pgserr,
	.clear_pgserr = FLASH_sr_clear_pgserr,
	.pgperr = FLASH_sr_pgperr,
	.clear_pgperr = FLASH_sr_clear_pgperr,
	.pgaerr = FLASH_sr_pgaerr,
	.clear_pgaerr = FLASH_sr_clear_pgaerr,
	.wrperr = FLASH_sr_wrperr,
	.clear_wrperr = FLASH_sr_clear_wrperr,
	.operr = FLASH_sr_operr,
	.clear_operr = FLASH_sr_clear_operr,
	.eop = FLASH_sr_eop,
	.clear_eop = FLASH_sr_clear_eop
};
static STM32FXXX_FLASH_cr stm32fxxx_flash_cr_setup = {
	// CR
	.lock = FLASH_cr_lock,
	.errie = FLASH_cr_errie,
	.eopie = FLASH_cr_eopie,
	.strt = FLASH_cr_strt,
	.psize = FLASH_cr_psize,
	.snb = FLASH_cr_snb,
	.mer = FLASH_cr_mer,
	.ser = FLASH_cr_ser,
	.pg = FLASH_cr_pg
};
static STM32FXXX_FLASH_optcr stm32fxxx_flash_optcr_setup = {
	// OPTCR
	.sprmod = FLASH_optcr_sprmod,
	.n_wrp = FLASH_optcr_n_wrp,
	.get_n_wrp = FLASH_optcr_get_n_wrp,
	.rdp = FLASH_optcr_rdp,
	.get_rdp = FLASH_optcr_get_rdp,
	.nrst_stdby = FLASH_optcr_nrst_stdby,
	.nrst_stop = FLASH_optcr_nrst_stop,
	.wdg_sw = FLASH_optcr_wdg_sw,
	.bor_lev = FLASH_optcr_bor_lev,
	.optstrt = FLASH_optcr_optstrt,
	.optlock = FLASH_optcr_optlock
};
/*** INIC Procedure & Function Definition ***/
static STM32FXXX_FLASH_Handler stm32fxxx_flash_setup = {
	.acr = &stm32fxxx_flash_acr_setup,
	.sr = &stm32fxxx_flash_sr_setup,
	.cr = &stm32fxxx_flash_cr_setup,
	.optcr = &stm32fxxx_flash_optcr_setup,
	.keyr = FLASH_keyr_key,
	.optkeyr = FLASH_optkeyr_optkey,
	.nvic = FLASH_nvic,
	.dev = dev
};

STM32FXXX_FLASH_Handler* flash(void){ return (STM32FXXX_FLASH_Handler*) &stm32fxxx_flash_setup; }

/*** EOF ***/



