/************************************************************************
	STM32FXXX INSTANCE
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32FXXX
Update: 07/01/2024
Comment:
	
************************************************************************/
#pragma once
/************ CMSIS BASE *************/
// SELECTION OF CHIP (CMSIS Access to its libraries)
// Options: __STM32F446xx_H    __STM32F411xE_H
#include "stm32f4xx.h"
#include <inttypes.h>
/*** General Purpose Bit field ***/
typedef union{
	struct UN32nibble{
		uint32_t n0:4;
		uint32_t n1:4;
		uint32_t n2:4;
		uint32_t n3:4;
		uint32_t n4:4;
		uint32_t n5:4;
		uint32_t n6:4;
		uint32_t n7:4;
	}nibble;
	struct UN32byte{
		uint8_t b0;
		uint8_t b1;
		uint8_t b2;
		uint8_t b3;
	}byte;
	struct UN32word{
		uint16_t w0;
		uint16_t w1;
	}word;
	uint32_t n;
}_UN32var;
typedef union{
	struct UN64nibble{
		uint32_t n0:4;
		uint32_t n1:4;
		uint32_t n2:4;
		uint32_t n3:4;
		uint32_t n4:4;
		uint32_t n5:4;
		uint32_t n6:4;
		uint32_t n7:4;
		uint32_t n8:4;
		uint32_t n9:4;
		uint32_t n10:4;
		uint32_t n11:4;
		uint32_t n12:4;
		uint32_t n13:4;
		uint32_t n14:4;
		uint32_t n15:4;
	}nibble;
	struct UN64byte{
		uint8_t b0;
		uint8_t b1;
		uint8_t b2;
		uint8_t b3;
		uint8_t b4;
		uint8_t b5;
		uint8_t b6;
		uint8_t b7;
	}byte;
	struct UN64word{
		uint16_t w0;
		uint16_t w1;
		uint16_t w2;
		uint16_t w3;
	}word;
	struct UN64dword{
		uint32_t d0;
		uint32_t d1;
	}dword;
	uint64_t n;
}_UN64var;
/*** Alternative CMSIS replacement ***/
//#include "stm32gpiobf.h"
//#include "stm32rccbf.h"
//#include "stm32timbf.h"
//#include "stm32usartbf.h"
//#include "stm32adcbf.h"
//#include "stm32i2cbf.h"
/*************************************/
/********* HARDWARE HANDLER **********/
/*************************************/
/*** ADC ***/
ADC_Common_TypeDef* adc_common_instance(void);
//STM32FXXXADC_COMMON_TypeDef* adc_common_instance(void);
ADC_TypeDef* adc1_instance(void);
//STM32FXXXADC_TypeDef* adc1_instance(void);
ADC_TypeDef* adc2_instance(void);
//STM32FXXXADC_TypeDef* adc2_instance(void);
ADC_TypeDef* adc3_instance(void);
//STM32FXXXADC_TypeDef* adc3_instance(void);
/*** CAN ***/
#ifdef STM32F446xx
CAN_TypeDef* can1_instance(void);
CAN_TypeDef* can2_instance(void);
/*** CEC ***/
CEC_TypeDef* cec_instance(void);
#endif
/*** CRC ***/
CRC_TypeDef* crc_instance(void);
/*** DAC ***/
#ifdef STM32F446xx
DAC_TypeDef* dac_instance(void);
#endif
/*** DBGMCU ***/
DBGMCU_TypeDef* dbgmcu_instance(void);
/*** DCMI ***/
#ifdef STM32F446xx
DCMI_TypeDef* dcmi_instance(void);
#endif
/*** DMA ***/
DMA_TypeDef* dma1_instance(void);
DMA_Stream_TypeDef* dma1_stream0_instance(void);
DMA_Stream_TypeDef* dma1_stream1_instance(void);
DMA_Stream_TypeDef* dma1_stream2_instance(void);
DMA_Stream_TypeDef* dma1_stream3_instance(void);
DMA_Stream_TypeDef* dma1_stream4_instance(void);
DMA_Stream_TypeDef* dma1_stream5_instance(void);
DMA_Stream_TypeDef* dma1_stream6_instance(void);
DMA_Stream_TypeDef* dma1_stream7_instance(void);
DMA_TypeDef* dma2_instance(void);
DMA_Stream_TypeDef* dma2_stream0_instance(void);
DMA_Stream_TypeDef* dma2_stream1_instance(void);
DMA_Stream_TypeDef* dma2_stream2_instance(void);
DMA_Stream_TypeDef* dma2_stream3_instance(void);
DMA_Stream_TypeDef* dma2_stream4_instance(void);
DMA_Stream_TypeDef* dma2_stream5_instance(void);
DMA_Stream_TypeDef* dma2_stream6_instance(void);
DMA_Stream_TypeDef* dma2_stream7_instance(void);
/*** EXTI ***/
EXTI_TypeDef* exti_instance(void);
/*** FLASH ***/
FLASH_TypeDef* flash_instance(void);
/*** FMC ***/
#ifdef STM32F446xx
FMC_Bank1_TypeDef* fmc_bank1_instance(void);
FMC_Bank1E_TypeDef* fmc_bank1e_instance(void);
FMC_Bank3_TypeDef* fmc_bank3_instance(void);
FMC_Bank5_6_TypeDef* fmc_bank5_6_instance(void);
#endif
/*** GPIO ***/
GPIO_TypeDef* gpioa_instance(void);
GPIO_TypeDef* gpiob_instance(void);
GPIO_TypeDef* gpioc_instance(void);
GPIO_TypeDef* gpiod_instance(void);
GPIO_TypeDef* gpioe_instance(void);
GPIO_TypeDef* gpiof_instance(void);
GPIO_TypeDef* gpiog_instance(void);
GPIO_TypeDef* gpioh_instance(void);
/*** SYSCFG ***/
SYSCFG_TypeDef* syscfg_instance(void);
/*** I2C ***/
I2C_TypeDef* i2c1_instance(void);
I2C_TypeDef* i2c2_instance(void);
I2C_TypeDef* i2c3_instance(void);
/*** FMPI2C ***/
#ifdef STM32F446xx
FMPI2C_TypeDef* fmpi2c1_instance(void);
#endif
/*** IWDG ***/
IWDG_TypeDef* iwdg_instance(void);
/*** PWR ***/
PWR_TypeDef* pwr_instance(void);
/*** RCC ***/
RCC_TypeDef* rcc_instance(void);
/*** RTC ***/
RTC_TypeDef* rtc_instance(void);
/*** SAI ***/
#ifdef STM32F446xx
//SAI_TypeDef* sai1_instance(void){return (SAI_TypeDef*) SAI1_BASE;}
SAI_Block_TypeDef* sai1_block_a_instance(void);
SAI_Block_TypeDef* sai1_block_b_instance(void);
SAI_TypeDef* sai2_instance(void);
SAI_Block_TypeDef* sai2_block_a_instance(void);
SAI_Block_TypeDef* sai2_block_b_instance(void);
#endif
/*** SDIO ***/
SDIO_TypeDef* sdio_instance(void);
/*** SPI ***/
SPI_TypeDef* spi1_instance(void);
SPI_TypeDef* spi2_instance(void);
SPI_TypeDef* spi3_instance(void);
SPI_TypeDef* spi4_instance(void);
/*** QUADSPI ***/
#ifdef STM32F446xx
QUADSPI_TypeDef* quadspi_instance(void);
#endif
/*** SPDIFRX ***/
#ifdef STM32F446xx
SPDIFRX_TypeDef* spdifrx_instance(void);
#endif
/*** TIM ***/
TIM_TypeDef* tim1_instance(void);
TIM_TypeDef* tim2_instance(void);
TIM_TypeDef* tim3_instance(void);
TIM_TypeDef* tim4_instance(void);
TIM_TypeDef* tim5_instance(void);
TIM_TypeDef* tim6_instance(void);
TIM_TypeDef* tim7_instance(void);
TIM_TypeDef* tim8_instance(void);
TIM_TypeDef* tim9_instance(void);
TIM_TypeDef* tim10_instance(void);
TIM_TypeDef* tim11_instance(void);
TIM_TypeDef* tim12_instance(void);
TIM_TypeDef* tim13_instance(void);
TIM_TypeDef* tim14_instance(void);
/*** USART ***/
USART_TypeDef* usart1_instance(void);
USART_TypeDef* usart2_instance(void);
USART_TypeDef* usart3_instance(void);
USART_TypeDef* uart4_instance(void);
USART_TypeDef* uart5_instance(void);
USART_TypeDef* usart6_instance(void);
/*** WWDG ***/
WWDG_TypeDef* wwdg_instance(void);
/*** USB ***/
USB_OTG_GlobalTypeDef* usb_otg_global_instance(void);
USB_OTG_DeviceTypeDef* usb_otg_device_instance(void);
USB_OTG_INEndpointTypeDef* usb_otg_inendpoint_instance(void);
USB_OTG_OUTEndpointTypeDef* usb_otg_outendpoint_instance(void);
USB_OTG_HostTypeDef* usb_otg_host_instance(void);
USB_OTG_HostChannelTypeDef* usb_otg_hotchannel_instance(void);

/*** Tools ***/
void set_reg(volatile uint32_t* reg, uint32_t hbits);
void clear_reg(volatile uint32_t* reg, uint32_t hbits);
uint32_t get_reg_Msk(uint32_t reg, uint32_t Msk, uint8_t Pos);
void write_reg_Msk(volatile uint32_t* reg, uint32_t Msk, uint8_t Pos, uint32_t data);
void set_reg_Msk(volatile uint32_t* reg, uint32_t Msk, uint8_t Pos, uint32_t data);
void set_hpins( GPIO_TypeDef* reg, uint16_t hpins );
void clear_hpins( GPIO_TypeDef* reg, uint16_t hpins );
void set_pin( GPIO_TypeDef* reg, uint8_t pin );
void clear_pin( GPIO_TypeDef* reg, uint8_t pin );
uint32_t get_reg_block(uint32_t reg, uint8_t size_block, uint8_t bit_n);
void write_reg_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data);
void set_reg_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data);
uint32_t get_bit_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n);
void set_bit_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data);

/***

***/

/*** EOF ***/

