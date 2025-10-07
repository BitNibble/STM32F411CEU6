/***************************************************
    STM32FXXX TOOLS – Optimized
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32FXXX
Update:   2025-10-02
Comment:  Safe, optimized, drop-in replacement
****************************************************/
#include "stm32fxxxtool.h"

// Shared global state for all C files
volatile int ft_Delay_Lock[FTDELAY_SIZE] = {0};
volatile int ftCounter[FTDELAY_SIZE] = {0};

// Fall-through delay
int ftdelayCycles(uint8_t lock_ID, unsigned int n_cycle, void (*execute)(void)) {
    int ret = 0;
    if (lock_ID > FTDELAY_SIZE) return 0; // safety check

    if (ft_Delay_Lock[lock_ID] != lock_ID) {
        ft_Delay_Lock[lock_ID] = lock_ID;
        ftCounter[lock_ID] = n_cycle;
        if(execute){ execute (); }
        ftCounter[lock_ID]--;
    } else {
        if (--ftCounter[lock_ID] > 0) {
            // still counting down, do nothing
        } else {
            ft_Delay_Lock[lock_ID] = 0;
            ret = 1; // delay expired
        }
    }
    return ret;
}

void ftdelayReset(uint8_t ID) {
    if (ID >= FTDELAY_SIZE) return; // safety check
    ft_Delay_Lock[ID] = 0;
    ftCounter[ID] = 0;
}

/*** EOF ***/

