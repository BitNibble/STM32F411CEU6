/******************************************************************************
	STM32 XXX ADC1
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     28022024
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXADC1_H_
	#define _STM32FXXXADC1_H_

/*** Library ***/
#include "stm32f411ceu6.h"
/*** ADC TypeDef ***/
typedef struct {
    void (*on_conversion_complete)(uint16_t value);
    void (*on_error)(uint32_t code);
    void (*on_start)(void);
    void (*on_stop)(void);
} ADC1_Callback;
// ADC -> ADC1
typedef struct
{
	/*** Clock and Nvic ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
	/*** Procedures ***/
	void (*startconversion)(void);
	void (*waitendofconversion)(void);
	/*** Other ***/
	void (*start)(void);
	void (*stop)(void);
	void (*temperaturesetup)(void);
	uint16_t (*readtemperature)(void);

	ADC1_Callback* callback;
}STM32FXXX_ADC1_Handler;

// INIC
void adc1_enable(void); STM32FXXX_ADC1_Handler* adc1(void);

#endif

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

/*** EOF ***/

