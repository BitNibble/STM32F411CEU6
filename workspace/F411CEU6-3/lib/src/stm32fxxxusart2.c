/******************************************************************************
	STM32 XXX USART2
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     24022024
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxusart2.h"
#include <string.h>
#include <math.h>

/*** File Variable ***/
static STM32FXXX_USART2 stm32fxxx_usart2 = {ZERO};
/******/
// Buffer for received and transmit data
uint8_t usart2_rx_buffer[USART2_RX_BUFFER_SIZE];
volatile uint16_t usart2_rx_index = ZERO;
uint8_t usart2_tx_buffer[USART2_TX_BUFFER_SIZE];
volatile uint16_t usart2_tx_index = ZERO;
const uint16_t usart2_rx_buffer_size = (USART2_RX_BUFFER_SIZE - ONE);
const uint16_t usart2_tx_buffer_size = (USART2_TX_BUFFER_SIZE - ONE);
static uint8_t usart2_flag = ZERO;
/*** USART Procedure & Function Definition ***/
/*** USART2 ***/
void USART2_Clock( uint8_t state )
{
	if(state){ RCC->APB1ENR |= (1 << RCC_APB1ENR_USART2EN_Pos); }else{ RCC->APB1ENR &= ~(1 << RCC_APB1ENR_USART2EN_Pos); }
}
void USART2_Nvic( uint8_t state )
{
	if(state){ set_bit_block(NVIC->ISER, ONE, USART2_IRQn, 1); }else{ set_bit_block(NVIC->ICER, ONE, USART2_IRQn, 1); }
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
    uint8_t sampling = 16; // Default to 16
    if (samplingmode == 8) {
        sampling = 8;
        USART2->CR1 |= (1 << USART_CR1_OVER8_Pos); // Set OVER8 for 8 times oversampling
    } else {
    	USART2->CR1 &= ~(1 << USART_CR1_OVER8_Pos); // Clear OVER8 for 16 times oversampling
    }

    double value = (double) getsysclk() / (gethpre() * sampling * baudrate);
    double fracpart, intpart;
    fracpart = modf(value, &intpart);

    USART2->BRR = 0; // Reset BRR
    uint32_t fraction = (sampling == 16) ? round(fracpart * 16) : round(fracpart * 8);
    USART2->BRR |= (uint32_t) fraction; // Set DIV_Fraction
    USART2->BRR |= ((uint32_t) intpart << USART_BRR_DIV_Mantissa_Pos); // Set DIV_Mantissa[11:0]
}
void USART2_TxEnable(void) { USART2->CR1 |= USART_CR1_TE; }
void USART2_TxDisable(void) { USART2->CR1 &= ~USART_CR1_TE; }
void USART2_RxEnable(void) { USART2->CR1 |= USART_CR1_RE; }
void USART2_RxDisable(void) { USART2->CR1 &= ~USART_CR1_RE; }
void USART2_TransmitChar(char c) {
	USART2->CR1 &= ~USART_CR1_TXEIE;
    while (!(USART2->SR & USART_SR_TXE)); // Wait until TX is empty
    USART2->DR = c;                       // Send the character
}
char USART2_ReceiveChar(void) {
	USART2->CR1 &= ~USART_CR1_RXNEIE;
    while (!(USART2->SR & USART_SR_RXNE)); // Wait until RX is ready
    return (char)USART2->DR;               // Return the received character
}
void USART2_RxFlush(void) {
	usart2_rx_index = ZERO;
	usart2_rx_buffer[ZERO] = ZERO;
}
void USART2_TransmitString(const char *str) {
	usart2_tx_index = ZERO;
    // Copy the string into the transmit buffer
    strncpy((char *)usart2_tx_buffer, str, usart2_tx_buffer_size); // Ensure tx_buffer is big enough
    usart2_tx_buffer[usart2_tx_buffer_size] = ZERO;
    // Enable the TXE interrupt to start sending data
    USART2->CR1 |= USART_CR1_TXEIE;
}
void USART2_ReceiveString(char* oneshot, char* rx, size_t size, const char* endl) {
	const uint32_t buff_size = size - ONE;
	oneshot[buff_size] = ZERO; rx[buff_size] = ZERO;
	if(usart2_flag) { *oneshot = ZERO; usart2_flag = ZERO; }
	char *ptr = (char*)usart2_rx_buffer;
	size_t ptr_length = strlen((char*)ptr);
	if( ptr_length < usart2_rx_buffer_size ) {
		size_t endl_length = strlen(endl);
		int32_t diff_length = ptr_length - endl_length;
		int32_t check;
		if( diff_length >= ZERO ) {
			check = strcmp((char*)ptr + diff_length, endl);
			if( !check ) {
				strncpy(oneshot, (const char*)ptr, buff_size);
				oneshot[diff_length] = ZERO;
				strncpy(rx, (const char*)ptr, buff_size);
				rx[diff_length] = ZERO;
				usart2_flag = 0xFF;
				USART2_RxFlush( );
			}
		}
	}else { USART2_RxFlush( ); }
}
void USART2_start(void) { USART2->CR1 |= USART_CR1_UE; }
void USART2_stop(void) { USART2->CR1 &= ~USART_CR1_UE; }

/*** USART2 INIC Procedure & Function Definition ***/
void usart2_enable(void)
{
	USART2_Clock( ON );
	/*** USART2 Bit Mapping Link ***/
	stm32fxxx_usart2.instance = USART2;
	// Other
	stm32fxxx_usart2.clock = USART2_Clock;
	stm32fxxx_usart2.nvic = USART2_Nvic;
	stm32fxxx_usart2.wordlength = USART2_WordLength;
	stm32fxxx_usart2.stopbits = USART2_StopBits;
	stm32fxxx_usart2.samplingmode = USART2_SamplingMode;
	stm32fxxx_usart2.tx_enable = USART2_TxEnable;
	stm32fxxx_usart2.tx_disable = USART2_TxDisable;
	stm32fxxx_usart2.rx_enable = USART2_RxEnable;
	stm32fxxx_usart2.rx_disable = USART2_RxDisable;
	stm32fxxx_usart2.transmit_char = USART2_TransmitChar;
	stm32fxxx_usart2.receive_char = USART2_ReceiveChar;
	stm32fxxx_usart2.rx_flush = USART2_RxFlush;
	stm32fxxx_usart2.transmit_string = USART2_TransmitString;
	stm32fxxx_usart2.receive_string = USART2_ReceiveString;
	stm32fxxx_usart2.start = USART2_start;
	stm32fxxx_usart2.stop = USART2_stop;
	// Inic
	usart2_tx_buffer[usart2_tx_buffer_size] = ZERO;
	usart2_rx_buffer[usart2_rx_buffer_size] = ZERO;
}

STM32FXXX_USART2*  usart2(void){ return (STM32FXXX_USART2*) &stm32fxxx_usart2; }

/*** Interrupt handler for USART2 ***/
void USART2_IRQHandler(void) {
	uint32_t sr = USART2->SR;
	uint32_t cr1 = USART2->CR1;

	if(cr1 & USART_CR1_RXNEIE) {
		// Check if the RXNE (Receive Not Empty) flag is set
		if (sr & USART_SR_RXNE) {
			uint8_t received_byte = USART2->DR;
			if (usart2_rx_index < usart2_rx_buffer_size) {
				usart2_rx_buffer[usart2_rx_index++] = received_byte;
				usart2_rx_buffer[usart2_rx_index] = ZERO;
			}
		}
	}

	if(cr1 & USART_CR1_TXEIE) {
		// Check if the TXE (Transmit Data Register Empty) flag is set
		if (sr & USART_SR_TXE) {
			if(usart2_tx_buffer[usart2_tx_index]) {
				USART2->DR = usart2_tx_buffer[usart2_tx_index++];
			}else{
				USART2->CR1 &= ~USART_CR1_TXEIE;
			}
		}
	}

	if(cr1 & USART_CR1_TCIE) {
		// Check if the TC (Transmission Complete) flag is set
		if (sr & USART_SR_TC) {
			// Transmission complete
			(void)USART2->SR;  // Read SR to acknowledge
			USART2->DR = ZERO;    // Write to DR to clear TC flag
			// Optionally disable TC interrupt if no further action is needed
			USART2->CR1 &= ~USART_CR1_TCIE;
		}
	}

    // Check for IDLE line detection
    if (sr & USART_SR_IDLE) {
        // Clear IDLE flag by reading SR and DR
        volatile uint8_t dummy = USART2->DR;
        (void)dummy;  // Prevent unused variable warning
        // Handle idle condition (e.g., mark end of transmission)
    }

    // Check for CTS flag (if hardware flow control is enabled)
    if (sr & USART_SR_CTS) {
        // Clear CTS flag by reading SR
        volatile uint8_t dummy = USART2->SR;
        (void)dummy;
        // Handle CTS change (e.g., pause/resume transmission)
    }

    // Check for LIN Break Detection (if LIN mode is enabled)
    if (sr & USART_SR_LBD) {
        // Clear LBD flag by writing a 0
        USART2->SR &= ~USART_SR_LBD;
        // Handle LIN break detection (e.g., reset communication)
    }

    // Error handling (Overrun, Noise, Framing, Parity)
    if (sr & (USART_SR_ORE | USART_SR_NE | USART_SR_FE | USART_SR_PE)) {
        if (sr & USART_SR_ORE) {
            // Overrun error: Clear ORE by reading DR
            volatile uint8_t dummy = USART2->DR;
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
        //USART2->SR &= ~USART_SR_WU;
        // Handle wakeup event (e.g., resume communication)
    //}
}

/*** EOF ***/

