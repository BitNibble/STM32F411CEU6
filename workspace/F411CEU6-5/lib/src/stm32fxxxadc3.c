/******************************************************************************
	STM32 XXX ADC3
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     28022024
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxadc3.h"
#include "stm32fxxxnvic.h"

/*** Define and Macro ***/
#define ADC_STAB_DELAY 15
#define END_OF_CONVERSION_TIME_OUT 100

/*** File Procedure & Function Header ***/
/*** ADC3 ***/
#ifdef STM32F446xx

void ADC3_Clock(uint8_t state)
{
	if(state){ RCC->APB2ENR |= RCC_APB2ENR_ADC3EN; }else{ RCC->APB2ENR &= ~RCC_APB2ENR_ADC3EN; }
}
void ADC3_Nvic(uint8_t state)
{
	if(state){ set_bit_block(NVIC->ISER, 1, ADC_IRQn, 1); } else{ set_bit_block(NVIC->ICER, 1, ADC_IRQn, 1); }
}
void ADC3_start(void)
{
	set_reg_Msk_Pos(&ADC3->CR2, ADC_CR2_ADON, ADC_CR2_ADON_Pos, 1);
}
void ADC3_stop(void)
{
	set_reg_Msk_Pos(&ADC3->CR2, ADC_CR2_ADON, ADC_CR2_ADON_Pos, 0);
}

/*** ADC3 ***/
static ADC3_Callback ADC3_callback_setup = {0};

static STM32FXXX_ADC3_Handler stm32fxxx_adc3_setup = {
	.clock = ADC3_Clock,
	.nvic = ADC3_Nvic,
	.start = ADC3_start,
	.stop = ADC3_stop,
	.callback = &ADC3_callback_setup
};

STM32FXXX_ADC3_Handler* adc3(void){ return (STM32FXXX_ADC3_Handler*) &stm32fxxx_adc3_setup; }

#endif
/*** EOF ***/

