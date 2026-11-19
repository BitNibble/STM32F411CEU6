/******************************************************************************
	STM32 FXXX RTC
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-FXXX
Date: 19062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxrtc.h"

#define ON 1
#define OFF 0

#define RTC_CLOCK_ENABLE_BIT 15
#define MAX_BACKUP_REGISTERS 80
#define BACKUP_REGISTER_BITS 8
#define HOUR_MASK 0x003F0000
#define HOUR_TENS_SHIFT 20
#define HOUR_UNITS_SHIFT 16
#define MAX_HOUR 23
#define MINUTE_MASK 0x00007F00
#define MINUTE_TENS_SHIFT 12
#define MINUTE_UNITS_SHIFT 8
#define MAX_MINUTE 59
#define SECOND_MASK 0x0000007F
#define SECOND_TENS_SHIFT 4
#define SECOND_UNITS_SHIFT 0
#define MAX_SECOND 59
#define YEAR_MASK 0x00FF0000
#define YEAR_TENS_SHIFT 20
#define YEAR_UNITS_SHIFT 16
#define MAX_YEAR 99
#define MONTH_MASK 0x00001F00
#define MONTH_TENS_SHIFT 12
#define MONTH_UNITS_SHIFT 8
#define MAX_MONTH 12
#define MIN_MONTH 1
#define WEEKDAY_MASK 0x0000E000
#define WEEKDAY_SHIFT 13
#define MAX_WEEKDAY 7
#define MIN_WEEKDAY 1
#define DAY_MASK 0x0000003F
#define DAY_TENS_SHIFT 4
#define DAY_UNITS_SHIFT 0
#define MAX_DAY 31
#define MIN_DAY 1
#define RTC_INIT_BIT (1 << 7)
#define RTC_INITF_BIT (1 << 6)
#define RTC_INIT_TIMEOUT 100
#define RTCSEL_LSI    0x02 // LSI oscillator clock
#define RTCSEL_LSE    0x01 // LSE oscillator clock
#define RTCSEL_HSE    0x03 // HSE oscillator clock

static STM32FXXX_RTC stm32fxxx_rtc = {0};
static uint32_t rtc_time_out;

/*** File Procedure & Function Header ***/
/***/
void STM32FXXXPwrClock(uint8_t state);
void STM32FXXXBckSramClock(uint8_t state);
void STM32FXXXRtcWriteEnable(void);
void STM32FXXXRtcWriteDisable(void);
void STM32FXXXRtcRegUnlock(void);
void STM32FXXXRtcRegWrite(volatile uint32_t* rtc_reg, uint32_t value);
void STM32FXXXRtcStopRead(void);
void STM32FXXXRtcWaitRead(void);
void STM32FXXXRtcSetTr(uint32_t value);
void STM32FXXXRtcSetDr(uint32_t value);
uint16_t rtc_get_ss(void);
char rtc_bcd2dec(char num);
char rtc_dec2bcd(char num);
void rtc_lenable(unsigned int lclock);
static void set_rtc_clock_source(uint8_t clock_source);
void rtc_lselect(uint8_t lclock);
/*** RTC Procedure & Function Definition ***/
void rtc_enable(void)
{
	stm32fxxx_rtc.instance = RTC;
	/***/
	stm32fxxx_rtc.get_Year = STM32FXXXRtc_get_Year;
	stm32fxxx_rtc.get_Month = STM32FXXXRtc_get_Month;
	stm32fxxx_rtc.get_WeekDay = STM32FXXXRtc_get_WeekDay;
	stm32fxxx_rtc.get_Day = STM32FXXXRtc_get_Day;
	stm32fxxx_rtc.get_Hour = STM32FXXXRtc_get_Hour;
	stm32fxxx_rtc.get_Minute = STM32FXXXRtc_get_Minute;
	stm32fxxx_rtc.get_Second = STM32FXXXRtc_get_Second;
	stm32fxxx_rtc.Day = STM32FXXXRtcDay;
	stm32fxxx_rtc.Month = STM32FXXXRtcMonth;
	stm32fxxx_rtc.WeekDay = STM32FXXXRtcWeekDay;
	stm32fxxx_rtc.Year = STM32FXXXRtcYear;
	stm32fxxx_rtc.Hour = STM32FXXXRtcHour;
	stm32fxxx_rtc.Minute = STM32FXXXRtcMinute;
	stm32fxxx_rtc.Second = STM32FXXXRtcSecond;
	stm32fxxx_rtc.dr2vec = STM32FXXXRtcdr2vec;
	stm32fxxx_rtc.tr2vec = STM32FXXXRtctr2vec;
	stm32fxxx_rtc.BckWrite = STM32FXXXRtcBckWrite;
	stm32fxxx_rtc.BckRead = STM32FXXXRtcBckRead;
	stm32fxxx_rtc.get_ss = rtc_get_ss;
	/*** Other ***/
	stm32fxxx_rtc.pwr_clock = STM32FXXXPwrClock;
	stm32fxxx_rtc.bck_sram_clock = STM32FXXXBckSramClock;
	stm32fxxx_rtc.clock = STM32FXXXConfigureRtcClock;
	stm32fxxx_rtc.nvic = STM32FXXXConfigureRtcInterrupt;
	stm32fxxx_rtc.inic = STM32FXXXRtcInic;

	//return &stm32fxxx_rtc;
}

STM32FXXX_RTC* rtc(void){ return (STM32FXXX_RTC*) &stm32fxxx_rtc; }

/*** Procedure & Function Definition ***/
void STM32FXXXConfigureRtcClock(uint8_t isEnabled) {
    STM32FXXXRtcWriteEnable();

    if (isEnabled) {
        RCC->BDCR |= (1 << RTC_CLOCK_ENABLE_BIT);  // Enable RTC clock
    } else {
        RCC->BDCR &= ~(1 << RTC_CLOCK_ENABLE_BIT); // Disable RTC clock
    }

    STM32FXXXRtcWriteDisable();
}

void STM32FXXXConfigureRtcInterrupt(uint8_t config) {
    switch(config) {
        case RTC_ENABLE_WAKEUP:
            set_bit_block(NVIC->ISER, 1, RTC_WKUP_IRQn, 1);
            break;
        case RTC_ENABLE_ALARM:
            set_bit_block(NVIC->ISER, 1, RTC_Alarm_IRQn, 1);
            break;
        case RTC_DISABLE_WAKEUP:
            set_bit_block(NVIC->ICER, 1, RTC_WKUP_IRQn, 1);
            break;
        case RTC_DISABLE_ALARM:
            set_bit_block(NVIC->ICER, 1, RTC_Alarm_IRQn, 1);
            break;
        default:
            // Optional: handle unexpected config value
            break;
    }
}

void STM32FXXXRtcInic(uint8_t clock)
{ // RM0390 pg657
	STM32FXXXPwrClock(ON);
	STM32FXXXBckSramClock(ON);
	STM32FXXXConfigureRtcClock(ON);

	rtc_lenable(clock);
	rtc_lselect(clock);

	STM32FXXXRtcStopRead();

	//STM32FXXXRtcWriteEnable();
	//STM32FXXXRtcRegUnlock();
	//STM32FXXXRtcRegWrite(&RTC->TR, 0x130000);
	//STM32FXXXRtcRegWrite(&RTC->DR, 0x215124);
	//RTC->CR &= (uint32_t) ~(1 << 5); // BYPSHAD: Disable Bypass the shadow registers
	//STM32FXXXRtcWriteDisable();
}

void STM32FXXXRtcBckWrite(uint8_t registerIndex, uint8_t data) {
    // Validate register index
    if (registerIndex >= MAX_BACKUP_REGISTERS) {
        // Handle error (e.g., return, assert, or log)
        return;
    }

    STM32FXXXPwrClock(ON);
    STM32FXXXBckSramClock(ON);
    STM32FXXXRtcWriteEnable();

    // Write data to the specified backup register
    set_bit_block(&RTC->BKP0R, BACKUP_REGISTER_BITS, (registerIndex * BACKUP_REGISTER_BITS), data);

    STM32FXXXRtcWriteDisable();
}

uint8_t STM32FXXXRtcBckRead(uint8_t registerIndex) {
    uint8_t value = 0;

    // Validate the register index
    if (registerIndex < MAX_BACKUP_REGISTERS) {
        value = get_bit_block(&RTC->BKP0R, BACKUP_REGISTER_BITS, (registerIndex * BACKUP_REGISTER_BITS));
    }

    return value;  // Returns 0 if the index is out of bounds
}

void STM32FXXXRtcHour(uint8_t hour) {
    // Validate the hour range (0-23)
    if (hour > MAX_HOUR) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    uint32_t Time = 0;
    uint8_t t, u;

    // Enable power clock for RTC
    STM32FXXXPwrClock(ON);

    // Convert hour to BCD format
    t = rtc_dec2bcd(hour / 10);
    u = rtc_dec2bcd(hour % 10);

    // Wait for RTC to be ready for reading
    STM32FXXXRtcWaitRead();

    // Read current Time register
    Time = RTC->TR;

    // Clear current hour bits (ht and hu)
    Time &= ~HOUR_MASK;

    // Set new hour bits (hu and ht)
    Time |= (uint32_t)((u << HOUR_UNITS_SHIFT) | (t << HOUR_TENS_SHIFT));

    // Write back to the Time register
    STM32FXXXRtcSetTr(Time);

    // Disable power clock for RTC
    STM32FXXXPwrClock(OFF);
}

void STM32FXXXRtcMinute(uint8_t minute) {
    // Validate the minute range (0-59)
    if (minute > MAX_MINUTE) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    uint32_t Time;
    uint8_t t, u;

    // Enable power clock for RTC
    STM32FXXXPwrClock(ON);

    // Convert minute to BCD format
    t = rtc_dec2bcd(minute / 10);
    u = rtc_dec2bcd(minute % 10);

    // Wait for RTC to be ready for reading
    STM32FXXXRtcWaitRead();

    // Read current Time register
    Time = RTC->TR;

    // Clear current minute bits (mnt and mnu)
    Time &= ~MINUTE_MASK;

    // Set new minute bits (mnu and mnt)
    Time |= (uint32_t)((u << MINUTE_UNITS_SHIFT) | (t << MINUTE_TENS_SHIFT));

    // Write back to the Time register
    STM32FXXXRtcSetTr(Time);

    // Disable power clock for RTC
    STM32FXXXPwrClock(OFF);
}

void STM32FXXXRtcSecond(uint8_t second) {
    // Validate the second range (0-59)
    if (second > MAX_SECOND) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    uint32_t Time;
    uint8_t t, u;

    // Enable power clock for RTC
    STM32FXXXPwrClock(ON);

    // Convert second to BCD format
    t = rtc_dec2bcd(second / 10);
    u = rtc_dec2bcd(second % 10);

    // Wait for RTC to be ready for reading
    STM32FXXXRtcWaitRead();

    // Read current Time register
    Time = RTC->TR;

    // Clear current second bits (st and su)
    Time &= ~SECOND_MASK;

    // Set new second bits (su and st)
    Time |= (uint32_t)((u << SECOND_UNITS_SHIFT) | (t << SECOND_TENS_SHIFT));

    // Write back to the Time register
    STM32FXXXRtcSetTr(Time);

    // Disable power clock for RTC
    STM32FXXXPwrClock(OFF);
}

void STM32FXXXRtcYear(uint8_t year) {
    // Validate the year range (0-99)
    if (year > MAX_YEAR) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    uint32_t Date;
    uint8_t t, u;

    // Enable power clock for RTC
    STM32FXXXPwrClock(ON);

    // Convert year to BCD format
    t = rtc_dec2bcd(year / 10);
    u = rtc_dec2bcd(year % 10);

    // Wait for RTC to be ready for reading
    STM32FXXXRtcWaitRead();

    // Read current Date register
    Date = RTC->DR;

    // Clear current year bits (YT and YU)
    Date &= ~YEAR_MASK;

    // Set new year bits (YU and YT)
    Date |= (uint32_t)((u << YEAR_UNITS_SHIFT) | (t << YEAR_TENS_SHIFT));

    // Write back to the Date register
    STM32FXXXRtcSetDr(Date);

    // Disable power clock for RTC
    STM32FXXXPwrClock(OFF);
}

void STM32FXXXRtcMonth(uint8_t month) {
    // Validate the month range (1-12)
    if (month < MIN_MONTH || month > MAX_MONTH) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    uint32_t Date;
    uint8_t t, u;

    // Enable power clock for RTC
    STM32FXXXPwrClock(ON);

    // Convert month to BCD format
    t = rtc_dec2bcd(month / 10);
    u = rtc_dec2bcd(month % 10);

    // Wait for RTC to be ready for reading
    STM32FXXXRtcWaitRead();

    // Read current Date register
    Date = RTC->DR;

    // Clear current month bits (MT and MU)
    Date &= ~MONTH_MASK;

    // Set new month bits (MU and MT)
    Date |= (uint32_t)((u << MONTH_UNITS_SHIFT) | (t << MONTH_TENS_SHIFT));

    // Write back to the Date register
    STM32FXXXRtcSetDr(Date);

    // Disable power clock for RTC
    STM32FXXXPwrClock(OFF);
}

void STM32FXXXRtcWeekDay(uint8_t weekday) {
    // Validate the weekday range (1-7)
    if (weekday < MIN_WEEKDAY || weekday > MAX_WEEKDAY) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    uint32_t Date;
    uint8_t u;

    // Enable power clock for RTC
    STM32FXXXPwrClock(ON);

    // Convert weekday to BCD format
    u = rtc_dec2bcd(weekday % 10); // Assuming weekday is represented as 1-7

    // Wait for RTC to be ready for reading
    STM32FXXXRtcWaitRead();

    // Read current Date register
    Date = RTC->DR;

    // Clear current weekday bits (WDU)
    Date &= ~WEEKDAY_MASK;

    // Set new weekday bits (WDU)
    Date |= (uint32_t)(u << WEEKDAY_SHIFT);

    // Write back to the Date register
    STM32FXXXRtcSetDr(Date);

    // Disable power clock for RTC
    STM32FXXXPwrClock(OFF);
}

void STM32FXXXRtcDay(uint8_t day) {
    // Validate the day range (1-31)
    if (day < MIN_DAY || day > MAX_DAY) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    uint32_t Date;
    uint8_t t, u;

    // Enable power clock for RTC
    STM32FXXXPwrClock(ON);

    // Convert day to BCD format
    t = rtc_dec2bcd(day / 10);
    u = rtc_dec2bcd(day % 10);

    // Wait for RTC to be ready for reading
    STM32FXXXRtcWaitRead();

    // Read current Date register
    Date = RTC->DR;

    // Clear current day bits (DT and DU)
    Date &= ~DAY_MASK;

    // Set new day bits (DU and DT)
    Date |= (uint32_t)((u << DAY_UNITS_SHIFT) | (t << DAY_TENS_SHIFT));

    // Write back to the Date register
    STM32FXXXRtcSetDr(Date);

    // Disable power clock for RTC
    STM32FXXXPwrClock(OFF);
}

void STM32FXXXRtcdr2vec(char* rtc_vect)
{
	if(RTC->ISR & (1 << 5)){ // RSF: Registers synchronisation flag
		uint32_t dr = RTC->DR;
		// YT
		rtc_vect[0] = (uint8_t) (dr >> 20) & 0x0F;
		rtc_vect[0] = rtc_bcd2dec(rtc_vect[0]);
		// YU
		rtc_vect[1] = (uint8_t) (dr >> 16) & 0x0F;
		rtc_vect[1] = rtc_bcd2dec(rtc_vect[1]);
		// WDU
		rtc_vect[2] = (uint8_t) (dr >> 13) & 0x07;
		rtc_vect[2] = rtc_bcd2dec(rtc_vect[2]);
		// MT
		rtc_vect[3] = (uint8_t) (dr >> 12) & 0x01;
		rtc_vect[3] = rtc_bcd2dec(rtc_vect[3]);
		// MU
		rtc_vect[4] = (uint8_t) (dr >> 8) & 0x0F;
		rtc_vect[4] = rtc_bcd2dec(rtc_vect[4]);
		// DT
		rtc_vect[5] = (uint8_t) (dr >> 4) & 0x03;
		rtc_vect[5] = rtc_bcd2dec(rtc_vect[5]);
		// DU
		rtc_vect[6] = (uint8_t) dr & 0x0F;
		rtc_vect[6] = rtc_bcd2dec(rtc_vect[6]);
		// Store Value
		// Clear Registers synchronisation flag
		RTC->ISR &= (uint32_t) ~(1 << 5);
	}
}

void STM32FXXXRtctr2vec(char* rtc_vect)
{
	if(RTC->ISR & (1 << 5)){ // RSF: Registers synchronisation flag
		uint32_t tr = RTC->TR;
		// ht
		rtc_vect[0] = (uint8_t) (tr >> 20) & 0x03;
		rtc_vect[0] = rtc_bcd2dec(rtc_vect[0]);
		// hu
		rtc_vect[1] = (uint8_t) (tr >> 16) & 0x0F;
		rtc_vect[1] = rtc_bcd2dec(rtc_vect[1]);
		// mnt
		rtc_vect[2] = (uint8_t) (tr >> 12) & 0x07;
		rtc_vect[2] = rtc_bcd2dec(rtc_vect[2]);
		// mnu
		rtc_vect[3] = (uint8_t) (tr >> 8) & 0x0F;
		rtc_vect[3] = rtc_bcd2dec(rtc_vect[3]);
		// st
		rtc_vect[4] = (uint8_t) (tr >> 4) & 0x07;
		rtc_vect[4] = rtc_bcd2dec(rtc_vect[4]);
		// su
		rtc_vect[5] = (uint8_t) tr & 0x0F;
		rtc_vect[5] = rtc_bcd2dec(rtc_vect[5]);
		// Store value
		// Clear Registers synchronisation flag
		RTC->ISR &= (uint32_t) ~(1 << 5);
	}
}

uint8_t STM32FXXXRtc_get_Year(void){
	STM32FXXXRtcWaitRead();
	uint32_t dr = RTC->DR;
	return rtc_bcd2dec((dr >> 16) & 0x00FF);
}
uint8_t STM32FXXXRtc_get_Month(void){
	STM32FXXXRtcWaitRead();
	uint32_t dr = RTC->DR;
	return rtc_bcd2dec((dr >> 8) & 0x001F);
}
uint8_t STM32FXXXRtc_get_WeekDay(void){
	STM32FXXXRtcWaitRead();
	uint32_t dr = RTC->DR;
	//return rtc_bcd2dec(get_reg_block(dr,3,13));
	return rtc_bcd2dec((dr >> 13) & 0x0007);
}
uint8_t STM32FXXXRtc_get_Day(void){
	STM32FXXXRtcWaitRead();
	uint32_t dr = RTC->DR;
	return rtc_bcd2dec(dr & 0x003F);
}
uint16_t rtc_get_ss(void)
{
	STM32FXXXRtcWaitRead();
	return RTC->SSR;
}

uint8_t STM32FXXXRtc_get_Hour(void){
	STM32FXXXRtcWaitRead();
	uint32_t tr = RTC->TR;
	return rtc_bcd2dec((tr >> 16) & 0x003F);
}
uint8_t STM32FXXXRtc_get_Minute(void){
	STM32FXXXRtcWaitRead();
	uint32_t tr = RTC->TR;
	return rtc_bcd2dec((tr >> 8) & 0x007F);
}
uint8_t STM32FXXXRtc_get_Second(void){
	STM32FXXXRtcWaitRead();
	uint32_t tr = RTC->TR;
	return rtc_bcd2dec(tr & 0x007F);
}

/*** AUX Procedure & Function Definition ***/
void STM32FXXXPwrClock(uint8_t state)
{
	set_reg_block(&RCC->APB1ENR, 1, 28, state); // Power interface clock enable
}
void STM32FXXXBckSramClock(uint8_t state)
{
	#ifdef STM32F446xx
		set_reg_block(&RCC->AHB1ENR, 1, 18, state); // Backup SRAM interface clock enable
	#endif
	set_reg_block(&RCC->AHB1LPENR, 1, 16, state); // Backup SRAM interface clock enable
}
void STM32FXXXRtcWriteEnable(void)
{
	PWR->CR |= (1 << 8); // Disable protection
}
void STM32FXXXRtcWriteDisable(void)
{
	PWR->CR &= (uint32_t) ~(1 << 8); // Enable protection
}
void STM32FXXXRtcRegUnlock(void)
{
	RTC->WPR |= RTC_KEY1;
	RTC->WPR |= RTC_KEY2;
}
void STM32FXXXRtcRegWrite(volatile uint32_t* rtc_reg, uint32_t value) {
    // Check if the register pointer is valid
    if (rtc_reg == NULL) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    // Set the INIT bit to enter initialization mode
    RTC->ISR |= RTC_INIT_BIT; // INIT

    // Wait for the INITF flag to be set, indicating that the RTC is ready
    uint32_t rtc_time_out = RTC_INIT_TIMEOUT;
    while (!(RTC->ISR & RTC_INITF_BIT) && rtc_time_out) {
        rtc_time_out--;
    }

    // Check for timeout
    if (!rtc_time_out) {
        // Optionally handle timeout error (e.g., return, assert, or log)
        RTC->ISR &= ~RTC_INIT_BIT; // Clear INIT bit
        return;
    }

    // Write the value to the specified RTC register
    *rtc_reg = value;

    // Clear the INIT bit to exit initialization mode
    RTC->ISR &= ~RTC_INIT_BIT;
}
void STM32FXXXRtcStopRead(void)
{
	RTC->ISR &= ~(1 << 5);
}
void STM32FXXXRtcWaitRead(void)
{ // Wait Data Ready
	for(rtc_time_out = 300; !(RTC->ISR & (1 << 5)) && rtc_time_out; rtc_time_out--);
}
//RTC
void STM32FXXXRtcSetTr(uint32_t value)
{
	STM32FXXXRtcWriteEnable();
	STM32FXXXRtcRegUnlock();
	STM32FXXXRtcRegWrite(&RTC->TR, value);
	STM32FXXXRtcWriteDisable();
}
void STM32FXXXRtcSetDr(uint32_t value)
{
	STM32FXXXRtcWriteEnable();
	STM32FXXXRtcRegUnlock();
	STM32FXXXRtcRegWrite(&RTC->DR, value);
	STM32FXXXRtcWriteDisable();
}
/*** COMMON ***/
char rtc_bcd2dec(char num)
{
	return ((num / 16 * 10) + (num % 16));
}
char rtc_dec2bcd(char num)
{
	return ((num / 10 * 16) + (num % 10));
}
void rtc_lenable(unsigned int lclock) {
    if (lclock > 2) {
        // Invalid clock selection; you might want to handle this error
        return;
    }

    unsigned int set = 1;
    unsigned int rdy = 1;

    while (rdy) {
        if (lclock == 0) { // Enable Internal Low-Speed Oscillator
            if (set) {
                STM32FXXXRtcWriteEnable();
                RCC->CSR |= RCC_CSR_LSION;
                STM32FXXXRtcWriteDisable();
                set = 0;
            } else if (RCC->CSR & RCC_CSR_LSIRDY) {
                rdy = 0; // Oscillator is ready
            }
        } else if (lclock == 1) { // Enable External Low-Speed Oscillator
            if (set) {
                STM32FXXXRtcWriteEnable();
                RCC->BDCR |= RCC_BDCR_LSEON;
                STM32FXXXRtcWriteDisable();
                set = 0;
            } else if (RCC->BDCR & RCC_BDCR_LSERDY) {
                rdy = 0; // Oscillator is ready
            }
        } else if (lclock == 2) { // Bypass External Low-Speed Oscillator
            if (set) {
                STM32FXXXRtcWriteEnable();
                RCC->BDCR |= RCC_BDCR_LSEBYP;
                STM32FXXXRtcWriteDisable();
            }
            lclock = 1; // Fall back to LSEON
        } else {
            lclock = 0; // Default to LSION
        }
    }
}
static void set_rtc_clock_source(uint8_t clock_source) {
    STM32FXXXRtcWriteEnable();
    set_reg_Msk(&RCC->BDCR, RCC_BDCR_RTCSEL_Msk, RCC_BDCR_RTCSEL_Pos, clock_source);
    STM32FXXXRtcWriteDisable();
}
void rtc_lselect(uint8_t lclock) {
    // Input validation
    if (lclock > 3) {
        // Invalid selection, default to LSI
        lclock = 0;
    }

    // Clear previous RTC selection
    STM32FXXXRtcWriteEnable();
    set_reg_Msk(&RCC->BDCR, RCC_BDCR_RTCSEL_Msk, RCC_BDCR_RTCSEL_Pos, 0);
    STM32FXXXRtcWriteDisable();

    // Set the selected clock source
    switch (lclock) {
        case 0:
            set_rtc_clock_source(RTCSEL_LSI);
            break;
        case 1:
            set_rtc_clock_source(RTCSEL_LSE);
            break;
        case 3:
            set_rtc_clock_source(RTCSEL_HSE);
            break;
        default:
            // Default case (redundant due to input validation, but kept for clarity)
            set_rtc_clock_source(RTCSEL_LSI);
            break;
    }
}
/*** General RTC Function Definitions ***/
const char* WeekDay_String(uint8_t weekday_n) {
    // Array of weekday strings, indexed from 0 to 7 for convenience
    const char* weekdays[] = {
        "Domingo", // 0 (unused)
        "Domingo", // 1
        "Segunda", // 2
        "Terca",   // 3
        "Quarta",  // 4
        "Quinta",  // 5
        "Sexta",   // 6
        "Sabado"   // 7
    };

    // Validate the input and return the corresponding weekday
    if (weekday_n >= 1 && weekday_n <= 7) {
        return weekdays[weekday_n];
    } else {
        return weekdays[1]; // Default to "domingo"
    }
}

/*** EOF ***/

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

