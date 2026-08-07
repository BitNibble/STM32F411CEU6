/**********************************************************************
	stm32g4_dev.c
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32F4 Family
**********************************************************************/
#include "stm32f4_dev.h"
#include "stm32x_tool.h"
#include <stdarg.h>
#include <math.h>

/*******************************************************************/
/********************* MAIN HARDWARE LAYER *************************/
/*******************************************************************/
static STM32F411CEU6_CORE_Instance stm32f411ceu6_core_setup = {
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

static STM32_DEVICE stm32f411ceu6_setup = {
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

const STM32_DEVICE* dev(void){ return &stm32f411ceu6_setup; }

/*******************************************************************/
/*********************** CLOCK LOOKUP TABLES ***********************/
/*******************************************************************/
static const uint16_t hpre_table[16] = {
    1,1,1,1,1,1,1,1,2,4,8,16,64,128,256,512
};

static const uint8_t ppre_table[8] = {1,1,1,1,2,4,8,16};

static const uint8_t mco_table[8] = {1,1,1,1,2,3,4,5};

/*******************************************************************/
/*************************** CLOCK Query ***************************/
/*******************************************************************/
uint16_t get_hpre(void) {
    uint32_t value = exe()->get_field(dev()->rcc->CFGR, RCC_CFGR_HPRE, RCC_CFGR_HPRE_Pos);
    return hpre_table[value];
}

uint8_t get_hppre1(void) {
    uint32_t value = exe()->get_field(dev()->rcc->CFGR, RCC_CFGR_PPRE1, RCC_CFGR_PPRE1_Pos);
    return ppre_table[value];
}

uint8_t get_hppre2(void) {
    uint32_t value = exe()->get_field(dev()->rcc->CFGR, RCC_CFGR_PPRE2, RCC_CFGR_PPRE2_Pos);
    return ppre_table[value];
}

uint8_t get_systickpre(void) {
    uint32_t value = exe()->get_field(dev()->core->systick->CTRL, SysTick_CTRL_CLKSOURCE_Msk, SysTick_CTRL_CLKSOURCE_Pos);
    return value ? 8 : 1;
}

uint8_t get_hmco1pre(void) {
    uint32_t value = exe()->get_field(dev()->rcc->CFGR, RCC_CFGR_MCO1PRE, RCC_CFGR_MCO1PRE_Pos);
    return mco_table[value];
}

uint8_t get_hmco2pre(void) {
    uint32_t value = exe()->get_field(dev()->rcc->CFGR, RCC_CFGR_MCO2PRE, RCC_CFGR_MCO2PRE_Pos);
    return mco_table[value];
}

uint8_t get_rtcpre(void) {
    return exe()->get_field(dev()->rcc->CFGR, RCC_CFGR_RTCPRE, RCC_CFGR_RTCPRE_Pos);
}

uint8_t get_pllm(void) {
    return exe()->get_field(dev()->rcc->PLLCFGR, RCC_PLLCFGR_PLLM, RCC_PLLCFGR_PLLM_Pos);
}

uint16_t get_plln(void) {
    return exe()->get_field(dev()->rcc->PLLCFGR, RCC_PLLCFGR_PLLN, RCC_PLLCFGR_PLLN_Pos);
}

uint8_t get_pllp(void) {
    uint32_t value = exe()->get_field(dev()->rcc->PLLCFGR, RCC_PLLCFGR_PLLP, RCC_PLLCFGR_PLLP_Pos);
    switch(value){
        case 0b00: return 2;
        case 0b01: return 4;
        case 0b10: return 6;
        case 0b11: return 8;
        default: return 2;
    }
}

uint8_t get_pllq(void) {
    return exe()->get_field(dev()->rcc->PLLCFGR, RCC_PLLCFGR_PLLQ, RCC_PLLCFGR_PLLQ_Pos);
}

#ifdef STM32F446xx
uint8_t get_pllr(void) {
    return exe()->get_field(dev()->rcc->PLLCFGR, RCC_PLLCFGR_PLLR);
}
#endif

uint32_t get_pllsclk(void) {
    return exe()->get_field(dev()->rcc->PLLCFGR, RCC_PLLCFGR_PLLSRC, RCC_PLLCFGR_PLLSRC_Pos) ? HSE_VALUE : HSI_VALUE;
}
uint32_t get_pll_vco_in(void) {
    return (get_pllsclk() / get_pllm());
}

uint32_t get_pll_vco_out(void) {
    return (get_pll_vco_in() * get_plln());
}

uint32_t get_pllclk(void)
{
    return (get_pll_vco_out() / get_pllp());
}

uint32_t get_plli2s_vco_in(void) {
    return get_pll_vco_in();
}

uint32_t get_pllsai_vco_in(void) {
    return get_pll_vco_in();
}

uint32_t get_sysclk(void) {
    uint32_t sws = exe()->get_field(dev()->rcc->CFGR, RCC_CFGR_SWS,RCC_CFGR_SWS_Pos);
    switch(sws) {
        case 0: return HSI_VALUE;
        case 1: return HSE_VALUE;
        case 2: return get_pllclk();
        default: return HSI_VALUE;
    }
}

uint32_t get_hclk(void) {
    return get_sysclk() / get_hpre();
}

uint32_t get_systickclk(void) {
    return get_hclk() / get_systickpre();
}

uint32_t get_pclk1(void) {
    return get_hclk() / get_hppre1();
}

uint32_t get_pclk2(void) {
    return get_hclk() / get_hppre2();
}

uint32_t get_timclk1(void)
{
    uint32_t pclk = get_pclk1();
    return (get_hppre1() == 1) ? pclk : (pclk * 2U);
}

uint32_t get_timclk2(void)
{
    uint32_t pclk = get_pclk2();
    return (get_hppre2() == 1) ? pclk : (pclk * 2U);
}

/************************* Generic UTILS ***************************/
U_word writeHLbyte(uint16_t v)
{
    U_word w;
    w.par.h = v >> 8;
    w.par.l = v & 0xFF;
    return w;
}

/************************** I2C UTILS ******************************/
void I2C_SclClock(I2C_TypeDef *i2c, uint32_t scl_hz)
{
	// --- Software reset ---
	exe()->write_field(&i2c->CR1, I2C_CR1_SWRST, I2C_CR1_SWRST_Pos,1);
	exe()->write_field(&i2c->CR1, I2C_CR1_SWRST, I2C_CR1_SWRST_Pos,0);

	// --- Get peripheral clock ---
	uint32_t pclk1     = get_pclk1();        // Hz
	uint32_t freq_mhz  = pclk1 / 1000000;    // MHz

	// --- CR2.FREQ (must be MHz) ---
	exe()->write_block(&i2c->CR2, 6, 0, (freq_mhz & 0x3F));

	// --- Standard or Fast mode ---
	uint32_t ccr = 0;

	if (scl_hz <= 100000) {
		// ---------- STANDARD MODE ----------
		CLEAR_BIT(i2c->CCR, I2C_CCR_FS);     // FS = 0 → standard mode

		ccr = pclk1 / (2 * scl_hz);
		if (ccr < 4) ccr = 4;

		exe()->write_block(&i2c->CCR, 12, 0, ccr);

		// TRISE = freq_mhz + 1
		exe()->write_block(&i2c->TRISE, 6, 0, freq_mhz + 1);

	} else {
		// ---------- FAST MODE ----------
		exe()->write_field(&i2c->CCR, I2C_CCR_FS, I2C_CCR_FS_Pos,1); // FS = 1 → fast mode

		// Duty = 0 → Tlow/Thigh = 2
		ccr = pclk1 / (3 * scl_hz);
		if (ccr < 1) ccr = 1;

		exe()->write_block(&i2c->CCR, 12, 0, ccr);

		// TRISE = freq_mhz * 300ns + 1
		uint32_t trise = ((freq_mhz * 300) / 1000) + 1;
		exe()->write_block(&i2c->TRISE, 6, 0, trise);
	}

	// --- Enable peripheral ---
	exe()->write_field(&i2c->CR1, I2C_CR1_PE, I2C_CR1_PE_Pos,1);
}

/**************************** ADC UTILS ****************************/
/* --- Regular sequence auto (0 < count <= 16) --- */
void adc_set_regular_auto(ADC_TypeDef *adc, ADC_RegularTracker *tracker, uint8_t count, ...)
{
    if (count == 0 || count > 16) return;

    va_list args;
    va_start(args, count);

    /* store tracker */
    tracker->length = count;
    tracker->index  = 0;

    /* clear SQR registers */
    adc->SQR1 &= ~ADC_SQR1_L;         /* clear L first */
    adc->SQR1 &= ~0x000FFFFFU;
    adc->SQR2 = 0;
    adc->SQR3 = 0;

    /* set length L = count - 1 */
    exe()->write_field(&adc->SQR1, ADC_SQR1_L, ADC_SQR1_L_Pos,(uint32_t)((count - 1) & 0x0F));

    for (uint8_t i = 0; i < count; ++i) {
        uint8_t ch = (uint8_t)va_arg(args, int);
        tracker->sequence[i] = ch;

        /* internal channels handling */
        if (ch == 16 || ch == 17) {
            exe()->write_field(&ADC->CCR, ADC_CCR_TSVREFE, ADC_CCR_TSVREFE_Pos,1);     /* enable temp + vref */
        } else if (ch == 18) {
            exe()->write_field(&ADC->CCR, ADC_CCR_VBATE, ADC_CCR_VBATE_Pos,1);       /* enable VBAT */
        }

        /* sampling time: 3 bits per channel.
           use long (7) for internal channels, default medium (3) for externals */
        uint32_t smp = (ch >= 16) ? 7U : 3U;
        if (ch <= 9) {
            /* SMPR2: SMP0..SMP9, pos = 3 * ch */
            exe()->write_block(&adc->SMPR2, 3, (uint8_t)(3 * ch), smp);
        } else {
            /* SMPR1: SMP10..SMP17, pos = 3 * (ch - 10) */
            exe()->write_block(&adc->SMPR1, 3, (uint8_t)(3 * (ch - 10)), smp);
        }

        /* write channel into SQRx: 5 bits per slot */
        uint8_t pos_bit;
        if (i < 6) {
            pos_bit = 5 * i;                 /* SQR3, SQ1..SQ6 */
            exe()->write_block(&adc->SQR3, 5, pos_bit, ch);
        } else if (i < 12) {
            pos_bit = 5 * (i - 6);           /* SQR2, SQ7..SQ12 */
            exe()->write_block(&adc->SQR2, 5, pos_bit, ch);
        } else {
            pos_bit = 5 * (i - 12);          /* SQR1, SQ13..SQ16 */
            exe()->write_block(&adc->SQR1, 5, pos_bit, ch);
        }
    }

    va_end(args);
}

/* --- Injected sequence auto (0 < count <= 4) --- */
void adc_set_injected_auto(ADC_TypeDef *adc, ADC_InjectTracker *tracker, uint8_t count, ...)
{
    if (count == 0 || count > 4) return;

    va_list args;
    va_start(args, count);

    tracker->length = count;
    tracker->index  = 0;

    /* clear JSQR */
    adc->JSQR = 0;

    /* set JL = count - 1 in JSQR */
    exe()->write_block(&adc->JSQR, 2, 20, (uint32_t)((count - 1) & 0x3)); /* JL is 2 bits at pos 20 */

    for (uint8_t i = 0; i < count; ++i) {
        uint8_t ch = (uint8_t)va_arg(args, int);
        tracker->sequence[i] = ch;

        /* internal channels handling */
        if (ch == 16 || ch == 17) {
            //exe()->write_field(&ADC->CCR, ADC_CCR_TSVREFE, 1);
            exe()->write_field(&dev()->adc1_common->CCR, ADC_CCR_TSVREFE, ADC_CCR_TSVREFE_Pos,1);
        } else if (ch == 18) {
            //exe()->write_field(&ADC->CCR, ADC_CCR_VBATE, 1);
            exe()->write_field(&dev()->adc1_common->CCR, ADC_CCR_VBATE, ADC_CCR_VBATE_Pos,1);
        }

        /* sampling time */
        uint32_t smp = (ch >= 16) ? 7U : 3U;
        if (ch <= 9) {
            exe()->write_block(&adc->SMPR2, 3, (uint8_t)(3 * ch), smp);
        } else {
            exe()->write_block(&adc->SMPR1, 3, (uint8_t)(3 * (ch - 10)), smp);
        }

        /* JSQR: JSQ4..JSQ1 fields are 5 bits each; hardware expects reversed order:
           position: JSQ1 is highest of those bits; easiest is to place at bit pos = 5*(3 - i) */
        uint8_t pos_bit = 5 * (3 - i);
        exe()->write_block(&adc->JSQR, 5, pos_bit, ch);
    }

    va_end(args);
}

/************************** USART UTILS ***************************/
void Usart_WordLength(USART_TypeDef* usart, uint8_t wordlength) {
    if(wordlength == 9) usart->CR1 |= (1 << USART_CR1_M_Pos);
    else usart->CR1 &= ~(1 << USART_CR1_M_Pos);
}

/*
void Usart_StopBits(USART_TypeDef* usart, double stopbits) {
    usart->CR2 &= ~USART_CR2_STOP;
    if(fabs(stopbits-0.5)<1e-6) usart->CR2 |= USART_CR2_STOP_0;
    else if(fabs(stopbits-1.5)<1e-6) usart->CR2 |= USART_CR2_STOP;
    else if(fabs(stopbits-2.0)<1e-6) usart->CR2 |= USART_CR2_STOP_1;
}
*/

void Usart_StopBits(USART_TypeDef* usart, USART_StopBits_t stop)
{
    usart->CR2 &= ~USART_CR2_STOP;
    usart->CR2 |= ((uint32_t)stop << USART_CR2_STOP_Pos);
}

void Usart_SamplingMode(USART_TypeDef* usart, uint8_t samplingmode, uint32_t baudrate) {
    if(samplingmode==8) usart->CR1 |= USART_CR1_OVER8;
    else { usart->CR1 &= ~USART_CR1_OVER8; samplingmode=16; }

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

/************************** FPU ENABLE *****************************/
void fpu_enable(void) {
    dev()->core->scb->CPACR |= (0xF << 20);
}

/*** EOF ***/

