/******************************************************************************
	STM32 XXX SRAM
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 19062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxsram.h"

/*** File Variable ***/
static STM32FXXX_SRAM stm32fxxx_sram = {0};

static uint32_t sram_time_out;

/*** SRAM Procedure & Function Definition ***/
void STM32FXXXSramAccess(void)
{
	// RM0390 pg 94
	// SRAM access
	// 0 - Power Up SRAM
	PWR->CSR |= (1 << 9); // BRE: Backup regulator enable
	// Check ready flag Bit 3 BRR: Backup regulator ready
	for( sram_time_out = 100; !(PWR->CSR & (1 << 3)) && sram_time_out; sram_time_out-- ); // BRR: Backup regulator ready

	// 1 - Enable the power interface clock by setting the PWREN bits in the RCC_APB1ENR
	RCC->APB1ENR |= (1 << 28); // Power interface clock enable
	//RCC->APB1ENR |= ((1 << 11) | (1 << 28));

	// 2 - Set the DBP bit in the PWR power control register (PWR_CR)
	PWR->CR |= (1 << 8); // Disable backup domain write protection

	// 3 - Enable the backup SRAM clock by setting BKPSRAMEN bit in the RCC_AHB1ENR
	RCC->AHB1ENR |= (1 << 18); // BKPSRAMEN: Backup SRAM interface clock enable
}

/*** SRAM Bit Mapping Definition ***/

/*** INIC Procedure & Function Definition ***/
void sram_enable(void)
{
	stm32fxxx_sram.access = STM32FXXXSramAccess;
	//return &stm32fxxx_sram;
}

STM32FXXX_SRAM* sram(void){ return (STM32FXXX_SRAM*) &stm32fxxx_sram; }

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

