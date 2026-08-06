/**********************************************************************
	STM32F411CEU6
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32F411CEU6
**********************************************************************/
#ifndef STM32F411CEU6_H
	#define STM32F411CEU6_H

#include "stm32f4_dev.h"
#include "stm32x_tool.h"
#include "stm32fxxxgpio.h"
#include "stm32x_gpio.h"

/****************************************/
/*******   0 -> HSI    1->HSE   *********/
#define H_Clock_Source 1
/****   PLL ON -> 1    PLL OFF = 0   ****/
#define PLL_ON_OFF 0
/****************************************/

// Clamping wrappers
#define LIMIT_INC(val, max, min)  ((val) >= (max) ? (min) : (val) + 1)
#define LIMIT_DEC(val, max, min)  ((val) <= (min) ? (max) : (val) - 1)

#endif
/*** EOF ***/

