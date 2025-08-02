/**********************************************************************
Author: Sergio Santos
<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32F4x1 mini_F4x1 Ver. V20 SN: 202005 DevEBox
Board Site: mcudev.taobao.com
Date: 28022024
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
	PC13 - LED blink
***********************************************************************/
#include "main.h"

#include "stm32fxxxrcc.h"
#include "stm32fxxxrtc.h"
#include "armsystick.h"
#include "stm32fxxxgpio.h"
#include "stm32fxxxtim1and8.h"

#include "armlcd.h"
#include "armfunction.h"
#include "explode.h"

uint16_t count0 = 0;
uint16_t count1 = 0;
uint16_t count2 = 0;
uint16_t count3 = 0;
uint16_t count4 = 0;
uint16_t count5 = 0;
uint16_t count6 = 0;
uint16_t count7 = 0;
uint16_t count8 = 0;
int8_t cdir;

EXPLODE PA;

I2C_HandleTypeDef i2c;

char str[33];

/** TIM1 CC IRQn CallBack ***/
/**
void tim1_u_callback(void){
	count1++;
}
**/
void tim1_cc1_callback(void){
	//count2++;
	//count8=tim1()->cnt->par.w0;
	GPIOC->BSRR = GPIO_BSRR_BR13;
}
void tim1_cc2_callback(void){
	//count3++;
	TIM1->CCR1 += (cdir * 295);
	if(TIM1->CCR1 > TIM1->CCR2 - 100){ cdir = -1; }
	if(TIM1->CCR1 < (1000 + 100)){ cdir = 1; }
	//count8=tim1()->cnt->par.w0;
	GPIOC->BSRR = GPIO_BSRR_BS13;
}
/**/

int main(void)
{
	rcc_start();
	systick_start();
	rtc_enable();
	gpiob_enable();
	gpioc_enable();
	tim1()->clock(ON);

	rtc()->inic(1);

	PA = EXPLODE_enable();

	gpiob()->clock(ON); // lcd and i2c
	gpioc()->clock(ON); // gpioc13
	gpioa()->clock(ON); // timer 1 pwm af channel 1 and K0 button

	i2c.Instance  = I2C1;

	//setup i2c io
	//rcc()->instance->apb1enr.par.i2c1en = 1;
	set_reg_Msk(&RCC->APB1ENR, RCC_APB1ENR_I2C1EN_Msk, 1);
	//PB5 I2C1_SMBA
	//gpiob()->instance->afr.par.pin_6 = 4; // PB6 AF4 (I2C1..3) I2C1_SCL
	//gpiob()->instance->afr.par.pin_7 = 4; // PB7 AF4 (I2C1..3) I2C1_SDA
	//gpiob()->instance->moder.par.pin_6 = 1;
	//gpiob()->instance->moder.par.pin_7 = 1;
	//gpiob()->instance->pupdr.par.pin_6 = 1;
	//gpiob()->instance->pupdr.par.pin_7 = 1;

	//setup i2c parameters
	//i2c1_instance()->cr2.par.freq = query()->pclk1 / 1000000;
	//i2c1_instance()->trise.par.trise = (query()->pclk1 / 1000000) + 1;
	i2c.Init.ClockSpeed = 100000;
	i2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
	i2c.Init.OwnAddress1 = 'A';
	i2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	i2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	i2c.Init.OwnAddress2 = 'A';
	i2c.Init.GeneralCallMode = I2C_GENERALCALL_ENABLE;
	i2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	//Initialise parameters
	if (HAL_I2C_Init(&i2c) != HAL_OK)
	{
		Error_Handler();
	}

	ARMLCD0_enable((GPIO_TypeDef*)gpiob()->instance);
	FUNC_enable();

	//gpioc()->instance->moder.par.pin_1 = 1;
	set_reg_Msk(&GPIOC->MODER, GPIO_MODER_MODE13_Msk, 1);

	tim1()->nvic(1);
	//stm()->tim1->nvic(17);
	tim1()->clock(ON);

	set_reg_Msk(&GPIOA->AFR[0], GPIO_AFRL_AFSEL7_Msk, 1); // pin 7 af tim1ch1n
	set_reg_Msk(&GPIOA->AFR[1], GPIO_AFRH_AFSEL8_Msk, 1); // pin 8 af tim1ch1
	set_reg_Msk(&GPIOA->MODER, GPIO_MODER_MODE7_Msk, 2); // AF enable
	set_reg_Msk(&GPIOA->MODER, GPIO_MODER_MODE8_Msk, 2); // AF enable

	set_reg_Msk(&TIM1->CCMR1, TIM_CCMR1_OC1M_Msk, 6);
	set_reg_Msk(&TIM1->CCER, TIM_CCER_CC1NE_Msk, 1);
	set_reg_Msk(&TIM1->CCER, TIM_CCER_CC1E_Msk, 1);
	set_reg_Msk(&TIM1->BDTR, TIM_BDTR_MOE_Msk, 1);
	TIM1->ARR = 0xFFFF;
	// Compare
	TIM1->CCR1 = 1000;
	TIM1->CCR2 = 60000;
	// pre-scaler
	TIM1->PSC = 1;
	// interrupt
	set_reg_Msk(&TIM1->DIER, TIM_DIER_CC1IE_Msk, 1);
	set_reg_Msk(&TIM1->DIER, TIM_DIER_CC2IE_Msk, 1);
	// other
	//tim1()->instance->dier.tim1and8_par.comie = 1;
	//tim1()->instance->dier.tim1and8_par.tie = 0;
	//tim1()->instance->dier.tim1and8_par.bie = 0;
	//
	//tim1()->instance->dier.tim1and8_par.ude = 1;
	//tim1()->instance->dier.tim1and8_par.cc1de = 1;

	// Enable (Start/Stop)
	set_reg_Msk(&TIM1->CR1, TIM_CR1_ARPE_Msk, 1);
	set_reg_Msk(&TIM1->CR1, TIM_CR1_CEN_Msk, 1);

	char vecT[8]; // for calendar
	//char vecD[8]; // for calendar
	//rtc()->Year(24);
	//rtc()->Month(1);
	//rtc()->Day(1);
	//rtc()->Hour(12);
	//rtc()->Minute(0);
	//rtc()->Second(0);
	cdir = 1;

	//HAL_I2C_Master_Transmit( &i2c, devaddr, pdata, size, timeout );

	//rtc()->BckWrite(2,23);

	while (1){
		/*** preamble ***/
		PA.update(&PA.par, GPIOA->IDR);
		/******/

		lcd0()->gotoxy(0,0);
		lcd0()->string_size(func()->ui32toa(TIM1->ARR),6); lcd0()->string_size(func()->ui32toa(TIM1->CCR1),6); lcd0()->string_size(func()->ui32toa(TIM1->CCR2),6);

		//lcd0()->gotoxy(1,0);
		//lcd0()->string_size(func()->ui32toa(count1),6); lcd0()->string_size(func()->i32toa(count2),6); lcd0()->string_size(func()->i32toa(count3),6);

		lcd0()->gotoxy(2,0);
		//lcd0()->string_size(func()->ui32toa(count4),6); lcd0()->string_size(func()->i32toa(count5),6); lcd0()->string_size(func()->i32toa(count6),6);
		//lcd0()->string_size(func()->print_binary(16,tim1()->cr1->reg),17);
		rtc()->tr2vec(vecT);
		func()->format_string(str,32,"hora: %d%d:%d%d:%d%d", vecT[0],vecT[1],vecT[2],vecT[3],vecT[4],vecT[5]);
		lcd0()->string_size(str,14);

		lcd0()->gotoxy(3,0);
		//lcd0()->string_size(func()->ui32toa(count4),6); lcd0()->string_size(func()->ui32toa(count5),6); lcd0()->string_size(func()->ui32toa(count7),6);
		//lcd0()->string_size(func()->print_v2("pclk1: %d", query()->pclk1()),14);
		lcd0()->string(func()->i32toa(rtc()->BckRead(2)));

	}
}
/*** END MAIN ***/

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

/*** EOF ***/

