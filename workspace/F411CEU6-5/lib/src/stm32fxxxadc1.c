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

/*** Define and Macro ***/
#define ADC_EOC_TIMEOUT    700U
#define ADC_JEOC_TIMEOUT   700U
#define ADC_STAB_DELAY     15U

/* trackers */
static ADC_RegularTracker ADC1_RegularTracker = { .length = 0, .index = 0 };
static ADC_InjectTracker ADC1_InjectTracker = { .length = 0, .index = 0 };

/* channel result vectors (you already declared these) */
static volatile uint16_t ADC1_Regular_Channel[19] = {0};
static volatile uint16_t ADC1_Injected_Channel[19] = {0};

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

/* helpers for tracking & stepping regular sequence */
static inline uint8_t adc_get_current_channel(ADC_RegularTracker *tracker)
{
	(void)ADC1_RegularTracker;
    if (tracker->length == 0) return 0xFF;
    return tracker->sequence[tracker->index];
}
static inline void adc_next_channel(ADC_RegularTracker *tracker)
{
    if (tracker->length == 0) return;
    tracker->index++;
    if (tracker->index >= tracker->length) tracker->index = 0;
}

/* injected trackers */
static inline uint8_t adc_get_current_injected_channel(ADC_InjectTracker *tracker)
{
	(void)ADC1_InjectTracker;
    if (tracker->length == 0) return 0xFF;
    return tracker->sequence[tracker->index];
}
static inline void adc_next_injected_channel(ADC_InjectTracker *tracker)
{
    if (tracker->length == 0) return;
    tracker->index++;
    if (tracker->index >= tracker->length) tracker->index = 0;
}

/* --- update helpers to store results into your indexed vectors --- */
/* call these from ISR or after checking EOC/JEOC flags */
static inline void adc_update_regular_result(ADC_TypeDef *adc, ADC_RegularTracker *tracker)
{
    uint8_t ch = adc_get_current_channel(tracker);
    if (ch <= 18) {
        ADC1_Regular_Channel[ch] = (uint16_t)(adc->DR & 0xFFFFU);
    }
    adc_next_channel(tracker);
}

static inline void adc_update_injected_result(ADC_TypeDef *adc, ADC_InjectTracker *tracker, uint8_t jdr_index)
{
    uint16_t val = 0;
    switch (jdr_index) {
        case 1: val = (uint16_t)(adc->JDR1 & 0xFFFFU); break;
        case 2: val = (uint16_t)(adc->JDR2 & 0xFFFFU); break;
        case 3: val = (uint16_t)(adc->JDR3 & 0xFFFFU); break;
        default: val = (uint16_t)(adc->JDR4 & 0xFFFFU); break;
    }
    uint8_t ch = adc_get_current_injected_channel(tracker);
    if (ch <= 18) ADC1_Injected_Channel[ch] = val;
    adc_next_injected_channel(tracker);
}

/* simple start/wait helpers using CMSIS flags */
static inline void adc_start_conversion(ADC_TypeDef *adc) { set_reg(&adc->CR2, ADC_CR2_SWSTART); /* cleared by hardware */ }
static inline void adc_wait_eoc(ADC_TypeDef *adc) {
    for (volatile uint32_t timeout = ADC_EOC_TIMEOUT; !get_reg_Msk(adc->SR, ADC_SR_EOC) && timeout; timeout--);
    //clear_reg(&adc->SR, ADC_SR_EOC); /* cleared by hardware */
}
static inline void adc_start_injected(ADC_TypeDef *adc) { adc->CR2 |= ADC_CR2_JSWSTART; }
static inline void adc_wait_jeoc(ADC_TypeDef *adc) {
    for (volatile uint32_t timeout = ADC_JEOC_TIMEOUT; !get_reg_Msk(adc->SR, ADC_SR_JEOC) && timeout; timeout--);
    //clear_reg(&adc->SR, ADC_SR_JEOC); /* cleared by hardware */
}

void ADC1_Start_Conversion(void) {
	adc_start_conversion(ADC1);
}

void ADC1_Wait_End_Of_Conversion(void) {
	adc_wait_eoc(ADC1);
}

void ADC1_Mode_Scan(uint8_t enable) {
	if(enable) write_reg_block(&ADC1->CR1, ONE, ADC_CR1_SCAN_Pos, ONE);
	else write_reg_block(&ADC1->CR1, ONE, ADC_CR1_SCAN_Pos, ZERO);
}

void ADC1_Mode_Scan_Cont(uint8_t enable) {
	if(enable) {
		write_reg_block(&ADC1->CR1, ONE, ADC_CR1_SCAN_Pos, ONE);
		write_reg_block(&ADC1->CR2, ONE, ADC_CR2_CONT_Pos, ONE);
	}else{
		write_reg_block(&ADC1->CR1, ONE, ADC_CR1_SCAN_Pos, ZERO);
		write_reg_block(&ADC1->CR2, ONE, ADC_CR2_CONT_Pos, ZERO);
	}
}

void ADC1_Mode_Discen(uint8_t enable) {
	if(enable) {
		write_reg_block(&ADC1->CR1, ONE, ADC_CR1_DISCEN_Pos, ONE);
	}else{
		write_reg_block(&ADC1->CR1, ONE, ADC_CR1_DISCEN_Pos, ZERO);
	}
}

void ADC1_Mode_Discen_Scan(uint8_t enable) {
	if(enable) {
		write_reg_block(&ADC1->CR1, ONE, ADC_CR1_DISCEN_Pos, ONE);
		write_reg_block(&ADC1->CR1, ONE, ADC_CR1_SCAN_Pos, ONE);
	}else{
		write_reg_block(&ADC1->CR1, ONE, ADC_CR1_DISCEN_Pos, ZERO);
		write_reg_block(&ADC1->CR1, ONE, ADC_CR1_SCAN_Pos, ZERO);
	}
}

void ADC1_Mode_Discen_Discnum(uint8_t enable, uint8_t num) {
	if(enable) {
		write_reg_block(&ADC1->CR1, ONE, ADC_CR1_DISCEN_Pos, ONE);
		write_reg_block(&ADC1->CR1, 3, ADC_CR1_DISCNUM_Pos, num & 0x07);
	}else{
		write_reg_block(&ADC1->CR1, ONE, ADC_CR1_DISCEN_Pos, ZERO);
	}
}

void ADC1_Mode_Discen_Discnum_Scan(uint8_t enable, uint8_t num) {
	if(enable) {
		write_reg_block(&ADC1->CR1, ONE, ADC_CR1_DISCEN_Pos, ONE);
		write_reg_block(&ADC1->CR1, ONE, ADC_CR1_SCAN_Pos, ONE);
		write_reg_block(&ADC1->CR1, 3, ADC_CR1_DISCNUM_Pos, num & 0x07);
	}else{
		write_reg_block(&ADC1->CR1, ONE, ADC_CR1_DISCEN_Pos, ZERO);
		write_reg_block(&ADC1->CR1, ONE, ADC_CR1_SCAN_Pos, ZERO);
	}
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
    adc_set_regular_auto(ADC1, &ADC1_RegularTracker, 1, 16);
    ADC1_Start();
    ADC1_Mode_Discen_Scan(ONE);
}

uint16_t ADC1_Read_Temperature(void) {
	adc_start_conversion(ADC1);
	adc_wait_eoc(ADC1);
	uint8_t ch = adc_get_current_channel(&ADC1_RegularTracker);
	ADC1_Regular_Channel[ch] = (uint16_t)(ADC1->DR & 0xFFFFU);
	adc_next_channel(&ADC1_RegularTracker);
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
	.callback = &ADC1_callback_setup
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

