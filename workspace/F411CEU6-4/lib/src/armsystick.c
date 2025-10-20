/******************************************************************************
	STM32 XXX systick
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Update:   16012024
*******************************************************************************/
#include "armsystick.h"
#if defined (STM32F411xE)
	#include "stm32f411ceu6.h"
#elif defined(STM32F446xx)
	#include "stm32f446re.h"
#endif
#include <stdio.h>
#include <string.h>
/******/
#define SYSTICK_ENABLE (1 << 0)
#define SYSTICK_TICKINT (1 << 1)
#define SYSTICK_CLKSOURCE (1 << 2)
/******/
static uint32_t systick_us = 0;
static uint32_t systick_10us = 0;
static uint32_t systick_100us = 0;
static uint32_t systick_ms = 0;
volatile uint32_t DelayCounter_0 = 0;
/******/
void delay_Configure(void)
{
    uint32_t DelayCounter_top;
    // Calculate DelayCounter_top once for both STM32 families
    DelayCounter_top = get_sysclk() / get_hpre(); // Assuming get_hpre() returns a valid pre-scaler
    // Calculate the SysTick values for different delay intervals
    systick_us 		= DelayCounter_top / 1000000 - 1 ; // 1 microsecond
    systick_10us 	= DelayCounter_top / 100000 - 1 ;  // 10 microseconds
    systick_100us 	= DelayCounter_top / 10000 - 1 ;   // 100 microseconds
    systick_ms 		= DelayCounter_top / 1000 - 1 ;    // 1 millisecond
    if(systick_us > 0);else systick_us = 70;
    if(systick_10us > 0);else systick_10us = 70;
    if(systick_100us > 0);else systick_100us = 70;
    if(systick_ms > 0);else systick_ms = 70;
}
inline uint32_t get_systick_us(void)
{
	return systick_us;
}
inline uint32_t get_systick_10us(void)
{
	return systick_10us;
}
inline uint32_t get_systick_ms(void)
{
	return systick_ms;
}
void delayMiliseconds(unsigned int ms) {
    volatile unsigned int count = ms * get_systick_ms( );
    while (count--);
}
void delayMicroseconds(unsigned int us) {
    volatile unsigned int count = us * get_systick_us( );
    while (count--);
}
void delayAsmMicroseconds(unsigned int us) {
    // Adjust the loop count accordingly
    unsigned int count = us * get_systick_us( ); // Rough estimate for timing

    __asm volatile (
        "1: \n"                    // Label 1
        "subs %[count], %[count], #1 \n" // Decrement count
        "bne 1b \n"                // Branch to label 1 if count is not zero
        : [count] "+r" (count)     // Input/output operand
    );
}
/******/
void _delay_us(uint32_t us)
{
	SysTick->CTRL &= (uint32_t) ~SYSTICK_ENABLE;
	SysTick->LOAD = get_systick_us( );
	for( DelayCounter_0 = 0, SysTick->CTRL |= SYSTICK_ENABLE; DelayCounter_0 < us; );
}
void _delay_10us(uint32_t dez_us)
{
	SysTick->CTRL &= (uint32_t) ~SYSTICK_ENABLE;
	SysTick->LOAD = get_systick_10us( );
	for( DelayCounter_0 = 0, SysTick->CTRL |= SYSTICK_ENABLE; DelayCounter_0 < dez_us; );
}
void _delay_ms(uint32_t ms)
{
	SysTick->CTRL &= (uint32_t) ~SYSTICK_ENABLE;
	SysTick->LOAD = get_systick_ms( );
	for( DelayCounter_0 = 0, SysTick->CTRL |= SYSTICK_ENABLE; DelayCounter_0 < ms; );
}
/******/
void systick_start(void)
{
	delay_Configure( );
	/******/
	SysTick->LOAD = 0x00FFFFFF;
	SysTick->VAL = 0UL;
	SysTick->CTRL |= (SYSTICK_TICKINT | SYSTICK_CLKSOURCE);
	SysTick->CTRL |= SYSTICK_ENABLE;
}
/**** Interrupt Handler ****/
void SysTick_Inc(void)
{
	DelayCounter_0++;
}
/***************************/

/******
Load does not accept values below 70
Note 'us' only work for high frequency clocks.

******/

/*** EOF ***/

