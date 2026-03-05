/******************************************************************************
	STM32 XXX CRC
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 19062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxcrc.h"

#define ON 1
#define OFF 0
/***File Variable ***/
static STM32FXXX_CRC stm32fxxx_crc = {0};

/*** File Procedure & Function Header ***/
/*** CRC Bit Mapping ***/
void STM32FXXXCRC_dr(uint32_t value)
{
	CRC->DR = value;
}
uint32_t STM32FXXXCRC_get_dr(void)
{
	return CRC->DR;
}
void STM32FXXXCRC_idr(uint8_t value)
{
	CRC->IDR = value;
}
uint8_t STM32FXXXCRC_get_idr(void)
{
	return CRC->IDR;
}
void STM32FXXXCRC_reset(void)
{
	CRC->CR = 1;
}
void STM32FXXXCRC_clock(uint8_t state)
{
	if(state){ RCC->AHB1ENR |= (1 << 12); } else{ RCC->AHB1ENR &= ~(1 << 12); }
}
/*** INIC Procedure & Function Definition ***/
void crc_enable(void)
{
	STM32FXXXCRC_clock(ON);
	stm32fxxx_crc.instance = CRC;
	/***CRC Bit Mapping Link***/
	stm32fxxx_crc.dr = STM32FXXXCRC_dr;
	stm32fxxx_crc.get_dr = STM32FXXXCRC_get_dr;
	stm32fxxx_crc.idr = STM32FXXXCRC_idr;
	stm32fxxx_crc.get_idr = STM32FXXXCRC_get_idr;
	stm32fxxx_crc.reset = STM32FXXXCRC_reset;
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

