/******************************************************************************
	STM32 XXX SRAM
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     19062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxsram.h"

/*** SRAM Procedure & Function Definition ***/
void SRAM_Access(void)
{
	volatile uint32_t sram_time_out;
	// RM0390 pg 94
	// SRAM access
	// 0 - Power Up SRAM
	PWR->CSR |= (1 << PWR_CSR_BRE_Pos); // BRE: Backup regulator enable
	// Check ready flag Bit 3 BRR: Backup regulator ready
	for( sram_time_out = 100; !(PWR->CSR & (1 << PWR_CSR_BRR_Pos)) && sram_time_out; sram_time_out-- ); // BRR: Backup regulator ready

	// 1 - Enable the power interface clock by setting the PWREN bits in the RCC_APB1ENR
	RCC->APB1ENR |= (1 << RCC_APB1ENR_PWREN_Pos); // Power interface clock enable
	//RCC->APB1ENR |= ((1 << 11) | (1 << 28));

	// 2 - Set the DBP bit in the PWR power control register (PWR_CR)
	PWR->CR |= (1 << PWR_CR_DBP_Pos); // Disable backup domain write protection

	// 3 - Enable the backup SRAM clock by setting BKPSRAMEN bit in the RCC_AHB1ENR
	RCC->AHB1LPENR |= (1 << RCC_AHB1LPENR_SRAM1LPEN_Pos); // BKPSRAMEN: Backup SRAM interface clock enable
}

/*** SRAM Bit Mapping Definition ***/

/*** INIC Procedure & Function Definition ***/
static STM32FXXX_SRAM_Handler stm32fxxx_sram_setup = {
	.access = SRAM_Access,
	.dev = dev
};

STM32FXXX_SRAM_Handler* sram(void){ return (STM32FXXX_SRAM_Handler*) &stm32fxxx_sram_setup; }

/*** EOF ***/



