/******************************************************************************
	STM32 FXXX RCC
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-FXXX
Date:     07032024
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include <stm32fxxxrcc.h>

/*** File Variables ***/
static STM32FXXX_RCC_PLL stm32fxxx_rcc_pll = {0};
static STM32FXXX_RCC_PLLI2S stm32fxxx_rcc_plli2s = {0};
#ifdef STM32F446xx
	static STM32FXXX_RCC_PLLSAI stm32fxxx_rcc_pllsai = {0};
#endif
static STM32FXXX_RCC stm32fxxx_rcc = {0};

/*** File Procedure & Function Header ***/
/*** Extended ***/
STM32FXXX_RCC_PLL* stm32fxxx_rcc_pll_inic(void);
STM32FXXX_RCC_PLLI2S* stm32fxxx_rcc_plli2s_inic(void);
STM32FXXX_RCC_PLLSAI* stm32fxxx_rcc_pllsai_inic(void);
/******/
void RCC_PwrClock(uint8_t state);
void RCC_WriteEnable(void);
void RCC_WriteDisable(void);
uint8_t RCC_PLLSelect(uint8_t hclock);

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
void RCC_HEnable(uint8_t hclock)
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
void RCC_HSelect(uint8_t hclock)
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
uint8_t RCC_PLLSelect(uint8_t hclock)
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
void RCC_LEnable(uint8_t lclock)
{
    uint8_t set = 1;
    uint8_t rdy = 1;

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
                    RCC_WriteEnable();
                    RCC->BDCR |= (1 << RCC_BDCR_LSEON_Pos); // Enable LSE
                    RCC_WriteDisable();
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
                    RCC_WriteEnable();
                    RCC->BDCR |= (1 << RCC_BDCR_LSEBYP_Pos); // Enable LSE bypass
                    RCC_WriteDisable();
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
void RCC_LSelect(uint8_t lclock)
{
	RCC_WriteEnable(); // Enable write access to the backup domain

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

	RCC_WriteDisable(); // Disable write access to the backup domain
}
void RCC_Prescaler(uint16_t ahbpre, uint8_t ppre1, uint8_t ppre2, uint8_t rtcpre)
{
	set_reg_block(&RCC->CFGR, 5, RCC_CFGR_RTCPRE_Pos, rtcpre);
	switch(ppre2){ // 13
		case 2:
			set_reg_block(&RCC->CFGR, 3, RCC_CFGR_PPRE2_Pos, 4);
		break;
		case 4:
			set_reg_block(&RCC->CFGR, 3, RCC_CFGR_PPRE2_Pos, 5);
		break;
		case 8:
			set_reg_block(&RCC->CFGR, 3, RCC_CFGR_PPRE2_Pos, 6);
		break;
		case 16:
			set_reg_block(&RCC->CFGR, 3, RCC_CFGR_PPRE2_Pos, 7);
		break;
		default:
			set_reg_block(&RCC->CFGR, 3, RCC_CFGR_PPRE2_Pos, 0);
		break;
	}
	switch(ppre1){ // 10
		case 2:
			set_reg_block(&RCC->CFGR, 3, RCC_CFGR_PPRE1_Pos, 4);
		break;
		case 4:
			set_reg_block(&RCC->CFGR, 3, RCC_CFGR_PPRE1_Pos, 5);
		break;
		case 8:
			set_reg_block(&RCC->CFGR, 3, RCC_CFGR_PPRE1_Pos, 6);
		break;
		case 16:
			set_reg_block(&RCC->CFGR, 3, RCC_CFGR_PPRE1_Pos, 7);
		break;
		default:
			set_reg_block(&RCC->CFGR, 3, RCC_CFGR_PPRE1_Pos, 0);
		break;
	}
	switch(ahbpre){ // 4
		case 2:
			set_reg_block(&RCC->CFGR, 4, RCC_CFGR_HPRE_Pos, 8);
		break;
		case 4:
			set_reg_block(&RCC->CFGR, 4, RCC_CFGR_HPRE_Pos, 9);
		break;
		case 8:
			set_reg_block(&RCC->CFGR, 4, RCC_CFGR_HPRE_Pos, 10);
		break;
		case 16:
			set_reg_block(&RCC->CFGR, 4, RCC_CFGR_HPRE_Pos, 11);
		break;
		case 64:
			set_reg_block(&RCC->CFGR, 4, RCC_CFGR_HPRE_Pos, 12);
		break;
		case 128:
			set_reg_block(&RCC->CFGR, 4, RCC_CFGR_HPRE_Pos, 13);
		break;
		case 256:
			set_reg_block(&RCC->CFGR, 4, RCC_CFGR_HPRE_Pos, 14);
			break;
		case 512:
			set_reg_block(&RCC->CFGR, 4, RCC_CFGR_HPRE_Pos, 15);
			break;
		default:
			set_reg_block(&RCC->CFGR, 4, RCC_CFGR_HPRE_Pos, 0);
		break;
	}
}
// PLL
void RCC_PLLDivision(uint8_t pllm, uint16_t plln, uint8_t pllp, uint8_t pllq)
{
	set_reg_block(&RCC->CR, 1, RCC_CR_PLLON_Pos, 0);
	set_reg_block(&RCC->PLLCFGR,4,RCC_PLLCFGR_PLLQ_Pos,pllq);
	switch(pllp){
		case 2:
			set_reg_block(&RCC->PLLCFGR,2,RCC_PLLCFGR_PLLP_Pos,0);
		break;
		case 4:
			set_reg_block(&RCC->PLLCFGR,2,RCC_PLLCFGR_PLLP_Pos,1);
		break;
		case 6:
			set_reg_block(&RCC->PLLCFGR,2,RCC_PLLCFGR_PLLP_Pos,2);
		break;
		case 8:
			set_reg_block(&RCC->PLLCFGR,2,RCC_PLLCFGR_PLLP_Pos,3);
		break;
		default: // 2
			set_reg_block(&RCC->PLLCFGR,2,RCC_PLLCFGR_PLLP_Pos,0);
		break;
	}
	set_reg_block(&RCC->PLLCFGR,9,RCC_PLLCFGR_PLLN_Pos,plln);
	set_reg_block(&RCC->PLLCFGR,6,RCC_PLLCFGR_PLLM_Pos,pllm);
}
void RCC_PLLCLKEnable(void)
{
	uint32_t rcc_time_out;
	//if(onoff){
		for( rcc_time_out = 0xFFFFFF, RCC->CR |= (1 << RCC_CR_PLLON_Pos) ; !(RCC->CR & (1 << RCC_CR_PLLRDY_Pos)) && rcc_time_out; rcc_time_out-- ); // PLLON: Main PLL (PLL) enable
	//}else{
		//RCC->CR &= (unsigned int) ~(1 << 24);
	//}
}
void RCC_PLLI2SEnable(void)
{
	uint32_t rcc_time_out;
	//if(onoff)
		for( rcc_time_out = 0xFFFFFF, RCC->CR |= (1 << RCC_CR_PLLI2SON_Pos) ; !(RCC->CR & (1 << RCC_CR_PLLI2SRDY_Pos)) && rcc_time_out; rcc_time_out-- ); // PLLI2SON: PLLI2S enable
	//else
		//RCC->CR &= (unsigned int) ~(1 << 26);
}
#ifdef STM32F446xx
	void RCC_PLLSAIEnable(void)
	{
		uint32_t rcc_time_out;
		//if(onoff)
		for( rcc_time_out = 0xFFFFFF, RCC->CR |= (1 << RCC_CR_PLLSAION_Pos) ; !(RCC->CR & (1 << RCC_CR_PLLSAIRDY_Pos)) && rcc_time_out; rcc_time_out-- ); // PLLSAION: PLLSAI enable
		//else
		//RCC->CR &= (unsigned int) ~(1 << 28);
	}
#endif
void RCC_PwrClock(uint8_t state)
{
	set_reg_block(&RCC->APB1ENR, 1, RCC_APB1ENR_PWREN_Pos, state); // Power interface clock enable
}
void RCC_WriteEnable(void)
{
	PWR->CR |= (1 << PWR_CR_DBP_Pos); // Disable protection
}
void RCC_WriteDisable(void)
{
	PWR->CR &= (uint32_t) ~(1 << PWR_CR_DBP_Pos); // Enable protection
}
/*** RCC Bit Mapping Definition ***/
/*** Other ***/
void RCC_nvic(uint8_t state)
{
	if(state){ set_bit_block(NVIC->ISER, 1, RCC_IRQn, 1); } else{ set_bit_block(NVIC->ICER, 1, RCC_IRQn, 1); }
}
/*** Extended ***/
STM32FXXX_RCC_PLL* stm32fxxx_rcc_pll_inic(void)
{

	stm32fxxx_rcc_pll.division = RCC_PLLDivision;
	stm32fxxx_rcc_pll.enable = RCC_PLLCLKEnable;
	return &stm32fxxx_rcc_pll;
}
STM32FXXX_RCC_PLLI2S* stm32fxxx_rcc_plli2s_inic(void)
{

	stm32fxxx_rcc_plli2s.enable = RCC_PLLI2SEnable;
	return &stm32fxxx_rcc_plli2s;
}
#ifdef STM32F446xx
	STM32FXXX_RCC_PLLSAI* stm32fxxx_rcc_pllsai_inic(void)
	{

		stm32fxxx_rcc_pllsai.enable = RCC_PLLSAIEnable;
		return &stm32fxxx_rcc_pllsai;
	}
#endif
/*** INIC Procedure & Function Definition ***/
void rcc_enable(void)
{
	rcc_start();
	/*** RCC Bit Mapping Link ***/
	stm32fxxx_rcc.prescaler = RCC_Prescaler;
	/*** PLL ***/
	stm32fxxx_rcc.pll = stm32fxxx_rcc_pll_inic();
	stm32fxxx_rcc.plli2s = stm32fxxx_rcc_plli2s_inic();
	#ifdef STM32F446xx
		stm32fxxx_rcc.pllsai = stm32fxxx_rcc_pllsai_inic();
	#else
		stm32fxxx_rcc.pllsai = (STM32FXXX_RCC_PLLSAI*) NULL;
	#endif
	/*** Other ***/
	stm32fxxx_rcc.henable = RCC_HEnable;
	stm32fxxx_rcc.hselect = RCC_HSelect;
	stm32fxxx_rcc.lenable = RCC_LEnable;
	stm32fxxx_rcc.lselect = RCC_LSelect;
	/*** Clock and Nvic ***/
	stm32fxxx_rcc.nvic = RCC_nvic;
	//return &stm32fxxx_rcc;
}

STM32FXXX_RCC* rcc(void){ return &stm32fxxx_rcc; };

/*** System Clock Init ***/
void rcc_start(void)
{	// Configure -> Enable -> Select
    // AHB 1,2,4,8,16,64,128,256,512;  APB1 1,2,4,8,16;  APB2 1,2,4,8,16;  RTC 2 to 31
	//STM32FXXXPrescaler(8, 1, 1, 1); // (8, 1, 1, 0)
	RCC_Prescaler(1, 1, 1, 0); // (1, 1, 1, 0)
	RCC_HEnable(H_Clock_Source); // 0 - HSI, 1 - HSE
	RCC_PLLSelect(H_Clock_Source); // 0 - HSI, 1 - HSE, H_Clock_Source
	// M 2 to 63;  N 50 to 432;  P 2,4,6,8;  Q 2 to 15;
	RCC_PLLDivision((uint32_t)getpllsourceclk()/1000000, 240, 2, 4);
	if(PLL_ON_OFF){
		RCC_PLLCLKEnable();
		// System Clock Switch
		RCC_HSelect(2); // 0 - HSI, 1 - HSE, 2 - PLL_P, 3 - PLL_R pg133 (manual 2) SW[1:0]: System clock switch
	}else{
		// System Clock Switch
		RCC_HSelect(H_Clock_Source); // 0 - HSI, 1 - HSE, 2 - PLL_P, 3 - PLL_R pg133 (manual 2) SW[1:0]: System clock switch
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

