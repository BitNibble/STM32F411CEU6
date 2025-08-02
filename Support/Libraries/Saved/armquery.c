/*************************************************************************
	STM32QUERY
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License     
Hardware: STM32QUERY
Date: 10/01/2024
Update: 
Comment:
	Tested STM32F446RE || STM32F411CEU6
************************************************************************/
#include "armquery.h"
#include "stm32fxxxinstance.h"
#include <math.h>

/****************************************/

static STM32FXXX_Query stm32fxxx_query = {0};
static STM32FXXXSYSTEM_prescaler stm32fxxx_System_prescaler;
static STM32FXXXPLL_prescaler stm32fxxx_Pll_prescaler;

STM32FXXXSYSTEM_prescaler* System_prescaler_inic(void);
STM32FXXXPLL_prescaler* Pll_prescaler_inic(void);

uint16_t gethpre(void)
{
	uint32_t value = get_reg_block(RCC->CFGR, 4, 4);
	switch(value)
	{
		case 0b1000:
			value = 2;
		break;
		case 0b1001:
			value = 4;
		break;
		case 0b1010:
			value = 8;
		break;
		case 0b1011:
			value = 16;
		break;
		case 0b1100:
			value = 64;
		break;
		case 0b1101:
			value = 128;
		break;
		case 0b1110:
			value = 256;
		break;
		case 0b1111:
			value = 512;
		break;
		default:
			value = 1;
		break;
	}
	return value;
}
uint8_t gethppre1(void)
{
	uint32_t value = get_reg_block(RCC->CFGR, 3, 10);
	switch(value)
	{
		case 0b100:
			value = 2;
		break;
		case 0b101:
			value = 4;
		break;
		case 0b110:
			value = 8;
		break;
		case 0b111:
			value = 16;
		break;
		default:
			value = 1;
		break;
	}
	return value;
}
uint8_t gethppre2(void)
{
	uint32_t value = get_reg_block(RCC->CFGR, 3, 13);
	switch(value)
	{
		case 0b100:
			value = 2;
		break;
		case 0b101:
			value = 4;
		break;
		case 0b110:
			value = 8;
		break;
		case 0b111:
			value = 16;
		break;
		default:
			value = 1;
		break;
	}
	return value;
}
uint8_t getrtcpre(void)
{
	return get_reg_block(RCC->CFGR, 5, 16);
}
uint8_t gethmco1pre(void)
{
	uint32_t value = get_reg_block(RCC->CFGR, 3, 24);
	switch(value)
	{
		case 0b100:
			value = 2;
		break;
		case 0b101:
			value = 3;
		break;
		case 0b110:
			value = 4;
		break;
		case 0b111:
			value = 5;
		break;
		default:
			value = 1;
		break;
	}
	return value;
}
uint8_t gethmco2pre(void)
{
	uint32_t value = get_reg_block(RCC->CFGR, 3, 27);
	switch(value)
	{
		case 0b100:
			value = 2;
		break;
		case 0b101:
			value = 3;
		break;
		case 0b110:
			value = 4;
		break;
		case 0b111:
			value = 5;
		break;
		default:
			value = 1;
		break;
		}
	return value;
}
uint8_t getpllm(void)
{
	return get_reg_block(RCC->PLLCFGR, 6, 0);
}
uint16_t getplln(void)
{
	return get_reg_block(RCC->PLLCFGR, 9, 6);
}
uint8_t getpllp(void)
{
	uint32_t value = get_reg_block(RCC->PLLCFGR, 2, 16);
	switch(value)
	{
		case 0b00:
			value = 2;
		break;
		case 0b01:
			value = 4;
		break;
		case 0b10:
			value = 6;
		break;
		case 0b11:
			value = 8;
		break;
		default:
		break;
	}
	return value;
}
uint8_t getpllq(void)
{
	return get_reg_block(RCC->PLLCFGR, 4, 24);
}
uint8_t getpllr(void)
{
	return get_reg_block(RCC->PLLCFGR, 3, 28);
}
uint32_t getpllsourceclk(void)
{
	uint32_t source;
	if( get_reg_block(RCC->PLLCFGR, 1, 22) ) source = HSE_OSC; else source = HSI_RC;
	return source;
}
uint32_t getpllclk(void)
{
	uint32_t pllclk;
	pllclk = getpllsourceclk() / getpllm();
	pllclk /= getpllp();
	pllclk *= getplln();
	return pllclk;
}
uint32_t getsysclk(void)
{
	uint32_t value = get_reg_block(RCC->CFGR, 2, 2);
	switch(value) // SWS[2]: System clock switch status
	{
		case 0:
			value = HSI_RC;
		break;
		case 1: // 01: HSE oscillator used as the system clock
			value = HSE_OSC;
		break;
		case 2: // 10: PLL used as the system clock
			value = getpllsourceclk() / getpllm();
			value /= getpllp();
			value *= getplln();
		break;
		case 3: // 11: PLL_R used as the system clock
			#ifdef STM32F446xx
				value = getpllsourceclk() / getpllm();
				value /= getpllr();
				value *= getplln();
			#endif
		break;
		default: // 00: HSI oscillator used as the system clock
		break;
	}
	return (uint32_t)value;
}
uint32_t gethclk(void){
	return getsysclk()/gethpre();
}
uint32_t getpclk1(void){
	uint32_t freq = getsysclk()/gethpre();
	return freq/gethppre1();
}
uint32_t getpclk2(void){
	uint32_t freq = getsysclk()/gethpre();
	return freq/gethppre2();
}
STM32FXXXSYSTEM_prescaler* System_prescaler_inic(void)
{
	stm32fxxx_System_prescaler.AHB = gethpre;
	stm32fxxx_System_prescaler.APB1 = gethppre1;
	stm32fxxx_System_prescaler.APB2 = gethppre2;
	stm32fxxx_System_prescaler.RTCclk = getrtcpre;
	stm32fxxx_System_prescaler.MCO1 = gethmco1pre;
	stm32fxxx_System_prescaler.MCO2 = gethmco2pre;
	return &stm32fxxx_System_prescaler;
}
STM32FXXXPLL_prescaler* Pll_prescaler_inic(void)
{
	stm32fxxx_Pll_prescaler.M = getpllm;
	stm32fxxx_Pll_prescaler.N = getplln;
	stm32fxxx_Pll_prescaler.P = getpllp;
	stm32fxxx_Pll_prescaler.Q = getpllq;
	stm32fxxx_Pll_prescaler.R = getpllr;
	return &stm32fxxx_Pll_prescaler;
}
STM32FXXX_Query query_enable(void)
{
	stm32fxxx_query.System_prescaler = System_prescaler_inic();
	stm32fxxx_query.Pll_prescaler = Pll_prescaler_inic();
	stm32fxxx_query.PllClock = getpllclk;
	stm32fxxx_query.SystemClock = getsysclk;
	stm32fxxx_query.hclk = gethclk;
	stm32fxxx_query.pclk1 = getpclk1;
	stm32fxxx_query.pclk2 = getpclk2;
	return stm32fxxx_query;
}

STM32FXXX_Query* query(void){ return (STM32FXXX_Query*) &stm32fxxx_query; }

/****** MISCELLANEOUS ******/
void enable_fpu(void) {
    // Set the CP10 and CP11 bits to enable access to the FPU
    uint32_t cpacr = SCB->CPACR; // Accessing the CPACR register
    cpacr |= (0xF << 20); // Set bits 20-23 to enable FPU for all modes
    SCB->CPACR = cpacr; // Write back to CPACR
}

/******
n = bit_n/32; bit_n = bit_n - (n * 32); -> bit_n = bit_n % 32;
(a+b)/a = a/a + b/a = 1 + b/a
a/b/c/d/e = a/(b*c*d*e)
*******/

/***EOF***/

