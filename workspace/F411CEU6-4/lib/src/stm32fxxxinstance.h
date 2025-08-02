/***************************************************
	STM32FXXX INSTANCE
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32FXXX
Update:   07/01/2024
Comment:
(root)		MAIN HEADER FILE!
****************************************************/
#pragma once

/******************* CMSIS BASE ********************/
// SELECTION OF CHIP (CMSIS Access to its libraries)
/*** Options: __STM32F446xx_H    __STM32F411xE_H ***/
#include "stm32f4xx.h"
/**************** START *****************/
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
/****************************************/
/*** File Constant & Macro ***/
#ifndef HSI_RC
	#define HSI_RC 16000000UL
#endif
#ifndef HSE_OSC
	#define HSE_OSC 25000000UL
#endif
#ifndef LSI
	#define LSI 32000UL
#endif
#ifndef LSE
	#define LSE 32768UL
#endif
#ifndef HSE_RTC
	#define HSE_RTC 4000000UL
#endif
#ifndef OFF
	#define OFF 0
#endif
#ifndef ZERO
	#define ZERO 0
#endif
#ifndef ON
	#define ON 1
#endif
#ifndef ONE
	#define ONE 1
#endif
#define TWO 2
#define NIBBLE_BITS 4
#define BYTE_BITS 8
#define WORD_BITS 16
#define DWORD_BITS 32
#define QWORD_BITS 64
/****************************************/
/*******   0 -> HSI    1->HSE   *********/
#define H_Clock_Source 1
/****************************************/
/****   PLL ON -> 1    PLL OFF = 0   ****/
#define PLL_ON_OFF 0
/****************************************/
typedef union{
	struct UN8bit{
		uint8_t p0:1;
		uint8_t p1:1;
		uint8_t p2:1;
		uint8_t p3:1;
		uint8_t p4:1;
		uint8_t p5:1;
		uint8_t p6:1;
		uint8_t p7:1;
	}bit;
	struct UN8nibble{
		uint8_t n0:4;
		uint8_t n1:4;
	}nibble;
	uint8_t un8;
}_UN8var;
typedef union{
	struct UN16byte{
		uint8_t b0;
		uint8_t b1;
	}byte;
	uint16_t un16;
}_UN16var;
typedef union{
	struct UN32word{
		uint16_t w0;
		uint16_t w1;
	}word;
	uint32_t un32;
}_UN32var;
typedef union{
	struct UN64dword{
		uint32_t dw0;
		uint32_t dw1;
	}dword;
	uint64_t un64;
}_UN64var;
/****************************************/
/*** Tools ***/
void set_reg(volatile uint32_t* reg, uint32_t hbits);
void clear_reg(volatile uint32_t* reg, uint32_t hbits);
uint32_t get_reg_Msk(uint32_t reg, uint32_t Msk);
void write_reg_Msk(volatile uint32_t* reg, uint32_t Msk, uint32_t data);
void set_reg_Msk(volatile uint32_t* reg, uint32_t Msk, uint32_t data);
uint32_t get_reg_block(uint32_t reg, uint8_t size_block, uint8_t bit_n);
void write_reg_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data);
void set_reg_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data);
uint32_t get_bit_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n);
void set_bit_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data);
// IO
void set_hpins( GPIO_TypeDef* reg, uint16_t hpins );
void clear_hpins( GPIO_TypeDef* reg, uint16_t hpins );
void set_pin( GPIO_TypeDef* reg, uint8_t pin );
void clear_pin( GPIO_TypeDef* reg, uint8_t pin );
/****************************************/
/****** MISCELLANEOUS ******/
/*** Clock ***/
uint32_t getpllsourceclk(void);
/*** -----> ***/
// HSI
// HSE
uint32_t getpllclk(void);
/*** -----> ***/
uint32_t getsysclk(void);
uint32_t gethclk(void);
uint32_t getpclk1(void);
uint32_t getpclk2(void);
/*** Scaler ***/
uint16_t gethpre(void);
uint8_t gethppre1(void);
uint8_t gethppre2(void);
uint8_t getrtcpre(void);
uint8_t gethmco1pre(void);
uint8_t gethmco2pre(void);
uint8_t getpllm(void);
uint16_t getplln(void);
uint8_t getpllp(void);
uint8_t getpllq(void);
uint8_t getpllr(void);
/****************************************/
/*** NULL Check ***/
int isPtrNull(void* ptr);
int isCharPtrFlush(void* ptr);
/*** FPU ***/
void fpu_enable(void);
/*** ADC ***/
float CalculateTemperature(uint16_t adc_value);
/*** General USART Function Prototypes ***/
void Usart_WordLength( USART_TypeDef* usart, uint8_t wordlength );
void Usart_StopBits( USART_TypeDef* usart, double stopbits );
void Usart_SamplingMode( USART_TypeDef* usart, uint8_t samplingmode, uint32_t baudrate);
/*** Fall Threw Delay ***/
int ftdelayCycles(uint8_t lock_ID, unsigned int n_cycle);
void ftdelayReset(uint8_t ID);
/****************************************/
/***
TypeDef -> Instance -> Handler
bit_n = bit_n % DWORD_BITS; is the same as bit_n = bit_n & (DWORD_BITS - 1);, for power of two numbers.
General behavior for filtering inputs, is if does not pass the filter it is to be ignored and not make
any changes, leaving everything as was. Maybe think later to just give a signal warning.
***/

/*** EOF ***/

