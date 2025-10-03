#ifndef _ARMSYSTICK_H_
#define _ARMSYSTICK_H_

#include <stdint.h>

/*** Initialization ***/
void systick_init(uint32_t sysclk_hz);

/*** Time retrieval ***/
uint32_t micros(void);
uint32_t millis(void);

/*** Blocking delays ***/
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);

/*** SysTick handler for ISR integration ***/
void SysTick_Handler(void);

#endif
