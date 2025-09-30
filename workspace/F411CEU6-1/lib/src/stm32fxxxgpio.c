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

/*** File Variables ***/
//static STM32FXXX_GPIOA stm32fxxx_gpioa = {0};
static STM32FXXX_GPIOB stm32fxxx_gpiob = {0};
static STM32FXXX_GPIOC stm32fxxx_gpioc = {0};
static STM32FXXX_GPIOD stm32fxxx_gpiod = {0};
static STM32FXXX_GPIOE stm32fxxx_gpioe = {0};
#ifdef STM32F446xx
	static STM32FXXX_GPIOF stm32fxxx_gpiof = {0};
	static STM32FXXX_GPIOG stm32fxxx_gpiog = {0};
	static STM32FXXX_GPIOH stm32fxxx_gpioh = {0};
#endif

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
static STM32FXXX_GPIOA stm32fxxx_gpioa = {
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

STM32FXXX_GPIOA* gpioa(void) { return &stm32fxxx_gpioa; }

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
#endif

void gpiob_enable(void)
{
	/*** Enable Clock ***/
	GPIOB_clock(1);
    /*** GPIOB RCC Clock Enable ***/
    stm32fxxx_gpiob.clock = GPIOB_clock;
	/*** Procedures ***/
	/*** Other ***/
    stm32fxxx_gpiob.moder = GPIOB_moder;
    stm32fxxx_gpiob.otype = GPIOB_otype;
    stm32fxxx_gpiob.ospeed = GPIOB_ospeed;
    stm32fxxx_gpiob.pupd = GPIOB_pupd;
    stm32fxxx_gpiob.set_hpins = GPIOB_set_hpins;
    stm32fxxx_gpiob.clear_hpins = GPIOB_clear_hpins;
    stm32fxxx_gpiob.lck = GPIOB_lck;
    stm32fxxx_gpiob.af = GPIOB_af;
    //return &stm32fxxx_gpiob;
}

STM32FXXX_GPIOB* gpiob(void) { return &stm32fxxx_gpiob; }

void gpioc_enable(void)
{
	/*** Enable Clock ***/
	GPIOC_clock(1);
    /*** GPIOC RCC Clock Enable ***/
    stm32fxxx_gpioc.clock = GPIOC_clock;
	/*** Procedures ***/
	/*** Other ***/
    stm32fxxx_gpioc.moder = GPIOC_moder;
    stm32fxxx_gpioc.otype = GPIOC_otype;
    stm32fxxx_gpioc.ospeed = GPIOC_ospeed;
    stm32fxxx_gpioc.pupd = GPIOC_pupd;
    stm32fxxx_gpioc.set_hpins = GPIOC_set_hpins;
    stm32fxxx_gpioc.clear_hpins = GPIOC_clear_hpins;
    stm32fxxx_gpioc.lck = GPIOC_lck;
    stm32fxxx_gpioc.af = GPIOC_af;
    //return &stm32fxxx_gpioc;
}

STM32FXXX_GPIOC* gpioc(void) { return &stm32fxxx_gpioc; }

void gpiod_enable(void)
{
	/*** Enable Clock ***/
	GPIOD_clock(1);
    /*** GPIOD RCC Clock Enable ***/
    stm32fxxx_gpiod.clock = GPIOD_clock;
	/*** Procedures ***/
	/*** Other ***/
    stm32fxxx_gpiod.moder = GPIOD_moder;
    stm32fxxx_gpiod.otype = GPIOD_otype;
    stm32fxxx_gpiod.ospeed = GPIOD_ospeed;
    stm32fxxx_gpiod.pupd = GPIOD_pupd;
    stm32fxxx_gpiod.set_hpins = GPIOD_set_hpins;
    stm32fxxx_gpiod.clear_hpins = GPIOD_clear_hpins;
    stm32fxxx_gpiod.lck = GPIOD_lck;
    stm32fxxx_gpiod.af = GPIOD_af;
    //return &stm32fxxx_gpiod;
}

STM32FXXX_GPIOD* gpiod(void) { return &stm32fxxx_gpiod; }

void gpioe_enable(void)
{
	/*** Enable Clock ***/
	GPIOE_clock(1);
    /*** GPIOE RCC Clock Enable ***/
    stm32fxxx_gpioe.clock = GPIOE_clock;
	/*** Procedures ***/
	/*** Other ***/
    stm32fxxx_gpioe.moder = GPIOE_moder;
    stm32fxxx_gpioe.otype = GPIOE_otype;
    stm32fxxx_gpioe.ospeed = GPIOE_ospeed;
    stm32fxxx_gpioe.pupd = GPIOE_pupd;
    stm32fxxx_gpioe.set_hpins = GPIOE_set_hpins;
    stm32fxxx_gpioe.clear_hpins = GPIOE_clear_hpins;
    stm32fxxx_gpioe.lck = GPIOE_lck;
    stm32fxxx_gpioe.af = GPIOE_af;
    //return &stm32fxxx_gpioe;
}

STM32FXXX_GPIOE* gpioe(void) { return &stm32fxxx_gpioe; }

#ifdef STM32F446xx
void gpiof_enable(void)
{
	GPIOF_clock(ON);
    /*** GPIOF RCC Clock Enable ***/
    stm32fxxx_gpiof.clock = GPIOF_clock;
	/*** Procedures ***/
	/*** Other ***/
    stm32fxxx_gpiof.moder = GPIOF_moder;
    stm32fxxx_gpiof.otype = GPIOF_otype;
    stm32fxxx_gpiof.ospeed = GPIOF_ospeed;
    stm32fxxx_gpiof.pupd = GPIOF_pupd;
    stm32fxxx_gpiof.set_hpins = GPIOF_set_hpins;
    stm32fxxx_gpiof.clear_hpins = GPIOF_clear_hpins;
    stm32fxxx_gpiof.lck = GPIOF_lck;
    stm32fxxx_gpiof.af = GPIOF_af;
    //return &stm32fxxx_gpiof;
}

STM32FXXX_GPIOF* gpiof(void) { return &stm32fxxx_gpiof; }

void gpiog_enable(void)
{
	GPIOG_clock(ON);
    /*** GPIOG RCC Clock Enable ***/
    stm32fxxx_gpiog.clock = GPIOG_clock;
	/*** Procedures ***/
	/*** Other ***/
    stm32fxxx_gpiog.moder = GPIOG_moder;
    stm32fxxx_gpiog.otype = GPIOG_otype;
    stm32fxxx_gpiog.ospeed = GPIOG_ospeed;
    stm32fxxx_gpiog.pupd = GPIOG_pupd;
    stm32fxxx_gpiog.set_hpins = GPIOG_set_hpins;
    stm32fxxx_gpiog.clear_hpins = GPIOG_clear_hpins;
    stm32fxxx_gpiog.lck = GPIOG_lck;
    stm32fxxx_gpiog.af = GPIOG_af;
    //return &stm32fxxx_gpiog;
}

STM32FXXX_GPIOG* gpiog(void) { return &stm32fxxx_gpiog; }

void gpioh_enable(void)
{
	GPIOH_clock(ON);
    /*** GPIOH RCC Clock Enable ***/
    stm32fxxx_gpioh.clock = GPIOH_clock;
	/*** Procedures ***/
	/*** Other ***/
    stm32fxxx_gpioh.moder = GPIOH_moder;
    stm32fxxx_gpioh.otype = GPIOH_otype;
    stm32fxxx_gpioh.ospeed = GPIOH_ospeed;
    stm32fxxx_gpioh.pupd = GPIOH_pupd;
    stm32fxxx_gpioh.set_hpins = GPIOH_set_hpins;
    stm32fxxx_gpioh.clear_hpins = GPIOH_clear_hpins;
    stm32fxxx_gpioh.lck = GPIOH_lck;
    stm32fxxx_gpioh.af = GPIOH_af;
    //return &stm32fxxx_gpioh;
}

STM32FXXX_GPIOH* gpioh(void) { return &stm32fxxx_gpioh; }

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

