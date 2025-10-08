/******************************************************************************
	STM32 XXX USART6
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     24022024
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxusart6.h"
#include <string.h>
#include <math.h>

/*** File Variable ***/
static STM32FXXX_USART6 stm32fxxx_usart6 = {0};
/******/
// Buffer for received and transmit data
uint8_t usart6_rx_buffer[USART6_RX_BUFFER_SIZE];
volatile uint16_t usart6_rx_index = 0;
uint8_t usart6_tx_buffer[USART6_TX_BUFFER_SIZE];
volatile uint16_t usart6_tx_index = 0;
const uint16_t usart6_rx_buffer_size = (USART6_RX_BUFFER_SIZE - 1);
const uint16_t usart6_tx_buffer_size = (USART6_TX_BUFFER_SIZE - 1);
static uint8_t usart6_flag = 0;
/*** USART Procedure & Function Definition ***/
/*** USART6 ***/
void USART6_Clock( uint8_t state )
{
	if(state){ RCC->APB2ENR |= (1 << RCC_APB2ENR_USART6EN_Pos); }else{ RCC->APB2ENR &= ~(1 << RCC_APB2ENR_USART6EN_Pos); }
}
void USART6_Nvic( uint8_t state )
{
	if(state){ set_bit_block(NVIC->ISER, 1, USART6_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, USART6_IRQn, 1); }
}
void USART6_WordLength(uint8_t wordlength) {
    // Clear the M bit to reset word length
	USART6->CR1 &= ~(1 << USART_CR1_M_Pos);

    if (wordlength == 9) {
    	USART6->CR1 |= (1 << USART_CR1_M_Pos); // Set M bit for 9-bit word length
    }
    // If wordlength is 8 or any other value, do nothing (remains 8-bit)
}
void USART6_StopBits(double stopbits) {
    // Reset stop bits configuration
	USART6->CR2 &= (uint32_t) ~(USART_CR2_STOP_1 | USART_CR2_STOP_0);

    if (fabs(stopbits - 0.5) < 0.00001) { // 0.5 Stop bits
    	USART6->CR2 |= USART_CR2_STOP_0; // Set bit 12
    } else if (fabs(stopbits - 1.0) < 0.00001) { // 1 Stop bit
        // No additional bits set (already cleared)
    } else if (fabs(stopbits - 1.5) < 0.00001) { // 1.5 Stop bits
    	USART6->CR2 |= (USART_CR2_STOP_1 | USART_CR2_STOP_0); // Set both bits
    } else if (fabs(stopbits - 2.0) < 0.00001) { // 2 Stop bits
    	USART6->CR2 |= USART_CR2_STOP_1; // Set bit 13
    }
}
void USART6_SamplingMode(uint8_t samplingmode, uint32_t baudrate)
{
    // 1) Configure OVER8 bit
    if (samplingmode == 8) {
    	USART6->CR1 |= (1 << 15);   // OVER8 = 1
    } else {
    	USART6->CR1 &= ~(1 << 15);  // OVER8 = 0 (16x)
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
    USART6->BRR = brr;
}
void USART6_TxEnable(void) { USART6->CR1 |= USART_CR1_TE; }
void USART6_TxDisable(void) { USART6->CR1 &= ~USART_CR1_TE; }
void USART6_RxEnable(void) { USART6->CR1 |= USART_CR1_RE; }
void USART6_RxDisable(void) { USART6->CR1 &= ~USART_CR1_RE; }
void USART6_TransmitChar(char c) {
	USART6->CR1 &= ~USART_CR1_TXEIE;
    while (!(USART6->SR & USART_SR_TXE)); // Wait until TX is empty
    USART6->DR = c;                       // Send the character
}
char USART6_ReceiveChar(void) {
	USART6->CR1 &= ~USART_CR1_RXNEIE;
    while (!(USART6->SR & USART_SR_RXNE)); // Wait until RX is ready
    return (char)USART6->DR;               // Return the received character
}
void USART6_RxFlush(void) {
	usart6_rx_index = 0;
	usart6_rx_buffer[0] = 0;
}
void USART6_TransmitString(const char *str) {
	usart6_tx_index = 0;
    // Copy the string into the transmit buffer
    strncpy((char *)usart6_tx_buffer, str, usart6_tx_buffer_size); // Ensure tx_buffer is big enough
    usart6_tx_buffer[usart6_tx_buffer_size] = 0;
    // Enable the TXE interrupt to start sending data
    USART6->CR1 |= USART_CR1_TXEIE;
}
void USART6_ReceiveString(char* oneshot, char* rx, size_t size, const char* endl) {
	const uint32_t buff_size = size - 1;
	oneshot[buff_size] = 0; rx[buff_size] = 0;
	if(usart6_flag) { *oneshot = 0; usart6_flag = 0; }
	char *ptr = (char*)usart6_rx_buffer;
	size_t ptr_length = strlen((char*)ptr);
	if( ptr_length < usart6_rx_buffer_size ) {
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
				usart6_flag = 0xFF;
				USART6_RxFlush( );
			}
		}
	}else { USART6_RxFlush( ); }
}
void USART6_start(void) { USART6->CR1 |= USART_CR1_UE; }
void USART6_stop(void) { USART6->CR1 &= ~USART_CR1_UE; }

/*** USART6 INIC Procedure & Function Definition ***/
void usart6_enable(void)
{
	USART6_Clock(1);
	// Other
	stm32fxxx_usart6.clock = USART6_Clock;
	stm32fxxx_usart6.nvic = USART6_Nvic;
	stm32fxxx_usart6.wordlength = USART6_WordLength;
	stm32fxxx_usart6.stopbits = USART6_StopBits;
	stm32fxxx_usart6.samplingmode = USART6_SamplingMode;
	stm32fxxx_usart6.tx_enable = USART6_TxEnable;
	stm32fxxx_usart6.tx_disable = USART6_TxDisable;
	stm32fxxx_usart6.rx_enable = USART6_RxEnable;
	stm32fxxx_usart6.rx_disable = USART6_RxDisable;
	stm32fxxx_usart6.transmit_char = USART6_TransmitChar;
	stm32fxxx_usart6.receive_char = USART6_ReceiveChar;
	stm32fxxx_usart6.rx_flush = USART6_RxFlush;
	stm32fxxx_usart6.transmit_string = USART6_TransmitString;
	stm32fxxx_usart6.receive_string = USART6_ReceiveString;
	stm32fxxx_usart6.start = USART6_start;
	stm32fxxx_usart6.stop = USART6_stop;
	// Inic
	usart6_tx_buffer[usart6_tx_buffer_size] = 0;
	usart6_rx_buffer[usart6_rx_buffer_size] = 0;
}

STM32FXXX_USART6*  usart6(void){ return (STM32FXXX_USART6*) &stm32fxxx_usart6; }

/*** Interrupt handler for USART6 ***/
void USART6_IRQHandler(void) {
	uint32_t sr = USART6->SR;
	uint32_t cr1 = USART6->CR1;

	if(cr1 & USART_CR1_RXNEIE) {
		// Check if the RXNE (Receive Not Empty) flag is set
		if (sr & USART_SR_RXNE) {
			uint8_t received_byte = USART6->DR;
			if (usart6_rx_index < usart6_rx_buffer_size) {
				usart6_rx_buffer[usart6_rx_index++] = received_byte;
				usart6_rx_buffer[usart6_rx_index] = 0;
			}
		}
	}

	if(cr1 & USART_CR1_TXEIE) {
		// Check if the TXE (Transmit Data Register Empty) flag is set
		if (sr & USART_SR_TXE) {
			if(usart6_tx_buffer[usart6_tx_index]) {
				USART6->DR = usart6_tx_buffer[usart6_tx_index++];
			}else{
				USART6->CR1 &= ~USART_CR1_TXEIE;
			}
		}
	}

	if(cr1 & USART_CR1_TCIE) {
		// Check if the TC (Transmission Complete) flag is set
		if (sr & USART_SR_TC) {
			// Transmission complete
			(void)USART6->SR;  // Read SR to acknowledge
			USART6->DR = 0;    // Write to DR to clear TC flag
			// Optionally disable TC interrupt if no further action is needed
			USART6->CR1 &= ~USART_CR1_TCIE;
		}
	}

    // Check for IDLE line detection
    if (sr & USART_SR_IDLE) {
        // Clear IDLE flag by reading SR and DR
        volatile uint8_t dummy = USART6->DR;
        (void)dummy;  // Prevent unused variable warning
        // Handle idle condition (e.g., mark end of transmission)
    }

    // Check for CTS flag (if hardware flow control is enabled)
    if (sr & USART_SR_CTS) {
        // Clear CTS flag by reading SR
        volatile uint8_t dummy = USART6->SR;
        (void)dummy;
        // Handle CTS change (e.g., pause/resume transmission)
    }

    // Check for LIN Break Detection (if LIN mode is enabled)
    if (sr & USART_SR_LBD) {
        // Clear LBD flag by writing a 0
        USART6->SR &= ~USART_SR_LBD;
        // Handle LIN break detection (e.g., reset communication)
    }

    // Error handling (Overrun, Noise, Framing, Parity)
    if (sr & (USART_SR_ORE | USART_SR_NE | USART_SR_FE | USART_SR_PE)) {
        if (sr & USART_SR_ORE) {
            // Overrun error: Clear ORE by reading DR
            volatile uint8_t dummy = USART6->DR;
            (void)dummy;
            // Handle overrun error (e.g., discard data)
        }
        if (sr & USART_SR_NE) {
            // Noise error: Handle noise (e.g., log or recover from error)
        }
        if (sr & USART_SR_FE) {
            // Framing error: Handle framing issues (e.g., re-sync communication)
        }
        if (sr & USART_SR_PE) {
            // Parity error: Handle parity mismatch (e.g., request retransmission)
        }

        // Optionally reset USART or take corrective action based on error type
    }

    // Wakeup from STOP mode (if enabled and used)
    //if (sr & USART_SR_WU) {
        // Clear wakeup flag by writing a 0
        //USART6->SR &= ~USART_SR_WU;
        // Handle wakeup event (e.g., resume communication)
    //}
}

/*** EOF ***/

