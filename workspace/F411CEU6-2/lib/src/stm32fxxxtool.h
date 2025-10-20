/***************************************************
	STM32FXXX TOOL
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32FXXX
Update:   07/01/2024
****************************************************/
#pragma once

#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

/*** Define & Macro ***/
#define ZERO 0
#define ONE 1
#define TWO 2
#define NIBBLE_BITS 4
#define BYTE_BITS 8
#define WORD_BITS 16
#define DWORD_BITS 32
#define QWORD_BITS 64

/*******************************************************************/
/****************************** Tools ******************************/
/*******************************************************************/
void set_reg(volatile uint32_t* reg, uint32_t hbits);
void clear_reg(volatile uint32_t* reg, uint32_t hbits);
uint32_t get_reg_Msk_Pos(uint32_t reg, uint32_t Msk, uint32_t Pos);
void write_reg_Msk_Pos(volatile uint32_t* reg, uint32_t Msk, uint32_t Pos, uint32_t data);
void set_reg_Msk_Pos(volatile uint32_t* reg, uint32_t Msk, uint32_t Pos, uint32_t data);
uint32_t get_reg_Msk(uint32_t reg, uint32_t Msk);
void write_reg_Msk(volatile uint32_t* reg, uint32_t Msk, uint32_t data);
void set_reg_Msk(volatile uint32_t* reg, uint32_t Msk, uint32_t data);
uint32_t get_reg_block(uint32_t reg, uint8_t size_block, uint8_t bit_n);
void write_reg_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data);
void set_reg_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data);
uint32_t get_bit_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n);
void set_bit_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data);
// --- Generic helpers ---
uint32_t _reg_get(volatile uint32_t *reg, uint32_t mask);
void _reg_set(volatile uint32_t *reg, uint32_t mask, uint32_t val);
/****************************************/
/*** NULL Check ***/
int isPtrNull(void* ptr);
int isCharPtrFlush(void* ptr);
/*** ADC ***/
float CalculateTemperature(uint16_t adc_value);
/*** Fall Threw Delay ***/
int ftdelayCycles(uint8_t lock_ID, unsigned int n_cycle, void (*execute)(void));
void ftdelayReset(uint8_t ID);
/****************************************/
/***
TypeDef -> Instance -> Handler
bit_n = bit_n % DWORD_BITS; is the same as bit_n = bit_n & (DWORD_BITS - 1);, for power of two numbers.
General behavior for filtering inputs, is if does not pass the filter it is to be ignored and not make
any changes, leaving everything as was. Maybe think later to just give a signal warning.
***/

/*** EOF ***/

