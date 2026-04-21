/************************************************************************
	STM32FXXX INSTANCE
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32FXXX
Update: 07/01/2024
Comment:
	
************************************************************************/
#pragma once

/************ CMSIS BASE *************/
// SELECTION OF CHIP (CMSIS Access to its libraries)
// Options: __STM32F446xx_H    __STM32F411xE_H
#include "stm32f4xx.h"
#include <inttypes.h>
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
#define ON 1
#define OFF 0
/*******   0 -> HSI    1->HSE   *********/
#define H_Clock_Source 1
/****************************************/
/****   PLL ON -> 1    PLL OFF = 0   ****/
#define PLL_ON_OFF 0
/****************************************/
typedef union{
	struct UN32nibble{
		uint32_t n0:4;
		uint32_t n1:4;
		uint32_t n2:4;
		uint32_t n3:4;
		uint32_t n4:4;
		uint32_t n5:4;
		uint32_t n6:4;
		uint32_t n7:4;
	}nibble;
	struct UN32byte{
		uint8_t b0;
		uint8_t b1;
		uint8_t b2;
		uint8_t b3;
	}byte;
	struct UN32word{
		uint16_t w0;
		uint16_t w1;
	}word;
	uint32_t n;
}_UN32var;
typedef union{
	struct UN64nibble{
		uint32_t n0:4;
		uint32_t n1:4;
		uint32_t n2:4;
		uint32_t n3:4;
		uint32_t n4:4;
		uint32_t n5:4;
		uint32_t n6:4;
		uint32_t n7:4;
		uint32_t n8:4;
		uint32_t n9:4;
		uint32_t n10:4;
		uint32_t n11:4;
		uint32_t n12:4;
		uint32_t n13:4;
		uint32_t n14:4;
		uint32_t n15:4;
	}nibble;
	struct UN64byte{
		uint8_t b0;
		uint8_t b1;
		uint8_t b2;
		uint8_t b3;
		uint8_t b4;
		uint8_t b5;
		uint8_t b6;
		uint8_t b7;
	}byte;
	struct UN64word{
		uint16_t w0;
		uint16_t w1;
		uint16_t w2;
		uint16_t w3;
	}word;
	struct UN64dword{
		uint32_t d0;
		uint32_t d1;
	}dword;
	uint64_t n;
}_UN64var;

/*** Tools ***/
void set_reg(volatile uint32_t* reg, uint32_t hbits);
void clear_reg(volatile uint32_t* reg, uint32_t hbits);
uint32_t get_reg_Msk(uint32_t reg, uint32_t Msk, uint8_t Pos);
void write_reg_Msk(volatile uint32_t* reg, uint32_t Msk, uint8_t Pos, uint32_t data);
void set_reg_Msk(volatile uint32_t* reg, uint32_t Msk, uint8_t Pos, uint32_t data);
void set_hpins( GPIO_TypeDef* reg, uint16_t hpins );
void clear_hpins( GPIO_TypeDef* reg, uint16_t hpins );
void set_pin( GPIO_TypeDef* reg, uint8_t pin );
void clear_pin( GPIO_TypeDef* reg, uint8_t pin );
uint32_t get_reg_block(uint32_t reg, uint8_t size_block, uint8_t bit_n);
void write_reg_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data);
void set_reg_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data);
uint32_t get_bit_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n);
void set_bit_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data);

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
/*** FPU ***/
void enable_fpu(void);

/***

***/

/*** EOF ***/

