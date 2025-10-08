/******************************************************************************
	STM32 XXX USART1
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     24022024
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxusart1.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

/*** File Variable ***/
//static STM32FXXX_USART1 stm32fxxx_usart1 = {0};
/******/
// Buffer for received and transmit data
static char usart1_rx_buffer[USART1_RX_BUFFER_SIZE] = {0};
volatile uint16_t usart1_rx_index = 0;
static char usart1_tx_buffer[USART1_TX_BUFFER_SIZE] = {0};
volatile uint16_t usart1_tx_index = 0;
const uint16_t usart1_rx_buffer_size = (USART1_RX_BUFFER_SIZE - 1);
const uint16_t usart1_tx_buffer_size = (USART1_TX_BUFFER_SIZE - 1);
static uint8_t usart1_flag = 0;
/*** USART Procedure & Function Definition ***/
/*** USART1 ***/
void USART1_Clock( uint8_t state )
{
	if(state){ RCC->APB2ENR |= (1 << RCC_APB2ENR_USART1EN_Pos); }else{ RCC->APB2ENR &= ~(1 << RCC_APB2ENR_USART1EN_Pos); }
}
void USART1_Nvic( uint8_t state )
{
	if(state){ set_bit_block(NVIC->ISER, 1, USART1_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, USART1_IRQn, 1); }
}
void USART1_WordLength(uint8_t wordlength) {
    // Clear the M bit to reset word length
	USART1->CR1 &= ~(1 << USART_CR1_M_Pos);

    if (wordlength == 9) {
    	USART1->CR1 |= (1 << USART_CR1_M_Pos); // Set M bit for 9-bit word length
    }
    // If wordlength is 8 or any other value, do nothing (remains 8-bit)
}
void USART1_StopBits(double stopbits) {
    // Reset stop bits configuration
	USART1->CR2 &= (uint32_t) ~(USART_CR2_STOP_1 | USART_CR2_STOP_0);

    if (fabs(stopbits - 0.5) < 0.00001) { // 0.5 Stop bits
    	USART1->CR2 |= USART_CR2_STOP_0; // Set bit 12
    } else if (fabs(stopbits - 1.0) < 0.00001) { // 1 Stop bit
        // No additional bits set (already cleared)
    } else if (fabs(stopbits - 1.5) < 0.00001) { // 1.5 Stop bits
    	USART1->CR2 |= (USART_CR2_STOP_1 | USART_CR2_STOP_0); // Set both bits
    } else if (fabs(stopbits - 2.0) < 0.00001) { // 2 Stop bits
    	USART1->CR2 |= USART_CR2_STOP_1; // Set bit 13
    }
}
void USART1_SamplingMode(uint8_t samplingmode, uint32_t baudrate)
{
    // 1) Configure OVER8 bit
    if (samplingmode == 8) {
    	USART1->CR1 |= (1 << 15);   // OVER8 = 1
    } else {
    	USART1->CR1 &= ~(1 << 15);  // OVER8 = 0 (16x)
        samplingmode = 16;         // normalize
    }

    // 2) Select proper peripheral clock
    uint32_t pclk = get_pclk2();
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
    USART1->BRR = brr;
}
void USART1_Tx_Enable( uint8_t state ) {
	if( state )
		USART1->CR1 |= USART_CR1_TE;
	else
		USART1->CR1 &= ~USART_CR1_TE;
}
void USART1_Rx_Enable( uint8_t state ) {
	if( state )
		USART1->CR1 |= USART_CR1_RE;
	else
		USART1->CR1 &= ~USART_CR1_RE;
}
void USART1_Tx_EInterrupt( uint8_t state ) {
	if( state )
		USART1->CR1 |= USART_CR1_TXEIE;
	else
		USART1->CR1 &= ~USART_CR1_TXEIE;
}
void USART1_Tx_CInterrupt( uint8_t state ) {
	if( state )
		USART1->CR1 |= USART_CR1_TCIE;
	else
		USART1->CR1 &= ~USART_CR1_TCIE;
}
void USART1_Rx_NEInterrupt( uint8_t state) {
	if ( state )
		USART1->CR1 |= USART_CR1_RXNEIE;
	else
		USART1->CR1 &= ~USART_CR1_RXNEIE;
}
/*****************************************************************************/
uint32_t is_CR1_PEIE(void){
	return USART1->CR1 & USART_CR1_PEIE;
}
uint32_t is_CR1_TXEIE(void){
	return USART1->CR1 & USART_CR1_TXEIE;
}
uint32_t is_CR1_TCIE(void){
	return USART1->CR1 & USART_CR1_TCIE;
}
uint32_t is_CR1_RXNEIE(void){
	return USART1->CR1 & USART_CR1_RXNEIE;
}
uint32_t is_CR1_IDLEIE(void){
	return USART1->CR1 & USART_CR1_IDLEIE;
}
/*****************************************************************************/
uint32_t is_SR_CTS(void){
	return USART1->SR & USART_SR_CTS;
}
uint32_t is_SR_LBD(void){
	return USART1->SR & USART_SR_LBD;
}
uint32_t is_SR_TXE(void){
	return USART1->SR & USART_SR_TXE;
}
uint32_t is_SR_TC(void){
	return USART1->SR & USART_SR_TC;
}
uint32_t is_SR_RXNE(void){
	return USART1->SR & USART_SR_RXNE;
}
uint32_t is_SR_IDLE(void){
	return USART1->SR & USART_SR_IDLE;
}
uint32_t is_SR_ORE(void){
	return USART1->SR & USART_SR_ORE;
}
uint32_t is_SR_NE(void){
	return USART1->SR & USART_SR_NE;
}
uint32_t is_SR_FE(void){
	return USART1->SR & USART_SR_FE;
}
uint32_t is_SR_PE(void){
	return USART1->SR & USART_SR_PE;
}
/*****************************************************************************/
void USART1_PutChar(char c) {
    USART1->DR = c;	// Send the character
}
char USART1_GetChar(void) {
    char ret = USART1->DR;	// Return the character
    return ret;
}
void USART1_TransmitChar(char c) {
    while (!(USART1->SR & USART_SR_TXE)); // Wait until TX is empty
    USART1_PutChar(c);	// Send the character
    USART1->CR1 &= ~USART_CR1_TXEIE;
}
char USART1_ReceiveChar(void) {
    while (!(USART1->SR & USART_SR_RXNE)); // Wait until RX is ready
    return USART1_GetChar();	// Return the received character
    USART1->CR1 &= ~USART_CR1_RXNEIE;
}
void USART1_RxFlush(void) {
	usart1_rx_index = 0;
	usart1_rx_buffer[0] = 0;
}
void USART1_RxPurge(void) {
	usart1_rx_index = 0;
	memset( usart1_rx_buffer, 0, USART1_RX_BUFFER_SIZE );
}
void USART1_TxFlush(void) {
	usart1_tx_index = 0;
	usart1_tx_buffer[0] = 0;
	//memset( usart1_tx_buffer, 0, USART1_TX_BUFFER_SIZE );
}
void USART1_TransmitString(const char *str) {
	USART1_TxFlush();
    // Copy the string into the transmit buffer
    strncpy( (char *)usart1_tx_buffer, str, usart1_tx_buffer_size ); // Ensure tx_buffer is big enough
    // Enable the TXE interrupt to start sending data
    USART1_Tx_EInterrupt(1);
}
void USART1_ReceiveString(char* oneshot, char* rx, size_t size, const char* endl) {
	const uint32_t buff_size = size - 1;
	if(usart1_flag) { memset(oneshot, 0, size); usart1_flag = 0; }
	char *ptr = usart1_rx_buffer;
	size_t ptr_length = strlen((char*)ptr);
	if( ptr_length < usart1_rx_buffer_size ) {
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
				usart1_flag = 0xFF;
				USART1_RxFlush( );
			}
		}
	}else { USART1_RxFlush( ); }
}
void USART1_ReceiveRxString(char* rx, size_t size, const char* endl) {
	const uint32_t buff_size = size - 1;
	char *ptr = usart1_rx_buffer;
	size_t ptr_length = strlen((char*)ptr);
	if( ptr_length < usart1_rx_buffer_size ) {
		size_t endl_length = strlen(endl);
		int32_t diff_length = ptr_length - endl_length;
		int32_t check;
		if( diff_length >= 0 ) {
			check = strcmp((char*)ptr + diff_length, endl);
			if( !check ) {
				strncpy(rx, (const char*)ptr, buff_size);
				rx[diff_length] = 0;
				USART1_RxFlush( );
			}
		}
	}else { USART1_RxFlush( ); }
}
void USART1_start(void) { USART1->CR1 |= USART_CR1_UE; }
void USART1_stop(void) { USART1->CR1 &= ~USART_CR1_UE; }

// CALLBACK
void CallBack_CTS(void){
	// Clear CTS flag by reading SR
	volatile uint8_t dummy = USART1->SR;
	(void)dummy;
	// Handle CTS change (e.g., pause/resume transmission)
}
void CallBack_LBD(void){
	// Clear LBD flag by writing a 0
	USART1->SR &= ~USART_SR_LBD;
	// Handle LIN break detection (e.g., reset communication)
}
void CallBack_TXE(void){
	if(usart1_tx_buffer[usart1_tx_index]) {
		USART1_PutChar( usart1_tx_buffer[usart1_tx_index++] );
	}else{
		USART1->CR1 &= ~USART_CR1_TXEIE;
	}
}
void CallBack_TC(void){
	// Transmission complete
	USART1->DR = 0; // Write to DR to clear TC flag
	// Optionally disable TC interrupt if no further action is needed
	USART1->CR1 &= ~USART_CR1_TCIE;
}
void CallBack_RXNE(void){
	char rx = USART1_GetChar();
	// Check if the RXNE (Receive Not Empty) flag is set
	if( rx ) {
		if (usart1_rx_index < usart1_rx_buffer_size) {
			usart1_rx_buffer[usart1_rx_index++] = rx;
			usart1_rx_buffer[usart1_rx_index] = 0;
		}
	}
}
void CallBack_IDLE(void){
	// Clear IDLE flag by reading SR and DR
	volatile uint8_t dummy = USART1_GetChar();
	(void)dummy;  // Prevent unused variable warning
	// Handle idle condition (e.g., mark end of transmission)
}
void CallBack_ORE(void){
	// Overrun error: Clear ORE by reading DR
	volatile uint8_t dummy = USART1_GetChar();
	(void)dummy;
	// Handle overrun error (e.g., discard data)
}

/*** USART1 INIC Procedure & Function Definition ***/
static STM32FXXX_USART1 stm32fxxx_usart1 = {
	// V-table
	.clock = USART1_Clock,
	.nvic = USART1_Nvic,
	// Config
	.wordlength = USART1_WordLength,
	.stopbits = USART1_StopBits,
	.samplingmode = USART1_SamplingMode,
	.is_tx_complete = is_SR_TC,
	.is_rx_idle = is_SR_IDLE,
	// Enable
	.tx = USART1_Tx_Enable,
	.rx = USART1_Rx_Enable,
	// Interrupt
	.tx_einterrupt = USART1_Tx_EInterrupt,
	.rx_neinterrupt = USART1_Rx_NEInterrupt,
	// Control
	.transmit_char = USART1_TransmitChar,
	.receive_char = USART1_ReceiveChar,
	.rx_flush = USART1_RxFlush,
	.rx_purge = USART1_RxPurge,
	.transmit_string = USART1_TransmitString,
	.receive_string = USART1_ReceiveString,
	.receive_rxstring = USART1_ReceiveRxString,
	.rxbuff = usart1_rx_buffer,
	.txbuff = usart1_tx_buffer,
	.start = USART1_start,
	.stop = USART1_stop,
	// Callback
	.callback.cts = CallBack_CTS,
	.callback.lbd = CallBack_LBD,
	.callback.txe = CallBack_TXE,
	.callback.tc = CallBack_TC,
	.callback.rxne = CallBack_RXNE,
	.callback.idle = CallBack_IDLE,
	.callback.ore = CallBack_ORE,
	.callback.ne = NULL,
	.callback.fe = NULL,
	.callback.pe = NULL
};

STM32FXXX_USART1*  usart1(void){ return (STM32FXXX_USART1*) &stm32fxxx_usart1; }

/*** Interrupt handler for USART1 ***/
void USART1_IRQHandler(void) {
	// Check for CTS flag (if hardware flow control is enabled)
	if (is_SR_CTS()) {
		if(usart1()->callback.cts){ usart1()->callback.cts(); }
	}
	// Check for LIN Break Detection (if LIN mode is enabled)
	if (is_SR_LBD()) {
		if(usart1()->callback.lbd){ usart1()->callback.lbd(); }
	}

	if(is_CR1_TXEIE()) {
		if(is_SR_TXE()) {
			if(usart1()->callback.txe){ usart1()->callback.txe(); }
		}
	}

	if(is_CR1_TCIE()) {
		// Check if the TC (Transmission Complete) flag is set
		if (is_SR_TC()) {
			if(usart1()->callback.tc){ usart1()->callback.tc(); }
		}
	}

	if(is_SR_RXNE()) {
		if(usart1()->callback.rxne){ usart1()->callback.rxne(); }
	}
    // Check for IDLE line detection
    if (is_SR_IDLE()) {
        if(usart1()->callback.idle){ usart1()->callback.idle(); }
    }
    // Error handling (Overrun, Noise, Framing, Parity)
    if (is_SR_ORE()) {
    	if(usart1()->callback.ore){ usart1()->callback.ore(); }
    }
    if (is_SR_NE()) {
    	// Noise error: Handle noise (e.g., log or recover from error)
    	USART1->SR &= ~USART_SR_NE;
    	if (usart1()->callback.ne) { usart1()->callback.ne(); }
    }
    if (is_SR_FE()) {
    	// Framing error: Handle framing issues (e.g., re-sync communication)
    	USART1->SR &= ~USART_SR_NE;
    	    if (usart1()->callback.fe) { usart1()->callback.fe(); }
    }
    if (is_SR_PE()) {
    	// Parity error: Handle parity mismatch (e.g., request retransmission)
    	USART1->SR &= ~USART_SR_NE;
    	    if (usart1()->callback.pe) { usart1()->callback.pe(); }
    }
    // Optionally reset USART or take corrective action based on error type
	/***/
    // Wakeup from STOP mode (if enabled and used)
    //if (sr & USART_SR_WU) {
        // Clear wakeup flag by writing a 0
        //USART1->SR &= ~USART_SR_WU;
        // Handle wakeup event (e.g., resume communication)
    //}
}

/*** EOF ***/

