/**********************************************************************
	STM32F411CEU6
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32F411CEU6
Date:     30092025
**********************************************************************/
#ifndef _STM32F411CEU6_H_
#define _STM32F411CEU6_H_

#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include "stm32f4xx.h"
#include "stm32fxxxtool.h"

/*** Clock sources ***/
#ifndef HSI_RC
#define HSI_RC 16000000UL
#endif
#ifndef HSE_OSC
#define HSE_OSC 25000000UL
#endif
#ifndef LSI
#define LSI 32000UL
#endif
#ifndef LSE
#define LSE 32768UL
#endif
#ifndef HSE_RTC
#define HSE_RTC 4000000UL
#endif

/****************************************/
/*******   0 -> HSI    1->HSE   *********/
#define H_Clock_Source 1
/****   PLL ON -> 1    PLL OFF = 0   ****/
#define PLL_ON_OFF 0
/****************************************/
/****************************************/
typedef union{
	struct UN8bit{
		uint8_t bit0:1;
		uint8_t bit1:1;
		uint8_t bit2:1;
		uint8_t bit3:1;
		uint8_t bit4:1;
		uint8_t bit5:1;
		uint8_t bit6:1;
		uint8_t bit7:1;
	}par;
	uint8_t var;
}_UN8_var;

typedef union{
	struct UN16byte{
		_UN8_var b0;
		_UN8_var b1;
	}par;
	uint16_t var;
}_UN16_var;

typedef union{
	struct UN32word{
		_UN16_var w0;
		_UN16_var w1;
	}par;
	uint32_t var;
}_UN32_var;

typedef union{
	struct UN64dword{
		_UN32_var dw0;
		_UN32_var dw1;
	}par;
	uint64_t var;
}_UN64_var;

/*******************************************************************/
/********************* MAIN HARDWARE LAYER *************************/
/*******************************************************************/
typedef struct {
    NVIC_Type* const nvic;
    SCB_Type* const scb;
    SCnSCB_Type* const scnscb;
    SysTick_Type* const systick;
    ITM_Type* const itm;
    DWT_Type* const dwt;
    TPI_Type* const tpi;
    MPU_Type* const mpu;
    FPU_Type* const fpu;
    CoreDebug_Type* const coredebug;
} STM32F411CEU6_CORE;

typedef struct {
    STM32F411CEU6_CORE* core;

    ADC_TypeDef* const adc1;
    ADC_Common_TypeDef* const adc1_common;
    CRC_TypeDef* const crc;
    DBGMCU_TypeDef* const dbgmcu;
    DMA_Stream_TypeDef* const dma1_stream0;
    DMA_Stream_TypeDef* const dma1_stream1;
    DMA_Stream_TypeDef* const dma1_stream2;
    DMA_Stream_TypeDef* const dma1_stream3;
    DMA_Stream_TypeDef* const dma1_stream4;
    DMA_Stream_TypeDef* const dma1_stream5;
    DMA_Stream_TypeDef* const dma1_stream6;
    DMA_Stream_TypeDef* const dma1_stream7;
    DMA_Stream_TypeDef* const dma2_stream0;
    DMA_Stream_TypeDef* const dma2_stream1;
    DMA_Stream_TypeDef* const dma2_stream2;
    DMA_Stream_TypeDef* const dma2_stream3;
    DMA_Stream_TypeDef* const dma2_stream4;
    DMA_Stream_TypeDef* const dma2_stream5;
    DMA_Stream_TypeDef* const dma2_stream6;
    DMA_Stream_TypeDef* const dma2_stream7;
    DMA_TypeDef* const dma1;
    DMA_TypeDef* const dma2;
    EXTI_TypeDef* const exti;
    FLASH_TypeDef* const flash;
    GPIO_TypeDef* const gpioa;
    GPIO_TypeDef* const gpiob;
    GPIO_TypeDef* const gpioc;
    GPIO_TypeDef* const gpiod;
    GPIO_TypeDef* const gpioe;
    GPIO_TypeDef* const gpioh;
    SYSCFG_TypeDef* const syscfg;
    I2C_TypeDef* const i2c1;
    I2C_TypeDef* const i2c2;
    I2C_TypeDef* const i2c3;
    IWDG_TypeDef* const iwdg;
    PWR_TypeDef* const pwr;
    RCC_TypeDef* const rcc;
    RTC_TypeDef* const rtc;
    SDIO_TypeDef* const sdio;
    SPI_TypeDef* const spi1;
    SPI_TypeDef* const spi2;
    SPI_TypeDef* const spi3;
    SPI_TypeDef* const spi4;
    SPI_TypeDef* const spi5;
    SPI_TypeDef* const i2s2sext;
    SPI_TypeDef* const i2s3sext;
    TIM_TypeDef* const tim1;
    TIM_TypeDef* const tim2;
    TIM_TypeDef* const tim3;
    TIM_TypeDef* const tim4;
    TIM_TypeDef* const tim5;
    TIM_TypeDef* const tim9;
    TIM_TypeDef* const tim10;
    TIM_TypeDef* const tim11;
    USART_TypeDef* const usart1;
    USART_TypeDef* const usart2;
    USART_TypeDef* const usart6;
    WWDG_TypeDef* const wwdg;
    USB_OTG_GlobalTypeDef* const usb_otg_global;
    USB_OTG_DeviceTypeDef* const usb_otg_device;
    USB_OTG_INEndpointTypeDef* const usb_otg_inendpoint;
    USB_OTG_OUTEndpointTypeDef* const usb_otg_outendpoint;
    USB_OTG_HostTypeDef* const usb_otg_host;
    USB_OTG_HostChannelTypeDef* const usb_otg_hostchannel;

} STM32F411CEU6;

STM32F411CEU6* stm32f411ceu6(void);

/*******************************************************************/
/************************** CLOCK GETTERS **************************/
/*******************************************************************/
uint16_t gethpre(void);
uint8_t gethppre1(void);
uint8_t gethppre2(void);
uint8_t getrtcpre(void);
uint8_t gethmco1pre(void);
uint8_t gethmco2pre(void);
uint8_t getpllm(void);
uint16_t getplln(void);
uint8_t getpllp(void);
uint8_t getpllq(void);
uint8_t getpllr(void); // F446 only

uint32_t getpllsourceclk(void);
uint32_t getpllclk(void);
uint32_t getsysclk(void);
uint32_t gethclk(void);
uint32_t getpclk1(void);
uint32_t getpclk2(void);

/*******************************************************************/
/************************** GPIO & USART ***************************/
/*******************************************************************/
void set_hpins(GPIO_TypeDef* reg, uint16_t hpins);
void clear_hpins(GPIO_TypeDef* reg, uint16_t hpins);
void set_pin(GPIO_TypeDef* reg, uint8_t pin);
void clear_pin(GPIO_TypeDef* reg, uint8_t pin);

void Usart_WordLength(USART_TypeDef* usart, uint8_t wordlength);
void Usart_StopBits(USART_TypeDef* usart, double stopbits);
void Usart_SamplingMode(USART_TypeDef* usart, uint8_t samplingmode, uint32_t baudrate);

void fpu_enable(void);

#endif

/*** EOF ***/

