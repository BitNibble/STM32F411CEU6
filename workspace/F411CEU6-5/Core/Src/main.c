/****************************************************************
Title:
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Software: STM32CubeIDE v1.16.0 Build: 21983_20240628_1741 (UTC)
Hardware: STM32F411CEU6 by DevBox
Date: 28052023
Comment:
	Button K0:
GPIO PA0 - Button
	LED D2:
GPIO PC13 - D2

GPIOA9 and GPIOA10 usart1
****************************************************************/
#include "stm32fxxxrcc.h"
#include "armsystick.h"
#include "stm32fxxxrtc.h"
#include "stm32fxxxusart1.h"
#include "stm32fxxxadc1.h"
#include "st7789.h"
/******/
#include "armfunction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADC_SAMPLE 8
#define TASK_ADC   0
#define TASK_BT    1
#define TASK_LCD   2
#define TASK_MAX   3

uint8_t current_task = 0;

// Snapshot RX buffer
static char rx_snapshot[USART1_RX_BUFFER_SIZE];
char str[32];
char oneshot[5][15];

int main(void)
{
    // --- Initialization ---
    rcc()->inic();
    systick_inic();
    fpu_enable();
    rtc()->inic();
    adc1()->clock(1);
    usart1()->inic();


    adc1()->temperature_setup();
    ST7789 lcd1 = st7789_enable(dev()->spi1, 2, 3, 4, NULL);
    lcd1.start(&lcd1.par);
    lcd1.draw_circle(&lcd1.par,200,80,15,ST77XX_BLACK);
    lcd1.draw_star5(&lcd1.par,200,80,15,5,ST77XX_GOLD);
    lcd1.stop(&lcd1.par);

    // Variables
    char vecD[8], vecT[8];
    char str[32];
    uint16_t adc_acc = 0;
    uint8_t adc_count = 0;

    while(1)
    {
        switch(current_task)
        {
            case TASK_ADC:
                adc_acc += adc1()->read_temperature();
                if(++adc_count >= ADC_SAMPLE) {
                    float temp = CalculateTemperature(adc_acc / ADC_SAMPLE);
                    adc_acc = 0;
                    adc_count = 0;

                    // Prepare string for LCD
                    snprintf(str, sizeof(str), "%.1f C", temp);
                    lcd1.start(&lcd1.par);
                    lcd1.drawstring16x24(&lcd1.par, str, 10, 40, ST77XX_BLACK, ST77XX_GREEN);
                    lcd1.stop(&lcd1.par);
                }
                break;

            case TASK_BT:
                // Snapshot USART buffer safely
                __disable_irq();
                size_t rx_len = usart1()->rx_index();
                if(rx_len > USART1_RX_BUFFER_SIZE) rx_len = USART1_RX_BUFFER_SIZE;
                memcpy(rx_snapshot, usart1()->rxbuff, rx_len);
                rx_snapshot[rx_len] = 0;
                __enable_irq();

                lcd1.start(&lcd1.par);
                lcd1.drawstring16x24(&lcd1.par, rx_snapshot, 10, 80, ST77XX_BLACK, ST77XX_GREEN);
                lcd1.stop(&lcd1.par);

                // Process Wi-Fi / commands
                if(rx_len && strstr(rx_snapshot, "\r\n")) {
                    // tokenize and handle command


                    usart1()->rx_purge();
                }
                break;

            case TASK_LCD:
                rtc()->dr2vec(vecD);
                rtc()->tr2vec(vecT);

                lcd1.start(&lcd1.par); // only one CS toggle
                func()->format_string(str, sizeof(str), "%d%d:%d%d:%d%d", vecT[0], vecT[1], vecT[2], vecT[3], vecT[4], vecT[5]);
                lcd1.drawstring16x24(&lcd1.par, str, 10, 120, ST77XX_BLACK, ST77XX_GREEN);

                lcd1.drawstring12x16(&lcd1.par, (char*)WeekDay_String(vecD[2]), 10, 160, ST77XX_BLACK, ST77XX_GREEN);

                func()->format_string(str, sizeof(str), "%d%d-%d%d-20%d%d",
                                      vecD[5], vecD[6], vecD[3], vecD[4], vecD[0], vecD[1]);
                lcd1.drawstring16x24(&lcd1.par, str, 10, 200, ST77XX_RED, ST77XX_GREEN);
                lcd1.stop(&lcd1.par);
                break;
        }

        // Round-robin
        if(++current_task >= TASK_MAX) current_task = 0;
    }
}

void Error_Handler(void)
{
    __disable_irq();
    while (1) {
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}

#endif

