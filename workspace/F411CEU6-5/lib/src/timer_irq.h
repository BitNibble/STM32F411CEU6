/******************************************************************************
	STM32 XXX TIM IRQ
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     08102024
Comment:
	
*******************************************************************************/
#ifndef TIMER_IRQ_H
	#define TIMER_IRQ_H

/*** Timer Callback Functions (weak definitions) ***/
void tim1_b_callback(void) __attribute__((weak));
void tim1_u_callback(void) __attribute__((weak));
void tim1_t_callback(void) __attribute__((weak));
void tim1_cc1_callback(void) __attribute__((weak));
void tim1_cc2_callback(void) __attribute__((weak));
void tim1_cc3_callback(void) __attribute__((weak));
void tim1_cc4_callback(void) __attribute__((weak));

void tim2_b_callback(void) __attribute__((weak));
void tim2_u_callback(void) __attribute__((weak));
void tim2_t_callback(void) __attribute__((weak));
void tim2_cc1_callback(void) __attribute__((weak));
void tim2_cc2_callback(void) __attribute__((weak));
void tim2_cc3_callback(void) __attribute__((weak));
void tim2_cc4_callback(void) __attribute__((weak));

void tim3_b_callback(void) __attribute__((weak));
void tim3_u_callback(void) __attribute__((weak));
void tim3_t_callback(void) __attribute__((weak));
void tim3_cc1_callback(void) __attribute__((weak));
void tim3_cc2_callback(void) __attribute__((weak));
void tim3_cc3_callback(void) __attribute__((weak));
void tim3_cc4_callback(void) __attribute__((weak));

void tim4_b_callback(void) __attribute__((weak));
void tim4_u_callback(void) __attribute__((weak));
void tim4_t_callback(void) __attribute__((weak));
void tim4_cc1_callback(void) __attribute__((weak));
void tim4_cc2_callback(void) __attribute__((weak));
void tim4_cc3_callback(void) __attribute__((weak));
void tim4_cc4_callback(void) __attribute__((weak));

void tim5_b_callback(void) __attribute__((weak));
void tim5_u_callback(void) __attribute__((weak));
void tim5_t_callback(void) __attribute__((weak));
void tim5_cc1_callback(void) __attribute__((weak));
void tim5_cc2_callback(void) __attribute__((weak));
void tim5_cc3_callback(void) __attribute__((weak));
void tim5_cc4_callback(void) __attribute__((weak));

void tim6_u_callback(void) __attribute__((weak));
void tim7_u_callback(void) __attribute__((weak));

void tim8_b_callback(void) __attribute__((weak));
void tim8_u_callback(void) __attribute__((weak));
void tim8_t_callback(void) __attribute__((weak));
void tim8_cc1_callback(void) __attribute__((weak));
void tim8_cc2_callback(void) __attribute__((weak));
void tim8_cc3_callback(void) __attribute__((weak));
void tim8_cc4_callback(void) __attribute__((weak));

void tim9_u_callback(void) __attribute__((weak));
void tim9_t_callback(void) __attribute__((weak));

void tim10_u_callback(void) __attribute__((weak));

void tim11_u_callback(void) __attribute__((weak));
void tim11_t_callback(void) __attribute__((weak));

void tim12_u_callback(void) __attribute__((weak));
void tim12_t_callback(void) __attribute__((weak));
void tim12_cc1_callback(void) __attribute__((weak));
void tim12_cc2_callback(void) __attribute__((weak));

void tim13_u_callback(void) __attribute__((weak));
void tim13_t_callback(void) __attribute__((weak));

void tim14_u_callback(void) __attribute__((weak));
void tim14_t_callback(void) __attribute__((weak));

#endif // TIMER_IRQ_H

/*** EOF ***/

