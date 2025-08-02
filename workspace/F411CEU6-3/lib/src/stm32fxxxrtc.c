/******************************************************************************
	STM32 FXXX RTC
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-FXXX
Date:     19062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32fxxxrtc.h"

/*** Define and Macro ***/
#define MAX_BACKUP_REGISTERS 80
#define MAX_HOUR 23
#define MAX_MINUTE 59
#define MAX_SECOND 59
#define MAX_YEAR 99
#define MAX_MONTH 12
#define MIN_MONTH 1
#define MAX_WEEKDAY 7
#define MIN_WEEKDAY 1
#define MAX_DAY 31
#define MIN_DAY 1
#define RTC_INIT_TIMEOUT 100
#define RTCSEL_LSI    0x02 // LSI oscillator clock
#define RTCSEL_LSE    0x01 // LSE oscillator clock
#define RTCSEL_HSE    0x03 // HSE oscillator clock

static STM32FXXX_RTC stm32fxxx_rtc = {0};
static uint32_t rtc_time_out;

/*** File Procedure & Function Header ***/
/***/
void RTC_PwrClock(uint8_t state);
void RTC_BckSramClock(uint8_t state);
void RTC_WriteEnable(void);
void RTC_WriteDisable(void);
void RTC_RegUnlock(void);
void RTC_RegWrite(volatile uint32_t* rtc_reg, uint32_t value);
void RTC_StopRead(void);
void RTC_WaitRead(void);
void RTC_SetTr(uint32_t value);
void RTC_SetDr(uint32_t value);
uint16_t rtc_get_ss(void);
char rtc_bcd2dec(char num);
char rtc_dec2bcd(char num);
void rtc_lenable(unsigned int lclock);
static void set_rtc_clock_source(uint8_t clock_source);
void rtc_lselect(uint8_t lclock);

/*** Procedure & Function Definition ***/
void RTC_Clock(uint8_t isEnabled) {
    RTC_WriteEnable();

    if (isEnabled) {
        RCC->BDCR |= (1 << RCC_BDCR_RTCEN_Pos);  // Enable RTC clock
    } else {
        RCC->BDCR &= ~(1 << RCC_BDCR_RTCEN_Pos); // Disable RTC clock
    }

    RTC_WriteDisable();
}

void RTC_Interrupt(uint8_t config) {
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

void RTC_Inic(uint8_t clock)
{ // RM0390 pg657
	RTC_PwrClock(ON);
	RTC_BckSramClock(ON);
	RTC_Clock(ON);

	rtc_lenable(clock);
	rtc_lselect(clock);

	RTC_StopRead();

	//RTC_WriteEnable();
	//RTC_RegUnlock();
	//RTC_RegWrite(&RTC->TR, 0x130000);
	//RTC_RegWrite(&RTC->DR, 0x215124);
	//RTC->CR &= (uint32_t) ~(1 << RTC_CR_BYPSHAD_Pos); // BYPSHAD: Disable Bypass the shadow registers
	//RTC_WriteDisable();
}

void RTC_BckWrite(uint8_t registerIndex, uint8_t data) {
    // Validate register index
    if (registerIndex >= MAX_BACKUP_REGISTERS) {
        // Handle error (e.g., return, assert, or log)
        return;
    }

    RTC_PwrClock(ON);
    RTC_BckSramClock(ON);
    RTC_WriteEnable();

    // Write data to the specified backup register
    set_bit_block(&RTC->BKP0R, BYTE_BITS, (registerIndex * BYTE_BITS), data);

    RTC_WriteDisable();
}

uint8_t RTC_BckRead(uint8_t registerIndex) {
    uint8_t value = 0;

    // Validate the register index
    if (registerIndex < MAX_BACKUP_REGISTERS) {
        value = get_bit_block(&RTC->BKP0R, BYTE_BITS, (registerIndex * BYTE_BITS));
    }

    return value;  // Returns 0 if the index is out of bounds
}

void RTC_Hour(uint8_t hour) {
    // Validate the hour range (0-23)
    if (hour > MAX_HOUR) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    uint32_t Time = 0;
    uint8_t t, u;

    // Enable power clock for RTC
    RTC_PwrClock(ON);

    // Convert hour to BCD format
    t = rtc_dec2bcd(hour / 10);
    u = rtc_dec2bcd(hour % 10);

    // Wait for RTC to be ready for reading
    RTC_WaitRead();

    // Read current Time register
    Time = RTC->TR;

    // Clear current hour bits (ht and hu)
    Time &= ~(RTC_TSTR_HT | RTC_TSTR_HU);

    // Set new hour bits (hu and ht)
    Time |= (uint32_t)((u << RTC_TSTR_HU_Pos) | (t << RTC_TSTR_HT_Pos));

    // Write back to the Time register
    RTC_SetTr(Time);

    // Disable power clock for RTC
    RTC_PwrClock(OFF);
}

void RTC_Minute(uint8_t minute) {
    // Validate the minute range (0-59)
    if (minute > MAX_MINUTE) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    uint32_t Time;
    uint8_t t, u;

    // Enable power clock for RTC
    RTC_PwrClock(ON);

    // Convert minute to BCD format
    t = rtc_dec2bcd(minute / 10);
    u = rtc_dec2bcd(minute % 10);

    // Wait for RTC to be ready for reading
    RTC_WaitRead();

    // Read current Time register
    Time = RTC->TR;

    // Clear current minute bits (mnt and mnu)
    Time &= ~(RTC_TSTR_MNT | RTC_TSTR_MNU);

    // Set new minute bits (mnu and mnt)
    Time |= (uint32_t)((u << RTC_TSTR_MNU_Pos) | (t << RTC_TSTR_MNT_Pos));

    // Write back to the Time register
    RTC_SetTr(Time);

    // Disable power clock for RTC
    RTC_PwrClock(OFF);
}

void RTC_Second(uint8_t second) {
    // Validate the second range (0-59)
    if (second > MAX_SECOND) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    uint32_t Time;
    uint8_t t, u;

    // Enable power clock for RTC
    RTC_PwrClock(ON);

    // Convert second to BCD format
    t = rtc_dec2bcd(second / 10);
    u = rtc_dec2bcd(second % 10);

    // Wait for RTC to be ready for reading
    RTC_WaitRead();

    // Read current Time register
    Time = RTC->TR;

    // Clear current second bits (st and su)
    Time &= ~(RTC_TSTR_ST | RTC_TSTR_SU);

    // Set new second bits (su and st)
    Time |= (uint32_t)((u << RTC_TSTR_SU_Pos) | (t << RTC_TSTR_ST_Pos));

    // Write back to the Time register
    RTC_SetTr(Time);

    // Disable power clock for RTC
    RTC_PwrClock(OFF);
}

void RTC_Year(uint8_t year) {
    // Validate the year range (0-99)
    if (year > MAX_YEAR) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    uint32_t Date;
    uint8_t t, u;

    // Enable power clock for RTC
    RTC_PwrClock(ON);

    // Convert year to BCD format
    t = rtc_dec2bcd(year / 10);
    u = rtc_dec2bcd(year % 10);

    // Wait for RTC to be ready for reading
    RTC_WaitRead();

    // Read current Date register
    Date = RTC->DR;

    // Clear current year bits (YT and YU)
    Date &= ~(RTC_DR_YT | RTC_DR_YU);

    // Set new year bits (YU and YT)
    Date |= (uint32_t)((u << RTC_DR_YU_Pos) | (t << RTC_DR_YT_Pos));

    // Write back to the Date register
    RTC_SetDr(Date);

    // Disable power clock for RTC
    RTC_PwrClock(OFF);
}

void RTC_Month(uint8_t month) {
    // Validate the month range (1-12)
    if (month < MIN_MONTH || month > MAX_MONTH) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    uint32_t Date;
    uint8_t t, u;

    // Enable power clock for RTC
    RTC_PwrClock(ON);

    // Convert month to BCD format
    t = rtc_dec2bcd(month / 10);
    u = rtc_dec2bcd(month % 10);

    // Wait for RTC to be ready for reading
    RTC_WaitRead();

    // Read current Date register
    Date = RTC->DR;

    // Clear current month bits (MT and MU)
    Date &= ~(RTC_TSDR_MT | RTC_TSDR_MU);

    // Set new month bits (MU and MT)
    Date |= (uint32_t)((u << RTC_TSDR_MU_Pos) | (t << RTC_TSDR_MT_Pos));

    // Write back to the Date register
    RTC_SetDr(Date);

    // Disable power clock for RTC
    RTC_PwrClock(OFF);
}

void RTC_WeekDay(uint8_t weekday) {
    // Validate the weekday range (1-7)
    if (weekday < MIN_WEEKDAY || weekday > MAX_WEEKDAY) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    uint32_t Date;
    uint8_t u;

    // Enable power clock for RTC
    RTC_PwrClock(ON);

    // Convert weekday to BCD format
    u = rtc_dec2bcd(weekday % 10); // Assuming weekday is represented as 1-7

    // Wait for RTC to be ready for reading
    RTC_WaitRead();

    // Read current Date register
    Date = RTC->DR;

    // Clear current weekday bits (WDU)
    Date &= ~RTC_TSDR_WDU;

    // Set new weekday bits (WDU)
    Date |= (uint32_t)(u << RTC_TSDR_WDU_Pos);

    // Write back to the Date register
    RTC_SetDr(Date);

    // Disable power clock for RTC
    RTC_PwrClock(OFF);
}

void RTC_Day(uint8_t day) {
    // Validate the day range (1-31)
    if (day < MIN_DAY || day > MAX_DAY) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    uint32_t Date;
    uint8_t t, u;

    // Enable power clock for RTC
    RTC_PwrClock(ON);

    // Convert day to BCD format
    t = rtc_dec2bcd(day / 10);
    u = rtc_dec2bcd(day % 10);

    // Wait for RTC to be ready for reading
    RTC_WaitRead();

    // Read current Date register
    Date = RTC->DR;

    // Clear current day bits (DT and DU)
    Date &= ~(RTC_TSDR_DT | RTC_TSDR_DU);

    // Set new day bits (DU and DT)
    Date |= (uint32_t)((u << RTC_TSDR_DU_Pos) | (t << RTC_TSDR_DT_Pos));

    // Write back to the Date register
    RTC_SetDr(Date);

    // Disable power clock for RTC
    RTC_PwrClock(OFF);
}

void RTC_dr2vec(char* rtc_vect)
{
	if(RTC->ISR & (1 << RTC_ISR_RSF_Pos)){ // RSF: Registers synchronisation flag
		uint32_t dr = RTC->DR;
		// YT
		rtc_vect[0] = (uint8_t) (dr >> RTC_DR_YT_Pos) & 0x0F;
		rtc_vect[0] = rtc_bcd2dec(rtc_vect[0]);
		// YU
		rtc_vect[1] = (uint8_t) (dr >> RTC_DR_YU_Pos) & 0x0F;
		rtc_vect[1] = rtc_bcd2dec(rtc_vect[1]);
		// WDU
		rtc_vect[2] = (uint8_t) (dr >> RTC_DR_WDU_Pos) & 0x07;
		rtc_vect[2] = rtc_bcd2dec(rtc_vect[2]);
		// MT
		rtc_vect[3] = (uint8_t) (dr >> RTC_DR_MT_Pos) & 0x01;
		rtc_vect[3] = rtc_bcd2dec(rtc_vect[3]);
		// MU
		rtc_vect[4] = (uint8_t) (dr >> RTC_DR_MU_Pos) & 0x0F;
		rtc_vect[4] = rtc_bcd2dec(rtc_vect[4]);
		// DT
		rtc_vect[5] = (uint8_t) (dr >> RTC_DR_DT_Pos) & 0x03;
		rtc_vect[5] = rtc_bcd2dec(rtc_vect[5]);
		// DU
		rtc_vect[6] = (uint8_t) dr & RTC_DR_DU;
		rtc_vect[6] = rtc_bcd2dec(rtc_vect[6]);
		// Store Value
		// Clear Registers synchronisation flag
		RTC->ISR &= (uint32_t) ~(1 << RTC_ISR_RSF_Pos);
	}
}

void RTC_tr2vec(char* rtc_vect)
{
	if(RTC->ISR & (1 << RTC_ISR_RSF_Pos)){ // RSF: Registers synchronisation flag
		uint32_t tr = RTC->TR;
		// ht
		rtc_vect[0] = (uint8_t) (tr >> RTC_TR_HT_Pos) & 0x03;
		rtc_vect[0] = rtc_bcd2dec(rtc_vect[0]);
		// hu
		rtc_vect[1] = (uint8_t) (tr >> RTC_TR_HU_Pos) & 0x0F;
		rtc_vect[1] = rtc_bcd2dec(rtc_vect[1]);
		// mnt
		rtc_vect[2] = (uint8_t) (tr >> RTC_TR_MNT_Pos) & 0x07;
		rtc_vect[2] = rtc_bcd2dec(rtc_vect[2]);
		// mnu
		rtc_vect[3] = (uint8_t) (tr >> RTC_TR_MNU_Pos) & 0x0F;
		rtc_vect[3] = rtc_bcd2dec(rtc_vect[3]);
		// st
		rtc_vect[4] = (uint8_t) (tr >> RTC_TR_ST_Pos) & 0x07;
		rtc_vect[4] = rtc_bcd2dec(rtc_vect[4]);
		// su
		rtc_vect[5] = (uint8_t) tr & RTC_TR_SU;
		rtc_vect[5] = rtc_bcd2dec(rtc_vect[5]);
		// Store value
		// Clear Registers synchronisation flag
		RTC->ISR &= (uint32_t) ~(1 << RTC_ISR_RSF_Pos);
	}
}

uint8_t RTC__get_Year(void){
	RTC_WaitRead();
	uint32_t dr = RTC->DR;
	return rtc_bcd2dec((dr >> 16) & 0x00FF);
}
uint8_t RTC__get_Month(void){
	RTC_WaitRead();
	uint32_t dr = RTC->DR;
	return rtc_bcd2dec((dr >> 8) & 0x001F);
}
uint8_t RTC__get_WeekDay(void){
	RTC_WaitRead();
	uint32_t dr = RTC->DR;
	//return rtc_bcd2dec(get_reg_block(dr,3,13));
	return rtc_bcd2dec((dr >> 13) & 0x0007);
}
uint8_t RTC__get_Day(void){
	RTC_WaitRead();
	uint32_t dr = RTC->DR;
	return rtc_bcd2dec(dr & 0x003F);
}
uint16_t rtc_get_ss(void)
{
	RTC_WaitRead();
	return RTC->SSR;
}

uint8_t RTC__get_Hour(void){
	RTC_WaitRead();
	uint32_t tr = RTC->TR;
	return rtc_bcd2dec((tr >> 16) & 0x003F);
}
uint8_t RTC__get_Minute(void){
	RTC_WaitRead();
	uint32_t tr = RTC->TR;
	return rtc_bcd2dec((tr >> 8) & 0x007F);
}
uint8_t RTC__get_Second(void){
	RTC_WaitRead();
	uint32_t tr = RTC->TR;
	return rtc_bcd2dec(tr & 0x007F);
}

/*** AUX Procedure & Function Definition ***/
void RTC_PwrClock(uint8_t state)
{
	set_reg_block(&RCC->APB1ENR, 1, RCC_APB1ENR_PWREN_Pos, state); // Power interface clock enable
}
void RTC_BckSramClock(uint8_t state)
{
	#ifdef STM32F446xx
		set_reg_block(&RCC->AHB1ENR, 1, RCC_AHB1ENR_BKPSRAMEN_Pos, state); // Backup SRAM interface clock enable
	#endif
	set_reg_block(&RCC->AHB1LPENR, 1, RCC_AHB1LPENR_SRAM1LPEN_Pos, state); // Backup SRAM interface clock enable
}
void RTC_WriteEnable(void)
{
	PWR->CR |= (1 << PWR_CR_DBP_Pos); // Disable protection
}
void RTC_WriteDisable(void)
{
	PWR->CR &= (uint32_t) ~(1 << PWR_CR_DBP_Pos); // Enable protection
}
void RTC_RegUnlock(void)
{
	RTC->WPR |= RTC_KEY1;
	RTC->WPR |= RTC_KEY2;
}
void RTC_RegWrite(volatile uint32_t* rtc_reg, uint32_t value) {
    // Check if the register pointer is valid
    if (rtc_reg == NULL) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    // Set the INIT bit to enter initialization mode
    RTC->ISR |= (1 << RTC_ISR_INIT_Pos); // INIT

    // Wait for the INITF flag to be set, indicating that the RTC is ready
    uint32_t rtc_time_out = RTC_INIT_TIMEOUT;
    while (!(RTC->ISR & (1 << RTC_ISR_INITF_Pos)) && rtc_time_out) {
        rtc_time_out--;
    }

    // Check for timeout
    if (!rtc_time_out) {
        // Optionally handle timeout error (e.g., return, assert, or log)
        RTC->ISR &= ~(1 << RTC_ISR_INIT_Pos); // Clear INIT bit
        return;
    }

    // Write the value to the specified RTC register
    *rtc_reg = value;

    // Clear the INIT bit to exit initialization mode
    RTC->ISR &= ~(1 << RTC_ISR_INIT_Pos);
}
void RTC_StopRead(void)
{
	RTC->ISR &= ~(1 << RTC_ISR_RSF_Pos);
}
void RTC_WaitRead(void)
{ // Wait Data Ready
	for(rtc_time_out = 300; !(RTC->ISR & (1 << RTC_ISR_RSF_Pos)) && rtc_time_out; rtc_time_out--);
}
//RTC
void RTC_SetTr(uint32_t value)
{
	RTC_WriteEnable();
	RTC_RegUnlock();
	RTC_RegWrite(&RTC->TR, value);
	RTC_WriteDisable();
}
void RTC_SetDr(uint32_t value)
{
	RTC_WriteEnable();
	RTC_RegUnlock();
	RTC_RegWrite(&RTC->DR, value);
	RTC_WriteDisable();
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
                RTC_WriteEnable();
                RCC->CSR |= RCC_CSR_LSION;
                RTC_WriteDisable();
                set = 0;
            } else if (RCC->CSR & RCC_CSR_LSIRDY) {
                rdy = 0; // Oscillator is ready
            }
        } else if (lclock == 1) { // Enable External Low-Speed Oscillator
            if (set) {
                RTC_WriteEnable();
                RCC->BDCR |= RCC_BDCR_LSEON;
                RTC_WriteDisable();
                set = 0;
            } else if (RCC->BDCR & RCC_BDCR_LSERDY) {
                rdy = 0; // Oscillator is ready
            }
        } else if (lclock == 2) { // Bypass External Low-Speed Oscillator
            if (set) {
                RTC_WriteEnable();
                RCC->BDCR |= RCC_BDCR_LSEBYP;
                RTC_WriteDisable();
            }
            lclock = 1; // Fall back to LSEON
        } else {
            lclock = 0; // Default to LSION
        }
    }
}
static void set_rtc_clock_source(uint8_t clock_source) {
    RTC_WriteEnable();
    set_reg_Msk(&RCC->BDCR, RCC_BDCR_RTCSEL_Msk, clock_source);
    RTC_WriteDisable();
}
void rtc_lselect(uint8_t lclock) {
    // Input validation
    if (lclock > 3) {
        // Invalid selection, default to LSI
        lclock = 0;
    }

    // Clear previous RTC selection
    RTC_WriteEnable();
    set_reg_Msk(&RCC->BDCR, RCC_BDCR_RTCSEL_Msk, 0);
    RTC_WriteDisable();

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

/*** RTC Procedure & Function Definition ***/
void rtc_enable(void)
{
	stm32fxxx_rtc.instance = RTC;
	/***/
	stm32fxxx_rtc.get_Year = RTC__get_Year;
	stm32fxxx_rtc.get_Month = RTC__get_Month;
	stm32fxxx_rtc.get_WeekDay = RTC__get_WeekDay;
	stm32fxxx_rtc.get_Day = RTC__get_Day;
	stm32fxxx_rtc.get_Hour = RTC__get_Hour;
	stm32fxxx_rtc.get_Minute = RTC__get_Minute;
	stm32fxxx_rtc.get_Second = RTC__get_Second;
	stm32fxxx_rtc.Day = RTC_Day;
	stm32fxxx_rtc.Month = RTC_Month;
	stm32fxxx_rtc.WeekDay = RTC_WeekDay;
	stm32fxxx_rtc.Year = RTC_Year;
	stm32fxxx_rtc.Hour = RTC_Hour;
	stm32fxxx_rtc.Minute = RTC_Minute;
	stm32fxxx_rtc.Second = RTC_Second;
	stm32fxxx_rtc.dr2vec = RTC_dr2vec;
	stm32fxxx_rtc.tr2vec = RTC_tr2vec;
	stm32fxxx_rtc.BckWrite = RTC_BckWrite;
	stm32fxxx_rtc.BckRead = RTC_BckRead;
	stm32fxxx_rtc.get_ss = rtc_get_ss;
	/*** Clock and Nvic ***/
	stm32fxxx_rtc.pwr_clock = RTC_PwrClock;
	stm32fxxx_rtc.bck_sram_clock = RTC_BckSramClock;
	stm32fxxx_rtc.clock = RTC_Clock;
	stm32fxxx_rtc.nvic = RTC_Interrupt;
	stm32fxxx_rtc.inic = RTC_Inic;

	//return &stm32fxxx_rtc;
}

STM32FXXX_RTC* rtc(void){ return (STM32FXXX_RTC*) &stm32fxxx_rtc; }

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

