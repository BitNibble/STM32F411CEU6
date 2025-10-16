/******************************************************************************
	STM32 XXX PWR
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     19062023
Comment:

*******************************************************************************/
#ifndef _STM32FXXXPWR_H_
	#define _STM32FXXXPWR_H_

/*** Library ***/
#include "stm32f411ceu6.h"
/*** PWR Bit Mapping TypeDef ***/
// CR
typedef struct
{
	void (*fissr)(uint8_t state);
	void (*fmssr)(uint8_t state);
	void (*uden)(uint8_t value);
	void (*odswen)(uint8_t state);
	void (*oden)(uint8_t state);
	void (*vos)(uint8_t value);
	void (*adcdc1)(uint8_t state);
	void (*mruds)(uint8_t state);
	void (*lpuds)(uint8_t state);
	void (*fpds)(uint8_t state);
	void (*dbp)(uint8_t state);
	void (*pls)(uint8_t value);
	uint8_t (*get_pls)(void);
	void (*pvde)(uint8_t state);
	void (*clear_csbf)(void);
	void (*clear_cwuf)(void);
	void (*pdds)(uint8_t state);
	void (*lpds)(uint8_t state);
}STM32FXXX_PWR_cr;
// CSR
typedef struct
{
	uint8_t (*udrdy)(void);
	void (*clear_udrdy)(void);
	uint8_t (*odswrdy)(void);
	uint8_t (*odrdy)(void);
	uint8_t (*vosrdy)(void);
	void (*bre)(uint8_t state);
	void (*ewup1)(uint8_t state);
	void (*ewup2)(uint8_t state);
	uint8_t (*brr)(void);
	uint8_t (*pvdo)(void);
	uint8_t (*sbf)(void);
	uint8_t (*wuf)(void);
}STM32FXXX_PWR_csr;

/*** PWR TypeDef ***/
typedef struct
{
	/*** Bit Mapping ***/
	STM32FXXX_PWR_cr* cr;
	STM32FXXX_PWR_csr* csr;
	/*** Clock and Nvic ***/
	void (*clock)(uint8_t state);

#if defined(STM32F411CEU6_H)
	STM32F411CEU6_Handler* (*dev)(void);
#endif
}STM32FXXX_PWR_Handler;

STM32FXXX_PWR_Handler* pwr(void);

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

