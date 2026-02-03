/****************************************************************
Title:    A simple Clock
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Software: STM32CubeIDE v1.16.0 Build: 21983_20240628_1741 (UTC)
Hardware: STM32F411CEU6 by DevBox
Date: 28052023
Comment:
	Button K0:
GPIO PA0 - Button
	LED D2:
GPIO PC13 - D2
	LCD 4x20:
GPIO PB3 - RS
GPIO PB4 - RW
GPIO PB5 - EN
GPIO PB6 - D4
GPIO PB7 - D5
GPIO PB8 - D6
GPIO PB9 - D7
	BLE or ESP8266
GPIOA9 and GPIOA10 usart1
***************************************************************
This program can run bluetooth module BLE05 or Z040, and it also can run
ESP8266 as replacement, after reset. In ESP8266 it is a server that gives a webpage
with two buttons, to turn on and off the gpioc13. Also the BLE does the same using the
mobile phone application "Serial Bluetooth Terminal" the message to turn on is "s00.",
and off "s01.".
Also "Serial WiFi Terminal" works.
Par ("192.168.1.53", "192.168.1.1", "255.255.255.0"), PORT 80.
****************************************************************/
#include "main.h"
/******/
#include "stm32fxxxrcc.h"
#include "armsystick.h"
#include "stm32fxxxrtc.h"
#include "stm32fxxxadc1.h"
#include "stm32fxxxusart1.h"
#include "stm32fxxxtim1and8.h"
#include "st7789.h"
/******/
#include "BT_Commands.h"
#include "ESP8266_Commands.h"
#include "armfunction.h"
#include "explode.h"
#include "webpages.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JMP_menu_repeat 5
#define ADC_DELAY 8
#define ADC_SAMPLE 4
#define STEP_DELAY 10
#define MAIN_MENU_DELAY 20
#define MAX_TOKENS 10
#define MAIN_BAUD 38400
#define PARSE_SIZE 2049
#define SUBPARSE_SIZE 513

EXPLODE_Handler PA;
char str[32];

void setup_usart1(void);

int main(void)
{
rcc()->inic();
systick_inic();
fpu_enable();
rtc()->inic();

_delay_ms(1);
HAL_Init();
char state[12];

adc1()->clock(1);
gpioa()->clock(1);
gpiob()->clock(1); // lcd0
gpioc()->clock(1); // gpioc13

setup_usart1();

PA = EXPLODE_enable();

U_byte Menu;
Menu.var = 8;
U_word adc_value;
adc_value.var = 0;
uint8_t count_1 = ADC_DELAY;
uint8_t n_sample = ADC_SAMPLE;
uint16_t incr_0 = 0;
uint8_t skip_0 = 0;
char* webpage_ptr = NULL;
size_t webpage_size = 0;
uint8_t link_ID = 0;

char parse[PARSE_SIZE + 1] = {0};
char sub_parse[SUBPARSE_SIZE + 1] = {0};

//const char unit = (char)0xDF; // degrees
char *tokens[MAX_TOKENS] = {NULL}; // Array of pointers to hold token addresses
char *sub_tokens[MAX_TOKENS] = {NULL}; // Array of pointers to hold token addresses

ST7789 lcd1 = st7789_enable(dev()->spi1, 2, 3, 4, NULL);

gpioc()->moder(13,1);
gpioa()->moder(0,0);
gpioa()->pupd(0,1);

FUNC_enable();
adc1()->temperature_setup();

char vecD[8]; // for calendar date
char vecT[8]; // for calendar time
PA.update(&PA.par, dev()->gpioa->IDR);

dev()->gpioc->BSRR = GPIO_BSRR_BS13;

lcd1.start(&lcd1.par);
lcd1.draw_circle(&lcd1.par,200,80,15,ST77XX_BLACK);
lcd1.draw_star5(&lcd1.par,200,80,15,5,ST77XX_GOLD);
lcd1.stop(&lcd1.par);

Turingi1to11_Wifi_Connect(1, "NOS-9C64", "RUSXRCKL" ); // wmode 1 and 3
tm_jumpstep( 0, 22 );
/*****************************************************************************/
/*****************************************************************************/
while (1) {
	Turingi22to24_Station_Mux1Server( );

	PA.update(&PA.par, dev()->gpioa->IDR);

	/*** Magic ***/
	if( !isCharPtrFlush(usart1()->rxbuff) && usart1()->is_rx_idle() ){
			strncpy( parse, usart1()->rxbuff, PARSE_SIZE );
			func()->tokenize_string( parse, tokens, MAX_TOKENS, "\r\n" );
			if(tokens[0] && !isCharPtrFlush(tokens[0])) {
				strncpy( sub_parse, tokens[0], SUBPARSE_SIZE ); // 0
				func()->tokenize_string( sub_parse, sub_tokens, MAX_TOKENS, ",:" );
			}
			usart1()->rx_purge();
	}

   lcd1.start(&lcd1.par);
   lcd1.drawstring16x24_size(&lcd1.par,tokens[0],10,40,ST77XX_YELLOW,ST77XX_GREEN, 20);
   lcd1.stop(&lcd1.par);
   //lcd0()->gotoxy(3, 0); lcd0()->string_size( tokens[1], 11 ); //3

   if (!tm_getstep()) { // avoid simultaneous calls
	   /*** IPD || CONNECT ***/
	   char connectStr[16];
	   for (int i = 0; i < 16; i++) {
		   sprintf(connectStr, "%d,CONNECT", i);
		   if (strstr(tokens[0], connectStr)) {
			   link_ID = i;
			   break;
		   }
		   sprintf(connectStr, "+IPD,%d", i);
		   if (strstr(tokens[0], connectStr)) {
			   link_ID = i;
			   break;
		   }
	   }

	   // Handle Status Fetch safely
	   if ((tokens[0] && strstr(tokens[0], "status")) ||
		   (tokens[1] && strstr(tokens[1], "status")))
	   {
		   char* status_text = (dev()->gpioc->ODR & (1 << 13)) ? "OFF" : "ON";
		   tm_setstep(25);
		   Turingi25to28_Station_Mux1ServerSend_tcp(link_ID, status_text, strlen(status_text));
		   continue; // skip the rest of the loop for this request
	   }

	   // Check for "GET / HTTP" in tokens[1]
	   if ( strstr(tokens[0], "GET / HTTP") || strstr(tokens[1], "GET / HTTP") ) {
		   webpage_ptr = webpage_2().str;
		   webpage_size = webpage_2().size;
		   tm_setstep(25);
	   }

	   // Check for "Button%201" or "Button%202" in tokens[1]
	   if ( strstr(tokens[0], "Button1") || strstr(tokens[1], "Button1")
		   ) {
		   // Implement device ON functionality here
		   webpage_ptr = webpage_200().str;
		   webpage_size = webpage_200().size;
		   gpioc()->clear_hpins(1 << 13);
		   tm_setstep(25);
	   }
	   else if ( strstr(tokens[0], "Button2") || strstr(tokens[1], "Button2")
	   ) {
		   // Implement device OFF functionality here
		   webpage_ptr = webpage_200().str;
		   webpage_size = webpage_200().size;
		   gpioc()->set_hpins(1 << 13);
		   tm_setstep(25);
	   }

   }

	Turingi25to28_Station_Mux1ServerSend_tcp( link_ID, (const char*)webpage_ptr , webpage_size ); // link_ID

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
				lcd1.drawstring16x24_size(&lcd1.par,str,10,80,ST77XX_MAGENTA,ST77XX_GREEN, 8);
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

	lcd1.start(&lcd1.par);
	lcd1.drawstring16x24_size(&lcd1.par,state,10,10,ST77XX_BLACK,ST77XX_GREEN, 12);

	func()->format_string(str,32,"%d%d-%d%d-20%d%d",vecD[5], vecD[6], vecD[3], vecD[4], vecD[0], vecD[1]);

	lcd1.drawstring16x24(&lcd1.par,str,10,120,ST77XX_BLACK,ST77XX_GREEN);

	lcd1.drawstring12x16(&lcd1.par,(char*)WeekDay_String(vecD[2]),10,160,ST77XX_BLACK,ST77XX_GREEN);

	func()->format_string(str,32,"%d%d:%d%d:%d%d",vecT[0], vecT[1], vecT[2], vecT[3], vecT[4], vecT[5]);

	lcd1.drawstring16x24(&lcd1.par,str,10,200,ST77XX_RED,ST77XX_GREEN);
	lcd1.stop(&lcd1.par);

	/***/
	if(!strcmp(sub_tokens[3],"s01.")){
		gpioc()->set_hpins(1 << 13);
	}
	if(!strcmp(sub_tokens[3],"s00.")){
		gpioc()->clear_hpins(1 << 13);
	}
	if(!strcmp(sub_tokens[0],"s01.")){
		gpioc()->set_hpins(1 << 13);
   }
	if(!strcmp(sub_tokens[0],"s00.")){
		gpioc()->clear_hpins(1 << 13);
   }
	/***/
}}

void setup_usart1(void){
	usart1()->clock(1);

	// Set PA9 and PA10 to alternate function mode
	gpioa()->moder(9,MODE_AF); gpioa()->moder(10,MODE_AF);

	// Set alternate function type to AF7 (USART1) for PA9 and PA10
	gpioa()->af(9,7); gpioa()->af(10,7); // Set AF7 for PA9 and PA10

	// Set PA9 as push-pull output, high speed
	gpioa()->ospeed(9,3); gpioa()->ospeed(10,3); // High speed for PA9, PA10
	gpioa()->otype(9,0); gpioa()->otype(10,0);  // Set to push-pull
	gpioa()->pupd(9,1); gpioa()->pupd(10,1); // No pull-up, no pull-down

	// Set USART1 baud rate
	usart1()->samplingmode( 0, MAIN_BAUD );

	// Interrupt handler setup
	usart1()->tx_einterrupt(1);
	usart1()->rx_neinterrupt(1);
	usart1()->nvic(1);

	// Enable USART1, TX, RX
	usart1()->tx(1); usart1()->rx(1); // Enable transmitter and receiver
	usart1()->start(); // Enable USART1
}

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

