/******************************************************************************
	STM32 FXXX RTC
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-FXXX
Date: 19062023
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXRTC_H_
	#define _STM32FXXXRTC_H_
/*** Library ***/
#include "stm32fxxxinstance.h"
/*** Define & Macro ***/
#ifndef RTC_KEY1
	#define RTC_KEY1 0xCA
#endif
#ifndef RTC_KEY2
	#define RTC_KEY2 0x53
#endif
#ifndef DATA_BITS
	#define DATA_BITS 31
#endif
#ifndef DATA_SIZE
	#define DATA_SIZE 32
#endif
/*** RTC Interrupt Enum ***/
typedef enum {
    RTC_ENABLE_WAKEUP = 0b01,
    RTC_ENABLE_ALARM = 0b10,
    RTC_DISABLE_WAKEUP = 0b101,
    RTC_DISABLE_ALARM = 0b110
} RTC_Config;
/*** RTC TypeDef ***/
typedef struct
{
	RTC_TypeDef* instance;
	/***/
	uint8_t (*get_Year)(void);
	uint8_t (*get_Month)(void);
	uint8_t (*get_WeekDay)(void);
	uint8_t (*get_Day)(void);
	uint8_t (*get_Hour)(void);
	uint8_t (*get_Minute)(void);
	uint8_t (*get_Second)(void);
	void (*Day)(uint8_t day);
	void (*Month)(uint8_t month);
	void (*WeekDay)(uint8_t weekday);
	void (*Year)(uint8_t year);
	void (*Hour)(uint8_t hour);
	void (*Minute)(uint8_t minute);
	void (*Second)(uint8_t second);
	void (*dr2vec)(char* rtc_vect);
	void (*tr2vec)(char* rtc_vect);
	void (*BckWrite)(uint8_t registerIndex, uint8_t data);
	uint8_t (*BckRead)(uint8_t registerIndex);
	uint16_t (*get_ss)(void);
	/*** Other ***/
	void (*pwr_clock)(uint8_t state);
	void (*bck_sram_clock)(uint8_t state);
	void (*clock)(uint8_t isEnabled);
	void (*inic)(uint8_t clock);
	void (*nvic)(uint8_t config);
}STM32FXXX_RTC;
/***/

/*** Global ***/
void rtc_enable(void);
STM32FXXX_RTC* rtc(void);

/*** RTC Procedure & Function Header ***/
void STM32FXXXConfigureRtcClock(uint8_t isEnabled);
void STM32FXXXConfigureRtcInterrupt(uint8_t config);
void STM32FXXXRtcInic(uint8_t clock);
void STM32FXXXRtcBckWrite(uint8_t registerIndex, uint8_t data);
uint8_t STM32FXXXRtcBckRead(uint8_t registerIndex);
uint8_t STM32FXXXRtc_get_Year(void);
uint8_t STM32FXXXRtc_get_Month(void);
uint8_t STM32FXXXRtc_get_WeekDay(void);
uint8_t STM32FXXXRtc_get_Day(void);
uint8_t STM32FXXXRtc_get_Hour(void);
uint8_t STM32FXXXRtc_get_Minute(void);
uint8_t STM32FXXXRtc_get_Second(void);
void STM32FXXXRtcHour(uint8_t hour);
void STM32FXXXRtcMinute(uint8_t minute);
void STM32FXXXRtcSecond(uint8_t second);
void STM32FXXXRtcDay(uint8_t day);
void STM32FXXXRtcYear(uint8_t year);
void STM32FXXXRtcMonth(uint8_t month);
void STM32FXXXRtcWeekDay(uint8_t weekday);
void STM32FXXXRtcdr2vec(char* rtc_vect);
void STM32FXXXRtctr2vec(char* rtc_vect);
/*** General RTC Function Prototypes ***/
const char* WeekDay_String(uint8_t weekday_n);

/*** INTERRUPT ***/
void RTC_WKUP_IRQHandler(void);
void RTC_Alarm_IRQHandler(void);

#endif

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

