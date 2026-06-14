/******************************************************************************
	STM32 FXXX RCC
Author: <sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-FXXX
Date: 21102025
*******************************************************************************/
/*** File Library ***/
#include <stm32fxxxrcc.h>

typedef enum
{
    RCC_CLK_HSI = 0,
    RCC_CLK_HSE = 1,
    RCC_CLK_HSEBYP = 2
} mcu_enable_clk;

typedef enum
{
    RCC_HCLK_HSI = 0,
    RCC_HCLK_HSE = 1,
    RCC_HCLK_PLL = 2
} mcu_select_clk;

typedef enum
{
    RCC_CLK_LSI = 0,
    RCC_CLK_LSE = 1,
	RCC_CLK_LSEBYP = 2
} rtc_enable_clk;

typedef enum
{
    RTC_CLK_LSI = 0,
    RTC_CLK_LSE = 1,
	RTC_CLK_HSE = 2
} rtc_select_clk;

/*** File Procedure & Function Header ***/
static void RCC_Flash_SetLatency(uint32_t sysclk);
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
void rcc_start(void)
{
    // Configure prescalers first (safe before increasing SYSCLK)
    STM32FXXX_Prescaler(1, 1, 1, 0);

    // Enable selected clock source (HSI/HSE) and wait ready inside
    STM32FXXX_Rcc_HEnable(H_Clock_Source);

    // Select PLL source
    STM32FXXX_Rcc_PLL_Select(H_Clock_Source);

    // Derive PLL input and parameters
    uint32_t input = get_pllsclk();
    uint32_t pllm = input / 1000000UL;

    if(pllm < 2)  pllm = 2;
    if(pllm > 63) pllm = 63;

    // Configure PLL (must be disabled inside)
    STM32FXXX_PLL_Division(pllm, 240, 2, 4);

    if (PLL_ON_OFF)
    {
        // Compute target SYSCLK deterministically
        uint32_t target = (input / pllm) * 240 / 2;

        // Set FLASH latency BEFORE increasing clock
        RCC_Flash_SetLatency(target);

        // Enable PLL
        STM32FXXX_Rcc_PLL_CLK_Enable();

        // Switch SYSCLK to PLL
        STM32FXXX_Rcc_HSelect(2);
    }
    else
    {
        // Direct switch to selected HSI/HSE
        STM32FXXX_Rcc_HSelect(H_Clock_Source);
    }
}
// Latency
static void RCC_Flash_SetLatency(uint32_t sysclk)
{
    uint32_t ws;

    if (sysclk <= 30000000) ws = 0;
    else if (sysclk <= 60000000) ws = 1;
    else if (sysclk <= 90000000) ws = 2;
    else ws = 3;

    dev()->flash->ACR = (dev()->flash->ACR & ~0x7) | ws;
    dev()->flash->ACR |= (1 << 8) | (1 << 9);
}
void STM32FXXX_Rcc_PLL_CLK_Enable(void)
{
	volatile uint32_t rcc_time_out;
	for( rcc_time_out = 0xFFFFFF, dev()->rcc->CR |= RCC_CR_PLLON ; !(dev()->rcc->CR & RCC_CR_PLLRDY) && rcc_time_out; rcc_time_out-- ); // PLLON: Main PLL (PLL) enable
}
void STM32FXXX_Rcc_PLL_I2S_Enable(void)
{
	volatile uint32_t rcc_time_out;
	for( rcc_time_out = 0xFFFFFF, dev()->rcc->CR |= RCC_CR_PLLI2SON ; !(dev()->rcc->CR & RCC_CR_PLLI2SRDY) && rcc_time_out; rcc_time_out-- ); // PLLI2SON: PLLI2S enable
}
void STM32FXXX_Rcc_PLL_SAI_Enable(void)
{
	volatile uint32_t rcc_time_out;
	for( rcc_time_out = 0xFFFFFF, dev()->rcc->CR |= (1 << 28) ; !(dev()->rcc->CR & (1 << 29)) && rcc_time_out; rcc_time_out-- ); // PLLSAION: PLLSAI enable
}
void STM32FXXX_Rcc_Pwr_Clock(uint8_t state)
{
	set_reg_block(&dev()->rcc->APB1ENR, 1, RCC_APB1ENR_PWREN_Pos, state); // Power interface clock enable
}
void STM32FXXX_Rcc_Write_Enable(void)
{
    STM32FXXX_Rcc_Pwr_Clock(1);

    dev()->pwr->CR |= PWR_CR_DBP;

    while(!(dev()->pwr->CR & PWR_CR_DBP)); // Confirm state
}
void STM32FXXX_Rcc_Write_Disable(void)
{
	dev()->pwr->CR &= (uint32_t) ~PWR_CR_DBP; // Enable protection
}
// RCC
void STM32FXXX_Rcc_HEnable(uint8_t hclock)
{
    uint8_t set = 1;
    uint8_t rdy = 1;
    uint32_t timeout;
    uint8_t choice = hclock;

    // Enable CSSON
    if(hclock == 1 || hclock == 2) {
        set_reg_Msk_Shifted(&dev()->rcc->CR, RCC_CR_CSSON_Msk, RCC_CR_CSSON); // Clock security system enable
    }

    while(rdy)
    {
        switch(choice)
        {
            case RCC_CLK_HSI: // HSION: Internal high-speed clock enable
                if(set) {
                	set_reg_Msk_Shifted(&dev()->rcc->CR, RCC_CR_HSION_Msk, RCC_CR_HSION); // Enable HSI
                    timeout = 0xFFFFF;
                    set = 0;
                }
                else if(dev()->rcc->CR & RCC_CR_HSIRDY) { // Wait for HSIRDY
                    rdy = 0;
                }
                else {
                	timeout--;
                	if(!timeout){
                		rdy = 0;
                		//choice = 0; set = 1;
                	}
                }
                break;

            case RCC_CLK_HSE: // HSEON: External high-speed clock enable
                if(set) {
                	set_reg_Msk_Shifted(&dev()->rcc->CR, RCC_CR_HSEON_Msk, RCC_CR_HSEON); // Enable HSE
                    timeout = 0xFFFFF;
                    set = 0;
                }
                else if(dev()->rcc->CR & RCC_CR_HSERDY) { // Wait for HSERDY
                    rdy = 0;
                }
                else {
                	timeout--;
                	if(!timeout){
                		choice = RCC_CLK_HSI; set = 1;
                	}
                }
                break;

            case 2: // HSEBYP: HSE clock bypass
                set_reg_Msk_Shifted(&dev()->rcc->CR, RCC_CR_HSEBYP_Msk, RCC_CR_HSEBYP);
                choice = RCC_CLK_HSE; // Switch to enabling HSE
                break;

            default: // Invalid value, default to HSI
                choice = RCC_CLK_HSI;
                break;
        }
    }
}
void STM32FXXX_Rcc_HSelect(uint8_t hclock)
{
	uint8_t verify = 0; uint32_t timeout = 0xFFFFF;
		switch(hclock){
			case RCC_HCLK_HSI: // HSI selected as system clock
				set_reg_block(&dev()->rcc->CFGR, 2, RCC_CFGR_SW_Pos, 0);
				verify = 1;
				break;

			case RCC_HCLK_HSE: // HSE oscillator selected as system clock
				set_reg_block(&dev()->rcc->CFGR, 2, RCC_CFGR_SW_Pos, 1);
				verify = 1;
				break;

			case RCC_HCLK_PLL:
				#ifdef STM32F446xx // PLL_R selected as system clock
					set_reg_block(&dev()->rcc->CFGR, 2, RCC_CFGR_SW_Pos, 3);
				#else // PLL_P selected as system clock
					set_reg_block(&dev()->rcc->CFGR, 2, RCC_CFGR_SW_Pos, 2);
				#endif
					verify = 1;
				break;

			default:
				set_reg_block(&dev()->rcc->CFGR, 2, RCC_CFGR_SW_Pos, 0);
				hclock = RCC_HCLK_HSI; verify = 1;
				break;
		}
	if(verify) { while((get_reg_Msk(dev()->rcc->CFGR, RCC_CFGR_SWS) != hclock) && timeout){timeout--;} }
}
uint8_t STM32FXXX_Rcc_PLL_Select(uint8_t hclock)
{ // This bit can be written only when PLL and PLLI2S are disabled
	set_reg_block(&dev()->rcc->CR, 1, RCC_CR_PLLON_Pos, 0);
	while(get_reg_block(dev()->rcc->CR, 1, RCC_CR_PLLRDY_Pos));

	set_reg_block(&dev()->rcc->CR, 1, RCC_CR_PLLI2SON_Pos, 0);
	while(get_reg_block(dev()->rcc->CR, 1, RCC_CR_PLLI2SRDY_Pos));

	switch(hclock){
		case RCC_CLK_HSI: // HSI
			set_reg_block(&dev()->rcc->PLLCFGR, 1, RCC_PLLCFGR_PLLSRC_Pos, 0);
		break;
		case RCC_CLK_HSE: // HSE
			set_reg_block(&dev()->rcc->PLLCFGR, 1, RCC_PLLCFGR_PLLSRC_Pos, 1);
		break;
		default: // HSI
			set_reg_block(&dev()->rcc->PLLCFGR, 1, RCC_PLLCFGR_PLLSRC_Pos, 0);
		break;
	}
	return get_reg_block(dev()->rcc->PLLCFGR, 1, RCC_PLLCFGR_PLLSRC_Pos);
}
void STM32FXXX_Rcc_LEnable(uint8_t lclock)
{
    uint8_t set = 1;
    uint8_t rdy = 1;
    uint32_t timeout;
    uint8_t choice = lclock;

    while(rdy)
    {
        switch(choice)
        {
            case RCC_CLK_LSI: // LSION: Internal low-speed oscillator enable
                if(set)
                {
                    dev()->rcc->CSR |= RCC_CSR_LSION; // Enable LSI
                    timeout = 0xFFFFF;
                    set = 0;
                }
                else if(dev()->rcc->CSR & RCC_CSR_LSIRDY) // Wait for LSIRDY
                {
                    rdy = 0; // LSI ready
                }
                else {
                	timeout--;
                	if(!timeout){
                		rdy = 0;
                	}
                }
                break;

            case RCC_CLK_LSE: // LSEON: External low-speed oscillator enable
                if(set)
                {
                    STM32FXXX_Rcc_Write_Enable();
                    dev()->rcc->BDCR |= RCC_BDCR_LSEON; // Enable LSE
                    STM32FXXX_Rcc_Write_Disable();
                    timeout = 0xFFFFF;
                    set = 0;
                }
                else if(dev()->rcc->BDCR & RCC_BDCR_LSERDY) // Wait for LSERDY
                {
                    rdy = 0; // LSE ready
                }
                else {
                	timeout--;
                	if(!timeout){
                		choice = RCC_CLK_LSI; set = 1;
                	}
                }
                break;

            case RCC_CLK_LSEBYP: // LSEBYP: External low-speed oscillator bypass
                STM32FXXX_Rcc_Write_Enable();
                dev()->rcc->BDCR |= RCC_BDCR_LSEBYP; // Enable LSE bypass
                STM32FXXX_Rcc_Write_Disable();
                choice = RCC_CLK_LSE; // Switch to enabling LSE
                break;

            default: // Default to enabling LSI (0)
            	choice = RCC_CLK_LSI;
                break;
        }
    }
}
void STM32FXXX_Rcc_LSelect(uint8_t lclock)
{
	STM32FXXX_Rcc_Write_Enable(); // Enable write access to the backup domain

	switch(lclock)
	{
		case RTC_CLK_LSE: // LSE oscillator clock used as the RTC clock
			set_reg_block(&dev()->rcc->BDCR, 2, RCC_BDCR_RTCSEL_Pos, 1);
			break;

		case RTC_CLK_LSI: // LSI oscillator clock used as the RTC clock
			set_reg_block(&dev()->rcc->BDCR, 2, RCC_BDCR_RTCSEL_Pos, 2);
			break;

		case RTC_CLK_HSE: // HSE oscillator clock divided by a programmable prescaler
			set_reg_block(&dev()->rcc->BDCR, 2, RCC_BDCR_RTCSEL_Pos, 3);
			break;

		default: // Default to LSE oscillator clock
			set_reg_block(&dev()->rcc->BDCR, 2, RCC_BDCR_RTCSEL_Pos, 1);
			break;
	}

	STM32FXXX_Rcc_Write_Disable(); // Disable write access to the backup domain
}
void _STM32FXXX_ppre2(uint8_t ppre2)
{
	switch(ppre2){ // 13
		case 2:
			set_reg_block(&dev()->rcc->CFGR, 3, RCC_CFGR_PPRE2_Pos, 4);
		break;
		case 4:
			set_reg_block(&dev()->rcc->CFGR, 3, RCC_CFGR_PPRE2_Pos, 5);
		break;
		case 8:
			set_reg_block(&dev()->rcc->CFGR, 3, RCC_CFGR_PPRE2_Pos, 6);
		break;
		case 16:
			set_reg_block(&dev()->rcc->CFGR, 3, RCC_CFGR_PPRE2_Pos, 7);
		break;
		default:
			set_reg_block(&dev()->rcc->CFGR, 3, RCC_CFGR_PPRE2_Pos, 0);
		break;
	}
}
void _STM32FXXX_ppre1(uint8_t ppre1)
{
	switch(ppre1){ // 10
		case 2:
			set_reg_block(&dev()->rcc->CFGR, 3, RCC_CFGR_PPRE1_Pos, 4);
		break;
		case 4:
			set_reg_block(&dev()->rcc->CFGR, 3, RCC_CFGR_PPRE1_Pos, 5);
		break;
		case 8:
			set_reg_block(&dev()->rcc->CFGR, 3, RCC_CFGR_PPRE1_Pos, 6);
		break;
		case 16:
			set_reg_block(&dev()->rcc->CFGR, 3, RCC_CFGR_PPRE1_Pos, 7);
		break;
		default:
			set_reg_block(&dev()->rcc->CFGR, 3, RCC_CFGR_PPRE1_Pos, 0);
		break;
	}
}
void _STM32FXXX_ahbpre(uint16_t ahbpre)
{
	switch(ahbpre){ // 4
		case 2:
			set_reg_block(&dev()->rcc->CFGR, 4, RCC_CFGR_HPRE_Pos, 8);
		break;
		case 4:
			set_reg_block(&dev()->rcc->CFGR, 4, RCC_CFGR_HPRE_Pos, 9);
		break;
		case 8:
			set_reg_block(&dev()->rcc->CFGR, 4, RCC_CFGR_HPRE_Pos, 10);
		break;
		case 16:
			set_reg_block(&dev()->rcc->CFGR, 4, RCC_CFGR_HPRE_Pos, 11);
		break;
		case 64:
			set_reg_block(&dev()->rcc->CFGR, 4, RCC_CFGR_HPRE_Pos, 12);
		break;
		case 128:
			set_reg_block(&dev()->rcc->CFGR, 4, RCC_CFGR_HPRE_Pos, 13);
		break;
		case 256:
			set_reg_block(&dev()->rcc->CFGR, 4, RCC_CFGR_HPRE_Pos, 14);
			break;
		case 512:
			set_reg_block(&dev()->rcc->CFGR, 4, RCC_CFGR_HPRE_Pos, 15);
			break;
		default:
			set_reg_block(&dev()->rcc->CFGR, 4, RCC_CFGR_HPRE_Pos, 0);
		break;
	}
}
void STM32FXXX_Prescaler(uint16_t ahbpre, uint8_t ppre1, uint8_t ppre2, uint8_t rtcpre)
{
	set_reg_block(&dev()->rcc->CFGR, 5, RCC_CFGR_RTCPRE_Pos, rtcpre);

	_STM32FXXX_ppre2(ppre2);

	_STM32FXXX_ppre1(ppre1);

	_STM32FXXX_ahbpre(ahbpre);
}
void _STM32FXXX_pllp(uint8_t pllp)
{
	switch(pllp){
			case 2:
				set_reg_block(&dev()->rcc->PLLCFGR,2,RCC_PLLCFGR_PLLP_Pos,0);
			break;
			case 4:
				set_reg_block(&dev()->rcc->PLLCFGR,2,RCC_PLLCFGR_PLLP_Pos,1);
			break;
			case 6:
				set_reg_block(&dev()->rcc->PLLCFGR,2,RCC_PLLCFGR_PLLP_Pos,2);
			break;
			case 8:
				set_reg_block(&dev()->rcc->PLLCFGR,2,RCC_PLLCFGR_PLLP_Pos,3);
			break;
			default: // 2
				set_reg_block(&dev()->rcc->PLLCFGR,2,RCC_PLLCFGR_PLLP_Pos,0);
			break;
		}
}
// PLL
void STM32FXXX_PLL_Division(uint8_t pllm, uint16_t plln, uint8_t pllp, uint8_t pllq)
{
	// disable PLL
	set_reg_block(&dev()->rcc->CR, 1, RCC_CR_PLLON_Pos, 0);
	while (get_reg_block(dev()->rcc->CR, 1, RCC_CR_PLLRDY_Pos));

	set_reg_block(&dev()->rcc->PLLCFGR,4,RCC_PLLCFGR_PLLQ_Pos,pllq);

	_STM32FXXX_pllp(pllp);

	set_reg_block(&dev()->rcc->PLLCFGR,9,RCC_PLLCFGR_PLLN_Pos,plln);
	set_reg_block(&dev()->rcc->PLLCFGR,6,RCC_PLLCFGR_PLLM_Pos,pllm);
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
	.nvic = STM32FXXX_RCC_nvic,
	/*** Device ***/
	//.dev = dev
};

STM32FXXX_RCC_HANDLER* rcc(void){ return &stm32fxxx_rcc_setup; };

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

