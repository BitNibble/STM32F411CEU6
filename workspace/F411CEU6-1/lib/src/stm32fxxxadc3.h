/******************************************************************************
	STM32 XXX ADC3
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     28022024
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXADC3_H_
	#define _STM32FXXXADC3_H_

/*** Library ***/
#if defined (STM32F411xE)
	#include "stm32f411ceu6.h"
#elif defined(STM32F446xx)
	#include "stm32f446re.h"
#else
	void* dev(void){ return NULL; }
#endif
/*** ADC TypeDef ***/
typedef struct {
    void (*on_conversion_complete)(uint16_t value);
    void (*on_error)(uint32_t code);
    void (*on_start)(void);
    void (*on_stop)(void);
} ADC3_Callback;
// ADC -> ADC3
typedef struct
{
	/*** Clock and Nvic ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
	/*** Other ***/
	void (*start)(void);
	void (*stop)(void);

	ADC3_Callback* callback;

#if defined(STM32F411CEU6_H)
	STM32F411CEU6_Handler* (*dev)(void);
#elif defined(STM32F446RE_H)
	STM32F446RE_Handler* (*dev)(void);
#else
	void* (*dev)(void);
#endif
}STM32FXXX_ADC3_Handler;

// INIC
void adc3_enable(void); STM32FXXX_ADC3_Handler* adc3(void);

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

