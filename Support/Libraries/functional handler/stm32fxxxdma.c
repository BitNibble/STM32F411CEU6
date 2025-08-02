/******************************************************************************
	STM32 XXX DMA
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 27062023
Comment:

*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxdma.h"

#define ON 1
#define OFF 0
/*** File Variables ***/
// DMA1
static STM32FXXXDMA_sr stm32fxxx_dma1_sr;
static STM32FXXXDMA_STREAM_cr stm32fxxx_dma1_stream0_cr;
static STM32FXXXDMA_STREAM_cr stm32fxxx_dma1_stream1_cr;
static STM32FXXXDMA_STREAM_cr stm32fxxx_dma1_stream2_cr;
static STM32FXXXDMA_STREAM_cr stm32fxxx_dma1_stream3_cr;
static STM32FXXXDMA_STREAM_cr stm32fxxx_dma1_stream4_cr;
static STM32FXXXDMA_STREAM_cr stm32fxxx_dma1_stream5_cr;
static STM32FXXXDMA_STREAM_cr stm32fxxx_dma1_stream6_cr;
static STM32FXXXDMA_STREAM_cr stm32fxxx_dma1_stream7_cr;
static STM32FXXXDMA_STREAM_fcr stm32fxxx_dma1_stream0_fcr;
static STM32FXXXDMA_STREAM_fcr stm32fxxx_dma1_stream1_fcr;
static STM32FXXXDMA_STREAM_fcr stm32fxxx_dma1_stream2_fcr;
static STM32FXXXDMA_STREAM_fcr stm32fxxx_dma1_stream3_fcr;
static STM32FXXXDMA_STREAM_fcr stm32fxxx_dma1_stream4_fcr;
static STM32FXXXDMA_STREAM_fcr stm32fxxx_dma1_stream5_fcr;
static STM32FXXXDMA_STREAM_fcr stm32fxxx_dma1_stream6_fcr;
static STM32FXXXDMA_STREAM_fcr stm32fxxx_dma1_stream7_fcr;
static STM32FXXXDMA_func stm32fxxx_dma1_func;
static STM32FXXX_DMA1 stm32fxxx_dma1  = {0};
// DMA2
static STM32FXXXDMA_sr stm32fxxx_dma2_sr;
static STM32FXXXDMA_STREAM_cr stm32fxxx_dma2_stream0_cr;
static STM32FXXXDMA_STREAM_cr stm32fxxx_dma2_stream1_cr;
static STM32FXXXDMA_STREAM_cr stm32fxxx_dma2_stream2_cr;
static STM32FXXXDMA_STREAM_cr stm32fxxx_dma2_stream3_cr;
static STM32FXXXDMA_STREAM_cr stm32fxxx_dma2_stream4_cr;
static STM32FXXXDMA_STREAM_cr stm32fxxx_dma2_stream5_cr;
static STM32FXXXDMA_STREAM_cr stm32fxxx_dma2_stream6_cr;
static STM32FXXXDMA_STREAM_cr stm32fxxx_dma2_stream7_cr;
static STM32FXXXDMA_STREAM_fcr stm32fxxx_dma2_stream0_fcr;
static STM32FXXXDMA_STREAM_fcr stm32fxxx_dma2_stream1_fcr;
static STM32FXXXDMA_STREAM_fcr stm32fxxx_dma2_stream2_fcr;
static STM32FXXXDMA_STREAM_fcr stm32fxxx_dma2_stream3_fcr;
static STM32FXXXDMA_STREAM_fcr stm32fxxx_dma2_stream4_fcr;
static STM32FXXXDMA_STREAM_fcr stm32fxxx_dma2_stream5_fcr;
static STM32FXXXDMA_STREAM_fcr stm32fxxx_dma2_stream6_fcr;
static STM32FXXXDMA_STREAM_fcr stm32fxxx_dma2_stream7_fcr;
static STM32FXXXDMA_func stm32fxxx_dma2_func;
static STM32FXXX_DMA2 stm32fxxx_dma2 = {0};

static uint32_t time_out;

/*** File Procedure & Function Header ***/
/*** REG INIC ***/
// DMA1
STM32FXXXDMA_sr* stm32fxxx_dma1_sr_inic(void);
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma1_stream0_cr_inic(void);
void stm32fxxx_dma1_stream0_ndt(uint16_t value);
void stm32fxxx_dma1_stream0_par(volatile long unsigned int periferal_addr);
void stm32fxxx_dma1_stream0_m0a(volatile long unsigned int mem0_addr);
void stm32fxxx_dma1_stream0_m1a(volatile long unsigned int mem1_addr);
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma1_stream0_fcr_inic(void);
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma1_stream1_cr_inic(void);
void stm32fxxx_dma1_stream1_ndt(uint16_t value);
void stm32fxxx_dma1_stream1_par(volatile long unsigned int periferal_addr);
void stm32fxxx_dma1_stream1_m0a(volatile long unsigned int mem0_addr);
void stm32fxxx_dma1_stream1_m1a(volatile long unsigned int mem1_addr);
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma1_stream1_fcr_inic(void);
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma1_stream2_cr_inic(void);
void stm32fxxx_dma1_stream2_ndt(uint16_t value);
void stm32fxxx_dma1_stream2_par(volatile long unsigned int periferal_addr);
void stm32fxxx_dma1_stream2_m0a(volatile long unsigned int mem0_addr);
void stm32fxxx_dma1_stream2_m1a(volatile long unsigned int mem1_addr);
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma1_stream2_fcr_inic(void);
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma1_stream3_cr_inic(void);
void stm32fxxx_dma1_stream3_ndt(uint16_t value);
void stm32fxxx_dma1_stream3_par(volatile long unsigned int periferal_addr);
void stm32fxxx_dma1_stream3_m0a(volatile long unsigned int mem0_addr);
void stm32fxxx_dma1_stream3_m1a(volatile long unsigned int mem1_addr);
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma1_stream3_fcr_inic(void);
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma1_stream4_cr_inic(void);
void stm32fxxx_dma1_stream4_ndt(uint16_t value);
void stm32fxxx_dma1_stream4_par(volatile long unsigned int periferal_addr);
void stm32fxxx_dma1_stream4_m0a(volatile long unsigned int mem0_addr);
void stm32fxxx_dma1_stream4_m1a(volatile long unsigned int mem1_addr);
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma1_stream4_fcr_inic(void);
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma1_stream5_cr_inic(void);
void stm32fxxx_dma1_stream5_ndt(uint16_t value);
void stm32fxxx_dma1_stream5_par(volatile long unsigned int periferal_addr);
void stm32fxxx_dma1_stream5_m0a(volatile long unsigned int mem0_addr);
void stm32fxxx_dma1_stream5_m1a(volatile long unsigned int mem1_addr);
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma1_stream5_fcr_inic(void);
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma1_stream6_cr_inic(void);
void stm32fxxx_dma1_stream6_ndt(uint16_t value);
void stm32fxxx_dma1_stream6_par(volatile long unsigned int periferal_addr);
void stm32fxxx_dma1_stream6_m0a(volatile long unsigned int mem0_addr);
void stm32fxxx_dma1_stream6_m1a(volatile long unsigned int mem1_addr);
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma1_stream6_fcr_inic(void);
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma1_stream7_cr_inic(void);
void stm32fxxx_dma1_stream7_ndt(uint16_t value);
void stm32fxxx_dma1_stream7_par(volatile long unsigned int periferal_addr);
void stm32fxxx_dma1_stream7_m0a(volatile long unsigned int mem0_addr);
void stm32fxxx_dma1_stream7_m1a(volatile long unsigned int mem1_addr);
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma1_stream7_fcr_inic(void);
STM32FXXXDMA_func* stm32fxxx_dma1_func_inic(void);
// DMA2
STM32FXXXDMA_sr* stm32fxxx_dma2_sr_inic(void);
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma2_stream0_cr_inic(void);
void stm32fxxx_dma2_stream0_ndt(uint16_t value);
void stm32fxxx_dma2_stream0_par(volatile long unsigned int periferal_addr);
void stm32fxxx_dma2_stream0_m0a(volatile long unsigned int mem0_addr);
void stm32fxxx_dma2_stream0_m1a(volatile long unsigned int mem1_addr);
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma2_stream0_fcr_inic(void);
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma2_stream1_cr_inic(void);
void stm32fxxx_dma2_stream1_ndt(uint16_t value);
void stm32fxxx_dma2_stream1_par(volatile long unsigned int periferal_addr);
void stm32fxxx_dma2_stream1_m0a(volatile long unsigned int mem0_addr);
void stm32fxxx_dma2_stream1_m1a(volatile long unsigned int mem1_addr);
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma2_stream1_fcr_inic(void);
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma2_stream2_cr_inic(void);
void stm32fxxx_dma2_stream2_ndt(uint16_t value);
void stm32fxxx_dma2_stream2_par(volatile long unsigned int periferal_addr);
void stm32fxxx_dma2_stream2_m0a(volatile long unsigned int mem0_addr);
void stm32fxxx_dma2_stream2_m1a(volatile long unsigned int mem1_addr);
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma2_stream2_fcr_inic(void);
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma2_stream3_cr_inic(void);
void stm32fxxx_dma2_stream3_ndt(uint16_t value);
void stm32fxxx_dma2_stream3_par(volatile long unsigned int periferal_addr);
void stm32fxxx_dma2_stream3_m0a(volatile long unsigned int mem0_addr);
void stm32fxxx_dma2_stream3_m1a(volatile long unsigned int mem1_addr);
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma2_stream3_fcr_inic(void);
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma2_stream4_cr_inic(void);
void stm32fxxx_dma2_stream4_ndt(uint16_t value);
void stm32fxxx_dma2_stream4_par(volatile long unsigned int periferal_addr);
void stm32fxxx_dma2_stream4_m0a(volatile long unsigned int mem0_addr);
void stm32fxxx_dma2_stream4_m1a(volatile long unsigned int mem1_addr);
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma2_stream4_fcr_inic(void);
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma2_stream5_cr_inic(void);
void stm32fxxx_dma2_stream5_ndt(uint16_t value);
void stm32fxxx_dma2_stream5_par(volatile long unsigned int periferal_addr);
void stm32fxxx_dma2_stream5_m0a(volatile long unsigned int mem0_addr);
void stm32fxxx_dma2_stream5_m1a(volatile long unsigned int mem1_addr);
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma2_stream5_fcr_inic(void);
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma2_stream6_cr_inic(void);
void stm32fxxx_dma2_stream6_ndt(uint16_t value);
void stm32fxxx_dma2_stream6_par(volatile long unsigned int periferal_addr);
void stm32fxxx_dma2_stream6_m0a(volatile long unsigned int mem0_addr);
void stm32fxxx_dma2_stream6_m1a(volatile long unsigned int mem1_addr);
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma2_stream6_fcr_inic(void);
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma2_stream7_cr_inic(void);
void stm32fxxx_dma2_stream7_ndt(uint16_t value);
void stm32fxxx_dma2_stream7_par(volatile long unsigned int periferal_addr);
void stm32fxxx_dma2_stream7_m0a(volatile long unsigned int mem0_addr);
void stm32fxxx_dma2_stream7_m1a(volatile long unsigned int mem1_addr);
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma2_stream7_fcr_inic(void);
STM32FXXXDMA_func* stm32fxxx_dma2_func_inic(void);
/*******************************************/
/*** DMA Procedure & Function Definition ***/
/*******************************************/
void STM32FXXXDma1Clock(uint8_t state)
{
	if(state){ RCC->AHB1ENR |= (1 << 21); } else{ RCC->AHB1ENR &= ~(1 << 21); }
}
void STM32FXXXDma2Clock(uint8_t state)
{
	if(state){ RCC->AHB1ENR |= (1 << 22); } else{ RCC->AHB1ENR &= ~(1 << 22); }
}
/********************************************/
/************* DMA1 Bit Mapping *************/
/********************************************/
// SR
uint8_t STM32FXXXDMA1_sr_tcif(uint8_t stream_n)
{
	uint8_t value = 0;
	switch(stream_n){
		case 0:
			value = get_reg_block(DMA1->LISR, 1, 5);
		break;
		case 1:
			value = get_reg_block(DMA1->LISR, 1, 11);
		break;
		case 2:
			value = get_reg_block(DMA1->LISR, 1, 21);
		break;
		case 3:
			value = get_reg_block(DMA1->LISR, 1, 27);
		break;
		case 4:
			value = get_reg_block(DMA1->HISR, 1, 5);
		break;
		case 5:
			value = get_reg_block(DMA1->HISR, 1, 11);
		break;
		case 6:
			value = get_reg_block(DMA1->HISR, 1, 21);
		break;
		case 7:
			value = get_reg_block(DMA1->HISR, 1, 27);
		break;
	default: break;
	}
	return value;
}
void STM32FXXXDMA1_sr_clear_tcif(uint8_t stream_n)
{
	switch(stream_n){
		case 0:
			set_reg_block(&DMA1->LIFCR, 1, 5, 1);
		break;
		case 1:
			set_reg_block(&DMA1->LIFCR, 1, 11, 1);
		break;
		case 2:
			set_reg_block(&DMA1->LIFCR, 1, 21, 1);
		break;
		case 3:
			set_reg_block(&DMA1->LIFCR, 1, 27, 1);
		break;
		case 4:
			set_reg_block(&DMA1->HIFCR, 1, 5, 1);
		break;
		case 5:
			set_reg_block(&DMA1->HIFCR, 1, 11, 1);
		break;
		case 6:
			set_reg_block(&DMA1->HIFCR, 1, 21, 1);
		break;
		case 7:
			set_reg_block(&DMA1->HIFCR, 1, 27, 1);
		break;
		default: break;
	}
}
uint8_t STM32FXXXDMA1_sr_htif(uint8_t stream_n)
{
	uint8_t value = 0;
	switch(stream_n){
		case 0:
			value = get_reg_block(DMA1->LISR, 1, 4);
		break;
		case 1:
			value = get_reg_block(DMA1->LISR, 1, 10);
		break;
		case 2:
			value = get_reg_block(DMA1->LISR, 1, 20);
		break;
		case 3:
			value = get_reg_block(DMA1->LISR, 1, 26);
		break;
		case 4:
			value = get_reg_block(DMA1->HISR, 1, 4);
		break;
		case 5:
			value = get_reg_block(DMA1->HISR, 1, 10);
		break;
		case 6:
			value = get_reg_block(DMA1->HISR, 1, 20);
		break;
		case 7:
			value = get_reg_block(DMA1->HISR, 1, 26);
		break;
	default: break;
	}
	return value;
}
void STM32FXXXDMA1_sr_clear_htif(uint8_t stream_n)
{
	switch(stream_n){
		case 0:
			set_reg_block(&DMA1->LIFCR, 1, 4, 1);
		break;
		case 1:
			set_reg_block(&DMA1->LIFCR, 1, 10, 1);
		break;
		case 2:
			set_reg_block(&DMA1->LIFCR, 1, 20, 1);
		break;
		case 3:
			set_reg_block(&DMA1->LIFCR, 1, 26, 1);
		break;
		case 4:
			set_reg_block(&DMA1->HIFCR, 1, 4, 1);
		break;
		case 5:
			set_reg_block(&DMA1->HIFCR, 1, 10, 1);
		break;
		case 6:
			set_reg_block(&DMA1->HIFCR, 1, 20, 1);
		break;
		case 7:
			set_reg_block(&DMA1->HIFCR, 1, 26, 1);
		break;
		default: break;
	}
}
uint8_t STM32FXXXDMA1_sr_teif(uint8_t stream_n)
{
	uint8_t value = 0;
	switch(stream_n){
		case 0:
			value = get_reg_block(DMA1->LISR, 1, 3);
		break;
		case 1:
			value = get_reg_block(DMA1->LISR, 1, 9);
		break;
		case 2:
			value = get_reg_block(DMA1->LISR, 1, 19);
		break;
		case 3:
			value = get_reg_block(DMA1->LISR, 1, 25);
		break;
		case 4:
			value = get_reg_block(DMA1->HISR, 1, 3);
		break;
		case 5:
			value = get_reg_block(DMA1->HISR, 1, 9);
		break;
		case 6:
			value = get_reg_block(DMA1->HISR, 1, 19);
		break;
		case 7:
			value = get_reg_block(DMA1->HISR, 1, 25);
		break;
	default: break;
	}
	return value;
}
void STM32FXXXDMA1_sr_clear_teif(uint8_t stream_n)
{
	switch(stream_n){
		case 0:
			set_reg_block(&DMA1->LIFCR, 1, 3, 1);
		break;
		case 1:
			set_reg_block(&DMA1->LIFCR, 1, 9, 1);
		break;
		case 2:
			set_reg_block(&DMA1->LIFCR, 1, 19, 1);
		break;
		case 3:
			set_reg_block(&DMA1->LIFCR, 1, 25, 1);
		break;
		case 4:
			set_reg_block(&DMA1->HIFCR, 1, 3, 1);
		break;
		case 5:
			set_reg_block(&DMA1->HIFCR, 1, 9, 1);
		break;
		case 6:
			set_reg_block(&DMA1->HIFCR, 1, 19, 1);
		break;
		case 7:
			set_reg_block(&DMA1->HIFCR, 1, 25, 1);
		break;
		default: break;
	}
}
uint8_t STM32FXXXDMA1_sr_dmeif(uint8_t stream_n)
{
	uint8_t value = 0;
	switch(stream_n){
		case 0:
			value = get_reg_block(DMA1->LISR, 1, 2);
		break;
		case 1:
			value = get_reg_block(DMA1->LISR, 1, 8);
		break;
		case 2:
			value = get_reg_block(DMA1->LISR, 1, 18);
		break;
		case 3:
			value = get_reg_block(DMA1->LISR, 1, 24);
		break;
		case 4:
			value = get_reg_block(DMA1->HISR, 1, 2);
		break;
		case 5:
			value = get_reg_block(DMA1->HISR, 1, 8);
		break;
		case 6:
			value = get_reg_block(DMA1->HISR, 1, 18);
		break;
		case 7:
			value = get_reg_block(DMA1->HISR, 1, 24);
		break;
	default: break;
	}
	return value;
}
void STM32FXXXDMA1_sr_clear_dmeif(uint8_t stream_n)
{
	switch(stream_n){
		case 0:
			set_reg_block(&DMA1->LIFCR, 1, 2, 1);
		break;
		case 1:
			set_reg_block(&DMA1->LIFCR, 1, 8, 1);
		break;
		case 2:
			set_reg_block(&DMA1->LIFCR, 1, 18, 1);
		break;
		case 3:
			set_reg_block(&DMA1->LIFCR, 1, 24, 1);
		break;
		case 4:
			set_reg_block(&DMA1->HIFCR, 1, 2, 1);
		break;
		case 5:
			set_reg_block(&DMA1->HIFCR, 1, 8, 1);
		break;
		case 6:
			set_reg_block(&DMA1->HIFCR, 1, 18, 1);
		break;
		case 7:
			set_reg_block(&DMA1->HIFCR, 1, 24, 1);
		break;
		default: break;
	}
}
uint8_t STM32FXXXDMA1_sr_feif(uint8_t stream_n)
{
	uint8_t value = 0;
	switch(stream_n){
		case 0:
			value = get_reg_block(DMA1->LISR, 1, 0);
		break;
		case 1:
			value = get_reg_block(DMA1->LISR, 1, 6);
		break;
		case 2:
			value = get_reg_block(DMA1->LISR, 1, 16);
		break;
		case 3:
			value = get_reg_block(DMA1->LISR, 1, 22);
		break;
		case 4:
			value = get_reg_block(DMA1->HISR, 1, 0);
		break;
		case 5:
			value = get_reg_block(DMA1->HISR, 1, 6);
		break;
		case 6:
			value = get_reg_block(DMA1->HISR, 1, 16);
		break;
		case 7:
			value = get_reg_block(DMA1->HISR, 1, 22);
		break;
	default: break;
	}
	return value;
}
void STM32FXXXDMA1_sr_clear_feif(uint8_t stream_n)
{
	switch(stream_n){
		case 0:
			set_reg_block(&DMA1->LIFCR, 1, 0, 1);
		break;
		case 1:
			set_reg_block(&DMA1->LIFCR, 1, 6, 1);
		break;
		case 2:
			set_reg_block(&DMA1->LIFCR, 1, 16, 1);
		break;
		case 3:
			set_reg_block(&DMA1->LIFCR, 1, 22, 1);
		break;
		case 4:
			set_reg_block(&DMA1->HIFCR, 1, 0, 1);
		break;
		case 5:
			set_reg_block(&DMA1->HIFCR, 1, 6, 1);
		break;
		case 6:
			set_reg_block(&DMA1->HIFCR, 1, 16, 1);
		break;
		case 7:
			set_reg_block(&DMA1->HIFCR, 1, 22, 1);
		break;
		default: break;
	}
}
/*** Inic SR ***/
STM32FXXXDMA_sr* stm32fxxx_dma1_sr_inic(void)
{

	// SR
	stm32fxxx_dma1_sr.tcif = STM32FXXXDMA1_sr_tcif;
	stm32fxxx_dma1_sr.clear_tcif = STM32FXXXDMA1_sr_clear_tcif;
	stm32fxxx_dma1_sr.htif = STM32FXXXDMA1_sr_htif;
	stm32fxxx_dma1_sr.clear_htif = STM32FXXXDMA1_sr_clear_htif;
	stm32fxxx_dma1_sr.teif = STM32FXXXDMA1_sr_teif;
	stm32fxxx_dma1_sr.clear_teif = STM32FXXXDMA1_sr_clear_teif;
	stm32fxxx_dma1_sr.dmeif = STM32FXXXDMA1_sr_dmeif;
	stm32fxxx_dma1_sr.clear_dmeif = STM32FXXXDMA1_sr_clear_dmeif;
	stm32fxxx_dma1_sr.feif = STM32FXXXDMA1_sr_feif;
	stm32fxxx_dma1_sr.clear_feif = STM32FXXXDMA1_sr_clear_feif;
	return &stm32fxxx_dma1_sr;
}
// DMA1 STREAM0 CR
void STM32FXXXDMA1_stream0_cr_chsel(uint8_t value)
{
	set_reg_block(&DMA1_Stream0->CR, 3, 25, value);
}
void STM32FXXXDMA1_stream0_cr_mburst(uint8_t value)
{
	set_reg_block(&DMA1_Stream0->CR, 2, 23, value);
}
void STM32FXXXDMA1_stream0_cr_pburst(uint8_t value)
{
	set_reg_block(&DMA1_Stream0->CR, 2, 21, value);
}
void STM32FXXXDMA1_stream0_cr_ct(uint8_t state)
{
	set_reg_block(&DMA1_Stream0->CR, 1, 19, state);
}
void STM32FXXXDMA1_stream0_cr_dbm(uint8_t state)
{
	set_reg_block(&DMA1_Stream0->CR, 1, 18, state);
}
void STM32FXXXDMA1_stream0_cr_pl(uint8_t value)
{
	set_reg_block(&DMA1_Stream0->CR, 2, 16, value);
}
void STM32FXXXDMA1_stream0_cr_pincos(uint8_t state)
{
	set_reg_block(&DMA1_Stream0->CR, 1, 15, state);
}
void STM32FXXXDMA1_stream0_cr_msize(uint8_t value)
{
	set_reg_block(&DMA1_Stream0->CR, 2, 13, value);
}
void STM32FXXXDMA1_stream0_cr_psize(uint8_t value)
{
	set_reg_block(&DMA1_Stream0->CR, 2, 11, value);
}
void STM32FXXXDMA1_stream0_cr_minc(uint8_t state)
{
	set_reg_block(&DMA1_Stream0->CR, 1, 10, state);
}
void STM32FXXXDMA1_stream0_cr_pinc(uint8_t state)
{
	set_reg_block(&DMA1_Stream0->CR, 1, 9, state);
}
void STM32FXXXDMA1_stream0_cr_circ(uint8_t state)
{
	set_reg_block(&DMA1_Stream0->CR, 1, 8, state);
}
void STM32FXXXDMA1_stream0_cr_dir(uint8_t value)
{
	set_reg_block(&DMA1_Stream0->CR, 2, 7, value);
}
void STM32FXXXDMA1_stream0_cr_pfctrl(uint8_t state)
{
	set_reg_block(&DMA1_Stream0->CR, 1, 5, state);
}
void STM32FXXXDMA1_stream0_cr_tcie(uint8_t state)
{
	set_reg_block(&DMA1_Stream0->CR, 1, 4, state);
}
void STM32FXXXDMA1_stream0_cr_htie(uint8_t state)
{
	set_reg_block(&DMA1_Stream0->CR, 1, 3, state);
}
void STM32FXXXDMA1_stream0_cr_teie(uint8_t state)
{
	set_reg_block(&DMA1_Stream0->CR, 1, 2, state);
}
void STM32FXXXDMA1_stream0_cr_dmeie(uint8_t state)
{
	set_reg_block(&DMA1_Stream0->CR, 1, 1, state);
}
void STM32FXXXDMA1_stream0_cr_en(uint8_t state)
{
	set_reg_block(&DMA1_Stream0->CR, 1, 0, state);
}
/*** Inic DMA1 STREAM0 CR ***/
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma1_stream0_cr_inic(void)
{

	// CR
	stm32fxxx_dma1_stream0_cr.chsel = STM32FXXXDMA1_stream0_cr_chsel;
	stm32fxxx_dma1_stream0_cr.mburst = STM32FXXXDMA1_stream0_cr_mburst;
	stm32fxxx_dma1_stream0_cr.pburst = STM32FXXXDMA1_stream0_cr_pburst;
	stm32fxxx_dma1_stream0_cr.ct = STM32FXXXDMA1_stream0_cr_ct;
	stm32fxxx_dma1_stream0_cr.dbm = STM32FXXXDMA1_stream0_cr_dbm;
	stm32fxxx_dma1_stream0_cr.pl = STM32FXXXDMA1_stream0_cr_pl;
	stm32fxxx_dma1_stream0_cr.pincos = STM32FXXXDMA1_stream0_cr_pincos;
	stm32fxxx_dma1_stream0_cr.msize = STM32FXXXDMA1_stream0_cr_msize;
	stm32fxxx_dma1_stream0_cr.psize = STM32FXXXDMA1_stream0_cr_psize;
	stm32fxxx_dma1_stream0_cr.minc = STM32FXXXDMA1_stream0_cr_minc;
	stm32fxxx_dma1_stream0_cr.pinc = STM32FXXXDMA1_stream0_cr_pinc;
	stm32fxxx_dma1_stream0_cr.circ = STM32FXXXDMA1_stream0_cr_circ;
	stm32fxxx_dma1_stream0_cr.dir = STM32FXXXDMA1_stream0_cr_dir;
	stm32fxxx_dma1_stream0_cr.pfctrl = STM32FXXXDMA1_stream0_cr_pfctrl;
	stm32fxxx_dma1_stream0_cr.tcie = STM32FXXXDMA1_stream0_cr_tcie;
	stm32fxxx_dma1_stream0_cr.htie = STM32FXXXDMA1_stream0_cr_htie;
	stm32fxxx_dma1_stream0_cr.teie = STM32FXXXDMA1_stream0_cr_teie;
	stm32fxxx_dma1_stream0_cr.dmeie = STM32FXXXDMA1_stream0_cr_dmeie;
	stm32fxxx_dma1_stream0_cr.en = STM32FXXXDMA1_stream0_cr_en;
	return &stm32fxxx_dma1_stream0_cr;
}
/*** Inic DMA1 STREAM0 Function ***/
void stm32fxxx_dma1_stream0_ndt(uint16_t value)
{
	DMA1_Stream0->NDTR = value;
}
void stm32fxxx_dma1_stream0_par(volatile long unsigned int periferal_addr)
{
	DMA1_Stream0->PAR = periferal_addr;
}
void stm32fxxx_dma1_stream0_m0a(volatile long unsigned int mem0_addr)
{
	DMA1_Stream0->M0AR = mem0_addr;
}
void stm32fxxx_dma1_stream0_m1a(volatile long unsigned int mem1_addr)
{
	DMA1_Stream0->M1AR = mem1_addr;
}
// DMA1 STREAM1 CR
void STM32FXXXDMA1_stream1_cr_chsel(uint8_t value)
{
	set_reg_block(&DMA1_Stream1->CR, 3, 25, value);
}
void STM32FXXXDMA1_stream1_cr_mburst(uint8_t value)
{
	set_reg_block(&DMA1_Stream1->CR, 2, 23, value);
}
void STM32FXXXDMA1_stream1_cr_pburst(uint8_t value)
{
	set_reg_block(&DMA1_Stream1->CR, 2, 21, value);
}
void STM32FXXXDMA1_stream1_cr_ct(uint8_t state)
{
	set_reg_block(&DMA1_Stream1->CR, 1, 19, state);
}
void STM32FXXXDMA1_stream1_cr_dbm(uint8_t state)
{
	set_reg_block(&DMA1_Stream1->CR, 1, 18, state);
}
void STM32FXXXDMA1_stream1_cr_pl(uint8_t value)
{
	set_reg_block(&DMA1_Stream1->CR, 2, 16, value);
}
void STM32FXXXDMA1_stream1_cr_pincos(uint8_t state)
{
	set_reg_block(&DMA1_Stream1->CR, 1, 15, state);
}
void STM32FXXXDMA1_stream1_cr_msize(uint8_t value)
{
	set_reg_block(&DMA1_Stream1->CR, 2, 13, value);
}
void STM32FXXXDMA1_stream1_cr_psize(uint8_t value)
{
	set_reg_block(&DMA1_Stream1->CR, 2, 11, value);
}
void STM32FXXXDMA1_stream1_cr_minc(uint8_t state)
{
	set_reg_block(&DMA1_Stream1->CR, 1, 10, state);
}
void STM32FXXXDMA1_stream1_cr_pinc(uint8_t state)
{
	set_reg_block(&DMA1_Stream1->CR, 1, 9, state);
}
void STM32FXXXDMA1_stream1_cr_circ(uint8_t state)
{
	set_reg_block(&DMA1_Stream1->CR, 1, 8, state);
}
void STM32FXXXDMA1_stream1_cr_dir(uint8_t value)
{
	set_reg_block(&DMA1_Stream1->CR, 2, 7, value);
}
void STM32FXXXDMA1_stream1_cr_pfctrl(uint8_t state)
{
	set_reg_block(&DMA1_Stream1->CR, 1, 5, state);
}
void STM32FXXXDMA1_stream1_cr_tcie(uint8_t state)
{
	set_reg_block(&DMA1_Stream1->CR, 1, 4, state);
}
void STM32FXXXDMA1_stream1_cr_htie(uint8_t state)
{
	set_reg_block(&DMA1_Stream1->CR, 1, 3, state);
}
void STM32FXXXDMA1_stream1_cr_teie(uint8_t state)
{
	set_reg_block(&DMA1_Stream1->CR, 1, 2, state);
}
void STM32FXXXDMA1_stream1_cr_dmeie(uint8_t state)
{
	set_reg_block(&DMA1_Stream1->CR, 1, 1, state);
}
void STM32FXXXDMA1_stream1_cr_en(uint8_t state)
{
	set_reg_block(&DMA1_Stream1->CR, 1, 0, state);
}
/*** Inic DMA1 STREAM1 CR ***/
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma1_stream1_cr_inic(void)
{

	// CR
	stm32fxxx_dma1_stream1_cr.chsel = STM32FXXXDMA1_stream1_cr_chsel;
	stm32fxxx_dma1_stream1_cr.mburst = STM32FXXXDMA1_stream1_cr_mburst;
	stm32fxxx_dma1_stream1_cr.pburst = STM32FXXXDMA1_stream1_cr_pburst;
	stm32fxxx_dma1_stream1_cr.ct = STM32FXXXDMA1_stream1_cr_ct;
	stm32fxxx_dma1_stream1_cr.dbm = STM32FXXXDMA1_stream1_cr_dbm;
	stm32fxxx_dma1_stream1_cr.pl = STM32FXXXDMA1_stream1_cr_pl;
	stm32fxxx_dma1_stream1_cr.pincos = STM32FXXXDMA1_stream1_cr_pincos;
	stm32fxxx_dma1_stream1_cr.msize = STM32FXXXDMA1_stream1_cr_msize;
	stm32fxxx_dma1_stream1_cr.psize = STM32FXXXDMA1_stream1_cr_psize;
	stm32fxxx_dma1_stream1_cr.minc = STM32FXXXDMA1_stream1_cr_minc;
	stm32fxxx_dma1_stream1_cr.pinc = STM32FXXXDMA1_stream1_cr_pinc;
	stm32fxxx_dma1_stream1_cr.circ = STM32FXXXDMA1_stream1_cr_circ;
	stm32fxxx_dma1_stream1_cr.dir = STM32FXXXDMA1_stream1_cr_dir;
	stm32fxxx_dma1_stream1_cr.pfctrl = STM32FXXXDMA1_stream1_cr_pfctrl;
	stm32fxxx_dma1_stream1_cr.tcie = STM32FXXXDMA1_stream1_cr_tcie;
	stm32fxxx_dma1_stream1_cr.htie = STM32FXXXDMA1_stream1_cr_htie;
	stm32fxxx_dma1_stream1_cr.teie = STM32FXXXDMA1_stream1_cr_teie;
	stm32fxxx_dma1_stream1_cr.dmeie = STM32FXXXDMA1_stream1_cr_dmeie;
	stm32fxxx_dma1_stream1_cr.en = STM32FXXXDMA1_stream1_cr_en;
	return &stm32fxxx_dma1_stream1_cr;
}
/*** Inic DMA1 STREAM1 Function ***/
void stm32fxxx_dma1_stream1_ndt(uint16_t value)
{
	DMA1_Stream1->NDTR = value;
}
void stm32fxxx_dma1_stream1_par(volatile long unsigned int periferal_addr)
{
	DMA1_Stream1->PAR = periferal_addr;
}
void stm32fxxx_dma1_stream1_m0a(volatile long unsigned int mem0_addr)
{
	DMA1_Stream1->M0AR = mem0_addr;
}
void stm32fxxx_dma1_stream1_m1a(volatile long unsigned int mem1_addr)
{
	DMA1_Stream1->M1AR = mem1_addr;
}
// DMA1 STREAM2 CR
void STM32FXXXDMA1_stream2_cr_chsel(uint8_t value)
{
	set_reg_block(&DMA1_Stream2->CR, 3, 25, value);
}
void STM32FXXXDMA1_stream2_cr_mburst(uint8_t value)
{
	set_reg_block(&DMA1_Stream2->CR, 2, 23, value);
}
void STM32FXXXDMA1_stream2_cr_pburst(uint8_t value)
{
	set_reg_block(&DMA1_Stream2->CR, 2, 21, value);
}
void STM32FXXXDMA1_stream2_cr_ct(uint8_t state)
{
	set_reg_block(&DMA1_Stream2->CR, 1, 19, state);
}
void STM32FXXXDMA1_stream2_cr_dbm(uint8_t state)
{
	set_reg_block(&DMA1_Stream2->CR, 1, 18, state);
}
void STM32FXXXDMA1_stream2_cr_pl(uint8_t value)
{
	set_reg_block(&DMA1_Stream2->CR, 2, 16, value);
}
void STM32FXXXDMA1_stream2_cr_pincos(uint8_t state)
{
	set_reg_block(&DMA1_Stream2->CR, 1, 15, state);
}
void STM32FXXXDMA1_stream2_cr_msize(uint8_t value)
{
	set_reg_block(&DMA1_Stream2->CR, 2, 13, value);
}
void STM32FXXXDMA1_stream2_cr_psize(uint8_t value)
{
	set_reg_block(&DMA1_Stream2->CR, 2, 11, value);
}
void STM32FXXXDMA1_stream2_cr_minc(uint8_t state)
{
	set_reg_block(&DMA1_Stream2->CR, 1, 10, state);
}
void STM32FXXXDMA1_stream2_cr_pinc(uint8_t state)
{
	set_reg_block(&DMA1_Stream2->CR, 1, 9, state);
}
void STM32FXXXDMA1_stream2_cr_circ(uint8_t state)
{
	set_reg_block(&DMA1_Stream2->CR, 1, 8, state);
}
void STM32FXXXDMA1_stream2_cr_dir(uint8_t value)
{
	set_reg_block(&DMA1_Stream2->CR, 2, 7, value);
}
void STM32FXXXDMA1_stream2_cr_pfctrl(uint8_t state)
{
	set_reg_block(&DMA1_Stream2->CR, 1, 5, state);
}
void STM32FXXXDMA1_stream2_cr_tcie(uint8_t state)
{
	set_reg_block(&DMA1_Stream2->CR, 1, 4, state);
}
void STM32FXXXDMA1_stream2_cr_htie(uint8_t state)
{
	set_reg_block(&DMA1_Stream2->CR, 1, 3, state);
}
void STM32FXXXDMA1_stream2_cr_teie(uint8_t state)
{
	set_reg_block(&DMA1_Stream2->CR, 1, 2, state);
}
void STM32FXXXDMA1_stream2_cr_dmeie(uint8_t state)
{
	set_reg_block(&DMA1_Stream2->CR, 1, 1, state);
}
void STM32FXXXDMA1_stream2_cr_en(uint8_t state)
{
	set_reg_block(&DMA1_Stream2->CR, 1, 0, state);
}
/*** Inic DMA1 STREAM2 CR ***/
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma1_stream2_cr_inic(void)
{

	// CR
	stm32fxxx_dma1_stream2_cr.chsel = STM32FXXXDMA1_stream2_cr_chsel;
	stm32fxxx_dma1_stream2_cr.mburst = STM32FXXXDMA1_stream2_cr_mburst;
	stm32fxxx_dma1_stream2_cr.pburst = STM32FXXXDMA1_stream2_cr_pburst;
	stm32fxxx_dma1_stream2_cr.ct = STM32FXXXDMA1_stream2_cr_ct;
	stm32fxxx_dma1_stream2_cr.dbm = STM32FXXXDMA1_stream2_cr_dbm;
	stm32fxxx_dma1_stream2_cr.pl = STM32FXXXDMA1_stream2_cr_pl;
	stm32fxxx_dma1_stream2_cr.pincos = STM32FXXXDMA1_stream2_cr_pincos;
	stm32fxxx_dma1_stream2_cr.msize = STM32FXXXDMA1_stream2_cr_msize;
	stm32fxxx_dma1_stream2_cr.psize = STM32FXXXDMA1_stream2_cr_psize;
	stm32fxxx_dma1_stream2_cr.minc = STM32FXXXDMA1_stream2_cr_minc;
	stm32fxxx_dma1_stream2_cr.pinc = STM32FXXXDMA1_stream2_cr_pinc;
	stm32fxxx_dma1_stream2_cr.circ = STM32FXXXDMA1_stream2_cr_circ;
	stm32fxxx_dma1_stream2_cr.dir = STM32FXXXDMA1_stream2_cr_dir;
	stm32fxxx_dma1_stream2_cr.pfctrl = STM32FXXXDMA1_stream2_cr_pfctrl;
	stm32fxxx_dma1_stream2_cr.tcie = STM32FXXXDMA1_stream2_cr_tcie;
	stm32fxxx_dma1_stream2_cr.htie = STM32FXXXDMA1_stream2_cr_htie;
	stm32fxxx_dma1_stream2_cr.teie = STM32FXXXDMA1_stream2_cr_teie;
	stm32fxxx_dma1_stream2_cr.dmeie = STM32FXXXDMA1_stream2_cr_dmeie;
	stm32fxxx_dma1_stream2_cr.en = STM32FXXXDMA1_stream2_cr_en;
	return &stm32fxxx_dma1_stream2_cr;
}
/*** Inic DMA1 STREAM2 Function ***/
void stm32fxxx_dma1_stream2_ndt(uint16_t value)
{
	DMA1_Stream2->NDTR = value;
}
void stm32fxxx_dma1_stream2_par(volatile long unsigned int periferal_addr)
{
	DMA1_Stream2->PAR = periferal_addr;
}
void stm32fxxx_dma1_stream2_m0a(volatile long unsigned int mem0_addr)
{
	DMA1_Stream2->M0AR = mem0_addr;
}
void stm32fxxx_dma1_stream2_m1a(volatile long unsigned int mem1_addr)
{
	DMA1_Stream2->M1AR = mem1_addr;
}
// DMA1 STREAM3 CR
void STM32FXXXDMA1_stream3_cr_chsel(uint8_t value)
{
	set_reg_block(&DMA1_Stream3->CR, 3, 25, value);
}
void STM32FXXXDMA1_stream3_cr_mburst(uint8_t value)
{
	set_reg_block(&DMA1_Stream3->CR, 2, 23, value);
}
void STM32FXXXDMA1_stream3_cr_pburst(uint8_t value)
{
	set_reg_block(&DMA1_Stream3->CR, 2, 21, value);
}
void STM32FXXXDMA1_stream3_cr_ct(uint8_t state)
{
	set_reg_block(&DMA1_Stream3->CR, 1, 19, state);
}
void STM32FXXXDMA1_stream3_cr_dbm(uint8_t state)
{
	set_reg_block(&DMA1_Stream3->CR, 1, 18, state);
}
void STM32FXXXDMA1_stream3_cr_pl(uint8_t value)
{
	set_reg_block(&DMA1_Stream3->CR, 2, 16, value);
}
void STM32FXXXDMA1_stream3_cr_pincos(uint8_t state)
{
	set_reg_block(&DMA1_Stream3->CR, 1, 15, state);
}
void STM32FXXXDMA1_stream3_cr_msize(uint8_t value)
{
	set_reg_block(&DMA1_Stream3->CR, 2, 13, value);
}
void STM32FXXXDMA1_stream3_cr_psize(uint8_t value)
{
	set_reg_block(&DMA1_Stream3->CR, 2, 11, value);
}
void STM32FXXXDMA1_stream3_cr_minc(uint8_t state)
{
	set_reg_block(&DMA1_Stream3->CR, 1, 10, state);
}
void STM32FXXXDMA1_stream3_cr_pinc(uint8_t state)
{
	set_reg_block(&DMA1_Stream3->CR, 1, 9, state);
}
void STM32FXXXDMA1_stream3_cr_circ(uint8_t state)
{
	set_reg_block(&DMA1_Stream3->CR, 1, 8, state);
}
void STM32FXXXDMA1_stream3_cr_dir(uint8_t value)
{
	set_reg_block(&DMA1_Stream3->CR, 2, 7, value);
}
void STM32FXXXDMA1_stream3_cr_pfctrl(uint8_t state)
{
	set_reg_block(&DMA1_Stream3->CR, 1, 5, state);
}
void STM32FXXXDMA1_stream3_cr_tcie(uint8_t state)
{
	set_reg_block(&DMA1_Stream3->CR, 1, 4, state);
}
void STM32FXXXDMA1_stream3_cr_htie(uint8_t state)
{
	set_reg_block(&DMA1_Stream3->CR, 1, 3, state);
}
void STM32FXXXDMA1_stream3_cr_teie(uint8_t state)
{
	set_reg_block(&DMA1_Stream3->CR, 1, 2, state);
}
void STM32FXXXDMA1_stream3_cr_dmeie(uint8_t state)
{
	set_reg_block(&DMA1_Stream3->CR, 1, 1, state);
}
void STM32FXXXDMA1_stream3_cr_en(uint8_t state)
{
	set_reg_block(&DMA1_Stream3->CR, 1, 0, state);
}
/*** Inic DMA1 STREAM3 CR ***/
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma1_stream3_cr_inic(void)
{

	// CR
	stm32fxxx_dma1_stream3_cr.chsel = STM32FXXXDMA1_stream3_cr_chsel;
	stm32fxxx_dma1_stream3_cr.mburst = STM32FXXXDMA1_stream3_cr_mburst;
	stm32fxxx_dma1_stream3_cr.pburst = STM32FXXXDMA1_stream3_cr_pburst;
	stm32fxxx_dma1_stream3_cr.ct = STM32FXXXDMA1_stream3_cr_ct;
	stm32fxxx_dma1_stream3_cr.dbm = STM32FXXXDMA1_stream3_cr_dbm;
	stm32fxxx_dma1_stream3_cr.pl = STM32FXXXDMA1_stream3_cr_pl;
	stm32fxxx_dma1_stream3_cr.pincos = STM32FXXXDMA1_stream3_cr_pincos;
	stm32fxxx_dma1_stream3_cr.msize = STM32FXXXDMA1_stream3_cr_msize;
	stm32fxxx_dma1_stream3_cr.psize = STM32FXXXDMA1_stream3_cr_psize;
	stm32fxxx_dma1_stream3_cr.minc = STM32FXXXDMA1_stream3_cr_minc;
	stm32fxxx_dma1_stream3_cr.pinc = STM32FXXXDMA1_stream3_cr_pinc;
	stm32fxxx_dma1_stream3_cr.circ = STM32FXXXDMA1_stream3_cr_circ;
	stm32fxxx_dma1_stream3_cr.dir = STM32FXXXDMA1_stream3_cr_dir;
	stm32fxxx_dma1_stream3_cr.pfctrl = STM32FXXXDMA1_stream3_cr_pfctrl;
	stm32fxxx_dma1_stream3_cr.tcie = STM32FXXXDMA1_stream3_cr_tcie;
	stm32fxxx_dma1_stream3_cr.htie = STM32FXXXDMA1_stream3_cr_htie;
	stm32fxxx_dma1_stream3_cr.teie = STM32FXXXDMA1_stream3_cr_teie;
	stm32fxxx_dma1_stream3_cr.dmeie = STM32FXXXDMA1_stream3_cr_dmeie;
	stm32fxxx_dma1_stream3_cr.en = STM32FXXXDMA1_stream3_cr_en;
	return &stm32fxxx_dma1_stream3_cr;
}
/*** Inic DMA1 STREAM3 Function ***/
void stm32fxxx_dma1_stream3_ndt(uint16_t value)
{
	DMA1_Stream3->NDTR = value;
}
void stm32fxxx_dma1_stream3_par(volatile long unsigned int periferal_addr)
{
	DMA1_Stream3->PAR = periferal_addr;
}
void stm32fxxx_dma1_stream3_m0a(volatile long unsigned int mem0_addr)
{
	DMA1_Stream3->M0AR = mem0_addr;
}
void stm32fxxx_dma1_stream3_m1a(volatile long unsigned int mem1_addr)
{
	DMA1_Stream3->M1AR = mem1_addr;
}
// DMA1 STREAM4 CR
void STM32FXXXDMA1_stream4_cr_chsel(uint8_t value)
{
	set_reg_block(&DMA1_Stream4->CR, 3, 25, value);
}
void STM32FXXXDMA1_stream4_cr_mburst(uint8_t value)
{
	set_reg_block(&DMA1_Stream4->CR, 2, 23, value);
}
void STM32FXXXDMA1_stream4_cr_pburst(uint8_t value)
{
	set_reg_block(&DMA1_Stream4->CR, 2, 21, value);
}
void STM32FXXXDMA1_stream4_cr_ct(uint8_t state)
{
	set_reg_block(&DMA1_Stream4->CR, 1, 19, state);
}
void STM32FXXXDMA1_stream4_cr_dbm(uint8_t state)
{
	set_reg_block(&DMA1_Stream4->CR, 1, 18, state);
}
void STM32FXXXDMA1_stream4_cr_pl(uint8_t value)
{
	set_reg_block(&DMA1_Stream4->CR, 2, 16, value);
}
void STM32FXXXDMA1_stream4_cr_pincos(uint8_t state)
{
	set_reg_block(&DMA1_Stream4->CR, 1, 15, state);
}
void STM32FXXXDMA1_stream4_cr_msize(uint8_t value)
{
	set_reg_block(&DMA1_Stream4->CR, 2, 13, value);
}
void STM32FXXXDMA1_stream4_cr_psize(uint8_t value)
{
	set_reg_block(&DMA1_Stream4->CR, 2, 11, value);
}
void STM32FXXXDMA1_stream4_cr_minc(uint8_t state)
{
	set_reg_block(&DMA1_Stream4->CR, 1, 10, state);
}
void STM32FXXXDMA1_stream4_cr_pinc(uint8_t state)
{
	set_reg_block(&DMA1_Stream4->CR, 1, 9, state);
}
void STM32FXXXDMA1_stream4_cr_circ(uint8_t state)
{
	set_reg_block(&DMA1_Stream4->CR, 1, 8, state);
}
void STM32FXXXDMA1_stream4_cr_dir(uint8_t value)
{
	set_reg_block(&DMA1_Stream4->CR, 2, 7, value);
}
void STM32FXXXDMA1_stream4_cr_pfctrl(uint8_t state)
{
	set_reg_block(&DMA1_Stream4->CR, 1, 5, state);
}
void STM32FXXXDMA1_stream4_cr_tcie(uint8_t state)
{
	set_reg_block(&DMA1_Stream4->CR, 1, 4, state);
}
void STM32FXXXDMA1_stream4_cr_htie(uint8_t state)
{
	set_reg_block(&DMA1_Stream4->CR, 1, 3, state);
}
void STM32FXXXDMA1_stream4_cr_teie(uint8_t state)
{
	set_reg_block(&DMA1_Stream4->CR, 1, 2, state);
}
void STM32FXXXDMA1_stream4_cr_dmeie(uint8_t state)
{
	set_reg_block(&DMA1_Stream4->CR, 1, 1, state);
}
void STM32FXXXDMA1_stream4_cr_en(uint8_t state)
{
	set_reg_block(&DMA1_Stream4->CR, 1, 0, state);
}
/*** Inic DMA1 STREAM4 CR ***/
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma1_stream4_cr_inic(void)
{

	// CR
	stm32fxxx_dma1_stream4_cr.chsel = STM32FXXXDMA1_stream4_cr_chsel;
	stm32fxxx_dma1_stream4_cr.mburst = STM32FXXXDMA1_stream4_cr_mburst;
	stm32fxxx_dma1_stream4_cr.pburst = STM32FXXXDMA1_stream4_cr_pburst;
	stm32fxxx_dma1_stream4_cr.ct = STM32FXXXDMA1_stream4_cr_ct;
	stm32fxxx_dma1_stream4_cr.dbm = STM32FXXXDMA1_stream4_cr_dbm;
	stm32fxxx_dma1_stream4_cr.pl = STM32FXXXDMA1_stream4_cr_pl;
	stm32fxxx_dma1_stream4_cr.pincos = STM32FXXXDMA1_stream4_cr_pincos;
	stm32fxxx_dma1_stream4_cr.msize = STM32FXXXDMA1_stream4_cr_msize;
	stm32fxxx_dma1_stream4_cr.psize = STM32FXXXDMA1_stream4_cr_psize;
	stm32fxxx_dma1_stream4_cr.minc = STM32FXXXDMA1_stream4_cr_minc;
	stm32fxxx_dma1_stream4_cr.pinc = STM32FXXXDMA1_stream4_cr_pinc;
	stm32fxxx_dma1_stream4_cr.circ = STM32FXXXDMA1_stream4_cr_circ;
	stm32fxxx_dma1_stream4_cr.dir = STM32FXXXDMA1_stream4_cr_dir;
	stm32fxxx_dma1_stream4_cr.pfctrl = STM32FXXXDMA1_stream4_cr_pfctrl;
	stm32fxxx_dma1_stream4_cr.tcie = STM32FXXXDMA1_stream4_cr_tcie;
	stm32fxxx_dma1_stream4_cr.htie = STM32FXXXDMA1_stream4_cr_htie;
	stm32fxxx_dma1_stream4_cr.teie = STM32FXXXDMA1_stream4_cr_teie;
	stm32fxxx_dma1_stream4_cr.dmeie = STM32FXXXDMA1_stream4_cr_dmeie;
	stm32fxxx_dma1_stream4_cr.en = STM32FXXXDMA1_stream4_cr_en;
	return &stm32fxxx_dma1_stream4_cr;
}
/*** Inic DMA1 STREAM4 Function ***/
void stm32fxxx_dma1_stream4_ndt(uint16_t value)
{
	DMA1_Stream4->NDTR = value;
}
void stm32fxxx_dma1_stream4_par(volatile long unsigned int periferal_addr)
{
	DMA1_Stream4->PAR = periferal_addr;
}
void stm32fxxx_dma1_stream4_m0a(volatile long unsigned int mem0_addr)
{
	DMA1_Stream4->M0AR = mem0_addr;
}
void stm32fxxx_dma1_stream4_m1a(volatile long unsigned int mem1_addr)
{
	DMA1_Stream4->M1AR = mem1_addr;
}
// DMA1 STREAM5 CR
void STM32FXXXDMA1_stream5_cr_chsel(uint8_t value)
{
	set_reg_block(&DMA1_Stream5->CR, 3, 25, value);
}
void STM32FXXXDMA1_stream5_cr_mburst(uint8_t value)
{
	set_reg_block(&DMA1_Stream5->CR, 2, 23, value);
}
void STM32FXXXDMA1_stream5_cr_pburst(uint8_t value)
{
	set_reg_block(&DMA1_Stream5->CR, 2, 21, value);
}
void STM32FXXXDMA1_stream5_cr_ct(uint8_t state)
{
	set_reg_block(&DMA1_Stream5->CR, 1, 19, state);
}
void STM32FXXXDMA1_stream5_cr_dbm(uint8_t state)
{
	set_reg_block(&DMA1_Stream5->CR, 1, 18, state);
}
void STM32FXXXDMA1_stream5_cr_pl(uint8_t value)
{
	set_reg_block(&DMA1_Stream5->CR, 2, 16, value);
}
void STM32FXXXDMA1_stream5_cr_pincos(uint8_t state)
{
	set_reg_block(&DMA1_Stream5->CR, 1, 15, state);
}
void STM32FXXXDMA1_stream5_cr_msize(uint8_t value)
{
	set_reg_block(&DMA1_Stream5->CR, 2, 13, value);
}
void STM32FXXXDMA1_stream5_cr_psize(uint8_t value)
{
	set_reg_block(&DMA1_Stream5->CR, 2, 11, value);
}
void STM32FXXXDMA1_stream5_cr_minc(uint8_t state)
{
	set_reg_block(&DMA1_Stream5->CR, 1, 10, state);
}
void STM32FXXXDMA1_stream5_cr_pinc(uint8_t state)
{
	set_reg_block(&DMA1_Stream5->CR, 1, 9, state);
}
void STM32FXXXDMA1_stream5_cr_circ(uint8_t state)
{
	set_reg_block(&DMA1_Stream5->CR, 1, 8, state);
}
void STM32FXXXDMA1_stream5_cr_dir(uint8_t value)
{
	set_reg_block(&DMA1_Stream5->CR, 2, 7, value);
}
void STM32FXXXDMA1_stream5_cr_pfctrl(uint8_t state)
{
	set_reg_block(&DMA1_Stream5->CR, 1, 5, state);
}
void STM32FXXXDMA1_stream5_cr_tcie(uint8_t state)
{
	set_reg_block(&DMA1_Stream5->CR, 1, 4, state);
}
void STM32FXXXDMA1_stream5_cr_htie(uint8_t state)
{
	set_reg_block(&DMA1_Stream5->CR, 1, 3, state);
}
void STM32FXXXDMA1_stream5_cr_teie(uint8_t state)
{
	set_reg_block(&DMA1_Stream5->CR, 1, 2, state);
}
void STM32FXXXDMA1_stream5_cr_dmeie(uint8_t state)
{
	set_reg_block(&DMA1_Stream5->CR, 1, 1, state);
}
void STM32FXXXDMA1_stream5_cr_en(uint8_t state)
{
	set_reg_block(&DMA1_Stream5->CR, 1, 0, state);
}
/*** Inic DMA1 STREAM5 CR ***/
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma1_stream5_cr_inic(void)
{

	// CR
	stm32fxxx_dma1_stream5_cr.chsel = STM32FXXXDMA1_stream5_cr_chsel;
	stm32fxxx_dma1_stream5_cr.mburst = STM32FXXXDMA1_stream5_cr_mburst;
	stm32fxxx_dma1_stream5_cr.pburst = STM32FXXXDMA1_stream5_cr_pburst;
	stm32fxxx_dma1_stream5_cr.ct = STM32FXXXDMA1_stream5_cr_ct;
	stm32fxxx_dma1_stream5_cr.dbm = STM32FXXXDMA1_stream5_cr_dbm;
	stm32fxxx_dma1_stream5_cr.pl = STM32FXXXDMA1_stream5_cr_pl;
	stm32fxxx_dma1_stream5_cr.pincos = STM32FXXXDMA1_stream5_cr_pincos;
	stm32fxxx_dma1_stream5_cr.msize = STM32FXXXDMA1_stream5_cr_msize;
	stm32fxxx_dma1_stream5_cr.psize = STM32FXXXDMA1_stream5_cr_psize;
	stm32fxxx_dma1_stream5_cr.minc = STM32FXXXDMA1_stream5_cr_minc;
	stm32fxxx_dma1_stream5_cr.pinc = STM32FXXXDMA1_stream5_cr_pinc;
	stm32fxxx_dma1_stream5_cr.circ = STM32FXXXDMA1_stream5_cr_circ;
	stm32fxxx_dma1_stream5_cr.dir = STM32FXXXDMA1_stream5_cr_dir;
	stm32fxxx_dma1_stream5_cr.pfctrl = STM32FXXXDMA1_stream5_cr_pfctrl;
	stm32fxxx_dma1_stream5_cr.tcie = STM32FXXXDMA1_stream5_cr_tcie;
	stm32fxxx_dma1_stream5_cr.htie = STM32FXXXDMA1_stream5_cr_htie;
	stm32fxxx_dma1_stream5_cr.teie = STM32FXXXDMA1_stream5_cr_teie;
	stm32fxxx_dma1_stream5_cr.dmeie = STM32FXXXDMA1_stream5_cr_dmeie;
	stm32fxxx_dma1_stream5_cr.en = STM32FXXXDMA1_stream5_cr_en;
	return &stm32fxxx_dma1_stream5_cr;
}
/*** Inic DMA1 STREAM5 Function ***/
void stm32fxxx_dma1_stream5_ndt(uint16_t value)
{
	DMA1_Stream5->NDTR = value;
}
void stm32fxxx_dma1_stream5_par(volatile long unsigned int periferal_addr)
{
	DMA1_Stream5->PAR = periferal_addr;
}
void stm32fxxx_dma1_stream5_m0a(volatile long unsigned int mem0_addr)
{
	DMA1_Stream5->M0AR = mem0_addr;
}
void stm32fxxx_dma1_stream5_m1a(volatile long unsigned int mem1_addr)
{
	DMA1_Stream5->M1AR = mem1_addr;
}
// DMA1 STREAM6 CR
void STM32FXXXDMA1_stream6_cr_chsel(uint8_t value)
{
	set_reg_block(&DMA1_Stream6->CR, 3, 25, value);
}
void STM32FXXXDMA1_stream6_cr_mburst(uint8_t value)
{
	set_reg_block(&DMA1_Stream6->CR, 2, 23, value);
}
void STM32FXXXDMA1_stream6_cr_pburst(uint8_t value)
{
	set_reg_block(&DMA1_Stream6->CR, 2, 21, value);
}
void STM32FXXXDMA1_stream6_cr_ct(uint8_t state)
{
	set_reg_block(&DMA1_Stream6->CR, 1, 19, state);
}
void STM32FXXXDMA1_stream6_cr_dbm(uint8_t state)
{
	set_reg_block(&DMA1_Stream6->CR, 1, 18, state);
}
void STM32FXXXDMA1_stream6_cr_pl(uint8_t value)
{
	set_reg_block(&DMA1_Stream6->CR, 2, 16, value);
}
void STM32FXXXDMA1_stream6_cr_pincos(uint8_t state)
{
	set_reg_block(&DMA1_Stream6->CR, 1, 15, state);
}
void STM32FXXXDMA1_stream6_cr_msize(uint8_t value)
{
	set_reg_block(&DMA1_Stream6->CR, 2, 13, value);
}
void STM32FXXXDMA1_stream6_cr_psize(uint8_t value)
{
	set_reg_block(&DMA1_Stream6->CR, 2, 11, value);
}
void STM32FXXXDMA1_stream6_cr_minc(uint8_t state)
{
	set_reg_block(&DMA1_Stream6->CR, 1, 10, state);
}
void STM32FXXXDMA1_stream6_cr_pinc(uint8_t state)
{
	set_reg_block(&DMA1_Stream6->CR, 1, 9, state);
}
void STM32FXXXDMA1_stream6_cr_circ(uint8_t state)
{
	set_reg_block(&DMA1_Stream6->CR, 1, 8, state);
}
void STM32FXXXDMA1_stream6_cr_dir(uint8_t value)
{
	set_reg_block(&DMA1_Stream6->CR, 2, 7, value);
}
void STM32FXXXDMA1_stream6_cr_pfctrl(uint8_t state)
{
	set_reg_block(&DMA1_Stream6->CR, 1, 5, state);
}
void STM32FXXXDMA1_stream6_cr_tcie(uint8_t state)
{
	set_reg_block(&DMA1_Stream6->CR, 1, 4, state);
}
void STM32FXXXDMA1_stream6_cr_htie(uint8_t state)
{
	set_reg_block(&DMA1_Stream6->CR, 1, 3, state);
}
void STM32FXXXDMA1_stream6_cr_teie(uint8_t state)
{
	set_reg_block(&DMA1_Stream6->CR, 1, 2, state);
}
void STM32FXXXDMA1_stream6_cr_dmeie(uint8_t state)
{
	set_reg_block(&DMA1_Stream6->CR, 1, 1, state);
}
void STM32FXXXDMA1_stream6_cr_en(uint8_t state)
{
	set_reg_block(&DMA1_Stream6->CR, 1, 0, state);
}
/*** Inic DMA1 STREAM6 CR ***/
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma1_stream6_cr_inic(void)
{

	// CR
	stm32fxxx_dma1_stream6_cr.chsel = STM32FXXXDMA1_stream6_cr_chsel;
	stm32fxxx_dma1_stream6_cr.mburst = STM32FXXXDMA1_stream6_cr_mburst;
	stm32fxxx_dma1_stream6_cr.pburst = STM32FXXXDMA1_stream6_cr_pburst;
	stm32fxxx_dma1_stream6_cr.ct = STM32FXXXDMA1_stream6_cr_ct;
	stm32fxxx_dma1_stream6_cr.dbm = STM32FXXXDMA1_stream6_cr_dbm;
	stm32fxxx_dma1_stream6_cr.pl = STM32FXXXDMA1_stream6_cr_pl;
	stm32fxxx_dma1_stream6_cr.pincos = STM32FXXXDMA1_stream6_cr_pincos;
	stm32fxxx_dma1_stream6_cr.msize = STM32FXXXDMA1_stream6_cr_msize;
	stm32fxxx_dma1_stream6_cr.psize = STM32FXXXDMA1_stream6_cr_psize;
	stm32fxxx_dma1_stream6_cr.minc = STM32FXXXDMA1_stream6_cr_minc;
	stm32fxxx_dma1_stream6_cr.pinc = STM32FXXXDMA1_stream6_cr_pinc;
	stm32fxxx_dma1_stream6_cr.circ = STM32FXXXDMA1_stream6_cr_circ;
	stm32fxxx_dma1_stream6_cr.dir = STM32FXXXDMA1_stream6_cr_dir;
	stm32fxxx_dma1_stream6_cr.pfctrl = STM32FXXXDMA1_stream6_cr_pfctrl;
	stm32fxxx_dma1_stream6_cr.tcie = STM32FXXXDMA1_stream6_cr_tcie;
	stm32fxxx_dma1_stream6_cr.htie = STM32FXXXDMA1_stream6_cr_htie;
	stm32fxxx_dma1_stream6_cr.teie = STM32FXXXDMA1_stream6_cr_teie;
	stm32fxxx_dma1_stream6_cr.dmeie = STM32FXXXDMA1_stream6_cr_dmeie;
	stm32fxxx_dma1_stream6_cr.en = STM32FXXXDMA1_stream6_cr_en;
	return &stm32fxxx_dma1_stream6_cr;
}
/*** Inic DMA1 STREAM6 Function ***/
void stm32fxxx_dma1_stream6_ndt(uint16_t value)
{
	DMA1_Stream6->NDTR = value;
}
void stm32fxxx_dma1_stream6_par(volatile long unsigned int periferal_addr)
{
	DMA1_Stream6->PAR = periferal_addr;
}
void stm32fxxx_dma1_stream6_m0a(volatile long unsigned int mem0_addr)
{
	DMA1_Stream6->M0AR = mem0_addr;
}
void stm32fxxx_dma1_stream6_m1a(volatile long unsigned int mem1_addr)
{
	DMA1_Stream6->M1AR = mem1_addr;
}
// DMA1 STREAM7 CR
void STM32FXXXDMA1_stream7_cr_chsel(uint8_t value)
{
	set_reg_block(&DMA1_Stream7->CR, 3, 25, value);
}
void STM32FXXXDMA1_stream7_cr_mburst(uint8_t value)
{
	set_reg_block(&DMA1_Stream7->CR, 2, 23, value);
}
void STM32FXXXDMA1_stream7_cr_pburst(uint8_t value)
{
	set_reg_block(&DMA1_Stream7->CR, 2, 21, value);
}
void STM32FXXXDMA1_stream7_cr_ct(uint8_t state)
{
	set_reg_block(&DMA1_Stream7->CR, 1, 19, state);
}
void STM32FXXXDMA1_stream7_cr_dbm(uint8_t state)
{
	set_reg_block(&DMA1_Stream7->CR, 1, 18, state);
}
void STM32FXXXDMA1_stream7_cr_pl(uint8_t value)
{
	set_reg_block(&DMA1_Stream7->CR, 2, 16, value);
}
void STM32FXXXDMA1_stream7_cr_pincos(uint8_t state)
{
	set_reg_block(&DMA1_Stream7->CR, 1, 15, state);
}
void STM32FXXXDMA1_stream7_cr_msize(uint8_t value)
{
	set_reg_block(&DMA1_Stream7->CR, 2, 13, value);
}
void STM32FXXXDMA1_stream7_cr_psize(uint8_t value)
{
	set_reg_block(&DMA1_Stream7->CR, 2, 11, value);
}
void STM32FXXXDMA1_stream7_cr_minc(uint8_t state)
{
	set_reg_block(&DMA1_Stream7->CR, 1, 10, state);
}
void STM32FXXXDMA1_stream7_cr_pinc(uint8_t state)
{
	set_reg_block(&DMA1_Stream7->CR, 1, 9, state);
}
void STM32FXXXDMA1_stream7_cr_circ(uint8_t state)
{
	set_reg_block(&DMA1_Stream7->CR, 1, 8, state);
}
void STM32FXXXDMA1_stream7_cr_dir(uint8_t value)
{
	set_reg_block(&DMA1_Stream7->CR, 2, 7, value);
}
void STM32FXXXDMA1_stream7_cr_pfctrl(uint8_t state)
{
	set_reg_block(&DMA1_Stream7->CR, 1, 5, state);
}
void STM32FXXXDMA1_stream7_cr_tcie(uint8_t state)
{
	set_reg_block(&DMA1_Stream7->CR, 1, 4, state);
}
void STM32FXXXDMA1_stream7_cr_htie(uint8_t state)
{
	set_reg_block(&DMA1_Stream7->CR, 1, 3, state);
}
void STM32FXXXDMA1_stream7_cr_teie(uint8_t state)
{
	set_reg_block(&DMA1_Stream7->CR, 1, 2, state);
}
void STM32FXXXDMA1_stream7_cr_dmeie(uint8_t state)
{
	set_reg_block(&DMA1_Stream7->CR, 1, 1, state);
}
void STM32FXXXDMA1_stream7_cr_en(uint8_t state)
{
	set_reg_block(&DMA1_Stream7->CR, 1, 0, state);
}
/*** Inic DMA1 STREAM7 CR ***/
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma1_stream7_cr_inic(void)
{

	// CR
	stm32fxxx_dma1_stream7_cr.chsel = STM32FXXXDMA1_stream7_cr_chsel;
	stm32fxxx_dma1_stream7_cr.mburst = STM32FXXXDMA1_stream7_cr_mburst;
	stm32fxxx_dma1_stream7_cr.pburst = STM32FXXXDMA1_stream7_cr_pburst;
	stm32fxxx_dma1_stream7_cr.ct = STM32FXXXDMA1_stream7_cr_ct;
	stm32fxxx_dma1_stream7_cr.dbm = STM32FXXXDMA1_stream7_cr_dbm;
	stm32fxxx_dma1_stream7_cr.pl = STM32FXXXDMA1_stream7_cr_pl;
	stm32fxxx_dma1_stream7_cr.pincos = STM32FXXXDMA1_stream7_cr_pincos;
	stm32fxxx_dma1_stream7_cr.msize = STM32FXXXDMA1_stream7_cr_msize;
	stm32fxxx_dma1_stream7_cr.psize = STM32FXXXDMA1_stream7_cr_psize;
	stm32fxxx_dma1_stream7_cr.minc = STM32FXXXDMA1_stream7_cr_minc;
	stm32fxxx_dma1_stream7_cr.pinc = STM32FXXXDMA1_stream7_cr_pinc;
	stm32fxxx_dma1_stream7_cr.circ = STM32FXXXDMA1_stream7_cr_circ;
	stm32fxxx_dma1_stream7_cr.dir = STM32FXXXDMA1_stream7_cr_dir;
	stm32fxxx_dma1_stream7_cr.pfctrl = STM32FXXXDMA1_stream7_cr_pfctrl;
	stm32fxxx_dma1_stream7_cr.tcie = STM32FXXXDMA1_stream7_cr_tcie;
	stm32fxxx_dma1_stream7_cr.htie = STM32FXXXDMA1_stream7_cr_htie;
	stm32fxxx_dma1_stream7_cr.teie = STM32FXXXDMA1_stream7_cr_teie;
	stm32fxxx_dma1_stream7_cr.dmeie = STM32FXXXDMA1_stream7_cr_dmeie;
	stm32fxxx_dma1_stream7_cr.en = STM32FXXXDMA1_stream7_cr_en;
	return &stm32fxxx_dma1_stream7_cr;
}
/*** Inic DMA1 STREAM7 Function ***/
void stm32fxxx_dma1_stream7_ndt(uint16_t value)
{
	DMA1_Stream7->NDTR = value;
}
void stm32fxxx_dma1_stream7_par(volatile long unsigned int periferal_addr)
{
	DMA1_Stream7->PAR = periferal_addr;
}
void stm32fxxx_dma1_stream7_m0a(volatile long unsigned int mem0_addr)
{
	DMA1_Stream7->M0AR = mem0_addr;
}
void stm32fxxx_dma1_stream7_m1a(volatile long unsigned int mem1_addr)
{
	DMA1_Stream7->M1AR = mem1_addr;
}
// DMA1 STREAM0 FCR
void STM32FXXXDMA1_stream0_fcr_feie(uint8_t state)
{
	set_reg_block(&DMA1_Stream0->FCR, 1, 7, state);
}
void STM32FXXXDMA1_stream0_fcr_fs(uint8_t value)
{
	set_reg_block(&DMA1_Stream0->FCR, 3, 3, value);
}
void STM32FXXXDMA1_stream0_fcr_dmdis(uint8_t state)
{
	set_reg_block(&DMA1_Stream0->FCR, 1, 2, state);
}
void STM32FXXXDMA1_stream0_fcr_fth(uint8_t value)
{
	set_reg_block(&DMA1_Stream0->FCR, 2, 0, value);
}
/*** Inic DMA1 STREAM0 FCR ***/
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma1_stream0_fcr_inic(void)
{

	// FCR
	stm32fxxx_dma1_stream0_fcr.feie = STM32FXXXDMA1_stream0_fcr_feie;
	stm32fxxx_dma1_stream0_fcr.fs = STM32FXXXDMA1_stream0_fcr_fs;
	stm32fxxx_dma1_stream0_fcr.dmdis = STM32FXXXDMA1_stream0_fcr_dmdis;
	stm32fxxx_dma1_stream0_fcr.fth = STM32FXXXDMA1_stream0_fcr_fth;
	return &stm32fxxx_dma1_stream0_fcr;
}
// DMA1 STREAM1 FCR
void STM32FXXXDMA1_stream1_fcr_feie(uint8_t state)
{
	set_reg_block(&DMA1_Stream1->FCR, 1, 7, state);
}
void STM32FXXXDMA1_stream1_fcr_fs(uint8_t value)
{
	set_reg_block(&DMA1_Stream1->FCR, 3, 3, value);
}
void STM32FXXXDMA1_stream1_fcr_dmdis(uint8_t state)
{
	set_reg_block(&DMA1_Stream1->FCR, 1, 2, state);
}
void STM32FXXXDMA1_stream1_fcr_fth(uint8_t value)
{
	set_reg_block(&DMA1_Stream1->FCR, 2, 0, value);
}
/*** Inic DMA1 STREAM1 FCR ***/
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma1_stream1_fcr_inic(void)
{

	// FCR
	stm32fxxx_dma1_stream1_fcr.feie = STM32FXXXDMA1_stream1_fcr_feie;
	stm32fxxx_dma1_stream1_fcr.fs = STM32FXXXDMA1_stream1_fcr_fs;
	stm32fxxx_dma1_stream1_fcr.dmdis = STM32FXXXDMA1_stream1_fcr_dmdis;
	stm32fxxx_dma1_stream1_fcr.fth = STM32FXXXDMA1_stream1_fcr_fth;
	return &stm32fxxx_dma1_stream1_fcr;
}
// DMA1 STREAM2 FCR
void STM32FXXXDMA1_stream2_fcr_feie(uint8_t state)
{
	set_reg_block(&DMA1_Stream2->FCR, 1, 7, state);
}
void STM32FXXXDMA1_stream2_fcr_fs(uint8_t value)
{
	set_reg_block(&DMA1_Stream2->FCR, 3, 3, value);
}
void STM32FXXXDMA1_stream2_fcr_dmdis(uint8_t state)
{
	set_reg_block(&DMA1_Stream2->FCR, 1, 2, state);
}
void STM32FXXXDMA1_stream2_fcr_fth(uint8_t value)
{
	set_reg_block(&DMA1_Stream2->FCR, 2, 0, value);
}
/*** Inic DMA1 STREAM2 FCR ***/
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma1_stream2_fcr_inic(void)
{

	// FCR
	stm32fxxx_dma1_stream2_fcr.feie = STM32FXXXDMA1_stream2_fcr_feie;
	stm32fxxx_dma1_stream2_fcr.fs = STM32FXXXDMA1_stream2_fcr_fs;
	stm32fxxx_dma1_stream2_fcr.dmdis = STM32FXXXDMA1_stream2_fcr_dmdis;
	stm32fxxx_dma1_stream2_fcr.fth = STM32FXXXDMA1_stream2_fcr_fth;
	return &stm32fxxx_dma1_stream2_fcr;
}
// DMA1 STREAM3 FCR
void STM32FXXXDMA1_stream3_fcr_feie(uint8_t state)
{
	set_reg_block(&DMA1_Stream3->FCR, 1, 7, state);
}
void STM32FXXXDMA1_stream3_fcr_fs(uint8_t value)
{
	set_reg_block(&DMA1_Stream3->FCR, 3, 3, value);
}
void STM32FXXXDMA1_stream3_fcr_dmdis(uint8_t state)
{
	set_reg_block(&DMA1_Stream3->FCR, 1, 2, state);
}
void STM32FXXXDMA1_stream3_fcr_fth(uint8_t value)
{
	set_reg_block(&DMA1_Stream3->FCR, 2, 0, value);
}
/*** Inic DMA1 STREAM3 FCR ***/
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma1_stream3_fcr_inic(void)
{

	// FCR
	stm32fxxx_dma1_stream3_fcr.feie = STM32FXXXDMA1_stream3_fcr_feie;
	stm32fxxx_dma1_stream3_fcr.fs = STM32FXXXDMA1_stream3_fcr_fs;
	stm32fxxx_dma1_stream3_fcr.dmdis = STM32FXXXDMA1_stream3_fcr_dmdis;
	stm32fxxx_dma1_stream3_fcr.fth = STM32FXXXDMA1_stream3_fcr_fth;
	return &stm32fxxx_dma1_stream3_fcr;
}
// DMA1 STREAM4 FCR
void STM32FXXXDMA1_stream4_fcr_feie(uint8_t state)
{
	set_reg_block(&DMA1_Stream4->FCR, 1, 7, state);
}
void STM32FXXXDMA1_stream4_fcr_fs(uint8_t value)
{
	set_reg_block(&DMA1_Stream4->FCR, 3, 3, value);
}
void STM32FXXXDMA1_stream4_fcr_dmdis(uint8_t state)
{
	set_reg_block(&DMA1_Stream4->FCR, 1, 2, state);
}
void STM32FXXXDMA1_stream4_fcr_fth(uint8_t value)
{
	set_reg_block(&DMA1_Stream4->FCR, 2, 0, value);
}
/*** Inic DMA1 STREAM4 FCR ***/
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma1_stream4_fcr_inic(void)
{

	// FCR
	stm32fxxx_dma1_stream4_fcr.feie = STM32FXXXDMA1_stream4_fcr_feie;
	stm32fxxx_dma1_stream4_fcr.fs = STM32FXXXDMA1_stream4_fcr_fs;
	stm32fxxx_dma1_stream4_fcr.dmdis = STM32FXXXDMA1_stream4_fcr_dmdis;
	stm32fxxx_dma1_stream4_fcr.fth = STM32FXXXDMA1_stream4_fcr_fth;
	return &stm32fxxx_dma1_stream4_fcr;
}
// DMA1 STREAM5 FCR
void STM32FXXXDMA1_stream5_fcr_feie(uint8_t state)
{
	set_reg_block(&DMA1_Stream5->FCR, 1, 7, state);
}
void STM32FXXXDMA1_stream5_fcr_fs(uint8_t value)
{
	set_reg_block(&DMA1_Stream5->FCR, 3, 3, value);
}
void STM32FXXXDMA1_stream5_fcr_dmdis(uint8_t state)
{
	set_reg_block(&DMA1_Stream5->FCR, 1, 2, state);
}
void STM32FXXXDMA1_stream5_fcr_fth(uint8_t value)
{
	set_reg_block(&DMA1_Stream5->FCR, 2, 0, value);
}
/*** Inic DMA1 STREAM5 FCR ***/
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma1_stream5_fcr_inic(void)
{

	// FCR
	stm32fxxx_dma1_stream5_fcr.feie = STM32FXXXDMA1_stream5_fcr_feie;
	stm32fxxx_dma1_stream5_fcr.fs = STM32FXXXDMA1_stream5_fcr_fs;
	stm32fxxx_dma1_stream5_fcr.dmdis = STM32FXXXDMA1_stream5_fcr_dmdis;
	stm32fxxx_dma1_stream5_fcr.fth = STM32FXXXDMA1_stream5_fcr_fth;
	return &stm32fxxx_dma1_stream5_fcr;
}
// DMA1 STREAM6 FCR
void STM32FXXXDMA1_stream6_fcr_feie(uint8_t state)
{
	set_reg_block(&DMA1_Stream6->FCR, 1, 7, state);
}
void STM32FXXXDMA1_stream6_fcr_fs(uint8_t value)
{
	set_reg_block(&DMA1_Stream6->FCR, 3, 3, value);
}
void STM32FXXXDMA1_stream6_fcr_dmdis(uint8_t state)
{
	set_reg_block(&DMA1_Stream6->FCR, 1, 2, state);
}
void STM32FXXXDMA1_stream6_fcr_fth(uint8_t value)
{
	set_reg_block(&DMA1_Stream6->FCR, 2, 0, value);
}
/*** Inic DMA1 STREAM6 FCR ***/
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma1_stream6_fcr_inic(void)
{

	// FCR
	stm32fxxx_dma1_stream6_fcr.feie = STM32FXXXDMA1_stream6_fcr_feie;
	stm32fxxx_dma1_stream6_fcr.fs = STM32FXXXDMA1_stream6_fcr_fs;
	stm32fxxx_dma1_stream6_fcr.dmdis = STM32FXXXDMA1_stream6_fcr_dmdis;
	stm32fxxx_dma1_stream6_fcr.fth = STM32FXXXDMA1_stream6_fcr_fth;
	return &stm32fxxx_dma1_stream6_fcr;
}
// DMA1 STREAM0 FCR
void STM32FXXXDMA1_stream7_fcr_feie(uint8_t state)
{
	set_reg_block(&DMA1_Stream7->FCR, 1, 7, state);
}
void STM32FXXXDMA1_stream7_fcr_fs(uint8_t value)
{
	set_reg_block(&DMA1_Stream7->FCR, 3, 3, value);
}
void STM32FXXXDMA1_stream7_fcr_dmdis(uint8_t state)
{
	set_reg_block(&DMA1_Stream7->FCR, 1, 2, state);
}
void STM32FXXXDMA1_stream7_fcr_fth(uint8_t value)
{
	set_reg_block(&DMA1_Stream7->FCR, 2, 0, value);
}
/*** Inic DMA1 STREAM7 FCR ***/
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma1_stream7_fcr_inic(void)
{

	// FCR
	stm32fxxx_dma1_stream7_fcr.feie = STM32FXXXDMA1_stream7_fcr_feie;
	stm32fxxx_dma1_stream7_fcr.fs = STM32FXXXDMA1_stream7_fcr_fs;
	stm32fxxx_dma1_stream7_fcr.dmdis = STM32FXXXDMA1_stream7_fcr_dmdis;
	stm32fxxx_dma1_stream7_fcr.fth = STM32FXXXDMA1_stream7_fcr_fth;
	return &stm32fxxx_dma1_stream7_fcr;
}
/*** FUNC ***/
void dma1_circ_cfg(volatile long unsigned int* p_addr, volatile long unsigned int* m_addr, uint8_t stream_n, uint8_t channel_n, uint16_t quant_d, uint8_t p_size, uint8_t m_size, uint8_t priority, uint8_t dir)
{
	set_reg_block(&RCC->AHB1ENR, 1, 22, 1);
	// Filter to Default
	if(stream_n > 7){ stream_n = 0;}
	if(channel_n > 7){ channel_n = 0;}
	if(quant_d > 65535){ quant_d = 1;}
	if(p_size > 2){ p_size = 0;}
	if(m_size > 2){ m_size = 0;}
	if(priority > 3){ priority = 0;}
	if( p_addr && m_addr ){
		/*** Verify Ready for Parameter ***/
		set_reg_block(&(DMA1_Stream0 + stream_n)->CR, 1, 0, 0);
		for(time_out = 200; get_reg_block((DMA1_Stream0 + stream_n)->CR, 1, 0) && time_out; time_out--);
		/*** Parameter Configure ***/
		(DMA1_Stream0 + stream_n)->PAR = (volatile long unsigned int) p_addr;
		(DMA1_Stream0 + stream_n)->M0AR = (volatile long unsigned int) m_addr;
		set_reg_block(&(DMA1_Stream0 + stream_n)->CR, 1, 5, 0); // 0 -> dma, 1 -> peri
		set_reg_block(&(DMA1_Stream0 + stream_n)->CR, 3, 25, channel_n); // channel
		(DMA1_Stream0 + stream_n)->NDTR = quant_d; //
		set_reg_block(&(DMA1_Stream0 + stream_n)->CR, 2, 13, m_size); // msize 2 -> 32bit
		set_reg_block(&(DMA1_Stream0 + stream_n)->CR, 2, 11, p_size); // psize 1 -> 16bit
		set_reg_block(&(DMA1_Stream0 + stream_n)->CR, 2, 16, priority); // priority
		if(dir){
			set_reg_block(&(DMA1_Stream0 + stream_n)->CR, 2, 6, 1); // DIR
			set_reg_block(&(DMA1_Stream0 + stream_n)->CR, 1, 9, 1); // PINC
			set_reg_block(&(DMA1_Stream0 + stream_n)->CR, 1, 10, 0); // MINC
		}else{
			set_reg_block(&(DMA1_Stream0 + stream_n)->CR, 2, 6, 0); // DIR
			set_reg_block(&(DMA1_Stream0 + stream_n)->CR, 1, 9, 0); // PINC
			set_reg_block(&(DMA1_Stream0 + stream_n)->CR, 1, 10, 1); // MINC
		}
		set_reg_block(&(DMA1_Stream0 + stream_n)->CR, 1, 8, 1); // CIRC
		set_reg_block(&(DMA1_Stream0 + stream_n)->CR, 1, 0, 1); // ENABLE
	}
}
/*** Inic FUNC ***/
STM32FXXXDMA_func* stm32fxxx_dma1_func_inic(void)
{

	stm32fxxx_dma1_func.circ_cfg = dma1_circ_cfg;
	return &stm32fxxx_dma1_func;
}
/****************************************************/
/**** DMA1 INIC Procedure & Function Definition *****/
/****************************************************/
void dma1_enable(void)
{
	STM32FXXXDma1Clock(ON);
	stm32fxxx_dma1.instance = DMA1;
	/*** DMA1 Bit Mapping Link ***/
	stm32fxxx_dma1.sr = stm32fxxx_dma1_sr_inic();

	stm32fxxx_dma1.stream[0]->instance = DMA1_Stream0;
	stm32fxxx_dma1.stream[0]->cr = stm32fxxx_dma1_stream0_cr_inic();
	stm32fxxx_dma1.stream[0]->fcr = stm32fxxx_dma1_stream0_fcr_inic();
	stm32fxxx_dma1.stream[0]->ndt = stm32fxxx_dma1_stream0_ndt;
	stm32fxxx_dma1.stream[0]->par = stm32fxxx_dma1_stream0_par;
	stm32fxxx_dma1.stream[0]->m0a = stm32fxxx_dma1_stream0_m0a;
	stm32fxxx_dma1.stream[0]->m1a = stm32fxxx_dma1_stream0_m1a;

	stm32fxxx_dma1.stream[1]->instance = DMA1_Stream1;
	stm32fxxx_dma1.stream[1]->cr = stm32fxxx_dma1_stream1_cr_inic();
	stm32fxxx_dma1.stream[1]->fcr = stm32fxxx_dma1_stream1_fcr_inic();
	stm32fxxx_dma1.stream[1]->ndt = stm32fxxx_dma1_stream1_ndt;
	stm32fxxx_dma1.stream[1]->par = stm32fxxx_dma1_stream1_par;
	stm32fxxx_dma1.stream[1]->m0a = stm32fxxx_dma1_stream1_m0a;
	stm32fxxx_dma1.stream[1]->m1a = stm32fxxx_dma1_stream1_m1a;

	stm32fxxx_dma1.stream[2]->instance = DMA1_Stream2;
	stm32fxxx_dma1.stream[2]->cr = stm32fxxx_dma1_stream2_cr_inic();
	stm32fxxx_dma1.stream[2]->fcr = stm32fxxx_dma1_stream2_fcr_inic();
	stm32fxxx_dma1.stream[2]->ndt = stm32fxxx_dma1_stream2_ndt;
	stm32fxxx_dma1.stream[2]->par = stm32fxxx_dma1_stream2_par;
	stm32fxxx_dma1.stream[2]->m0a = stm32fxxx_dma1_stream2_m0a;
	stm32fxxx_dma1.stream[2]->m1a = stm32fxxx_dma1_stream2_m1a;

	stm32fxxx_dma1.stream[3]->instance = DMA1_Stream3;
	stm32fxxx_dma1.stream[3]->cr = stm32fxxx_dma1_stream3_cr_inic();
	stm32fxxx_dma1.stream[3]->fcr = stm32fxxx_dma1_stream3_fcr_inic();
	stm32fxxx_dma1.stream[3]->ndt = stm32fxxx_dma1_stream3_ndt;
	stm32fxxx_dma1.stream[3]->par = stm32fxxx_dma1_stream3_par;
	stm32fxxx_dma1.stream[3]->m0a = stm32fxxx_dma1_stream3_m0a;
	stm32fxxx_dma1.stream[3]->m1a = stm32fxxx_dma1_stream3_m1a;

	stm32fxxx_dma1.stream[4]->instance = DMA1_Stream4;
	stm32fxxx_dma1.stream[4]->cr = stm32fxxx_dma1_stream4_cr_inic();
	stm32fxxx_dma1.stream[4]->fcr = stm32fxxx_dma1_stream4_fcr_inic();
	stm32fxxx_dma1.stream[4]->ndt = stm32fxxx_dma1_stream4_ndt;
	stm32fxxx_dma1.stream[4]->par = stm32fxxx_dma1_stream4_par;
	stm32fxxx_dma1.stream[4]->m0a = stm32fxxx_dma1_stream4_m0a;
	stm32fxxx_dma1.stream[4]->m1a = stm32fxxx_dma1_stream4_m1a;

	stm32fxxx_dma1.stream[5]->instance = DMA1_Stream5;
	stm32fxxx_dma1.stream[5]->cr = stm32fxxx_dma1_stream5_cr_inic();
	stm32fxxx_dma1.stream[5]->fcr = stm32fxxx_dma1_stream5_fcr_inic();
	stm32fxxx_dma1.stream[5]->ndt = stm32fxxx_dma1_stream5_ndt;
	stm32fxxx_dma1.stream[5]->par = stm32fxxx_dma1_stream5_par;
	stm32fxxx_dma1.stream[5]->m0a = stm32fxxx_dma1_stream5_m0a;
	stm32fxxx_dma1.stream[5]->m1a = stm32fxxx_dma1_stream5_m1a;

	stm32fxxx_dma1.stream[6]->instance = DMA1_Stream6;
	stm32fxxx_dma1.stream[6]->cr = stm32fxxx_dma1_stream6_cr_inic();
	stm32fxxx_dma1.stream[6]->fcr = stm32fxxx_dma1_stream6_fcr_inic();
	stm32fxxx_dma1.stream[6]->ndt = stm32fxxx_dma1_stream6_ndt;
	stm32fxxx_dma1.stream[6]->par = stm32fxxx_dma1_stream6_par;
	stm32fxxx_dma1.stream[6]->m0a = stm32fxxx_dma1_stream6_m0a;
	stm32fxxx_dma1.stream[6]->m1a = stm32fxxx_dma1_stream6_m1a;

	stm32fxxx_dma1.stream[7]->instance = DMA1_Stream7;
	stm32fxxx_dma1.stream[7]->cr = stm32fxxx_dma1_stream7_cr_inic();
	stm32fxxx_dma1.stream[7]->fcr = stm32fxxx_dma1_stream7_fcr_inic();
	stm32fxxx_dma1.stream[7]->ndt = stm32fxxx_dma1_stream7_ndt;
	stm32fxxx_dma1.stream[7]->par = stm32fxxx_dma1_stream7_par;
	stm32fxxx_dma1.stream[7]->m0a = stm32fxxx_dma1_stream7_m0a;
	stm32fxxx_dma1.stream[7]->m1a = stm32fxxx_dma1_stream7_m1a;
	/*** Other ***/
	stm32fxxx_dma1.func = stm32fxxx_dma1_func_inic();
	stm32fxxx_dma1.clock = STM32FXXXDma1Clock;
	//return &stm32fxxx_dma1;
}

STM32FXXX_DMA1* dma1(void){ return &stm32fxxx_dma1; }

/********************************************/
/************* DMA2 Bit Mapping *************/
/********************************************/
// SR
uint8_t STM32FXXXDMA2_sr_tcif(uint8_t stream_n)
{
	uint8_t value = 0;
	switch(stream_n){
		case 0:
			value = get_reg_block(DMA2->LISR, 1, 5);
		break;
		case 1:
			value = get_reg_block(DMA2->LISR, 1, 11);
		break;
		case 2:
			value = get_reg_block(DMA2->LISR, 1, 21);
		break;
		case 3:
			value = get_reg_block(DMA2->LISR, 1, 27);
		break;
		case 4:
			value = get_reg_block(DMA2->HISR, 1, 5);
		break;
		case 5:
			value = get_reg_block(DMA2->HISR, 1, 11);
		break;
		case 6:
			value = get_reg_block(DMA2->HISR, 1, 21);
		break;
		case 7:
			value = get_reg_block(DMA2->HISR, 1, 27);
		break;
	default: break;
	}
	return value;
}
void STM32FXXXDMA2_sr_clear_tcif(uint8_t stream_n)
{
	switch(stream_n){
		case 0:
			set_reg_block(&DMA2->LIFCR, 1, 5, 1);
		break;
		case 1:
			set_reg_block(&DMA2->LIFCR, 1, 11, 1);
		break;
		case 2:
			set_reg_block(&DMA2->LIFCR, 1, 21, 1);
		break;
		case 3:
			set_reg_block(&DMA2->LIFCR, 1, 27, 1);
		break;
		case 4:
			set_reg_block(&DMA2->HIFCR, 1, 5, 1);
		break;
		case 5:
			set_reg_block(&DMA2->HIFCR, 1, 11, 1);
		break;
		case 6:
			set_reg_block(&DMA2->HIFCR, 1, 21, 1);
		break;
		case 7:
			set_reg_block(&DMA2->HIFCR, 1, 27, 1);
		break;
		default: break;
	}
}
uint8_t STM32FXXXDMA2_sr_htif(uint8_t stream_n)
{
	uint8_t value = 0;
	switch(stream_n){
		case 0:
			value = get_reg_block(DMA2->LISR, 1, 4);
		break;
		case 1:
			value = get_reg_block(DMA2->LISR, 1, 10);
		break;
		case 2:
			value = get_reg_block(DMA2->LISR, 1, 20);
		break;
		case 3:
			value = get_reg_block(DMA2->LISR, 1, 26);
		break;
		case 4:
			value = get_reg_block(DMA2->HISR, 1, 4);
		break;
		case 5:
			value = get_reg_block(DMA2->HISR, 1, 10);
		break;
		case 6:
			value = get_reg_block(DMA2->HISR, 1, 20);
		break;
		case 7:
			value = get_reg_block(DMA2->HISR, 1, 26);
		break;
	default: break;
	}
	return value;
}
void STM32FXXXDMA2_sr_clear_htif(uint8_t stream_n)
{
	switch(stream_n){
		case 0:
			set_reg_block(&DMA2->LIFCR, 1, 4, 1);
		break;
		case 1:
			set_reg_block(&DMA2->LIFCR, 1, 10, 1);
		break;
		case 2:
			set_reg_block(&DMA2->LIFCR, 1, 20, 1);
		break;
		case 3:
			set_reg_block(&DMA2->LIFCR, 1, 26, 1);
		break;
		case 4:
			set_reg_block(&DMA2->HIFCR, 1, 4, 1);
		break;
		case 5:
			set_reg_block(&DMA2->HIFCR, 1, 10, 1);
		break;
		case 6:
			set_reg_block(&DMA2->HIFCR, 1, 20, 1);
		break;
		case 7:
			set_reg_block(&DMA2->HIFCR, 1, 26, 1);
		break;
		default: break;
	}
}
uint8_t STM32FXXXDMA2_sr_teif(uint8_t stream_n)
{
	uint8_t value = 0;
	switch(stream_n){
		case 0:
			value = get_reg_block(DMA2->LISR, 1, 3);
		break;
		case 1:
			value = get_reg_block(DMA2->LISR, 1, 9);
		break;
		case 2:
			value = get_reg_block(DMA2->LISR, 1, 19);
		break;
		case 3:
			value = get_reg_block(DMA2->LISR, 1, 25);
		break;
		case 4:
			value = get_reg_block(DMA2->HISR, 1, 3);
		break;
		case 5:
			value = get_reg_block(DMA2->HISR, 1, 9);
		break;
		case 6:
			value = get_reg_block(DMA2->HISR, 1, 19);
		break;
		case 7:
			value = get_reg_block(DMA2->HISR, 1, 25);
		break;
	default: break;
	}
	return value;
}
void STM32FXXXDMA2_sr_clear_teif(uint8_t stream_n)
{
	switch(stream_n){
		case 0:
			set_reg_block(&DMA2->LIFCR, 1, 3, 1);
		break;
		case 1:
			set_reg_block(&DMA2->LIFCR, 1, 9, 1);
		break;
		case 2:
			set_reg_block(&DMA2->LIFCR, 1, 19, 1);
		break;
		case 3:
			set_reg_block(&DMA2->LIFCR, 1, 25, 1);
		break;
		case 4:
			set_reg_block(&DMA2->HIFCR, 1, 3, 1);
		break;
		case 5:
			set_reg_block(&DMA2->HIFCR, 1, 9, 1);
		break;
		case 6:
			set_reg_block(&DMA2->HIFCR, 1, 19, 1);
		break;
		case 7:
			set_reg_block(&DMA2->HIFCR, 1, 25, 1);
		break;
		default: break;
	}
}
uint8_t STM32FXXXDMA2_sr_dmeif(uint8_t stream_n)
{
	uint8_t value = 0;
	switch(stream_n){
		case 0:
			value = get_reg_block(DMA2->LISR, 1, 2);
		break;
		case 1:
			value = get_reg_block(DMA2->LISR, 1, 8);
		break;
		case 2:
			value = get_reg_block(DMA2->LISR, 1, 18);
		break;
		case 3:
			value = get_reg_block(DMA2->LISR, 1, 24);
		break;
		case 4:
			value = get_reg_block(DMA2->HISR, 1, 2);
		break;
		case 5:
			value = get_reg_block(DMA2->HISR, 1, 8);
		break;
		case 6:
			value = get_reg_block(DMA2->HISR, 1, 18);
		break;
		case 7:
			value = get_reg_block(DMA2->HISR, 1, 24);
		break;
	default: break;
	}
	return value;
}
void STM32FXXXDMA2_sr_clear_dmeif(uint8_t stream_n)
{
	switch(stream_n){
		case 0:
			set_reg_block(&DMA2->LIFCR, 1, 2, 1);
		break;
		case 1:
			set_reg_block(&DMA2->LIFCR, 1, 8, 1);
		break;
		case 2:
			set_reg_block(&DMA2->LIFCR, 1, 18, 1);
		break;
		case 3:
			set_reg_block(&DMA2->LIFCR, 1, 24, 1);
		break;
		case 4:
			set_reg_block(&DMA2->HIFCR, 1, 2, 1);
		break;
		case 5:
			set_reg_block(&DMA2->HIFCR, 1, 8, 1);
		break;
		case 6:
			set_reg_block(&DMA2->HIFCR, 1, 18, 1);
		break;
		case 7:
			set_reg_block(&DMA2->HIFCR, 1, 24, 1);
		break;
		default: break;
	}
}
uint8_t STM32FXXXDMA2_sr_feif(uint8_t stream_n)
{
	uint8_t value = 0;
	switch(stream_n){
		case 0:
			value = get_reg_block(DMA2->LISR, 1, 0);
		break;
		case 1:
			value = get_reg_block(DMA2->LISR, 1, 6);
		break;
		case 2:
			value = get_reg_block(DMA2->LISR, 1, 16);
		break;
		case 3:
			value = get_reg_block(DMA2->LISR, 1, 22);
		break;
		case 4:
			value = get_reg_block(DMA2->HISR, 1, 0);
		break;
		case 5:
			value = get_reg_block(DMA2->HISR, 1, 6);
		break;
		case 6:
			value = get_reg_block(DMA2->HISR, 1, 16);
		break;
		case 7:
			value = get_reg_block(DMA2->HISR, 1, 22);
		break;
	default: break;
	}
	return value;
}
void STM32FXXXDMA2_sr_clear_feif(uint8_t stream_n)
{
	switch(stream_n){
		case 0:
			set_reg_block(&DMA2->LIFCR, 1, 0, 1);
		break;
		case 1:
			set_reg_block(&DMA2->LIFCR, 1, 6, 1);
		break;
		case 2:
			set_reg_block(&DMA2->LIFCR, 1, 16, 1);
		break;
		case 3:
			set_reg_block(&DMA2->LIFCR, 1, 22, 1);
		break;
		case 4:
			set_reg_block(&DMA2->HIFCR, 1, 0, 1);
		break;
		case 5:
			set_reg_block(&DMA2->HIFCR, 1, 6, 1);
		break;
		case 6:
			set_reg_block(&DMA2->HIFCR, 1, 16, 1);
		break;
		case 7:
			set_reg_block(&DMA2->HIFCR, 1, 22, 1);
		break;
		default: break;
	}
}
/*** Inic SR ***/
STM32FXXXDMA_sr* stm32fxxx_dma2_sr_inic(void)
{

	// SR
	stm32fxxx_dma2_sr.tcif = STM32FXXXDMA2_sr_tcif;
	stm32fxxx_dma2_sr.clear_tcif = STM32FXXXDMA2_sr_clear_tcif;
	stm32fxxx_dma2_sr.htif = STM32FXXXDMA2_sr_htif;
	stm32fxxx_dma2_sr.clear_htif = STM32FXXXDMA2_sr_clear_htif;
	stm32fxxx_dma2_sr.teif = STM32FXXXDMA2_sr_teif;
	stm32fxxx_dma2_sr.clear_teif = STM32FXXXDMA2_sr_clear_teif;
	stm32fxxx_dma2_sr.dmeif = STM32FXXXDMA2_sr_dmeif;
	stm32fxxx_dma2_sr.clear_dmeif = STM32FXXXDMA2_sr_clear_dmeif;
	stm32fxxx_dma2_sr.feif = STM32FXXXDMA2_sr_feif;
	stm32fxxx_dma2_sr.clear_feif = STM32FXXXDMA2_sr_clear_feif;
	return &stm32fxxx_dma2_sr;
}
// DMA2 STREAM0 CR
void STM32FXXXDMA2_stream0_cr_chsel(uint8_t value)
{
	set_reg_block(&DMA2_Stream0->CR, 3, 25, value);
}
void STM32FXXXDMA2_stream0_cr_mburst(uint8_t value)
{
	set_reg_block(&DMA2_Stream0->CR, 2, 23, value);
}
void STM32FXXXDMA2_stream0_cr_pburst(uint8_t value)
{
	set_reg_block(&DMA2_Stream0->CR, 2, 21, value);
}
void STM32FXXXDMA2_stream0_cr_ct(uint8_t state)
{
	set_reg_block(&DMA2_Stream0->CR, 1, 19, state);
}
void STM32FXXXDMA2_stream0_cr_dbm(uint8_t state)
{
	set_reg_block(&DMA2_Stream0->CR, 1, 18, state);
}
void STM32FXXXDMA2_stream0_cr_pl(uint8_t value)
{
	set_reg_block(&DMA2_Stream0->CR, 2, 16, value);
}
void STM32FXXXDMA2_stream0_cr_pincos(uint8_t state)
{
	set_reg_block(&DMA2_Stream0->CR, 1, 15, state);
}
void STM32FXXXDMA2_stream0_cr_msize(uint8_t value)
{
	set_reg_block(&DMA2_Stream0->CR, 2, 13, value);
}
void STM32FXXXDMA2_stream0_cr_psize(uint8_t value)
{
	set_reg_block(&DMA2_Stream0->CR, 2, 11, value);
}
void STM32FXXXDMA2_stream0_cr_minc(uint8_t state)
{
	set_reg_block(&DMA2_Stream0->CR, 1, 10, state);
}
void STM32FXXXDMA2_stream0_cr_pinc(uint8_t state)
{
	set_reg_block(&DMA2_Stream0->CR, 1, 9, state);
}
void STM32FXXXDMA2_stream0_cr_circ(uint8_t state)
{
	set_reg_block(&DMA2_Stream0->CR, 1, 8, state);
}
void STM32FXXXDMA2_stream0_cr_dir(uint8_t value)
{
	set_reg_block(&DMA2_Stream0->CR, 2, 7, value);
}
void STM32FXXXDMA2_stream0_cr_pfctrl(uint8_t state)
{
	set_reg_block(&DMA2_Stream0->CR, 1, 5, state);
}
void STM32FXXXDMA2_stream0_cr_tcie(uint8_t state)
{
	set_reg_block(&DMA2_Stream0->CR, 1, 4, state);
}
void STM32FXXXDMA2_stream0_cr_htie(uint8_t state)
{
	set_reg_block(&DMA2_Stream0->CR, 1, 3, state);
}
void STM32FXXXDMA2_stream0_cr_teie(uint8_t state)
{
	set_reg_block(&DMA2_Stream0->CR, 1, 2, state);
}
void STM32FXXXDMA2_stream0_cr_dmeie(uint8_t state)
{
	set_reg_block(&DMA2_Stream0->CR, 1, 1, state);
}
void STM32FXXXDMA2_stream0_cr_en(uint8_t state)
{
	set_reg_block(&DMA2_Stream0->CR, 1, 0, state);
}
/*** Inic DMA2 STREAM0 CR ***/
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma2_stream0_cr_inic(void)
{

	// CR
	stm32fxxx_dma2_stream0_cr.chsel = STM32FXXXDMA2_stream0_cr_chsel;
	stm32fxxx_dma2_stream0_cr.mburst = STM32FXXXDMA2_stream0_cr_mburst;
	stm32fxxx_dma2_stream0_cr.pburst = STM32FXXXDMA2_stream0_cr_pburst;
	stm32fxxx_dma2_stream0_cr.ct = STM32FXXXDMA2_stream0_cr_ct;
	stm32fxxx_dma2_stream0_cr.dbm = STM32FXXXDMA2_stream0_cr_dbm;
	stm32fxxx_dma2_stream0_cr.pl = STM32FXXXDMA2_stream0_cr_pl;
	stm32fxxx_dma2_stream0_cr.pincos = STM32FXXXDMA2_stream0_cr_pincos;
	stm32fxxx_dma2_stream0_cr.msize = STM32FXXXDMA2_stream0_cr_msize;
	stm32fxxx_dma2_stream0_cr.psize = STM32FXXXDMA2_stream0_cr_psize;
	stm32fxxx_dma2_stream0_cr.minc = STM32FXXXDMA2_stream0_cr_minc;
	stm32fxxx_dma2_stream0_cr.pinc = STM32FXXXDMA2_stream0_cr_pinc;
	stm32fxxx_dma2_stream0_cr.circ = STM32FXXXDMA2_stream0_cr_circ;
	stm32fxxx_dma2_stream0_cr.dir = STM32FXXXDMA2_stream0_cr_dir;
	stm32fxxx_dma2_stream0_cr.pfctrl = STM32FXXXDMA2_stream0_cr_pfctrl;
	stm32fxxx_dma2_stream0_cr.tcie = STM32FXXXDMA2_stream0_cr_tcie;
	stm32fxxx_dma2_stream0_cr.htie = STM32FXXXDMA2_stream0_cr_htie;
	stm32fxxx_dma2_stream0_cr.teie = STM32FXXXDMA2_stream0_cr_teie;
	stm32fxxx_dma2_stream0_cr.dmeie = STM32FXXXDMA2_stream0_cr_dmeie;
	stm32fxxx_dma2_stream0_cr.en = STM32FXXXDMA2_stream0_cr_en;
	return &stm32fxxx_dma2_stream0_cr;
}
/*** Inic DMA2 STREAM0 Function ***/
void stm32fxxx_dma2_stream0_ndt(uint16_t value)
{
	DMA2_Stream0->NDTR = value;
}
void stm32fxxx_dma2_stream0_par(volatile long unsigned int periferal_addr)
{
	DMA2_Stream0->PAR = periferal_addr;
}
void stm32fxxx_dma2_stream0_m0a(volatile long unsigned int mem0_addr)
{
	DMA2_Stream0->M0AR = mem0_addr;
}
void stm32fxxx_dma2_stream0_m1a(volatile long unsigned int mem1_addr)
{
	DMA2_Stream0->M1AR = mem1_addr;
}
// DMA2 STREAM1 CR
void STM32FXXXDMA2_stream1_cr_chsel(uint8_t value)
{
	set_reg_block(&DMA2_Stream1->CR, 3, 25, value);
}
void STM32FXXXDMA2_stream1_cr_mburst(uint8_t value)
{
	set_reg_block(&DMA2_Stream1->CR, 2, 23, value);
}
void STM32FXXXDMA2_stream1_cr_pburst(uint8_t value)
{
	set_reg_block(&DMA2_Stream1->CR, 2, 21, value);
}
void STM32FXXXDMA2_stream1_cr_ct(uint8_t state)
{
	set_reg_block(&DMA2_Stream1->CR, 1, 19, state);
}
void STM32FXXXDMA2_stream1_cr_dbm(uint8_t state)
{
	set_reg_block(&DMA2_Stream1->CR, 1, 18, state);
}
void STM32FXXXDMA2_stream1_cr_pl(uint8_t value)
{
	set_reg_block(&DMA2_Stream1->CR, 2, 16, value);
}
void STM32FXXXDMA2_stream1_cr_pincos(uint8_t state)
{
	set_reg_block(&DMA2_Stream1->CR, 1, 15, state);
}
void STM32FXXXDMA2_stream1_cr_msize(uint8_t value)
{
	set_reg_block(&DMA2_Stream1->CR, 2, 13, value);
}
void STM32FXXXDMA2_stream1_cr_psize(uint8_t value)
{
	set_reg_block(&DMA2_Stream1->CR, 2, 11, value);
}
void STM32FXXXDMA2_stream1_cr_minc(uint8_t state)
{
	set_reg_block(&DMA2_Stream1->CR, 1, 10, state);
}
void STM32FXXXDMA2_stream1_cr_pinc(uint8_t state)
{
	set_reg_block(&DMA2_Stream1->CR, 1, 9, state);
}
void STM32FXXXDMA2_stream1_cr_circ(uint8_t state)
{
	set_reg_block(&DMA2_Stream1->CR, 1, 8, state);
}
void STM32FXXXDMA2_stream1_cr_dir(uint8_t value)
{
	set_reg_block(&DMA2_Stream1->CR, 2, 7, value);
}
void STM32FXXXDMA2_stream1_cr_pfctrl(uint8_t state)
{
	set_reg_block(&DMA2_Stream1->CR, 1, 5, state);
}
void STM32FXXXDMA2_stream1_cr_tcie(uint8_t state)
{
	set_reg_block(&DMA2_Stream1->CR, 1, 4, state);
}
void STM32FXXXDMA2_stream1_cr_htie(uint8_t state)
{
	set_reg_block(&DMA2_Stream1->CR, 1, 3, state);
}
void STM32FXXXDMA2_stream1_cr_teie(uint8_t state)
{
	set_reg_block(&DMA2_Stream1->CR, 1, 2, state);
}
void STM32FXXXDMA2_stream1_cr_dmeie(uint8_t state)
{
	set_reg_block(&DMA2_Stream1->CR, 1, 1, state);
}
void STM32FXXXDMA2_stream1_cr_en(uint8_t state)
{
	set_reg_block(&DMA2_Stream1->CR, 1, 0, state);
}
/*** Inic DMA2 STREAM1 CR ***/
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma2_stream1_cr_inic(void)
{

	// CR
	stm32fxxx_dma2_stream1_cr.chsel = STM32FXXXDMA2_stream1_cr_chsel;
	stm32fxxx_dma2_stream1_cr.mburst = STM32FXXXDMA2_stream1_cr_mburst;
	stm32fxxx_dma2_stream1_cr.pburst = STM32FXXXDMA2_stream1_cr_pburst;
	stm32fxxx_dma2_stream1_cr.ct = STM32FXXXDMA2_stream1_cr_ct;
	stm32fxxx_dma2_stream1_cr.dbm = STM32FXXXDMA2_stream1_cr_dbm;
	stm32fxxx_dma2_stream1_cr.pl = STM32FXXXDMA2_stream1_cr_pl;
	stm32fxxx_dma2_stream1_cr.pincos = STM32FXXXDMA2_stream1_cr_pincos;
	stm32fxxx_dma2_stream1_cr.msize = STM32FXXXDMA2_stream1_cr_msize;
	stm32fxxx_dma2_stream1_cr.psize = STM32FXXXDMA2_stream1_cr_psize;
	stm32fxxx_dma2_stream1_cr.minc = STM32FXXXDMA2_stream1_cr_minc;
	stm32fxxx_dma2_stream1_cr.pinc = STM32FXXXDMA2_stream1_cr_pinc;
	stm32fxxx_dma2_stream1_cr.circ = STM32FXXXDMA2_stream1_cr_circ;
	stm32fxxx_dma2_stream1_cr.dir = STM32FXXXDMA2_stream1_cr_dir;
	stm32fxxx_dma2_stream1_cr.pfctrl = STM32FXXXDMA2_stream1_cr_pfctrl;
	stm32fxxx_dma2_stream1_cr.tcie = STM32FXXXDMA2_stream1_cr_tcie;
	stm32fxxx_dma2_stream1_cr.htie = STM32FXXXDMA2_stream1_cr_htie;
	stm32fxxx_dma2_stream1_cr.teie = STM32FXXXDMA2_stream1_cr_teie;
	stm32fxxx_dma2_stream1_cr.dmeie = STM32FXXXDMA2_stream1_cr_dmeie;
	stm32fxxx_dma2_stream1_cr.en = STM32FXXXDMA2_stream1_cr_en;
	return &stm32fxxx_dma2_stream1_cr;
}
/*** Inic DMA2 STREAM1 Function ***/
void stm32fxxx_dma2_stream1_ndt(uint16_t value)
{
	DMA2_Stream1->NDTR = value;
}
void stm32fxxx_dma2_stream1_par(volatile long unsigned int periferal_addr)
{
	DMA2_Stream1->PAR = periferal_addr;
}
void stm32fxxx_dma2_stream1_m0a(volatile long unsigned int mem0_addr)
{
	DMA2_Stream1->M0AR = mem0_addr;
}
void stm32fxxx_dma2_stream1_m1a(volatile long unsigned int mem1_addr)
{
	DMA2_Stream1->M1AR = mem1_addr;
}
// DMA2 STREAM2 CR
void STM32FXXXDMA2_stream2_cr_chsel(uint8_t value)
{
	set_reg_block(&DMA2_Stream2->CR, 3, 25, value);
}
void STM32FXXXDMA2_stream2_cr_mburst(uint8_t value)
{
	set_reg_block(&DMA2_Stream2->CR, 2, 23, value);
}
void STM32FXXXDMA2_stream2_cr_pburst(uint8_t value)
{
	set_reg_block(&DMA2_Stream2->CR, 2, 21, value);
}
void STM32FXXXDMA2_stream2_cr_ct(uint8_t state)
{
	set_reg_block(&DMA2_Stream2->CR, 1, 19, state);
}
void STM32FXXXDMA2_stream2_cr_dbm(uint8_t state)
{
	set_reg_block(&DMA2_Stream2->CR, 1, 18, state);
}
void STM32FXXXDMA2_stream2_cr_pl(uint8_t value)
{
	set_reg_block(&DMA2_Stream2->CR, 2, 16, value);
}
void STM32FXXXDMA2_stream2_cr_pincos(uint8_t state)
{
	set_reg_block(&DMA2_Stream2->CR, 1, 15, state);
}
void STM32FXXXDMA2_stream2_cr_msize(uint8_t value)
{
	set_reg_block(&DMA2_Stream2->CR, 2, 13, value);
}
void STM32FXXXDMA2_stream2_cr_psize(uint8_t value)
{
	set_reg_block(&DMA2_Stream2->CR, 2, 11, value);
}
void STM32FXXXDMA2_stream2_cr_minc(uint8_t state)
{
	set_reg_block(&DMA2_Stream2->CR, 1, 10, state);
}
void STM32FXXXDMA2_stream2_cr_pinc(uint8_t state)
{
	set_reg_block(&DMA2_Stream2->CR, 1, 9, state);
}
void STM32FXXXDMA2_stream2_cr_circ(uint8_t state)
{
	set_reg_block(&DMA2_Stream2->CR, 1, 8, state);
}
void STM32FXXXDMA2_stream2_cr_dir(uint8_t value)
{
	set_reg_block(&DMA2_Stream2->CR, 2, 7, value);
}
void STM32FXXXDMA2_stream2_cr_pfctrl(uint8_t state)
{
	set_reg_block(&DMA2_Stream2->CR, 1, 5, state);
}
void STM32FXXXDMA2_stream2_cr_tcie(uint8_t state)
{
	set_reg_block(&DMA2_Stream2->CR, 1, 4, state);
}
void STM32FXXXDMA2_stream2_cr_htie(uint8_t state)
{
	set_reg_block(&DMA2_Stream2->CR, 1, 3, state);
}
void STM32FXXXDMA2_stream2_cr_teie(uint8_t state)
{
	set_reg_block(&DMA2_Stream2->CR, 1, 2, state);
}
void STM32FXXXDMA2_stream2_cr_dmeie(uint8_t state)
{
	set_reg_block(&DMA2_Stream2->CR, 1, 1, state);
}
void STM32FXXXDMA2_stream2_cr_en(uint8_t state)
{
	set_reg_block(&DMA2_Stream2->CR, 1, 0, state);
}
/*** Inic DMA2 STREAM2 CR ***/
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma2_stream2_cr_inic(void)
{

	// CR
	stm32fxxx_dma2_stream2_cr.chsel = STM32FXXXDMA2_stream2_cr_chsel;
	stm32fxxx_dma2_stream2_cr.mburst = STM32FXXXDMA2_stream2_cr_mburst;
	stm32fxxx_dma2_stream2_cr.pburst = STM32FXXXDMA2_stream2_cr_pburst;
	stm32fxxx_dma2_stream2_cr.ct = STM32FXXXDMA2_stream2_cr_ct;
	stm32fxxx_dma2_stream2_cr.dbm = STM32FXXXDMA2_stream2_cr_dbm;
	stm32fxxx_dma2_stream2_cr.pl = STM32FXXXDMA2_stream2_cr_pl;
	stm32fxxx_dma2_stream2_cr.pincos = STM32FXXXDMA2_stream2_cr_pincos;
	stm32fxxx_dma2_stream2_cr.msize = STM32FXXXDMA2_stream2_cr_msize;
	stm32fxxx_dma2_stream2_cr.psize = STM32FXXXDMA2_stream2_cr_psize;
	stm32fxxx_dma2_stream2_cr.minc = STM32FXXXDMA2_stream2_cr_minc;
	stm32fxxx_dma2_stream2_cr.pinc = STM32FXXXDMA2_stream2_cr_pinc;
	stm32fxxx_dma2_stream2_cr.circ = STM32FXXXDMA2_stream2_cr_circ;
	stm32fxxx_dma2_stream2_cr.dir = STM32FXXXDMA2_stream2_cr_dir;
	stm32fxxx_dma2_stream2_cr.pfctrl = STM32FXXXDMA2_stream2_cr_pfctrl;
	stm32fxxx_dma2_stream2_cr.tcie = STM32FXXXDMA2_stream2_cr_tcie;
	stm32fxxx_dma2_stream2_cr.htie = STM32FXXXDMA2_stream2_cr_htie;
	stm32fxxx_dma2_stream2_cr.teie = STM32FXXXDMA2_stream2_cr_teie;
	stm32fxxx_dma2_stream2_cr.dmeie = STM32FXXXDMA2_stream2_cr_dmeie;
	stm32fxxx_dma2_stream2_cr.en = STM32FXXXDMA2_stream2_cr_en;
	return &stm32fxxx_dma2_stream2_cr;
}
/*** Inic DMA2 STREAM2 Function ***/
void stm32fxxx_dma2_stream2_ndt(uint16_t value)
{
	DMA2_Stream2->NDTR = value;
}
void stm32fxxx_dma2_stream2_par(volatile long unsigned int periferal_addr)
{
	DMA2_Stream2->PAR = periferal_addr;
}
void stm32fxxx_dma2_stream2_m0a(volatile long unsigned int mem0_addr)
{
	DMA2_Stream2->M0AR = mem0_addr;
}
void stm32fxxx_dma2_stream2_m1a(volatile long unsigned int mem1_addr)
{
	DMA2_Stream2->M1AR = mem1_addr;
}
// DMA2 STREAM3 CR
void STM32FXXXDMA2_stream3_cr_chsel(uint8_t value)
{
	set_reg_block(&DMA2_Stream3->CR, 3, 25, value);
}
void STM32FXXXDMA2_stream3_cr_mburst(uint8_t value)
{
	set_reg_block(&DMA2_Stream3->CR, 2, 23, value);
}
void STM32FXXXDMA2_stream3_cr_pburst(uint8_t value)
{
	set_reg_block(&DMA2_Stream3->CR, 2, 21, value);
}
void STM32FXXXDMA2_stream3_cr_ct(uint8_t state)
{
	set_reg_block(&DMA2_Stream3->CR, 1, 19, state);
}
void STM32FXXXDMA2_stream3_cr_dbm(uint8_t state)
{
	set_reg_block(&DMA2_Stream3->CR, 1, 18, state);
}
void STM32FXXXDMA2_stream3_cr_pl(uint8_t value)
{
	set_reg_block(&DMA2_Stream3->CR, 2, 16, value);
}
void STM32FXXXDMA2_stream3_cr_pincos(uint8_t state)
{
	set_reg_block(&DMA2_Stream3->CR, 1, 15, state);
}
void STM32FXXXDMA2_stream3_cr_msize(uint8_t value)
{
	set_reg_block(&DMA2_Stream3->CR, 2, 13, value);
}
void STM32FXXXDMA2_stream3_cr_psize(uint8_t value)
{
	set_reg_block(&DMA2_Stream3->CR, 2, 11, value);
}
void STM32FXXXDMA2_stream3_cr_minc(uint8_t state)
{
	set_reg_block(&DMA2_Stream3->CR, 1, 10, state);
}
void STM32FXXXDMA2_stream3_cr_pinc(uint8_t state)
{
	set_reg_block(&DMA2_Stream3->CR, 1, 9, state);
}
void STM32FXXXDMA2_stream3_cr_circ(uint8_t state)
{
	set_reg_block(&DMA2_Stream3->CR, 1, 8, state);
}
void STM32FXXXDMA2_stream3_cr_dir(uint8_t value)
{
	set_reg_block(&DMA2_Stream3->CR, 2, 7, value);
}
void STM32FXXXDMA2_stream3_cr_pfctrl(uint8_t state)
{
	set_reg_block(&DMA2_Stream3->CR, 1, 5, state);
}
void STM32FXXXDMA2_stream3_cr_tcie(uint8_t state)
{
	set_reg_block(&DMA2_Stream3->CR, 1, 4, state);
}
void STM32FXXXDMA2_stream3_cr_htie(uint8_t state)
{
	set_reg_block(&DMA2_Stream3->CR, 1, 3, state);
}
void STM32FXXXDMA2_stream3_cr_teie(uint8_t state)
{
	set_reg_block(&DMA2_Stream3->CR, 1, 2, state);
}
void STM32FXXXDMA2_stream3_cr_dmeie(uint8_t state)
{
	set_reg_block(&DMA2_Stream3->CR, 1, 1, state);
}
void STM32FXXXDMA2_stream3_cr_en(uint8_t state)
{
	set_reg_block(&DMA2_Stream3->CR, 1, 0, state);
}
/*** Inic DMA2 STREAM3 CR ***/
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma2_stream3_cr_inic(void)
{

	// CR
	stm32fxxx_dma2_stream3_cr.chsel = STM32FXXXDMA2_stream3_cr_chsel;
	stm32fxxx_dma2_stream3_cr.mburst = STM32FXXXDMA2_stream3_cr_mburst;
	stm32fxxx_dma2_stream3_cr.pburst = STM32FXXXDMA2_stream3_cr_pburst;
	stm32fxxx_dma2_stream3_cr.ct = STM32FXXXDMA2_stream3_cr_ct;
	stm32fxxx_dma2_stream3_cr.dbm = STM32FXXXDMA2_stream3_cr_dbm;
	stm32fxxx_dma2_stream3_cr.pl = STM32FXXXDMA2_stream3_cr_pl;
	stm32fxxx_dma2_stream3_cr.pincos = STM32FXXXDMA2_stream3_cr_pincos;
	stm32fxxx_dma2_stream3_cr.msize = STM32FXXXDMA2_stream3_cr_msize;
	stm32fxxx_dma2_stream3_cr.psize = STM32FXXXDMA2_stream3_cr_psize;
	stm32fxxx_dma2_stream3_cr.minc = STM32FXXXDMA2_stream3_cr_minc;
	stm32fxxx_dma2_stream3_cr.pinc = STM32FXXXDMA2_stream3_cr_pinc;
	stm32fxxx_dma2_stream3_cr.circ = STM32FXXXDMA2_stream3_cr_circ;
	stm32fxxx_dma2_stream3_cr.dir = STM32FXXXDMA2_stream3_cr_dir;
	stm32fxxx_dma2_stream3_cr.pfctrl = STM32FXXXDMA2_stream3_cr_pfctrl;
	stm32fxxx_dma2_stream3_cr.tcie = STM32FXXXDMA2_stream3_cr_tcie;
	stm32fxxx_dma2_stream3_cr.htie = STM32FXXXDMA2_stream3_cr_htie;
	stm32fxxx_dma2_stream3_cr.teie = STM32FXXXDMA2_stream3_cr_teie;
	stm32fxxx_dma2_stream3_cr.dmeie = STM32FXXXDMA2_stream3_cr_dmeie;
	stm32fxxx_dma2_stream3_cr.en = STM32FXXXDMA2_stream3_cr_en;
	return &stm32fxxx_dma2_stream3_cr;
}
/*** Inic DMA2 STREAM3 Function ***/
void stm32fxxx_dma2_stream3_ndt(uint16_t value)
{
	DMA2_Stream3->NDTR = value;
}
void stm32fxxx_dma2_stream3_par(volatile long unsigned int periferal_addr)
{
	DMA2_Stream3->PAR = periferal_addr;
}
void stm32fxxx_dma2_stream3_m0a(volatile long unsigned int mem0_addr)
{
	DMA2_Stream3->M0AR = mem0_addr;
}
void stm32fxxx_dma2_stream3_m1a(volatile long unsigned int mem1_addr)
{
	DMA2_Stream3->M1AR = mem1_addr;
}
// DMA2 STREAM4 CR
void STM32FXXXDMA2_stream4_cr_chsel(uint8_t value)
{
	set_reg_block(&DMA2_Stream4->CR, 3, 25, value);
}
void STM32FXXXDMA2_stream4_cr_mburst(uint8_t value)
{
	set_reg_block(&DMA2_Stream4->CR, 2, 23, value);
}
void STM32FXXXDMA2_stream4_cr_pburst(uint8_t value)
{
	set_reg_block(&DMA2_Stream4->CR, 2, 21, value);
}
void STM32FXXXDMA2_stream4_cr_ct(uint8_t state)
{
	set_reg_block(&DMA2_Stream4->CR, 1, 19, state);
}
void STM32FXXXDMA2_stream4_cr_dbm(uint8_t state)
{
	set_reg_block(&DMA2_Stream4->CR, 1, 18, state);
}
void STM32FXXXDMA2_stream4_cr_pl(uint8_t value)
{
	set_reg_block(&DMA2_Stream4->CR, 2, 16, value);
}
void STM32FXXXDMA2_stream4_cr_pincos(uint8_t state)
{
	set_reg_block(&DMA2_Stream4->CR, 1, 15, state);
}
void STM32FXXXDMA2_stream4_cr_msize(uint8_t value)
{
	set_reg_block(&DMA2_Stream4->CR, 2, 13, value);
}
void STM32FXXXDMA2_stream4_cr_psize(uint8_t value)
{
	set_reg_block(&DMA2_Stream4->CR, 2, 11, value);
}
void STM32FXXXDMA2_stream4_cr_minc(uint8_t state)
{
	set_reg_block(&DMA2_Stream4->CR, 1, 10, state);
}
void STM32FXXXDMA2_stream4_cr_pinc(uint8_t state)
{
	set_reg_block(&DMA2_Stream4->CR, 1, 9, state);
}
void STM32FXXXDMA2_stream4_cr_circ(uint8_t state)
{
	set_reg_block(&DMA2_Stream4->CR, 1, 8, state);
}
void STM32FXXXDMA2_stream4_cr_dir(uint8_t value)
{
	set_reg_block(&DMA2_Stream4->CR, 2, 7, value);
}
void STM32FXXXDMA2_stream4_cr_pfctrl(uint8_t state)
{
	set_reg_block(&DMA2_Stream4->CR, 1, 5, state);
}
void STM32FXXXDMA2_stream4_cr_tcie(uint8_t state)
{
	set_reg_block(&DMA2_Stream4->CR, 1, 4, state);
}
void STM32FXXXDMA2_stream4_cr_htie(uint8_t state)
{
	set_reg_block(&DMA2_Stream4->CR, 1, 3, state);
}
void STM32FXXXDMA2_stream4_cr_teie(uint8_t state)
{
	set_reg_block(&DMA2_Stream4->CR, 1, 2, state);
}
void STM32FXXXDMA2_stream4_cr_dmeie(uint8_t state)
{
	set_reg_block(&DMA2_Stream4->CR, 1, 1, state);
}
void STM32FXXXDMA2_stream4_cr_en(uint8_t state)
{
	set_reg_block(&DMA2_Stream4->CR, 1, 0, state);
}
/*** Inic DMA2 STREAM4 CR ***/
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma2_stream4_cr_inic(void)
{

	// CR
	stm32fxxx_dma2_stream4_cr.chsel = STM32FXXXDMA2_stream4_cr_chsel;
	stm32fxxx_dma2_stream4_cr.mburst = STM32FXXXDMA2_stream4_cr_mburst;
	stm32fxxx_dma2_stream4_cr.pburst = STM32FXXXDMA2_stream4_cr_pburst;
	stm32fxxx_dma2_stream4_cr.ct = STM32FXXXDMA2_stream4_cr_ct;
	stm32fxxx_dma2_stream4_cr.dbm = STM32FXXXDMA2_stream4_cr_dbm;
	stm32fxxx_dma2_stream4_cr.pl = STM32FXXXDMA2_stream4_cr_pl;
	stm32fxxx_dma2_stream4_cr.pincos = STM32FXXXDMA2_stream4_cr_pincos;
	stm32fxxx_dma2_stream4_cr.msize = STM32FXXXDMA2_stream4_cr_msize;
	stm32fxxx_dma2_stream4_cr.psize = STM32FXXXDMA2_stream4_cr_psize;
	stm32fxxx_dma2_stream4_cr.minc = STM32FXXXDMA2_stream4_cr_minc;
	stm32fxxx_dma2_stream4_cr.pinc = STM32FXXXDMA2_stream4_cr_pinc;
	stm32fxxx_dma2_stream4_cr.circ = STM32FXXXDMA2_stream4_cr_circ;
	stm32fxxx_dma2_stream4_cr.dir = STM32FXXXDMA2_stream4_cr_dir;
	stm32fxxx_dma2_stream4_cr.pfctrl = STM32FXXXDMA2_stream4_cr_pfctrl;
	stm32fxxx_dma2_stream4_cr.tcie = STM32FXXXDMA2_stream4_cr_tcie;
	stm32fxxx_dma2_stream4_cr.htie = STM32FXXXDMA2_stream4_cr_htie;
	stm32fxxx_dma2_stream4_cr.teie = STM32FXXXDMA2_stream4_cr_teie;
	stm32fxxx_dma2_stream4_cr.dmeie = STM32FXXXDMA2_stream4_cr_dmeie;
	stm32fxxx_dma2_stream4_cr.en = STM32FXXXDMA2_stream4_cr_en;
	return &stm32fxxx_dma2_stream4_cr;
}
/*** Inic DMA2 STREAM4 Function ***/
void stm32fxxx_dma2_stream4_ndt(uint16_t value)
{
	DMA2_Stream4->NDTR = value;
}
void stm32fxxx_dma2_stream4_par(volatile long unsigned int periferal_addr)
{
	DMA2_Stream4->PAR = periferal_addr;
}
void stm32fxxx_dma2_stream4_m0a(volatile long unsigned int mem0_addr)
{
	DMA2_Stream4->M0AR = mem0_addr;
}
void stm32fxxx_dma2_stream4_m1a(volatile long unsigned int mem1_addr)
{
	DMA2_Stream4->M1AR = mem1_addr;
}
// DMA2 STREAM5 CR
void STM32FXXXDMA2_stream5_cr_chsel(uint8_t value)
{
	set_reg_block(&DMA2_Stream5->CR, 3, 25, value);
}
void STM32FXXXDMA2_stream5_cr_mburst(uint8_t value)
{
	set_reg_block(&DMA2_Stream5->CR, 2, 23, value);
}
void STM32FXXXDMA2_stream5_cr_pburst(uint8_t value)
{
	set_reg_block(&DMA2_Stream5->CR, 2, 21, value);
}
void STM32FXXXDMA2_stream5_cr_ct(uint8_t state)
{
	set_reg_block(&DMA2_Stream5->CR, 1, 19, state);
}
void STM32FXXXDMA2_stream5_cr_dbm(uint8_t state)
{
	set_reg_block(&DMA2_Stream5->CR, 1, 18, state);
}
void STM32FXXXDMA2_stream5_cr_pl(uint8_t value)
{
	set_reg_block(&DMA2_Stream5->CR, 2, 16, value);
}
void STM32FXXXDMA2_stream5_cr_pincos(uint8_t state)
{
	set_reg_block(&DMA2_Stream5->CR, 1, 15, state);
}
void STM32FXXXDMA2_stream5_cr_msize(uint8_t value)
{
	set_reg_block(&DMA2_Stream5->CR, 2, 13, value);
}
void STM32FXXXDMA2_stream5_cr_psize(uint8_t value)
{
	set_reg_block(&DMA2_Stream5->CR, 2, 11, value);
}
void STM32FXXXDMA2_stream5_cr_minc(uint8_t state)
{
	set_reg_block(&DMA2_Stream5->CR, 1, 10, state);
}
void STM32FXXXDMA2_stream5_cr_pinc(uint8_t state)
{
	set_reg_block(&DMA2_Stream5->CR, 1, 9, state);
}
void STM32FXXXDMA2_stream5_cr_circ(uint8_t state)
{
	set_reg_block(&DMA2_Stream5->CR, 1, 8, state);
}
void STM32FXXXDMA2_stream5_cr_dir(uint8_t value)
{
	set_reg_block(&DMA2_Stream5->CR, 2, 7, value);
}
void STM32FXXXDMA2_stream5_cr_pfctrl(uint8_t state)
{
	set_reg_block(&DMA2_Stream5->CR, 1, 5, state);
}
void STM32FXXXDMA2_stream5_cr_tcie(uint8_t state)
{
	set_reg_block(&DMA2_Stream5->CR, 1, 4, state);
}
void STM32FXXXDMA2_stream5_cr_htie(uint8_t state)
{
	set_reg_block(&DMA2_Stream5->CR, 1, 3, state);
}
void STM32FXXXDMA2_stream5_cr_teie(uint8_t state)
{
	set_reg_block(&DMA2_Stream5->CR, 1, 2, state);
}
void STM32FXXXDMA2_stream5_cr_dmeie(uint8_t state)
{
	set_reg_block(&DMA2_Stream5->CR, 1, 1, state);
}
void STM32FXXXDMA2_stream5_cr_en(uint8_t state)
{
	set_reg_block(&DMA2_Stream5->CR, 1, 0, state);
}
/*** Inic DMA2 STREAM5 CR ***/
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma2_stream5_cr_inic(void)
{

	// CR
	stm32fxxx_dma2_stream5_cr.chsel = STM32FXXXDMA2_stream5_cr_chsel;
	stm32fxxx_dma2_stream5_cr.mburst = STM32FXXXDMA2_stream5_cr_mburst;
	stm32fxxx_dma2_stream5_cr.pburst = STM32FXXXDMA2_stream5_cr_pburst;
	stm32fxxx_dma2_stream5_cr.ct = STM32FXXXDMA2_stream5_cr_ct;
	stm32fxxx_dma2_stream5_cr.dbm = STM32FXXXDMA2_stream5_cr_dbm;
	stm32fxxx_dma2_stream5_cr.pl = STM32FXXXDMA2_stream5_cr_pl;
	stm32fxxx_dma2_stream5_cr.pincos = STM32FXXXDMA2_stream5_cr_pincos;
	stm32fxxx_dma2_stream5_cr.msize = STM32FXXXDMA2_stream5_cr_msize;
	stm32fxxx_dma2_stream5_cr.psize = STM32FXXXDMA2_stream5_cr_psize;
	stm32fxxx_dma2_stream5_cr.minc = STM32FXXXDMA2_stream5_cr_minc;
	stm32fxxx_dma2_stream5_cr.pinc = STM32FXXXDMA2_stream5_cr_pinc;
	stm32fxxx_dma2_stream5_cr.circ = STM32FXXXDMA2_stream5_cr_circ;
	stm32fxxx_dma2_stream5_cr.dir = STM32FXXXDMA2_stream5_cr_dir;
	stm32fxxx_dma2_stream5_cr.pfctrl = STM32FXXXDMA2_stream5_cr_pfctrl;
	stm32fxxx_dma2_stream5_cr.tcie = STM32FXXXDMA2_stream5_cr_tcie;
	stm32fxxx_dma2_stream5_cr.htie = STM32FXXXDMA2_stream5_cr_htie;
	stm32fxxx_dma2_stream5_cr.teie = STM32FXXXDMA2_stream5_cr_teie;
	stm32fxxx_dma2_stream5_cr.dmeie = STM32FXXXDMA2_stream5_cr_dmeie;
	stm32fxxx_dma2_stream5_cr.en = STM32FXXXDMA2_stream5_cr_en;
	return &stm32fxxx_dma2_stream5_cr;
}
/*** Inic DMA2 STREAM5 Function ***/
void stm32fxxx_dma2_stream5_ndt(uint16_t value)
{
	DMA2_Stream5->NDTR = value;
}
void stm32fxxx_dma2_stream5_par(volatile long unsigned int periferal_addr)
{
	DMA2_Stream5->PAR = periferal_addr;
}
void stm32fxxx_dma2_stream5_m0a(volatile long unsigned int mem0_addr)
{
	DMA2_Stream5->M0AR = mem0_addr;
}
void stm32fxxx_dma2_stream5_m1a(volatile long unsigned int mem1_addr)
{
	DMA2_Stream5->M1AR = mem1_addr;
}
// DMA2 STREAM6 CR
void STM32FXXXDMA2_stream6_cr_chsel(uint8_t value)
{
	set_reg_block(&DMA2_Stream6->CR, 3, 25, value);
}
void STM32FXXXDMA2_stream6_cr_mburst(uint8_t value)
{
	set_reg_block(&DMA2_Stream6->CR, 2, 23, value);
}
void STM32FXXXDMA2_stream6_cr_pburst(uint8_t value)
{
	set_reg_block(&DMA2_Stream6->CR, 2, 21, value);
}
void STM32FXXXDMA2_stream6_cr_ct(uint8_t state)
{
	set_reg_block(&DMA2_Stream6->CR, 1, 19, state);
}
void STM32FXXXDMA2_stream6_cr_dbm(uint8_t state)
{
	set_reg_block(&DMA2_Stream6->CR, 1, 18, state);
}
void STM32FXXXDMA2_stream6_cr_pl(uint8_t value)
{
	set_reg_block(&DMA2_Stream6->CR, 2, 16, value);
}
void STM32FXXXDMA2_stream6_cr_pincos(uint8_t state)
{
	set_reg_block(&DMA2_Stream6->CR, 1, 15, state);
}
void STM32FXXXDMA2_stream6_cr_msize(uint8_t value)
{
	set_reg_block(&DMA2_Stream6->CR, 2, 13, value);
}
void STM32FXXXDMA2_stream6_cr_psize(uint8_t value)
{
	set_reg_block(&DMA2_Stream6->CR, 2, 11, value);
}
void STM32FXXXDMA2_stream6_cr_minc(uint8_t state)
{
	set_reg_block(&DMA2_Stream6->CR, 1, 10, state);
}
void STM32FXXXDMA2_stream6_cr_pinc(uint8_t state)
{
	set_reg_block(&DMA2_Stream6->CR, 1, 9, state);
}
void STM32FXXXDMA2_stream6_cr_circ(uint8_t state)
{
	set_reg_block(&DMA2_Stream6->CR, 1, 8, state);
}
void STM32FXXXDMA2_stream6_cr_dir(uint8_t value)
{
	set_reg_block(&DMA2_Stream6->CR, 2, 7, value);
}
void STM32FXXXDMA2_stream6_cr_pfctrl(uint8_t state)
{
	set_reg_block(&DMA2_Stream6->CR, 1, 5, state);
}
void STM32FXXXDMA2_stream6_cr_tcie(uint8_t state)
{
	set_reg_block(&DMA2_Stream6->CR, 1, 4, state);
}
void STM32FXXXDMA2_stream6_cr_htie(uint8_t state)
{
	set_reg_block(&DMA2_Stream6->CR, 1, 3, state);
}
void STM32FXXXDMA2_stream6_cr_teie(uint8_t state)
{
	set_reg_block(&DMA2_Stream6->CR, 1, 2, state);
}
void STM32FXXXDMA2_stream6_cr_dmeie(uint8_t state)
{
	set_reg_block(&DMA2_Stream6->CR, 1, 1, state);
}
void STM32FXXXDMA2_stream6_cr_en(uint8_t state)
{
	set_reg_block(&DMA2_Stream6->CR, 1, 0, state);
}
/*** Inic DMA2 STREAM6 CR ***/
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma2_stream6_cr_inic(void)
{

	// CR
	stm32fxxx_dma2_stream6_cr.chsel = STM32FXXXDMA2_stream6_cr_chsel;
	stm32fxxx_dma2_stream6_cr.mburst = STM32FXXXDMA2_stream6_cr_mburst;
	stm32fxxx_dma2_stream6_cr.pburst = STM32FXXXDMA2_stream6_cr_pburst;
	stm32fxxx_dma2_stream6_cr.ct = STM32FXXXDMA2_stream6_cr_ct;
	stm32fxxx_dma2_stream6_cr.dbm = STM32FXXXDMA2_stream6_cr_dbm;
	stm32fxxx_dma2_stream6_cr.pl = STM32FXXXDMA2_stream6_cr_pl;
	stm32fxxx_dma2_stream6_cr.pincos = STM32FXXXDMA2_stream6_cr_pincos;
	stm32fxxx_dma2_stream6_cr.msize = STM32FXXXDMA2_stream6_cr_msize;
	stm32fxxx_dma2_stream6_cr.psize = STM32FXXXDMA2_stream6_cr_psize;
	stm32fxxx_dma2_stream6_cr.minc = STM32FXXXDMA2_stream6_cr_minc;
	stm32fxxx_dma2_stream6_cr.pinc = STM32FXXXDMA2_stream6_cr_pinc;
	stm32fxxx_dma2_stream6_cr.circ = STM32FXXXDMA2_stream6_cr_circ;
	stm32fxxx_dma2_stream6_cr.dir = STM32FXXXDMA2_stream6_cr_dir;
	stm32fxxx_dma2_stream6_cr.pfctrl = STM32FXXXDMA2_stream6_cr_pfctrl;
	stm32fxxx_dma2_stream6_cr.tcie = STM32FXXXDMA2_stream6_cr_tcie;
	stm32fxxx_dma2_stream6_cr.htie = STM32FXXXDMA2_stream6_cr_htie;
	stm32fxxx_dma2_stream6_cr.teie = STM32FXXXDMA2_stream6_cr_teie;
	stm32fxxx_dma2_stream6_cr.dmeie = STM32FXXXDMA2_stream6_cr_dmeie;
	stm32fxxx_dma2_stream6_cr.en = STM32FXXXDMA2_stream6_cr_en;
	return &stm32fxxx_dma2_stream6_cr;
}
/*** Inic DMA2 STREAM6 Function ***/
void stm32fxxx_dma2_stream6_ndt(uint16_t value)
{
	DMA2_Stream6->NDTR = value;
}
void stm32fxxx_dma2_stream6_par(volatile long unsigned int periferal_addr)
{
	DMA2_Stream6->PAR = periferal_addr;
}
void stm32fxxx_dma2_stream6_m0a(volatile long unsigned int mem0_addr)
{
	DMA2_Stream6->M0AR = mem0_addr;
}
void stm32fxxx_dma2_stream6_m1a(volatile long unsigned int mem1_addr)
{
	DMA2_Stream6->M1AR = mem1_addr;
}
// DMA2 STREAM7 CR
void STM32FXXXDMA2_stream7_cr_chsel(uint8_t value)
{
	set_reg_block(&DMA2_Stream7->CR, 3, 25, value);
}
void STM32FXXXDMA2_stream7_cr_mburst(uint8_t value)
{
	set_reg_block(&DMA2_Stream7->CR, 2, 23, value);
}
void STM32FXXXDMA2_stream7_cr_pburst(uint8_t value)
{
	set_reg_block(&DMA2_Stream7->CR, 2, 21, value);
}
void STM32FXXXDMA2_stream7_cr_ct(uint8_t state)
{
	set_reg_block(&DMA2_Stream7->CR, 1, 19, state);
}
void STM32FXXXDMA2_stream7_cr_dbm(uint8_t state)
{
	set_reg_block(&DMA2_Stream7->CR, 1, 18, state);
}
void STM32FXXXDMA2_stream7_cr_pl(uint8_t value)
{
	set_reg_block(&DMA2_Stream7->CR, 2, 16, value);
}
void STM32FXXXDMA2_stream7_cr_pincos(uint8_t state)
{
	set_reg_block(&DMA2_Stream7->CR, 1, 15, state);
}
void STM32FXXXDMA2_stream7_cr_msize(uint8_t value)
{
	set_reg_block(&DMA2_Stream7->CR, 2, 13, value);
}
void STM32FXXXDMA2_stream7_cr_psize(uint8_t value)
{
	set_reg_block(&DMA2_Stream7->CR, 2, 11, value);
}
void STM32FXXXDMA2_stream7_cr_minc(uint8_t state)
{
	set_reg_block(&DMA2_Stream7->CR, 1, 10, state);
}
void STM32FXXXDMA2_stream7_cr_pinc(uint8_t state)
{
	set_reg_block(&DMA2_Stream7->CR, 1, 9, state);
}
void STM32FXXXDMA2_stream7_cr_circ(uint8_t state)
{
	set_reg_block(&DMA2_Stream7->CR, 1, 8, state);
}
void STM32FXXXDMA2_stream7_cr_dir(uint8_t value)
{
	set_reg_block(&DMA2_Stream7->CR, 2, 7, value);
}
void STM32FXXXDMA2_stream7_cr_pfctrl(uint8_t state)
{
	set_reg_block(&DMA2_Stream7->CR, 1, 5, state);
}
void STM32FXXXDMA2_stream7_cr_tcie(uint8_t state)
{
	set_reg_block(&DMA2_Stream7->CR, 1, 4, state);
}
void STM32FXXXDMA2_stream7_cr_htie(uint8_t state)
{
	set_reg_block(&DMA2_Stream7->CR, 1, 3, state);
}
void STM32FXXXDMA2_stream7_cr_teie(uint8_t state)
{
	set_reg_block(&DMA2_Stream7->CR, 1, 2, state);
}
void STM32FXXXDMA2_stream7_cr_dmeie(uint8_t state)
{
	set_reg_block(&DMA2_Stream7->CR, 1, 1, state);
}
void STM32FXXXDMA2_stream7_cr_en(uint8_t state)
{
	set_reg_block(&DMA2_Stream7->CR, 1, 0, state);
}
/*** Inic DMA2 STREAM7 CR ***/
STM32FXXXDMA_STREAM_cr* stm32fxxx_dma2_stream7_cr_inic(void)
{

	// CR
	stm32fxxx_dma2_stream7_cr.chsel = STM32FXXXDMA2_stream7_cr_chsel;
	stm32fxxx_dma2_stream7_cr.mburst = STM32FXXXDMA2_stream7_cr_mburst;
	stm32fxxx_dma2_stream7_cr.pburst = STM32FXXXDMA2_stream7_cr_pburst;
	stm32fxxx_dma2_stream7_cr.ct = STM32FXXXDMA2_stream7_cr_ct;
	stm32fxxx_dma2_stream7_cr.dbm = STM32FXXXDMA2_stream7_cr_dbm;
	stm32fxxx_dma2_stream7_cr.pl = STM32FXXXDMA2_stream7_cr_pl;
	stm32fxxx_dma2_stream7_cr.pincos = STM32FXXXDMA2_stream7_cr_pincos;
	stm32fxxx_dma2_stream7_cr.msize = STM32FXXXDMA2_stream7_cr_msize;
	stm32fxxx_dma2_stream7_cr.psize = STM32FXXXDMA2_stream7_cr_psize;
	stm32fxxx_dma2_stream7_cr.minc = STM32FXXXDMA2_stream7_cr_minc;
	stm32fxxx_dma2_stream7_cr.pinc = STM32FXXXDMA2_stream7_cr_pinc;
	stm32fxxx_dma2_stream7_cr.circ = STM32FXXXDMA2_stream7_cr_circ;
	stm32fxxx_dma2_stream7_cr.dir = STM32FXXXDMA2_stream7_cr_dir;
	stm32fxxx_dma2_stream7_cr.pfctrl = STM32FXXXDMA2_stream7_cr_pfctrl;
	stm32fxxx_dma2_stream7_cr.tcie = STM32FXXXDMA2_stream7_cr_tcie;
	stm32fxxx_dma2_stream7_cr.htie = STM32FXXXDMA2_stream7_cr_htie;
	stm32fxxx_dma2_stream7_cr.teie = STM32FXXXDMA2_stream7_cr_teie;
	stm32fxxx_dma2_stream7_cr.dmeie = STM32FXXXDMA2_stream7_cr_dmeie;
	stm32fxxx_dma2_stream7_cr.en = STM32FXXXDMA2_stream7_cr_en;
	return &stm32fxxx_dma2_stream7_cr;
}
/*** Inic DMA2 STREAM7 Function ***/
void stm32fxxx_dma2_stream7_ndt(uint16_t value)
{
	DMA2_Stream7->NDTR = value;
}
void stm32fxxx_dma2_stream7_par(volatile long unsigned int periferal_addr)
{
	DMA2_Stream7->PAR = periferal_addr;
}
void stm32fxxx_dma2_stream7_m0a(volatile long unsigned int mem0_addr)
{
	DMA2_Stream7->M0AR = mem0_addr;
}
void stm32fxxx_dma2_stream7_m1a(volatile long unsigned int mem1_addr)
{
	DMA2_Stream7->M1AR = mem1_addr;
}
// DMA2 STREAM0 FCR
void STM32FXXXDMA2_stream0_fcr_feie(uint8_t state)
{
	set_reg_block(&DMA2_Stream0->FCR, 1, 7, state);
}
void STM32FXXXDMA2_stream0_fcr_fs(uint8_t value)
{
	set_reg_block(&DMA2_Stream0->FCR, 3, 3, value);
}
void STM32FXXXDMA2_stream0_fcr_dmdis(uint8_t state)
{
	set_reg_block(&DMA2_Stream0->FCR, 1, 2, state);
}
void STM32FXXXDMA2_stream0_fcr_fth(uint8_t value)
{
	set_reg_block(&DMA2_Stream0->FCR, 2, 0, value);
}
/*** Inic DMA2 STREAM0 FCR ***/
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma2_stream0_fcr_inic(void)
{

	// FCR
	stm32fxxx_dma2_stream0_fcr.feie = STM32FXXXDMA2_stream0_fcr_feie;
	stm32fxxx_dma2_stream0_fcr.fs = STM32FXXXDMA2_stream0_fcr_fs;
	stm32fxxx_dma2_stream0_fcr.dmdis = STM32FXXXDMA2_stream0_fcr_dmdis;
	stm32fxxx_dma2_stream0_fcr.fth = STM32FXXXDMA2_stream0_fcr_fth;
	return &stm32fxxx_dma2_stream0_fcr;
}
// DMA2 STREAM1 FCR
void STM32FXXXDMA2_stream1_fcr_feie(uint8_t state)
{
	set_reg_block(&DMA2_Stream1->FCR, 1, 7, state);
}
void STM32FXXXDMA2_stream1_fcr_fs(uint8_t value)
{
	set_reg_block(&DMA2_Stream1->FCR, 3, 3, value);
}
void STM32FXXXDMA2_stream1_fcr_dmdis(uint8_t state)
{
	set_reg_block(&DMA2_Stream1->FCR, 1, 2, state);
}
void STM32FXXXDMA2_stream1_fcr_fth(uint8_t value)
{
	set_reg_block(&DMA2_Stream1->FCR, 2, 0, value);
}
/*** Inic DMA2 STREAM1 FCR ***/
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma2_stream1_fcr_inic(void)
{

	// FCR
	stm32fxxx_dma2_stream1_fcr.feie = STM32FXXXDMA2_stream1_fcr_feie;
	stm32fxxx_dma2_stream1_fcr.fs = STM32FXXXDMA2_stream1_fcr_fs;
	stm32fxxx_dma2_stream1_fcr.dmdis = STM32FXXXDMA2_stream1_fcr_dmdis;
	stm32fxxx_dma2_stream1_fcr.fth = STM32FXXXDMA2_stream1_fcr_fth;
	return &stm32fxxx_dma2_stream1_fcr;
}
// DMA2 STREAM2 FCR
void STM32FXXXDMA2_stream2_fcr_feie(uint8_t state)
{
	set_reg_block(&DMA2_Stream2->FCR, 1, 7, state);
}
void STM32FXXXDMA2_stream2_fcr_fs(uint8_t value)
{
	set_reg_block(&DMA2_Stream2->FCR, 3, 3, value);
}
void STM32FXXXDMA2_stream2_fcr_dmdis(uint8_t state)
{
	set_reg_block(&DMA2_Stream2->FCR, 1, 2, state);
}
void STM32FXXXDMA2_stream2_fcr_fth(uint8_t value)
{
	set_reg_block(&DMA2_Stream2->FCR, 2, 0, value);
}
/*** Inic DMA2 STREAM2 FCR ***/
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma2_stream2_fcr_inic(void)
{

	// FCR
	stm32fxxx_dma2_stream2_fcr.feie = STM32FXXXDMA2_stream2_fcr_feie;
	stm32fxxx_dma2_stream2_fcr.fs = STM32FXXXDMA2_stream2_fcr_fs;
	stm32fxxx_dma2_stream2_fcr.dmdis = STM32FXXXDMA2_stream2_fcr_dmdis;
	stm32fxxx_dma2_stream2_fcr.fth = STM32FXXXDMA2_stream2_fcr_fth;
	return &stm32fxxx_dma2_stream2_fcr;
}
// DMA2 STREAM3 FCR
void STM32FXXXDMA2_stream3_fcr_feie(uint8_t state)
{
	set_reg_block(&DMA2_Stream3->FCR, 1, 7, state);
}
void STM32FXXXDMA2_stream3_fcr_fs(uint8_t value)
{
	set_reg_block(&DMA2_Stream3->FCR, 3, 3, value);
}
void STM32FXXXDMA2_stream3_fcr_dmdis(uint8_t state)
{
	set_reg_block(&DMA2_Stream3->FCR, 1, 2, state);
}
void STM32FXXXDMA2_stream3_fcr_fth(uint8_t value)
{
	set_reg_block(&DMA2_Stream3->FCR, 2, 0, value);
}
/*** Inic DMA2 STREAM3 FCR ***/
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma2_stream3_fcr_inic(void)
{

	// FCR
	stm32fxxx_dma2_stream3_fcr.feie = STM32FXXXDMA2_stream3_fcr_feie;
	stm32fxxx_dma2_stream3_fcr.fs = STM32FXXXDMA2_stream3_fcr_fs;
	stm32fxxx_dma2_stream3_fcr.dmdis = STM32FXXXDMA2_stream3_fcr_dmdis;
	stm32fxxx_dma2_stream3_fcr.fth = STM32FXXXDMA2_stream3_fcr_fth;
	return &stm32fxxx_dma2_stream3_fcr;
}
// DMA1 STREAM4 FCR
void STM32FXXXDMA2_stream4_fcr_feie(uint8_t state)
{
	set_reg_block(&DMA2_Stream4->FCR, 1, 7, state);
}
void STM32FXXXDMA2_stream4_fcr_fs(uint8_t value)
{
	set_reg_block(&DMA2_Stream4->FCR, 3, 3, value);
}
void STM32FXXXDMA2_stream4_fcr_dmdis(uint8_t state)
{
	set_reg_block(&DMA2_Stream4->FCR, 1, 2, state);
}
void STM32FXXXDMA2_stream4_fcr_fth(uint8_t value)
{
	set_reg_block(&DMA2_Stream4->FCR, 2, 0, value);
}
/*** Inic DMA2 STREAM4 FCR ***/
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma2_stream4_fcr_inic(void)
{

	// FCR
	stm32fxxx_dma2_stream4_fcr.feie = STM32FXXXDMA2_stream4_fcr_feie;
	stm32fxxx_dma2_stream4_fcr.fs = STM32FXXXDMA2_stream4_fcr_fs;
	stm32fxxx_dma2_stream4_fcr.dmdis = STM32FXXXDMA2_stream4_fcr_dmdis;
	stm32fxxx_dma2_stream4_fcr.fth = STM32FXXXDMA2_stream4_fcr_fth;
	return &stm32fxxx_dma2_stream4_fcr;
}
// DMA1 STREAM5 FCR
void STM32FXXXDMA2_stream5_fcr_feie(uint8_t state)
{
	set_reg_block(&DMA2_Stream5->FCR, 1, 7, state);
}
void STM32FXXXDMA2_stream5_fcr_fs(uint8_t value)
{
	set_reg_block(&DMA2_Stream5->FCR, 3, 3, value);
}
void STM32FXXXDMA2_stream5_fcr_dmdis(uint8_t state)
{
	set_reg_block(&DMA2_Stream5->FCR, 1, 2, state);
}
void STM32FXXXDMA2_stream5_fcr_fth(uint8_t value)
{
	set_reg_block(&DMA2_Stream5->FCR, 2, 0, value);
}
/*** Inic DMA2 STREAM5 FCR ***/
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma2_stream5_fcr_inic(void)
{

	// FCR
	stm32fxxx_dma2_stream5_fcr.feie = STM32FXXXDMA2_stream5_fcr_feie;
	stm32fxxx_dma2_stream5_fcr.fs = STM32FXXXDMA2_stream5_fcr_fs;
	stm32fxxx_dma2_stream5_fcr.dmdis = STM32FXXXDMA2_stream5_fcr_dmdis;
	stm32fxxx_dma2_stream5_fcr.fth = STM32FXXXDMA2_stream5_fcr_fth;
	return &stm32fxxx_dma2_stream5_fcr;
}
// DMA1 STREAM6 FCR
void STM32FXXXDMA2_stream6_fcr_feie(uint8_t state)
{
	set_reg_block(&DMA2_Stream6->FCR, 1, 7, state);
}
void STM32FXXXDMA2_stream6_fcr_fs(uint8_t value)
{
	set_reg_block(&DMA2_Stream6->FCR, 3, 3, value);
}
void STM32FXXXDMA2_stream6_fcr_dmdis(uint8_t state)
{
	set_reg_block(&DMA2_Stream6->FCR, 1, 2, state);
}
void STM32FXXXDMA2_stream6_fcr_fth(uint8_t value)
{
	set_reg_block(&DMA2_Stream6->FCR, 2, 0, value);
}
/*** Inic DMA2 STREAM6 FCR ***/
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma2_stream6_fcr_inic(void)
{

	// FCR
	stm32fxxx_dma2_stream6_fcr.feie = STM32FXXXDMA2_stream6_fcr_feie;
	stm32fxxx_dma2_stream6_fcr.fs = STM32FXXXDMA2_stream6_fcr_fs;
	stm32fxxx_dma2_stream6_fcr.dmdis = STM32FXXXDMA2_stream6_fcr_dmdis;
	stm32fxxx_dma2_stream6_fcr.fth = STM32FXXXDMA2_stream6_fcr_fth;
	return &stm32fxxx_dma2_stream6_fcr;
}
// DMA2 STREAM0 FCR
void STM32FXXXDMA2_stream7_fcr_feie(uint8_t state)
{
	set_reg_block(&DMA2_Stream7->FCR, 1, 7, state);
}
void STM32FXXXDMA2_stream7_fcr_fs(uint8_t value)
{
	set_reg_block(&DMA2_Stream7->FCR, 3, 3, value);
}
void STM32FXXXDMA2_stream7_fcr_dmdis(uint8_t state)
{
	set_reg_block(&DMA2_Stream7->FCR, 1, 2, state);
}
void STM32FXXXDMA2_stream7_fcr_fth(uint8_t value)
{
	set_reg_block(&DMA2_Stream7->FCR, 2, 0, value);
}
/*** Inic DMA2 STREAM7 FCR ***/
STM32FXXXDMA_STREAM_fcr* stm32fxxx_dma2_stream7_fcr_inic(void)
{

	// FCR
	stm32fxxx_dma2_stream7_fcr.feie = STM32FXXXDMA2_stream7_fcr_feie;
	stm32fxxx_dma2_stream7_fcr.fs = STM32FXXXDMA2_stream7_fcr_fs;
	stm32fxxx_dma2_stream7_fcr.dmdis = STM32FXXXDMA2_stream7_fcr_dmdis;
	stm32fxxx_dma2_stream7_fcr.fth = STM32FXXXDMA2_stream7_fcr_fth;
	return &stm32fxxx_dma2_stream7_fcr;
}
/*** FUNC ***/
void dma2_circ_cfg(volatile long unsigned int* p_addr, volatile long unsigned int* m_addr, uint8_t stream_n, uint8_t channel_n, uint16_t quant_d, uint8_t p_size, uint8_t m_size, uint8_t priority, uint8_t dir)
{
	// Filter to Default
	if(stream_n > 7){ stream_n = 0;}
	if(channel_n > 7){ channel_n = 0;}
	if(quant_d > 65535){ quant_d = 1;}
	if(p_size > 2){ p_size = 0;}
	if(m_size > 2){ m_size = 0;}
	if(priority > 3){ priority = 0;}
	if( p_addr && m_addr ){
		/*** Verify Ready for Parameter ***/
		set_reg_block(&(DMA2_Stream0 + stream_n)->CR, 1, 0, 0);
		for(time_out = 200; get_reg_block((DMA2_Stream0 + stream_n)->CR, 1, 0) && time_out; time_out--);
		/*** Parameter Configure ***/
		(DMA2_Stream0 + stream_n)->PAR = (volatile long unsigned int) p_addr;
		(DMA2_Stream0 + stream_n)->M0AR = (volatile long unsigned int) m_addr;
		set_reg_block(&(DMA2_Stream0 + stream_n)->CR, 1, 5, 0); // 0 -> dma, 1 -> peri
		set_reg_block(&(DMA2_Stream0 + stream_n)->CR, 3, 25, channel_n); // channel
		(DMA2_Stream0 + stream_n)->NDTR = quant_d; //
		set_reg_block(&(DMA2_Stream0 + stream_n)->CR, 2, 13, m_size); // msize 2 -> 32bit
		set_reg_block(&(DMA2_Stream0 + stream_n)->CR, 2, 11, p_size); // psize 1 -> 16bit
		set_reg_block(&(DMA2_Stream0 + stream_n)->CR, 2, 16, priority); // priority
		if(dir){
			set_reg_block(&(DMA2_Stream0 + stream_n)->CR, 2, 6, 1); // DIR
			set_reg_block(&(DMA2_Stream0 + stream_n)->CR, 1, 9, 1); // PINC
			set_reg_block(&(DMA2_Stream0 + stream_n)->CR, 1, 10, 0); // MINC
		}else{
			set_reg_block(&(DMA2_Stream0 + stream_n)->CR, 2, 6, 0); // DIR
			set_reg_block(&(DMA2_Stream0 + stream_n)->CR, 1, 9, 0); // PINC
			set_reg_block(&(DMA2_Stream0 + stream_n)->CR, 1, 10, 1); // MINC
		}
		set_reg_block(&(DMA2_Stream0 + stream_n)->CR, 1, 8, 1); // CIRC
		set_reg_block(&(DMA2_Stream0 + stream_n)->CR, 1, 0, 1); // ENABLE
	}
}
/*** Inic FUNC ***/
STM32FXXXDMA_func* stm32fxxx_dma2_func_inic(void)
{

	stm32fxxx_dma2_func.circ_cfg = dma2_circ_cfg;
	return &stm32fxxx_dma2_func;
}
/****************************************************/
/**** DMA2 INIC Procedure & Function Definition *****/
/****************************************************/
void dma2_enable(void)
{
	STM32FXXXDma2Clock(ON);
	stm32fxxx_dma2.instance = DMA2;
	/*** DMA2 Bit Mapping Link ***/
	stm32fxxx_dma2.sr = stm32fxxx_dma2_sr_inic();

	stm32fxxx_dma2.stream[0]->instance = DMA2_Stream0;
	stm32fxxx_dma2.stream[0]->cr = stm32fxxx_dma2_stream0_cr_inic();
	stm32fxxx_dma2.stream[0]->fcr = stm32fxxx_dma2_stream0_fcr_inic();
	stm32fxxx_dma2.stream[0]->ndt = stm32fxxx_dma2_stream0_ndt;
	stm32fxxx_dma2.stream[0]->par = stm32fxxx_dma2_stream0_par;
	stm32fxxx_dma2.stream[0]->m0a = stm32fxxx_dma2_stream0_m0a;
	stm32fxxx_dma2.stream[0]->m1a = stm32fxxx_dma2_stream0_m1a;

	stm32fxxx_dma2.stream[1]->instance = DMA2_Stream1;
	stm32fxxx_dma2.stream[1]->cr = stm32fxxx_dma2_stream1_cr_inic();
	stm32fxxx_dma2.stream[1]->fcr = stm32fxxx_dma2_stream1_fcr_inic();
	stm32fxxx_dma2.stream[1]->ndt = stm32fxxx_dma2_stream1_ndt;
	stm32fxxx_dma2.stream[1]->par = stm32fxxx_dma2_stream1_par;
	stm32fxxx_dma2.stream[1]->m0a = stm32fxxx_dma2_stream1_m0a;
	stm32fxxx_dma2.stream[1]->m1a = stm32fxxx_dma2_stream1_m1a;

	stm32fxxx_dma2.stream[2]->instance = DMA2_Stream2;
	stm32fxxx_dma2.stream[2]->cr = stm32fxxx_dma2_stream2_cr_inic();
	stm32fxxx_dma2.stream[2]->fcr = stm32fxxx_dma2_stream2_fcr_inic();
	stm32fxxx_dma2.stream[2]->ndt = stm32fxxx_dma2_stream2_ndt;
	stm32fxxx_dma2.stream[2]->par = stm32fxxx_dma2_stream2_par;
	stm32fxxx_dma2.stream[2]->m0a = stm32fxxx_dma2_stream2_m0a;
	stm32fxxx_dma2.stream[2]->m1a = stm32fxxx_dma2_stream2_m1a;

	stm32fxxx_dma2.stream[3]->instance = DMA2_Stream3;
	stm32fxxx_dma2.stream[3]->cr = stm32fxxx_dma2_stream3_cr_inic();
	stm32fxxx_dma2.stream[3]->fcr = stm32fxxx_dma2_stream3_fcr_inic();
	stm32fxxx_dma2.stream[3]->ndt = stm32fxxx_dma2_stream3_ndt;
	stm32fxxx_dma2.stream[3]->par = stm32fxxx_dma2_stream3_par;
	stm32fxxx_dma2.stream[3]->m0a = stm32fxxx_dma2_stream3_m0a;
	stm32fxxx_dma2.stream[3]->m1a = stm32fxxx_dma2_stream3_m1a;

	stm32fxxx_dma2.stream[4]->instance = DMA2_Stream4;
	stm32fxxx_dma2.stream[4]->cr = stm32fxxx_dma2_stream4_cr_inic();
	stm32fxxx_dma2.stream[4]->fcr = stm32fxxx_dma2_stream4_fcr_inic();
	stm32fxxx_dma2.stream[4]->ndt = stm32fxxx_dma2_stream4_ndt;
	stm32fxxx_dma2.stream[4]->par = stm32fxxx_dma2_stream4_par;
	stm32fxxx_dma2.stream[4]->m0a = stm32fxxx_dma2_stream4_m0a;
	stm32fxxx_dma2.stream[4]->m1a = stm32fxxx_dma2_stream4_m1a;

	stm32fxxx_dma2.stream[5]->instance = DMA2_Stream5;
	stm32fxxx_dma2.stream[5]->cr = stm32fxxx_dma2_stream5_cr_inic();
	stm32fxxx_dma2.stream[5]->fcr = stm32fxxx_dma2_stream5_fcr_inic();
	stm32fxxx_dma2.stream[5]->ndt = stm32fxxx_dma2_stream5_ndt;
	stm32fxxx_dma2.stream[5]->par = stm32fxxx_dma2_stream5_par;
	stm32fxxx_dma2.stream[5]->m0a = stm32fxxx_dma2_stream5_m0a;
	stm32fxxx_dma2.stream[5]->m1a = stm32fxxx_dma2_stream5_m1a;

	stm32fxxx_dma2.stream[6]->instance = DMA2_Stream6;
	stm32fxxx_dma2.stream[6]->cr = stm32fxxx_dma2_stream6_cr_inic();
	stm32fxxx_dma2.stream[6]->fcr = stm32fxxx_dma2_stream6_fcr_inic();
	stm32fxxx_dma2.stream[6]->ndt = stm32fxxx_dma2_stream6_ndt;
	stm32fxxx_dma2.stream[6]->par = stm32fxxx_dma2_stream6_par;
	stm32fxxx_dma2.stream[6]->m0a = stm32fxxx_dma2_stream6_m0a;
	stm32fxxx_dma2.stream[6]->m1a = stm32fxxx_dma2_stream6_m1a;

	stm32fxxx_dma2.stream[7]->instance = DMA2_Stream7;
	stm32fxxx_dma2.stream[7]->cr = stm32fxxx_dma2_stream7_cr_inic();
	stm32fxxx_dma2.stream[7]->fcr = stm32fxxx_dma2_stream7_fcr_inic();
	stm32fxxx_dma2.stream[7]->ndt = stm32fxxx_dma2_stream7_ndt;
	stm32fxxx_dma2.stream[7]->par = stm32fxxx_dma2_stream7_par;
	stm32fxxx_dma2.stream[7]->m0a = stm32fxxx_dma2_stream7_m0a;
	stm32fxxx_dma2.stream[7]->m1a = stm32fxxx_dma2_stream7_m1a;
	/*** Other ***/
	stm32fxxx_dma2.func = stm32fxxx_dma2_func_inic();
	stm32fxxx_dma2.clock = STM32FXXXDma2Clock;
	//return &stm32fxxx_dma2;
}

STM32FXXX_DMA2* dma2(void){ return &stm32fxxx_dma2; }

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

