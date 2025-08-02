/******************************************************************************
	STM32 XXX PWR
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 19062023
Comment:

*******************************************************************************/
#ifndef _STM32FXXXPWR_H_
	#define _STM32FXXXPWR_H_
/*** Library ***/
#include "stm32fxxxinstance.h"
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
}STM32FXXXPWR_cr;
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
}STM32FXXXPWR_csr;

/*** PWR TypeDef ***/
typedef struct
{
	PWR_TypeDef* instance;
	/*** Bit Mapping ***/
	STM32FXXXPWR_cr* cr;
	STM32FXXXPWR_csr* csr;
	/*** Other ***/
	void (*clock)(uint8_t state);
}STM32FXXX_PWR;

void pwr_enable(void);
STM32FXXX_PWR* pwr(void);

/*** PWR Bit Mapping Header ***/
void STM32FXXXPWR_clock(uint8_t state);
// CR
void STM32FXXXPWR_cr_fissr(uint8_t state);
void STM32FXXXPWR_cr_fmssr(uint8_t state);
void STM32FXXXPWR_cr_uden(uint8_t value);
void STM32FXXXPWR_cr_odswen(uint8_t state);
void STM32FXXXPWR_cr_oden(uint8_t state);
void STM32FXXXPWR_cr_vos(uint8_t value);
void STM32FXXXPWR_cr_adcdc1(uint8_t state);
void STM32FXXXPWR_cr_mruds(uint8_t state);
void STM32FXXXPWR_cr_lpuds(uint8_t state);
void STM32FXXXPWR_cr_fpds(uint8_t state);
void STM32FXXXPWR_cr_dbp(uint8_t state);
void STM32FXXXPWR_cr_pls(uint8_t value);
uint8_t STM32FXXXPWR_cr_get_pls(void);
void STM32FXXXPWR_cr_pvde(uint8_t state);
void STM32FXXXPWR_cr_clear_csbf(void);
void STM32FXXXPWR_cr_clear_cwuf(void);
void STM32FXXXPWR_cr_pdds(uint8_t state);
void STM32FXXXPWR_cr_lpds(uint8_t state);
// CSR
uint8_t STM32FXXXPWR_udrdy(void);
void STM32FXXXPWR_csr_clear_udrdy(void);
uint8_t STM32FXXXPWR_csr_odswrdy(void);
uint8_t STM32FXXXPWR_csr_odrdy(void);
uint8_t STM32FXXXPWR_csr_vosrdy(void);
void STM32FXXXPWR_csr_bre(uint8_t state);
void STM32FXXXPWR_csr_ewup1(uint8_t state);
void STM32FXXXPWR_csr_ewup2(uint8_t state);
uint8_t STM32FXXXPWR_csr_brr(void);
uint8_t STM32FXXXPWR_csr_pvdo(void);
uint8_t STM32FXXXPWR_csr_sbf(void);
uint8_t STM32FXXXPWR_csr_wuf(void);

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

