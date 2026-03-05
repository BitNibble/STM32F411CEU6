/******************************************************************************
	STM32 XXX I2C
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
*******************************************************************************/
#ifndef STM32FXXXI2C_H
	#define STM32FXXXI2C_H

/*** Library ***/
//#if defined (STM32F411xE)
	#include "stm32f411ceu6.h"
//#elif defined(STM32F446xx)
//	#include "stm32f446re.h"
//#else
//	void* dev(void){ return NULL; }
//#endif
/***********/
//#define I2C_SCL_CLOCK 100000UL
#define I2C_ACK 1
#define I2C_NACK 0

/*** IRQ ***/
typedef struct {
	void (*event)(void);           // Generic EV interrupt
	void (*error)(void);           // Generic ER interrupt
	void (*tx_complete)(void);     // TXE
	void (*rx_complete)(void);     // RXNE
	void (*stop_detected)(void);   // STOPF
	void (*start_detected)(void);  // SB
	void (*addr_matched)(void);    // ADDR
	void (*bus_error)(void);       // BERR
	void (*arb_lost)(void);        // ARLO
	void (*ovr_error)(void);       // OVR
} STM32FXXX_I2C_Callback;

/*** I2C 1..3 Handler TypeDef ***/
// I2C -> I2C1,2,3
typedef const struct
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

	/* Callback */
	STM32FXXX_I2C_Callback* callback;

#if defined(STM32F411CEU6_H)
	STM32F411CEU6_Instance* (*dev)(void);
#elif defined(STM32F446RE_H)
	STM32F446RE_Instance* (*dev)(void);
#else
	void* (*dev)(void);
#endif
}STM32FXXX_I2C1_Handler, STM32FXXX_I2C2_Handler, STM32FXXX_I2C3_Handler;

/*** I2C Procedure and Function Declarations ***/
STM32FXXX_I2C1_Handler* i2c1(void);
STM32FXXX_I2C2_Handler* i2c2(void);
STM32FXXX_I2C3_Handler* i2c3(void);

#endif

/*** EOF ***/

