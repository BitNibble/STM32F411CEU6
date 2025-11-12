/******************************************************************************
	STM32 XXX ADC1
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     28022024
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxadc1.h"
#include "stm32fxxxnvic.h"
#include <stdarg.h>

/*** Define and Macro ***/
#define ADC_EOC_TIMEOUT    100U   // example
#define ADC_STAB_DELAY     15U      // already defined

/* trackers */
static struct { uint8_t sequence[16]; uint8_t length; uint8_t index; } ADC1_SeqTracker = { .length = 0, .index = 0 };
static struct { uint8_t sequence[4];  uint8_t length; uint8_t index; } ADC1_InjectTracker = { .length = 0, .index = 0 };

/* channel result vectors (you already declared these) */
static volatile uint16_t ADC1_Regular_Channel[19];
static volatile uint16_t ADC1_Injected_Channel[19];

/*** File Procedure & Function Header ***/
/*** ADC1 ***/
void ADC1_Clock(uint8_t state)
{
	if(state){ set_reg_Msk(&RCC->APB2ENR , RCC_APB2ENR_ADC1EN_Msk, 1); }
	else{ set_reg_Msk(&RCC->APB2ENR , RCC_APB2ENR_ADC1EN_Msk, 0); }

}
void ADC1_Nvic(uint8_t state) {
	if(state){ set_bit_block(NVIC->ISER, 1, ADC_IRQn, 1); } else{ set_bit_block(NVIC->ICER, 1, ADC_IRQn, 1); }
}

/* --- Regular sequence auto (0 < count <= 16) --- */
void adc_set_sequence_auto(ADC_TypeDef *adc, uint8_t count, ...)
{
    if (count == 0 || count > 16) return;

    va_list args;
    va_start(args, count);

    /* store tracker */
    ADC1_SeqTracker.length = count;
    ADC1_SeqTracker.index  = 0;

    /* clear SQR registers */
    adc->SQR1 &= ~ADC_SQR1_L;         /* clear L first */
    adc->SQR1 &= ~0x000FFFFFU;
    adc->SQR2 = 0;
    adc->SQR3 = 0;

    /* set length L = count - 1 */
    set_reg_Msk(&adc->SQR1, ADC_SQR1_L, (uint32_t)((count - 1) & 0x0F));

    for (uint8_t i = 0; i < count; ++i) {
        uint8_t ch = (uint8_t)va_arg(args, int);
        ADC1_SeqTracker.sequence[i] = ch;

        /* internal channels handling */
        if (ch == 16 || ch == 17) {
            set_reg_Msk(&ADC->CCR, ADC_CCR_TSVREFE, 1);     /* enable temp + vref */
        } else if (ch == 18) {
            set_reg_Msk(&ADC->CCR, ADC_CCR_VBATE, 1);       /* enable VBAT */
        }

        /* sampling time: 3 bits per channel.
           use long (7) for internal channels, default medium (3) for externals */
        uint32_t smp = (ch >= 16) ? 7U : 3U;
        if (ch <= 9) {
            /* SMPR2: SMP0..SMP9, pos = 3 * ch */
            set_reg_block(&adc->SMPR2, 3, (uint8_t)(3 * ch), smp);
        } else {
            /* SMPR1: SMP10..SMP17, pos = 3 * (ch - 10) */
            set_reg_block(&adc->SMPR1, 3, (uint8_t)(3 * (ch - 10)), smp);
        }

        /* write channel into SQRx: 5 bits per slot */
        uint8_t pos_bit;
        if (i < 6) {
            pos_bit = 5 * i;                 /* SQR3, SQ1..SQ6 */
            set_reg_block(&adc->SQR3, 5, pos_bit, ch);
        } else if (i < 12) {
            pos_bit = 5 * (i - 6);           /* SQR2, SQ7..SQ12 */
            set_reg_block(&adc->SQR2, 5, pos_bit, ch);
        } else {
            pos_bit = 5 * (i - 12);          /* SQR1, SQ13..SQ16 */
            set_reg_block(&adc->SQR1, 5, pos_bit, ch);
        }
    }

    va_end(args);
}

/* helpers for tracking & stepping regular sequence */
static inline uint8_t adc_get_current_channel(void)
{
    if (ADC1_SeqTracker.length == 0) return 0xFF;
    return ADC1_SeqTracker.sequence[ADC1_SeqTracker.index];
}
static inline void adc_next_channel(void)
{
    if (ADC1_SeqTracker.length == 0) return;
    ADC1_SeqTracker.index++;
    if (ADC1_SeqTracker.index >= ADC1_SeqTracker.length) ADC1_SeqTracker.index = 0;
}

/* --- Injected sequence auto (0 < count <= 4) --- */
void adc_set_injected_auto(ADC_TypeDef *adc, uint8_t count, ...)
{
    if (count == 0 || count > 4) return;

    va_list args;
    va_start(args, count);

    ADC1_InjectTracker.length = count;
    ADC1_InjectTracker.index  = 0;

    /* clear JSQR */
    adc->JSQR = 0;

    /* set JL = count - 1 in JSQR */
    set_reg_block(&adc->JSQR, 2, 20, (uint32_t)((count - 1) & 0x3)); /* JL is 2 bits at pos 20 */

    for (uint8_t i = 0; i < count; ++i) {
        uint8_t ch = (uint8_t)va_arg(args, int);
        ADC1_InjectTracker.sequence[i] = ch;

        /* internal channels handling */
        if (ch == 16 || ch == 17) {
            set_reg_Msk(&ADC->CCR, ADC_CCR_TSVREFE, 1);
        } else if (ch == 18) {
            set_reg_Msk(&ADC->CCR, ADC_CCR_VBATE, 1);
        }

        /* sampling time */
        uint32_t smp = (ch >= 16) ? 7U : 3U;
        if (ch <= 9) {
            set_reg_block(&adc->SMPR2, 3, (uint8_t)(3 * ch), smp);
        } else {
            set_reg_block(&adc->SMPR1, 3, (uint8_t)(3 * (ch - 10)), smp);
        }

        /* JSQR: JSQ4..JSQ1 fields are 5 bits each; hardware expects reversed order:
           position: JSQ1 is highest of those bits; easiest is to place at bit pos = 5*(3 - i) */
        uint8_t pos_bit = 5 * (3 - i);
        set_reg_block(&adc->JSQR, 5, pos_bit, ch);
    }

    va_end(args);
}

/* injected trackers */
static inline uint8_t adc_get_current_injected_channel(void)
{
    if (ADC1_InjectTracker.length == 0) return 0xFF;
    return ADC1_InjectTracker.sequence[ADC1_InjectTracker.index];
}
static inline void adc_next_injected_channel(void)
{
    if (ADC1_InjectTracker.length == 0) return;
    ADC1_InjectTracker.index++;
    if (ADC1_InjectTracker.index >= ADC1_InjectTracker.length) ADC1_InjectTracker.index = 0;
}

/* --- update helpers to store results into your indexed vectors --- */
/* call these from ISR or after checking EOC/JEOC flags */
static inline void adc_update_regular_result(ADC_TypeDef *adc)
{
    uint8_t ch = adc_get_current_channel();
    if (ch <= 18) {
        ADC1_Regular_Channel[ch] = (uint16_t)(adc->DR & 0xFFFFU);
    }
    adc_next_channel();
}

static inline void adc_update_injected_result(ADC_TypeDef *adc, uint8_t jdr_index)
{
    uint16_t val = 0;
    switch (jdr_index) {
        case 1: val = (uint16_t)(adc->JDR1 & 0xFFFFU); break;
        case 2: val = (uint16_t)(adc->JDR2 & 0xFFFFU); break;
        case 3: val = (uint16_t)(adc->JDR3 & 0xFFFFU); break;
        default: val = (uint16_t)(adc->JDR4 & 0xFFFFU); break;
    }
    uint8_t ch = adc_get_current_injected_channel();
    if (ch <= 18) ADC1_Injected_Channel[ch] = val;
    adc_next_injected_channel();
}

/* simple start/wait helpers using CMSIS flags */
static inline void adc_start_conversion(ADC_TypeDef *adc) { adc->CR2 |= ADC_CR2_SWSTART; }
static inline void adc_wait_eoc(ADC_TypeDef *adc) { while (!(adc->SR & ADC_SR_EOC)); adc->SR &= ~ADC_SR_EOC; }
static inline void adc_start_injected(ADC_TypeDef *adc) { adc->CR2 |= ADC_CR2_JSWSTART; }
static inline void adc_wait_jeoc(ADC_TypeDef *adc) { while (!(adc->SR & ADC_SR_JEOC)); adc->SR &= ~ADC_SR_JEOC; }

void ADC1_Start_Conversion(void) {
    set_reg_Msk(&ADC1->CR2, ADC_CR2_SWSTART, 1);
}

void ADC1_Wait_End_Of_Conversion(void) {
    for (volatile uint32_t timeout = ADC_EOC_TIMEOUT;
         !get_reg_Msk(ADC1->SR, ADC_SR_EOC) && timeout;
         timeout--);
    clear_reg(&ADC1->SR, ADC_SR_EOC);
}

void ADC1_Start(void) {
    set_reg_Msk(&ADC1->CR2, ADC_CR2_ADON, 1);
    for (volatile uint8_t i = ADC_STAB_DELAY; i; i--);  // stabilization wait
}

void ADC1_Stop(void) {
    clear_reg(&ADC1->CR2, ADC_CR2_ADON);
}

void ADC1_Temperature_Setup(void) {
    ADC1_Clock(1);
    ADC1->CR1 = 0;
    adc_set_sequence_auto(ADC1, 1, 16);
    ADC1_Start();
}
uint16_t ADC1_Read_Temperature(void) {
	ADC1_Start_Conversion();
	ADC1_Wait_End_Of_Conversion();
    ADC1_Regular_Channel[16] = ADC1->DR;
    return ADC1_Regular_Channel[16];
}

/*** ADC1 ***/
static ADC1_Callback ADC1_callback_setup = {0};

static STM32FXXX_ADC1_Handler stm32fxxx_adc1_setup = {
	.clock = ADC1_Clock,
	.nvic = ADC1_Nvic,
	.start_conversion = ADC1_Start_Conversion,
	.wait_end_of_conversion = ADC1_Wait_End_Of_Conversion,
	.start = ADC1_Start,
	.stop = ADC1_Stop,
	.temperature_setup = ADC1_Temperature_Setup,
	.read_temperature = ADC1_Read_Temperature,
	.callback = &ADC1_callback_setup,
	.dev = dev
};

STM32FXXX_ADC1_Handler* adc1(void){ return (STM32FXXX_ADC1_Handler*) &stm32fxxx_adc1_setup; }

/*** INTERRUPT ***/
void ADC_IRQHandler(void)
{
	ADC1_Callback* cb = adc1()->callback;
    uint32_t status = dev()->adc1->SR;   // Read status register
    uint32_t value  = 0;

    /*** 1. End of Conversion (EOC) ***/
    if (status & (1 << 1))  // EOC flag
    {
        value = dev()->adc1->DR;  // Read result clears EOC
        if (cb->on_conversion_complete)
            cb->on_conversion_complete((uint16_t)value);
    }

    /*** 2. End of Injected Conversion (JEOC) ***/
    if (status & (1 << 2))  // JEOC flag
    {
        // Read injected data register if used
        // For now just trigger callback for injected channel done
        if (cb->on_conversion_complete)
            cb->on_conversion_complete((uint16_t)dev()->adc1->DR);
        dev()->adc1->SR &= ~(1 << 2);  // Clear JEOC manually
    }

    /*** 3. Analog Watchdog (AWD) ***/
    if (status & (1 << 0))  // AWD flag
    {
        if (cb->on_error)
            cb->on_error(0xA0);  // Custom code for AWD
        dev()->adc1->SR &= ~(1 << 0);  // Clear AWD
    }

    /*** 4. Overrun Error (OVR) ***/
    if (status & (1 << 5))  // OVR flag
    {
        if (cb->on_error)
            cb->on_error(0xE0);  // Custom code for overrun
        dev()->adc1->SR &= ~(1 << 5);  // Clear OVR
    }

    /*** 5. Start/Stop notification (optional custom hooks) ***/
    if (cb->on_start)
    {
        // Could trigger when ADC_CR2.ADON set, handled elsewhere if desired
        // adc1()->callback.on_start();
    }

    if (cb->on_stop)
    {
        // Could trigger when ADC_CR2.ADON cleared, handled elsewhere if desired
        // adc1()->callback.on_stop();
    }
}

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

