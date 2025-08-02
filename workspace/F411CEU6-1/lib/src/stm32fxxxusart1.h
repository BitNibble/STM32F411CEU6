/******************************************************************************
	STM32 XXX USART1
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     24022024
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXUSART1_H_
	#define _STM32FXXXUSART1_H_

/*** Library ***/
#include "stm32fxxxinstance.h"
/*** Define and Macros ***/
#define USART1_RX_BUFFER_SIZE 2049
#define USART1_TX_BUFFER_SIZE 2049
/*** USART 1..6 Handler TypeDef ***/
// USART -> USART1
typedef struct
{
	char* rxbuff;
	char* txbuff;
	/*** Bit Mapping ***/
	USART_TypeDef* instance;
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
	// CALLBACK
	void (*callback_cts)(void);
	void (*callback_lbd)(void);
	void (*callback_txe)(void);
	void (*callback_tc)(void);
	void (*callback_rxne)(void);
	void (*callback_idle)(void);
	void (*callback_ore)(void);
	void (*callback_ne)(void);
	void (*callback_fe)(void);
	void (*callback_pe)(void);
}STM32FXXX_USART1;

STM32FXXX_USART1*  usart1(void);

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

