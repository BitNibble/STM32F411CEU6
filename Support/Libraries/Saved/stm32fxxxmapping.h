/******************************************************************************
	STM32 XXX MAPPING
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 28022024
Comment:
	-manual um1724, m0390, pm0056, pm0214, and other sources.
	-Virtual Image STM32-XXX, mapping.
	-Still in progress 15062023, increment has go along.
	-Dependent on CMSIS
	-Stable.
*******************************************************************************/
#ifndef _STM32FXXXMAPPING_H_
	#define _STM32FXXXMAPPING_H_
/*** Module Library ***/
// May comment out modules not being used
#include "stm32fxxxsram.h"
#include "stm32fxxxnvic.h"
#include "stm32fxxxadc1.h"
#include "stm32fxxxadc2.h"
#include "stm32fxxxadc3.h"
#include "stm32fxxxcrc.h"
#include "stm32fxxxdma.h"
#include "stm32fxxxflash.h"
#include "stm32fxxxgpio.h"
#include "stm32fxxxsyscfg.h"
#include "stm32fxxxi2c.h"
#include "stm32fxxxpwr.h"
#include "stm32fxxxrcc.h"
#include "stm32fxxxrtc.h"
#include "stm32fxxxtim1and8.h"
#include "stm32fxxxtim2to5.h"
#include "stm32fxxxtim6and7.h"
#include "stm32fxxxtim9to14.h"
#include "stm32fxxxusart.h"
/***** Libraries *****/
#include "armquery.h"
#include "armsystick.h"
/***************** STM32FXXX TypeDef *****************/
typedef struct
{
	#if defined(_STM32FXXXSRAM_H_)
		void (*sram_enable)(void);
		STM32FXXX_SRAM* sram;
	#endif
	#if defined(_STM32FXXXNVIC_H_)
		void (*nvic_enable)(void);
		STM32FXXX_NVIC* nvic;
	#endif
	#if defined(_STM32FXXXADC1_H_)
		void (*adc1_enable)(void);
		STM32FXXX_ADC1* adc1;
	#endif
	#if defined(_STM32FXXXADC2_H_)
		void (*adc2_enable)(void);
		STM32FXXX_ADC2* adc2;
	#endif
	#if defined(_STM32FXXXADC3_H_)
		void (*adc3_enable)(void);
		STM32FXXX_ADC3* adc3;
	#endif
	#if defined(_STM32FXXXCRC_H_)
		void (*crc_enable)(void);
		STM32FXXX_CRC* crc;
	#endif
	#if defined(_STM32FXXXDBGMCU_H_)
	#endif
	#if defined(_STM32FXXXDMA_H_)
		void (*dma1_enable)(void);
		void (*dma2_enable)(void);
		STM32FXXX_DMA1* dma1;
		STM32FXXX_DMA2* dma2;
	#endif
	#if defined(_STM32FXXXEXTI_H_)
	#endif
	#if defined(_STM32FXXXFLASH_H_)
		void (*flash_enable)(void);
		STM32FXXX_FLASH* flash;
	#endif
	#if defined(_STM32FXXXGPIO_H_)
		void (*gpioa_enable)(void);
		STM32FXXX_GPIOA* gpioa;
		void (*gpiob_enable)(void);
		STM32FXXX_GPIOB* gpiob;
		void (*gpioc_enable)(void);
		STM32FXXX_GPIOC* gpioc;
		void (*gpiod_enable)(void);
		STM32FXXX_GPIOD* gpiod;
		void (*gpioe_enable)(void);
		STM32FXXX_GPIOE* gpioe;
		void (*gpiof_enable)(void);
		STM32FXXX_GPIOF* gpiof;
		void (*gpiog_enable)(void);
		STM32FXXX_GPIOG* gpiog;
		void (*gpioh_enable)(void);
		STM32FXXX_GPIOH* gpioh;
	#endif
	#if defined(_STM32FXXXSYSCFG_H_)
		void (*syscfg_enable)(void);
		STM32FXXX_SYSCFG* syscfg;
	#endif
	#if defined(_STM32FXXXI2C_H_)
		void (*i2c1_enable)(uint32_t SclClock);
		void (*i2c2_enable)(uint32_t SclClock);
		void (*i2c3_enable)(uint32_t SclClock);
		STM32FXXX_I2C1_Handler* i2c1;
		STM32FXXX_I2C2_Handler* i2c2;
		STM32FXXX_I2C3_Handler* i2c3;
	#endif
	#if defined(_STM32FXXXIWDG_H_)
	#endif
	#if defined(_STM32FXXXPWR_H_)
		void (*pwr_enable)(void);
		STM32FXXX_PWR* pwr;
	#endif
	#if defined(_STM32FXXXRCC_H_)
		void (*rcc_enable)(void);
		STM32FXXX_RCC* rcc;
	#endif
	#if defined(_STM32FXXXRTC_H_)
		void (*rtc_enable)(void);
		STM32FXXX_RTC* rtc;
	#endif
	#if defined(_STM32FXXXSDIO_H_)
	#endif
	#if defined(_STM32FXXXSPI_H_)
	#endif
	#if defined(_STM32FXXXTIM1AND8_H_)
		void (*tim1_enable)(void);
		void (*tim8_enable)(void);
		STM32FXXX_TIM1* tim1;
		STM32FXXX_TIM8* tim8;
	#endif
	#if defined(_STM32FXXXTIM2TO5_H_)
		void (*tim2_enable)(void);
		void (*tim3_enable)(void);
		void (*tim4_enable)(void);
		void (*tim5_enable)(void);
		STM32FXXX_TIM2* tim2;
		STM32FXXX_TIM3* tim3;
		STM32FXXX_TIM4* tim4;
		STM32FXXX_TIM5* tim5;
	#endif
	#if defined(_STM32FXXXTIM6AND7_H_)
		void (*tim6_enable)(void);
		void (*tim7_enable)(void);
		STM32FXXX_TIM6* tim6;
		STM32FXXX_TIM7* tim7;
	#endif
	#if defined(_STM32FXXXTIM9TO14_H_)
		void (*tim9_enable)(void);
		void (*tim10_enable)(void);
		void (*tim11_enable)(void);
		void (*tim12_enable)(void);
		void (*tim13_enable)(void);
		void (*tim14_enable)(void);
		STM32FXXX_TIM9* tim9;
		STM32FXXX_TIM10* tim10;
		STM32FXXX_TIM11* tim11;
		STM32FXXX_TIM12* tim12;
		STM32FXXX_TIM13* tim13;
		STM32FXXX_TIM14* tim14;
	#endif
	#if defined(_STM32FXXXUSART_H_)
		void (*usart1_enable)(void);
		void (*usart2_enable)(void);
		void (*usart3_enable)(void);
		void (*uart4_enable)(void);
		void (*uart5_enable)(void);
		void (*usart6_enable)(void);
		STM32FXXX_USART1* usart1;
		STM32FXXX_USART2* usart2;
		STM32FXXX_USART3* usart3;
		STM32FXXX_UART4* uart4;
		STM32FXXX_UART5* uart5;
		STM32FXXX_USART6* usart6;
	#endif
	#if defined(_STM32FXXXWWDG_H_)
	#endif
	#if defined(_STM32FXXXUSB_H_)
	#endif
}STM32FXXX;

/*** Global ***/
void STM32FXXX_enable(void);
STM32FXXX* stm(void);

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

TypeDef->Instance->Handler
******/

/***EOF***/

