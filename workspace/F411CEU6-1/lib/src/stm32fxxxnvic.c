/******************************************************************************
	STM32FXXX NVIC
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     19062023
Comment:
	Interrupt Vector
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxnvic.h"

/*** File Variable ***/
static STM32FXXX_NVIC stm32fxxx_nvic = {0};

/*** NVIC Procedure & Function Definition ***/
void NVIC_set_enable( uint8_t IRQn )
{
	set_bit_block(NVIC->ISER, 1, IRQn, 1);
}
void NVIC_clear_enable( uint8_t IRQn )
{
	set_bit_block(NVIC->ICER, 1, IRQn, 1);
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
	volatile uint8_t* reg = (uint8_t*) NVIC->ISPR;
	*(reg + IRQn ) = priority;
}
void NVIC_trigger(uint32_t IRQn)
{
	write_reg_block(&NVIC->STIR, 9, 0, IRQn);
}
void NVIC_SetClear(uint8_t irq_num, uint8_t state) {
    if (state) {
        set_bit_block(NVIC->ISER, 1, irq_num, ON);
    } else {
        set_bit_block(NVIC->ICER, 1, irq_num, OFF);
    }
}
/*** INIC Procedure & Function Definition ***/
void nvic_enable(void)
{
	stm32fxxx_nvic.instance = NVIC;
	/*** NVIC Bit Mapping Link ***/
	stm32fxxx_nvic.set_enable = NVIC_set_enable;
	stm32fxxx_nvic.clear_enable = NVIC_clear_enable;
	stm32fxxx_nvic.set_pending = NVIC_set_pending;
	stm32fxxx_nvic.clear_pending = NVIC_clear_pending;
	stm32fxxx_nvic.active = NVIC_active;
	stm32fxxx_nvic.priority = NVIC_priority;
	stm32fxxx_nvic.trigger = NVIC_trigger;

	//return &stm32fxxx_nvic;
}

STM32FXXX_NVIC* nvic(void){ return (STM32FXXX_NVIC*) &stm32fxxx_nvic; }

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

