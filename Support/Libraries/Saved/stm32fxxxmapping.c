/******************************************************************************
	STM32 XXX MAPPING
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 28/02/2024
Comment:
	-manual um1724, m0390, pm0056, pm0214, and other sources.
	-Virtual Image STM32-XXX, mapping.
	-Still in progress 15062023, increment has go along.
	-Dependent on CMSIS
	-Stable.
*******************************************************************************/
/*** File Library ***/
#include <stm32fxxxmapping.h>
/*** File Variables ***/
static STM32FXXX stm32fxxx = {0};
/*** File Function Identity ***/
static void initialize_nvic(void);
static void initialize_adc(void);
static void initialize_crc(void);
static void initialize_dma(void);
static void initialize_flash(void);
static void initialize_gpio(void);
static void initialize_syscfg(void);
static void initialize_i2c(void);
static void initialize_pwr(void);
static void initialize_rcc(void);
static void initialize_rtc(void);
static void initialize_sram(void);
static void initialize_tim(void);
static void initialize_usart(void);
/******* STM32F446RE Procedure & Function Definition *******/
void STM32FXXX_enable(void){
	/************* CORE ************/
	initialize_nvic();
	/************ MCU ************/
	initialize_adc();
	initialize_crc();
	initialize_dma();
	initialize_flash();
	initialize_gpio();
	initialize_syscfg();
	initialize_i2c();
	initialize_pwr();
	initialize_rcc();
	initialize_rtc();
	initialize_sram();
	initialize_tim();
	initialize_usart();
	/*** System ***/
	rcc_start();
	query_enable();
	systick_start();
	//return &stm32fxxx;
}
STM32FXXX* stm(void){return (STM32FXXX*) &stm32fxxx;}
// NVIC
static void initialize_nvic(void) {
	#if defined(_STM32FXXXNVIC_H_)
		stm32fxxx.nvic_enable = nvic_enable;
		stm32fxxx.nvic = nvic();
	#endif
}
// ADC
static void initialize_adc(void) {
    #if defined(_STM32FXXXADC1_H_)
        stm32fxxx.adc1_enable = adc1_enable;
        stm32fxxx.adc1 = adc1();
    #endif
	#if defined(_STM32FXXXADC2_H_)
		#ifdef STM32F446xx
			stm32fxxx.adc2_enable = adc2_enable;
        	stm32fxxx.adc2 = adc2();
		#endif
	#endif
	#if defined(_STM32FXXXADC3_H_)
		#ifdef STM32F446xx
			stm32fxxx.adc3_enable = adc3_enable;
        	stm32fxxx.adc3 = adc3();
		#endif
	#endif
}
// CRC
static void initialize_crc(void) {
	#if defined(_STM32FXXXCRC_H_)
		stm32fxxx.crc_enable = crc_enable;
		stm32fxxx.crc = crc();
	#endif
}
// DMA
static void initialize_dma(void) {
	#if defined(_STM32FXXXDMA_H_)
		stm32fxxx.dma1_enable = dma1_enable;
		stm32fxxx.dma2_enable = dma2_enable;
		stm32fxxx.dma1 = dma1();
		stm32fxxx.dma2 = dma2();
	#endif
}
// FLASH
static void initialize_flash(void) {
	#if defined(_STM32FXXXFLASH_H_)
		stm32fxxx.flash_enable = flash_enable;
		stm32fxxx.flash = flash();
	#endif
}
// GPIO
static void initialize_gpio(void) {
    #if defined(_STM32FXXXGPIO_H_)
        stm32fxxx.gpioa_enable = gpioa_enable;
        stm32fxxx.gpiob_enable = gpiob_enable;
        stm32fxxx.gpioc_enable = gpioc_enable;
        stm32fxxx.gpiod_enable = gpiod_enable;
        stm32fxxx.gpioe_enable = gpioe_enable;
        stm32fxxx.gpioa = gpioa();
        stm32fxxx.gpiob = gpiob();
        stm32fxxx.gpioc = gpioc();
        stm32fxxx.gpiod = gpiod();
        stm32fxxx.gpioe = gpioe();
		#ifdef STM32F446xx
        	stm32fxxx.gpiof_enable = gpiof_enable;
        	stm32fxxx.gpiog_enable = gpiog_enable;
        	stm32fxxx.gpioh_enable = gpioh_enable;
        	stm32fxxx.gpiof = gpiof();
        	stm32fxxx.gpiog = gpiog();
        	stm32fxxx.gpioh = gpioh();
		#endif
    #endif
}
// SYSCFG
static void initialize_syscfg(void) {
	#if defined(_STM32FXXXSYSCFG_H_)
		stm32fxxx.syscfg_enable = syscfg_enable;
		stm32fxxx.syscfg = syscfg();
	#endif
}
static void initialize_i2c(void) {
	#if defined(_STM32FXXXI2C_H_)
		stm32fxxx.i2c1_enable = i2c1_enable;
		stm32fxxx.i2c2_enable = i2c2_enable;
		stm32fxxx.i2c3_enable = i2c3_enable;
		stm32fxxx.i2c1 = i2c1();
		stm32fxxx.i2c2 = i2c2();
		stm32fxxx.i2c3 = i2c3();
	#endif
}
// PWR
static void initialize_pwr(void) {
	#if defined(_STM32FXXXPWR_H_)
		stm32fxxx.pwr_enable = pwr_enable;
		stm32fxxx.pwr = pwr();
	#endif
}
// RCC
static void initialize_rcc(void) {
	#if defined(_STM32FXXXRCC_H_)
		stm32fxxx.rcc_enable = rcc_enable;
		stm32fxxx.rcc = rcc();
	#endif
}
// RTC
static void initialize_rtc(void) {
	#if defined(_STM32FXXXRTC_H_)
		stm32fxxx.rtc_enable = rtc_enable;
		stm32fxxx.rtc = rtc();
	#endif
}
// SRAM
static void initialize_sram(void) {
	#if defined(_STM32FXXXSRAM_H_)
		stm32fxxx.sram_enable = sram_enable;
		stm32fxxx.sram = sram();
	#endif
}
// TIM
static void initialize_tim(void) {
	#if defined(_STM32FXXXTIM1AND8_H_)
		stm32fxxx.tim1_enable = tim1_enable;
		stm32fxxx.tim1 = tim1();
		#ifdef STM32F446xx
			stm32fxxx.tim8_enable = tim8_enable;
			stm32fxxx.tim8 = tim8();
		#endif
	#endif
	#if defined(_STM32FXXXTIM2TO5_H_)
		stm32fxxx.tim2_enable = tim2_enable;
		stm32fxxx.tim3_enable = tim3_enable;
		stm32fxxx.tim4_enable = tim4_enable;
		stm32fxxx.tim5_enable = tim5_enable;
		stm32fxxx.tim2 = tim2();
		stm32fxxx.tim3 = tim3();
		stm32fxxx.tim4 = tim4();
		stm32fxxx.tim5 = tim5();
	#endif
	#if defined(_STM32FXXXTIM6AND7_H_)
		#ifdef STM32F446xx
			stm32fxxx.tim6_enable = tim6_enable;
			stm32fxxx.tim7_enable = tim7_enable;
			stm32fxxx.tim6 = tim6();
			stm32fxxx.tim7 = tim7();
		#endif
	#endif
	#if defined(_STM32FXXXTIM9TO14_H_)
		stm32fxxx.tim9_enable = tim9_enable;
		stm32fxxx.tim10_enable = tim10_enable;
		stm32fxxx.tim11_enable = tim11_enable;
		stm32fxxx.tim9 = tim9();
		stm32fxxx.tim10 = tim10();
		stm32fxxx.tim11 = tim11();
		#ifdef STM32F446xx
			stm32fxxx.tim12_enable = tim12_enable;
			stm32fxxx.tim13_enable = tim13_enable;
			stm32fxxx.tim14_enable = tim14_enable;
			stm32fxxx.tim12 = tim12();
			stm32fxxx.tim13 = tim13();
			stm32fxxx.tim14 = tim14();
		#endif
	#endif
}
// USART
static void initialize_usart(void) {
	#if defined(_STM32FXXXUSART_H_)
		stm32fxxx.usart1_enable = usart1_enable;
		stm32fxxx.usart2_enable = usart2_enable;
		stm32fxxx.usart1 = usart1();
		stm32fxxx.usart2 = usart2();
		#ifdef STM32F446xx
			stm32fxxx.usart3_enable = usart3_enable;
			stm32fxxx.uart4_enable = uart4_enable;
			stm32fxxx.uart5_enable = uart5_enable;
			stm32fxxx.usart3 = usart3();
			stm32fxxx.uart4 = uart4();
			stm32fxxx.uart5 = uart5();
		#endif
		stm32fxxx.usart6_enable = usart6_enable;
		stm32fxxx.usart6 = usart6();
	#endif
}
/***EOF***/
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

