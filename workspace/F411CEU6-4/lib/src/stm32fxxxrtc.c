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
#include "stm32fxxxnvic.h"

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

/*** File Procedure & Function Header ***/
/***/
void RTC_PWR_clock(uint8_t state);
void RTC_BkpSram_clock(uint8_t state);
void RTC_Write_enable(void);
void RTC_Write_disable(void);
void RTC_Reg_unlock(void);
void RTC_Reg_write(volatile uint32_t* rtc_reg, uint32_t value);
void RTC_Stop_read(void);
void RTC_Wait_read(void);
void RTC_Set_tr(uint32_t value);
void RTC_Set_dr(uint32_t value);
uint16_t RTC_Get_ss(void);
char _rtc_bcd2dec(char num);
char _rtc_dec2bcd(char num);
void RTC_L_enable(unsigned int lclock);
static void set_rtc_clock_source(uint8_t clock_source);
void RTC_L_select(uint8_t lclock);

/*** Procedure & Function Definition ***/
void RTC_Clock(uint8_t isEnabled) {
    RTC_Write_enable();

    if (isEnabled) {
        RCC->BDCR |= (1 << RCC_BDCR_RTCEN_Pos);  // Enable RTC clock
    } else {
        RCC->BDCR &= ~(1 << RCC_BDCR_RTCEN_Pos); // Disable RTC clock
    }

    RTC_Write_disable();
}

void RTC_NVIC(RTC_NVIC_config type) {
    switch(type) {
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

void RTC_IRQ_enable(RTC_IRQ_config type)
{
    RTC_Write_enable();
    RTC_Reg_unlock();

    switch (type) {
        case RTC_IRQ_ALARM:
            RTC->CR |= RTC_CR_ALRAIE;
            break;
        case RTC_IRQ_WAKEUP:
            RTC->CR |= RTC_CR_WUTIE;
            break;
        case RTC_IRQ_TS:
            RTC->CR |= RTC_CR_TSIE;
            break;
        case RTC_IRQ_TAMPER:
            RTC->TAFCR |= RTC_TAFCR_TAMPIE;
            break;
    }

    RTC_Write_disable();
}

void RTC_IRQ_disable(RTC_IRQ_config type)
{
    RTC_Write_enable();
    RTC_Reg_unlock();

    switch (type) {
        case RTC_IRQ_ALARM:
            RTC->CR &= ~RTC_CR_ALRAIE;
            break;
        case RTC_IRQ_WAKEUP:
            RTC->CR &= ~RTC_CR_WUTIE;
            break;
        case RTC_IRQ_TS:
            RTC->CR &= ~RTC_CR_TSIE;
            break;
        case RTC_IRQ_TAMPER:
            RTC->TAFCR &= ~RTC_TAFCR_TAMPIE;
            break;
    }

    RTC_Write_disable();
}

void RTC_Inic(uint8_t clock)
{ // RM0390 pg657
	RTC_PWR_clock(1);
	RTC_BkpSram_clock(1);
	RTC_Clock(1);

	RTC_L_enable(clock);
	RTC_L_select(clock);

	RTC_Stop_read();
}

void RTC_Default(void)
{ // RM0390 pg657
	RTC_PWR_clock(1);
	RTC_BkpSram_clock(1);
	RTC_Clock(1);

	RTC_L_enable(1);
	RTC_L_select(1);

	RTC_Stop_read();
}

void RTC_Bkp_write(uint8_t registerIndex, uint8_t data) {
    // Validate register index
    if (registerIndex >= MAX_BACKUP_REGISTERS) {
        // Handle error (e.g., return, assert, or log)
        return;
    }

    RTC_PWR_clock(1);
    RTC_BkpSram_clock(1);
    RTC_Write_enable();

    // Write data to the specified backup register
    set_bit_block(&RTC->BKP0R, BYTE_BITS, (registerIndex * BYTE_BITS), data);

    RTC_Write_disable();
}

uint8_t RTC_Bkp_read(uint8_t registerIndex) {
    uint8_t value = 0;

    // Validate the register index
    if (registerIndex < MAX_BACKUP_REGISTERS) {
        value = get_bit_block(&RTC->BKP0R, BYTE_BITS, (registerIndex * BYTE_BITS));
    }

    return value;  // Returns 0 if the index is out of bounds
}

void RTC_Set_hour(uint8_t hour) {
    // Validate the hour range (0-23)
    if (hour > MAX_HOUR) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    uint32_t Time = 0;
    uint8_t t, u;

    // Enable power clock for RTC
    RTC_PWR_clock(1);

    // Convert hour to BCD format
    t = _rtc_dec2bcd(hour / 10);
    u = _rtc_dec2bcd(hour % 10);

    // Wait for RTC to be ready for reading
    RTC_Wait_read();

    // Read current Time register
    Time = RTC->TR;

    // Clear current hour bits (ht and hu)
    Time &= ~(RTC_TSTR_HT | RTC_TSTR_HU);

    // Set new hour bits (hu and ht)
    Time |= (uint32_t)((u << RTC_TSTR_HU_Pos) | (t << RTC_TSTR_HT_Pos));

    // Write back to the Time register
    RTC_Set_tr(Time);

    // Disable power clock for RTC
    RTC_PWR_clock(0);
}

void RTC_Set_minute(uint8_t minute) {
    // Validate the minute range (0-59)
    if (minute > MAX_MINUTE) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    uint32_t Time;
    uint8_t t, u;

    // Enable power clock for RTC
    RTC_PWR_clock(1);

    // Convert minute to BCD format
    t = _rtc_dec2bcd(minute / 10);
    u = _rtc_dec2bcd(minute % 10);

    // Wait for RTC to be ready for reading
    RTC_Wait_read();

    // Read current Time register
    Time = RTC->TR;

    // Clear current minute bits (mnt and mnu)
    Time &= ~(RTC_TSTR_MNT | RTC_TSTR_MNU);

    // Set new minute bits (mnu and mnt)
    Time |= (uint32_t)((u << RTC_TSTR_MNU_Pos) | (t << RTC_TSTR_MNT_Pos));

    // Write back to the Time register
    RTC_Set_tr(Time);

    // Disable power clock for RTC
    RTC_PWR_clock(0);
}

void RTC_Set_second(uint8_t second) {
    // Validate the second range (0-59)
    if (second > MAX_SECOND) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    uint32_t Time;
    uint8_t t, u;

    // Enable power clock for RTC
    RTC_PWR_clock(1);

    // Convert second to BCD format
    t = _rtc_dec2bcd(second / 10);
    u = _rtc_dec2bcd(second % 10);

    // Wait for RTC to be ready for reading
    RTC_Wait_read();

    // Read current Time register
    Time = RTC->TR;

    // Clear current second bits (st and su)
    Time &= ~(RTC_TSTR_ST | RTC_TSTR_SU);

    // Set new second bits (su and st)
    Time |= (uint32_t)((u << RTC_TSTR_SU_Pos) | (t << RTC_TSTR_ST_Pos));

    // Write back to the Time register
    RTC_Set_tr(Time);

    // Disable power clock for RTC
    RTC_PWR_clock(0);
}

void RTC_Set_year(uint8_t year) {
    // Validate the year range (0-99)
    if (year > MAX_YEAR) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    uint32_t Date;
    uint8_t t, u;

    // Enable power clock for RTC
    RTC_PWR_clock(1);

    // Convert year to BCD format
    t = _rtc_dec2bcd(year / 10);
    u = _rtc_dec2bcd(year % 10);

    // Wait for RTC to be ready for reading
    RTC_Wait_read();

    // Read current Date register
    Date = RTC->DR;

    // Clear current year bits (YT and YU)
    Date &= ~(RTC_DR_YT | RTC_DR_YU);

    // Set new year bits (YU and YT)
    Date |= (uint32_t)((u << RTC_DR_YU_Pos) | (t << RTC_DR_YT_Pos));

    // Write back to the Date register
    RTC_Set_dr(Date);

    // Disable power clock for RTC
    RTC_PWR_clock(0);
}

void RTC_Set_month(uint8_t month) {
    // Validate the month range (1-12)
    if (month < MIN_MONTH || month > MAX_MONTH) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    uint32_t Date;
    uint8_t t, u;

    // Enable power clock for RTC
    RTC_PWR_clock(1);

    // Convert month to BCD format
    t = _rtc_dec2bcd(month / 10);
    u = _rtc_dec2bcd(month % 10);

    // Wait for RTC to be ready for reading
    RTC_Wait_read();

    // Read current Date register
    Date = RTC->DR;

    // Clear current month bits (MT and MU)
    Date &= ~(RTC_TSDR_MT | RTC_TSDR_MU);

    // Set new month bits (MU and MT)
    Date |= (uint32_t)((u << RTC_TSDR_MU_Pos) | (t << RTC_TSDR_MT_Pos));

    // Write back to the Date register
    RTC_Set_dr(Date);

    // Disable power clock for RTC
    RTC_PWR_clock(0);
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
    RTC_PWR_clock(1);

    // Convert weekday to BCD format
    u = _rtc_dec2bcd(weekday % 10); // Assuming weekday is represented as 1-7

    // Wait for RTC to be ready for reading
    RTC_Wait_read();

    // Read current Date register
    Date = RTC->DR;

    // Clear current weekday bits (WDU)
    Date &= ~RTC_TSDR_WDU;

    // Set new weekday bits (WDU)
    Date |= (uint32_t)(u << RTC_TSDR_WDU_Pos);

    // Write back to the Date register
    RTC_Set_dr(Date);

    // Disable power clock for RTC
    RTC_PWR_clock(0);
}

void RTC_Set_day(uint8_t day) {
    // Validate the day range (1-31)
    if (day < MIN_DAY || day > MAX_DAY) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    uint32_t Date;
    uint8_t t, u;

    // Enable power clock for RTC
    RTC_PWR_clock(1);

    // Convert day to BCD format
    t = _rtc_dec2bcd(day / 10);
    u = _rtc_dec2bcd(day % 10);

    // Wait for RTC to be ready for reading
    RTC_Wait_read();

    // Read current Date register
    Date = RTC->DR;

    // Clear current day bits (DT and DU)
    Date &= ~(RTC_TSDR_DT | RTC_TSDR_DU);

    // Set new day bits (DU and DT)
    Date |= (uint32_t)((u << RTC_TSDR_DU_Pos) | (t << RTC_TSDR_DT_Pos));

    // Write back to the Date register
    RTC_Set_dr(Date);

    // Disable power clock for RTC
    RTC_PWR_clock(0);
}

void RTC_dr2vec(char* rtc_vect)
{
	if(RTC->ISR & (1 << RTC_ISR_RSF_Pos)){ // RSF: Registers synchronisation flag
		uint32_t dr = RTC->DR;
		// YT
		rtc_vect[0] = (uint8_t) (dr >> RTC_DR_YT_Pos) & 0x0F;
		rtc_vect[0] = _rtc_bcd2dec(rtc_vect[0]);
		// YU
		rtc_vect[1] = (uint8_t) (dr >> RTC_DR_YU_Pos) & 0x0F;
		rtc_vect[1] = _rtc_bcd2dec(rtc_vect[1]);
		// WDU
		rtc_vect[2] = (uint8_t) (dr >> RTC_DR_WDU_Pos) & 0x07;
		rtc_vect[2] = _rtc_bcd2dec(rtc_vect[2]);
		// MT
		rtc_vect[3] = (uint8_t) (dr >> RTC_DR_MT_Pos) & 0x01;
		rtc_vect[3] = _rtc_bcd2dec(rtc_vect[3]);
		// MU
		rtc_vect[4] = (uint8_t) (dr >> RTC_DR_MU_Pos) & 0x0F;
		rtc_vect[4] = _rtc_bcd2dec(rtc_vect[4]);
		// DT
		rtc_vect[5] = (uint8_t) (dr >> RTC_DR_DT_Pos) & 0x03;
		rtc_vect[5] = _rtc_bcd2dec(rtc_vect[5]);
		// DU
		rtc_vect[6] = (uint8_t) dr & RTC_DR_DU;
		rtc_vect[6] = _rtc_bcd2dec(rtc_vect[6]);
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
		rtc_vect[0] = _rtc_bcd2dec(rtc_vect[0]);
		// hu
		rtc_vect[1] = (uint8_t) (tr >> RTC_TR_HU_Pos) & 0x0F;
		rtc_vect[1] = _rtc_bcd2dec(rtc_vect[1]);
		// mnt
		rtc_vect[2] = (uint8_t) (tr >> RTC_TR_MNT_Pos) & 0x07;
		rtc_vect[2] = _rtc_bcd2dec(rtc_vect[2]);
		// mnu
		rtc_vect[3] = (uint8_t) (tr >> RTC_TR_MNU_Pos) & 0x0F;
		rtc_vect[3] = _rtc_bcd2dec(rtc_vect[3]);
		// st
		rtc_vect[4] = (uint8_t) (tr >> RTC_TR_ST_Pos) & 0x07;
		rtc_vect[4] = _rtc_bcd2dec(rtc_vect[4]);
		// su
		rtc_vect[5] = (uint8_t) tr & RTC_TR_SU;
		rtc_vect[5] = _rtc_bcd2dec(rtc_vect[5]);
		// Store value
		// Clear Registers synchronisation flag
		RTC->ISR &= (uint32_t) ~(1 << RTC_ISR_RSF_Pos);
	}
}

uint8_t RTC_Get_year(void){
	RTC_Wait_read();
	uint32_t dr = RTC->DR;
	return _rtc_bcd2dec((dr >> 16) & 0x00FF);
}
uint8_t RTC_Get_month(void){
	RTC_Wait_read();
	uint32_t dr = RTC->DR;
	return _rtc_bcd2dec((dr >> 8) & 0x001F);
}
uint8_t RTC_Get_weekday(void){
	RTC_Wait_read();
	uint32_t dr = RTC->DR;
	//return _rtc_bcd2dec(get_reg_block(dr,3,13));
	return _rtc_bcd2dec((dr >> 13) & 0x0007);
}
uint8_t RTC_Get_day(void){
	RTC_Wait_read();
	uint32_t dr = RTC->DR;
	return _rtc_bcd2dec(dr & 0x003F);
}
uint16_t RTC_Get_ss(void)
{
	RTC_Wait_read();
	return RTC->SSR;
}

uint8_t RTC_Get_hour(void){
	RTC_Wait_read();
	uint32_t tr = RTC->TR;
	return _rtc_bcd2dec((tr >> 16) & 0x003F);
}
uint8_t RTC_Get_minute(void){
	RTC_Wait_read();
	uint32_t tr = RTC->TR;
	return _rtc_bcd2dec((tr >> 8) & 0x007F);
}
uint8_t RTC_Get_second(void){
	RTC_Wait_read();
	uint32_t tr = RTC->TR;
	return _rtc_bcd2dec(tr & 0x007F);
}

/*** AUX Procedure & Function Definition ***/
void RTC_PWR_clock(uint8_t state)
{
	set_reg_block(&RCC->APB1ENR, 1, RCC_APB1ENR_PWREN_Pos, state); // Power interface clock enable
}
void RTC_BkpSram_clock(uint8_t state)
{
	#ifdef STM32F446xx
		set_reg_block(&RCC->AHB1ENR, 1, RCC_AHB1ENR_BKPSRAMEN_Pos, state); // Backup SRAM interface clock enable
	#endif
	set_reg_block(&RCC->AHB1LPENR, 1, RCC_AHB1LPENR_SRAM1LPEN_Pos, state); // Backup SRAM interface clock enable
}
void RTC_Write_enable(void)
{
	PWR->CR |= (1 << PWR_CR_DBP_Pos); // Disable protection
}
void RTC_Write_disable(void)
{
	PWR->CR &= (uint32_t) ~(1 << PWR_CR_DBP_Pos); // Enable protection
}
void RTC_Reg_unlock(void)
{
	RTC->WPR |= RTC_KEY1;
	RTC->WPR |= RTC_KEY2;
}
void RTC_Reg_write(volatile uint32_t* rtc_reg, uint32_t value) {
    // Check if the register pointer is valid
    if (rtc_reg == NULL) {
        // Optionally handle error (e.g., return, assert, or log)
        return;
    }

    // Set the INIT bit to enter initialization mode
    RTC->ISR |= (1 << RTC_ISR_INIT_Pos); // INIT

    // Wait for the INITF flag to be set, indicating that the RTC is ready
    volatile uint32_t rtc_time_out = RTC_INIT_TIMEOUT;
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
void RTC_Stop_read(void)
{
	RTC->ISR &= ~(1 << RTC_ISR_RSF_Pos);
}
void RTC_Wait_read(void)
{ // Wait Data Ready
	volatile uint32_t rtc_time_out;
	for(rtc_time_out = 300; !(RTC->ISR & (1 << RTC_ISR_RSF_Pos)) && rtc_time_out; rtc_time_out--);
}
//RTC
void RTC_Set_tr(uint32_t value)
{
	RTC_Write_enable();
	RTC_Reg_unlock();
	RTC_Reg_write(&RTC->TR, value);
	RTC_Write_disable();
}
void RTC_Set_dr(uint32_t value)
{
	RTC_Write_enable();
	RTC_Reg_unlock();
	RTC_Reg_write(&RTC->DR, value);
	RTC_Write_disable();
}
/*** COMMON ***/
char _rtc_bcd2dec(char num)
{
	return ((num / 16 * 10) + (num % 16));
}
char _rtc_dec2bcd(char num)
{
	return ((num / 10 * 16) + (num % 10));
}
void RTC_L_enable(unsigned int lclock) {
    if (lclock > 2) {
        // Invalid clock selection; you might want to handle this error
        return;
    }

    unsigned int set = 1;
    unsigned int rdy = 1;

    while (rdy) {
        if (lclock == 0) { // Enable Internal Low-Speed Oscillator
            if (set) {
                RTC_Write_enable();
                RCC->CSR |= RCC_CSR_LSION;
                RTC_Write_disable();
                set = 0;
            } else if (RCC->CSR & RCC_CSR_LSIRDY) {
                rdy = 0; // Oscillator is ready
            }
        } else if (lclock == 1) { // Enable External Low-Speed Oscillator
            if (set) {
                RTC_Write_enable();
                RCC->BDCR |= RCC_BDCR_LSEON;
                RTC_Write_disable();
                set = 0;
            } else if (RCC->BDCR & RCC_BDCR_LSERDY) {
                rdy = 0; // Oscillator is ready
            }
        } else if (lclock == 2) { // Bypass External Low-Speed Oscillator
            if (set) {
                RTC_Write_enable();
                RCC->BDCR |= RCC_BDCR_LSEBYP;
                RTC_Write_disable();
            }
            lclock = 1; // Fall back to LSEON
        } else {
            lclock = 0; // Default to LSION
        }
    }
}
static void set_rtc_clock_source(uint8_t clock_source) {
    RTC_Write_enable();
    set_reg_Msk(&RCC->BDCR, RCC_BDCR_RTCSEL_Msk, clock_source);
    RTC_Write_disable();
}
void RTC_L_select(uint8_t lclock) {
    // Input validation
    if (lclock > 3) {
        // Invalid selection, default to LSI
        lclock = 0;
    }

    // Clear previous RTC selection
    RTC_Write_enable();
    set_reg_Msk(&RCC->BDCR, RCC_BDCR_RTCSEL_Msk, 0);
    RTC_Write_disable();

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
static RTC_callback RTC_callback_setup = {0};

static STM32FXXX_RTC_Handler stm32fxxx_rtc_setup = {
	/***/
	.get_year = RTC_Get_year,
	.get_month = RTC_Get_month,
	.get_weekday = RTC_Get_weekday,
	.get_day = RTC_Get_day,
	.get_hour = RTC_Get_hour,
	.get_minute = RTC_Get_minute,
	.get_second = RTC_Get_second,
	.set_day = RTC_Set_day,
	.set_month = RTC_Set_month,
	.set_weekday = RTC_WeekDay,
	.set_year = RTC_Set_year,
	.set_hour = RTC_Set_hour,
	.set_minute = RTC_Set_minute,
	.set_second = RTC_Set_second,
	.dr2vec = RTC_dr2vec,
	.tr2vec = RTC_tr2vec,
	.bkp_write = RTC_Bkp_write,
	.bkp_read = RTC_Bkp_read,
	.get_ss = RTC_Get_ss,
	/*** Clock and Nvic ***/
	.pwr_clock = RTC_PWR_clock,
	.bkp_sram_clock = RTC_BkpSram_clock,
	.clock = RTC_Clock,
	.inic = RTC_Default,
	.nvic = RTC_NVIC,
	.irq_enable = RTC_IRQ_enable,
	.irq_disable = RTC_IRQ_disable,
	.callback = &RTC_callback_setup
};

STM32FXXX_RTC_Handler* rtc(void){ return (STM32FXXX_RTC_Handler*) &stm32fxxx_rtc_setup; }

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

/*** INTERRUPT ***/
void RTC_IRQHandler(void)
{
	RTC_callback* cb = rtc()->callback;
    // Alarm
    if (RTC->ISR & RTC_ISR_ALRAF) {
        RTC->ISR &= ~RTC_ISR_ALRAF; // Clear flag
        if (cb->Alarm) cb->Alarm();
    }

    // WakeUp
    if (RTC->ISR & RTC_ISR_WUTF) {
        RTC->ISR &= ~RTC_ISR_WUTF;  // Clear flag
        if (cb->WakeUp) cb->WakeUp();
    }

    // Timestamp
    if (RTC->ISR & RTC_ISR_TSF) {
        RTC->ISR &= ~RTC_ISR_TSF;
        if (cb->TimeStamp) cb->TimeStamp();
    }

    // Tamper (depends on TAFCR)
    if (RTC->ISR & RTC_ISR_TAMP1F) {
        RTC->ISR &= ~RTC_ISR_TAMP1F;
        if (cb->Tamper) cb->Tamper();
    }

    // Overrun (if applicable)
    if (RTC->ISR & RTC_ISR_RECALPF) {
        RTC->ISR &= ~RTC_ISR_RECALPF;
        if (cb->Overrun) cb->Overrun();
    }

    // Clear EXTI line 17 flag if used
    EXTI->PR |= (1 << 17);
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

