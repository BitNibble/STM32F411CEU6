/******************************************************************************
	STM32 XXX USART1
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     24022024
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxusart1.h"
#include "stm32fxxxnvic.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

/*** File Variable ***/
// Buffer for received and transmit data
static char usart1_rx_buffer[USART1_RX_BUFFER_SIZE + 1] = {0};
volatile size_t usart1_rx_index = 0;
static char usart1_tx_buffer[USART1_TX_BUFFER_SIZE + 1] = {0};
volatile size_t usart1_tx_index = 0;
static uint8_t usart1_flag = 0;
/*** USART Procedure & Function Definition ***/
/*** Default Init ***/
void USART1_defualt_init(void)
{
    usart1()->clock(1);

    // GPIO config
    GPIO_moder(dev()->gpioa, 9, MODE_AF);
    GPIO_moder(dev()->gpioa,10, MODE_AF);

    GPIO_af(dev()->gpioa, 9, 7);
    GPIO_af(dev()->gpioa, 10, 7);

    GPIO_ospeed(dev()->gpioa, 9, 3);
    GPIO_ospeed(dev()->gpioa, 10, 3);

    GPIO_otype(dev()->gpioa, 9, 0);
    GPIO_otype(dev()->gpioa, 10, 0);

    GPIO_pupd(dev()->gpioa, 9, 0);   // TX no pull
    GPIO_pupd(dev()->gpioa, 10, 2);  // RX pull-up (REQUIRED)

    // Baud rate / sampling
    usart1()->samplingmode(0, 38400);

    // Enable USART core FIRST
    usart1()->tx(1);
    usart1()->rx(1);
    usart1()->start();     // clears SR internally

    // THEN enable interrupts
    usart1()->tx_einterrupt(1);
    usart1()->rx_neinterrupt(1);
    usart1()->nvic(1);
}
/*** USART1 ***/
void USART1_Clock( uint8_t state )
{
	if(state){ RCC->APB2ENR |= (1 << RCC_APB2ENR_USART1EN_Pos); }
	else{ RCC->APB2ENR &= ~(1 << RCC_APB2ENR_USART1EN_Pos); }
}
void USART1_Nvic( uint8_t state )
{
	if(state){ set_bit_block(NVIC->ISER, 1, USART1_IRQn, 1); }
	else{ set_bit_block(NVIC->ICER, 1, USART1_IRQn, 1); }
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
        samplingmode = 16;          // normalize
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
void USART1_TX_enable( uint8_t state ) {
	if( state )
		USART1->CR1 |= USART_CR1_TE;
	else
		USART1->CR1 &= ~USART_CR1_TE;
}
void USART1_RX_enable( uint8_t state ) {
	if( state )
		USART1->CR1 |= USART_CR1_RE;
	else
		USART1->CR1 &= ~USART_CR1_RE;
}
void USART1_TXEI_enable( uint8_t state ) {
	if( state )
		USART1->CR1 |= USART_CR1_TXEIE;
	else
		USART1->CR1 &= ~USART_CR1_TXEIE;
}
void USART1_TCI_enable( uint8_t state ) {
	if( state )
		USART1->CR1 |= USART_CR1_TCIE;
	else
		USART1->CR1 &= ~USART_CR1_TCIE;
}
void USART1_RXNEI_enable( uint8_t state) {
	if ( state )
		USART1->CR1 |= USART_CR1_RXNEIE;
	else
		USART1->CR1 &= ~USART_CR1_RXNEIE;
}
/*****************************************************************************/
uint32_t USART1_RX_index( void )
{
	return usart1_rx_index;
}
uint32_t is_USART1_CR1_PEIE(void){
	return USART1->CR1 & USART_CR1_PEIE;
}
uint32_t is_USART1_CR1_TXEIE(void){
	return USART1->CR1 & USART_CR1_TXEIE;
}
uint32_t is_USART1_CR1_TCIE(void){
	return USART1->CR1 & USART_CR1_TCIE;
}
uint32_t is_USART1_CR1_RXNEIE(void){
	return USART1->CR1 & USART_CR1_RXNEIE;
}
uint32_t is_USART1_CR1_IDLEIE(void){
	return USART1->CR1 & USART_CR1_IDLEIE;
}
/*****************************************************************************/
uint32_t is_USART1_SR_CTS(void){
	return USART1->SR & USART_SR_CTS;
}
uint32_t is_USART1_SR_LBD(void){
	return USART1->SR & USART_SR_LBD;
}
uint32_t is_USART1_SR_TXE(void){
	return USART1->SR & USART_SR_TXE;
}
uint32_t is_USART1_SR_TC(void){
	return USART1->SR & USART_SR_TC;
}
uint32_t is_USART1_SR_RXNE(void){
	return USART1->SR & USART_SR_RXNE;
}
uint32_t is_USART1_SR_IDLE(void){
	return USART1->SR & USART_SR_IDLE;
}
uint32_t is_USART1_SR_ORE(void){
	return USART1->SR & USART_SR_ORE;
}
uint32_t is_USART1_SR_NE(void){
	return USART1->SR & USART_SR_NE;
}
uint32_t is_USART1_SR_FE(void){
	return USART1->SR & USART_SR_FE;
}
uint32_t is_USART1_SR_PE(void){
	return USART1->SR & USART_SR_PE;
}
void _USART1_clear_SR(void){
	volatile uint32_t tmp;
	tmp = USART1->SR;
	tmp = USART1->DR;
	(void)tmp;
}

/*****************************************************************************/
void USART1_PutChar(char c) {
    USART1->DR = c;	// Send the character
}
char USART1_GetChar(void) {
    return USART1->DR;	// Return the character
}
void USART1_TransmitChar(char c) {
    if (USART1->CR1 & USART_CR1_TXEIE) return; // protect IRQ TX
    while (!(USART1->SR & USART_SR_TXE));
    USART1_PutChar(c);
}
char USART1_ReceiveChar(void) {
    while (!(USART1->SR & USART_SR_RXNE)); // Wait until RX is ready
    return USART1_GetChar();	// Return the received character
    //USART1->CR1 &= ~USART_CR1_RXNEIE;
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
}
void USART1_TransmitString(const char *str) {
	USART1_TxFlush();
    // Copy the string into the transmit buffer
    strncpy( (char *)usart1_tx_buffer, str, USART1_TX_BUFFER_SIZE ); // Ensure tx_buffer is big enough
    // Enable the TXE interrupt to start sending data
    USART1_TXEI_enable(1);
}
void USART1_ReceiveString(char* oneshot, char* rx, size_t size, const char* endl) {
	const uint32_t buff_size = size - 1;
	if(usart1_flag) { memset(oneshot, 0, size); usart1_flag = 0; }
	char *ptr = usart1_rx_buffer;
	size_t ptr_length = usart1_rx_index;
	if( ptr_length < USART1_RX_BUFFER_SIZE ) {
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
	size_t ptr_length = usart1_rx_index;
	if( ptr_length < USART1_RX_BUFFER_SIZE ) {
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

void USART1_start(void)
{
    // Disable USART
    USART1->CR1 &= ~USART_CR1_UE;

    // Clear pending flags
    _USART1_clear_SR();

    // Reset indexes
    usart1_rx_index = 0;
    usart1_tx_index = 0;

    // Enable USART
    USART1->CR1 |= USART_CR1_UE;
}

void USART1_stop(void) { USART1->CR1 &= ~USART_CR1_UE; }

void USART1_hard_reset(void)
{
    USART1_stop();
    _USART1_clear_SR();
    USART1_RxFlush();
    USART1_start();
}

// CALLBACK
void USART1_CallBack_ERROR(void){
	// Overrun error: Clear ORE by reading DR
	_USART1_clear_SR();
	// Handle overrun error (e.g., discard data)
}
void USART1_CallBack_CTS(void){
	// Clear CTS flag by reading SR
	volatile uint32_t dummy = USART1->SR;
	(void)dummy;
	// Handle CTS change (e.g., pause/resume transmission)
}
void USART1_CallBack_LBD(void){
	// Clear LBD flag by writing a 0
	_USART1_clear_SR();
	// Handle LIN break detection (e.g., reset communication)
}
void USART1_CallBack_TXE(void){
	if(usart1_tx_buffer[usart1_tx_index]) {
		USART1_PutChar( usart1_tx_buffer[usart1_tx_index++] );
	}else{
		USART1->CR1 &= ~USART_CR1_TXEIE;
	}
}
void USART1_CallBack_TC(void){
	// Transmission complete
	//USART1->DR = 0; // Write to DR to clear TC flag
	// Optionally disable TC interrupt if no further action is needed
	USART1->CR1 &= ~USART_CR1_TCIE;
}
void USART1_CallBack_RXNE(void){
	char rx = USART1_GetChar();
	// Check if the RXNE (Receive Not Empty) flag is set
		if (usart1_rx_index < USART1_RX_BUFFER_SIZE) {
			usart1_rx_buffer[usart1_rx_index++] = rx;
			usart1_rx_buffer[usart1_rx_index] = 0;
		}
}
void USART1_CallBack_IDLE(void){
	// Clear IDLE flag by reading SR and DR
	_USART1_clear_SR();
	// Handle idle condition (e.g., mark end of transmission)
}

/*** USART1 INIC Procedure & Function Definition ***/
static STM32FXXX_USART1_CallBack USART1_callback_setup = {
		.cts = USART1_CallBack_CTS,
		.lbd = USART1_CallBack_LBD,
		.txe = USART1_CallBack_TXE,
		.tc = USART1_CallBack_TC,
		.rxne = USART1_CallBack_RXNE,
		.idle = USART1_CallBack_IDLE,
		.error = USART1_CallBack_ERROR,
		.ore = NULL,
		.ne = NULL,
		.fe = NULL,
		.pe = NULL
};

static STM32FXXX_USART1_Handler stm32fxxx_usart1_setup = {
	// V-table
	.clock = USART1_Clock,
	.nvic = USART1_Nvic,
	// Config
	.inic = USART1_defualt_init,
	.wordlength = USART1_WordLength,
	.stopbits = USART1_StopBits,
	.samplingmode = USART1_SamplingMode,
	.is_tx_complete = is_USART1_SR_TC,
	.is_rx_idle = is_USART1_SR_IDLE,
	// Enable
	.tx = USART1_TX_enable,
	.rx = USART1_RX_enable,
	.rx_index = USART1_RX_index,
	// Interrupt
	.tx_einterrupt = USART1_TXEI_enable,
	.rx_neinterrupt = USART1_RXNEI_enable,
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
	.callback = &USART1_callback_setup,
};

STM32FXXX_USART1_Handler*  usart1(void){ return (STM32FXXX_USART1_Handler*) &stm32fxxx_usart1_setup; }

/*** Interrupt handler for USART1 ***/
void USART1_IRQHandler(void)
{
    STM32FXXX_USART1_CallBack* cb = &USART1_callback_setup;

    // 1️⃣ ERROR FIRST — ALWAYS
    if (is_USART1_SR_ORE() || is_USART1_SR_NE() ||
        is_USART1_SR_FE()  || is_USART1_SR_PE())
    {
        if (cb->error) cb->error();
        return; // STOP processing this IRQ
    }
    // 2️⃣ RX
    if (is_USART1_CR1_RXNEIE() && is_USART1_SR_RXNE()) {
        if (cb->rxne) cb->rxne();
    }

    // 3️⃣ IDLE
    if (is_USART1_CR1_IDLEIE() && is_USART1_SR_IDLE()) {
        if (cb->idle) cb->idle();
    }

    // 4️⃣ TX
    if (is_USART1_CR1_TXEIE() && is_USART1_SR_TXE()) {
        if (cb->txe) cb->txe();
    }

    if (is_USART1_CR1_TCIE() && is_USART1_SR_TC()) {
        if (cb->tc) cb->tc();
    }
}

/*** EOF ***/

