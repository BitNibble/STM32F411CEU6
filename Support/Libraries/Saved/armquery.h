/*************************************************************************
	ARMQUERY
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License     
Hardware: STM32QUERY
Date: 10/01/2024
Update: 
Comment:
	Tested STM32F446RE || STM32F411CEU6
************************************************************************/
#ifndef _ARMQUERY_H_
	#define _ARMQUERY_H_
/*** File Library ***/
#include <inttypes.h>
/*** File Constant & Macro ***/
#ifndef HSI_RC
	#define HSI_RC 16000000UL
#endif
#ifndef HSE_OSC
	#define HSE_OSC 25000000UL
#endif
#ifndef LSI
	#define LSI 32000UL
#endif
#ifndef LSE
	#define LSE 32768UL
#endif
#ifndef HSE_RTC
	#define HSE_RTC 4000000UL
#endif
/*******   0 -> HSI    1->HSE   *********/
#define H_Clock_Source 1
/****************************************/
/****   PLL ON -> 1    PLL OFF = 0   ****/
#define PLL_ON_OFF 0
/****************************************/
#ifndef on
	#define on 1
#endif
#ifndef ON
	#define ON 1
#endif
#ifndef off
	#define off 0
#endif
#ifndef OFF
	#define OFF 0
#endif
#ifndef yes
	#define yes 1
#endif
#ifndef YES
	#define YES 1
#endif
#ifndef no
	#define no 0
#endif
#ifndef NO
	#define NO 0
#endif
/****************************************/

typedef struct{
uint16_t (*AHB)(void);
uint8_t (*APB1)(void);
uint8_t (*APB2)(void);
uint8_t (*RTCclk)(void);
uint8_t (*MCO1)(void);
uint8_t (*MCO2)(void);
}STM32FXXXSYSTEM_prescaler;
typedef struct{
uint8_t (*M)(void);
uint16_t (*N)(void);
uint8_t (*P)(void);
uint8_t (*Q)(void);
uint8_t (*R)(void);
}STM32FXXXPLL_prescaler;
typedef struct{
STM32FXXXSYSTEM_prescaler* System_prescaler;
STM32FXXXPLL_prescaler* Pll_prescaler;
uint32_t (*PllClock)(void);
uint32_t (*SystemClock)(void);
uint32_t (*hclk)(void);
uint32_t (*pclk1)(void);
uint32_t (*pclk2)(void);
}STM32FXXX_Query;

STM32FXXX_Query query_enable(void);
STM32FXXX_Query* query(void);

/*** Clock ***/
uint32_t getpllsourceclk(void);
/*** -----> ***/
// HSI
// HSE
uint32_t getpllclk(void);
/*** -----> ***/
uint32_t getsysclk(void);
uint32_t gethclk(void);
uint32_t getpclk1(void);
uint32_t getpclk2(void);

/*** Scaler ***/
uint16_t gethpre(void);
uint8_t gethppre1(void);
uint8_t gethppre2(void);
uint8_t getrtcpre(void);
uint8_t gethmco1pre(void);
uint8_t gethmco2pre(void);
uint8_t getpllm(void);
uint16_t getplln(void);
uint8_t getpllp(void);
uint8_t getpllq(void);
uint8_t getpllr(void);

/****** MISCELLANEOUS ******/
void enable_fpu(void);

#endif

/***EOF***/

