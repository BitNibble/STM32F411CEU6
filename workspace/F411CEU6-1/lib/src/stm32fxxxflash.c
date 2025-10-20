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

/*** File Variable ***/
static STM32FXXX_FLASH_acr stm32fxxx_flash_acr_setup = {0};
static STM32FXXX_FLASH_sr stm32fxxx_flash_sr_setup = {0};
static STM32FXXX_FLASH_cr stm32fxxx_flash_cr_setup = {0};
static STM32FXXX_FLASH_optcr stm32fxxx_flash_optcr_setup = {0};
static STM32FXXX_FLASH_Handler stm32fxxx_flash_setup = {0};

/*** File Procedure & Function Header ***/
STM32FXXX_FLASH_acr* stm32fxxx_flash_acr_inic(void);
STM32FXXX_FLASH_sr* stm32fxxx_flash_sr_inic(void);
STM32FXXX_FLASH_cr* stm32fxxx_flash_cr_inic(void);
STM32FXXX_FLASH_optcr* stm32fxxx_flash_optcr_inic(void);
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
STM32FXXX_FLASH_acr* stm32fxxx_flash_acr_inic(void)
{
	// ACR
	stm32fxxx_flash_acr_setup.dcrst = FLASH_acr_dcrst;
	stm32fxxx_flash_acr_setup.icrst = FLASH_acr_icrst;
	stm32fxxx_flash_acr_setup.dcen = FLASH_acr_dcen;
	stm32fxxx_flash_acr_setup.icen = FLASH_acr_icen;
	stm32fxxx_flash_acr_setup.prften = FLASH_acr_prften;
	stm32fxxx_flash_acr_setup.latency = FLASH_acr_latency;
	return &stm32fxxx_flash_acr_setup;
}
STM32FXXX_FLASH_sr* stm32fxxx_flash_sr_inic(void)
{
	// SR
	stm32fxxx_flash_sr_setup.bsy = FLASH_sr_bsy;
	stm32fxxx_flash_sr_setup.rderr = FLASH_sr_rderr;
	stm32fxxx_flash_sr_setup.clear_rderr = FLASH_sr_clear_rderr;
	stm32fxxx_flash_sr_setup.pgserr = FLASH_sr_pgserr;
	stm32fxxx_flash_sr_setup.clear_pgserr = FLASH_sr_clear_pgserr;
	stm32fxxx_flash_sr_setup.pgperr = FLASH_sr_pgperr;
	stm32fxxx_flash_sr_setup.clear_pgperr = FLASH_sr_clear_pgperr;
	stm32fxxx_flash_sr_setup.pgaerr = FLASH_sr_pgaerr;
	stm32fxxx_flash_sr_setup.clear_pgaerr = FLASH_sr_clear_pgaerr;
	stm32fxxx_flash_sr_setup.wrperr = FLASH_sr_wrperr;
	stm32fxxx_flash_sr_setup.clear_wrperr = FLASH_sr_clear_wrperr;
	stm32fxxx_flash_sr_setup.operr = FLASH_sr_operr;
	stm32fxxx_flash_sr_setup.clear_operr = FLASH_sr_clear_operr;
	stm32fxxx_flash_sr_setup.eop = FLASH_sr_eop;
	stm32fxxx_flash_sr_setup.clear_eop = FLASH_sr_clear_eop;
	return &stm32fxxx_flash_sr_setup;
}
STM32FXXX_FLASH_cr* stm32fxxx_flash_cr_inic(void)
{
	// CR
	stm32fxxx_flash_cr_setup.lock = FLASH_cr_lock;
	stm32fxxx_flash_cr_setup.errie = FLASH_cr_errie;
	stm32fxxx_flash_cr_setup.eopie = FLASH_cr_eopie;
	stm32fxxx_flash_cr_setup.strt = FLASH_cr_strt;
	stm32fxxx_flash_cr_setup.psize = FLASH_cr_psize;
	stm32fxxx_flash_cr_setup.snb = FLASH_cr_snb;
	stm32fxxx_flash_cr_setup.mer = FLASH_cr_mer;
	stm32fxxx_flash_cr_setup.ser = FLASH_cr_ser;
	stm32fxxx_flash_cr_setup.pg = FLASH_cr_pg;
	return &stm32fxxx_flash_cr_setup;
}
STM32FXXX_FLASH_optcr* stm32fxxx_flash_optcr_inic(void)
{
	// OPTCR
	stm32fxxx_flash_optcr_setup.sprmod = FLASH_optcr_sprmod;
	stm32fxxx_flash_optcr_setup.n_wrp = FLASH_optcr_n_wrp;
	stm32fxxx_flash_optcr_setup.get_n_wrp = FLASH_optcr_get_n_wrp;
	stm32fxxx_flash_optcr_setup.rdp = FLASH_optcr_rdp;
	stm32fxxx_flash_optcr_setup.get_rdp = FLASH_optcr_get_rdp;
	stm32fxxx_flash_optcr_setup.nrst_stdby = FLASH_optcr_nrst_stdby;
	stm32fxxx_flash_optcr_setup.nrst_stop = FLASH_optcr_nrst_stop;
	stm32fxxx_flash_optcr_setup.wdg_sw = FLASH_optcr_wdg_sw;
	stm32fxxx_flash_optcr_setup.bor_lev = FLASH_optcr_bor_lev;
	stm32fxxx_flash_optcr_setup.optstrt = FLASH_optcr_optstrt;
	stm32fxxx_flash_optcr_setup.optlock = FLASH_optcr_optlock;
	return &stm32fxxx_flash_optcr_setup;
}
/*** INIC Procedure & Function Definition ***/
void flash_enable(void)
{
	/*** FLASH Bit Mapping Link ***/
	stm32fxxx_flash_setup.acr = stm32fxxx_flash_acr_inic();
	stm32fxxx_flash_setup.sr = stm32fxxx_flash_sr_inic();
	stm32fxxx_flash_setup.cr = stm32fxxx_flash_cr_inic();
	stm32fxxx_flash_setup.optcr = stm32fxxx_flash_optcr_inic();
	stm32fxxx_flash_setup.keyr = FLASH_keyr_key;
	stm32fxxx_flash_setup.optkeyr = FLASH_optkeyr_optkey;
	stm32fxxx_flash_setup.nvic = FLASH_nvic;
	stm32fxxx_flash_setup.dev = dev;
}

STM32FXXX_FLASH_Handler* flash(void){ return (STM32FXXX_FLASH_Handler*) &stm32fxxx_flash_setup; }

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

