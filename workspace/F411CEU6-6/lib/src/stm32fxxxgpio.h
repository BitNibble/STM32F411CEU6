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
#include "stm32f411ceu6.h"

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

#endif
/*** EOF ***/

