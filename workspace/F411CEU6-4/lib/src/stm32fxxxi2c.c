/******************************************************************************
	STM32 XXX I2C
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
*******************************************************************************/
#include "stm32fxxxi2c.h"
#include "stm32fxxxnvic.h"

/*** Define and Macro ***/
#define START_TIME_OUT 1000

/*** I2C Procedure & Function Definition ***/
// COMMON
void I2C_SclClock(I2C_TypeDef* instance, uint32_t sclclock) {
    // Software reset
    instance->CR1 |= I2C_CR1_SWRST;  // Set SWRST bit
    instance->CR1 &= ~I2C_CR1_SWRST; // Clear SWRST bit to release the reset
    // Set SCL frequency
    uint32_t pclk1 = get_pclk1(); // Get APB1 clock frequency in Hz
    uint32_t freq = pclk1 / 1000000; // Frequency in MHz
    instance->CR2 &= ~I2C_CR2_FREQ; // Clear the FREQ bits
    instance->CR2 |= (freq & I2C_CR2_FREQ); // Set the FREQ field in CR2
    // Set CCR for the clock control register
    uint32_t ccr_value = pclk1 / (2 * sclclock); // Calculate CCR value
    instance->CCR = (ccr_value & I2C_CCR_CCR); // Set CCR, ensure it fits in the register
    // Set TRISE (maximum rise time in ns)
    instance->TRISE = (sclclock / 1000000) + 1; // TRISE calculation
    // Enable I2C peripheral
    instance->CR1 |= I2C_CR1_PE; // Set PE bit to enable I2C
}
static inline void I2C_EnableEventInterrupt(I2C_TypeDef *I2Cx)
{
    /* Enable the event interrupt (SB, ADDR, TXE, RXNE, STOPF) */
    I2Cx->CR2 |= I2C_CR2_ITEVTEN;
}

static inline void I2C_EnableErrorInterrupt(I2C_TypeDef *I2Cx)
{
    /* Enable error interrupts (BERR, ARLO, OVR) */
    I2Cx->CR2 |= I2C_CR2_ITERREN;
}
static inline uint8_t _wait_flag(volatile uint32_t *reg, uint32_t mask, volatile uint32_t timeout) {
    while(!(*reg & mask) && timeout--);
    return timeout > 0;
}

/*** I2C1 ***/
void I2C1_Clock( uint8_t state ) {
    if(state){
        set_reg(&RCC->APB1ENR, RCC_APB1ENR_I2C1EN);
    } else {
        clear_reg(&RCC->APB1ENR, RCC_APB1ENR_I2C1EN);
    }
}
void I2C1_EvNvic( uint8_t state ){
    if(state){
        set_bit_block(NVIC->ISER, 1, I2C1_EV_IRQn, 1);
        //NVIC_EnableIRQ(I2C1_EV_IRQn);  // Direct NVIC API for enabling interrupts
    } else {
        set_bit_block(NVIC->ICER, 1, I2C1_EV_IRQn, 0);
        //NVIC_DisableIRQ(I2C1_EV_IRQn);  // Direct NVIC API for disabling interrupts
    }
}
void I2C1_ErNvic( uint8_t state ) {
    if(state){
        set_bit_block(NVIC->ISER, 1, I2C1_ER_IRQn, 1);
    } else {
        set_bit_block(NVIC->ICER, 1, I2C1_ER_IRQn, 0);
    }
}
void I2C1_SclClock(uint32_t sclclock){I2C_SclClock(I2C1, sclclock);}
/*** I2C1 RUN ***/
void I2C1_Start(void) {
	volatile uint32_t time_out = 0;
	I2C1->CR1 |= I2C_CR1_START; // Generate start condition
	for ( time_out = START_TIME_OUT; !(I2C1->SR1 & I2C_SR1_SB) && time_out; time_out-- ); // Wait for start condition
}
void I2C1_Connect(uint16_t address, uint8_t rw) {
	if (rw) {
		address |= 1; // Read
	} else {
		address &= ~1; // Write
	}
	I2C1->DR = address; // Send address
	while (!(I2C1->SR1 & I2C_SR1_ADDR)); // Wait for address sent
	(void)I2C1->SR2; // Clear ADDR flag
}
void I2C1_Master_Write(uint8_t data) {
	I2C1->DR = data; // Send data
	while (!(I2C1->SR1 & I2C_SR1_TXE)); // Wait for transmit data register empty
}
uint8_t I2C1_Master_Read(uint8_t ack_nack) {
	if (ack_nack) {
		I2C1->CR1 |= I2C_CR1_ACK; // Send ACK
		} else {
			I2C1->CR1 &= ~I2C_CR1_ACK; // Send NACK
	}
	while (!(I2C1->SR1 & I2C_SR1_RXNE)); // Wait for data received
	return I2C1->DR; // Return received data
}
void I2C1_Stop(void) {
	volatile uint32_t time_out = 0;
	I2C1->CR1 |= I2C_CR1_STOP; // Generate stop condition
	for ( time_out = 200; (I2C1->CR1 & I2C_CR1_STOP) && time_out; time_out-- ); // Wait for stop condition to be generated
}
uint8_t I2C1_Status(void) {
	return I2C1->SR1; // Return status register 1
}
/*** I2C2 ***/
void I2C2_Clock( uint8_t state ){
    if(state){
        set_reg(&RCC->APB1ENR, RCC_APB1ENR_I2C2EN);
    } else {
        clear_reg(&RCC->APB1ENR, RCC_APB1ENR_I2C2EN);
    }
}
void I2C2_EvNvic( uint8_t state ){
    if(state){
        set_bit_block(NVIC->ISER, 1, I2C2_EV_IRQn, 1);
    } else {
        set_bit_block(NVIC->ICER, 1, I2C2_EV_IRQn, 0);
    }
}
void I2C2_ErNvic( uint8_t state ){
    if(state){
        set_bit_block(NVIC->ISER, 1, I2C2_ER_IRQn, 1);
    } else {
        set_bit_block(NVIC->ICER, 1, I2C2_ER_IRQn, 0);
    }
}
void I2C2_SclClock(uint32_t sclclock){I2C_SclClock(I2C2, sclclock);}
/*** I2C2 RUN ***/
void I2C2_Start(void) {
	I2C2->CR1 |= I2C_CR1_START; // Generate start condition
	while (!(I2C2->SR1 & I2C_SR1_SB)); // Wait for start condition
}
void I2C2_Connect(uint16_t address, uint8_t rw) {
	if (rw) {
		address |= 1; // Read
		} else {
		address &= ~1; // Write
	}
	I2C2->DR = address; // Send address
	while (!(I2C2->SR1 & I2C_SR1_ADDR)); // Wait for address sent
	(void)I2C2->SR2; // Clear ADDR flag
}
void I2C2_Master_Write(uint8_t data) {
	I2C2->DR = data; // Send data
	while (!(I2C2->SR1 & I2C_SR1_TXE)); // Wait for transmit data register empty
}
uint8_t I2C2_Master_Read(uint8_t ack_nack) {
	if (ack_nack) {
		I2C2->CR1 |= I2C_CR1_ACK; // Send ACK
		} else {
			I2C2->CR1 &= ~I2C_CR1_ACK; // Send NACK
	}
	while (!(I2C2->SR1 & I2C_SR1_RXNE)); // Wait for data received
	return I2C2->DR; // Return received data
}
void I2C2_Stop(void) {
	volatile uint32_t time_out = 0;
	I2C2->CR1 |= I2C_CR1_STOP; // Generate stop condition
	for ( time_out = 200; (I2C2->CR1 & I2C_CR1_STOP) && time_out; time_out-- ); // Wait for stop condition to be generated
}
uint8_t I2C2_Status(void) {
	return I2C2->SR1; // Return status register 1
}
/*** I2C3 ***/
void I2C3_Clock( uint8_t state ){
    if(state){
        set_reg(&RCC->APB1ENR, RCC_APB1ENR_I2C3EN);
    } else {
        clear_reg(&RCC->APB1ENR, RCC_APB1ENR_I2C3EN);
    }
}
void I2C3_EvNvic( uint8_t state ){
    if(state){
        set_bit_block(NVIC->ISER, 1, I2C3_EV_IRQn, 1);
    } else {
        set_bit_block(NVIC->ICER, 1, I2C3_EV_IRQn, 0);
    }
}
void I2C3_ErNvic( uint8_t state ){
    if(state){
        set_bit_block(NVIC->ISER, 1, I2C3_ER_IRQn, 1);
    } else {
        set_bit_block(NVIC->ICER, 1, I2C3_ER_IRQn, 0);
    }
}
void I2C3_SclClock(uint32_t sclclock){I2C_SclClock(I2C3, sclclock);}
/*** I2C3 RUN ***/
void I2C3_Start(void) {
	I2C3->CR1 |= I2C_CR1_START; // Generate start condition
	while (!(I2C3->SR1 & I2C_SR1_SB)); // Wait for start condition
}
void I2C3_Connect(uint16_t address, uint8_t rw) {
	if (rw) {
		address |= 1; // Read
		} else {
		address &= ~1; // Write
	}
	I2C3->DR = address; // Send address
	while (!(I2C3->SR1 & I2C_SR1_ADDR)); // Wait for address sent
	(void)I2C3->SR2; // Clear ADDR flag
}
void I2C3_Master_Write(uint8_t data) {
	I2C3->DR = data; // Send data
	while (!(I2C3->SR1 & I2C_SR1_TXE)); // Wait for transmit data register empty
}
uint8_t I2C3_Master_Read(uint8_t ack_nack) {
	if (ack_nack) {
		I2C3->CR1 |= I2C_CR1_ACK; // Send ACK
		} else {
			I2C3->CR1 &= ~I2C_CR1_ACK; // Send NACK
	}
	while (!(I2C3->SR1 & I2C_SR1_RXNE)); // Wait for data received
	return I2C3->DR; // Return received data
}
void I2C3_Stop(void) {
	volatile uint32_t time_out = 0;
	I2C3->CR1 |= I2C_CR1_STOP; // Generate stop condition
	for ( time_out = 200; (I2C3->CR1 & I2C_CR1_STOP) && time_out; time_out-- ); // Wait for stop condition to be generated
}
uint8_t I2C3_Status(void) {
	return I2C3->SR1; // Return status register 1
}
/**************************************************************************************************/
/*** I2C1 INIC Handler ***/
static STM32FXXX_I2C_Callback I2C1_callback_setup = {0};

static STM32FXXX_I2C1_Handler stm32fxxx_i2c1_setup = {
	/*** Clock and Nvic ***/
	.clock = I2C1_Clock,
	.evnvic = I2C1_EvNvic,
	.ernvic = I2C1_ErNvic,
	.scl_clock = I2C1_SclClock,
	/*** Other ***/
	.start = I2C1_Start,
	.connect = I2C1_Connect,
	.master_write = I2C1_Master_Write,
	.master_read = I2C1_Master_Read,
	.stop = I2C1_Stop,
	.status = I2C1_Status,
	.callback = &I2C1_callback_setup,

#if defined(STM32F411CEU6_H)
	.dev = dev
#endif
};

STM32FXXX_I2C1_Handler*  i2c1(void){ return (STM32FXXX_I2C1_Handler*) &stm32fxxx_i2c1_setup; }

/*** IRQ ***/
void I2C1_EV_IRQHandler(void)
{
	STM32FXXX_I2C_Callback* cb = i2c1()->callback;
	uint32_t sr1 = I2C1->SR1;
	uint32_t sr2 = I2C1->SR2; // Read SR2 to clear some flags

	if (sr1 & I2C_SR1_SB) {
		if (cb->start_detected)
			cb->start_detected();
	}

	if (sr1 & I2C_SR1_ADDR) {
		if (cb->addr_matched)
			cb->addr_matched();
		(void)I2C1->SR2; // Clear ADDR
	}

	if (sr1 & I2C_SR1_TXE) {
		if (cb->tx_complete)
			cb->tx_complete();
	}

	if (sr1 & I2C_SR1_RXNE) {
		if (cb->rx_complete)
			cb->rx_complete();
	}

	if (sr1 & I2C_SR1_STOPF) {
		if (cb->stop_detected)
			cb->stop_detected();
		I2C1->CR1 |= I2C_CR1_PE; // Clear STOPF
	}

	if (cb->event)
		cb->event();
	(void)sr2;
}

void I2C1_ER_IRQHandler(void)
{
	STM32FXXX_I2C_Callback* cb = i2c1()->callback;
	uint32_t sr1 = I2C1->SR1;

	if (sr1 & I2C_SR1_BERR) {
		I2C1->SR1 &= ~I2C_SR1_BERR;
		if (cb->bus_error)
			cb->bus_error();
	}

	if (sr1 & I2C_SR1_ARLO) {
		I2C1->SR1 &= ~I2C_SR1_ARLO;
		if (cb->arb_lost)
			cb->arb_lost();
	}

	if (sr1 & I2C_SR1_OVR) {
		I2C1->SR1 &= ~I2C_SR1_OVR;
		if (cb->ovr_error)
			cb->ovr_error();
	}

	if (cb->error)
		cb->error();
}

/*** I2C2 INIC Handler ***/
static STM32FXXX_I2C_Callback I2C2_callback_setup = {0};

static STM32FXXX_I2C2_Handler stm32fxxx_i2c2_setup = {
	/*** Clock and Nvic ***/
	.clock = I2C2_Clock,
	.evnvic = I2C2_EvNvic,
	.ernvic = I2C2_ErNvic,
	.scl_clock = I2C2_SclClock,
	/*** Other ***/
	.start = I2C2_Start,
	.connect = I2C2_Connect,
	.master_write = I2C2_Master_Write,
	.master_read = I2C2_Master_Read,
	.stop = I2C2_Stop,
	.status = I2C2_Status,
	.callback = &I2C2_callback_setup,

#if defined(STM32F411CEU6_H)
	.dev = dev
#endif
};

STM32FXXX_I2C2_Handler*  i2c2(void){ return (STM32FXXX_I2C2_Handler*) &stm32fxxx_i2c2_setup; }

/*** IRQ ***/
void I2C2_EV_IRQHandler(void)
{
	STM32FXXX_I2C_Callback* cb = i2c2()->callback;
	uint32_t sr1 = I2C1->SR1;
	uint32_t sr2 = I2C1->SR2; // Read SR2 to clear some flags

	if (sr1 & I2C_SR1_SB) {
		if (cb->start_detected)
			cb->start_detected();
	}

	if (sr1 & I2C_SR1_ADDR) {
		if (cb->addr_matched)
			cb->addr_matched();
		(void)I2C1->SR2; // Clear ADDR
	}

	if (sr1 & I2C_SR1_TXE) {
		if (cb->tx_complete)
			cb->tx_complete();
	}

	if (sr1 & I2C_SR1_RXNE) {
		if (cb->rx_complete)
			cb->rx_complete();
	}

	if (sr1 & I2C_SR1_STOPF) {
		if (cb->stop_detected)
			cb->stop_detected();
		I2C1->CR1 |= I2C_CR1_PE; // Clear STOPF
	}

	if (cb->event)
		cb->event();
	(void)sr2;
}

void I2C2_ER_IRQHandler(void)
{
	STM32FXXX_I2C_Callback* cb = i2c2()->callback;
	uint32_t sr1 = I2C1->SR1;

	if (sr1 & I2C_SR1_BERR) {
		I2C1->SR1 &= ~I2C_SR1_BERR;
		if (cb->bus_error)
			cb->bus_error();
	}

	if (sr1 & I2C_SR1_ARLO) {
		I2C1->SR1 &= ~I2C_SR1_ARLO;
		if (cb->arb_lost)
			cb->arb_lost();
	}

	if (sr1 & I2C_SR1_OVR) {
		I2C1->SR1 &= ~I2C_SR1_OVR;
		if (cb->ovr_error)
			cb->ovr_error();
	}

	if (cb->error)
		cb->error();
}

/*** I2C3 INIC Handler ***/
static STM32FXXX_I2C_Callback I2C3_callback_setup = {0};

static STM32FXXX_I2C3_Handler stm32fxxx_i2c3_setup = {
	/*** Clock and Nvic ***/
	.clock = I2C3_Clock,
	.evnvic = I2C3_EvNvic,
	.ernvic = I2C3_ErNvic,
	.scl_clock = I2C3_SclClock,
	/*** Other ***/
	.start = I2C3_Start,
	.connect = I2C3_Connect,
	.master_write = I2C3_Master_Write,
	.master_read = I2C3_Master_Read,
	.stop = I2C3_Stop,
	.status = I2C3_Status,
	.callback = &I2C3_callback_setup,

#if defined(STM32F411CEU6_H)
	.dev = dev
#endif
};

STM32FXXX_I2C3_Handler*  i2c3(void){ return (STM32FXXX_I2C3_Handler*) &stm32fxxx_i2c3_setup; }

/*** IRQ ***/
void I2C3_EV_IRQHandler(void)
{
	STM32FXXX_I2C_Callback* cb = i2c3()->callback;
	uint32_t sr1 = I2C1->SR1;
	uint32_t sr2 = I2C1->SR2; // Read SR2 to clear some flags

	if (sr1 & I2C_SR1_SB) {
		if (cb->start_detected)
			cb->start_detected();
	}

	if (sr1 & I2C_SR1_ADDR) {
		if (cb->addr_matched)
			cb->addr_matched();
		(void)I2C1->SR2; // Clear ADDR
	}

	if (sr1 & I2C_SR1_TXE) {
		if (cb->tx_complete)
			cb->tx_complete();
	}

	if (sr1 & I2C_SR1_RXNE) {
		if (cb->rx_complete)
			cb->rx_complete();
	}

	if (sr1 & I2C_SR1_STOPF) {
		if (cb->stop_detected)
			cb->stop_detected();
		I2C1->CR1 |= I2C_CR1_PE; // Clear STOPF
	}

	if (cb->event)
		cb->event();
	(void)sr2;
}

void I2C3_ER_IRQHandler(void)
{
	STM32FXXX_I2C_Callback* cb = i2c3()->callback;
	uint32_t sr1 = I2C1->SR1;

	if (sr1 & I2C_SR1_BERR) {
		I2C1->SR1 &= ~I2C_SR1_BERR;
		if (cb->bus_error)
			cb->bus_error();
	}

	if (sr1 & I2C_SR1_ARLO) {
		I2C1->SR1 &= ~I2C_SR1_ARLO;
		if (cb->arb_lost)
			cb->arb_lost();
	}

	if (sr1 & I2C_SR1_OVR) {
		I2C1->SR1 &= ~I2C_SR1_OVR;
		if (cb->ovr_error)
			cb->ovr_error();
	}

	if (cb->error)
		cb->error();
}

/*** EOF ***/

