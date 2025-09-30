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
/*** Define and Macro ***/
#if !defined (MODE_INPUT) || !defined (MODE_OUTPUT) || !defined (MODE_AF) || !defined (MODE_ANALOG)
	#define MODE_INPUT 0x0UL
	#define MODE_OUTPUT 0x1UL
	#define MODE_AF 0x2UL
	#define MODE_ANALOG 0x3UL
#endif
/*** GPIO -> GPIO ***/
typedef struct
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
	/*************/

}STM32FXXX_GPIOA, STM32FXXX_GPIOB, STM32FXXX_GPIOC, \
 STM32FXXX_GPIOD, STM32FXXX_GPIOE, STM32FXXX_GPIOF, \
 STM32FXXX_GPIOG, STM32FXXX_GPIOH;
// INIC
STM32FXXX_GPIOA* gpioa(void);
void gpiob_enable(void); STM32FXXX_GPIOB* gpiob(void);
void gpioc_enable(void); STM32FXXX_GPIOC* gpioc(void);
void gpiod_enable(void); STM32FXXX_GPIOD* gpiod(void);
void gpioe_enable(void); STM32FXXX_GPIOE* gpioe(void);
void gpiof_enable(void); STM32FXXX_GPIOF* gpiof(void);
void gpiog_enable(void); STM32FXXX_GPIOG* gpiog(void);
void gpioh_enable(void); STM32FXXX_GPIOH* gpioh(void);

#endif

/*** EOF ***/

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

