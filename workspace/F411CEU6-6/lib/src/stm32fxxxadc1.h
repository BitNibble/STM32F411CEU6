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
typedef const struct
{
	/*** Clock and Nvic ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
	/*** Procedures ***/
	void (*start_conversion)(void);
	void (*wait_end_of_conversion)(void);
	/*** Other ***/
	void (*start)(void);
	void (*stop)(void);
	void (*temperature_setup)(void);
	uint16_t (*read_temperature)(void);

	ADC1_Callback* callback;
}STM32FXXX_ADC1_Handler;

// INIC
STM32FXXX_ADC1_Handler* adc1(void);

#endif
/*** EOF ***/

