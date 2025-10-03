/******************************************************************************
	STM32 XXX TIM IRQ
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     08102024
Comment:
	
*******************************************************************************/
#include "timer_irq.h"

/*** Library ***/
#include "stm32fxxxtim1and8.h"
#include "stm32fxxxtim2to5.h"
#include "stm32fxxxtim6and7.h"
#include "stm32fxxxtim9to14.h"

/*** Default Callback Implementations ***/
void tim1_b_callback(void) {}
void tim1_u_callback(void) {}
void tim1_t_callback(void) {}
void tim1_cc1_callback(void) {}
void tim1_cc2_callback(void) {}
void tim1_cc3_callback(void) {}
void tim1_cc4_callback(void) {}

void tim2_b_callback(void) {}
void tim2_u_callback(void) {}
void tim2_t_callback(void) {}
void tim2_cc1_callback(void) {}
void tim2_cc2_callback(void) {}
void tim2_cc3_callback(void) {}
void tim2_cc4_callback(void) {}

void tim3_b_callback(void) {}
void tim3_u_callback(void) {}
void tim3_t_callback(void) {}
void tim3_cc1_callback(void) {}
void tim3_cc2_callback(void) {}
void tim3_cc3_callback(void) {}
void tim3_cc4_callback(void) {}

void tim4_b_callback(void) {}
void tim4_u_callback(void) {}
void tim4_t_callback(void) {}
void tim4_cc1_callback(void) {}
void tim4_cc2_callback(void) {}
void tim4_cc3_callback(void) {}
void tim4_cc4_callback(void) {}

void tim5_b_callback(void) {}
void tim5_u_callback(void) {}
void tim5_t_callback(void) {}
void tim5_cc1_callback(void) {}
void tim5_cc2_callback(void) {}
void tim5_cc3_callback(void) {}
void tim5_cc4_callback(void) {}

void tim6_u_callback(void) {}
void tim7_u_callback(void) {}

void tim8_b_callback(void) {}
void tim8_u_callback(void) {}
void tim8_t_callback(void) {}
void tim8_cc1_callback(void) {}
void tim8_cc2_callback(void) {}
void tim8_cc3_callback(void) {}
void tim8_cc4_callback(void) {}

void tim9_u_callback(void) {}
void tim9_t_callback(void) {}

void tim10_u_callback(void) {}

void tim11_u_callback(void) {}
void tim11_t_callback(void) {}

void tim12_u_callback(void) {}
void tim12_t_callback(void) {}
void tim12_cc1_callback(void) {}
void tim12_cc2_callback(void) {}

void tim13_u_callback(void) {}
void tim13_t_callback(void) {}

void tim14_u_callback(void) {}
void tim14_t_callback(void) {}

/*** Timer IRQ Handlers ***/
void TIM1_BRK_TIM9_IRQHandler(void) {
    if (TIM1->SR & TIM_SR_BIF) {
        TIM1->SR &= ~TIM_SR_BIF;
        //tim1_b_callback();
        if(tim1()->callback.b){ tim1()->callback.b(); }
    }
    if (TIM9->SR & TIM_SR_UIF) {
        //tim9_u_callback();
        if(tim9()->callback.u){ tim9()->callback.u(); }
        TIM9->SR &= ~TIM_SR_UIF;
    }
}

void TIM1_UP_TIM10_IRQHandler(void) {
    if (TIM1->SR & TIM_SR_UIF) {
        TIM1->SR &= ~TIM_SR_UIF;
        //tim1_u_callback();
        if(tim1()->callback.u){ tim1()->callback.u(); }
    }
    if (TIM10->SR & TIM_SR_UIF) {
        //tim10_u_callback();
        if(tim10()->callback.u){ tim10()->callback.u(); }
        TIM10->SR &= ~TIM_SR_UIF;
    }
}

void TIM1_TRG_COM_TIM11_IRQHandler(void) {
    if (TIM1->SR & TIM_SR_TIF) {
        TIM1->SR &= ~TIM_SR_TIF;
        //tim1_t_callback();
        if(tim1()->callback.t){ tim1()->callback.t(); }
    }
    if (TIM11->SR & TIM_SR_UIF) {
        //tim11_u_callback();
        if(tim11()->callback.u){ tim11()->callback.u(); }
        TIM11->SR &= ~TIM_SR_UIF;
    }
}

void TIM1_CC_IRQHandler(void) {
    if (TIM1->SR & TIM_SR_CC1IF) {
        TIM1->SR &= ~TIM_SR_CC1IF;
        //tim1_cc1_callback();
        if(tim1()->callback.cc1){ tim1()->callback.cc1(); }
    }
    if (TIM1->SR & TIM_SR_CC2IF) {
        TIM1->SR &= ~TIM_SR_CC2IF;
        //tim1_cc2_callback();
        if(tim1()->callback.cc2){ tim1()->callback.cc2(); }
    }
    if (TIM1->SR & TIM_SR_CC3IF) {
        TIM1->SR &= ~TIM_SR_CC3IF;
        //tim1_cc3_callback();
        if(tim1()->callback.cc3){ tim1()->callback.cc3(); }
    }
    if (TIM1->SR & TIM_SR_CC4IF) {
        TIM1->SR &= ~TIM_SR_CC4IF;
        //tim1_cc4_callback();
        if(tim1()->callback.cc4){ tim1()->callback.cc4(); }
    }
}

// Repeat similar structure for other timers
void TIM2_IRQHandler(void) {
    if (TIM2->SR & TIM_SR_UIF) {
        //tim2_u_callback();
        if(tim2()->callback.u){ tim2()->callback.u(); }
        TIM2->SR &= ~TIM_SR_UIF;
    }
    if (TIM2->SR & TIM_SR_TIF) {
        //tim2_t_callback();
        if(tim2()->callback.t){ tim2()->callback.t(); }
        TIM2->SR &= ~TIM_SR_TIF;
    }
    if (TIM2->SR & TIM_SR_CC1IF) {
        //tim2_cc1_callback();
        if(tim2()->callback.cc1){ tim2()->callback.cc1(); }
        TIM2->SR &= ~TIM_SR_CC1IF;
    }
    if (TIM2->SR & TIM_SR_CC2IF) {
        //tim2_cc2_callback();
        if(tim2()->callback.cc2){ tim2()->callback.cc2(); }
        TIM2->SR &= ~TIM_SR_CC2IF;
    }
    if (TIM2->SR & TIM_SR_CC3IF) {
        //tim2_cc3_callback();
        if(tim2()->callback.cc3){ tim2()->callback.cc3(); }
        TIM2->SR &= ~TIM_SR_CC3IF;
    }
    if (TIM2->SR & TIM_SR_CC4IF) {
        //tim2_cc4_callback();
        if(tim2()->callback.cc4){ tim2()->callback.cc4(); }
        TIM2->SR &= ~TIM_SR_CC4IF;
    }
}

void TIM3_IRQHandler(void) {
    if (TIM3->SR & TIM_SR_UIF) {
        //tim3_u_callback();
        if(tim3()->callback.u){ tim3()->callback.u(); }
        TIM3->SR &= ~TIM_SR_UIF;
    }
    if (TIM3->SR & TIM_SR_TIF) {
        //tim3_t_callback();
        if(tim3()->callback.t){ tim3()->callback.t(); }
        TIM3->SR &= ~TIM_SR_TIF;
    }
    if (TIM3->SR & TIM_SR_CC1IF) {
        //tim3_cc1_callback();
        if(tim3()->callback.cc1){ tim3()->callback.cc1(); }
        TIM3->SR &= ~TIM_SR_CC1IF;
    }
    if (TIM3->SR & TIM_SR_CC2IF) {
        //tim3_cc2_callback();
        if(tim3()->callback.cc2){ tim3()->callback.cc2(); }
        TIM3->SR &= ~TIM_SR_CC2IF;
    }
    if (TIM3->SR & TIM_SR_CC3IF) {
        //tim3_cc3_callback();
        if(tim3()->callback.cc3){ tim3()->callback.cc3(); }
        TIM3->SR &= ~TIM_SR_CC3IF;
    }
    if (TIM3->SR & TIM_SR_CC4IF) {
        //tim3_cc4_callback();
        if(tim3()->callback.cc4){ tim3()->callback.cc4(); }
        TIM3->SR &= ~TIM_SR_CC4IF;
    }
}

void TIM4_IRQHandler(void) {
    if (TIM4->SR & TIM_SR_UIF) {
        //tim4_u_callback();
        if(tim4()->callback.u){ tim4()->callback.u(); }
        TIM4->SR &= ~TIM_SR_UIF;
    }
    if (TIM4->SR & TIM_SR_TIF) {
        //tim4_t_callback();
        if(tim4()->callback.t){ tim4()->callback.t(); }
        TIM4->SR &= ~TIM_SR_TIF;
    }
    if (TIM4->SR & TIM_SR_CC1IF) {
        //tim4_cc1_callback();
        if(tim4()->callback.cc1){ tim4()->callback.cc1(); }
        TIM4->SR &= ~TIM_SR_CC1IF;
    }
    if (TIM4->SR & TIM_SR_CC2IF) {
        //tim4_cc2_callback();
        if(tim4()->callback.cc2){ tim4()->callback.cc2(); }
        TIM4->SR &= ~TIM_SR_CC2IF;
    }
    if (TIM4->SR & TIM_SR_CC3IF) {
        //tim4_cc3_callback();
        if(tim4()->callback.cc3){ tim4()->callback.cc3(); }
        TIM4->SR &= ~TIM_SR_CC3IF;
    }
    if (TIM4->SR & TIM_SR_CC4IF) {
        //tim4_cc4_callback();
        if(tim4()->callback.cc4){ tim4()->callback.cc4(); }
        TIM4->SR &= ~TIM_SR_CC4IF;
    }
}

void TIM5_IRQHandler(void) {
    if (TIM5->SR & TIM_SR_UIF) {
        //tim5_u_callback();
        if(tim5()->callback.u){ tim5()->callback.u(); }
        TIM5->SR &= ~TIM_SR_UIF;
    }
    if (TIM5->SR & TIM_SR_TIF) {
        //tim5_t_callback();
        if(tim5()->callback.t){ tim5()->callback.t(); }
        TIM5->SR &= ~TIM_SR_TIF;
    }
    if (TIM5->SR & TIM_SR_CC1IF) {
        //tim5_cc1_callback();
        if(tim5()->callback.cc1){ tim5()->callback.cc1(); }
        TIM5->SR &= ~TIM_SR_CC1IF;
    }
    if (TIM5->SR & TIM_SR_CC2IF) {
        //tim5_cc2_callback();
        if(tim5()->callback.cc2){ tim5()->callback.cc2(); }
        TIM5->SR &= ~TIM_SR_CC2IF;
    }
    if (TIM5->SR & TIM_SR_CC3IF) {
        //tim5_cc3_callback();
        if(tim5()->callback.cc3){ tim5()->callback.cc3(); }
        TIM5->SR &= ~TIM_SR_CC3IF;
    }
    if (TIM5->SR & TIM_SR_CC4IF) {
        //tim5_cc4_callback();
        if(tim5()->callback.cc4){ tim5()->callback.cc4(); }
        TIM5->SR &= ~TIM_SR_CC4IF;
    }
}

#ifdef STM32F446xx
// TIM6 and TIM7 only have update interrupt
void TIM6_DAC_IRQHandler(void) {
    if (TIM6->SR & TIM_SR_UIF) {
        //tim6_u_callback();
        if(tim6()->callback.u){ tim6()->callback.u(); }
        TIM6->SR &= ~TIM_SR_UIF;
    }
}

void TIM7_IRQHandler(void) {
    if (TIM7->SR & TIM_SR_UIF) {
        //tim7_u_callback();
        if(tim7()->callback.u){ tim7()->callback.u(); }
        TIM7->SR &= ~TIM_SR_UIF;
    }
}

// TIM8 has similar structure
void TIM8_BRK_IRQHandler(void) {
    if (TIM8->SR & TIM_SR_BIF) {
        //tim8_b_callback();
        if(tim8()->callback.b){ tim8()->callback.b(); }
        TIM8->SR &= ~TIM_SR_BIF;
    }
}

void TIM8_BRK_TIM12_IRQHandler(void) {}

void TIM8_UP_IRQHandler(void) {
    if (TIM8->SR & TIM_SR_UIF) {
        //tim8_u_callback();
        if(tim8()->callback.u){ tim8()->callback.u(); }
        TIM8->SR &= ~TIM_SR_UIF;
    }
}

void TIM8_UP_TIM13_IRQHandler(void) {}

void TIM8_TRG_COM_IRQHandler(void) {
    if (TIM8->SR & TIM_SR_TIF) {
        //tim8_t_callback();
        if(tim8()->callback.t){ tim8()->callback.t(); }
        TIM8->SR &= ~TIM_SR_TIF;
    }
}

void TIM8_TRG_COM_TIM14_IRQHandler(void) {};

void TIM8_CC_IRQHandler(void) {
    if (TIM8->SR & TIM_SR_CC1IF) {
        //tim8_cc1_callback();
        if(tim8()->callback.cc1){ tim8()->callback.cc1(); }
        TIM8->SR &= ~TIM_SR_CC1IF;
    }
    if (TIM8->SR & TIM_SR_CC2IF) {
        //tim8_cc2_callback();
        if(tim8()->callback.cc2){ tim8()->callback.cc2(); }
        TIM8->SR &= ~TIM_SR_CC2IF;
    }
    if (TIM8->SR & TIM_SR_CC3IF) {
        //tim8_cc3_callback();
        if(tim8()->callback.cc3){ tim8()->callback.cc3(); }
        TIM8->SR &= ~TIM_SR_CC3IF;
    }
    if (TIM8->SR & TIM_SR_CC4IF) {
        //tim8_cc4_callback();
        if(tim8()->callback.cc4){ tim8()->callback.cc4(); }
        TIM8->SR &= ~TIM_SR_CC4IF;
    }
}
#endif

void TIM9_IRQHandler(void) {
    if (TIM9->SR & TIM_SR_UIF) {
        //tim9_u_callback();
        if(tim9()->callback.u){ tim9()->callback.u(); }
        TIM9->SR &= ~TIM_SR_UIF;
    }
    if (TIM9->SR & TIM_SR_TIF) {
        //tim9_t_callback();
        if(tim9()->callback.t){ tim9()->callback.t(); }
        TIM9->SR &= ~TIM_SR_TIF;
    }
}

void TIM10_IRQHandler(void) {
    if (TIM10->SR & TIM_SR_UIF) {
        //tim10_u_callback();
        if(tim10()->callback.u){ tim10()->callback.u(); }
        TIM10->SR &= ~TIM_SR_UIF;
    }
}

void TIM11_IRQHandler(void) {
    if (TIM11->SR & TIM_SR_UIF) {
        //tim11_u_callback();
        if(tim11()->callback.u){ tim11()->callback.u(); }
        TIM11->SR &= ~TIM_SR_UIF;
    }
    if (TIM11->SR & TIM_SR_TIF) {
        //tim11_t_callback();
        if(tim11()->callback.t){ tim11()->callback.t(); }
        TIM11->SR &= ~TIM_SR_TIF;
    }
}

#ifdef STM32F446xx
void TIM12_IRQHandler(void) {
    if (TIM12->SR & TIM_SR_UIF) {
        //tim12_u_callback();
        if(tim12()->callback.u){ tim12()->callback.u(); }
        TIM12->SR &= ~TIM_SR_UIF;
    }
    if (TIM12->SR & TIM_SR_TIF) {
        //tim12_t_callback();
        if(tim12()->callback.t){ tim12()->callback.t(); }
        TIM12->SR &= ~TIM_SR_TIF;
    }
    if (TIM12->SR & TIM_SR_CC1IF) {
        //tim12_cc1_callback();
        if(tim12()->callback.cc1){ tim12()->callback.cc1(); }
        TIM12->SR &= ~TIM_SR_CC1IF;
    }
    if (TIM12->SR & TIM_SR_CC2IF) {
        //tim12_cc2_callback();
        if(tim12()->callback.cc2){ tim12()->callback.cc2(); }
        TIM12->SR &= ~TIM_SR_CC2IF;
    }
}

void TIM13_IRQHandler(void) {
    if (TIM13->SR & TIM_SR_UIF) {
        //tim13_u_callback();
        if(tim13()->callback.u){ tim13()->callback.u(); }
        TIM13->SR &= ~TIM_SR_UIF;
    }
}

void TIM14_IRQHandler(void) {
    if (TIM14->SR & TIM_SR_UIF) {
        //tim14_u_callback();
        if(tim14()->callback.u){ tim14()->callback.u(); }
        TIM14->SR &= ~TIM_SR_UIF;
    }
}

#endif
/*** EOF ***/

