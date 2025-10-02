/******************************************************************************
	STM32 XXX DMA
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     27062023
Comment:

*******************************************************************************/
#ifndef _STM32FXXXDMA_H_
	#define _STM32FXXXDMA_H_

/*** Library ***/
#include "stm32f411ceu6.h"
/*** DMA Bit Mapping TypeDef ***/
// SR
typedef struct
{
	uint8_t (*tcif)(uint8_t stream_n);
	void (*clear_tcif)(uint8_t stream_n);
	uint8_t (*htif)(uint8_t stream_n);
	void (*clear_htif)(uint8_t stream_n);
	uint8_t (*teif)(uint8_t stream_n);
	void (*clear_teif)(uint8_t stream_n);
	uint8_t (*dmeif)(uint8_t stream_n);
	void (*clear_dmeif)(uint8_t stream_n);
	uint8_t (*feif)(uint8_t stream_n);
	void (*clear_feif)(uint8_t stream_n);
}STM32FXXX_DMA_sr;
// CR
typedef struct
{
	void (*chsel)(uint8_t value);
	void (*mburst)(uint8_t value);
	void (*pburst)(uint8_t value);
	void (*ct)(uint8_t state);
	void (*dbm)(uint8_t state);
	void (*pl)(uint8_t vlue);
	void (*pincos)(uint8_t state);
	void (*msize)(uint8_t value);
	void (*psize)(uint8_t value);
	void (*minc)(uint8_t state);
	void (*pinc)(uint8_t state);
	void (*circ)(uint8_t state);
	void (*dir)(uint8_t value);
	void (*pfctrl)(uint8_t state);
	void (*tcie)(uint8_t state);
	void (*htie)(uint8_t state);
	void (*teie)(uint8_t state);
	void (*dmeie)(uint8_t state);
	void (*en)(uint8_t state);
}STM32FXXX_DMA_STREAM_cr;
// FCR
typedef struct
{
	void (*feie)(uint8_t state);
	void (*fs)(uint8_t value);
	void (*dmdis)(uint8_t state);
	void (*fth)(uint8_t value);
}STM32FXXX_DMA_STREAM_fcr;
// FUNC
typedef struct
{
	void (*circ_cfg)(volatile long unsigned int* p_addr, volatile long unsigned int* m_addr, uint8_t stream_n, uint8_t channel_n, uint16_t quant_d, uint8_t p_size, uint8_t m_size, uint8_t priority, uint8_t dir);
}STM32FXXX_DMA_func;
/*************************************/
/*************************************/
// DMA_Stream
typedef struct
{
	/*** Bit Mapping ***/
	STM32FXXX_DMA_STREAM_cr* cr;
	void (*ndt)(uint16_t value);
	void (*par)(volatile long unsigned int periferal_addr);
	void (*m0a)(volatile long unsigned int mem0_addr);
	void (*m1a)(volatile long unsigned int mem1_addr);
	STM32FXXX_DMA_STREAM_fcr* fcr;
	void (*nvic)(uint8_t state);
}STM32FXXX_DMA_Streamx;
// DMA
typedef struct
{
	STM32FXXX_DMA_Streamx* stream[8];
	/*** Bit Mapping ***/
	STM32FXXX_DMA_sr* sr;
	/*** Clock and Nvic ***/
	void (*clock)(uint8_t state);
	STM32FXXX_DMA_func* func;
}STM32FXXX_DMA, STM32FXXX_DMA1, STM32FXXX_DMA2;
/*************************************/
/*************************************/
void dma1_enable(void); STM32FXXX_DMA1* dma1(void);
void dma2_enable(void); STM32FXXX_DMA2* dma2(void);

/*** INTERRUPT HEADER ***/
void DMA1_Stream0_IRQHandler(void);
void DMA1_Stream1_IRQHandler(void);
void DMA1_Stream2_IRQHandler(void);
void DMA1_Stream3_IRQHandler(void);
void DMA1_Stream4_IRQHandler(void);
void DMA1_Stream5_IRQHandler(void);
void DMA1_Stream6_IRQHandler(void);
void DMA1_Stream7_IRQHandler(void);
void DMA2_Stream0_IRQHandler(void);
void DMA2_Stream1_IRQHandler(void);
void DMA2_Stream2_IRQHandler(void);
void DMA2_Stream3_IRQHandler(void);
void DMA2_Stream4_IRQHandler(void);
void DMA2_Stream5_IRQHandler(void);
void DMA2_Stream6_IRQHandler(void);
void DMA2_Stream7_IRQHandler(void);

#endif

/*** EOF ***/

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

