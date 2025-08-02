/******************************************************************************
	STM32 XXX ADC1
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 28022024
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
	/*** Other ***/
	void (*clock)(uint8_t state);
	void (*nvic)(uint8_t state);
}STM32FXXX_ADC1;

// INIC
void adc1_enable(void);
STM32FXXX_ADC1* adc1(void);

/***** ADC1 Procedure & Function Header ******/
void STM32FXXXAdc1Clock(uint8_t state);
void STM32FXXXAdc1Nvic(uint8_t state);

/****** MISCELLANEOUS ******/
void ADC_TemperatureSetup(void);
uint16_t ADC_ReadTemperature(void);
float CalculateTemperature(uint16_t adc_value);

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

