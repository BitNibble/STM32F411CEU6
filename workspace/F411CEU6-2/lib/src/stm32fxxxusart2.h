/******************************************************************************
	STM32 XXX USART2
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     24022024
*******************************************************************************/
#ifndef _STM32FXXXUSART2_H_
	#define _STM32FXXXUSART2_H_

/*** Library ***/
//#if defined (STM32F411xE)
	#include "stm32f411ceu6.h"
//#elif defined(STM32F446xx)
//	#include "stm32f446re.h"
//#else
//	void* dev(void){ return NULL; }
//#endif
/*** Define and Macros ***/
#define USART2_RX_BUFFER_SIZE 2049
#define USART2_TX_BUFFER_SIZE 2049
/*** USART 2 Callback TypeDef ***/
typedef struct {
	void (*cts)(void);
	void (*lbd)(void);
	void (*txe)(void);
	void (*tc)(void);
	void (*rxne)(void);
	void (*idle)(void);
	void (*ore)(void);
	void (*ne)(void);
	void (*fe)(void);
	void (*pe)(void);
}STM32FXXX_USART2_CallBack;
/*** USART 2 Handler TypeDef ***/
typedef const struct {
	char* rxbuff;
	char* txbuff;
	/*** Callback ***/
	STM32FXXX_USART2_CallBack* callback;
	/*** Clock and Nvic ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
	/*** Other ***/
	void (*wordlength)(uint8_t wordlength);
	void (*stopbits)(double stopbits);
	void (*samplingmode)(uint8_t samplingmode, uint32_t baudrate);
	uint32_t (*is_tx_complete)( void );
	uint32_t (*is_rx_idle)( void );
	void (*tx)( uint8_t state );
	void (*rx)( uint8_t state );
	void (*tx_einterrupt)( uint8_t state );
	void (*rx_neinterrupt)( uint8_t state );
	void (*transmit_char)(char c);
	char (*receive_char)(void);
	void (*rx_flush)(void);
	void (*rx_purge)(void);
	void (*transmit_string)(const char *str);
	void (*receive_string)(char* oneshot, char* rx, size_t size, const char* endl);
	void (*receive_rxstring)(char* rx, size_t size, const char* endl);
	void (*start)(void);
	void (*stop)(void);

#if defined(STM32F411CEU6_H)
	STM32F411CEU6_Instance* (*dev)(void);
#elif defined(STM32F446RE_H)
	STM32F446RE_Instance* (*dev)(void);
#else
	void* (*dev)(void);
#endif
}STM32FXXX_USART2_Handler;

STM32FXXX_USART2_Handler*  usart2(void);

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

