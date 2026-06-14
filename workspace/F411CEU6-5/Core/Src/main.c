/****************************************************************
Title:    A simple Clock
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Software: STM32CubeIDE v1.16.0 Build: 21983_20240628_1741 (UTC)
Hardware: STM32F411CEU6
Date: 14062026
Comment:
	Button K0:
GPIO PA0 - Button
	LED D2:
GPIO PC13 - D2
	SPI LCD
PA7 - SDA
PA5 - SCL
PA4 - RST
PA3 - DC
PA2 - CS
3.3V - BL
****************************************************************/
/******/
#include "stm32fxxxrcc.h"
#include "armsystick.h"
#include "stm32fxxxrtc.h"
#include "stm32fxxxadc1.h"
#include "stm32fxxxtim1and8.h"
#include "st7789.h"
/******/
#include "armfunction.h"
#include "explode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JMP_menu_repeat 5
#define ADC_DELAY 16
#define ADC_SAMPLE 128
#define STEP_DELAY 10
#define MAIN_MENU_DELAY 20
#define BG_COLOUR 0x0000

char str[32];

int main(void)
{
rcc()->inic();
systick_inic();
fpu_enable();
rtc()->inic();

_delay_ms(1);
char state[12];

adc1()->clock(1);
gpioa()->clock(1);
gpiob()->clock(1); // lcd0
gpioc()->clock(1); // gpioc13

EXPLODE_Handler PA = EXPLODE_enable();
EXPLODE_Handler seconds = EXPLODE_enable();

U_byte Menu;
Menu.var = 8;
U_dword adc_value;
adc_value.var = 0;
uint8_t count_1 = ADC_DELAY;
uint8_t n_sample = ADC_SAMPLE;
uint16_t incr_0 = 0;
uint8_t skip_0 = 0;

ST7789 lcd1 = st7789_enable(dev()->spi1, 2, 3, 4, NULL);

gpioc()->moder(13,1);
gpioa()->moder(0,0);
gpioa()->pupd(0,1);

adc1()->temperature_setup();

char vecD[8]; // for calendar date
char vecT[8]; // for calendar time

dev()->gpioc->BSRR = GPIO_BSRR_BS13;

lcd1.start(&lcd1.par);
lcd1.boot_screen(&lcd1.par,BG_COLOUR);
lcd1.draw_circle(&lcd1.par,210,210,15,ST77XX_CYAN);
lcd1.draw_star5(&lcd1.par,210,210,15,5,ST77XX_GOLD);
lcd1.stop(&lcd1.par);

/*****************************************************************************/
while (1) {

	PA.update(&PA.par, dev()->gpioa->IDR);

	switch (Menu.var) {

	case 0:
		strcpy(state,"BLE");

		if (PA.par.LH & 1) {
			ftdelayReset(1);
			if (skip_0 > 0) { // Handle button hold logic if necessary

			}
			skip_0++;
		}

		if (PA.par.LL & 1) {
			if(ftdelayCycles(1, STEP_DELAY, NULL)){
				Menu.var = 1; skip_0++;
			}
		}
		break;

	case 1:
		strcpy(state,"Set Hour");

		if (PA.par.LH & 1) {
			ftdelayReset(1);
			if (skip_0 > 0) { // Handle button hold logic if necessary
				incr_0 = rtc()->get_hour();
				incr_0 = (incr_0 > 22) ? 0 : incr_0 + 1;
				rtc()->set_hour(incr_0);
			}
			skip_0++;
		}

		if (PA.par.LL & 1) { // Jump menu
			if(ftdelayCycles(1, STEP_DELAY, NULL)){
				Menu.var = 2; skip_0 = 0;
			}
		}
		break;

	case 2:
		strcpy(state,"Set Minute");

		if (PA.par.LH & 1) {
			ftdelayReset(1);
			if (skip_0 > 0) { // Handle button hold logic if necessary
				incr_0 = rtc()->get_minute();
				incr_0 = (incr_0 > 58) ? 0 : incr_0 + 1;
				rtc()->set_minute(incr_0);
			}
			skip_0++;
		}

		if (PA.par.LL & 1) {
			if(ftdelayCycles(1, STEP_DELAY, NULL)){
				Menu.var = 3; skip_0 = 0;
			}
		}
		break;

	case 3:
		strcpy(state,"Set Second");

		if (PA.par.LH & 1) {
			ftdelayReset(1);
			if (skip_0 > 0) { // Handle button hold logic if necessary
				incr_0 = rtc()->get_second();
				incr_0 = (incr_0 > 58) ? 0 : incr_0 + 1;
				rtc()->set_second(incr_0);
			}
			skip_0++;
		}

		if (PA.par.LL & 1) {
			if(ftdelayCycles(1, STEP_DELAY, NULL)){
				Menu.var = 4; skip_0 = 0;
			}
		}
		break;

	case 4:
		strcpy(state,"Set Year");

		if (PA.par.LH & 1) {
			ftdelayReset(1);
			if (skip_0 > 0) { // Handle button hold logic if necessary
				incr_0 = rtc()->get_year();
				incr_0 = (incr_0 > 98) ? 0 : incr_0 + 1;
				rtc()->set_year(incr_0);
			}
			skip_0++;
		}

		if (PA.par.LL & 1) {
			if(ftdelayCycles(1, STEP_DELAY, NULL)){
				Menu.var = 5; skip_0 = 0;
			}
		}
		break;

	case 5:
		strcpy(state,"Set Month");

		if (PA.par.LH & 1) {
			ftdelayReset(1);
			if (skip_0 > 0) { // Handle button hold logic if necessary
				incr_0 = rtc()->get_month();
				incr_0 = (incr_0 > 11) ? 1 : incr_0 + 1;
				rtc()->set_month(incr_0);
			}
			skip_0++;
		}

		if (PA.par.LL & 1) {
			if(ftdelayCycles(1, STEP_DELAY, NULL)){
				Menu.var = 6; skip_0 = 0;
			}
		}
		break;

	case 6:
		strcpy(state,"Set WeekDay");

		if (PA.par.LH & 1) {
			ftdelayReset(1);
			if (skip_0 > 0) { // Handle button hold logic if necessary
				incr_0 = rtc()->get_weekday();
				incr_0 = (incr_0 > 6) ? 1 : incr_0 + 1;
				rtc()->set_weekday(incr_0);
			}
			skip_0++;
		}

		if (PA.par.LL & 1) {
			if(ftdelayCycles(1, STEP_DELAY, NULL)){
				Menu.var = 7; skip_0 = 0;
			}
		}
		break;

	case 7:
		strcpy(state,"Set Day");

		if (PA.par.LH & 1) {
			ftdelayReset(1);
			if (skip_0 > 0) { // Handle button hold logic if necessary
				incr_0 = rtc()->get_day();
				incr_0 = (incr_0 > 30) ? 1 : incr_0 + 1;
				rtc()->set_day(incr_0);
			}
			skip_0++;
		}

		if (PA.par.LL & 1) {
			if(ftdelayCycles(1, STEP_DELAY, NULL)){
				Menu.var = 8; skip_0 = 0;
			}
		}

		break;

	case 8:
		strcpy(state,"Clock");

		count_1--;
		if (!count_1) {
			count_1 = ADC_DELAY;
			if (n_sample) {
				n_sample--;
				adc_value.var += adc1()->read_temperature();
			} else {
				n_sample = ADC_SAMPLE;
				adc_value.var /= ADC_SAMPLE;  // Ensure proper averaging
				//temperature = CalculateTemperature(adc_value);
				snprintf(str, 8, "%.1f C", CalculateTemperature(adc_value.var));
				lcd1.start(&lcd1.par);
				lcd1.drawstring16x24_size(&lcd1.par,str,130,40,ST77XX_MAGENTA,BG_COLOUR, 8);
				lcd1.stop(&lcd1.par);
				adc_value.var = 0;  // Reset adc_value after use
			}
		}

		if (PA.par.LH & 1) {
			ftdelayReset(1);
			if (skip_0 < 1) { // Handle button hold logic if necessary

			}
			skip_0++;
		}

		if (PA.par.LL & 1) {
			if(ftdelayCycles(1, MAIN_MENU_DELAY, NULL)){
				Menu.var = 0;  skip_0 = 0;
			}
		}
		break;
	}

	rtc()->dr2vec(vecD);
	rtc()->tr2vec(vecT);

	if(seconds.update(&seconds.par,vecT[5])){

	lcd1.start(&lcd1.par);
	lcd1.drawstring16x24_size(&lcd1.par,state,10,10,ST77XX_BLUE,BG_COLOUR, 12);

	func()->format_string(str,32,"%d%d-%d%d-20%d%d",vecD[5], vecD[6], vecD[3], vecD[4], vecD[0], vecD[1]);

	lcd1.drawstring16x24(&lcd1.par,str,10,150,ST77XX_GREEN,BG_COLOUR);

	lcd1.drawstring12x16_size(&lcd1.par,(char*)WeekDay_String(vecD[2]),10,200,ST77XX_GREEN,BG_COLOUR,7);

	func()->format_string(str,32,"%d%d:%d%d:%d%d",vecT[0], vecT[1], vecT[2], vecT[3], vecT[4], vecT[5]);

	lcd1.drawstring24x48_size(&lcd1.par,str,15,70,ST77XX_WHITE,BG_COLOUR,8);
	lcd1.stop(&lcd1.par);

	}
}}

void Error_Handler(void)
{
    __disable_irq();
    while (1) {
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}

#endif

