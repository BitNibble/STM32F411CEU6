/******************************************************************************
	STM32 XXX USART2
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     24022024
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxusart2.h"
#include "stm32fxxxnvic.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

/*** File Variable ***/
// Buffer for received and transmit data
static char usart2_rx_buffer[USART2_RX_BUFFER_SIZE] = {0};
volatile uint16_t usart2_rx_index = 0;
static char usart2_tx_buffer[USART2_TX_BUFFER_SIZE] = {0};
volatile uint16_t usart2_tx_index = 0;
const uint16_t usart2_rx_buffer_size = (USART2_RX_BUFFER_SIZE - 1);
const uint16_t usart2_tx_buffer_size = (USART2_TX_BUFFER_SIZE - 1);
static uint8_t usart2_flag = 0;
/*** USART Procedure & Function Definition ***/
/*** USART2 ***/
void USART2_Clock( uint8_t state )
{
	if(state){ RCC->APB1ENR |= (1 << RCC_APB1ENR_USART2EN_Pos); }else{ RCC->APB1ENR &= ~(1 << RCC_APB1ENR_USART2EN_Pos); }
}
void USART2_Nvic( uint8_t state )
{
	if(state){ set_bit_block(NVIC->ISER, 1, USART2_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, USART2_IRQn, 1); }
}
void USART2_WordLength(uint8_t wordlength) {
    // Clear the M bit to reset word length
	USART2->CR1 &= ~(1 << USART_CR1_M_Pos);

    if (wordlength == 9) {
    	USART2->CR1 |= (1 << USART_CR1_M_Pos); // Set M bit for 9-bit word length
    }
    // If wordlength is 8 or any other value, do nothing (remains 8-bit)
}
void USART2_StopBits(double stopbits) {
    // Reset stop bits configuration
	USART2->CR2 &= (uint32_t) ~(USART_CR2_STOP_1 | USART_CR2_STOP_0);

    if (fabs(stopbits - 0.5) < 0.00001) { // 0.5 Stop bits
    	USART2->CR2 |= USART_CR2_STOP_0; // Set bit 12
    } else if (fabs(stopbits - 1.0) < 0.00001) { // 1 Stop bit
        // No additional bits set (already cleared)
    } else if (fabs(stopbits - 1.5) < 0.00001) { // 1.5 Stop bits
    	USART2->CR2 |= (USART_CR2_STOP_1 | USART_CR2_STOP_0); // Set both bits
    } else if (fabs(stopbits - 2.0) < 0.00001) { // 2 Stop bits
    	USART2->CR2 |= USART_CR2_STOP_1; // Set bit 13
    }
}
void USART2_SamplingMode(uint8_t samplingmode, uint32_t baudrate)
{
    // 1) Configure OVER8 bit
    if (samplingmode == 8) {
    	USART2->CR1 |= (1 << 15);   // OVER8 = 1
    } else {
    	USART2->CR1 &= ~(1 << 15);  // OVER8 = 0 (16x)
        samplingmode = 16;          // normalize
    }

    // 2) Select proper peripheral clock
    uint32_t pclk = get_pclk1();
    //if (usart == USART1 || usart == USART6)
        //pclk = get_pclk2();
    //else
        //pclk = get_pclk1();

    // 3) Compute USARTDIV
    double usartdiv = (double)pclk / (samplingmode * baudrate);

    uint32_t mantissa = (uint32_t)usartdiv;
    double fractionf = usartdiv - mantissa;

    // 4) Build BRR according to oversampling
    uint32_t brr = 0;
    if (samplingmode == 16) {
        uint32_t fraction = (uint32_t)round(fractionf * 16);
        if (fraction == 16) { mantissa++; fraction = 0; }
        brr = (mantissa << 4) | (fraction & 0xF);
    } else { // samplingmode == 8
        uint32_t fraction = (uint32_t)round(fractionf * 8);
        if (fraction == 8) { mantissa++; fraction = 0; }
        brr = (mantissa << 4) | ((fraction & 0x7) << 1);
    }

    // 5) Write BRR
    USART2->BRR = brr;
}
void USART2_Tx_Enable( uint8_t state ) {
	if( state )
		USART2->CR1 |= USART_CR1_TE;
	else
		USART2->CR1 &= ~USART_CR1_TE;
}
void USART2_Rx_Enable( uint8_t state ) {
	if( state )
		USART2->CR1 |= USART_CR1_RE;
	else
		USART2->CR1 &= ~USART_CR1_RE;
}
void USART2_Tx_EInterrupt( uint8_t state ) {
	if( state )
		USART2->CR1 |= USART_CR1_TXEIE;
	else
		USART2->CR1 &= ~USART_CR1_TXEIE;
}
void USART2_Tx_CInterrupt( uint8_t state ) {
	if( state )
		USART2->CR1 |= USART_CR1_TCIE;
	else
		USART2->CR1 &= ~USART_CR1_TCIE;
}
void USART2_Rx_NEInterrupt( uint8_t state) {
	if ( state )
		USART2->CR1 |= USART_CR1_RXNEIE;
	else
		USART2->CR1 &= ~USART_CR1_RXNEIE;
}
/*****************************************************************************/
uint32_t is_USART2_CR1_PEIE(void){
	return USART2->CR1 & USART_CR1_PEIE;
}
uint32_t is_USART2_CR1_TXEIE(void){
	return USART2->CR1 & USART_CR1_TXEIE;
}
uint32_t is_USART2_CR1_TCIE(void){
	return USART2->CR1 & USART_CR1_TCIE;
}
uint32_t is_USART2_CR1_RXNEIE(void){
	return USART2->CR1 & USART_CR1_RXNEIE;
}
uint32_t is_USART2_CR1_IDLEIE(void){
	return USART2->CR1 & USART_CR1_IDLEIE;
}
/*****************************************************************************/
uint32_t is_USART2_SR_CTS(void){
	return USART2->SR & USART_SR_CTS;
}
uint32_t is_USART2_SR_LBD(void){
	return USART2->SR & USART_SR_LBD;
}
uint32_t is_USART2_SR_TXE(void){
	return USART2->SR & USART_SR_TXE;
}
uint32_t is_USART2_SR_TC(void){
	return USART2->SR & USART_SR_TC;
}
uint32_t is_USART2_SR_RXNE(void){
	return USART2->SR & USART_SR_RXNE;
}
uint32_t is_USART2_SR_IDLE(void){
	return USART2->SR & USART_SR_IDLE;
}
uint32_t is_USART2_SR_ORE(void){
	return USART2->SR & USART_SR_ORE;
}
uint32_t is_USART2_SR_NE(void){
	return USART2->SR & USART_SR_NE;
}
uint32_t is_USART2_SR_FE(void){
	return USART2->SR & USART_SR_FE;
}
uint32_t is_USART2_SR_PE(void){
	return USART2->SR & USART_SR_PE;
}
/*****************************************************************************/
void USART2_PutChar(char c) {
    USART2->DR = c;	// Send the character
}
char USART2_GetChar(void) {
    char ret = USART2->DR;	// Return the character
    return ret;
}
void USART2_TransmitChar(char c) {
    while (!(USART2->SR & USART_SR_TXE)); // Wait until TX is empty
    USART2_PutChar(c);	// Send the character
    USART2->CR1 &= ~USART_CR1_TXEIE;
}
char USART2_ReceiveChar(void) {
    while (!(USART2->SR & USART_SR_RXNE)); // Wait until RX is ready
    return USART2_GetChar();	// Return the received character
    USART2->CR1 &= ~USART_CR1_RXNEIE;
}
void USART2_RxFlush(void) {
	usart2_rx_index = 0;
	usart2_rx_buffer[0] = 0;
}
void USART2_RxPurge(void) {
	usart2_rx_index = 0;
	memset( usart2_rx_buffer, 0, USART2_RX_BUFFER_SIZE );
}
void USART2_TxFlush(void) {
	usart2_tx_index = 0;
	usart2_tx_buffer[0] = 0;
	//memset( usart2_tx_buffer, 0, USART2_TX_BUFFER_SIZE );
}
void USART2_TransmitString(const char *str) {
	USART2_TxFlush();
    // Copy the string into the transmit buffer
    strncpy( (char *)usart2_tx_buffer, str, usart2_tx_buffer_size ); // Ensure tx_buffer is big enough
    // Enable the TXE interrupt to start sending data
    USART2_Tx_EInterrupt(1);
}
void USART2_ReceiveString(char* oneshot, char* rx, size_t size, const char* endl) {
	const uint32_t buff_size = size - 1;
	if(usart2_flag) { memset(oneshot, 0, size); usart2_flag = 0; }
	char *ptr = usart2_rx_buffer;
	size_t ptr_length = strlen((char*)ptr);
	if( ptr_length < usart2_rx_buffer_size ) {
		size_t endl_length = strlen(endl);
		int32_t diff_length = ptr_length - endl_length;
		int32_t check;
		if( diff_length >= 0 ) {
			check = strcmp((char*)ptr + diff_length, endl);
			if( !check ) {
				strncpy(oneshot, (const char*)ptr, buff_size);
				oneshot[diff_length] = 0;
				strncpy(rx, (const char*)ptr, buff_size);
				rx[diff_length] = 0;
				usart2_flag = 0xFF;
				USART2_RxFlush( );
			}
		}
	}else { USART2_RxFlush( ); }
}
void USART2_ReceiveRxString(char* rx, size_t size, const char* endl) {
	const uint32_t buff_size = size - 1;
	char *ptr = usart2_rx_buffer;
	size_t ptr_length = strlen((char*)ptr);
	if( ptr_length < usart2_rx_buffer_size ) {
		size_t endl_length = strlen(endl);
		int32_t diff_length = ptr_length - endl_length;
		int32_t check;
		if( diff_length >= 0 ) {
			check = strcmp((char*)ptr + diff_length, endl);
			if( !check ) {
				strncpy(rx, (const char*)ptr, buff_size);
				rx[diff_length] = 0;
				USART2_RxFlush( );
			}
		}
	}else { USART2_RxFlush( ); }
}
void USART2_start(void) { USART2->CR1 |= USART_CR1_UE; }
void USART2_stop(void) { USART2->CR1 &= ~USART_CR1_UE; }

// CALLBACK
void USART2_CallBack_CTS(void){
	// Clear CTS flag by reading SR
	volatile uint8_t dummy = USART2->SR;
	(void)dummy;
	// Handle CTS change (e.g., pause/resume transmission)
}
void USART2_CallBack_LBD(void){
	// Clear LBD flag by writing a 0
	USART2->SR &= ~USART_SR_LBD;
	// Handle LIN break detection (e.g., reset communication)
}
void USART2_CallBack_TXE(void){
	if(usart2_tx_buffer[usart2_tx_index]) {
		USART2_PutChar( usart2_tx_buffer[usart2_tx_index++] );
	}else{
		USART2->CR1 &= ~USART_CR1_TXEIE;
	}
}
void USART2_CallBack_TC(void){
	// Transmission complete
	USART2->DR = 0; // Write to DR to clear TC flag
	// Optionally disable TC interrupt if no further action is needed
	USART2->CR1 &= ~USART_CR1_TCIE;
}
void USART2_CallBack_RXNE(void){
	char rx = USART2_GetChar();
	// Check if the RXNE (Receive Not Empty) flag is set
	if( rx ) {
		if (usart2_rx_index < usart2_rx_buffer_size) {
			usart2_rx_buffer[usart2_rx_index++] = rx;
			usart2_rx_buffer[usart2_rx_index] = 0;
		}
	}
}
void USART2_CallBack_IDLE(void){
	// Clear IDLE flag by reading SR and DR
	volatile uint8_t dummy = USART2_GetChar();
	(void)dummy;  // Prevent unused variable warning
	// Handle idle condition (e.g., mark end of transmission)
}
void USART2_CallBack_ORE(void){
	// Overrun error: Clear ORE by reading DR
	volatile uint8_t dummy = USART2_GetChar();
	(void)dummy;
	// Handle overrun error (e.g., discard data)
}

/*** USART2 INIC Procedure & Function Definition ***/
static STM32FXXX_USART2_CallBack USART2_callback_setup = {
		.cts = USART2_CallBack_CTS,
		.lbd = USART2_CallBack_LBD,
		.txe = USART2_CallBack_TXE,
		.tc = USART2_CallBack_TC,
		.rxne = USART2_CallBack_RXNE,
		.idle = USART2_CallBack_IDLE,
		.ore = USART2_CallBack_ORE,
		.ne = NULL,
		.fe = NULL,
		.pe = NULL
};

static STM32FXXX_USART2_Handler stm32fxxx_usart2_setup = {
	// V-table
	.clock = USART2_Clock,
	.nvic = USART2_Nvic,
	// Config
	.wordlength = USART2_WordLength,
	.stopbits = USART2_StopBits,
	.samplingmode = USART2_SamplingMode,
	.is_tx_complete = is_USART2_SR_TC,
	.is_rx_idle = is_USART2_SR_IDLE,
	// Enable
	.tx = USART2_Tx_Enable,
	.rx = USART2_Rx_Enable,
	// Interrupt
	.tx_einterrupt = USART2_Tx_EInterrupt,
	.rx_neinterrupt = USART2_Rx_NEInterrupt,
	// Control
	.transmit_char = USART2_TransmitChar,
	.receive_char = USART2_ReceiveChar,
	.rx_flush = USART2_RxFlush,
	.rx_purge = USART2_RxPurge,
	.transmit_string = USART2_TransmitString,
	.receive_string = USART2_ReceiveString,
	.receive_rxstring = USART2_ReceiveRxString,
	.rxbuff = usart2_rx_buffer,
	.txbuff = usart2_tx_buffer,
	.start = USART2_start,
	.stop = USART2_stop,
	// Callback
	.callback = &USART2_callback_setup,

#if defined(STM32F411CEU6_H)
	.dev = stm32f411ceu6
#endif
};

STM32FXXX_USART2_Handler*  usart2(void){ return (STM32FXXX_USART2_Handler*) &stm32fxxx_usart2_setup; }

/*** Interrupt handler for USART2 ***/
void USART2_IRQHandler(void) {
	STM32FXXX_USART2_CallBack* cb = &USART2_callback_setup;
	// Check for CTS flag (if hardware flow control is enabled)
	if (is_USART2_SR_CTS()) {
		if(cb->cts){ cb->cts(); }
	}
	// Check for LIN Break Detection (if LIN mode is enabled)
	if (is_USART2_SR_LBD()) {
		if(cb->lbd){ cb->lbd(); }
	}

	if(is_USART2_CR1_TXEIE()) {
		if(is_USART2_SR_TXE()) {
			if(cb->txe){ cb->txe(); }
		}
	}

	if(is_USART2_CR1_TCIE()) {
		// Check if the TC (Transmission Complete) flag is set
		if (is_USART2_SR_TC()) {
			if(cb->tc){ cb->tc(); }
		}
	}

	if(is_USART2_SR_RXNE()) {
		if(cb->rxne){ cb->rxne(); }
	}
    // Check for IDLE line detection
    if (is_USART2_SR_IDLE()) {
        if(cb->idle){ cb->idle(); }
    }
    // Error handling (Overrun, Noise, Framing, Parity)
    if (is_USART2_SR_ORE()) {
    	if(cb->ore){ cb->ore(); }
    }
    if (is_USART2_SR_NE()) {
    	// Noise error: Handle noise (e.g., log or recover from error)
    	USART2->SR &= ~USART_SR_NE;
    	if (cb->ne) { cb->ne(); }
    }
    if (is_USART2_SR_FE()) {
    	// Framing error: Handle framing issues (e.g., re-sync communication)
    	USART2->SR &= ~USART_SR_NE;
    	if (cb->fe) { cb->fe(); }
    }
    if (is_USART2_SR_PE()) {
    	// Parity error: Handle parity mismatch (e.g., request retransmission)
    	USART2->SR &= ~USART_SR_NE;
    	if (cb->pe) { cb->pe(); }
    }
    // Optionally reset USART or take corrective action based on error type
	/***/
    // Wakeup from STOP mode (if enabled and used)
    //if (sr & USART_SR_WU) {
        // Clear wakeup flag by writing a 0
        //USART2->SR &= ~USART_SR_WU;
        // Handle wakeup event (e.g., resume communication)
    //}
}

/*** EOF ***/

