/******************************************************************************
	STM32 XXX FLASH
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 19062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxflash.h"

/*** File Variable ***/
static STM32FXXXFLASH_acr stm32fxxx_flash_acr;
static STM32FXXXFLASH_sr stm32fxxx_flash_sr;
static STM32FXXXFLASH_cr stm32fxxx_flash_cr;
static STM32FXXXFLASH_optcr stm32fxxx_flash_optcr;
static STM32FXXX_FLASH stm32fxxx_flash = {0};

/*** File Procedure & Function Header ***/
STM32FXXXFLASH_acr* stm32fxxx_flash_acr_inic(void);
STM32FXXXFLASH_sr* stm32fxxx_flash_sr_inic(void);
STM32FXXXFLASH_cr* stm32fxxx_flash_cr_inic(void);
STM32FXXXFLASH_optcr* stm32fxxx_flash_optcr_inic(void);
/*** FLASH Bit Mapping ***/
// ACR
void STM32FXXXFLASH_acr_dcrst(uint8_t state)
{
	set_reg_block(&FLASH->ACR, 1, 12, state);
}
void STM32FXXXFLASH_acr_icrst(uint8_t state)
{
	set_reg_block(&FLASH->ACR, 1, 11, state);
}
void STM32FXXXFLASH_acr_dcen(uint8_t state)
{
	set_reg_block(&FLASH->ACR, 1, 10, state);
}
void STM32FXXXFLASH_acr_icen(uint8_t state)
{
	set_reg_block(&FLASH->ACR, 1, 9, state);
}
void STM32FXXXFLASH_acr_prften(uint8_t state)
{
	set_reg_block(&FLASH->ACR, 1, 8, state);
}
void STM32FXXXFLASH_acr_latency(uint8_t value)
{
	set_reg_block(&FLASH->ACR, 4, 0, value);
}
// KEYR
void STM32FXXXFLASH_keyr_key(uint32_t value)
{
	FLASH->KEYR = value;
}
// OPTKEYR
void STM32FXXXFLASH_optkeyr_optkey(uint32_t value)
{
	FLASH->OPTKEYR = value;
}
// SR
uint8_t STM32FXXXFLASH_sr_bsy(void)
{
	return get_reg_block(FLASH->SR, 1, 16);
}
uint8_t STM32FXXXFLASH_sr_rderr(void)
{
	return get_reg_block(FLASH->SR, 1, 8);
}
void STM32FXXXFLASH_sr_clear_rderr(void)
{
	set_reg_block(&FLASH->SR, 1, 8, 1);
}
uint8_t STM32FXXXFLASH_sr_pgserr(void)
{
	return get_reg_block(FLASH->SR, 1, 7);
}
void STM32FXXXFLASH_sr_clear_pgserr(void)
{
	set_reg_block(&FLASH->SR, 1, 7, 1);
}
uint8_t STM32FXXXFLASH_sr_pgperr(void)
{
	return get_reg_block(FLASH->SR, 1, 6);
}
void STM32FXXXFLASH_sr_clear_pgperr(void)
{
	set_reg_block(&FLASH->SR, 1, 6, 1);
}
uint8_t STM32FXXXFLASH_sr_pgaerr(void)
{
	return get_reg_block(FLASH->SR, 1, 5);
}
void STM32FXXXFLASH_sr_clear_pgaerr(void)
{
	set_reg_block(&FLASH->SR, 1, 5, 1);
}
uint8_t STM32FXXXFLASH_sr_wrperr(void)
{
	return get_reg_block(FLASH->SR, 1, 4);
}
void STM32FXXXFLASH_sr_clear_wrperr(void)
{
	set_reg_block(&FLASH->SR, 1, 4, 1);
}
uint8_t STM32FXXXFLASH_sr_operr(void)
{
	return get_reg_block(FLASH->SR, 1, 1);
}
void STM32FXXXFLASH_sr_clear_operr(void)
{
	set_reg_block(&FLASH->SR, 1, 1, 1);
}
uint8_t STM32FXXXFLASH_sr_eop(void)
{
	return get_reg_block(FLASH->SR, 1, 0);
}
void STM32FXXXFLASH_sr_clear_eop(void)
{
	set_reg_block(&FLASH->SR, 1, 0, 1);
}
// CR
void STM32FXXXFLASH_cr_lock(void)
{
	set_reg_block(&FLASH->CR, 1, 31, 1);
}
void STM32FXXXFLASH_cr_errie(uint8_t state)
{
	set_reg_block(&FLASH->CR, 1, 25, state);
}
void STM32FXXXFLASH_cr_eopie(uint8_t state)
{
	set_reg_block(&FLASH->CR, 1, 24, state);
}
void STM32FXXXFLASH_cr_strt(void)
{
	set_reg_block(&FLASH->CR, 1, 16, 1);
}
void STM32FXXXFLASH_cr_psize(uint8_t value)
{
	set_reg_block(&FLASH->CR, 2, 8, value);
}
void STM32FXXXFLASH_cr_snb(uint8_t value)
{
	set_reg_block(&FLASH->CR, 4, 3, value);
}
void STM32FXXXFLASH_cr_mer(uint8_t state)
{
	set_reg_block(&FLASH->CR, 1, 2, state);
}
void STM32FXXXFLASH_cr_ser(uint8_t state)
{
	set_reg_block(&FLASH->CR, 1, 1, state);
}
void STM32FXXXFLASH_cr_pg(uint8_t state)
{
	set_reg_block(&FLASH->CR, 1, 0, state);
}
// OPTCR
void STM32FXXXFLASH_optcr_sprmod(uint8_t state)
{
	set_reg_block(&FLASH->OPTCR, 1, 31, state);
}
void STM32FXXXFLASH_optcr_n_wrp(uint8_t value)
{
	set_reg_block(&FLASH->OPTCR, 8, 16, value);
}
uint8_t STM32FXXXFLASH_optcr_get_n_wrp(void)
{
	return get_reg_block(FLASH->OPTCR, 8, 16);
}
void STM32FXXXFLASH_optcr_rdp(uint8_t value)
{ // Do not permit Blocking Chip !!
	if(value != 0xCC){ set_reg_block(&FLASH->OPTCR, 8, 8, value);}
}
uint8_t STM32FXXXFLASH_optcr_get_rdp(void)
{
	return get_reg_block(FLASH->OPTCR, 8, 8);
}
void STM32FXXXFLASH_optcr_nrst_stdby(uint8_t state)
{
	set_reg_block(&FLASH->OPTCR, 1, 7, state);
}
void STM32FXXXFLASH_optcr_nrst_stop(uint8_t state)
{
	set_reg_block(&FLASH->OPTCR, 1, 6, state);
}
void STM32FXXXFLASH_optcr_wdg_sw(uint8_t state)
{
	set_reg_block(&FLASH->OPTCR, 1, 5, state);
}
void STM32FXXXFLASH_optcr_bor_lev(uint8_t value)
{
	set_reg_block(&FLASH->OPTCR, 2, 2, value);
}
void STM32FXXXFLASH_optcr_optstrt(uint8_t state)
{
	set_reg_block(&FLASH->OPTCR, 1, 1, state);
}
void STM32FXXXFLASH_optcr_optlock(uint8_t state)
{
	set_reg_block(&FLASH->OPTCR, 1, 0, state);
}
/*** Other ***/
void STM32FXXXFLASH_nvic(uint8_t state)
{
	if(state){ set_bit_block(NVIC->ISER, 1, FLASH_IRQn, 1); } else{ set_bit_block(NVIC->ICER, 1, FLASH_IRQn, 1); }
}
/*** FLASH Auxiliar ***/
STM32FXXXFLASH_acr* stm32fxxx_flash_acr_inic(void)
{
	// ACR
	stm32fxxx_flash_acr.dcrst = STM32FXXXFLASH_acr_dcrst;
	stm32fxxx_flash_acr.icrst = STM32FXXXFLASH_acr_icrst;
	stm32fxxx_flash_acr.dcen = STM32FXXXFLASH_acr_dcen;
	stm32fxxx_flash_acr.icen = STM32FXXXFLASH_acr_icen;
	stm32fxxx_flash_acr.prften = STM32FXXXFLASH_acr_prften;
	stm32fxxx_flash_acr.latency = STM32FXXXFLASH_acr_latency;
	return &stm32fxxx_flash_acr;
}
STM32FXXXFLASH_sr* stm32fxxx_flash_sr_inic(void)
{
	// SR
	stm32fxxx_flash_sr.bsy = STM32FXXXFLASH_sr_bsy;
	stm32fxxx_flash_sr.rderr = STM32FXXXFLASH_sr_rderr;
	stm32fxxx_flash_sr.clear_rderr = STM32FXXXFLASH_sr_clear_rderr;
	stm32fxxx_flash_sr.pgserr = STM32FXXXFLASH_sr_pgserr;
	stm32fxxx_flash_sr.clear_pgserr = STM32FXXXFLASH_sr_clear_pgserr;
	stm32fxxx_flash_sr.pgperr = STM32FXXXFLASH_sr_pgperr;
	stm32fxxx_flash_sr.clear_pgperr = STM32FXXXFLASH_sr_clear_pgperr;
	stm32fxxx_flash_sr.pgaerr = STM32FXXXFLASH_sr_pgaerr;
	stm32fxxx_flash_sr.clear_pgaerr = STM32FXXXFLASH_sr_clear_pgaerr;
	stm32fxxx_flash_sr.wrperr = STM32FXXXFLASH_sr_wrperr;
	stm32fxxx_flash_sr.clear_wrperr = STM32FXXXFLASH_sr_clear_wrperr;
	stm32fxxx_flash_sr.operr = STM32FXXXFLASH_sr_operr;
	stm32fxxx_flash_sr.clear_operr = STM32FXXXFLASH_sr_clear_operr;
	stm32fxxx_flash_sr.eop = STM32FXXXFLASH_sr_eop;
	stm32fxxx_flash_sr.clear_eop = STM32FXXXFLASH_sr_clear_eop;
	return &stm32fxxx_flash_sr;
}
STM32FXXXFLASH_cr* stm32fxxx_flash_cr_inic(void)
{
	// CR
	stm32fxxx_flash_cr.lock = STM32FXXXFLASH_cr_lock;
	stm32fxxx_flash_cr.errie = STM32FXXXFLASH_cr_errie;
	stm32fxxx_flash_cr.eopie = STM32FXXXFLASH_cr_eopie;
	stm32fxxx_flash_cr.strt = STM32FXXXFLASH_cr_strt;
	stm32fxxx_flash_cr.psize = STM32FXXXFLASH_cr_psize;
	stm32fxxx_flash_cr.snb = STM32FXXXFLASH_cr_snb;
	stm32fxxx_flash_cr.mer = STM32FXXXFLASH_cr_mer;
	stm32fxxx_flash_cr.ser = STM32FXXXFLASH_cr_ser;
	stm32fxxx_flash_cr.pg = STM32FXXXFLASH_cr_pg;
	return &stm32fxxx_flash_cr;
}
STM32FXXXFLASH_optcr* stm32fxxx_flash_optcr_inic(void)
{
	// OPTCR
	stm32fxxx_flash_optcr.sprmod = STM32FXXXFLASH_optcr_sprmod;
	stm32fxxx_flash_optcr.n_wrp = STM32FXXXFLASH_optcr_n_wrp;
	stm32fxxx_flash_optcr.get_n_wrp = STM32FXXXFLASH_optcr_get_n_wrp;
	stm32fxxx_flash_optcr.rdp = STM32FXXXFLASH_optcr_rdp;
	stm32fxxx_flash_optcr.get_rdp = STM32FXXXFLASH_optcr_get_rdp;
	stm32fxxx_flash_optcr.nrst_stdby = STM32FXXXFLASH_optcr_nrst_stdby;
	stm32fxxx_flash_optcr.nrst_stop = STM32FXXXFLASH_optcr_nrst_stop;
	stm32fxxx_flash_optcr.wdg_sw = STM32FXXXFLASH_optcr_wdg_sw;
	stm32fxxx_flash_optcr.bor_lev = STM32FXXXFLASH_optcr_bor_lev;
	stm32fxxx_flash_optcr.optstrt = STM32FXXXFLASH_optcr_optstrt;
	stm32fxxx_flash_optcr.optlock = STM32FXXXFLASH_optcr_optlock;
	return &stm32fxxx_flash_optcr;
}
/*** INIC Procedure & Function Definition ***/
void flash_enable(void)
{
	/*** FLASH Bit Mapping Link ***/
	stm32fxxx_flash.acr = stm32fxxx_flash_acr_inic();
	stm32fxxx_flash.sr = stm32fxxx_flash_sr_inic();
	stm32fxxx_flash.cr = stm32fxxx_flash_cr_inic();
	stm32fxxx_flash.optcr = stm32fxxx_flash_optcr_inic();
	stm32fxxx_flash.keyr = STM32FXXXFLASH_keyr_key;
	stm32fxxx_flash.optkeyr = STM32FXXXFLASH_optkeyr_optkey;
	stm32fxxx_flash.nvic = STM32FXXXFLASH_nvic;

	//return &stm32fxxx_flash;
}

STM32FXXX_FLASH* flash(void){ return (STM32FXXX_FLASH*) &stm32fxxx_flash; }

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

