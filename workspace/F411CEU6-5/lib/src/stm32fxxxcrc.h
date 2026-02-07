/******************************************************************************
	STM32 XXX CRC
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     19062023
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXCRC_H_
	#define _STM32FXXXCRC_H_

/*** Library ***/
#include "stm32f411ceu6.h"

/*** CRC TypeDef ***/
typedef const struct
{
	/*** Bit Mapping ***/
	void (*dr)(uint32_t value);
	uint32_t (*get_dr)(void);
	void (*idr)(uint8_t value);
	uint8_t (*get_idr)(void);
	void (*reset)(void);
	/*** Clock and Nvic ***/
	void (*clock)(uint8_t state);

}STM32FXXX_CRC_Handler;

STM32FXXX_CRC_Handler* crc(void);

#endif
/*** EOF ***/



