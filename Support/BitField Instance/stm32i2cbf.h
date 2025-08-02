/******************************************************************************
	STM32 XXX I2CBF
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 16042024
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXI2CBF_H_
	#define _STM32FXXXI2CBF_H_

#include <inttypes.h>

/*** I2C BitField TypeDef ***/
typedef volatile struct {
    // CR1
    union {
        struct {
            uint32_t pe:1;
            uint32_t smbus:1;
            uint32_t reserved1:1;
            uint32_t smbtype:1;
            uint32_t enarp:1;
            uint32_t enpec:1;
            uint32_t engc:1;
            uint32_t nostretch:1;
            uint32_t start:1;
            uint32_t stop:1;
            uint32_t ack:1;
            uint32_t pos:1;
            uint32_t pec:1;
            uint32_t alert:1;
            uint32_t reserved2:1;
            uint32_t swrst:1;
            uint32_t reserved3:16;
        } par;
        uint32_t reg;
    } cr1;

    // CR2
    union {
        struct {
            uint32_t freq:6;
            uint32_t reserved1:2;
            uint32_t iterren:1;
            uint32_t itevten:1;
            uint32_t itbufen:1;
            uint32_t dmaen:1;
            uint32_t last:1;
            uint32_t reserved2:19;
        } par;
        uint32_t reg;
    } cr2;

    // OAR1
    union {
        struct {
            uint32_t add0:1;
            uint32_t add:9;
            uint32_t reserved1:5;
            uint32_t addmode:1;
            uint32_t reserved2:16;
        } par;
        uint32_t reg;
    } oar1;

    // OAR2
    union {
        struct {
            uint32_t endual:1;
            uint32_t add2:7;
            uint32_t reserved:24;
        } par;
        uint32_t reg;
    } oar2;

    // DR
    union {
        struct {
            uint32_t dr:8;
            uint32_t reserved:24;
        } par;
        uint32_t reg;
    } dr;

    // SR1
    union {
        struct {
            uint32_t sb:1;
            uint32_t addr:1;
            uint32_t btf:1;
            uint32_t add10:1;
            uint32_t stopf:1;
            uint32_t reserved1:1;
            uint32_t rxne:1;
            uint32_t txe:1;
            uint32_t berr:1;
            uint32_t arlo:1;
            uint32_t af:1;
            uint32_t ovr:1;
            uint32_t pecerr:1;
            uint32_t reserved2:1;
            uint32_t timeout:1;
            uint32_t smbalert:1;
            uint32_t reserved3:16;
        } par;
        uint32_t reg;
    } sr1;

    // SR2
    union {
        struct {
            uint32_t msl:1;
            uint32_t busy:1;
            uint32_t tra:1;
            uint32_t reserved1:1;
            uint32_t gencall:1;
            uint32_t smbdefault:1;
            uint32_t smbhost:1;
            uint32_t dualf:1;
            uint32_t pec:8;
            uint32_t reserved2:16;
        } par;
        uint32_t reg;
    } sr2;

    // CCR
    union {
        struct {
            uint32_t ccr:12;
            uint32_t reserved1:2;
            uint32_t duty:1;
            uint32_t fs:1;
            uint32_t reserved2:16;
        } par;
        uint32_t reg;
    } ccr;

    // TRISE
    union {
        struct {
            uint32_t trise:6;
            uint32_t reserved:26;
        } par;
        uint32_t reg;
    } trise;

    // FLTR
    union {
        struct {
            uint32_t dnf:4;
            uint32_t anoff:1;
            uint32_t reserved:27;
        } par;
        uint32_t reg;
    } fltr;
} STM32FXXXI2C_TypeDef;

#endif

/***EOF***/

