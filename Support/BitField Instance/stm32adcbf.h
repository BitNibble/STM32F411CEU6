/******************************************************************************
	STM32 XXX ADCBF
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 28022024
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXADCBF_H_
	#define _STM32FXXXADCBF_H_

#include <inttypes.h>

/*** ADC 1..3 BitField TypeDef ***/
typedef volatile struct {
	// SR
	union {
		struct {
			uint32_t awd:1;
			uint32_t eoc:1;
			uint32_t jeoc:1;
			uint32_t jstrt:1;
			uint32_t strt:1;
			uint32_t ovr:1;
			uint32_t fill:26;
		}par;
		uint32_t reg;
	}sr;
	// CR1
	union {
		struct {
			uint32_t awdch:5;
			uint32_t eocie:1;
			uint32_t awdie:1;
			uint32_t jeocie:1;
			uint32_t scan:1;
			uint32_t awd_sgl:1;
			uint32_t jauto:1;
			uint32_t discen:1;
			uint32_t jdiscen:1;
			uint32_t discnum:3;
			uint32_t reserved1:6;
			uint32_t jawden:1;
			uint32_t awden:1;
			uint32_t res:2;
			uint32_t ovrie:1;
			uint32_t reserved2:5;
		}par;
		uint32_t reg;
	}cr1;
	// CR2
	union {
		struct {
			uint32_t adon:1;
			uint32_t cont:1;
			uint32_t reserved1:6;
			uint32_t dma:1;
			uint32_t dds:1;
			uint32_t eocs:1;
			uint32_t align:1;
			uint32_t reserved2:4;
			uint32_t jextsel:4;
			uint32_t jexten:2;
			uint32_t jswstart:1;
			uint32_t reserved3:1;
			uint32_t extsel:4;
			uint32_t exten:2;
			uint32_t swstart:1;
			uint32_t reserved4:1;
		}par;
		uint32_t reg;
	}cr2;
	// SMPR1
	union {
		struct {
			uint32_t smp10:3;
			uint32_t smp11:3;
			uint32_t smp12:3;
			uint32_t smp13:3;
			uint32_t smp14:3;
			uint32_t smp15:3;
			uint32_t smp16:3;
			uint32_t smp17:3;
			uint32_t smp18:3;
			uint32_t reserved:5;
		}par;
		uint32_t reg;
	}smpr1;
	// SMPR2
	union {
		struct {
			uint32_t smp0:3;
			uint32_t smp1:3;
			uint32_t smp2:3;
			uint32_t smp3:3;
			uint32_t smp4:3;
			uint32_t smp5:3;
			uint32_t smp6:3;
			uint32_t smp7:3;
			uint32_t smp8:3;
			uint32_t smp9:3;
			uint32_t reserved:2;
		}par;
		uint32_t reg;
	}smpr2;
	// JOFR1..4
	union {
		struct {
			uint32_t joffset:12;
			uint32_t reserved:20;
		}par;
		uint32_t reg;
	}jofr1;
	union {
		struct {
			uint32_t joffset:12;
			uint32_t reserved:20;
		}par;
		uint32_t reg;
	}jofr2;
	union {
		struct {
			uint32_t joffset:12;
			uint32_t reserved:20;
		}par;
		uint32_t reg;
	}jofr3;
	union {
		struct {
			uint32_t joffset:12;
			uint32_t reserved:20;
		}par;
		uint32_t reg;
	}jofr4;
	// HTR
	union {
		struct {
			uint32_t ht:12;
			uint32_t reserved:20;
		}par;
		uint32_t reg;
	}htr;
	// LTR
	union {
		struct {
			uint32_t lt:12;
			uint32_t reserved:20;
		}par;
		uint32_t reg;
	}ltr;
	// SQR1
	union {
		struct {
			uint32_t sq13:5;
			uint32_t sq14:5;
			uint32_t sq15:5;
			uint32_t sq16:5;
			uint32_t l:4;
			uint32_t reserved:8;
		}par;
		uint32_t reg;
	}sqr1;
	// SQR2
	union {
		struct {
			uint32_t sq7:5;
			uint32_t sq8:5;
			uint32_t sq9:5;
			uint32_t sq10:5;
			uint32_t sq11:5;
			uint32_t sq12:5;
			uint32_t reserved:2;
		}par;
		uint32_t reg;
	}sqr2;
	// SQR3
	union {
		struct {
			uint32_t sq1:5;
			uint32_t sq2:5;
			uint32_t sq3:5;
			uint32_t sq4:5;
			uint32_t sq5:5;
			uint32_t sq6:5;
			uint32_t reserved:2;
		}par;
		uint32_t reg;
	}sqr3;
	// JSQR
	union {
		struct {
			uint32_t jsq1:5;
			uint32_t jsq2:5;
			uint32_t jsq3:5;
			uint32_t jsq4:5;
			uint32_t jl:2;
			uint32_t reserved:10;
		}par;
		uint32_t reg;
	}jsqr;
	// JDR1..4
	union {
		struct {
			uint16_t jdata;
			uint16_t reserved;
		}par;
		uint32_t reg;
	}jdr1;
	union {
		struct {
			uint16_t jdata;
			uint16_t reserved;
		}par;
		uint32_t reg;
	}jdr2;
	union {
		struct {
			uint16_t jdata;
			uint16_t reserved;
		}par;
		uint32_t reg;
	}jdr3;
	union {
		struct {
			uint16_t jdata;
			uint16_t reserved;
		}par;
		uint32_t reg;
	}jdr4;
	// DR
	union {
		struct {
			uint16_t data;
			uint16_t reserved;
		}par;
		uint32_t reg;
	}dr;
}STM32FXXXADC_TypeDef;

/*** ADC_Common ***/
typedef volatile struct {
	// CSR
	union {
		struct {
			uint32_t awd1:1;
			uint32_t eoc1:1;
			uint32_t jeoc1:1;
			uint32_t jstrt1:1;
			uint32_t strt1:1;
			uint32_t ovr1:1;
			uint32_t reserved1:2;
			uint32_t awd2:1;
			uint32_t eoc2:1;
			uint32_t jeoc2:1;
			uint32_t jstrt2:1;
			uint32_t strt2:1;
			uint32_t ovr2:1;
			uint32_t reserved2:2;
			uint32_t awd3:1;
			uint32_t eoc3:1;
			uint32_t jeoc3:1;
			uint32_t jstrt3:1;
			uint32_t strt3:1;
			uint32_t ovr3:1;
			uint32_t reserved3:10;
		}par;
		struct {
			uint32_t awd1:1;
			uint32_t eoc1:1;
			uint32_t jeoc1:1;
			uint32_t jstrt1:1;
			uint32_t strt1:1;
			uint32_t ovr1:1;
			uint32_t reserved:26;
		}adc1_par;
		struct {
			uint32_t reserved1:8;
			uint32_t awd2:1;
			uint32_t eoc2:1;
			uint32_t jeoc2:1;
			uint32_t jstrt2:1;
			uint32_t strt2:1;
			uint32_t ovr2:1;
			uint32_t reserved2:18;
		}adc2_par;
		struct {
			uint32_t reserved1:16;
			uint32_t awd3:1;
			uint32_t eoc3:1;
			uint32_t jeoc3:1;
			uint32_t jstrt3:1;
			uint32_t strt3:1;
			uint32_t ovr3:1;
			uint32_t reserved2:10;
		}adc3_par;
		uint32_t reg;
	}csr;
	// CCR
	union {
		struct {
			uint16_t reserved1;
			uint16_t adcpre:2;
			uint16_t reserved2:4;
			uint16_t vbate:1;
			uint16_t tsvrefe:1;
			uint16_t reserved3:8;
		}par;
		uint32_t reg;
	}ccr;
	// CDR
	union {
		struct {
			uint16_t data1;
			uint16_t data2;
		}par;
		uint32_t reg;
	}cdr;
}STM32FXXXADC_COMMON_TypeDef;

#endif

/***EOF***/

