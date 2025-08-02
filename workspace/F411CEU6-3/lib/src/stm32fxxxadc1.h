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
#include "stm32fxxxinstance.h"
/*** ADC TypeDef ***/
// ADC -> ADC1
typedef struct
{
	/*** BitField Mapping ***/
	ADC_TypeDef* instance;
	ADC_Common_TypeDef* common_instance;
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
}STM32FXXX_ADC1;

// INIC
void adc1_enable(void); STM32FXXX_ADC1* adc1(void);

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

