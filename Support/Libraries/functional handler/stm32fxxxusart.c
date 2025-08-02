/******************************************************************************
	STM32 XXX USART
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 24022024
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxusart.h"
#include "armquery.h"
#include <math.h>

/*** File Variable ***/
static STM32FXXX_USART1 stm32fxxx_usart1 = {0};
static STM32FXXX_USART2 stm32fxxx_usart2 = {0};
#ifdef STM32F446xx
	static STM32FXXX_USART3 stm32fxxx_usart3 = {0};
	static STM32FXXX_UART4 stm32fxxx_uart4 = {0};
	static STM32FXXX_UART5 stm32fxxx_uart5 = {0};
#endif
static STM32FXXX_USART6 stm32fxxx_usart6 = {0};
/*** USART Procedure & Function Definition ***/
void Usart3_WordLength(uint8_t wordlength);
void Usart3_StopBits(double stopbits);
void Usart3_SamplingMode(uint8_t samplingmode, uint32_t baudrate);
void Usart4_WordLength(uint8_t wordlength);
void Usart4_StopBits(double stopbits);
void Usart4_SamplingMode(uint8_t samplingmode, uint32_t baudrate);
void Usart5_WordLength(uint8_t wordlength);
void Usart5_StopBits(double stopbits);
void Usart5_SamplingMode(uint8_t samplingmode, uint32_t baudrate);
/*** USART1 ***/
void STM32FXXXUsart1Clock( uint8_t state )
{
	if(state){ RCC->APB2ENR |= (1 << 4); }else{ RCC->APB2ENR &= ~(1 << 4); }
}
void STM32FXXXUsart1Nvic( uint8_t state )
{
	if(state){ set_bit_block(NVIC->ISER, 1, USART1_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, USART1_IRQn, 1); }
}
void Usart1_WordLength(uint8_t wordlength) {
    // Clear the M bit to reset word length
	USART1->CR1 &= ~(1 << 12);

    if (wordlength == 9) {
    	USART1->CR1 |= (1 << 12); // Set M bit for 9-bit word length
    }
    // If wordlength is 8 or any other value, do nothing (remains 8-bit)
}

void Usart1_StopBits(double stopbits) {
    // Reset stop bits configuration
	USART1->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));

    if (fabs(stopbits - 0.5) < 0.00001) { // 0.5 Stop bits
    	USART1->CR2 |= (1 << 12); // Set bit 12
    } else if (fabs(stopbits - 1.0) < 0.00001) { // 1 Stop bit
        // No additional bits set (already cleared)
    } else if (fabs(stopbits - 1.5) < 0.00001) { // 1.5 Stop bits
    	USART1->CR2 |= (1 << 13) | (1 << 12); // Set both bits
    } else if (fabs(stopbits - 2.0) < 0.00001) { // 2 Stop bits
    	USART1->CR2 |= (1 << 13); // Set bit 13
    }
}

void Usart1_SamplingMode(uint8_t samplingmode, uint32_t baudrate)
{
    uint8_t sampling = 16; // Default to 16
    if (samplingmode == 8) {
        sampling = 8;
        USART1->CR1 |= (1 << 15); // Set OVER8 for 8 times oversampling
    } else {
    	USART1->CR1 &= ~(1 << 15); // Clear OVER8 for 16 times oversampling
    }

    double value = (double) getsysclk() / (gethpre() * sampling * baudrate);
    double fracpart, intpart;
    fracpart = modf(value, &intpart);

    USART1->BRR = 0; // Reset BRR
    uint32_t fraction = (sampling == 16) ? round(fracpart * 16) : round(fracpart * 8);
    USART1->BRR |= (uint32_t) fraction; // Set DIV_Fraction
    USART1->BRR |= ((uint32_t) intpart << 4); // Set DIV_Mantissa[11:0]
}
/*** USART2 ***/
void STM32FXXXUsart2Clock( uint8_t state )
{
	if(state){ RCC->APB1ENR |= (1 << 17); }else{ RCC->APB1ENR &= ~(1 << 17); }
}
void STM32FXXXUsart2Nvic( uint8_t state )
{
	if(state){ set_bit_block(NVIC->ISER, 1, USART2_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, USART2_IRQn, 1); }
}
void Usart2_WordLength(uint8_t wordlength) {
    // Clear the M bit to reset word length
	USART2->CR1 &= ~(1 << 12);

    if (wordlength == 9) {
    	USART2->CR1 |= (1 << 12); // Set M bit for 9-bit word length
    }
    // If wordlength is 8 or any other value, do nothing (remains 8-bit)
}

void Usart2_StopBits(double stopbits) {
    // Reset stop bits configuration
	USART2->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));

    if (fabs(stopbits - 0.5) < 0.00001) { // 0.5 Stop bits
    	USART2->CR2 |= (1 << 12); // Set bit 12
    } else if (fabs(stopbits - 1.0) < 0.00001) { // 1 Stop bit
        // No additional bits set (already cleared)
    } else if (fabs(stopbits - 1.5) < 0.00001) { // 1.5 Stop bits
    	USART2->CR2 |= (1 << 13) | (1 << 12); // Set both bits
    } else if (fabs(stopbits - 2.0) < 0.00001) { // 2 Stop bits
    	USART2->CR2 |= (1 << 13); // Set bit 13
    }
}

void Usart2_SamplingMode(uint8_t samplingmode, uint32_t baudrate)
{
    uint8_t sampling = 16; // Default to 16
    if (samplingmode == 8) {
        sampling = 8;
        USART2->CR1 |= (1 << 15); // Set OVER8 for 8 times oversampling
    } else {
    	USART2->CR1 &= ~(1 << 15); // Clear OVER8 for 16 times oversampling
    }

    double value = (double) getsysclk() / (gethpre() * sampling * baudrate);
    double fracpart, intpart;
    fracpart = modf(value, &intpart);

    USART2->BRR = 0; // Reset BRR
    uint32_t fraction = (sampling == 16) ? round(fracpart * 16) : round(fracpart * 8);
    USART2->BRR |= (uint32_t) fraction; // Set DIV_Fraction
    USART2->BRR |= ((uint32_t) intpart << 4); // Set DIV_Mantissa[11:0]
}

#ifdef STM32F446xx
/*** USART3 ***/
void STM32FXXXUsart3Clock( uint8_t state )
{
	if(state){ RCC->APB1ENR |= (1 << 18); }else{ RCC->APB1ENR &= ~(1 << 18); }
}
void STM32FXXXUsart3Nvic( uint8_t state )
{
	if(state){ set_bit_block(NVIC->ISER, 1, USART3_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, USART3_IRQn, 1); }
}
void Usart3_WordLength(uint8_t wordlength) {
    // Clear the M bit to reset word length
	USART3->CR1 &= ~(1 << 12);

    if (wordlength == 9) {
    	USART3->CR1 |= (1 << 12); // Set M bit for 9-bit word length
    }
    // If wordlength is 8 or any other value, do nothing (remains 8-bit)
}

void Usart3_StopBits(double stopbits) {
    // Reset stop bits configuration
	USART3->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));

    if (fabs(stopbits - 0.5) < 0.00001) { // 0.5 Stop bits
    	USART3->CR2 |= (1 << 12); // Set bit 12
    } else if (fabs(stopbits - 1.0) < 0.00001) { // 1 Stop bit
        // No additional bits set (already cleared)
    } else if (fabs(stopbits - 1.5) < 0.00001) { // 1.5 Stop bits
    	USART3->CR2 |= (1 << 13) | (1 << 12); // Set both bits
    } else if (fabs(stopbits - 2.0) < 0.00001) { // 2 Stop bits
    	USART3->CR2 |= (1 << 13); // Set bit 13
    }
}

void Usart3_SamplingMode(uint8_t samplingmode, uint32_t baudrate)
{
    uint8_t sampling = 16; // Default to 16
    if (samplingmode == 8) {
        sampling = 8;
        USART3->CR1 |= (1 << 15); // Set OVER8 for 8 times oversampling
    } else {
    	USART3->CR1 &= ~(1 << 15); // Clear OVER8 for 16 times oversampling
    }

    double value = (double) getsysclk() / (gethpre() * sampling * baudrate);
    double fracpart, intpart;
    fracpart = modf(value, &intpart);

    USART3->BRR = 0; // Reset BRR
    uint32_t fraction = (sampling == 16) ? round(fracpart * 16) : round(fracpart * 8);
    USART3->BRR |= (uint32_t) fraction; // Set DIV_Fraction
    USART3->BRR |= ((uint32_t) intpart << 4); // Set DIV_Mantissa[11:0]
}
/*** UART4 ***/
void STM32FXXXUart4Clock( uint8_t state )
{
	if(state){ RCC->APB1ENR |= (1 << 19); }else{ RCC->APB1ENR &= ~(1 << 19); }

}
void STM32FXXXUart4Nvic( uint8_t state )
{
	if(state){ set_bit_block(NVIC->ISER, 1, UART4_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, UART4_IRQn, 1); }
}
void Usart4_WordLength(uint8_t wordlength) {
    // Clear the M bit to reset word length
	USART4->CR1 &= ~(1 << 12);

    if (wordlength == 9) {
    	USART4->CR1 |= (1 << 12); // Set M bit for 9-bit word length
    }
    // If wordlength is 8 or any other value, do nothing (remains 8-bit)
}

void Usart4_StopBits(double stopbits) {
    // Reset stop bits configuration
	USART4->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));

    if (fabs(stopbits - 0.5) < 0.00001) { // 0.5 Stop bits
    	USART4->CR2 |= (1 << 12); // Set bit 12
    } else if (fabs(stopbits - 1.0) < 0.00001) { // 1 Stop bit
        // No additional bits set (already cleared)
    } else if (fabs(stopbits - 1.5) < 0.00001) { // 1.5 Stop bits
    	USART4->CR2 |= (1 << 13) | (1 << 12); // Set both bits
    } else if (fabs(stopbits - 2.0) < 0.00001) { // 2 Stop bits
    	USART4->CR2 |= (1 << 13); // Set bit 13
    }
}

void Usart4_SamplingMode(uint8_t samplingmode, uint32_t baudrate)
{
    uint8_t sampling = 16; // Default to 16
    if (samplingmode == 8) {
        sampling = 8;
        USART4->CR1 |= (1 << 15); // Set OVER8 for 8 times oversampling
    } else {
    	USART4->CR1 &= ~(1 << 15); // Clear OVER8 for 16 times oversampling
    }

    double value = (double) getsysclk() / (gethpre() * sampling * baudrate);
    double fracpart, intpart;
    fracpart = modf(value, &intpart);

    USART4->BRR = 0; // Reset BRR
    uint32_t fraction = (sampling == 16) ? round(fracpart * 16) : round(fracpart * 8);
    USART4->BRR |= (uint32_t) fraction; // Set DIV_Fraction
    USART4->BRR |= ((uint32_t) intpart << 4); // Set DIV_Mantissa[11:0]
}
/*** UART5 ***/
void STM32FXXXUart5Clock( uint8_t state )
{
	if(state){ RCC->APB1ENR |= (1 << 20); } // UART5EN: USART5 clock enable
	else{ RCC->APB1ENR &= ~(1 << 20); } // UART5EN: USART5 clock disable
}
void STM32FXXXUart5Nvic( uint8_t state )
{
	if(state){ set_bit_block(NVIC->ISER, 1, UART5_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, UART5_IRQn, 1); }
}
void Usart5_WordLength(uint8_t wordlength) {
    // Clear the M bit to reset word length
	USART5->CR1 &= ~(1 << 12);

    if (wordlength == 9) {
    	USART5->CR1 |= (1 << 12); // Set M bit for 9-bit word length
    }
    // If wordlength is 8 or any other value, do nothing (remains 8-bit)
}

void Usart5_StopBits(double stopbits) {
    // Reset stop bits configuration
	USART5->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));

    if (fabs(stopbits - 0.5) < 0.00001) { // 0.5 Stop bits
    	USART5->CR2 |= (1 << 12); // Set bit 12
    } else if (fabs(stopbits - 1.0) < 0.00001) { // 1 Stop bit
        // No additional bits set (already cleared)
    } else if (fabs(stopbits - 1.5) < 0.00001) { // 1.5 Stop bits
    	USART5->CR2 |= (1 << 13) | (1 << 12); // Set both bits
    } else if (fabs(stopbits - 2.0) < 0.00001) { // 2 Stop bits
    	USART5->CR2 |= (1 << 13); // Set bit 13
    }
}

void Usart5_SamplingMode(uint8_t samplingmode, uint32_t baudrate)
{
    uint8_t sampling = 16; // Default to 16
    if (samplingmode == 8) {
        sampling = 8;
        USART5->CR1 |= (1 << 15); // Set OVER8 for 8 times oversampling
    } else {
    	USART5->CR1 &= ~(1 << 15); // Clear OVER8 for 16 times oversampling
    }

    double value = (double) getsysclk() / (gethpre() * sampling * baudrate);
    double fracpart, intpart;
    fracpart = modf(value, &intpart);

    USART5->BRR = 0; // Reset BRR
    uint32_t fraction = (sampling == 16) ? round(fracpart * 16) : round(fracpart * 8);
    USART5->BRR |= (uint32_t) fraction; // Set DIV_Fraction
    USART5->BRR |= ((uint32_t) intpart << 4); // Set DIV_Mantissa[11:0]
}

#endif
/*** USART6 ***/
void STM32FXXXUsart6Clock( uint8_t state )
{
	if(state){ RCC->APB2ENR |= (1 << 5); }else{ RCC->APB2ENR &= ~(1 << 5); }
}
void STM32FXXXUsart6Nvic( uint8_t state )
{
	if(state){ set_bit_block(NVIC->ISER, 1, USART6_IRQn, 1); }else{ set_bit_block(NVIC->ICER, 1, USART6_IRQn, 1); }
}
void Usart6_WordLength(uint8_t wordlength) {
    // Clear the M bit to reset word length
	USART6->CR1 &= ~(1 << 12);

    if (wordlength == 9) {
    	USART6->CR1 |= (1 << 12); // Set M bit for 9-bit word length
    }
    // If wordlength is 8 or any other value, do nothing (remains 8-bit)
}

void Usart6_StopBits(double stopbits) {
    // Reset stop bits configuration
	USART6->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));

    if (fabs(stopbits - 0.5) < 0.00001) { // 0.5 Stop bits
    	USART6->CR2 |= (1 << 12); // Set bit 12
    } else if (fabs(stopbits - 1.0) < 0.00001) { // 1 Stop bit
        // No additional bits set (already cleared)
    } else if (fabs(stopbits - 1.5) < 0.00001) { // 1.5 Stop bits
    	USART6->CR2 |= (1 << 13) | (1 << 12); // Set both bits
    } else if (fabs(stopbits - 2.0) < 0.00001) { // 2 Stop bits
    	USART6->CR2 |= (1 << 13); // Set bit 13
    }
}

void Usart6_SamplingMode(uint8_t samplingmode, uint32_t baudrate)
{
    uint8_t sampling = 16; // Default to 16
    if (samplingmode == 8) {
        sampling = 8;
        USART6->CR1 |= (1 << 15); // Set OVER8 for 8 times oversampling
    } else {
    	USART6->CR1 &= ~(1 << 15); // Clear OVER8 for 16 times oversampling
    }

    double value = (double) getsysclk() / (gethpre() * sampling * baudrate);
    double fracpart, intpart;
    fracpart = modf(value, &intpart);

    USART6->BRR = 0; // Reset BRR
    uint32_t fraction = (sampling == 16) ? round(fracpart * 16) : round(fracpart * 8);
    USART6->BRR |= (uint32_t) fraction; // Set DIV_Fraction
    USART6->BRR |= ((uint32_t) intpart << 4); // Set DIV_Mantissa[11:0]
}
/*** USART1 INIC Procedure & Function Definition ***/
void usart1_enable(void)
{
	STM32FXXXUsart1Clock( ON );
	/*** USART1 Bit Mapping Link ***/
	stm32fxxx_usart1.instance = USART1;
	// Other
	stm32fxxx_usart1.clock = STM32FXXXUsart1Clock;
	stm32fxxx_usart1.nvic = STM32FXXXUsart1Nvic;
	stm32fxxx_usart1.wordlength = Usart1_WordLength;
	stm32fxxx_usart1.stopbits = Usart1_StopBits;
	stm32fxxx_usart1.samplingmode = Usart1_SamplingMode;
	//return &stm32fxxx_usart1;
}

STM32FXXX_USART1*  usart1(void){ return (STM32FXXX_USART1*) &stm32fxxx_usart1; }

/*** USART2 INIC Procedure & Function Definition ***/
void usart2_enable(void)
{
	STM32FXXXUsart2Clock( ON );
	/*** USART2 Bit Mapping Link ***/
	stm32fxxx_usart2.instance = USART2;
	// Other
	stm32fxxx_usart2.clock = STM32FXXXUsart2Clock;
	stm32fxxx_usart2.nvic = STM32FXXXUsart2Nvic;
	stm32fxxx_usart2.wordlength = Usart2_WordLength;
	stm32fxxx_usart2.stopbits = Usart2_StopBits;
	stm32fxxx_usart2.samplingmode = Usart2_SamplingMode;
	//return &stm32fxxx_usart2;
}

STM32FXXX_USART2*  usart2(void){ return (STM32FXXX_USART2*) &stm32fxxx_usart2; }

#ifdef STM32F446xx
/*** USART3 INIC Procedure & Function Definition ***/
void usart3_enable(void)
{
	STM32FXXXUsart3Clock( ON );
	/*** USART3 Bit Mapping Link ***/
	#ifdef STM32F446xx
		stm32fxxx_usart3.instance = USART3;
	#else
		stm32fxxx_usart3.instance = NULL;
	#endif
	// Other
	stm32fxxx_usart3.clock = STM32FXXXUsart3Clock;
	stm32fxxx_usart3.nvic = STM32FXXXUsart3Nvic;
	stm32fxxx_usart3.wordlength = Usart3_WordLength;
	stm32fxxx_usart3.stopbits = Usart3_StopBits;
	stm32fxxx_usart3.samplingmode = Usart3_SamplingMode;
	//return &stm32fxxx_usart3;
}

STM32FXXX_USART3*  usart3(void){ return (STM32FXXX_USART3*) &stm32fxxx_usart3; }

/*** UART4 INIC Procedure & Function Definition ***/
void uart4_enable(void)
{
	STM32FXXXUsart4Clock( ON );
	/*** UART4 Bit Mapping Link ***/
	#ifdef STM32F446xx
		stm32fxxx_uart4.instance = UART4;
	#else
		stm32fxxx_uart4.instance = NULL;
	#endif
	// Other
	stm32fxxx_uart4.clock = STM32FXXXUart4Clock;
	stm32fxxx_uart4.nvic = STM32FXXXUart4Nvic;
	stm32fxxx_uart4.wordlength = Usart4_WordLength;
	stm32fxxx_uart4.stopbits = Usart4_StopBits;
	stm32fxxx_uart4.samplingmode = Usart4_SamplingMode;
	//return &stm32fxxx_uart4;
}

STM32FXXX_UART4*  uart4(void){ return (STM32FXXX_UART4*) &stm32fxxx_uart4; }

/*** UART5 INIC Procedure & Function Definition ***/
void uart5_enable(void)
{
	STM32FXXXUsart5Clock( ON );
	/*** UART5 Bit Mapping Link ***/
	#ifdef STM32F446xx
		stm32fxxx_uart5.instance = UART5;
	#else
		stm32fxxx_uart5.instance = NULL;
	#endif
	// Other
	stm32fxxx_uart5.clock = STM32FXXXUart5Clock;
	stm32fxxx_uart5.nvic = STM32FXXXUart5Nvic;
	stm32fxxx_uart5.wordlength = Usart5_WordLength;
	stm32fxxx_uart5.stopbits = Usart5_StopBits;
	stm32fxxx_uart5.samplingmode = Usart5_SamplingMode;
	//return &stm32fxxx_uart5;
}

STM32FXXX_UART5*  uart5(void){ return (STM32FXXX_UART5*) &stm32fxxx_uart5; }

#endif

/*** USART6 INIC Procedure & Function Definition ***/
void usart6_enable(void)
{
	STM32FXXXUsart6Clock( ON );
	/*** USART6 Bit Mapping Link ***/
	stm32fxxx_usart6.instance = USART6;
	// Other
	stm32fxxx_usart6.clock = STM32FXXXUsart6Clock;
	stm32fxxx_usart6.nvic = STM32FXXXUsart6Nvic;
	stm32fxxx_usart6.wordlength = Usart6_WordLength;
	stm32fxxx_usart6.stopbits = Usart6_StopBits;
	stm32fxxx_usart6.samplingmode = Usart6_SamplingMode;
	//return &stm32fxxx_usart6;
}

STM32FXXX_USART6*  usart6(void){ return (STM32FXXX_USART6*) &stm32fxxx_usart6; }

/*** General USART Function Definitions ***/
void Usart_WordLength(USART_TypeDef* usart, uint8_t wordlength) {
    // Clear the M bit to reset word length
    usart->CR1 &= ~(1 << 12);

    if (wordlength == 9) {
        usart->CR1 |= (1 << 12); // Set M bit for 9-bit word length
    }
    // If wordlength is 8 or any other value, do nothing (remains 8-bit)
}

void Usart_StopBits(USART_TypeDef* usart, double stopbits) {
    // Reset stop bits configuration
    usart->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));

    if (fabs(stopbits - 0.5) < 0.00001) { // 0.5 Stop bits
        usart->CR2 |= (1 << 12); // Set bit 12
    } else if (fabs(stopbits - 1.0) < 0.00001) { // 1 Stop bit
        // No additional bits set (already cleared)
    } else if (fabs(stopbits - 1.5) < 0.00001) { // 1.5 Stop bits
        usart->CR2 |= (1 << 13) | (1 << 12); // Set both bits
    } else if (fabs(stopbits - 2.0) < 0.00001) { // 2 Stop bits
        usart->CR2 |= (1 << 13); // Set bit 13
    }
}

void Usart_SamplingMode(USART_TypeDef* usart, uint8_t samplingmode, uint32_t baudrate)
{
    uint8_t sampling = 16; // Default to 16
    if (samplingmode == 8) {
        sampling = 8;
        usart->CR1 |= (1 << 15); // Set OVER8 for 8 times oversampling
    } else {
        usart->CR1 &= ~(1 << 15); // Clear OVER8 for 16 times oversampling
    }

    double value = (double) getsysclk() / (gethpre() * sampling * baudrate);
    double fracpart, intpart;
    fracpart = modf(value, &intpart);

    usart->BRR = 0; // Reset BRR
    uint32_t fraction = (sampling == 16) ? round(fracpart * 16) : round(fracpart * 8);
    usart->BRR |= (uint32_t) fraction; // Set DIV_Fraction
    usart->BRR |= ((uint32_t) intpart << 4); // Set DIV_Mantissa[11:0]
}

/*** EOF ***/

