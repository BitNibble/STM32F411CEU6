/**************************************************************************
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Software: STM32CubeIDE v1.16.0 Build: 21983_20240628_1741 (UTC)
Hardware: STM32F411CEU6 by DevBox
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
void tim1_u_callback(void);

int main(void)
{
	rcc()->inic(); // Clock Configuration
	systick_inic(); // Delays
	gpioa()->clock(1);
	gpiob()->clock(1); // LCD display 4x20
	gpioc()->clock(1); // Gpioc13
	tim1()->clock(1); // Blink led at uie (4)

	rtc()->inic();

	char vecT[8]; // for calendar

	ARMLCD0_enable( dev()->gpiob );
	FUNC_enable();

	GPIOC->MODER |= GPIO_MODER_MODER13_0;
	gpioa()->moder(5,1);

	dev()->tim1->ARR = 0xFFFF;
	dev()->tim1->PSC = 100;
	tim1()->nvic(4);
	tim1()->callback->u = tim1_u_callback;
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

void tim1_u_callback(void){
	dev()->gpioc->ODR ^= GPIO_ODR_ODR_13;
	dev()->gpioa->ODR ^= GPIO_ODR_ODR_5;
}

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

