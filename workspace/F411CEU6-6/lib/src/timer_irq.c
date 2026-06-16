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

/*** Default Callback Implementation ***/
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
	uint32_t sr1 = TIM1->SR;
	uint32_t sr9 = TIM9->SR;
    if (sr1 & TIM_SR_BIF) {
        TIM1->SR &= ~TIM_SR_BIF;
        //tim1_b_callback();
        if(tim1()->callback->b){ tim1()->callback->b(); }
    }
    if (sr9 & TIM_SR_UIF) {
    	TIM9->SR &= ~TIM_SR_UIF;
        //tim9_u_callback();
        if(tim9()->callback->u){ tim9()->callback->u(); }
    }
}

void TIM1_UP_TIM10_IRQHandler(void) {
	uint32_t sr1 = TIM1->SR;
	uint32_t sr10 = TIM10->SR;
    if (sr1 & TIM_SR_UIF) {
        TIM1->SR &= ~TIM_SR_UIF;
        //tim1_u_callback();
        if(tim1()->callback->u){ tim1()->callback->u(); }
    }
    if (sr10 & TIM_SR_UIF) {
    	TIM10->SR &= ~TIM_SR_UIF;
        //tim10_u_callback();
        if(tim10()->callback->u){ tim10()->callback->u(); }
    }
}

void TIM1_TRG_COM_TIM11_IRQHandler(void) {
	uint32_t sr1 = TIM1->SR;
	uint32_t sr11 = TIM11->SR;
    if (sr1 & TIM_SR_TIF) {
        TIM1->SR &= ~TIM_SR_TIF;
        //tim1_t_callback();
        if(tim1()->callback->t){ tim1()->callback->t(); }
    }
    if (sr11 & TIM_SR_UIF) {
    	TIM11->SR &= ~TIM_SR_UIF;
        //tim11_u_callback();
        if(tim11()->callback->u){ tim11()->callback->u(); }
    }
}

void TIM1_CC_IRQHandler(void) {
	tim1and8_callback* cb = tim1()->callback;
	uint32_t sr = TIM1->SR;
    if (sr & TIM_SR_CC1IF) {
        TIM1->SR &= ~TIM_SR_CC1IF;
        //tim1_cc1_callback();
        if(cb->cc1){ cb->cc1(); }
    }
    if (sr & TIM_SR_CC2IF) {
        TIM1->SR &= ~TIM_SR_CC2IF;
        //tim1_cc2_callback();
        if(cb->cc2){ cb->cc2(); }
    }
    if (sr & TIM_SR_CC3IF) {
        TIM1->SR &= ~TIM_SR_CC3IF;
        //tim1_cc3_callback();
        if(cb->cc3){ cb->cc3(); }
    }
    if (sr & TIM_SR_CC4IF) {
        TIM1->SR &= ~TIM_SR_CC4IF;
        //tim1_cc4_callback();
        if(cb->cc4){ cb->cc4(); }
    }
}

// Repeat similar structure for other timers
void TIM2_IRQHandler(void) {
	tim2to5_callback* cb = tim2()->callback;
	uint32_t sr = TIM2->SR;
    if (sr & TIM_SR_UIF) {
    	TIM2->SR &= ~TIM_SR_UIF;
        //tim2_u_callback();
        if(cb->u){ cb->u(); }
    }
    if (sr & TIM_SR_TIF) {
    	TIM2->SR &= ~TIM_SR_TIF;
        //tim2_t_callback();
        if(cb->t){ cb->t(); }
    }
    if (sr & TIM_SR_CC1IF) {
    	TIM2->SR &= ~TIM_SR_CC1IF;
        //tim2_cc1_callback();
        if(cb->cc1){ cb->cc1(); }
    }
    if (sr & TIM_SR_CC2IF) {
    	TIM2->SR &= ~TIM_SR_CC2IF;
        //tim2_cc2_callback();
        if(cb->cc2){ cb->cc2(); }
    }
    if (sr & TIM_SR_CC3IF) {
    	TIM2->SR &= ~TIM_SR_CC3IF;
        //tim2_cc3_callback();
        if(cb->cc3){ cb->cc3(); }
    }
    if (sr & TIM_SR_CC4IF) {
    	TIM2->SR &= ~TIM_SR_CC4IF;
        //tim2_cc4_callback();
        if(cb->cc4){ cb->cc4(); }
    }
}

void TIM3_IRQHandler(void) {
	tim2to5_callback* cb = tim3()->callback;
	uint32_t sr = TIM3->SR;
    if (sr & TIM_SR_UIF) {
    	TIM3->SR &= ~TIM_SR_UIF;
        //tim3_u_callback();
        if(cb->u){ cb->u(); }
    }
    if (sr & TIM_SR_TIF) {
    	TIM3->SR &= ~TIM_SR_TIF;
        //tim3_t_callback();
        if(cb->t){ cb->t(); }
    }
    if (sr & TIM_SR_CC1IF) {
    	TIM3->SR &= ~TIM_SR_CC1IF;
        //tim3_cc1_callback();
        if(cb->cc1){ cb->cc1(); }
    }
    if (sr & TIM_SR_CC2IF) {
    	TIM3->SR &= ~TIM_SR_CC2IF;
        //tim3_cc2_callback();
        if(cb->cc2){ cb->cc2(); }
    }
    if (sr & TIM_SR_CC3IF) {
    	TIM3->SR &= ~TIM_SR_CC3IF;
        //tim3_cc3_callback();
        if(cb->cc3){ cb->cc3(); }
    }
    if (sr & TIM_SR_CC4IF) {
    	TIM3->SR &= ~TIM_SR_CC4IF;
        //tim3_cc4_callback();
        if(cb->cc4){ cb->cc4(); }
    }
}

void TIM4_IRQHandler(void) {
	tim2to5_callback* cb = tim4()->callback;
	uint32_t sr = TIM4->SR;
    if (sr & TIM_SR_UIF) {
    	TIM4->SR &= ~TIM_SR_UIF;
        //tim4_u_callback();
        if(cb->u){ cb->u(); }
    }
    if (sr & TIM_SR_TIF) {
    	TIM4->SR &= ~TIM_SR_TIF;
        //tim4_t_callback();
        if(cb->t){ cb->t(); }
    }
    if (sr & TIM_SR_CC1IF) {
    	TIM4->SR &= ~TIM_SR_CC1IF;
        //tim4_cc1_callback();
        if(cb->cc1){ cb->cc1(); }
    }
    if (sr & TIM_SR_CC2IF) {
    	TIM4->SR &= ~TIM_SR_CC2IF;
        //tim4_cc2_callback();
        if(cb->cc2){ cb->cc2(); }
    }
    if (sr & TIM_SR_CC3IF) {
    	TIM4->SR &= ~TIM_SR_CC3IF;
        //tim4_cc3_callback();
        if(cb->cc3){ cb->cc3(); }
    }
    if (sr & TIM_SR_CC4IF) {
    	TIM4->SR &= ~TIM_SR_CC4IF;
        //tim4_cc4_callback();
        if(cb->cc4){ cb->cc4(); }
    }
}

void TIM5_IRQHandler(void) {
	tim2to5_callback* cb = tim5()->callback;
	uint32_t sr = TIM5->SR;
    if (sr & TIM_SR_UIF) {
    	TIM5->SR &= ~TIM_SR_UIF;
        //tim5_u_callback();
        if(cb->u){ cb->u(); }
    }
    if (sr & TIM_SR_TIF) {
    	TIM5->SR &= ~TIM_SR_TIF;
        //tim5_t_callback();
        if(cb->t){ cb->t(); }
    }
    if (sr & TIM_SR_CC1IF) {
    	TIM5->SR &= ~TIM_SR_CC1IF;
        //tim5_cc1_callback();
        if(cb->cc1){ cb->cc1(); }
    }
    if (sr & TIM_SR_CC2IF) {
    	TIM5->SR &= ~TIM_SR_CC2IF;
        //tim5_cc2_callback();
        if(cb->cc2){ cb->cc2(); }
    }
    if (sr & TIM_SR_CC3IF) {
    	TIM5->SR &= ~TIM_SR_CC3IF;
        //tim5_cc3_callback();
        if(cb->cc3){ cb->cc3(); }
    }
    if (sr & TIM_SR_CC4IF) {
    	TIM5->SR &= ~TIM_SR_CC4IF;
        //tim5_cc4_callback();
        if(cb->cc4){ cb->cc4(); }
    }
}

#ifdef STM32F446xx
// TIM6 and TIM7 only have update interrupt
void TIM6_DAC_IRQHandler(void) {
	uint32_t sr = TIM6->SR;
    if (sr & TIM_SR_UIF) {
    	TIM6->SR &= ~TIM_SR_UIF;
        //tim6_u_callback();
        if(tim6()->callback->u){ tim6()->callback->u(); }
    }
}

void TIM7_IRQHandler(void) {
	uint32_t sr = TIM7->SR;
    if (sr & TIM_SR_UIF) {
    	TIM7->SR &= ~TIM_SR_UIF;
        //tim7_u_callback();
        if(tim7()->callback->u){ tim7()->callback->u(); }
    }
}

// TIM8 has similar structure
void TIM8_BRK_IRQHandler(void) {
	uint32_t sr = TIM8->SR;
    if (sr & TIM_SR_BIF) {
    	TIM8->SR &= ~TIM_SR_BIF;
        //tim8_b_callback();
        if(tim8()->callback->b){ tim8()->callback->b(); }
    }
}

void TIM8_BRK_TIM12_IRQHandler(void) {}

void TIM8_UP_IRQHandler(void) {
	uint32_t sr = TIM8->SR;
    if (sr & TIM_SR_UIF) {
    	TIM8->SR &= ~TIM_SR_UIF;
        //tim8_u_callback();
        if(tim8()->callback->u){ tim8()->callback->u(); }
    }
}

void TIM8_UP_TIM13_IRQHandler(void) {}

void TIM8_TRG_COM_IRQHandler(void) {
	uint32_t sr = TIM8->SR;
    if (sr & TIM_SR_TIF) {
    	TIM8->SR &= ~TIM_SR_TIF;
        //tim8_t_callback();
        if(tim8()->callback->t){ tim8()->callback->t(); }
    }
}

void TIM8_TRG_COM_TIM14_IRQHandler(void) {};

void TIM8_CC_IRQHandler(void) {
	tim1and8_callback* cb = tim8()->callback;
	uint32_t sr = TIM8->SR;
    if (sr & TIM_SR_CC1IF) {
    	TIM8->SR &= ~TIM_SR_CC1IF;
        //tim8_cc1_callback();
        if(cb->cc1){ cb->cc1(); }
    }
    if (sr & TIM_SR_CC2IF) {
    	TIM8->SR &= ~TIM_SR_CC2IF;
        //tim8_cc2_callback();
        if(cb->cc2){ cb->cc2(); }
    }
    if (sr & TIM_SR_CC3IF) {
    	TIM8->SR &= ~TIM_SR_CC3IF;
        //tim8_cc3_callback();
        if(cb->cc3){ cb->cc3(); }
    }
    if (sr & TIM_SR_CC4IF) {
    	TIM8->SR &= ~TIM_SR_CC4IF;
        //tim8_cc4_callback();
        if(cb->cc4){ cb->cc4(); }
    }
}
#endif

void TIM9_IRQHandler(void) {
	tim9to14_callback* cb = tim9()->callback;
	uint32_t sr = TIM9->SR;
    if (sr & TIM_SR_UIF) {
    	TIM9->SR &= ~TIM_SR_UIF;
        //tim9_u_callback();
        if(cb->u){ cb->u(); }
    }
    if (sr & TIM_SR_TIF) {
    	TIM9->SR &= ~TIM_SR_TIF;
        //tim9_t_callback();
        if(cb->t){ cb->t(); }
    }
}

void TIM10_IRQHandler(void) {
	uint32_t sr = TIM10->SR;
    if (sr & TIM_SR_UIF) {
    	TIM10->SR &= ~TIM_SR_UIF;
        //tim10_u_callback();
        if(tim10()->callback->u){ tim10()->callback->u(); }
    }
}

void TIM11_IRQHandler(void) {
	tim9to14_callback* cb = tim11()->callback;
	uint32_t sr = TIM11->SR;
    if (sr & TIM_SR_UIF) {
    	TIM11->SR &= ~TIM_SR_UIF;
        //tim11_u_callback();
        if(cb->u){ cb->u(); }
    }
    if (sr & TIM_SR_TIF) {
    	TIM11->SR &= ~TIM_SR_TIF;
        //tim11_t_callback();
        if(cb->t){ cb->t(); }
    }
}

#ifdef STM32F446xx
void TIM12_IRQHandler(void) {
	tim9to14_callback* cb = tim12()->callback;
	uint32_t sr = TIM12->SR;
    if (sr & TIM_SR_UIF) {
    	TIM12->SR &= ~TIM_SR_UIF;
        //tim12_u_callback();
        if(cb->u){ cb->u(); }
    }
    if (sr & TIM_SR_TIF) {
    	TIM12->SR &= ~TIM_SR_TIF;
        //tim12_t_callback();
        if(cb->t){ cb->t(); }
    }
    if (sr & TIM_SR_CC1IF) {
    	TIM12->SR &= ~TIM_SR_CC1IF;
        //tim12_cc1_callback();
        if(cb->cc1){ cb->cc1(); }
    }
    if (sr & TIM_SR_CC2IF) {
    	TIM12->SR &= ~TIM_SR_CC2IF;
        //tim12_cc2_callback();
        if(cb->cc2){ cb->cc2(); }
    }
}

void TIM13_IRQHandler(void) {
	uint32_t sr = TIM13->SR;
    if (sr & TIM_SR_UIF) {
    	TIM13->SR &= ~TIM_SR_UIF;
        //tim13_u_callback();
        if(tim13()->callback->u){ tim13()->callback->u(); }
    }
}

void TIM14_IRQHandler(void) {
	uint32_t sr = TIM14->SR;
    if (sr & TIM_SR_UIF) {
    	TIM14->SR &= ~TIM_SR_UIF;
        //tim14_u_callback();
        if(tim14()->callback->u){ tim14()->callback->u(); }
    }
}

#endif
/*** EOF ***/

