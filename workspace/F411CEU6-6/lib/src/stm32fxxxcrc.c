/******************************************************************************
	STM32 XXX CRC
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     19062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxcrc.h"

/*** File Procedure & Function Header ***/
/*** CRC Bit Mapping ***/
void CRC_dr(uint32_t value)
{
	CRC->DR = value;
}
uint32_t CRC_get_dr(void)
{
	return CRC->DR;
}
void CRC_idr(uint8_t value)
{
	CRC->IDR = value;
}
uint8_t CRC_get_idr(void)
{
	return CRC->IDR;
}
void CRC_reset(void)
{
	CRC->CR = 1;
}
void CRC_clock(uint8_t state)
{
	if(state){ RCC->AHB1ENR |= (1 << RCC_AHB1ENR_CRCEN_Pos); } else{ RCC->AHB1ENR &= ~(1 << RCC_AHB1ENR_CRCEN_Pos); }
}
/*** INIC Procedure & Function Definition ***/
static STM32FXXX_CRC_Handler stm32fxxx_crc_setup = {
	/***CRC Bit Mapping Link***/
	.dr = CRC_dr,
	.get_dr = CRC_get_dr,
	.idr = CRC_idr,
	.get_idr = CRC_get_idr,
	.reset = CRC_reset,
	.clock = CRC_clock,
	.dev = dev
};

STM32FXXX_CRC_Handler* crc(void){ return (STM32FXXX_CRC_Handler*) &stm32fxxx_crc_setup; }

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

/*** EOF ***/

