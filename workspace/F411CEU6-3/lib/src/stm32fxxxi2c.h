/******************************************************************************
	STM32 XXX I2C
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     04102024
Comment:

*******************************************************************************/
#ifndef _STM32FXXXI2C_H_
	#define _STM32FXXXI2C_H_

/*** Library ***/
#include "stm32f411ceu6.h"
/******/
//#define I2C_SCL_CLOCK 100000UL
#define I2C_ACK 1
#define I2C_NACK 0
/*** I2C 1..3 Handler TypeDef ***/
// I2C -> I2C1,2,3
typedef struct
{
	/*** Clock and Nvic ***/
	void (*clock)(uint8_t state);
	void (*evnvic)(uint8_t state);
	void (*ernvic)(uint8_t state);
	void (*scl_clock)(uint32_t sclclock);
	/*** Other ***/
	void (*start)(void);
	void (*connect)(uint16_t address, uint8_t rw);
	void (*master_write)(uint8_t data);
	uint8_t (*master_read)(uint8_t ack_nack);
	void (*stop)(void);
	uint8_t (*status)(void);
}STM32FXXX_I2C1_Handler, STM32FXXX_I2C2_Handler, STM32FXXX_I2C3_Handler;

/*** I2C Procedure and Function Declarations ***/
STM32FXXX_I2C1_Handler* i2c1(void);
STM32FXXX_I2C2_Handler* i2c2(void);
STM32FXXX_I2C3_Handler* i2c3(void);

#endif

/*** EOF ***/

