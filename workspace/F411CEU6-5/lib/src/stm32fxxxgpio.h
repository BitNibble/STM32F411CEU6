/******************************************************************************
	STM32 XXX GPIO
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     19/06/2023
Update:   28/02/2024
Comment:
	TypeDef Pointer Structures, Library Function Headers.
*******************************************************************************/
#ifndef _STM32FXXXGPIO_H_
	#define _STM32FXXXGPIO_H_

/*** File Library ***/
//#if defined (STM32F411xE)
	#include "stm32f411ceu6.h"
//#elif defined(STM32F446xx)
//	#include "stm32f446re.h"
//#endif
/*** GPIO -> GPIO ***/
typedef const struct
{
	/*** Clock and Nvic ***/
	void (*moder)(uint8_t pin, uint8_t mode);
	void (*otype)(uint8_t pin, uint8_t otype);
	void (*ospeed)(uint8_t pin, uint8_t ospeed);
	void (*pupd)(uint8_t pin, uint8_t pupd);
	void (*set_hpins)(uint16_t hpins);
	void (*clear_hpins)(uint16_t hpins);
	void (*lck)(uint16_t hpins);
	void (*af)(uint8_t pin, uint8_t af);
	/*************/
	void (*clock)( uint8_t state );
	/*** Device ***/
//#if defined(STM32F411CEU6_H)
//	STM32F411CEU6_Instance* (*dev)(void);
//#elif defined(STM32F446RE_H)
//	STM32F446RE_Instance* (*dev)(void);
//#else
//	void* (*dev)(void);
//#endif
}STM32FXXX_GPIOA_Handler, STM32FXXX_GPIOB_Handler, STM32FXXX_GPIOC_Handler, \
 STM32FXXX_GPIOD_Handler, STM32FXXX_GPIOE_Handler, STM32FXXX_GPIOF_Handler, \
 STM32FXXX_GPIOG_Handler, STM32FXXX_GPIOH_Handler;
// INIC
STM32FXXX_GPIOA_Handler* gpioa(void);
STM32FXXX_GPIOB_Handler* gpiob(void);
STM32FXXX_GPIOC_Handler* gpioc(void);
STM32FXXX_GPIOD_Handler* gpiod(void);
STM32FXXX_GPIOE_Handler* gpioe(void);
STM32FXXX_GPIOF_Handler* gpiof(void);
STM32FXXX_GPIOG_Handler* gpiog(void);
STM32FXXX_GPIOH_Handler* gpioh(void);

/*** GPIO Procedure & Function Definition ***/
void GPIO_clock( GPIO_TypeDef* GPIO, uint8_t enable );
void GPIO_moder( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t mode );
void GPIO_otype( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t otype );
void GPIO_ospeed( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t ospeed );
void GPIO_pupd( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t pupd );
void GPIO_set_hpins( GPIO_TypeDef* GPIO, uint16_t hpins );
void GPIO_clear_hpins( GPIO_TypeDef* GPIO, uint16_t hpins );
void GPIO_lck( GPIO_TypeDef* GPIO, uint16_t hpins );
void GPIO_af( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t af );

#endif
/*** EOF ***/

