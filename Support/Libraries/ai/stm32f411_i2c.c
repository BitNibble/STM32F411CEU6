#include "stm32f411_i2c.h"

/*** Internal Handler ***/
static I2C0_Handler stm32f411_i2c = {
    .callback = { .i2c_vect = NULL },
};

/*** Forward declarations ***/
static void I2C_start(void);
static uint8_t I2C_connect(uint8_t address, uint8_t rw);
static uint8_t I2C_master_write(uint8_t data);
static uint8_t I2C_master_read(uint8_t ack_nack);
static void I2C_stop(void);
static uint32_t I2C_status(void);

/*** Enable / Init ***/
void i2c_enable(I2C_TypeDef *i2c, uint32_t timing)
{
    // Enable peripheral clock
    if(i2c == I2C1) RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    else if(i2c == I2C2) RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;

    // Reset I2C
    i2c->CR1 = I2C_CR1_SWRST;
    i2c->CR1 = 0;

    // Timing register (assumes 100kHz)
    i2c->CR2 = 16; // APB1 clock in MHz
    i2c->CCR = timing;
    i2c->TRISE = 17; // max rise time

    i2c->CR1 |= I2C_CR1_PE;

    // Attach virtual table
    stm32f411_i2c.start = I2C_start;
    stm32f411_i2c.connect = I2C_connect;
    stm32f411_i2c.master_write = I2C_master_write;
    stm32f411_i2c.master_read = I2C_master_read;
    stm32f411_i2c.stop = I2C_stop;
    stm32f411_i2c.status = I2C_status;
}

I2C0_Handler* i2c(void){ return &stm32f411_i2c; }

/*** Implementation ***/
static void I2C_start(void)
{
    I2C1->CR1 |= I2C_CR1_START;
    while(!(I2C1->SR1 & I2C_SR1_SB)); // Wait for start bit
}

static uint8_t I2C_connect(uint8_t address, uint8_t rw)
{
    I2C1->DR = (address << 1) | (rw & 0x01);
    while(!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR2; // clear ADDR flag
    return 0;
}

static uint8_t I2C_master_write(uint8_t data)
{
    I2C1->DR = data;
    while(!(I2C1->SR1 & I2C_SR1_TXE));
    return 0;
}

static uint8_t I2C_master_read(uint8_t ack_nack)
{
    if(ack_nack) I2C1->CR1 |= I2C_CR1_ACK;
    else I2C1->CR1 &= ~I2C_CR1_ACK;

    while(!(I2C1->SR1 & I2C_SR1_RXNE));
    return I2C1->DR;
}

static void I2C_stop(void)
{
    I2C1->CR1 |= I2C_CR1_STOP;
}

static uint32_t I2C_status(void)
{
    return I2C1->SR1;
}
