/******************************************************************************
	STM32 XXX FLASH
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     19062023
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXFLASH_H_
	#define _STM32FXXXFLASH_H_

/*** Library ***/
#if defined (STM32F411xE)
	#include "stm32f411ceu6.h"
#elif defined(STM32F446xx)
	#include "stm32f446re.h"
#else
	void* dev(void){ return NULL; }
#endif
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
}STM32FXXX_FLASH_acr;
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
}STM32FXXX_FLASH_sr;
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
}STM32FXXX_FLASH_cr;
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
}STM32FXXX_FLASH_optcr;
/*** FLASH TypeDef ***/
typedef const struct
{
	/*** Bit Mapping ***/
	STM32FXXX_FLASH_acr* acr;
	STM32FXXX_FLASH_sr* sr;
	STM32FXXX_FLASH_cr* cr;
	STM32FXXX_FLASH_optcr* optcr;
	void (*keyr)(uint32_t);
	void (*optkeyr)(uint32_t);
	/*** Clock and Nvic ***/
	void (*nvic)(uint8_t state);

#if defined(STM32F411CEU6_H)
	STM32F411CEU6_Handler* (*dev)(void);
#elif defined(STM32F446RE_H)
	STM32F446RE_Handler* (*dev)(void);
#else
	void* (*dev)(void);
#endif
}STM32FXXX_FLASH_Handler;

STM32FXXX_FLASH_Handler* flash(void);

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

