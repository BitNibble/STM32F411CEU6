/******************************************************************************
	STM32 FXXX RTC
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-FXXX
Date:     19062023
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXRTC_H_
	#define _STM32FXXXRTC_H_

/*** Library ***/
#include "stm32f411ceu6.h"
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
} RTC_NVIC_config;
typedef enum {
	RTC_IRQ_ALARM = 0,
	RTC_IRQ_WAKEUP,
	RTC_IRQ_TAMPER,
	RTC_IRQ_TS,
} RTC_IRQ_config;
typedef struct {
    void (*Alarm)(void);
    void (*WakeUp)(void);
    void (*TimeStamp)(void);
    void (*Tamper)(void);
    void (*Overrun)(void);
} RTC_callback;
/*** RTC TypeDef ***/
typedef struct
{
	/***/
	uint8_t (*get_year)(void);
	uint8_t (*get_month)(void);
	uint8_t (*get_weekday)(void);
	uint8_t (*get_day)(void);
	uint8_t (*get_hour)(void);
	uint8_t (*get_minute)(void);
	uint8_t (*get_second)(void);
	void (*set_day)(uint8_t day);
	void (*set_month)(uint8_t month);
	void (*set_weekday)(uint8_t weekday);
	void (*set_year)(uint8_t year);
	void (*set_hour)(uint8_t hour);
	void (*set_minute)(uint8_t minute);
	void (*set_second)(uint8_t second);
	void (*dr2vec)(char* rtc_vect);
	void (*tr2vec)(char* rtc_vect);
	void (*bkp_write)(uint8_t registerIndex, uint8_t data);
	uint8_t (*bkp_read)(uint8_t registerIndex);
	uint16_t (*get_ss)(void);
	/*** Clock and Nvic ***/
	void (*pwr_clock)(uint8_t state);
	void (*bkp_sram_clock)(uint8_t state);
	void (*clock)(uint8_t isEnabled);
	void (*inic)(void);
	void (*nvic)(uint8_t config);
	void (*irq_enable)(uint8_t type);
	void (*irq_disable)(uint8_t type);
	RTC_callback* callback;
}STM32FXXX_RTC_Handler;

/*** Global ***/
STM32FXXX_RTC_Handler* rtc(void);

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

