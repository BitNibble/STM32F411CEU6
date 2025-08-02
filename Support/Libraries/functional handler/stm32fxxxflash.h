/******************************************************************************
	STM32 XXX FLASH
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 19062023
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXFLASH_H_
	#define _STM32FXXXFLASH_H_
/*** Library ***/
#include "stm32fxxxinstance.h"
/*** Macros ***/
#ifndef FLASH_KEY1
	#define FLASH_KEY1  0x45670123
#endif
#ifndef FLASH_KEY2
	#define FLASH_KEY2  0xCDEF89AB
#endif
#ifndef FLASH_OPTKEY1
	#define FLASH_OPTKEY1  0x08192A3B
#endif
#ifndef FLASH_OPTKEY2
	#define FLASH_OPTKEY2  0x4C5D6E7F
#endif
#ifndef FLASH_READPROTECTL0
	#define FLASH_READPROTECTL0  0xAA
#endif
#ifndef FLASH_READPROTECTL2
	#define FLASH_READPROTECTL2  0xCC
#endif
/*** FLASH Bit Mapping TypeDef ***/
// ACR
typedef struct
{
	void (*dcrst)(uint8_t state);
	void (*icrst)(uint8_t state);
	void (*dcen)(uint8_t state);
	void (*icen)(uint8_t state);
	void (*prften)(uint8_t state);
	void (*latency)(uint8_t value);
}STM32FXXXFLASH_acr;
// SR
typedef struct
{
	uint8_t (*bsy)(void);
	uint8_t (*rderr)(void);
	void (*clear_rderr)(void);
	uint8_t (*pgserr)(void);
	void (*clear_pgserr)(void);
	uint8_t (*pgperr)(void);
	void (*clear_pgperr)(void);
	uint8_t (*pgaerr)(void);
	void (*clear_pgaerr)(void);
	uint8_t (*wrperr)(void);
	void (*clear_wrperr)(void);
	uint8_t (*operr)(void);
	void (*clear_operr)(void);
	uint8_t (*eop)(void);
	void (*clear_eop)(void);
}STM32FXXXFLASH_sr;
// CR
typedef struct
{
	void (*lock)(void);
	void (*errie)(uint8_t state);
	void (*eopie)(uint8_t state);
	void (*strt)(void);
	void (*psize)(uint8_t value);
	void (*snb)(uint8_t value);
	void (*mer)(uint8_t state);
	void (*ser)(uint8_t state);
	void (*pg)(uint8_t state);
}STM32FXXXFLASH_cr;
// OPTCR
typedef struct
{
	void (*sprmod)(uint8_t state);
	void (*n_wrp)(uint8_t value);
	uint8_t (*get_n_wrp)(void);
	void (*rdp)(uint8_t value);
	uint8_t(*get_rdp)(void);
	void (*nrst_stdby)(uint8_t state);
	void (*nrst_stop)(uint8_t state);
	void (*wdg_sw)(uint8_t state);
	void (*bor_lev)(uint8_t value);
	void (*optstrt)(uint8_t state);
	void (*optlock)(uint8_t state);
}STM32FXXXFLASH_optcr;
/*** FLASH TypeDef ***/
typedef struct
{

	/*** Bit Mapping ***/
	STM32FXXXFLASH_acr* acr;
	STM32FXXXFLASH_sr* sr;
	STM32FXXXFLASH_cr* cr;
	STM32FXXXFLASH_optcr* optcr;
	void (*keyr)(uint32_t);
	void (*optkeyr)(uint32_t);
	/*** Other ***/
	void (*nvic)(uint8_t state);
}STM32FXXX_FLASH;

void flash_enable(void);
STM32FXXX_FLASH* flash(void);

/*** Procedure & Function Header ***/
void STM32FXXXFLASH_nvic(uint8_t state);
/*** FLASH Bit Mapping Header ***/
// ACR
void STM32FXXXFLASH_acr_dcrst(uint8_t state);
void STM32FXXXFLASH_acr_icrst(uint8_t state);
void STM32FXXXFLASH_acr_dcen(uint8_t state);
void STM32FXXXFLASH_acr_icen(uint8_t state);
void STM32FXXXFLASH_acr_prften(uint8_t state);
void STM32FXXXFLASH_acr_latency(uint8_t value);
// SR
uint8_t STM32FXXXFLASH_sr_bsy(void);
uint8_t STM32FXXXFLASH_sr_rderr(void);
void STM32FXXXFLASH_sr_clear_rderr(void);
uint8_t STM32FXXXFLASH_sr_pgserr(void);
void STM32FXXXFLASH_sr_clear_pgserr(void);
uint8_t STM32FXXXFLASH_sr_pgperr(void);
void STM32FXXXFLASH_sr_clear_pgperr(void);
uint8_t STM32FXXXFLASH_sr_pgaerr(void);
void STM32FXXXFLASH_sr_clear_pgaerr(void);
uint8_t STM32FXXXFLASH_sr_wrperr(void);
void STM32FXXXFLASH_sr_clear_wrperr(void);
uint8_t STM32FXXXFLASH_sr_operr(void);
void STM32FXXXFLASH_sr_clear_operr(void);
uint8_t STM32FXXXFLASH_sr_eop(void);
void STM32FXXXFLASH_sr_clear_eop(void);
// CR
void STM32FXXXFLASH_cr_lock(void);
void STM32FXXXFLASH_cr_errie(uint8_t state);
void STM32FXXXFLASH_cr_eopie(uint8_t state);
void STM32FXXXFLASH_cr_strt(void);
void STM32FXXXFLASH_cr_psize(uint8_t value);
void STM32FXXXFLASH_cr_snb(uint8_t value);
void STM32FXXXFLASH_cr_mer(uint8_t state);
void STM32FXXXFLASH_cr_ser(uint8_t state);
void STM32FXXXFLASH_cr_pg(uint8_t state);
// OPTCR
void STM32FXXXFLASH_optcr_sprmod(uint8_t state);
void STM32FXXXFLASH_optcr_n_wrp(uint8_t value);
uint8_t STM32FXXXFLASH_optcr_get_n_wrp(void);
void STM32FXXXFLASH_optcr_rdp(uint8_t value);
uint8_t STM32FXXXFLASH_optcr_get_rdp(void);
void STM32FXXXFLASH_optcr_nrst_stdby(uint8_t state);
void STM32FXXXFLASH_optcr_nrst_stop(uint8_t state);
void STM32FXXXFLASH_optcr_wdg_sw(uint8_t state);
void STM32FXXXFLASH_optcr_bor_lev(uint8_t value);
void STM32FXXXFLASH_optcr_optstrt(uint8_t state);
void STM32FXXXFLASH_optcr_optlock(uint8_t state);
// KEYR
void STM32FXXXFLASH_keyr_key(uint32_t value);
// OPTKEYR
void STM32FXXXFLASH_optkeyr_optkey(uint32_t value);

/*** INTERRRUPT HEADER ***/
void FLASH_IRQHandler(void);

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

