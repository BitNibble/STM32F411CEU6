/******************************************************************************
	STM32 FXXX RCC
Author: <sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-FXXX
Date: 21102025
*******************************************************************************/
/*** File Library ***/
#include <stm32fxxxrcc.h>

/*** File Procedure & Function Header ***/
void STM32FXXX_Rcc_Pwr_Clock(uint8_t state);
void STM32FXXX_Rcc_Write_Enable(void);
void STM32FXXX_Rcc_Write_Disable(void);
uint8_t STM32FXXX_Rcc_PLL_Select(uint8_t hclock);

/*******   0 -> HSI    1->HSE   *********/
#ifndef H_Clock_Source
	#define H_Clock_Source 1
#endif
/****************************************/
/****   PLL ON -> 1    PLL OFF = 0   ****/
#ifndef PLL_ON_OFF
	#define PLL_ON_OFF 0
#endif
/****************************************/

/*** RCC Procedure & Function Definition ***/
void rcc_start(void)
{	// Configure -> Enable -> Select
    // AHB 1,2,4,8,16,64,128,256,512;  APB1 1,2,4,8,16;  APB2 1,2,4,8,16;  RTC 2 to 31
	//STM32FXXXPrescaler(8, 1, 1, 1); // (8, 1, 1, 0)
	STM32FXXX_Prescaler(1, 1, 1, 0); // (1, 1, 1, 0)
	STM32FXXX_Rcc_HEnable(H_Clock_Source); // 0 - HSI, 1 - HSE
	STM32FXXX_Rcc_PLL_Select(H_Clock_Source); // 0 - HSI, 1 - HSE, H_Clock_Source
	// M 2 to 63;  N 50 to 432;  P 2,4,6,8;  Q 2 to 15;
	STM32FXXX_PLL_Division((uint32_t)get_pllsclk()/1000000, 240, 2, 4);
	if(PLL_ON_OFF){
		STM32FXXX_Rcc_PLL_CLK_Enable();
		// System Clock Switch
		STM32FXXX_Rcc_HSelect(2); // 0 - HSI, 1 - HSE, 2 - PLL_P, 3 - PLL_R pg133 (manual 2) SW[1:0]: System clock switch
	}else{
		// System Clock Switch
		STM32FXXX_Rcc_HSelect(H_Clock_Source); // 0 - HSI, 1 - HSE, 2 - PLL_P, 3 - PLL_R pg133 (manual 2) SW[1:0]: System clock switch
	}
}
// RCC
void STM32FXXX_Rcc_HEnable(uint8_t hclock)
{
    uint8_t set = 1;
    uint8_t rdy = 1;

    // Enable CSSON
    set_reg_block(&dev()->rcc->CR, 1, 19, 1); // Clock security system enable

    while(rdy)
    {
        switch(hclock)
        {
            case 0: // HSION: Internal high-speed clock enable
                if(set) {
                    dev()->rcc->CR |= (1 << 0); // Enable HSI
                    set = 0;
                }
                else if(dev()->rcc->CR & (1 << 1)) // Wait for HSIRDY
                    rdy = 0;
                break;

            case 1: // HSEON: External high-speed clock enable
                if(set) {
                    dev()->rcc->CR |= (1 << 16); // Enable HSE
                    set = 0;
                }
                else if(dev()->rcc->CR & (1 << 17)) // Wait for HSERDY
                    rdy = 0;
                break;

            case 2: // HSEBYP: HSE clock bypass
                if(set) {
                    dev()->rcc->CR |= (1 << 18); // Enable HSE bypass
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
void STM32FXXX_Rcc_HSelect(uint8_t hclock)
{
    switch(hclock){
        case 0: // HSI selected as system clock
            set_reg_block(&dev()->rcc->CFGR, 2, 0, 0);
            break;

        case 1: // HSE oscillator selected as system clock
            set_reg_block(&dev()->rcc->CFGR, 2, 0, 1);
            break;

        case 2: // PLL_P selected as system clock
            set_reg_block(&dev()->rcc->CFGR, 2, 0, 2);
            break;

        case 3: // PLL_R selected as system clock (only on STM32F446xx)
            #ifdef STM32F446xx
                set_reg_block(&dev()->rcc->CFGR, 2, 0, 3);
            #else
                set_reg_block(&dev()->rcc->CFGR, 2, 0, 0); // Default to HSI if not STM32F446
            #endif
            break;

        default: // Default to HSI (00) if an invalid value is passed
            set_reg_block(&dev()->rcc->CFGR, 2, 0, 0);
            break;
    }
}
uint8_t STM32FXXX_Rcc_PLL_Select(uint8_t hclock)
{ // This bit can be written only when PLL and PLLI2S are disabled
	set_reg_block(&dev()->rcc->CR, 1, 24, 0); set_reg_block(&dev()->rcc->CR, 1, 26, 0);
	switch(hclock){
		case 0: // HSI
			set_reg_block(&dev()->rcc->PLLCFGR, 1, 22, 0);
		break;
		case 1: // HSE
			set_reg_block(&dev()->rcc->PLLCFGR, 1, 22, 1);
		break;
		default: // HSI
			set_reg_block(&dev()->rcc->PLLCFGR, 1, 22, 0);
		break;
	}
	return get_reg_block(dev()->rcc->PLLCFGR, 1, 22);
}
void STM32FXXX_Rcc_LEnable(uint8_t lclock)
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
                    dev()->rcc->CSR |= (1 << 0); // Enable LSI
                    set = 0;
                }
                else if(dev()->rcc->CSR & (1 << 1)) // Wait for LSIRDY
                {
                    rdy = 0; // LSI ready
                }
                break;

            case 1: // LSEON: External low-speed oscillator enable
                if(set)
                {
                    STM32FXXX_Rcc_Write_Enable();
                    dev()->rcc->BDCR |= (1 << 0); // Enable LSE
                    STM32FXXX_Rcc_Write_Disable();
                    set = 0;
                }
                else if(dev()->rcc->BDCR & (1 << 1)) // Wait for LSERDY
                {
                    rdy = 0; // LSE ready
                }
                break;

            case 2: // LSEBYP: External low-speed oscillator bypass
                if(set)
                {
                    STM32FXXX_Rcc_Write_Enable();
                    dev()->rcc->BDCR |= (1 << 2); // Enable LSE bypass
                    STM32FXXX_Rcc_Write_Disable();
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
void STM32FXXX_Rcc_LSelect(uint8_t lclock)
{
	STM32FXXX_Rcc_Write_Enable(); // Enable write access to the backup domain

	switch(lclock)
	{
		case 0: // LSI oscillator clock used as the RTC clock
			set_reg_block(&dev()->rcc->BDCR, 2, 8, 2);
			break;

		case 1: // LSE oscillator clock used as the RTC clock
			set_reg_block(&dev()->rcc->BDCR, 2, 8, 1);
			break;

		case 2: // HSE oscillator clock divided by a programmable prescaler
			set_reg_block(&dev()->rcc->BDCR, 2, 8, 3);
			break;

		default: // Default to LSE oscillator clock
			set_reg_block(&dev()->rcc->BDCR, 2, 8, 1);
			break;
	}

	STM32FXXX_Rcc_Write_Disable(); // Disable write access to the backup domain
}
void STM32FXXX_Prescaler(uint16_t ahbpre, uint8_t ppre1, uint8_t ppre2, uint8_t rtcpre)
{
	set_reg_block(&dev()->rcc->CFGR, 5, 16, rtcpre);
	switch(ppre2){ // 13
		case 2:
			set_reg_block(&dev()->rcc->CFGR, 3, 13, 4);
		break;
		case 4:
			set_reg_block(&dev()->rcc->CFGR, 3, 13, 5);
		break;
		case 8:
			set_reg_block(&dev()->rcc->CFGR, 3, 13, 6);
		break;
		case 16:
			set_reg_block(&dev()->rcc->CFGR, 3, 13, 7);
		break;
		default:
			set_reg_block(&dev()->rcc->CFGR, 3, 13, 0);
		break;
	}
	switch(ppre1){ // 10
		case 2:
			set_reg_block(&dev()->rcc->CFGR, 3, 10, 4);
		break;
		case 4:
			set_reg_block(&dev()->rcc->CFGR, 3, 10, 5);
		break;
		case 8:
			set_reg_block(&dev()->rcc->CFGR, 3, 10, 6);
		break;
		case 16:
			set_reg_block(&dev()->rcc->CFGR, 3, 10, 7);
		break;
		default:
			set_reg_block(&dev()->rcc->CFGR, 3, 10, 0);
		break;
	}
	switch(ahbpre){ // 4
		case 2:
			set_reg_block(&dev()->rcc->CFGR, 4, 4, 8);
		break;
		case 4:
			set_reg_block(&dev()->rcc->CFGR, 4, 4, 9);
		break;
		case 8:
			set_reg_block(&dev()->rcc->CFGR, 4, 4, 10);
		break;
		case 16:
			set_reg_block(&dev()->rcc->CFGR, 4, 4, 11);
		break;
		case 64:
			set_reg_block(&dev()->rcc->CFGR, 4, 4, 12);
		break;
		case 128:
			set_reg_block(&dev()->rcc->CFGR, 4, 4, 13);
		break;
		case 256:
			set_reg_block(&dev()->rcc->CFGR, 4, 4, 14);
			break;
		case 512:
			set_reg_block(&dev()->rcc->CFGR, 4, 4, 15);
			break;
		default:
			set_reg_block(&dev()->rcc->CFGR, 4, 4, 0);
		break;
	}
}
// PLL
void STM32FXXX_PLL_Division(uint8_t pllm, uint16_t plln, uint8_t pllp, uint8_t pllq)
{
	set_reg_block(&dev()->rcc->CR, 1, 24, 0);
	set_reg_block(&dev()->rcc->PLLCFGR,4,24,pllq);
	switch(pllp){
		case 2:
			set_reg_block(&dev()->rcc->PLLCFGR,2,16,0);
		break;
		case 4:
			set_reg_block(&dev()->rcc->PLLCFGR,2,16,1);
		break;
		case 6:
			set_reg_block(&dev()->rcc->PLLCFGR,2,16,2);
		break;
		case 8:
			set_reg_block(&dev()->rcc->PLLCFGR,2,16,3);
		break;
		default: // 2
			set_reg_block(&dev()->rcc->PLLCFGR,2,16,0);
		break;
	}
	set_reg_block(&dev()->rcc->PLLCFGR,9,6,plln);
	set_reg_block(&dev()->rcc->PLLCFGR,6,0,pllm);
}
void STM32FXXX_Rcc_PLL_CLK_Enable(void)
{
	volatile uint32_t rcc_time_out;
	//if(onoff){
		for( rcc_time_out = 0xFFFFFF, dev()->rcc->CR |= (1 << 24) ; !(dev()->rcc->CR & (1 << 25)) && rcc_time_out; rcc_time_out-- ); // PLLON: Main PLL (PLL) enable
	//}else{
		//dev()->rcc->CR &= (unsigned int) ~(1 << 24);
	//}
}
void STM32FXXX_Rcc_PLL_I2S_Enable(void)
{
	volatile uint32_t rcc_time_out;
	//if(onoff)
		for( rcc_time_out = 0xFFFFFF, dev()->rcc->CR |= (1 << 26) ; !(dev()->rcc->CR & (1 << 27)) && rcc_time_out; rcc_time_out-- ); // PLLI2SON: PLLI2S enable
	//else
		//dev()->rcc->CR &= (unsigned int) ~(1 << 26);
}
void STM32FXXX_Rcc_PLL_SAI_Enable(void)
{
	volatile uint32_t rcc_time_out;
	//if(onoff)
		for( rcc_time_out = 0xFFFFFF, dev()->rcc->CR |= (1 << 28) ; !(dev()->rcc->CR & (1 << 29)) && rcc_time_out; rcc_time_out-- ); // PLLSAION: PLLSAI enable
	//else
		//dev()->rcc->CR &= (unsigned int) ~(1 << 28);
}
void STM32FXXX_Rcc_Pwr_Clock(uint8_t state)
{
	set_reg_block(&dev()->rcc->APB1ENR, 1, 28, state); // Power interface clock enable
}
void STM32FXXX_Rcc_Write_Enable(void)
{
	dev()->pwr->CR |= (1 << 8); // Disable protection
}
void STM32FXXX_Rcc_Write_Disable(void)
{
	dev()->pwr->CR &= (uint32_t) ~(1 << 8); // Enable protection
}
/*** RCC Bit Mapping Definition ***/
/*** Other ***/
void STM32FXXX_RCC_nvic(uint8_t state)
{
	if(state){ set_bit_block(dev()->core->nvic->ISER, 1, RCC_IRQn, 1); } else{ set_bit_block(dev()->core->nvic->ICER, 1, RCC_IRQn, 1); }
}
/*** Extended ***/
static STM32FXXX_RCC_PLL stm32fxxx_rcc_pll_setup = {
	.division = STM32FXXX_PLL_Division,
	.enable = STM32FXXX_Rcc_PLL_CLK_Enable
};
static STM32FXXX_RCC_PLL_I2S stm32fxxx_rcc_pll_i2s_setup = {
	.enable = STM32FXXX_Rcc_PLL_I2S_Enable
};
static STM32FXXX_RCC_PLL_SAI stm32fxxx_rcc_pll_sai_setup = {
	.enable = STM32FXXX_Rcc_PLL_SAI_Enable
};
/*** HANDLER ***/
static STM32FXXX_RCC_HANDLER stm32fxxx_rcc_setup = {
	/*** RCC Bit Mapping Link ***/
	.prescaler = STM32FXXX_Prescaler,
	/*** PLL ***/
	.pll = &stm32fxxx_rcc_pll_setup,
	.pll_i2s = &stm32fxxx_rcc_pll_i2s_setup,
	.pll_sai = &stm32fxxx_rcc_pll_sai_setup,
	/*** Other ***/
	.inic = rcc_start,
	.henable = STM32FXXX_Rcc_HEnable,
	.hselect = STM32FXXX_Rcc_HSelect,
	.lenable = STM32FXXX_Rcc_LEnable,
	.lselect = STM32FXXX_Rcc_LSelect,
	/*** NVIC ***/
	.nvic = STM32FXXX_RCC_nvic
};

STM32FXXX_RCC_HANDLER* rcc(void){ return &stm32fxxx_rcc_setup; };

/*** EOF ***/

