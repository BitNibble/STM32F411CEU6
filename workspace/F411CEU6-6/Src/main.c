/****************************************************************
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Software: STM32CubeIDE v1.16.0 Build: 21983_20240628_1741 (UTC)
Hardware: STM32F411CEU6
Date: 16062026
Comment:
	Button K0:
GPIO PA0 - Button
	LED D2:
GPIO PC13 - D2
****************************************************************/

#include "stm32fxxxrcc.h"

int main(void) {
	rcc()->inic();
	fpu_enable();
    /* Loop forever */
	for(;;);
}
