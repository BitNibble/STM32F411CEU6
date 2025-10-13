/**********************************************************************
	STM32F411CEU6
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32F411CEU6
Date:     30092025
**********************************************************************/
#include "stm32f411ceu6.h"
#include <math.h>

/*******************************************************************/
/********************* MAIN HARDWARE LAYER *************************/
/*******************************************************************/
static STM32F411CEU6_CORE_Handler stm32f411ceu6_core_setup = {
    .nvic = ((NVIC_Type*) NVIC_BASE),
    .scb = ((SCB_Type*) SCB_BASE),
    .scnscb = ((SCnSCB_Type*) SCS_BASE),
    .systick = ((SysTick_Type*) SysTick_BASE),
    .itm = ((ITM_Type*) ITM_BASE),
    .dwt = ((DWT_Type*) DWT_BASE),
    .tpi = ((TPI_Type*) TPI_BASE),
    .mpu = ((MPU_Type*) MPU_BASE),
    .fpu = ((FPU_Type*) FPU_BASE),
    .coredebug = ((CoreDebug_Type*) CoreDebug_BASE)
};

static STM32F411CEU6_Handler stm32f411ceu6_setup = {
    .core = &stm32f411ceu6_core_setup,
    .adc1 = ((ADC_TypeDef *) ADC1_BASE),
    .adc1_common = ((ADC_Common_TypeDef *) ADC1_COMMON_BASE),
    .crc = ((CRC_TypeDef *) CRC_BASE),
    .dbgmcu = ((DBGMCU_TypeDef *) DBGMCU_BASE),
    .dma1_stream0 = ((DMA_Stream_TypeDef *) DMA1_Stream0_BASE),
    .dma1_stream1 = ((DMA_Stream_TypeDef *) DMA1_Stream1_BASE),
    .dma1_stream2 = ((DMA_Stream_TypeDef *) DMA1_Stream2_BASE),
    .dma1_stream3 = ((DMA_Stream_TypeDef *) DMA1_Stream3_BASE),
    .dma1_stream4 = ((DMA_Stream_TypeDef *) DMA1_Stream4_BASE),
    .dma1_stream5 = ((DMA_Stream_TypeDef *) DMA1_Stream5_BASE),
    .dma1_stream6 = ((DMA_Stream_TypeDef *) DMA1_Stream6_BASE),
    .dma1_stream7 = ((DMA_Stream_TypeDef *) DMA1_Stream7_BASE),
    .dma2_stream0 = ((DMA_Stream_TypeDef *) DMA2_Stream0_BASE),
    .dma2_stream1 = ((DMA_Stream_TypeDef *) DMA2_Stream1_BASE),
    .dma2_stream2 = ((DMA_Stream_TypeDef *) DMA2_Stream2_BASE),
    .dma2_stream3 = ((DMA_Stream_TypeDef *) DMA2_Stream3_BASE),
    .dma2_stream4 = ((DMA_Stream_TypeDef *) DMA2_Stream4_BASE),
    .dma2_stream5 = ((DMA_Stream_TypeDef *) DMA2_Stream5_BASE),
    .dma2_stream6 = ((DMA_Stream_TypeDef *) DMA2_Stream6_BASE),
    .dma2_stream7 = ((DMA_Stream_TypeDef *) DMA2_Stream7_BASE),
    .dma1 = ((DMA_TypeDef *) DMA1_BASE),
    .dma2 = ((DMA_TypeDef *) DMA2_BASE),
    .exti = ((EXTI_TypeDef *) EXTI_BASE),
    .flash = ((FLASH_TypeDef *) FLASH_R_BASE),
    .gpioa = ((GPIO_TypeDef *) GPIOA_BASE),
    .gpiob = ((GPIO_TypeDef *) GPIOB_BASE),
    .gpioc = ((GPIO_TypeDef *) GPIOC_BASE),
    .gpiod = ((GPIO_TypeDef *) GPIOD_BASE),
    .gpioe = ((GPIO_TypeDef *) GPIOE_BASE),
    .gpioh = ((GPIO_TypeDef *) GPIOH_BASE),
    .syscfg = ((SYSCFG_TypeDef *) SYSCFG_BASE),
    .i2c1 = ((I2C_TypeDef *) I2C1_BASE),
    .i2c2 = ((I2C_TypeDef *) I2C2_BASE),
    .i2c3 = ((I2C_TypeDef *) I2C3_BASE),
    .iwdg = ((IWDG_TypeDef *) IWDG_BASE),
    .pwr = ((PWR_TypeDef *) PWR_BASE),
    .rcc = ((RCC_TypeDef *) RCC_BASE),
    .rtc = ((RTC_TypeDef *) RTC_BASE),
    .sdio = ((SDIO_TypeDef *) SDIO_BASE),
    .spi1 = ((SPI_TypeDef *) SPI1_BASE),
    .spi2 = ((SPI_TypeDef *) SPI2_BASE),
    .spi3 = ((SPI_TypeDef *) SPI3_BASE),
    .spi4 = ((SPI_TypeDef *) SPI4_BASE),
    .spi5 = ((SPI_TypeDef *) SPI5_BASE),
    .i2s2sext = ((SPI_TypeDef *) I2S2ext_BASE),
    .i2s3sext = ((SPI_TypeDef *) I2S3ext_BASE),
    .tim1 = ((TIM_TypeDef *) TIM1_BASE),
    .tim2 = ((TIM_TypeDef *) TIM2_BASE),
    .tim3 = ((TIM_TypeDef *) TIM3_BASE),
    .tim4 = ((TIM_TypeDef *) TIM4_BASE),
    .tim5 = ((TIM_TypeDef *) TIM5_BASE),
    .tim9 = ((TIM_TypeDef *) TIM9_BASE),
    .tim10 = ((TIM_TypeDef *) TIM10_BASE),
    .tim11 = ((TIM_TypeDef *) TIM11_BASE),
    .usart1 = ((USART_TypeDef *) USART1_BASE),
    .usart2 = ((USART_TypeDef *) USART2_BASE),
    .usart6 = ((USART_TypeDef *) USART6_BASE),
    .wwdg = ((WWDG_TypeDef *) WWDG_BASE),
    .usb_otg_global = ((USB_OTG_GlobalTypeDef*) USB_OTG_GLOBAL_BASE),
    .usb_otg_device = ((USB_OTG_DeviceTypeDef*) USB_OTG_DEVICE_BASE),
    .usb_otg_inendpoint = ((USB_OTG_INEndpointTypeDef*) USB_OTG_IN_ENDPOINT_BASE),
    .usb_otg_outendpoint = ((USB_OTG_OUTEndpointTypeDef*) USB_OTG_OUT_ENDPOINT_BASE),
    .usb_otg_host = ((USB_OTG_HostTypeDef*) USB_OTG_HOST_BASE),
    .usb_otg_hostchannel = ((USB_OTG_HostChannelTypeDef*) USB_OTG_HOST_CHANNEL_BASE)
};

STM32F411CEU6_Handler* stm32f411ceu6(void){ return &stm32f411ceu6_setup; }

/*******************************************************************/
/************************** LOOKUP TABLES **************************/
/*******************************************************************/
static const uint16_t hpre_table[16] = {
    1,1,1,1,1,1,1,1,2,4,8,16,64,128,256,512
};

static const uint8_t ppre_table[8] = {1,1,1,1,2,4,8,16};

static const uint8_t mco_table[8] = {1,1,1,1,2,3,4,5};

/*******************************************************************/
/************************** CLOCK GETTERS **************************/
/*******************************************************************/
uint16_t get_hpre(void) {
    uint32_t value = get_reg_Msk(RCC->CFGR, RCC_CFGR_HPRE);
    return hpre_table[value];
}

uint8_t get_hppre1(void) {
    uint32_t value = get_reg_Msk(RCC->CFGR, RCC_CFGR_PPRE1);
    return ppre_table[value];
}

uint8_t get_hppre2(void) {
    uint32_t value = get_reg_Msk(RCC->CFGR, RCC_CFGR_PPRE2);
    return ppre_table[value];
}

uint8_t get_hmco1pre(void) {
    uint32_t value = get_reg_Msk(RCC->CFGR, RCC_CFGR_MCO1PRE);
    return mco_table[value];
}

uint8_t get_hmco2pre(void) {
    uint32_t value = get_reg_Msk(RCC->CFGR, RCC_CFGR_MCO2PRE);
    return mco_table[value];
}

uint8_t get_rtcpre(void) {
    return get_reg_Msk(RCC->CFGR, RCC_CFGR_RTCPRE);
}

uint8_t get_pllm(void) {
    return get_reg_Msk(RCC->PLLCFGR, RCC_PLLCFGR_PLLM);
}

uint16_t get_plln(void) {
    return get_reg_Msk(RCC->PLLCFGR, RCC_PLLCFGR_PLLN);
}

uint8_t get_pllp(void) {
    uint32_t value = get_reg_Msk(RCC->PLLCFGR, RCC_PLLCFGR_PLLP);
    switch(value){
        case 0b00: return 2;
        case 0b01: return 4;
        case 0b10: return 6;
        case 0b11: return 8;
        default: return 2;
    }
}

uint8_t get_pllq(void) {
    return get_reg_Msk(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ);
}

#ifdef STM32F446xx
uint8_t get_pllr(void) {
    return get_reg_Msk(RCC->PLLCFGR, RCC_PLLCFGR_PLLR);
}
#endif

uint32_t get_pllsourceclk(void) {
    return get_reg_Msk(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC) ? HSE_OSC : HSI_RC;
}

uint32_t get_pllclk(void) {
    uint32_t clk = get_pllsourceclk() / get_pllm();
    clk /= get_pllp();
    clk *= get_plln();
    return clk;
}

uint32_t get_sysclk(void) {
    uint32_t sws = get_reg_Msk(RCC->CFGR, RCC_CFGR_SWS);
    switch(sws) {
        case 0: return HSI_RC;
        case 1: return HSE_OSC;
        case 2: return get_pllclk();
        default: return HSI_RC;
    }
}

uint32_t get_hclk(void) {
    return get_sysclk() / get_hpre();
}

uint32_t get_pclk1(void) {
    return get_hclk() / get_hppre1();
}

uint32_t get_pclk2(void) {
    return get_hclk() / get_hppre2();
}

/*******************************************************************/
/************************** GPIO UTILS *****************************/
/*******************************************************************/
inline void set_hpins(GPIO_TypeDef* reg, uint16_t hpins) {
    reg->BSRR = hpins;
}

inline void clear_hpins(GPIO_TypeDef* reg, uint16_t hpins) {
    reg->BSRR = ((uint32_t)hpins) << 16;
}

inline void set_pin(GPIO_TypeDef* reg, uint8_t pin) {
    reg->BSRR = (1 << pin);
}

inline void clear_pin(GPIO_TypeDef* reg, uint8_t pin) {
    reg->BSRR = ((uint32_t)(1 << pin)) << 16;
}

/*******************************************************************/
/************************** USART UTILS ***************************/
/*******************************************************************/
void Usart_WordLength(USART_TypeDef* usart, uint8_t wordlength) {
    if(wordlength == 9) usart->CR1 |= (1 << 12);
    else usart->CR1 &= ~(1 << 12);
}

void Usart_StopBits(USART_TypeDef* usart, double stopbits) {
    usart->CR2 &= ~((1 << 12) | (1 << 13));
    if(fabs(stopbits-0.5)<1e-6) usart->CR2 |= (1 << 12);
    else if(fabs(stopbits-1.5)<1e-6) usart->CR2 |= (1<<13)|(1<<12);
    else if(fabs(stopbits-2.0)<1e-6) usart->CR2 |= (1 << 13);
}

void Usart_SamplingMode(USART_TypeDef* usart, uint8_t samplingmode, uint32_t baudrate) {
    if(samplingmode==8) usart->CR1 |= (1 << 15);
    else { usart->CR1 &= ~(1<<15); samplingmode=16; }

    uint32_t pclk = (usart==USART1 || usart==USART6)? get_pclk2() : get_pclk1();
    double usartdiv = (double)pclk / (samplingmode * baudrate);
    uint32_t mantissa = (uint32_t)usartdiv;
    double fractionf = usartdiv - mantissa;
    uint32_t brr = 0;

    if(samplingmode==16) {
        uint32_t fraction = (uint32_t)round(fractionf*16);
        if(fraction==16){ mantissa++; fraction=0; }
        brr = (mantissa<<4) | (fraction & 0xF);
    } else {
        uint32_t fraction = (uint32_t)round(fractionf*8);
        if(fraction==8){ mantissa++; fraction=0; }
        brr = (mantissa<<4) | ((fraction & 0x7)<<1);
    }
    usart->BRR = brr;
}

/*******************************************************************/
/************************** FPU ENABLE *****************************/
/*******************************************************************/
void fpu_enable(void) {
    SCB->CPACR |= (0xF << 20);
}

/*** EOF ***/

