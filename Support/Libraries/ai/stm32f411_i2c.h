#ifndef _STM32F411_I2C_H_
#define _STM32F411_I2C_H_

#include "stm32f411xe.h"
#include <stdint.h>

/*** Constants & Macros ***/
#define I2C_ACK 1
#define I2C_NACK 0
#define I2C_WRITE 0
#define I2C_READ 1

// Timeout ticks
#define I2C_TIMEOUT 10000U

typedef struct {
    void (*i2c_vect)(void);
} I2C0_Callback;

typedef struct {
    I2C0_Callback callback;

    // Virtual table
    void (*start)(void);
    uint8_t (*connect)(uint8_t address, uint8_t rw);
    uint8_t (*master_write)(uint8_t data);
    uint8_t (*master_read)(uint8_t ack_nack);
    void (*stop)(void);
    uint32_t (*status)(void);

} I2C0_Handler;

/*** Handler Functions ***/
void i2c_enable(I2C_TypeDef *i2c, uint32_t timing);
I2C0_Handler* i2c(void);

#endif
