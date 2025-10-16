/******************************************************************************
	STM32 FXXX RCC
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-FXXX
Date:     07032024
*******************************************************************************/
/*** File Library ***/
#include <stm32fxxxrcc.h>
#include "stm32fxxxnvic.h"

/*** File Procedure & Function Header ***/
void RCC_PWR_clock(uint8_t state);
void RCC_Write_enable(void);
void RCC_Write_disable(void);
uint8_t RCC_PLL_select(uint8_t hclock);

/*******   0 -> HSI    1->HSE   *********/
#ifndef H_Clock_Source
	#define H_Clock_Source 0
#endif
/****************************************/
/****   PLL ON -> 1    PLL OFF = 0   ****/
#ifndef PLL_ON_OFF
	#define PLL_ON_OFF 0
#endif
/****************************************/

/*** RCC Procedure & Function Definition ***/
// RCC
void RCC_H_enable(uint8_t hclock)
{
    uint8_t set = 1;
    uint8_t rdy = 1;

    // Enable CSSON
    set_reg_block(&RCC->CR, 1, RCC_CR_CSSON_Pos, 1); // Clock security system enable

    while(rdy)
    {
        switch(hclock)
        {
            case 0: // HSION: Internal high-speed clock enable
                if(set) {
                    RCC->CR |= (1 << RCC_CR_HSION_Pos); // Enable HSI
                    set = 0;
                }
                else if(RCC->CR & (1 << RCC_CR_HSIRDY_Pos)) // Wait for HSIRDY
                    rdy = 0;
                break;

            case 1: // HSEON: External high-speed clock enable
                if(set) {
                    RCC->CR |= (1 << RCC_CR_HSEON_Pos); // Enable HSE
                    set = 0;
                }
                else if(RCC->CR & (1 << RCC_CR_HSERDY_Pos)) // Wait for HSERDY
                    rdy = 0;
                break;

            case 2: // HSEBYP: HSE clock bypass
                if(set) {
                    RCC->CR |= (1 << RCC_CR_HSEBYP_Pos); // Enable HSE bypass
                    set = 0;
                }
                hclock = 1; // Switch to enabling HSE
                break;

            default: // Invalid value, default to HSI
                hclock = 0;
                break;
        }
    }
}
void RCC_H_select(uint8_t hclock)
{
    switch(hclock){
        case 0: // HSI selected as system clock
            set_reg_block(&RCC->CFGR, 2, RCC_CFGR_SW_Pos, 0);
            break;

        case 1: // HSE oscillator selected as system clock
            set_reg_block(&RCC->CFGR, 2, RCC_CFGR_SW_Pos, 1);
            break;

        case 2: // PLL_P selected as system clock
            set_reg_block(&RCC->CFGR, 2, RCC_CFGR_SW_Pos, 2);
            break;

        case 3: // PLL_R selected as system clock (only on STM32F446xx)
            #ifdef STM32F446xx
                set_reg_block(&RCC->CFGR, 2, RCC_CFGR_SW_Pos, 3);
            #else
                set_reg_block(&RCC->CFGR, 2, RCC_CFGR_SW_Pos, 0); // Default to HSI if not STM32F446
            #endif
            break;

        default: // Default to HSI (00) if an invalid value is passed
            set_reg_block(&RCC->CFGR, 2, RCC_CFGR_SW_Pos, 0);
            break;
    }
}
uint8_t RCC_PLL_select(uint8_t hclock)
{ // This bit can be written only when PLL and PLLI2S are disabled
	set_reg_block(&RCC->CR, 1, RCC_CR_PLLON_Pos, 0); set_reg_block(&RCC->CR, 1, RCC_CR_PLLI2SON_Pos, 0);
	switch(hclock){
		case 0: // HSI
			set_reg_block(&RCC->PLLCFGR, 1, RCC_PLLCFGR_PLLSRC_Pos, 0);
		break;
		case 1: // HSE
			set_reg_block(&RCC->PLLCFGR, 1, RCC_PLLCFGR_PLLSRC_Pos, 1);
		break;
		default: // HSI
			set_reg_block(&RCC->PLLCFGR, 1, RCC_PLLCFGR_PLLSRC_Pos, 0);
		break;
	}
	return get_reg_block(RCC->PLLCFGR, 1, RCC_PLLCFGR_PLLSRC_Pos);
}
void RCC_L_enable(uint8_t lclock)
{
    uint8_t set = 1;
    uint8_t rdy = 1;
    RCC_PWR_clock(1);

    while(rdy)
    {
        switch(lclock)
        {
            case 0: // LSION: Internal low-speed oscillator enable
                if(set)
                {
                    RCC->CSR |= (1 << RCC_CSR_LSION_Pos); // Enable LSI
                    set = 0;
                }
                else if(RCC->CSR & (1 << RCC_CSR_LSIRDY_Pos)) // Wait for LSIRDY
                {
                    rdy = 0; // LSI ready
                }
                break;

            case 1: // LSEON: External low-speed oscillator enable
                if(set)
                {
                    RCC_Write_enable();
                    RCC->BDCR |= (1 << RCC_BDCR_LSEON_Pos); // Enable LSE
                    RCC_Write_disable();
                    set = 0;
                }
                else if(RCC->BDCR & (1 << RCC_BDCR_LSERDY_Pos)) // Wait for LSERDY
                {
                    rdy = 0; // LSE ready
                }
                break;

            case 2: // LSEBYP: External low-speed oscillator bypass
                if(set)
                {
                    RCC_Write_enable();
                    RCC->BDCR |= (1 << RCC_BDCR_LSEBYP_Pos); // Enable LSE bypass
                    RCC_Write_disable();
                    set = 0;
                }
                lclock = 1; // Switch to enabling LSE
                break;

            default: // Default to enabling LSI (0)
                lclock = 0;
                break;
        }
    }
}
void RCC_L_select(uint8_t lclock)
{
	RCC_PWR_clock(1);
	RCC_Write_enable(); // Enable write access to the backup domain

	switch(lclock)
	{
		case 0: // LSI oscillator clock used as the RTC clock
			set_reg_block(&RCC->BDCR, 2, RCC_BDCR_RTCSEL_Pos, 2);
			break;

		case 1: // LSE oscillator clock used as the RTC clock
			set_reg_block(&RCC->BDCR, 2, RCC_BDCR_RTCSEL_Pos, 1);
			break;

		case 2: // HSE oscillator clock divided by a programmable prescaler
			set_reg_block(&RCC->BDCR, 2, RCC_BDCR_RTCSEL_Pos, 3);
			break;

		default: // Default to LSE oscillator clock
			set_reg_block(&RCC->BDCR, 2, RCC_BDCR_RTCSEL_Pos, 1);
			break;
	}

	RCC_Write_disable(); // Disable write access to the backup domain
}

// Helper to map prescaler to CFGR bits
static uint8_t _ahb_prescaler_bits(uint16_t ahbpre) {
    switch(ahbpre) {
        case 2:   return 8;
        case 4:   return 9;
        case 8:   return 10;
        case 16:  return 11;
        case 64:  return 12;
        case 128: return 13;
        case 256: return 14;
        case 512: return 15;
        default:  return 0;
    }
}

static uint8_t _apb_prescaler_bits(uint8_t ppre) {
    switch(ppre) {
        case 2:   return 4;
        case 4:   return 5;
        case 8:   return 6;
        case 16:  return 7;
        default:  return 0;
    }
}

// Function to set AHB prescaler
void RCC_Set_AHBPrescaler(uint16_t ahbpre) {
    set_reg_block(&RCC->CFGR, 4, RCC_CFGR_HPRE_Pos, _ahb_prescaler_bits(ahbpre));
}

// Function to set APB1 prescaler
void RCC_Set_APB1Prescaler(uint8_t ppre1) {
    set_reg_block(&RCC->CFGR, 3, RCC_CFGR_PPRE1_Pos, _apb_prescaler_bits(ppre1));
}

// Function to set APB2 prescaler
void RCC_Set_APB2Prescaler(uint8_t ppre2) {
    set_reg_block(&RCC->CFGR, 3, RCC_CFGR_PPRE2_Pos, _apb_prescaler_bits(ppre2));
}

// Function to set RTC prescaler
void RCC_Set_RTCPre(uint8_t rtcpre) {
    set_reg_block(&RCC->CFGR, 5, RCC_CFGR_RTCPRE_Pos, rtcpre);
}

// Main prescaler setup function
void RCC_Prescaler(uint16_t ahbpre, uint8_t ppre1, uint8_t ppre2, uint8_t rtcpre) {
    RCC_Set_AHBPrescaler(ahbpre);
    RCC_Set_APB1Prescaler(ppre1);
    RCC_Set_APB2Prescaler(ppre2);
    RCC_Set_RTCPre(rtcpre);
}

// Set PLLM
void RCC_Set_PLLM(uint8_t pllm) {
    set_reg_block(&RCC->PLLCFGR, 6, RCC_PLLCFGR_PLLM_Pos, pllm);
}

// Set PLLN
void RCC_Set_PLLN(uint16_t plln) {
    set_reg_block(&RCC->PLLCFGR, 9, RCC_PLLCFGR_PLLN_Pos, plln);
}

// Set PLLP
void RCC_Set_PLLP(uint8_t pllp) {
    uint8_t bits;
    switch(pllp){
        case 2: bits = 0; break;
        case 4: bits = 1; break;
        case 6: bits = 2; break;
        case 8: bits = 3; break;
        default: bits = 0; break; // default 2
    }
    set_reg_block(&RCC->PLLCFGR, 2, RCC_PLLCFGR_PLLP_Pos, bits);
}

// Set PLLQ
void RCC_Set_PLLQ(uint8_t pllq) {
    set_reg_block(&RCC->PLLCFGR, 4, RCC_PLLCFGR_PLLQ_Pos, pllq);
}

// Enable/Disable PLL
void RCC_PLL_enable(uint8_t enable) {
    set_reg_block(&RCC->CR, 1, RCC_CR_PLLON_Pos, enable ? 1 : 0);
}

// Main PLL configuration
void RCC_PLL_division(uint8_t pllm, uint16_t plln, uint8_t pllp, uint8_t pllq) {
    RCC_PLL_enable(0);      // Turn off PLL before configuring
    RCC_Set_PLLQ(pllq);
    RCC_Set_PLLP(pllp);
    RCC_Set_PLLN(plln);
    RCC_Set_PLLM(pllm);
    // Optionally re-enable PLL here if needed:
    // RCC_PLL_enable(1);
}

void RCC_PLLCLK_enable(void)
{
	volatile uint32_t rcc_time_out;
	//if(onoff){
		for( rcc_time_out = 0xFFFFFF, RCC->CR |= (1 << RCC_CR_PLLON_Pos) ; !(RCC->CR & (1 << RCC_CR_PLLRDY_Pos)) && rcc_time_out; rcc_time_out-- ); // PLLON: Main PLL (PLL) enable
	//}else{
		//RCC->CR &= (unsigned int) ~(1 << 24);
	//}
}
void RCC_PLLI2S_enable(void)
{
	volatile uint32_t rcc_time_out;
	//if(onoff)
		for( rcc_time_out = 0xFFFFFF, RCC->CR |= (1 << RCC_CR_PLLI2SON_Pos) ; !(RCC->CR & (1 << RCC_CR_PLLI2SRDY_Pos)) && rcc_time_out; rcc_time_out-- ); // PLLI2SON: PLLI2S enable
	//else
		//RCC->CR &= (unsigned int) ~(1 << 26);
}
#ifdef STM32F446xx
	void RCC_PLLSAI_enable(void)
	{
		volatile uint32_t rcc_time_out;
		//if(onoff)
		for( rcc_time_out = 0xFFFFFF, RCC->CR |= (1 << RCC_CR_PLLSAION_Pos) ; !(RCC->CR & (1 << RCC_CR_PLLSAIRDY_Pos)) && rcc_time_out; rcc_time_out-- ); // PLLSAION: PLLSAI enable
		//else
		//RCC->CR &= (unsigned int) ~(1 << 28);
	}
#endif
void RCC_PWR_clock(uint8_t state)
{
	set_reg_block(&RCC->APB1ENR, 1, RCC_APB1ENR_PWREN_Pos, state); // Power interface clock enable
}
void RCC_Write_enable(void)
{
	PWR->CR |= (1 << PWR_CR_DBP_Pos); // Disable protection
}
void RCC_Write_disable(void)
{
	PWR->CR &= (uint32_t) ~(1 << PWR_CR_DBP_Pos); // Enable protection
}
/*** Other ***/
void RCC_nvic(uint8_t state)
{
	if(state){ set_bit_block(NVIC->ISER, 1, RCC_IRQn, 1); } else{ set_bit_block(NVIC->ICER, 1, RCC_IRQn, 1); }
}
/*** Extended ***/
static STM32FXXX_RCC_PLL stm32fxxx_rcc_pll = {

	.division = RCC_PLL_division,
	.enable = RCC_PLLCLK_enable
};

static STM32FXXX_RCC_PLLI2S stm32fxxx_rcc_plli2s = {

	.enable = RCC_PLLI2S_enable
};

#ifdef STM32F446xx
	static STM32FXXX_RCC_PLLSAI stm32fxxx_rcc_pllsai = {
		.enable = RCC_PLLSAI_enable,
	}
#endif

/*** System Clock Init ***/
void RCC_default(void)
{	// Configure -> Enable -> Select
	// AHB 1,2,4,8,16,64,128,256,512;  APB1 1,2,4,8,16;  APB2 1,2,4,8,16;  RTC 2 to 31
	//STM32FXXXPrescaler(8, 1, 1, 1); // (8, 1, 1, 0)
	RCC_Prescaler(1, 1, 1, 0); // (1, 1, 1, 0)
	RCC_H_enable(H_Clock_Source); // 0 - HSI, 1 - HSE
	RCC_PLL_select(H_Clock_Source); // 0 - HSI, 1 - HSE, H_Clock_Source
	// M 2 to 63;  N 50 to 432;  P 2,4,6,8;  Q 2 to 15;
	RCC_PLL_division((uint32_t)get_pllsourceclk()/1000000, 240, 2, 4);
	if(PLL_ON_OFF){
		RCC_PLLCLK_enable();
		// System Clock Switch
		RCC_H_select(2); // 0 - HSI, 1 - HSE, 2 - PLL_P, 3 - PLL_R pg133 (manual 2) SW[1:0]: System clock switch
	}else{
		// System Clock Switch
		RCC_H_select(H_Clock_Source); // 0 - HSI, 1 - HSE, 2 - PLL_P, 3 - PLL_R pg133 (manual 2) SW[1:0]: System clock switch
	}
}

/*** INIC Procedure & Function Definition ***/
static	RCC_Callback RCC_Callback_setup = {0};

static STM32FXXX_RCC_Handler stm32fxxx_rcc_setup = {
	.inic = RCC_default,
	/*** RCC Bit Mapping Link ***/
	.prescaler = RCC_Prescaler,
	/*** PLL ***/
	.pll = &stm32fxxx_rcc_pll,
	.plli2s = &stm32fxxx_rcc_plli2s,
	#ifdef STM32F446xx
		.pllsai = &stm32fxxx_rcc_pllsai,
	#else
		.pllsai = NULL,
	#endif
	/*** Other ***/
	.h_enable = RCC_H_enable,
	.h_select = RCC_H_select,
	.l_enable = RCC_L_enable,
	.l_select = RCC_L_select,
	/*** Clock and Nvic ***/
	.nvic = RCC_nvic,
	.callback = &RCC_Callback_setup,

#if defined(STM32F411CEU6_H)
	.dev = stm32f411ceu6
#endif
};

STM32FXXX_RCC_Handler* rcc(void){ return &stm32fxxx_rcc_setup; };

/*** Interrupt ***/
void RCC_IRQHandler(void)
{
	RCC_Callback* cb = rcc()->callback;
    uint32_t status = RCC->CIR;
    uint32_t mask   = status & 0xFF; // lower bits are flags

    // LSI Ready
    if (status & RCC_CIR_LSIRDYF) {
        RCC->CIR = RCC_CIR_LSIRDYC; // clear
        if (cb->lsi_ready) cb->lsi_ready();
    }

    // LSE Ready
    if (status & RCC_CIR_LSERDYF) {
        RCC->CIR = RCC_CIR_LSERDYC;
        if (cb->lse_ready) cb->lse_ready();
    }

    // HSI Ready
    if (status & RCC_CIR_HSIRDYF) {
        RCC->CIR = RCC_CIR_HSIRDYC;
        if (cb->hsi_ready) cb->hsi_ready();
    }

    // HSE Ready
    if (status & RCC_CIR_HSERDYF) {
        RCC->CIR = RCC_CIR_HSERDYC;
        if (cb->hse_ready) cb->hse_ready();
    }

    // PLL Ready
    if (status & RCC_CIR_PLLRDYF) {
        RCC->CIR = RCC_CIR_PLLRDYC;
        if (cb->pll_ready) cb->pll_ready();
    }

    // PLLI2S Ready
    if (status & RCC_CIR_PLLI2SRDYF) {
        RCC->CIR = RCC_CIR_PLLI2SRDYC;
        if (cb->plli2s_ready) cb->plli2s_ready();
    }

    // Clock Security System Fault
    if (status & RCC_CIR_CSSF) {
        RCC->CIR = RCC_CIR_CSSC;
        if (cb->css_fault) cb->css_fault();
    }

    (void)mask; // silence unused variable warning
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

