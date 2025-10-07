/******************************************************************************
Author: Sergio Santos
<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32
Date: 28052023
	Comment:
LCD
	PB3 - RS
	PB4 - RW
	PB5 - E
	PB6 - D4
	PB7 - D5
	PB8 - D6
	PB9 - D7
********************************************************************************/
#include "main.h"

#include "stm32fxxxrcc.h"
#include "armsystick.h"
#include "stm32fxxxgpio.h"

#include "armlcd.h"
#include "armfunction.h"

char time[12];
//rtc()->BckWrite(0,65);

void blink(void);

int main(void)
{
	rcc_start();
	systick_start();
	gpiob()->clock(1);
	gpioc()->clock(1);
	gpioc()->moder(13,1);

	ARMLCD0_enable(GPIOB);
	FUNC_enable();

	while (1)
	{
		func()->arm->dispar4x20(lcd0());

		ftdelayCycles(1, 3, blink);
	}
}
/*******************************************************************************/
/*******************************************************************************/

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

void blink(void){
	stm32f411ceu6()->gpioc->ODR ^= (1 << 13);
}
