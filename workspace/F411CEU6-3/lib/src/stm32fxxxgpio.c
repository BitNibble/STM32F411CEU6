/******************************************************************************
	STM32 XXX GPIO
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     19/06/2023
Update:   28/02/2024
Comment:
	File Vars, File Function Header, Library Function Definitions.
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxgpio.h"
#include <math.h>

/*** GPIOA Procedure & Function Definition ***/
void GPIOA_clock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOAEN_Pos);
    } else {
        RCC->AHB1ENR &= ~(1 << RCC_AHB1ENR_GPIOAEN_Pos);
    }
}
void GPIOA_moder( uint8_t pin, uint8_t mode )
{
	if(pin < WORD_BITS && mode < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t Pos = pin * BLOCK_SIZE;
		mode &= MASK;
		GPIOA->MODER &= ~(MASK << Pos);
		GPIOA->MODER |= (mode << Pos);
	}
}
void GPIOA_otype(uint8_t pin, uint8_t otype)
{
    if(pin < WORD_BITS && otype < TWO){
    	GPIOA->OTYPER &= ~(1 << pin);
    	GPIOA->OTYPER |= ( otype << pin );
    }
}
void GPIOA_ospeed(uint8_t pin, uint8_t ospeed)
{
	if(pin < WORD_BITS && ospeed < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint16_t Pos = (pin * BLOCK_SIZE);
		ospeed &= MASK;
		GPIOA->OSPEEDR &= ~( MASK << Pos );
		GPIOA->OSPEEDR |= ( ospeed << Pos );
	}
}
void GPIOA_pupd(uint8_t pin, uint8_t pupd)
{
	if(pin < WORD_BITS && pupd < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint16_t Pos = (pin * BLOCK_SIZE);
		pupd &= MASK;
		GPIOA->PUPDR &= ~( MASK << Pos );
		GPIOA->PUPDR |= ( pupd << Pos );
	}
}
void GPIOA_set_hpins(uint16_t hpins)
{
	GPIOA->BSRR = (uint32_t)hpins;
}
void GPIOA_clear_hpins(uint16_t hpins)
{
	GPIOA->BSRR = (uint32_t)(hpins << WORD_BITS);
}
void GPIOA_lck(uint16_t hpins){
	GPIOA->LCKR = hpins;
	for(uint8_t status = TWO; status; ) {
		if(GPIOA->LCKR & (1 << WORD_BITS)) {
			status = 0;
		}else {
			GPIOA->LCKR |= 1 << WORD_BITS;
			GPIOA->LCKR &= ~(1 << WORD_BITS);
			GPIOA->LCKR |= 1 << WORD_BITS;
			(void)GPIOA->LCKR;
			status--;
		}
	}

}
void GPIOA_af(uint8_t pin, uint8_t af)
{
	if(pin < WORD_BITS && af < WORD_BITS){
		const uint8_t BLOCK_SIZE = NIBBLE_BITS;
    	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    	const uint8_t index = (pin * BLOCK_SIZE) / DWORD_BITS;
    	const uint16_t Pos = (pin * BLOCK_SIZE) % DWORD_BITS;

    	af &= MASK;
    	if(index < TWO){
    		GPIOA->AFR[index] &= ~( MASK << Pos );
    		GPIOA->AFR[index] |= ( af << Pos );
    	}
	}
}

/*** HANDLER ***/
static STM32FXXX_GPIOA_Handler stm32fxxx_gpioa_setup = {
    // V-table
    .clock = GPIOA_clock,
    .moder = GPIOA_moder,
    .otype = GPIOA_otype,
    .ospeed = GPIOA_ospeed,
    .pupd = GPIOA_pupd,
    .set_hpins = GPIOA_set_hpins,
    .clear_hpins = GPIOA_clear_hpins,
    .lck = GPIOA_lck,
    .af = GPIOA_af
};

STM32FXXX_GPIOA_Handler* gpioa(void) { return &stm32fxxx_gpioa_setup; }

/*** GPIOB ***/
void GPIOB_clock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOBEN_Pos);
    } else {
        RCC->AHB1ENR &= ~(1 << RCC_AHB1ENR_GPIOBEN_Pos);
    }
}
void GPIOB_moder( uint8_t pin, uint8_t mode )
{
	if(pin < WORD_BITS && mode < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t Pos = pin * BLOCK_SIZE;
		mode &= MASK;
		GPIOB->MODER &= ~(MASK << Pos);
		GPIOB->MODER |= (mode << Pos);
	}
}
void GPIOB_otype(uint8_t pin, uint8_t otype)
{
	if(pin < WORD_BITS && otype < TWO){
		GPIOB->OTYPER &= ~(1 << pin);
		GPIOB->OTYPER |= ( otype << pin );
	}
}
void GPIOB_ospeed(uint8_t pin, uint8_t ospeed)
{
	if(pin < WORD_BITS && ospeed < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
    	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    	const uint16_t Pos = (pin * BLOCK_SIZE);
    	ospeed &= MASK;
    	GPIOB->OSPEEDR &= ~( MASK << Pos );
    	GPIOB->OSPEEDR |= ( ospeed << Pos );
	}
}
void GPIOB_pupd(uint8_t pin, uint8_t pupd)
{
	if(pin < WORD_BITS && pupd < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
    	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    	const uint16_t Pos = (pin * BLOCK_SIZE);
    	pupd &= MASK;
    	GPIOB->PUPDR &= ~( MASK << Pos );
    	GPIOB->PUPDR |= ( pupd << Pos );
	}
}
void GPIOB_set_hpins(uint16_t hpins)
{
	GPIOB->BSRR = (uint32_t)hpins;
}
void GPIOB_clear_hpins(uint16_t hpins)
{
	GPIOB->BSRR = (uint32_t)(hpins << WORD_BITS);
}
void GPIOB_lck(uint16_t hpins){
	GPIOB->LCKR = hpins;
	for(uint8_t status = TWO; status; ) {
		if(GPIOB->LCKR & (1 << WORD_BITS)) {
			status = 0;
		}else {
			GPIOB->LCKR |= 1 << WORD_BITS;
			GPIOB->LCKR &= ~(1 << WORD_BITS);
			GPIOB->LCKR |= 1 << WORD_BITS;
			(void)GPIOB->LCKR;
			status--;
		}
	}
}
void GPIOB_af(uint8_t pin, uint8_t af)
{
	if(pin < WORD_BITS && af < WORD_BITS){
		const uint8_t BLOCK_SIZE = NIBBLE_BITS;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t index = (pin * BLOCK_SIZE) / DWORD_BITS;
		const uint16_t Pos = (pin * BLOCK_SIZE) % DWORD_BITS;

		af &= MASK;
		if(index < TWO){
			GPIOB->AFR[index] &= ~( MASK << Pos );
	    	GPIOB->AFR[index] |= ( af << Pos );
		}
	}
}

/*** HANDLER ***/
static STM32FXXX_GPIOB_Handler stm32fxxx_gpiob_setup = {
    // V-table
    .clock = GPIOB_clock,
    .moder = GPIOB_moder,
    .otype = GPIOB_otype,
    .ospeed = GPIOB_ospeed,
    .pupd = GPIOB_pupd,
    .set_hpins = GPIOB_set_hpins,
    .clear_hpins = GPIOB_clear_hpins,
    .lck = GPIOB_lck,
    .af = GPIOB_af
};

STM32FXXX_GPIOB_Handler* gpiob(void) { return &stm32fxxx_gpiob_setup; }

/*** GPIOC ***/
void GPIOC_clock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOCEN_Pos);
    } else {
        RCC->AHB1ENR &= ~(1 << RCC_AHB1ENR_GPIOCEN_Pos);
    }
}
void GPIOC_moder( uint8_t pin, uint8_t mode )
{
	if(pin < WORD_BITS && mode < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t Pos = pin * BLOCK_SIZE;
		mode &= MASK;
		GPIOC->MODER &= ~(MASK << Pos);
		GPIOC->MODER |= (mode << Pos);
	}
}
void GPIOC_otype(uint8_t pin, uint8_t otype)
{
	if(pin < WORD_BITS && otype < TWO){
		GPIOC->OTYPER &= ~(1 << pin);
    	GPIOC->OTYPER |= ( otype << pin );
	}
}
void GPIOC_ospeed(uint8_t pin, uint8_t ospeed)
{
	if(pin < WORD_BITS && ospeed < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
    	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    	const uint16_t Pos = (pin * BLOCK_SIZE);
    	ospeed &= MASK;
    	GPIOC->OSPEEDR &= ~( MASK << Pos );
    	GPIOC->OSPEEDR |= ( ospeed << Pos );
	}
}
void GPIOC_pupd(uint8_t pin, uint8_t pupd)
{
	if(pin < WORD_BITS && pupd < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
    	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    	const uint16_t Pos = (pin * BLOCK_SIZE);
    	pupd &= MASK;
    	GPIOC->PUPDR &= ~( MASK << Pos );
    	GPIOC->PUPDR |= ( pupd << Pos );
	}
}
void GPIOC_set_hpins(uint16_t hpins)
{
	GPIOC->BSRR = (uint32_t)hpins;
}
void GPIOC_clear_hpins(uint16_t hpins)
{
	GPIOC->BSRR = (uint32_t)(hpins << WORD_BITS);
}
void GPIOC_lck(uint16_t hpins){
	GPIOC->LCKR = hpins;
	for(uint8_t status = TWO; status; ) {
		if(GPIOC->LCKR & (1 << WORD_BITS)) {
			status = 0;
		}else {
			GPIOC->LCKR |= 1 << WORD_BITS;
			GPIOC->LCKR &= ~(1 << WORD_BITS);
			GPIOC->LCKR |= 1 << WORD_BITS;
			(void)GPIOC->LCKR;
			status--;
		}
	}

}
void GPIOC_af(uint8_t pin, uint8_t af)
{
	if(pin < WORD_BITS && af < WORD_BITS){
		const uint8_t BLOCK_SIZE = NIBBLE_BITS;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t index = (pin * BLOCK_SIZE) / DWORD_BITS;
		const uint16_t Pos = (pin * BLOCK_SIZE) % DWORD_BITS;

		af &= MASK;
		if(index < TWO){
			GPIOC->AFR[index] &= ~( MASK << Pos );
	    	GPIOC->AFR[index] |= ( af << Pos );
		}
	}
}

/*** HANDLER ***/
static STM32FXXX_GPIOC_Handler stm32fxxx_gpioc_setup = {
    // V-table
    .clock = GPIOC_clock,
    .moder = GPIOC_moder,
    .otype = GPIOC_otype,
    .ospeed = GPIOC_ospeed,
    .pupd = GPIOC_pupd,
    .set_hpins = GPIOC_set_hpins,
    .clear_hpins = GPIOC_clear_hpins,
    .lck = GPIOC_lck,
    .af = GPIOC_af
};

STM32FXXX_GPIOC_Handler* gpioc(void) { return &stm32fxxx_gpioc_setup; }

/*** GPIOD ***/
void GPIOD_clock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIODEN_Pos);
    } else {
        RCC->AHB1ENR &= ~(1 << RCC_AHB1ENR_GPIODEN_Pos);
    }
}
void GPIOD_moder( uint8_t pin, uint8_t mode )
{
	if(pin < WORD_BITS && mode < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t Pos = pin * BLOCK_SIZE;
		mode &= MASK;
		GPIOD->MODER &= ~(MASK << Pos);
		GPIOD->MODER |= (mode << Pos);
	}
}
void GPIOD_otype(uint8_t pin, uint8_t otype)
{
	if(pin < WORD_BITS && otype < TWO){
		GPIOD->OTYPER &= ~(1 << pin);
		GPIOD->OTYPER |= ( otype << pin );
	}
}
void GPIOD_ospeed(uint8_t pin, uint8_t ospeed)
{
	if(pin < WORD_BITS && ospeed < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint16_t Pos = (pin * BLOCK_SIZE);
		ospeed &= MASK;
		GPIOD->OSPEEDR &= ~( MASK << Pos );
		GPIOD->OSPEEDR |= ( ospeed << Pos );
	}
}
void GPIOD_pupd(uint8_t pin, uint8_t pupd)
{
	if(pin < WORD_BITS && pupd < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
    	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    	const uint16_t Pos = (pin * BLOCK_SIZE);
    	pupd &= MASK;
    	GPIOD->PUPDR &= ~( MASK << Pos );
    	GPIOD->PUPDR |= ( pupd << Pos );
	}
}
void GPIOD_set_hpins(uint16_t hpins)
{
	GPIOD->BSRR = (uint32_t)hpins;
}
void GPIOD_clear_hpins(uint16_t hpins)
{
	GPIOD->BSRR = (uint32_t)(hpins << WORD_BITS);
}
void GPIOD_lck(uint16_t hpins){
	GPIOD->LCKR = hpins;
	for(uint8_t status = TWO; status; ) {
		if(GPIOD->LCKR & (1 << WORD_BITS)) {
			status = 0;
		}else {
			GPIOD->LCKR |= 1 << WORD_BITS;
			GPIOD->LCKR &= ~(1 << WORD_BITS);
			GPIOD->LCKR |= 1 << WORD_BITS;
			(void)GPIOD->LCKR;
			status--;
		}
	}
}
void GPIOD_af(uint8_t pin, uint8_t af)
{
	if(pin < WORD_BITS && af < WORD_BITS){
		const uint8_t BLOCK_SIZE = NIBBLE_BITS;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t index = (pin * BLOCK_SIZE) / DWORD_BITS;
		const uint16_t Pos = (pin * BLOCK_SIZE) % DWORD_BITS;

		af &= MASK;
		if(index < TWO){
			GPIOD->AFR[index] &= ~( MASK << Pos );
	    	GPIOD->AFR[index] |= ( af << Pos );
		}
	}
}

/*** HANDLER ***/
static STM32FXXX_GPIOD_Handler stm32fxxx_gpiod_setup = {
    // V-table
    .clock = GPIOD_clock,
    .moder = GPIOD_moder,
    .otype = GPIOD_otype,
    .ospeed = GPIOD_ospeed,
    .pupd = GPIOD_pupd,
    .set_hpins = GPIOD_set_hpins,
    .clear_hpins = GPIOD_clear_hpins,
    .lck = GPIOD_lck,
    .af = GPIOD_af
};

STM32FXXX_GPIOD_Handler* gpiod(void) { return &stm32fxxx_gpiod_setup; }

/*** GPIOE ***/
void GPIOE_clock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOEEN_Pos);
    } else {
        RCC->AHB1ENR &= ~(1 << RCC_AHB1ENR_GPIOEEN_Pos);
    }
}
void GPIOE_moder( uint8_t pin, uint8_t mode )
{
	if(pin < WORD_BITS && mode < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t Pos = pin * BLOCK_SIZE;
		mode &= MASK;
		GPIOE->MODER &= ~(MASK << Pos);
		GPIOE->MODER |= (mode << Pos);
	}
}
void GPIOE_otype(uint8_t pin, uint8_t otype)
{
	if(pin < WORD_BITS && otype < TWO){
		GPIOE->OTYPER &= ~(1 << pin);
		GPIOE->OTYPER |= ( otype << pin );
	}
}
void GPIOE_ospeed(uint8_t pin, uint8_t ospeed)
{
	if(pin < WORD_BITS && ospeed < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint16_t Pos = (pin * BLOCK_SIZE);
		ospeed &= MASK;
		GPIOE->OSPEEDR &= ~( MASK << Pos );
		GPIOE->OSPEEDR |= ( ospeed << Pos );
	}
}
void GPIOE_pupd(uint8_t pin, uint8_t pupd)
{
	if(pin < WORD_BITS && pupd < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint16_t Pos = (pin * BLOCK_SIZE);
		pupd &= MASK;
		GPIOE->PUPDR &= ~( MASK << Pos );
		GPIOE->PUPDR |= ( pupd << Pos );
	}
}
void GPIOE_set_hpins(uint16_t hpins)
{
	GPIOE->BSRR = (uint32_t)hpins;
}
void GPIOE_clear_hpins(uint16_t hpins)
{
	GPIOE->BSRR = (uint32_t)(hpins << WORD_BITS);
}
void GPIOE_lck(uint16_t hpins){
	GPIOE->LCKR = hpins;
	for(uint8_t status = TWO; status; ) {
		if(GPIOE->LCKR & (1 << WORD_BITS)) {
			status = 0;
		}else {
			GPIOE->LCKR |= 1 << WORD_BITS;
			GPIOE->LCKR &= ~(1 << WORD_BITS);
			GPIOE->LCKR |= 1 << WORD_BITS;
			(void)GPIOE->LCKR;
			status--;
		}
	}

}
void GPIOE_af(uint8_t pin, uint8_t af)
{
	if(pin < WORD_BITS && af < WORD_BITS){
		const uint8_t BLOCK_SIZE = NIBBLE_BITS;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t index = (pin * BLOCK_SIZE) / DWORD_BITS;
		const uint16_t Pos = (pin * BLOCK_SIZE) % DWORD_BITS;

		af &= MASK;
		if(index < TWO){
			GPIOE->AFR[index] &= ~( MASK << Pos );
			GPIOE->AFR[index] |= ( af << Pos );
		}
	}
}

/*** HANDLER ***/
static STM32FXXX_GPIOE_Handler stm32fxxx_gpioe_setup = {
    // V-table
    .clock = GPIOE_clock,
    .moder = GPIOE_moder,
    .otype = GPIOE_otype,
    .ospeed = GPIOE_ospeed,
    .pupd = GPIOE_pupd,
    .set_hpins = GPIOE_set_hpins,
    .clear_hpins = GPIOE_clear_hpins,
    .lck = GPIOE_lck,
    .af = GPIOE_af
};

STM32FXXX_GPIOE_Handler* gpioe(void) { return &stm32fxxx_gpioe_setup; }

#ifdef STM32F446xx
/*** GPIOF ***/
void GPIOF_clock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOFEN_Pos);
    } else {
        RCC->AHB1ENR &= ~(1 << RCC_AHB1ENR_GPIOFEN_Pos);
    }
}
void GPIOF_moder( uint8_t pin, uint8_t mode )
{
	if(pin < WORD_BITS && mode < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t Pos = pin * BLOCK_SIZE;
		mode &= MASK;
		GPIOF->MODER &= ~(MASK << Pos);
		GPIOF->MODER |= (mode << Pos);
	}
}
void GPIOF_otype(uint8_t pin, uint8_t otype)
{
	if(pin < WORD_BITS && otype < TWO){
		GPIOF->OTYPER &= ~(1 << pin);
		GPIOF->OTYPER |= ( otype << pin );
	}
}
void GPIOF_ospeed(uint8_t pin, uint8_t ospeed)
{
	if(pin < WORD_BITS && ospeed < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
    	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    	const uint16_t Pos = (pin * BLOCK_SIZE);
    	ospeed &= MASK;
    	GPIOF->OSPEEDR &= ~( MASK << Pos );
    	GPIOF->OSPEEDR |= ( ospeed << Pos );
	}
}
void GPIOF_pupd(uint8_t pin, uint8_t pupd)
{
	if(pin < WORD_BITS && pupd < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
    	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    	const uint16_t Pos = (pin * BLOCK_SIZE);
    	pupd &= MASK;
    	GPIOF->PUPDR &= ~( MASK << Pos );
    	GPIOF->PUPDR |= ( pupd << Pos );
	}
}
void GPIOF_set_hpins(uint16_t hpins)
{
	GPIOF->BSRR = (uint32_t)hpins;
}
void GPIOF_clear_hpins(uint16_t hpins)
{
	GPIOF->BSRR = (uint32_t)(hpins << WORD_BITS);
}
void GPIOF_lck(uint16_t hpins){
	GPIOF->LCKR = hpins;
	for(uint8_t status = TWO; status; ) {
		if(GPIOF->LCKR & (1 << WORD_BITS)) {
			status = ZERO;
		}else {
			GPIOF->LCKR |= 1 << WORD_BITS;
			GPIOF->LCKR &= ~(1 << WORD_BITS);
			GPIOF->LCKR |= 1 << WORD_BITS;
			(void)GPIOF->LCKR;
			status--;
		}
	}

}
void GPIOF_af(uint8_t pin, uint8_t af)
{
	if(pin < WORD_BITS && af < WORD_BITS){
		const uint8_t BLOCK_SIZE = NIBBLE_BITS;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t index = (pin * BLOCK_SIZE) / DWORD_BITS;
		const uint16_t Pos = (pin * BLOCK_SIZE) % DWORD_BITS;

		af &= MASK;
		if(index < TWO){
			GPIOF->AFR[index] &= ~( MASK << Pos );
	    	GPIOF->AFR[index] |= ( af << Pos );
		}
	}
}

/*** HANDLER ***/
static STM32FXXX_GPIOF_Handler stm32fxxx_gpiof_setup = {
    // V-table
    .clock = GPIOF_clock,
    .moder = GPIOF_moder,
    .otype = GPIOF_otype,
    .ospeed = GPIOF_ospeed,
    .pupd = GPIOF_pupd,
    .set_hpins = GPIOF_set_hpins,
    .clear_hpins = GPIOF_clear_hpins,
    .lck = GPIOF_lck,
    .af = GPIOF_af
};

STM32FXXX_GPIOF_Handler* gpiof(void) { return &stm32fxxx_gpiof_setup; }

/*** GPIOG ***/
void GPIOG_clock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOGEN_Pos);
    } else {
        RCC->AHB1ENR &= ~(1 << RCC_AHB1ENR_GPIOGEN_Pos);
    }
}
void GPIOG_moder( uint8_t pin, uint8_t mode )
{
	if(pin < WORD_BITS && mode < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t Pos = pin * BLOCK_SIZE;
		mode &= MASK;
		GPIOG->MODER &= ~(MASK << Pos);
		GPIOG->MODER |= (mode << Pos);
	}
}
void GPIOG_otype(uint8_t pin, uint8_t otype)
{
	if(pin < WORD_BITS && otype < TWO){
		GPIOG->OTYPER &= ~(1 << pin);
		GPIOG->OTYPER |= ( otype << pin );
	}
}
void GPIOG_ospeed(uint8_t pin, uint8_t ospeed)
{
	if(pin < WORD_BITS && ospeed < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
    	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    	const uint16_t Pos = (pin * BLOCK_SIZE);
    	ospeed &= MASK;
    	GPIOG->OSPEEDR &= ~( MASK << Pos );
    	GPIOG->OSPEEDR |= ( ospeed << Pos );
	}
}
void GPIOG_pupd(uint8_t pin, uint8_t pupd)
{
	if(pin < WORD_BITS && pupd < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
    	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    	const uint16_t Pos = (pin * BLOCK_SIZE);
    	pupd &= MASK;
    	GPIOG->PUPDR &= ~( MASK << Pos );
    	GPIOG->PUPDR |= ( pupd << Pos );
	}
}
void GPIOG_set_hpins(uint16_t hpins)
{
	GPIOG->BSRR = (uint32_t)hpins;
}
void GPIOG_clear_hpins(uint16_t hpins)
{
	GPIOG->BSRR = (uint32_t)(hpins << WORD_BITS);
}
void GPIOG_lck(uint16_t hpins){
	GPIOG->LCKR = hpins;
	for(uint8_t status = TWO; status; ) {
		if(GPIOG->LCKR & (1 << WORD_BITS)) {
			status = ZERO;
		}else {
			GPIOG->LCKR |= 1 << WORD_BITS;
			GPIOG->LCKR &= ~(1 << WORD_BITS);
			GPIOG->LCKR |= 1 << WORD_BITS;
			(void)GPIOG->LCKR;
			status--;
		}
	}

}
void GPIOG_af(uint8_t pin, uint8_t af)
{
	if(pin < WORD_BITS && af < WORD_BITS){
		const uint8_t BLOCK_SIZE = NIBBLE_BITS;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t index = (pin * BLOCK_SIZE) / DWORD_BITS;
		const uint16_t Pos = (pin * BLOCK_SIZE) % DWORD_BITS;

		af &= MASK;
		if(index < TWO){
			GPIOG->AFR[index] &= ~( MASK << Pos );
	    	GPIOG->AFR[index] |= ( af << Pos );
		}
	}
}

/*** HANDLER ***/
static STM32FXXX_GPIOG_Handler stm32fxxx_gpiog_setup = {
    // V-table
    .clock = GPIOG_clock,
    .moder = GPIOG_moder,
    .otype = GPIOG_otype,
    .ospeed = GPIOG_ospeed,
    .pupd = GPIOG_pupd,
    .set_hpins = GPIOG_set_hpins,
    .clear_hpins = GPIOG_clear_hpins,
    .lck = GPIOG_lck,
    .af = GPIOG_af
};

STM32FXXX_GPIOG_Handler* gpiog(void) { return &stm32fxxx_gpiog_setup; }

/*** GPIOH ***/
void GPIOH_clock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOHEN_Pos);
    } else {
        RCC->AHB1ENR &= ~(1 << RCC_AHB1ENR_GPIOHEN_Pos);
    }
}
void GPIOH_moder( uint8_t pin, uint8_t mode )
{
	if(pin < WORD_BITS && mode < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t Pos = pin * BLOCK_SIZE;
		mode &= MASK;
		GPIOH->MODER &= ~(MASK << Pos);
		GPIOH->MODER |= (mode << Pos);
	}
}
void GPIOH_otype(uint8_t pin, uint8_t otype)
{
	if(pin < WORD_BITS && otype < TWO){
		GPIOH->OTYPER &= ~(1 << pin);
		GPIOH->OTYPER |= ( otype << pin );
	}
}
void GPIOH_ospeed(uint8_t pin, uint8_t ospeed)
{
	if(pin < WORD_BITS && ospeed < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
    	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    	const uint16_t Pos = (pin * BLOCK_SIZE);
    	ospeed &= MASK;
    	GPIOH->OSPEEDR &= ~( MASK << Pos );
    	GPIOH->OSPEEDR |= ( ospeed << Pos );
	}
}
void GPIOH_pupd(uint8_t pin, uint8_t pupd)
{
	if(pin < WORD_BITS && pupd < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint16_t Pos = (pin * BLOCK_SIZE);
		pupd &= MASK;
    	GPIOH->PUPDR &= ~( MASK << Pos );
    	GPIOH->PUPDR |= ( pupd << Pos );
	}
}
void GPIOH_set_hpins(uint16_t hpins)
{
	GPIOH->BSRR = (uint32_t)hpins;
}
void GPIOH_clear_hpins(uint16_t hpins)
{
	GPIOH->BSRR = (uint32_t)(hpins << WORD_BITS);
}
void GPIOH_lck(uint16_t hpins){
	GPIOH->LCKR = hpins;
	for(uint8_t status = TWO; status; ) {
		if(GPIOH->LCKR & (1 << WORD_BITS)) {
			status = ZERO;
		}else {
			GPIOH->LCKR |= 1 << WORD_BITS;
			GPIOH->LCKR &= ~(1 << WORD_BITS);
			GPIOH->LCKR |= 1 << WORD_BITS;
			(void)GPIOH->LCKR;
			status--;
		}
	}

}
void GPIOH_af(uint8_t pin, uint8_t af)
{
	if(pin < WORD_BITS && af < WORD_BITS){
		const uint8_t BLOCK_SIZE = NIBBLE_BITS;
		const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
		const uint8_t index = (pin * BLOCK_SIZE) / DWORD_BITS;
		const uint16_t Pos = (pin * BLOCK_SIZE) % DWORD_BITS;

		af &= MASK;
		if(index < TWO){
			GPIOH->AFR[index] &= ~( MASK << Pos );
	    	GPIOH->AFR[index] |= ( af << Pos );
		}
	}
}

/*** HANDLER ***/
static STM32FXXX_GPIOH_Handler stm32fxxx_gpioh_setup = {
    // V-table
    .clock = GPIOH_clock,
    .moder = GPIOH_moder,
    .otype = GPIOH_otype,
    .ospeed = GPIOH_ospeed,
    .pupd = GPIOH_pupd,
    .set_hpins = GPIOH_set_hpins,
    .clear_hpins = GPIOH_clear_hpins,
    .lck = GPIOH_lck,
    .af = GPIOH_af
};

STM32FXXX_GPIOH_Handler* gpioh(void) { return &stm32fxxx_gpioh_setup; }

#endif

/*
 * More Interested in finding the best work flow, then coding itself. Because that will become redundant after
 * achieving the objective.
 * bit_n = bit_n % DWORD_BITS; is the same as bit_n = bit_n & (DWORD_BITS - 1);, for power of two numbers.
 * **/

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

/**** EOF ****/

