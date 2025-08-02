/******************************************************************************
	STM32 XXX GPIOBF
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 25032024
Comment:
	wrapper
*******************************************************************************/
#ifndef _STM32GPIOBF_H_
	#define _STM32GPIOBF_H_

#include <stdint.h>

/* GPIO Registers Structure */
typedef volatile struct {
    /*** GPIO -> moder ***/
    union {
        struct {
            uint32_t mode0 : 2;  /* Mode for pin 0 */
            uint32_t mode1 : 2;  /* Mode for pin 1 */
            uint32_t mode2 : 2;  /* Mode for pin 2 */
            uint32_t mode3 : 2;  /* Mode for pin 3 */
            uint32_t mode4 : 2;  /* Mode for pin 4 */
            uint32_t mode5 : 2;  /* Mode for pin 5 */
            uint32_t mode6 : 2;  /* Mode for pin 6 */
            uint32_t mode7 : 2;  /* Mode for pin 7 */
            uint32_t mode8 : 2;  /* Mode for pin 8 */
            uint32_t mode9 : 2;  /* Mode for pin 9 */
            uint32_t mode10: 2;  /* Mode for pin 10 */
            uint32_t mode11: 2;  /* Mode for pin 11 */
            uint32_t mode12: 2;  /* Mode for pin 12 */
            uint32_t mode13: 2;  /* Mode for pin 13 */
            uint32_t mode14: 2;  /* Mode for pin 14 */
            uint32_t mode15: 2;  /* Mode for pin 15 */
        } par;
        uint32_t reg;
    } moder;  /* 0x00 */

    /*** GPIO -> otyper ***/
    union {
        struct {
            uint32_t ot0 : 1;    /* Output type for pin 0 */
            uint32_t ot1 : 1;    /* Output type for pin 1 */
            uint32_t ot2 : 1;    /* Output type for pin 2 */
            uint32_t ot3 : 1;    /* Output type for pin 3 */
            uint32_t ot4 : 1;    /* Output type for pin 4 */
            uint32_t ot5 : 1;    /* Output type for pin 5 */
            uint32_t ot6 : 1;    /* Output type for pin 6 */
            uint32_t ot7 : 1;    /* Output type for pin 7 */
            uint32_t ot8 : 1;    /* Output type for pin 8 */
            uint32_t ot9 : 1;    /* Output type for pin 9 */
            uint32_t ot10: 1;    /* Output type for pin 10 */
            uint32_t ot11: 1;    /* Output type for pin 11 */
            uint32_t ot12: 1;    /* Output type for pin 12 */
            uint32_t ot13: 1;    /* Output type for pin 13 */
            uint32_t ot14: 1;    /* Output type for pin 14 */
            uint32_t ot15: 1;    /* Output type for pin 15 */
            uint32_t reserved: 16; /* Reserved for padding */
        } par;
        struct {
        	uint16_t ot;   /* Bit set register (low 16 pars) */
        	uint16_t reserved;   /* Bit reset register (high 16 pars) */
        } word;
        uint32_t reg;
    } otyper;  /* 0x04 */

    /*** GPIO -> ospeedr ***/
    union {
        struct {
            uint32_t ospeed0 : 2; /* Output speed for pin 0 */
            uint32_t ospeed1 : 2; /* Output speed for pin 1 */
            uint32_t ospeed2 : 2; /* Output speed for pin 2 */
            uint32_t ospeed3 : 2; /* Output speed for pin 3 */
            uint32_t ospeed4 : 2; /* Output speed for pin 4 */
            uint32_t ospeed5 : 2; /* Output speed for pin 5 */
            uint32_t ospeed6 : 2; /* Output speed for pin 6 */
            uint32_t ospeed7 : 2; /* Output speed for pin 7 */
            uint32_t ospeed8 : 2; /* Output speed for pin 8 */
            uint32_t ospeed9 : 2; /* Output speed for pin 9 */
            uint32_t ospeed10: 2; /* Output speed for pin 10 */
            uint32_t ospeed11: 2; /* Output speed for pin 11 */
            uint32_t ospeed12: 2; /* Output speed for pin 12 */
            uint32_t ospeed13: 2; /* Output speed for pin 13 */
            uint32_t ospeed14: 2; /* Output speed for pin 14 */
            uint32_t ospeed15: 2; /* Output speed for pin 15 */
        } par;
        uint32_t reg;
    } ospeedr;  /* 0x08 */

    /*** GPIO -> pupdr ***/
    union {
        struct {
            uint32_t pupd0 : 2; /* Pull-up/Pull-down for pin 0 */
            uint32_t pupd1 : 2; /* Pull-up/Pull-down for pin 1 */
            uint32_t pupd2 : 2; /* Pull-up/Pull-down for pin 2 */
            uint32_t pupd3 : 2; /* Pull-up/Pull-down for pin 3 */
            uint32_t pupd4 : 2; /* Pull-up/Pull-down for pin 4 */
            uint32_t pupd5 : 2; /* Pull-up/Pull-down for pin 5 */
            uint32_t pupd6 : 2; /* Pull-up/Pull-down for pin 6 */
            uint32_t pupd7 : 2; /* Pull-up/Pull-down for pin 7 */
            uint32_t pupd8 : 2; /* Pull-up/Pull-down for pin 8 */
            uint32_t pupd9 : 2; /* Pull-up/Pull-down for pin 9 */
            uint32_t pupd10: 2; /* Pull-up/Pull-down for pin 10 */
            uint32_t pupd11: 2; /* Pull-up/Pull-down for pin 11 */
            uint32_t pupd12: 2; /* Pull-up/Pull-down for pin 12 */
            uint32_t pupd13: 2; /* Pull-up/Pull-down for pin 13 */
            uint32_t pupd14: 2; /* Pull-up/Pull-down for pin 14 */
            uint32_t pupd15: 2; /* Pull-up/Pull-down for pin 15 */
        } par;
        uint32_t reg;
    } pupdr;  /* 0x0C */

    /*** GPIO -> idr ***/
    union {
        struct {
            uint32_t id0 : 1;    /* Input data for pin 0 */
            uint32_t id1 : 1;    /* Input data for pin 1 */
            uint32_t id2 : 1;    /* Input data for pin 2 */
            uint32_t id3 : 1;    /* Input data for pin 3 */
            uint32_t id4 : 1;    /* Input data for pin 4 */
            uint32_t id5 : 1;    /* Input data for pin 5 */
            uint32_t id6 : 1;    /* Input data for pin 6 */
            uint32_t id7 : 1;    /* Input data for pin 7 */
            uint32_t id8 : 1;    /* Input data for pin 8 */
            uint32_t id9 : 1;    /* Input data for pin 9 */
            uint32_t id10: 1;    /* Input data for pin 10 */
            uint32_t id11: 1;    /* Input data for pin 11 */
            uint32_t id12: 1;    /* Input data for pin 12 */
            uint32_t id13: 1;    /* Input data for pin 13 */
            uint32_t id14: 1;    /* Input data for pin 14 */
            uint32_t id15: 1;    /* Input data for pin 15 */
            uint32_t reserved: 16; /* Reserved for padding */
        } par;
        struct {
        	uint16_t id;   /* Bit set register (low 16 pars) */
			uint16_t reserved;   /* Bit reset register (high 16 pars) */
        } word;
        uint32_t reg;
    } idr;  /* 0x10 */

    /*** GPIO -> odr ***/
    union {
        struct {
            uint32_t od0 : 1;    /* Output data for pin 0 */
            uint32_t od1 : 1;    /* Output data for pin 1 */
            uint32_t od2 : 1;    /* Output data for pin 2 */
            uint32_t od3 : 1;    /* Output data for pin 3 */
            uint32_t od4 : 1;    /* Output data for pin 4 */
            uint32_t od5 : 1;    /* Output data for pin 5 */
            uint32_t od6 : 1;    /* Output data for pin 6 */
            uint32_t od7 : 1;    /* Output data for pin 7 */
            uint32_t od8 : 1;    /* Output data for pin 8 */
            uint32_t od9 : 1;    /* Output data for pin 9 */
            uint32_t od10: 1;    /* Output data for pin 10 */
            uint32_t od11: 1;    /* Output data for pin 11 */
            uint32_t od12: 1;    /* Output data for pin 12 */
            uint32_t od13: 1;    /* Output data for pin 13 */
            uint32_t od14: 1;    /* Output data for pin 14 */
            uint32_t od15: 1;    /* Output data for pin 15 */
            uint32_t reserved: 16; /* Reserved for padding */
        } par;
        struct {
        	uint16_t od;   /* Bit set register (low 16 pars) */
			uint16_t reserved;   /* Bit reset register (high 16 pars) */
        } word;
        uint32_t reg;
    } odr;  /* 0x14 */

    /*** GPIO -> bsrr ***/
    union {
        struct {
            uint32_t bs0 : 1;    /* Bit set for pin 0 */
            uint32_t bs1 : 1;    /* Bit set for pin 1 */
            uint32_t bs2 : 1;    /* Bit set for pin 2 */
            uint32_t bs3 : 1;    /* Bit set for pin 3 */
            uint32_t bs4 : 1;    /* Bit set for pin 4 */
            uint32_t bs5 : 1;    /* Bit set for pin 5 */
            uint32_t bs6 : 1;    /* Bit set for pin 6 */
            uint32_t bs7 : 1;    /* Bit set for pin 7 */
            uint32_t bs8 : 1;    /* Bit set for pin 8 */
            uint32_t bs9 : 1;    /* Bit set for pin 9 */
            uint32_t bs10: 1;    /* Bit set for pin 10 */
            uint32_t bs11: 1;    /* Bit set for pin 11 */
            uint32_t bs12: 1;    /* Bit set for pin 12 */
            uint32_t bs13: 1;    /* Bit set for pin 13 */
            uint32_t bs14: 1;    /* Bit set for pin 14 */
            uint32_t bs15: 1;    /* Bit set for pin 15 */
            uint32_t br0 : 1;    /* Bit reset for pin 0 */
            uint32_t br1 : 1;    /* Bit reset for pin 1 */
            uint32_t br2 : 1;    /* Bit reset for pin 2 */
            uint32_t br3 : 1;    /* Bit reset for pin 3 */
            uint32_t br4 : 1;    /* Bit reset for pin 4 */
            uint32_t br5 : 1;    /* Bit reset for pin 5 */
            uint32_t br6 : 1;    /* Bit reset for pin 6 */
            uint32_t br7 : 1;    /* Bit reset for pin 7 */
            uint32_t br8 : 1;    /* Bit reset for pin 8 */
            uint32_t br9 : 1;    /* Bit reset for pin 9 */
            uint32_t br10: 1;    /* Bit reset for pin 10 */
            uint32_t br11: 1;    /* Bit reset for pin 11 */
            uint32_t br12: 1;    /* Bit reset for pin 12 */
            uint32_t br13: 1;    /* Bit reset for pin 13 */
            uint32_t br14: 1;    /* Bit reset for pin 14 */
            uint32_t br15: 1;    /* Bit reset for pin 15 */
        } par;
        struct {
            uint16_t bs;   /* Bit set register (low 16 pars) */
            uint16_t br;   /* Bit reset register (high 16 pars) */
        } word;
        uint32_t reg;
    } bsrr;  /* 0x18 */

    /*** GPIO -> lckr ***/
    union {
        struct {
            uint32_t lck0 : 1;    /* Lock for pin 0 */
            uint32_t lck1 : 1;    /* Lock for pin 1 */
            uint32_t lck2 : 1;    /* Lock for pin 2 */
            uint32_t lck3 : 1;    /* Lock for pin 3 */
            uint32_t lck4 : 1;    /* Lock for pin 4 */
            uint32_t lck5 : 1;    /* Lock for pin 5 */
            uint32_t lck6 : 1;    /* Lock for pin 6 */
            uint32_t lck7 : 1;    /* Lock for pin 7 */
            uint32_t lck8 : 1;    /* Lock for pin 8 */
            uint32_t lck9 : 1;    /* Lock for pin 9 */
            uint32_t lck10: 1;    /* Lock for pin 10 */
            uint32_t lck11: 1;    /* Lock for pin 11 */
            uint32_t lck12: 1;    /* Lock for pin 12 */
            uint32_t lck13: 1;    /* Lock for pin 13 */
            uint32_t lck14: 1;    /* Lock for pin 14 */
            uint32_t lck15: 1;    /* Lock for pin 15 */
            uint32_t reserved: 16; /* Reserved for padding */
        } par;
        struct {
            uint16_t lck; /* Lock register (low 16 pars) */
            uint16_t reserved; /* Reserved for padding */
        } word;
        uint32_t reg;
    } lckr;  /* 0x1C */

    /*** GPIO -> afr ***/
    union {
        struct {
            uint32_t af0 : 4;    /* Alternate function for pin 0 */
            uint32_t af1 : 4;    /* Alternate function for pin 1 */
            uint32_t af2 : 4;    /* Alternate function for pin 2 */
            uint32_t af3 : 4;    /* Alternate function for pin 3 */
            uint32_t af4 : 4;    /* Alternate function for pin 4 */
            uint32_t af5 : 4;    /* Alternate function for pin 5 */
            uint32_t af6 : 4;    /* Alternate function for pin 6 */
            uint32_t af7 : 4;    /* Alternate function for pin 7 */
            uint32_t af8 : 4;    /* Alternate function for pin 8 */
            uint32_t af9 : 4;    /* Alternate function for pin 9 */
            uint32_t af10: 4;    /* Alternate function for pin 10 */
            uint32_t af11: 4;    /* Alternate function for pin 11 */
            uint32_t af12: 4;    /* Alternate function for pin 12 */
            uint32_t af13: 4;    /* Alternate function for pin 13 */
            uint32_t af14: 4;    /* Alternate function for pin 14 */
            uint32_t af15: 4;    /* Alternate function for pin 15 */
        } par;
        struct {
            uint32_t l; /* Alternate function low register (0x20) */
            uint32_t h; /* Alternate function high register (0x24) */
        } reg;
    } afr;  /* 0x20 and 0x24 */

} STM32FXXXGPIOX_TypeDef;

#endif /* _STM32GPIOBF_H_ */

/*** EOF ***/

