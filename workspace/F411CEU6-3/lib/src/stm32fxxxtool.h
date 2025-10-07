/***************************************************
    STM32FXXX TOOLS
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32FXXX
Update:   2025-10-02
****************************************************/
#pragma once

#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <math.h>
#include <stdarg.h>

/*** Define & Macro ***/
#define TWO 2
#define NIBBLE_BITS 4
#define BYTE_BITS 8
#define WORD_BITS 16
#define DWORD_BITS 32
#define QWORD_BITS 64

/****************************************/
/*** Fall Through Delay Arrays ***/
#define FTDELAY_SIZE 256

// Prototypes (no static state here)
int ftdelayCycles(uint8_t lock_ID, unsigned int n_cycle, void (*execute)(void));
void ftdelayReset(uint8_t ID);

/*** Helper: bit mask / position ***/
static inline uint32_t size_to_block(uint32_t size_block) {
    return (size_block >= 32) ? 0xFFFFFFFFU : ((1U << size_block) - 1);
}

static inline uint32_t block_to_size(uint32_t block) {
    return (block == 0) ? 0 : (32 - __builtin_clz(block));
}

static inline uint32_t get_Msk(uint32_t size_block, uint32_t Pos){
    return size_to_block(size_block) << Pos;
}

static inline uint32_t get_Pos(uint32_t size_block, uint32_t block_n){
    return size_block * block_n;
}

static inline uint32_t Msk_Pos(uint32_t Msk){
    return (Msk == 0) ? 0 : __builtin_ctz(Msk);
}

/****************************************/
/*** Register access helpers ***/
static inline void set_reg(volatile uint32_t* reg, uint32_t hbits) {
    *reg |= hbits;
}

static inline void clear_reg(volatile uint32_t* reg, uint32_t hbits) {
    *reg &= ~hbits;
}

static inline uint32_t get_reg_Msk(uint32_t reg, uint32_t Msk) {
    return (reg & Msk) >> Msk_Pos(Msk);
}

static inline void write_reg_Msk(volatile uint32_t* reg, uint32_t Msk, uint32_t data) {
    uint32_t pos = Msk_Pos(Msk);
    *reg = (*reg & ~Msk) | ((data << pos) & Msk);
}

static inline void set_reg_Msk(volatile uint32_t* reg, uint32_t Msk, uint32_t data) {
    write_reg_Msk(reg, Msk, data);  // reuse implementation
}

/*** Block access within a 32-bit register ***/
static inline uint32_t get_reg_block(uint32_t reg, uint8_t size_block, uint8_t bit_n) {
    if(bit_n < DWORD_BITS && size_block != 0 && bit_n + size_block <= DWORD_BITS) {
        uint32_t mask = size_to_block(size_block) << bit_n;
        reg = (reg & mask) >> bit_n;
    }
    return reg;
}

static inline void write_reg_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data) {
    if(bit_n < DWORD_BITS && size_block != 0 && bit_n + size_block <= DWORD_BITS) {
        uint32_t mask = size_to_block(size_block) << bit_n;
        *reg = (*reg & ~mask) | ((data & size_to_block(size_block)) << bit_n);
    }
}

static inline void set_reg_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data) {
    write_reg_block(reg, size_block, bit_n, data);
}

/*** Multi-word bit block access ***/
static inline uint32_t get_bit_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n) {
    uint32_t n = bit_n / DWORD_BITS;
    bit_n %= DWORD_BITS;
    uint32_t value = *(reg + n);
    if(size_block != 0 && bit_n + size_block <= DWORD_BITS) {
        uint32_t mask = size_to_block(size_block) << bit_n;
        value = (value & mask) >> bit_n;
    }
    return value;
}

static inline void set_bit_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data) {
    uint32_t n = bit_n / DWORD_BITS;
    bit_n %= DWORD_BITS;
    if(size_block != 0 && bit_n + size_block <= DWORD_BITS) {
        uint32_t mask = size_to_block(size_block);
        *(reg + n) = (*(reg + n) & ~(mask << bit_n)) | ((data & mask) << bit_n);
    }
}

/*** Generic helpers ***/
static inline unsigned _mask_pos(uint32_t mask) {
    return (mask == 0) ? 0 : __builtin_ctz(mask);
}

static inline uint32_t _reg_get(volatile uint32_t *reg, uint32_t mask) {
    return (*reg & mask) >> _mask_pos(mask);
}

static inline void _reg_set(volatile uint32_t *reg, uint32_t mask, uint32_t val) {
    *reg = (*reg & ~mask) | ((val << _mask_pos(mask)) & mask);
}

/****************************************/
/*** Vector setup helper ***/
static inline void STM32446VecSetup(volatile uint32_t vec[], unsigned int size_block, unsigned int block_n, unsigned int data) {
    const unsigned int n_bits = sizeof(data) * BYTE_BITS;
    if(size_block > n_bits) size_block = n_bits;
    unsigned int index = get_Pos(size_block, block_n) / n_bits;
    unsigned int shift = get_Pos(size_block, block_n) % n_bits;
    unsigned int mask = size_to_block(size_block);
    data &= mask;
    vec[index] &= ~(mask << shift);
    vec[index] |= (data << shift);
}

/****************************************/
/*** NULL checks ***/
static inline int isPtrNull(void* ptr) {
    return ptr == NULL;
}

static inline int isCharPtrFlush(void* ptr) {
    if(!ptr) return 1;  // safe check
    return *((unsigned char*)ptr) == 0;
}

/*** ADC temperature calculation ***/
static inline float CalculateTemperature(uint16_t adc_value) {
    const float V_25 = 0.76f;
    const float Avg_slope = 0.0025f;
    const float V_ref = 3.3f;

    float V_sense = ((float)adc_value / 4096.0f) * V_ref;
    return ((V_sense - V_25) / Avg_slope) + 25.0f;
}

/*** EOF ***/


