/******************************************************************************
	STM32 XXX USART
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 24022024
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXUSART_H_
	#define _STM32FXXXUSART_H_
/*** Library ***/
#include "stm32fxxxinstance.h"
/*** USART 1..6 Handler TypeDef ***/
// USART -> USART1,2,3,6
typedef struct
{
	/*** Bit Mapping ***/
	USART_TypeDef* instance;
	/*** Other ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
	void (*wordlength)(uint8_t wordlength);
	void (*stopbits)(double stopbits);
	void (*samplingmode)(uint8_t samplingmode, uint32_t baudrate);
}STM32FXXX_USART1, STM32FXXX_USART2, STM32FXXX_USART3, STM32FXXX_USART6;
// USART -> UART4,5
typedef struct
{
	/*** Bit Mapping ***/
	USART_TypeDef* instance;
	/*** Other ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
	void (*wordlength)(uint8_t wordlength);
	void (*stopbits)(double stopbits);
	void (*samplingmode)(uint8_t samplingmode, uint32_t baudrate);
}STM32FXXX_UART4, STM32FXXX_UART5;

void usart1_enable(void);
STM32FXXX_USART1*  usart1(void);

void usart2_enable(void);
STM32FXXX_USART2*  usart2(void);

void usart3_enable(void);
STM32FXXX_USART3*  usart3(void);

void uart4_enable(void);
STM32FXXX_UART4*  uart4(void);

void uart5_enable(void);
STM32FXXX_UART5*  uart5(void);

void usart6_enable(void);
STM32FXXX_USART6*  usart6(void);
/*** USART1 Header ***/
void STM32FXXXUsart1Clock( uint8_t state );
void STM32FXXXUsart1Nvic( uint8_t state );
/*** USART2 Header ***/
void STM32FXXXUsart2Clock( uint8_t state );
void STM32FXXXUsart2Nvic( uint8_t state );
/*** USART3 Header ***/
void STM32FXXXUsart3Clock( uint8_t state );
void STM32FXXXUsart3Nvic( uint8_t state );
/*** UART4 Header ***/
void STM32FXXXUart4Clock( uint8_t state );
void STM32FXXXUart4Nvic( uint8_t state );
/*** UART5 Header ***/
void STM32FXXXUart5Clock( uint8_t state );
void STM32FXXXUart5Nvic( uint8_t state );
/*** USART6 Header ***/
void STM32FXXXUsart6Clock( uint8_t state );
void STM32FXXXUsart6Nvic( uint8_t state );
/*** General USART Function Prototypes ***/
void Usart_WordLength( USART_TypeDef* usart, uint8_t wordlength );
void Usart_StopBits( USART_TypeDef* usart, double stopbits );
void Usart_SamplingMode( USART_TypeDef* usart, uint8_t samplingmode, uint32_t baudrate);
/*** INTERRUPT HEADER ***/
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
void UART4_IRQHandler(void);
void UART5_IRQHandler(void);
void USART6_IRQHandler(void);

#endif
/*** EOF ***/

/******
1º Sequence
2º Scope
	- Library Scope
	- File Scope
	- Function Scope
	- Precedence Scope
3º Pointer and Variable
4º Casting
******/

