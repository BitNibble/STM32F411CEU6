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

/***File Variable ***/
static STM32FXXX_CRC stm32fxxx_crc = {0};

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
void crc_enable(void)
{
	CRC_clock(1);
	/***CRC Bit Mapping Link***/
	stm32fxxx_crc.dr = CRC_dr;
	stm32fxxx_crc.get_dr = CRC_get_dr;
	stm32fxxx_crc.idr = CRC_idr;
	stm32fxxx_crc.get_idr = CRC_get_idr;
	stm32fxxx_crc.reset = CRC_reset;
	//return &stm32fxxx_crc;
}

STM32FXXX_CRC* crc(void){ return (STM32FXXX_CRC*) &stm32fxxx_crc; }

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

