#include "armsystick.h"
#include "stm32f4xx.h"  // adjust to your STM32 variant

static volatile uint32_t tick_ms = 0;
static uint32_t ticks_per_us = 0;   // number of SysTick ticks per microsecond

void systick_init(uint32_t sysclk_hz)
{
    // SysTick counts down from LOAD to 0
    // 1 tick = 1 CPU clock cycle if CLKSOURCE = processor clock
    SysTick->CTRL = 0;                // disable SysTick
    SysTick->VAL  = 0;                // clear current value
    ticks_per_us  = sysclk_hz / 1000000UL;

    SysTick->LOAD = 0x00FFFFFF;       // max reload
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | 
                    SysTick_CTRL_TICKINT_Msk | 
                    SysTick_CTRL_ENABLE_Msk;
}

/*** Retrieve current microseconds ***/
uint32_t micros(void)
{
    uint32_t ms;
    uint32_t sysval;
    
    // disable interrupts briefly to read consistent values
    __disable_irq();
    ms = tick_ms;
    sysval = SysTick->VAL;
    __enable_irq();

    // calculate elapsed us in current millisecond
    uint32_t us = ms * 1000UL + (ticks_per_us ? (SysTick->LOAD - sysval) / ticks_per_us : 0);
    return us;
}

/*** Retrieve current milliseconds ***/
uint32_t millis(void)
{
    return tick_ms;
}

/*** Delay for microseconds (blocking) ***/
void delay_us(uint32_t us)
{
    if(us == 0) return;

    uint32_t start = micros();
    while ((micros() - start) < us);
}

/*** Delay for milliseconds (blocking) ***/
void delay_ms(uint32_t ms)
{
    if(ms == 0) return;

    uint32_t start = millis();
    while ((millis() - start) < ms);
}

/*** SysTick interrupt handler ***/
void SysTick_Handler(void)
{
    tick_ms++;
}

void _delay_us(uint32_t us)
{
    if(us == 0) return;

    // For very short delays, use inline assembly busy-wait
    if(us < 10) {
        // Rough estimate: 1 iteration ≈ 1 CPU cycle, adjust if needed
        volatile uint32_t count = us * 10; // tuning factor depends on CPU freq
        __asm volatile (
            "1: \n"
            "subs %[c], %[c], #1 \n"
            "bne 1b \n"
            : [c] "+r" (count)
        );
        return;
    }

    // For longer delays, use SysTick-based timing
    uint32_t start = micros();
    while((micros() - start) < us);
}
