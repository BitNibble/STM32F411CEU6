/**************************************************************************
Author: Sergio Santos
<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32F4x1 mini_F4x1 Ver. V20 SN: 202005 DevEBox
Board Site: mcudev.taobao.com
Date: 22022024
	Comment:
LCD
	PB3 - RS
	PB4 - RW
	PB5 - E
	PB6 - D4
	PB7 - D5
	PB8 - D6
	PB9 - D7
LED Blinking
	PB13 - LED blink
***************************************************************************/
#include "main.h"

#include "stm32fxxxrcc.h"
#include "stm32fxxxrtc.h"
#include "armsystick.h"
#include "stm32fxxxgpio.h"
#include "stm32fxxxtim1and8.h"

#include "armlcd.h"
#include "armfunction.h"

char str[33];

int main(void)
{
	rcc_start(); // Clock Configuration
	systick_start(); // Delays
	rtc_enable(); // Real Time Clock
	gpiob_enable(); // LCD display 4x20
	gpioc_enable(); // Gpioc13
	tim1()->clock(ON); // Blink led at uie (4)

	rtc()->inic(1);

	char vecT[8]; // for calendar

	ARMLCD0_enable(gpiob()->instance);
	FUNC_enable();

	GPIOC->MODER |= GPIO_MODER_MODER13_0;

	tim1()->reg->ARR = 0xFFFF;
	tim1()->reg->PSC = 100;
	tim1()->nvic(4);
	tim1()->start();

	while (1){
		lcd0()->gotoxy(0,0);
		lcd0()->string_size("Welcome",7);
		lcd0()->gotoxy(1,0);
		lcd0()->string_size(func()->ftoa((double)33/654,8),20);

		lcd0()->gotoxy(2,0);
		//lcd0()->string_size(func()->ui32toa(count4),6); lcd0()->string_size(func()->i32toa(count5),6); lcd0()->string_size(func()->i32toa(count6),6);
		//lcd0()->string_size(func()->print_binary(16,tim1()->cr1->reg),17);
		rtc()->tr2vec(vecT);
		func()->format_string(str,32,"hora: %d%d:%d%d:%d%d", vecT[0],vecT[1],vecT[2],vecT[3],vecT[4],vecT[5]);
		lcd0()->string_size(str,20);

	}
}

void tim1_u_callback(void){ gpioc()->instance->ODR ^= GPIO_ODR_ODR_13; }

void Error_Handler(void)
{
	__disable_irq();
	while (1)
	{
	}
}
#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif

