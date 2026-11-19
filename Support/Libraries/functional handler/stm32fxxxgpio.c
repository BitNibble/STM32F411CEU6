/******************************************************************************
	STM32 XXX GPIO
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 19/06/2023
Update: 28/02/2024
Comment:
	File Vars, File Function Header, Library Function Definitions.
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxgpio.h"

/****************************************/
#define TWO 2
#define NIBBLE_BITS 4
#define BYTE_BITS 8
#define WORD_BITS 16
#define N_BITS 32
#define N_LIMBITS 33
#define H_BIT 31
#define L_BIT 0
#define ON 1
#define OFF 0
/****************************************/

/*** File Variables ***/
static STM32FXXX_GPIOA stm32fxxx_gpioa = {0};
static STM32FXXX_GPIOB stm32fxxx_gpiob = {0};
static STM32FXXX_GPIOC stm32fxxx_gpioc = {0};
static STM32FXXX_GPIOD stm32fxxx_gpiod = {0};
static STM32FXXX_GPIOE stm32fxxx_gpioe = {0};
static STM32FXXX_GPIOF stm32fxxx_gpiof = {0};
static STM32FXXX_GPIOG stm32fxxx_gpiog = {0};
static STM32FXXX_GPIOH stm32fxxx_gpioh = {0};

/*** GPIO Procedure & Function Definition ***/
/*** GPIOA ***/
void STM32FXXXGpioAclock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << 0);
    } else {
        RCC->AHB1ENR &= ~(1 << 0);
    }
}

void STM32FXXXGpioAafr(uint8_t pin, uint8_t data)
{
    const uint8_t BLOCK_SIZE = NIBBLE_BITS;
    const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
    const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
    const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

    data &= MASK;
    if(index < TWO){
    	GPIOA->AFR[index] &= ~( MASK << Pos );
    	GPIOA->AFR[index] |= ( data << Pos );
    }
}

/*** GPIOB ***/
void STM32FXXXGpioBclock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << 1);
    } else {
        RCC->AHB1ENR &= ~(1 << 1);
    }
}

void STM32FXXXGpioBafr(uint8_t pin, uint8_t data)
{
	const uint8_t BLOCK_SIZE = NIBBLE_BITS;
	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
	const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
	const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

	data &= MASK;
	if(index < TWO){
		GPIOB->AFR[index] &= ~( MASK << Pos );
	    GPIOB->AFR[index] |= ( data << Pos );
	}
}

/*** GPIOC ***/
void STM32FXXXGpioCclock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << 2);
    } else {
        RCC->AHB1ENR &= ~(1 << 2);
    }
}

void STM32FXXXGpioCafr(uint8_t pin, uint8_t data)
{
	const uint8_t BLOCK_SIZE = NIBBLE_BITS;
	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
	const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
	const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

	data &= MASK;
	if(index < TWO){
		GPIOC->AFR[index] &= ~( MASK << Pos );
	    GPIOC->AFR[index] |= ( data << Pos );
	}
}

/*** GPIOD ***/
void STM32FXXXGpioDclock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << 3);
    } else {
        RCC->AHB1ENR &= ~(1 << 3);
    }
}

void STM32FXXXGpioDafr(uint8_t pin, uint8_t data)
{
	const uint8_t BLOCK_SIZE = NIBBLE_BITS;
	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
	const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
	const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

	data &= MASK;
	if(index < TWO){
		GPIOD->AFR[index] &= ~( MASK << Pos );
	    GPIOD->AFR[index] |= ( data << Pos );
	}
}

/*** GPIOE ***/
void STM32FXXXGpioEclock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << 4);
    } else {
        RCC->AHB1ENR &= ~(1 << 4);
    }
}

void STM32FXXXGpioEafr(uint8_t pin, uint8_t data)
{
	const uint8_t BLOCK_SIZE = NIBBLE_BITS;
	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
	const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
	const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

	data &= MASK;
	if(index < TWO){
		GPIOE->AFR[index] &= ~( MASK << Pos );
	    GPIOE->AFR[index] |= ( data << Pos );
	}
}

#ifdef STM32F446xx
/*** GPIOF ***/
void STM32FXXXGpioFclock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << 5);
    } else {
        RCC->AHB1ENR &= ~(1 << 5);
    }
}

void STM32FXXXGpioFafr(uint8_t pin, uint8_t data)
{
	const uint8_t BLOCK_SIZE = NIBBLE_BITS;
	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
	const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
	const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

	data &= MASK;
	if(index < TWO){
		GPIOF->AFR[index] &= ~( MASK << Pos );
	    GPIOF->AFR[index] |= ( data << Pos );
	}
}

/*** GPIOG ***/
void STM32FXXXGpioGclock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << 6);
    } else {
        RCC->AHB1ENR &= ~(1 << 6);
    }
}

void STM32FXXXGpioGafr(uint8_t pin, uint8_t data)
{
	const uint8_t BLOCK_SIZE = NIBBLE_BITS;
	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
	const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
	const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

	data &= MASK;
	if(index < TWO){
		GPIOG->AFR[index] &= ~( MASK << Pos );
	    GPIOG->AFR[index] |= ( data << Pos );
	}
}

/*** GPIOH ***/
void STM32FXXXGpioHclock(uint8_t enable)
{
    if (enable) {
        RCC->AHB1ENR |= (1 << 7);
    } else {
        RCC->AHB1ENR &= ~(1 << 7);
    }
}

void STM32FXXXGpioHafr(uint8_t pin, uint8_t data)
{
	const uint8_t BLOCK_SIZE = NIBBLE_BITS;
	const uint8_t MASK = (1 << BLOCK_SIZE) - 1;
	const uint8_t index = (pin * BLOCK_SIZE) / N_BITS;
	const uint16_t Pos = (pin * BLOCK_SIZE) % N_BITS;

	data &= MASK;
	if(index < TWO){
		GPIOH->AFR[index] &= ~( MASK << Pos );
	    GPIOH->AFR[index] |= ( data << Pos );
	}
}
#endif
/*** Initialization Procedures & Function Definitions ***/
void gpioa_enable(void)
{
	/*** Enable Clock ***/
	STM32FXXXGpioAclock(ON);
    /*** GPIOA TypeDef ***/
	stm32fxxx_gpioa.instance = GPIOA;
    /******************/
    stm32fxxx_gpioa.afr = STM32FXXXGpioAafr;
    /*** GPIOA RCC Clock Enable ***/
    stm32fxxx_gpioa.clock = STM32FXXXGpioAclock;
    /*** Other ***/
    //return &stm32fxxx_gpioa;
}

STM32FXXX_GPIOA* gpioa(void) { return &stm32fxxx_gpioa; }

void gpiob_enable(void)
{
	/*** Enable Clock ***/
	STM32FXXXGpioBclock(ON);
    /*** GPIOA TypeDef ***/
    stm32fxxx_gpiob.instance = GPIOB;
    /******************/
    stm32fxxx_gpiob.afr = STM32FXXXGpioBafr;
    /*** GPIOB RCC Clock Enable ***/
    stm32fxxx_gpiob.clock = STM32FXXXGpioBclock;
    /*** Other ***/
    //return &stm32fxxx_gpiob;
}

STM32FXXX_GPIOB* gpiob(void) { return &stm32fxxx_gpiob; }

void gpioc_enable(void)
{
	/*** Enable Clock ***/
	STM32FXXXGpioCclock(ON);
    /*** GPIOA TypeDef ***/
    stm32fxxx_gpioc.instance = GPIOC;
    /******************/
    stm32fxxx_gpioc.afr = STM32FXXXGpioCafr;
    /*** GPIOC RCC Clock Enable ***/
    stm32fxxx_gpioc.clock = STM32FXXXGpioCclock;
    /*** Other ***/
    //return &stm32fxxx_gpioc;
}

STM32FXXX_GPIOC* gpioc(void) { return &stm32fxxx_gpioc; }

void gpiod_enable(void)
{
	/*** Enable Clock ***/
	STM32FXXXGpioDclock(ON);
    /*** GPIOA TypeDef ***/
    stm32fxxx_gpiod.instance = GPIOD;
    /******************/
    stm32fxxx_gpiod.afr = STM32FXXXGpioDafr;
    /*** GPIOD RCC Clock Enable ***/
    stm32fxxx_gpiod.clock = STM32FXXXGpioDclock;
    /*** Other ***/
    //return &stm32fxxx_gpiod;
}

STM32FXXX_GPIOD* gpiod(void) { return &stm32fxxx_gpiod; }

void gpioe_enable(void)
{
	/*** Enable Clock ***/
	STM32FXXXGpioEclock(ON);
    /*** GPIOA TypeDef ***/
    stm32fxxx_gpioe.instance = GPIOE;
    /******************/
    stm32fxxx_gpioe.afr = STM32FXXXGpioEafr;
    /*** GPIOE RCC Clock Enable ***/
    stm32fxxx_gpioe.clock = STM32FXXXGpioEclock;
    /*** Other ***/
    //return &stm32fxxx_gpioe;
}

STM32FXXX_GPIOE* gpioe(void) { return &stm32fxxx_gpioe; }

void gpiof_enable(void)
{
	#ifdef STM32F446xx
		STM32FXXXGpioFclock(ON);
    	stm32fxxx_gpiof.instance = GPIOF;
	#endif
    /******************/
    stm32fxxx_gpiof.afr = STM32FXXXGpioFafr;
    /*** GPIOF RCC Clock Enable ***/
    stm32fxxx_gpiof.clock = STM32FXXXGpioFclock;
    /*** Other ***/
    //return &stm32fxxx_gpiof;
}

STM32FXXX_GPIOF* gpiof(void) { return &stm32fxxx_gpiof; }

void gpiog_enable(void)
{
	#ifdef STM32F446xx
		STM32FXXXGpioGclock(ON);
    	stm32fxxx_gpiog.instance = GPIOG;
	#endif
    /******************/
    stm32fxxx_gpiog.afr = STM32FXXXGpioGafr;
    /*** GPIOG RCC Clock Enable ***/
    stm32fxxx_gpiog.clock = STM32FXXXGpioGclock;
    /*** Other ***/
    //return &stm32fxxx_gpiog;
}

STM32FXXX_GPIOG* gpiog(void) { return &stm32fxxx_gpiog; }

void gpioh_enable(void)
{
	#ifdef STM32F446xx
		STM32FXXXGpioHclock(ON);
    	stm32fxxx_gpioh.instance = GPIOH;
	#endif
    /******************/
    stm32fxxx_gpioh.afr = STM32FXXXGpioHafr;
    /*** GPIOH RCC Clock Enable ***/
    stm32fxxx_gpioh.clock = STM32FXXXGpioHclock;
    /*** Other ***/
    //return &stm32fxxx_gpioh;
}

STM32FXXX_GPIOH* gpioh(void) { return &stm32fxxx_gpioh; }

/*
 * More Interested in finding the best work flow, then coding itself. Because that will become redundant after
 * achieving the objective.
 *
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

