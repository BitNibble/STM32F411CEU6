/******************************************************************************
	STM32FXXX NVIC
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     19062023
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxnvic.h"

/*** NVIC Procedure & Function Definition ***/
void NVIC_set_enable( uint8_t IRQn )
{
	set_bit_block(NVIC->ISER, 1, IRQn, 1);
}
void NVIC_clear_enable( uint8_t IRQn )
{
	set_bit_block(NVIC->ICER, 1, IRQn, 1);
}
void NVIC_set_clear(uint8_t IRQn, uint8_t state) {
    volatile uint32_t* reg = state ? NVIC->ISER : NVIC->ICER;
    *(reg + (IRQn / 32)) = (1UL << (IRQn % 32));
}
void NVIC_set_pending( uint8_t IRQn )
{
	set_bit_block(NVIC->ISPR, 1, IRQn, 1);
}
void NVIC_clear_pending( uint8_t IRQn )
{
	set_bit_block(NVIC->ICPR, 1, IRQn, 1);
}
uint8_t NVIC_active( uint8_t IRQn ) // Query
{
	volatile uint32_t* reg = NVIC->IABR;
	uint8_t state; uint32_t n = 0;
	if(IRQn > 31){ n = IRQn/32; IRQn = IRQn - (n * 32); }
	if( *(reg + n ) & (1 << IRQn) ) state = 1; else state = 0 ;
	//return nvic_getset_bit_block(NVIC->ICPR, 1, IRQn);
	return state;
}
void NVIC_priority(uint32_t IRQn, uint32_t priority)
{
	volatile uint8_t* reg = (volatile uint8_t*) NVIC->IP;
	*(reg + IRQn ) = (uint8_t)priority;
}
void NVIC_trigger(uint32_t IRQn)
{
	write_reg_block(&NVIC->STIR, 9, 0, IRQn);
}
/*** INIC Procedure & Function Definition ***/
static STM32FXXX_NVIC_Handler stm32fxxx_nvic_setup = {
	/*** NVIC Bit Mapping Link ***/
	.set_enable = NVIC_set_enable,
	.clear_enable = NVIC_clear_enable,
	.set_clear = NVIC_set_clear,
	.set_pending = NVIC_set_pending,
	.clear_pending = NVIC_clear_pending,
	.active = NVIC_active,
	.priority = NVIC_priority,
	.trigger = NVIC_trigger,
	.dev = dev
};

STM32FXXX_NVIC_Handler* nvic(void){ return (STM32FXXX_NVIC_Handler*) &stm32fxxx_nvic_setup; }

/*** EOF ***/

