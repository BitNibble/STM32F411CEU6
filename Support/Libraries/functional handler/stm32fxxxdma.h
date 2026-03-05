/******************************************************************************
	STM32 XXX DMA
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 27062023
Comment:

*******************************************************************************/
#ifndef _STM32FXXXDMA_H_
	#define _STM32FXXXDMA_H_
/*** Library ***/
#include "stm32fxxxinstance.h"
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
}STM32FXXXDMA_sr;
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
}STM32FXXXDMA_STREAM_cr;
// FCR
typedef struct
{
	void (*feie)(uint8_t state);
	void (*fs)(uint8_t value);
	void (*dmdis)(uint8_t state);
	void (*fth)(uint8_t value);
}STM32FXXXDMA_STREAM_fcr;
// FUNC
typedef struct
{
	void (*circ_cfg)(volatile long unsigned int* p_addr, volatile long unsigned int* m_addr, uint8_t stream_n, uint8_t channel_n, uint16_t quant_d, uint8_t p_size, uint8_t m_size, uint8_t priority, uint8_t dir);
}STM32FXXXDMA_func;
/*************************************/
/*************************************/
// DMA_Stream
typedef struct
{
	DMA_Stream_TypeDef* instance;
	/*** Bit Mapping ***/
	STM32FXXXDMA_STREAM_cr* cr;
	void (*ndt)(uint16_t value);
	void (*par)(volatile long unsigned int periferal_addr);
	void (*m0a)(volatile long unsigned int mem0_addr);
	void (*m1a)(volatile long unsigned int mem1_addr);
	STM32FXXXDMA_STREAM_fcr* fcr;
	void (*nvic)(uint8_t state);
}STM32FXXXDMAStreamx;
// DMA
typedef struct
{
	DMA_TypeDef* instance;
	STM32FXXXDMAStreamx* stream[8];
	/*** Bit Mapping ***/
	STM32FXXXDMA_sr* sr;
	/*** Other ***/
	void (*clock)(uint8_t state);
	STM32FXXXDMA_func* func;
}STM32FXXX_DMA, STM32FXXX_DMA1, STM32FXXX_DMA2;
/*************************************/
/*************************************/
void dma1_enable(void);
STM32FXXX_DMA1* dma1(void);

void dma2_enable(void);
STM32FXXX_DMA2* dma2(void);
/***** DMA Procedure & Function Header ******/
/*** DMA ***/
void STM32FXXXDma1Clock(uint8_t state);
void STM32FXXXDma2Clock(uint8_t state);
/*** DMA1 Bit Mapping Header ***/
// SR
uint8_t STM32FXXXDMA1_sr_tcif(uint8_t stream_n);
void STM32FXXXDMA1_sr_clear_tcif(uint8_t stream_n);
uint8_t STM32FXXXDMA1_sr_htif(uint8_t stream_n);
void STM32FXXXDMA1_sr_clear_htif(uint8_t stream_n);
uint8_t STM32FXXXDMA1_sr_teif(uint8_t stream_n);
void STM32FXXXDMA1_sr_clear_teif(uint8_t stream_n);
uint8_t STM32FXXXDMA1_sr_dmeif(uint8_t stream_n);
void STM32FXXXDMA1_sr_clear_dmeif(uint8_t stream_n);
uint8_t STM32FXXXDMA1_sr_feif(uint8_t stream_n);
void STM32FXXXDMA1_sr_clear_feif(uint8_t stream_n);
// DMA1 STREAM0 CR
void STM32FXXXDMA1_stream0_cr_chsel(uint8_t value);
void STM32FXXXDMA1_stream0_cr_mburst(uint8_t value);
void STM32FXXXDMA1_stream0_cr_pburst(uint8_t value);
void STM32FXXXDMA1_stream0_cr_ct(uint8_t state);
void STM32FXXXDMA1_stream0_cr_dbm(uint8_t state);
void STM32FXXXDMA1_stream0_cr_pl(uint8_t value);
void STM32FXXXDMA1_stream0_cr_pincos(uint8_t state);
void STM32FXXXDMA1_stream0_cr_msize(uint8_t value);
void STM32FXXXDMA1_stream0_cr_psize(uint8_t value);
void STM32FXXXDMA1_stream0_cr_minc(uint8_t state);
void STM32FXXXDMA1_stream0_cr_pinc(uint8_t state);
void STM32FXXXDMA1_stream0_cr_circ(uint8_t state);
void STM32FXXXDMA1_stream0_cr_dir(uint8_t value);
void STM32FXXXDMA1_stream0_cr_pfctrl(uint8_t state);
void STM32FXXXDMA1_stream0_cr_tcie(uint8_t state);
void STM32FXXXDMA1_stream0_cr_htie(uint8_t state);
void STM32FXXXDMA1_stream0_cr_teie(uint8_t state);
void STM32FXXXDMA1_stream0_cr_dmeie(uint8_t state);
void STM32FXXXDMA1_stream0_cr_en(uint8_t state);
// DMA1 STREAM1 CR
void STM32FXXXDMA1_stream1_cr_chsel(uint8_t value);
void STM32FXXXDMA1_stream1_cr_mburst(uint8_t value);
void STM32FXXXDMA1_stream1_cr_pburst(uint8_t value);
void STM32FXXXDMA1_stream1_cr_ct(uint8_t state);
void STM32FXXXDMA1_stream1_cr_dbm(uint8_t state);
void STM32FXXXDMA1_stream1_cr_pl(uint8_t value);
void STM32FXXXDMA1_stream1_cr_pincos(uint8_t state);
void STM32FXXXDMA1_stream1_cr_msize(uint8_t value);
void STM32FXXXDMA1_stream1_cr_psize(uint8_t value);
void STM32FXXXDMA1_stream1_cr_minc(uint8_t state);
void STM32FXXXDMA1_stream1_cr_pinc(uint8_t state);
void STM32FXXXDMA1_stream1_cr_circ(uint8_t state);
void STM32FXXXDMA1_stream1_cr_dir(uint8_t value);
void STM32FXXXDMA1_stream1_cr_pfctrl(uint8_t state);
void STM32FXXXDMA1_stream1_cr_tcie(uint8_t state);
void STM32FXXXDMA1_stream1_cr_htie(uint8_t state);
void STM32FXXXDMA1_stream1_cr_teie(uint8_t state);
void STM32FXXXDMA1_stream1_cr_dmeie(uint8_t state);
void STM32FXXXDMA1_stream1_cr_en(uint8_t state);
// DMA1 STREAM2 CR
void STM32FXXXDMA1_stream2_cr_chsel(uint8_t value);
void STM32FXXXDMA1_stream2_cr_mburst(uint8_t value);
void STM32FXXXDMA1_stream2_cr_pburst(uint8_t value);
void STM32FXXXDMA1_stream2_cr_ct(uint8_t state);
void STM32FXXXDMA1_stream2_cr_dbm(uint8_t state);
void STM32FXXXDMA1_stream2_cr_pl(uint8_t value);
void STM32FXXXDMA1_stream2_cr_pincos(uint8_t state);
void STM32FXXXDMA1_stream2_cr_msize(uint8_t value);
void STM32FXXXDMA1_stream2_cr_psize(uint8_t value);
void STM32FXXXDMA1_stream2_cr_minc(uint8_t state);
void STM32FXXXDMA1_stream2_cr_pinc(uint8_t state);
void STM32FXXXDMA1_stream2_cr_circ(uint8_t state);
void STM32FXXXDMA1_stream2_cr_dir(uint8_t value);
void STM32FXXXDMA1_stream2_cr_pfctrl(uint8_t state);
void STM32FXXXDMA1_stream2_cr_tcie(uint8_t state);
void STM32FXXXDMA1_stream2_cr_htie(uint8_t state);
void STM32FXXXDMA1_stream2_cr_teie(uint8_t state);
void STM32FXXXDMA1_stream2_cr_dmeie(uint8_t state);
void STM32FXXXDMA1_stream2_cr_en(uint8_t state);
// DMA1 STREAM3 CR
void STM32FXXXDMA1_stream3_cr_chsel(uint8_t value);
void STM32FXXXDMA1_stream3_cr_mburst(uint8_t value);
void STM32FXXXDMA1_stream3_cr_pburst(uint8_t value);
void STM32FXXXDMA1_stream3_cr_ct(uint8_t state);
void STM32FXXXDMA1_stream3_cr_dbm(uint8_t state);
void STM32FXXXDMA1_stream3_cr_pl(uint8_t value);
void STM32FXXXDMA1_stream3_cr_pincos(uint8_t state);
void STM32FXXXDMA1_stream3_cr_msize(uint8_t value);
void STM32FXXXDMA1_stream3_cr_psize(uint8_t value);
void STM32FXXXDMA1_stream3_cr_minc(uint8_t state);
void STM32FXXXDMA1_stream3_cr_pinc(uint8_t state);
void STM32FXXXDMA1_stream3_cr_circ(uint8_t state);
void STM32FXXXDMA1_stream3_cr_dir(uint8_t value);
void STM32FXXXDMA1_stream3_cr_pfctrl(uint8_t state);
void STM32FXXXDMA1_stream3_cr_tcie(uint8_t state);
void STM32FXXXDMA1_stream3_cr_htie(uint8_t state);
void STM32FXXXDMA1_stream3_cr_teie(uint8_t state);
void STM32FXXXDMA1_stream3_cr_dmeie(uint8_t state);
void STM32FXXXDMA1_stream3_cr_en(uint8_t state);
// DMA1 STREAM4 CR
void STM32FXXXDMA1_stream4_cr_chsel(uint8_t value);
void STM32FXXXDMA1_stream4_cr_mburst(uint8_t value);
void STM32FXXXDMA1_stream4_cr_pburst(uint8_t value);
void STM32FXXXDMA1_stream4_cr_ct(uint8_t state);
void STM32FXXXDMA1_stream4_cr_dbm(uint8_t state);
void STM32FXXXDMA1_stream4_cr_pl(uint8_t value);
void STM32FXXXDMA1_stream4_cr_pincos(uint8_t state);
void STM32FXXXDMA1_stream4_cr_msize(uint8_t value);
void STM32FXXXDMA1_stream4_cr_psize(uint8_t value);
void STM32FXXXDMA1_stream4_cr_minc(uint8_t state);
void STM32FXXXDMA1_stream4_cr_pinc(uint8_t state);
void STM32FXXXDMA1_stream4_cr_circ(uint8_t state);
void STM32FXXXDMA1_stream4_cr_dir(uint8_t value);
void STM32FXXXDMA1_stream4_cr_pfctrl(uint8_t state);
void STM32FXXXDMA1_stream4_cr_tcie(uint8_t state);
void STM32FXXXDMA1_stream4_cr_htie(uint8_t state);
void STM32FXXXDMA1_stream4_cr_teie(uint8_t state);
void STM32FXXXDMA1_stream4_cr_dmeie(uint8_t state);
void STM32FXXXDMA1_stream4_cr_en(uint8_t state);
// DMA1 STREAM5 CR
void STM32FXXXDMA1_stream5_cr_chsel(uint8_t value);
void STM32FXXXDMA1_stream5_cr_mburst(uint8_t value);
void STM32FXXXDMA1_stream5_cr_pburst(uint8_t value);
void STM32FXXXDMA1_stream5_cr_ct(uint8_t state);
void STM32FXXXDMA1_stream5_cr_dbm(uint8_t state);
void STM32FXXXDMA1_stream5_cr_pl(uint8_t value);
void STM32FXXXDMA1_stream5_cr_pincos(uint8_t state);
void STM32FXXXDMA1_stream5_cr_msize(uint8_t value);
void STM32FXXXDMA1_stream5_cr_psize(uint8_t value);
void STM32FXXXDMA1_stream5_cr_minc(uint8_t state);
void STM32FXXXDMA1_stream5_cr_pinc(uint8_t state);
void STM32FXXXDMA1_stream5_cr_circ(uint8_t state);
void STM32FXXXDMA1_stream5_cr_dir(uint8_t value);
void STM32FXXXDMA1_stream5_cr_pfctrl(uint8_t state);
void STM32FXXXDMA1_stream5_cr_tcie(uint8_t state);
void STM32FXXXDMA1_stream5_cr_htie(uint8_t state);
void STM32FXXXDMA1_stream5_cr_teie(uint8_t state);
void STM32FXXXDMA1_stream5_cr_dmeie(uint8_t state);
void STM32FXXXDMA1_stream5_cr_en(uint8_t state);
// DMA1 STREAM6 CR
void STM32FXXXDMA1_stream6_cr_chsel(uint8_t value);
void STM32FXXXDMA1_stream6_cr_mburst(uint8_t value);
void STM32FXXXDMA1_stream6_cr_pburst(uint8_t value);
void STM32FXXXDMA1_stream6_cr_ct(uint8_t state);
void STM32FXXXDMA1_stream6_cr_dbm(uint8_t state);
void STM32FXXXDMA1_stream6_cr_pl(uint8_t value);
void STM32FXXXDMA1_stream6_cr_pincos(uint8_t state);
void STM32FXXXDMA1_stream6_cr_msize(uint8_t value);
void STM32FXXXDMA1_stream6_cr_psize(uint8_t value);
void STM32FXXXDMA1_stream6_cr_minc(uint8_t state);
void STM32FXXXDMA1_stream6_cr_pinc(uint8_t state);
void STM32FXXXDMA1_stream6_cr_circ(uint8_t state);
void STM32FXXXDMA1_stream6_cr_dir(uint8_t value);
void STM32FXXXDMA1_stream6_cr_pfctrl(uint8_t state);
void STM32FXXXDMA1_stream6_cr_tcie(uint8_t state);
void STM32FXXXDMA1_stream6_cr_htie(uint8_t state);
void STM32FXXXDMA1_stream6_cr_teie(uint8_t state);
void STM32FXXXDMA1_stream6_cr_dmeie(uint8_t state);
void STM32FXXXDMA1_stream6_cr_en(uint8_t state);
// DMA1 STREAM7 CR
void STM32FXXXDMA1_stream7_cr_chsel(uint8_t value);
void STM32FXXXDMA1_stream7_cr_mburst(uint8_t value);
void STM32FXXXDMA1_stream7_cr_pburst(uint8_t value);
void STM32FXXXDMA1_stream7_cr_ct(uint8_t state);
void STM32FXXXDMA1_stream7_cr_dbm(uint8_t state);
void STM32FXXXDMA1_stream7_cr_pl(uint8_t value);
void STM32FXXXDMA1_stream7_cr_pincos(uint8_t state);
void STM32FXXXDMA1_stream7_cr_msize(uint8_t value);
void STM32FXXXDMA1_stream7_cr_psize(uint8_t value);
void STM32FXXXDMA1_stream7_cr_minc(uint8_t state);
void STM32FXXXDMA1_stream7_cr_pinc(uint8_t state);
void STM32FXXXDMA1_stream7_cr_circ(uint8_t state);
void STM32FXXXDMA1_stream7_cr_dir(uint8_t value);
void STM32FXXXDMA1_stream7_cr_pfctrl(uint8_t state);
void STM32FXXXDMA1_stream7_cr_tcie(uint8_t state);
void STM32FXXXDMA1_stream7_cr_htie(uint8_t state);
void STM32FXXXDMA1_stream7_cr_teie(uint8_t state);
void STM32FXXXDMA1_stream7_cr_dmeie(uint8_t state);
void STM32FXXXDMA1_stream7_cr_en(uint8_t state);
// DMA1 STREAM0 FCR
void STM32FXXXDMA1_stream0_fcr_feie(uint8_t state);
void STM32FXXXDMA1_stream0_fcr_fs(uint8_t value);
void STM32FXXXDMA1_stream0_fcr_dmdis(uint8_t state);
void STM32FXXXDMA1_stream0_fcr_fth(uint8_t value);
// DMA1 STREAM1 FCR
void STM32FXXXDMA1_stream1_fcr_feie(uint8_t state);
void STM32FXXXDMA1_stream1_fcr_fs(uint8_t value);
void STM32FXXXDMA1_stream1_fcr_dmdis(uint8_t state);
void STM32FXXXDMA1_stream1_fcr_fth(uint8_t value);
// DMA1 STREAM2 FCR
void STM32FXXXDMA1_stream2_fcr_feie(uint8_t state);
void STM32FXXXDMA1_stream2_fcr_fs(uint8_t value);
void STM32FXXXDMA1_stream2_fcr_dmdis(uint8_t state);
void STM32FXXXDMA1_stream2_fcr_fth(uint8_t value);
// DMA1 STREAM3 FCR
void STM32FXXXDMA1_stream3_fcr_feie(uint8_t state);
void STM32FXXXDMA1_stream3_fcr_fs(uint8_t value);
void STM32FXXXDMA1_stream3_fcr_dmdis(uint8_t state);
void STM32FXXXDMA1_stream3_fcr_fth(uint8_t value);
// DMA1 STREAM4 FCR
void STM32FXXXDMA1_stream4_fcr_feie(uint8_t state);
void STM32FXXXDMA1_stream4_fcr_fs(uint8_t value);
void STM32FXXXDMA1_stream4_fcr_dmdis(uint8_t state);
void STM32FXXXDMA1_stream4_fcr_fth(uint8_t value);
// DMA1 STREAM5 FCR
void STM32FXXXDMA1_stream5_fcr_feie(uint8_t state);
void STM32FXXXDMA1_stream5_fcr_fs(uint8_t value);
void STM32FXXXDMA1_stream5_fcr_dmdis(uint8_t state);
void STM32FXXXDMA1_stream5_fcr_fth(uint8_t value);
// DMA1 STREAM6 FCR
void STM32FXXXDMA1_stream6_fcr_feie(uint8_t state);
void STM32FXXXDMA1_stream6_fcr_fs(uint8_t value);
void STM32FXXXDMA1_stream6_fcr_dmdis(uint8_t state);
void STM32FXXXDMA1_stream6_fcr_fth(uint8_t value);
// DMA1 STREAM7 FCR
void STM32FXXXDMA1_stream7_fcr_feie(uint8_t state);
void STM32FXXXDMA1_stream7_fcr_fs(uint8_t value);
void STM32FXXXDMA1_stream7_fcr_dmdis(uint8_t state);
void STM32FXXXDMA1_stream7_fcr_fth(uint8_t value);
// FUNC
void dma1_circ_cfg(volatile long unsigned int* p_addr, volatile long unsigned int* m_addr, uint8_t stream_n, uint8_t channel_n, uint16_t quant_d, uint8_t p_size, uint8_t m_size, uint8_t priority, uint8_t dir);
/*** DMA2 Bit Mapping Header ***/
// SR
uint8_t STM32FXXXDMA2_sr_tcif(uint8_t stream_n);
void STM32FXXXDMA2_sr_clear_tcif(uint8_t stream_n);
uint8_t STM32FXXXDMA2_sr_htif(uint8_t stream_n);
void STM32FXXXDMA2_sr_clear_htif(uint8_t stream_n);
uint8_t STM32FXXXDMA2_sr_teif(uint8_t stream_n);
void STM32FXXXDMA2_sr_clear_teif(uint8_t stream_n);
uint8_t STM32FXXXDMA2_sr_dmeif(uint8_t stream_n);
void STM32FXXXDMA2_sr_clear_dmeif(uint8_t stream_n);
uint8_t STM32FXXXDMA2_sr_feif(uint8_t stream_n);
void STM32FXXXDMA2_sr_clear_feif(uint8_t stream_n);
// DMA2 STREAM0 CR
void STM32FXXXDMA2_stream0_cr_chsel(uint8_t value);
void STM32FXXXDMA2_stream0_cr_mburst(uint8_t value);
void STM32FXXXDMA2_stream0_cr_pburst(uint8_t value);
void STM32FXXXDMA2_stream0_cr_ct(uint8_t state);
void STM32FXXXDMA2_stream0_cr_dbm(uint8_t state);
void STM32FXXXDMA2_stream0_cr_pl(uint8_t value);
void STM32FXXXDMA2_stream0_cr_pincos(uint8_t state);
void STM32FXXXDMA2_stream0_cr_msize(uint8_t value);
void STM32FXXXDMA2_stream0_cr_psize(uint8_t value);
void STM32FXXXDMA2_stream0_cr_minc(uint8_t state);
void STM32FXXXDMA2_stream0_cr_pinc(uint8_t state);
void STM32FXXXDMA2_stream0_cr_circ(uint8_t state);
void STM32FXXXDMA2_stream0_cr_dir(uint8_t value);
void STM32FXXXDMA2_stream0_cr_pfctrl(uint8_t state);
void STM32FXXXDMA2_stream0_cr_tcie(uint8_t state);
void STM32FXXXDMA2_stream0_cr_htie(uint8_t state);
void STM32FXXXDMA2_stream0_cr_teie(uint8_t state);
void STM32FXXXDMA2_stream0_cr_dmeie(uint8_t state);
void STM32FXXXDMA2_stream0_cr_en(uint8_t state);
// DMA2 STREAM1 CR
void STM32FXXXDMA2_stream1_cr_chsel(uint8_t value);
void STM32FXXXDMA2_stream1_cr_mburst(uint8_t value);
void STM32FXXXDMA2_stream1_cr_pburst(uint8_t value);
void STM32FXXXDMA2_stream1_cr_ct(uint8_t state);
void STM32FXXXDMA2_stream1_cr_dbm(uint8_t state);
void STM32FXXXDMA2_stream1_cr_pl(uint8_t value);
void STM32FXXXDMA2_stream1_cr_pincos(uint8_t state);
void STM32FXXXDMA2_stream1_cr_msize(uint8_t value);
void STM32FXXXDMA2_stream1_cr_psize(uint8_t value);
void STM32FXXXDMA2_stream1_cr_minc(uint8_t state);
void STM32FXXXDMA2_stream1_cr_pinc(uint8_t state);
void STM32FXXXDMA2_stream1_cr_circ(uint8_t state);
void STM32FXXXDMA2_stream1_cr_dir(uint8_t value);
void STM32FXXXDMA2_stream1_cr_pfctrl(uint8_t state);
void STM32FXXXDMA2_stream1_cr_tcie(uint8_t state);
void STM32FXXXDMA2_stream1_cr_htie(uint8_t state);
void STM32FXXXDMA2_stream1_cr_teie(uint8_t state);
void STM32FXXXDMA2_stream1_cr_dmeie(uint8_t state);
void STM32FXXXDMA2_stream1_cr_en(uint8_t state);
// DMA2 STREAM2 CR
void STM32FXXXDMA2_stream2_cr_chsel(uint8_t value);
void STM32FXXXDMA2_stream2_cr_mburst(uint8_t value);
void STM32FXXXDMA2_stream2_cr_pburst(uint8_t value);
void STM32FXXXDMA2_stream2_cr_ct(uint8_t state);
void STM32FXXXDMA2_stream2_cr_dbm(uint8_t state);
void STM32FXXXDMA2_stream2_cr_pl(uint8_t value);
void STM32FXXXDMA2_stream2_cr_pincos(uint8_t state);
void STM32FXXXDMA2_stream2_cr_msize(uint8_t value);
void STM32FXXXDMA2_stream2_cr_psize(uint8_t value);
void STM32FXXXDMA2_stream2_cr_minc(uint8_t state);
void STM32FXXXDMA2_stream2_cr_pinc(uint8_t state);
void STM32FXXXDMA2_stream2_cr_circ(uint8_t state);
void STM32FXXXDMA2_stream2_cr_dir(uint8_t value);
void STM32FXXXDMA2_stream2_cr_pfctrl(uint8_t state);
void STM32FXXXDMA2_stream2_cr_tcie(uint8_t state);
void STM32FXXXDMA2_stream2_cr_htie(uint8_t state);
void STM32FXXXDMA2_stream2_cr_teie(uint8_t state);
void STM32FXXXDMA2_stream2_cr_dmeie(uint8_t state);
void STM32FXXXDMA2_stream2_cr_en(uint8_t state);
// DMA2 STREAM3 CR
void STM32FXXXDMA2_stream3_cr_chsel(uint8_t value);
void STM32FXXXDMA2_stream3_cr_mburst(uint8_t value);
void STM32FXXXDMA2_stream3_cr_pburst(uint8_t value);
void STM32FXXXDMA2_stream3_cr_ct(uint8_t state);
void STM32FXXXDMA2_stream3_cr_dbm(uint8_t state);
void STM32FXXXDMA2_stream3_cr_pl(uint8_t value);
void STM32FXXXDMA2_stream3_cr_pincos(uint8_t state);
void STM32FXXXDMA2_stream3_cr_msize(uint8_t value);
void STM32FXXXDMA2_stream3_cr_psize(uint8_t value);
void STM32FXXXDMA2_stream3_cr_minc(uint8_t state);
void STM32FXXXDMA2_stream3_cr_pinc(uint8_t state);
void STM32FXXXDMA2_stream3_cr_circ(uint8_t state);
void STM32FXXXDMA2_stream3_cr_dir(uint8_t value);
void STM32FXXXDMA2_stream3_cr_pfctrl(uint8_t state);
void STM32FXXXDMA2_stream3_cr_tcie(uint8_t state);
void STM32FXXXDMA2_stream3_cr_htie(uint8_t state);
void STM32FXXXDMA2_stream3_cr_teie(uint8_t state);
void STM32FXXXDMA2_stream3_cr_dmeie(uint8_t state);
void STM32FXXXDMA2_stream3_cr_en(uint8_t state);
// DMA2 STREAM4 CR
void STM32FXXXDMA2_stream4_cr_chsel(uint8_t value);
void STM32FXXXDMA2_stream4_cr_mburst(uint8_t value);
void STM32FXXXDMA2_stream4_cr_pburst(uint8_t value);
void STM32FXXXDMA2_stream4_cr_ct(uint8_t state);
void STM32FXXXDMA2_stream4_cr_dbm(uint8_t state);
void STM32FXXXDMA2_stream4_cr_pl(uint8_t value);
void STM32FXXXDMA2_stream4_cr_pincos(uint8_t state);
void STM32FXXXDMA2_stream4_cr_msize(uint8_t value);
void STM32FXXXDMA2_stream4_cr_psize(uint8_t value);
void STM32FXXXDMA2_stream4_cr_minc(uint8_t state);
void STM32FXXXDMA2_stream4_cr_pinc(uint8_t state);
void STM32FXXXDMA2_stream4_cr_circ(uint8_t state);
void STM32FXXXDMA2_stream4_cr_dir(uint8_t value);
void STM32FXXXDMA2_stream4_cr_pfctrl(uint8_t state);
void STM32FXXXDMA2_stream4_cr_tcie(uint8_t state);
void STM32FXXXDMA2_stream4_cr_htie(uint8_t state);
void STM32FXXXDMA2_stream4_cr_teie(uint8_t state);
void STM32FXXXDMA2_stream4_cr_dmeie(uint8_t state);
void STM32FXXXDMA2_stream4_cr_en(uint8_t state);
// DMA2 STREAM5 CR
void STM32FXXXDMA2_stream5_cr_chsel(uint8_t value);
void STM32FXXXDMA2_stream5_cr_mburst(uint8_t value);
void STM32FXXXDMA2_stream5_cr_pburst(uint8_t value);
void STM32FXXXDMA2_stream5_cr_ct(uint8_t state);
void STM32FXXXDMA2_stream5_cr_dbm(uint8_t state);
void STM32FXXXDMA2_stream5_cr_pl(uint8_t value);
void STM32FXXXDMA2_stream5_cr_pincos(uint8_t state);
void STM32FXXXDMA2_stream5_cr_msize(uint8_t value);
void STM32FXXXDMA2_stream5_cr_psize(uint8_t value);
void STM32FXXXDMA2_stream5_cr_minc(uint8_t state);
void STM32FXXXDMA2_stream5_cr_pinc(uint8_t state);
void STM32FXXXDMA2_stream5_cr_circ(uint8_t state);
void STM32FXXXDMA2_stream5_cr_dir(uint8_t value);
void STM32FXXXDMA2_stream5_cr_pfctrl(uint8_t state);
void STM32FXXXDMA2_stream5_cr_tcie(uint8_t state);
void STM32FXXXDMA2_stream5_cr_htie(uint8_t state);
void STM32FXXXDMA2_stream5_cr_teie(uint8_t state);
void STM32FXXXDMA2_stream5_cr_dmeie(uint8_t state);
void STM32FXXXDMA2_stream5_cr_en(uint8_t state);
// DMA2 STREAM6 CR
void STM32FXXXDMA2_stream6_cr_chsel(uint8_t value);
void STM32FXXXDMA2_stream6_cr_mburst(uint8_t value);
void STM32FXXXDMA2_stream6_cr_pburst(uint8_t value);
void STM32FXXXDMA2_stream6_cr_ct(uint8_t state);
void STM32FXXXDMA2_stream6_cr_dbm(uint8_t state);
void STM32FXXXDMA2_stream6_cr_pl(uint8_t value);
void STM32FXXXDMA2_stream6_cr_pincos(uint8_t state);
void STM32FXXXDMA2_stream6_cr_msize(uint8_t value);
void STM32FXXXDMA2_stream6_cr_psize(uint8_t value);
void STM32FXXXDMA2_stream6_cr_minc(uint8_t state);
void STM32FXXXDMA2_stream6_cr_pinc(uint8_t state);
void STM32FXXXDMA2_stream6_cr_circ(uint8_t state);
void STM32FXXXDMA2_stream6_cr_dir(uint8_t value);
void STM32FXXXDMA2_stream6_cr_pfctrl(uint8_t state);
void STM32FXXXDMA2_stream6_cr_tcie(uint8_t state);
void STM32FXXXDMA2_stream6_cr_htie(uint8_t state);
void STM32FXXXDMA2_stream6_cr_teie(uint8_t state);
void STM32FXXXDMA2_stream6_cr_dmeie(uint8_t state);
void STM32FXXXDMA2_stream6_cr_en(uint8_t state);
// DMA2 STREAM7 CR
void STM32FXXXDMA2_stream7_cr_chsel(uint8_t value);
void STM32FXXXDMA2_stream7_cr_mburst(uint8_t value);
void STM32FXXXDMA2_stream7_cr_pburst(uint8_t value);
void STM32FXXXDMA2_stream7_cr_ct(uint8_t state);
void STM32FXXXDMA2_stream7_cr_dbm(uint8_t state);
void STM32FXXXDMA2_stream7_cr_pl(uint8_t value);
void STM32FXXXDMA2_stream7_cr_pincos(uint8_t state);
void STM32FXXXDMA2_stream7_cr_msize(uint8_t value);
void STM32FXXXDMA2_stream7_cr_psize(uint8_t value);
void STM32FXXXDMA2_stream7_cr_minc(uint8_t state);
void STM32FXXXDMA2_stream7_cr_pinc(uint8_t state);
void STM32FXXXDMA2_stream7_cr_circ(uint8_t state);
void STM32FXXXDMA2_stream7_cr_dir(uint8_t value);
void STM32FXXXDMA2_stream7_cr_pfctrl(uint8_t state);
void STM32FXXXDMA2_stream7_cr_tcie(uint8_t state);
void STM32FXXXDMA2_stream7_cr_htie(uint8_t state);
void STM32FXXXDMA2_stream7_cr_teie(uint8_t state);
void STM32FXXXDMA2_stream7_cr_dmeie(uint8_t state);
void STM32FXXXDMA2_stream7_cr_en(uint8_t state);
// DMA2 STREAM0 FCR
void STM32FXXXDMA2_stream0_fcr_feie(uint8_t state);
void STM32FXXXDMA2_stream0_fcr_fs(uint8_t value);
void STM32FXXXDMA2_stream0_fcr_dmdis(uint8_t state);
void STM32FXXXDMA2_stream0_fcr_fth(uint8_t value);
// DMA2 STREAM1 FCR
void STM32FXXXDMA2_stream1_fcr_feie(uint8_t state);
void STM32FXXXDMA2_stream1_fcr_fs(uint8_t value);
void STM32FXXXDMA2_stream1_fcr_dmdis(uint8_t state);
void STM32FXXXDMA2_stream1_fcr_fth(uint8_t value);
// DMA2 STREAM2 FCR
void STM32FXXXDMA2_stream2_fcr_feie(uint8_t state);
void STM32FXXXDMA2_stream2_fcr_fs(uint8_t value);
void STM32FXXXDMA2_stream2_fcr_dmdis(uint8_t state);
void STM32FXXXDMA2_stream2_fcr_fth(uint8_t value);
// DMA2 STREAM3 FCR
void STM32FXXXDMA2_stream3_fcr_feie(uint8_t state);
void STM32FXXXDMA2_stream3_fcr_fs(uint8_t value);
void STM32FXXXDMA2_stream3_fcr_dmdis(uint8_t state);
void STM32FXXXDMA2_stream3_fcr_fth(uint8_t value);
// DMA2 STREAM4 FCR
void STM32FXXXDMA2_stream4_fcr_feie(uint8_t state);
void STM32FXXXDMA2_stream4_fcr_fs(uint8_t value);
void STM32FXXXDMA2_stream4_fcr_dmdis(uint8_t state);
void STM32FXXXDMA2_stream4_fcr_fth(uint8_t value);
// DMA2 STREAM5 FCR
void STM32FXXXDMA2_stream5_fcr_feie(uint8_t state);
void STM32FXXXDMA2_stream5_fcr_fs(uint8_t value);
void STM32FXXXDMA2_stream5_fcr_dmdis(uint8_t state);
void STM32FXXXDMA2_stream5_fcr_fth(uint8_t value);
// DMA2 STREAM6 FCR
void STM32FXXXDMA2_stream6_fcr_feie(uint8_t state);
void STM32FXXXDMA2_stream6_fcr_fs(uint8_t value);
void STM32FXXXDMA2_stream6_fcr_dmdis(uint8_t state);
void STM32FXXXDMA2_stream6_fcr_fth(uint8_t value);
// DMA2 STREAM7 FCR
void STM32FXXXDMA2_stream7_fcr_feie(uint8_t state);
void STM32FXXXDMA2_stream7_fcr_fs(uint8_t value);
void STM32FXXXDMA2_stream7_fcr_dmdis(uint8_t state);
void STM32FXXXDMA2_stream7_fcr_fth(uint8_t value);
// FUNC
void dma2_circ_cfg(volatile long unsigned int* p_addr, volatile long unsigned int* m_addr, uint8_t stream_n, uint8_t channel_n, uint16_t quant_d, uint8_t p_size, uint8_t m_size, uint8_t priority, uint8_t dir);

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

