/**********************************************************************
	STM32F411CEU6
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32F411CEU6
Date:     30092025
**********************************************************************/
#ifndef _STM32F411CEU6_INSTANCE_H_
	#define _STM32F411CEU6_INSTANCE_H_

/******************* CMSIS BASE ********************/
// SELECTION OF CHIP (CMSIS Access to its libraries)
/*** Options: __STM32F446xx_H    __STM32F411xE_H ***/
#include "stm32f4xx.h"
#include "stm32fxxxtool.h"

/*** Define & Macro ***/
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
/****************************************/
/****   PLL ON -> 1    PLL OFF = 0   ****/
#define PLL_ON_OFF 0
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
	NVIC_Type* const nvic; // ((NVIC_Type*) NVIC_BASE)
	SCB_Type* const scb; // ((SCB_Type*) SCB_BASE)
	SCnSCB_Type* const scnscb; // ((SCnSCB_Type*) SCS_BASE)
	SysTick_Type* const systick; // ((SysTick_Type*) SysTick_BASE)
	ITM_Type* const itm; // ((ITM_Type*) ITM_BASE)
	DWT_Type* const dwt; // ((DWT_Type*) DWT_BASE)
	TPI_Type* const tpi; // ((TPI_Type*) TPI_BASE)
	MPU_Type* const mpu; // ((MPU_Type*) MPU_BASE)
	FPU_Type* const fpu; // ((FPU_Type*) FPU_BASE)
	CoreDebug_Type* const coredebug; // ((CoreDebug_Type*) CoreDebug_BASE)

} STM32F411CEU6_CORE;

typedef struct {
	STM32F411CEU6_CORE* core;
	ADC_TypeDef* const adc1; // ((ADC_TypeDef *) ADC1_BASE)
	ADC_Common_TypeDef* const adc1_common; // ((ADC_Common_TypeDef *) ADC1_COMMON_BASE)
	CRC_TypeDef* const crc; // ((CRC_TypeDef *) CRC_BASE)
	DBGMCU_TypeDef* const dbgmcu; // ((DBGMCU_TypeDef *) DBGMCU_BASE)
	DMA_Stream_TypeDef* const dma1_stream0; // ((DMA_Stream_TypeDef *) DMA1_Stream0_BASE)
	DMA_Stream_TypeDef* const dma1_stream1; // ((DMA_Stream_TypeDef *) DMA1_Stream1_BASE)
	DMA_Stream_TypeDef* const dma1_stream2; // ((DMA_Stream_TypeDef *) DMA1_Stream2_BASE)
	DMA_Stream_TypeDef* const dma1_stream3; // ((DMA_Stream_TypeDef *) DMA1_Stream3_BASE)
	DMA_Stream_TypeDef* const dma1_stream4; // ((DMA_Stream_TypeDef *) DMA1_Stream4_BASE)
	DMA_Stream_TypeDef* const dma1_stream5; // ((DMA_Stream_TypeDef *) DMA1_Stream5_BASE)
	DMA_Stream_TypeDef* const dma1_stream6; // ((DMA_Stream_TypeDef *) DMA1_Stream6_BASE)
	DMA_Stream_TypeDef* const dma1_stream7; // ((DMA_Stream_TypeDef *) DMA1_Stream7_BASE)
	DMA_Stream_TypeDef* const dma2_stream0; // ((DMA_Stream_TypeDef *) DMA2_Stream0_BASE)
	DMA_Stream_TypeDef* const dma2_stream1; // ((DMA_Stream_TypeDef *) DMA2_Stream1_BASE)
	DMA_Stream_TypeDef* const dma2_stream2; // ((DMA_Stream_TypeDef *) DMA2_Stream2_BASE)
	DMA_Stream_TypeDef* const dma2_stream3; // ((DMA_Stream_TypeDef *) DMA2_Stream3_BASE)
	DMA_Stream_TypeDef* const dma2_stream4; // ((DMA_Stream_TypeDef *) DMA2_Stream4_BASE)
	DMA_Stream_TypeDef* const dma2_stream5; // ((DMA_Stream_TypeDef *) DMA2_Stream5_BASE)
	DMA_Stream_TypeDef* const dma2_stream6; // ((DMA_Stream_TypeDef *) DMA2_Stream6_BASE)
	DMA_Stream_TypeDef* const dma2_stream7; // ((DMA_Stream_TypeDef *) DMA2_Stream7_BASE)
	DMA_TypeDef* const dma1; // ((DMA_TypeDef *) DMA1_BASE)
	DMA_TypeDef* const dma2; // ((DMA_TypeDef *) DMA2_BASE)
	EXTI_TypeDef* const exti; // ((EXTI_TypeDef *) EXTI_BASE)
	FLASH_TypeDef* const flash; // ((FLASH_TypeDef *) FLASH_R_BASE)
	GPIO_TypeDef* const gpioa; // ((GPIO_TypeDef *) GPIOA_BASE)
	GPIO_TypeDef* const gpiob; // ((GPIO_TypeDef *) GPIOB_BASE)
	GPIO_TypeDef* const gpioc; // ((GPIO_TypeDef *) GPIOC_BASE)
	GPIO_TypeDef* const gpiod; // ((GPIO_TypeDef *) GPIOD_BASE)
	GPIO_TypeDef* const gpioe; // ((GPIO_TypeDef *) GPIOE_BASE)
	GPIO_TypeDef* const gpioh; // ((GPIO_TypeDef *) GPIOH_BASE)
	SYSCFG_TypeDef* const syscfg; // ((SYSCFG_TypeDef *) SYSCFG_BASE)
	I2C_TypeDef* const i2c1; // ((I2C_TypeDef *) I2C1_BASE)
	I2C_TypeDef* const i2c2; // ((I2C_TypeDef *) I2C2_BASE)
	I2C_TypeDef* const i2c3; // ((I2C_TypeDef *) I2C3_BASE)
	IWDG_TypeDef* const iwdg; // ((IWDG_TypeDef *) IWDG_BASE)
	PWR_TypeDef* const pwr; // ((PWR_TypeDef *) PWR_BASE)
	RCC_TypeDef* const rcc; // ((RCC_TypeDef *) RCC_BASE)
	RTC_TypeDef* const rtc; // ((RTC_TypeDef *) RTC_BASE)
	SDIO_TypeDef* const sdio; // ((SDIO_TypeDef *) SDIO_BASE)
	SPI_TypeDef* const spi1; // ((SPI_TypeDef *) SPI1_BASE)
	SPI_TypeDef* const spi2; // ((SPI_TypeDef *) SPI2_BASE)
	SPI_TypeDef* const spi3; // ((SPI_TypeDef *) SPI3_BASE)
	SPI_TypeDef* const spi4; // ((SPI_TypeDef *) SPI4_BASE)
	SPI_TypeDef* const spi5; // ((SPI_TypeDef *) SPI5_BASE)
	SPI_TypeDef* const i2s2sext; // ((SPI_TypeDef *) I2S2ext_BASE)
	SPI_TypeDef* const i2s3sext; // ((SPI_TypeDef *) I2S3ext_BASE)
	TIM_TypeDef* const tim1; // ((TIM_TypeDef *) TIM1_BASE)
	TIM_TypeDef* const tim2; // ((TIM_TypeDef *) TIM2_BASE)
	TIM_TypeDef* const tim3; // ((TIM_TypeDef *) TIM3_BASE)
	TIM_TypeDef* const tim4; // ((TIM_TypeDef *) TIM4_BASE)
	TIM_TypeDef* const tim5; // ((TIM_TypeDef *) TIM5_BASE)
	TIM_TypeDef* const tim9; // ((TIM_TypeDef *) TIM9_BASE)
	TIM_TypeDef* const tim10; // ((TIM_TypeDef *) TIM10_BASE)
	TIM_TypeDef* const tim11; // ((TIM_TypeDef *) TIM11_BASE)
	USART_TypeDef* const usart1; // ((USART_TypeDef *) USART1_BASE)
	USART_TypeDef* const usart2; // ((USART_TypeDef *) USART2_BASE)
	USART_TypeDef* const usart6; // ((USART_TypeDef *) USART6_BASE)
	WWDG_TypeDef* const wwdg; // ((WWDG_TypeDef *) WWDG_BASE)
	USB_OTG_GlobalTypeDef* const usb_otg_global; // ((USB_OTG_GlobalTypeDef*) USB_OTG_GLOBAL_BASE)
	USB_OTG_DeviceTypeDef* const usb_otg_device; // ((USB_OTG_DeviceTypeDef*) USB_OTG_DEVICE_BASE)
	USB_OTG_INEndpointTypeDef*  const usb_otg_inendpoint; // ((USB_OTG_INEndpointTypeDef*) USB_OTG_IN_ENDPOINT_BASE)
	USB_OTG_OUTEndpointTypeDef* const usb_otg_outendpoint; // ((USB_OTG_OUTEndpointTypeDef*) USB_OTG_OUT_ENDPOINT_BASE)
	USB_OTG_HostTypeDef* const usb_otg_host; // ((USB_OTG_HostTypeDef*) USB_OTG_HOST_BASE)
	USB_OTG_HostChannelTypeDef* const usb_otg_hostchannel; // ((USB_OTG_HostChannelTypeDef*) USB_OTG_HOST_CHANNEL_BASE)
} STM32F411CEU6;
STM32F411CEU6* stm32f411ceu6(void);

/*******************************************************************/
/************************** MISCELLANEOUS **************************/
/*******************************************************************/
uint32_t getpllsourceclk(void);
uint32_t getpllclk(void);
uint32_t getsysclk(void);
uint32_t gethclk(void);
uint32_t getpclk1(void);
uint32_t getpclk2(void);
/*** Scaler ***/
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
uint8_t getpllr(void);

/*******************************************************************/
/************************** MISCELLANEOUS **************************/
/*******************************************************************/
void set_hpins( GPIO_TypeDef* reg, uint16_t hpins );
void clear_hpins( GPIO_TypeDef* reg, uint16_t hpins );
void set_pin( GPIO_TypeDef* reg, uint8_t pin );
void clear_pin( GPIO_TypeDef* reg, uint8_t pin );
void Usart_WordLength( USART_TypeDef* usart, uint8_t wordlength );
void Usart_StopBits( USART_TypeDef* usart, double stopbits );
void Usart_SamplingMode( USART_TypeDef* usart, uint8_t samplingmode, uint32_t baudrate);
void fpu_enable(void);

#endif
/*** EOF ***/

