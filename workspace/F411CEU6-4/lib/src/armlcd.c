/*************************************************************************
	ARMLCD
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32F4
Date:     28052023
Comment:
	STM32F446RE || STM32F411CEU6
************************************************************************/
/*** File Library ***/
#include "armlcd.h"
#include "armsystick.h"
/*** File Constant & Macro ***/
// CMD RS
#define ARMLCD0_INST 0
#define ARMLCD0_DATA 1
/****/
#define ARMLCD0_RS_Msk (1 << ARMLCD0_RS)
#define ARMLCD0_RW_Msk (1 << ARMLCD0_RW)
#define ARMLCD0_EN_Msk (1 << ARMLCD0_EN)
#define ARMLCD0_NC_Msk (1 << ARMLCD0_NC)
#define ARMLCD0_DB4_Msk (1 << ARMLCD0_DB4)
#define ARMLCD0_DB5_Msk (1 << ARMLCD0_DB5)
#define ARMLCD0_DB6_Msk (1 << ARMLCD0_DB6)
#define ARMLCD0_DB7_Msk (1 << ARMLCD0_DB7)
#define MODER_CMD_RESET_Msk ((3 << (ARMLCD0_RS * 2)) | (3 << (ARMLCD0_RW * 2)) | (3 << (ARMLCD0_EN * 2)))
#define MODER_CMD_OUTPUT_Msk ((1 << (ARMLCD0_RS * 2)) | (1 << (ARMLCD0_RW * 2)) | (1 << (ARMLCD0_EN * 2)))
#define MODER_DATA_RESET_Msk ((3 << (ARMLCD0_DB4 * 2)) | (3 << (ARMLCD0_DB5 * 2)) | (3 << (ARMLCD0_DB6 * 2)) | (3 << (ARMLCD0_DB7 * 2)))
#define MODER_DATA_INPUT_Msk ((3 << (ARMLCD0_DB4 * 2)) | (3 << (ARMLCD0_DB5 * 2)) | (3 << (ARMLCD0_DB6 * 2)) | (3 << (ARMLCD0_DB7 * 2)))
#define MODER_DATA_OUTPUT_Msk ((1 << (ARMLCD0_DB4 * 2)) | (1 << (ARMLCD0_DB5 * 2)) | (1 << (ARMLCD0_DB6 * 2)) | (1 << (ARMLCD0_DB7 * 2)))
#define MODER_NC_RESET_Msk (3 << (ARMLCD0_NC * 2))
#define PUPDR_DATA_RESET_Msk ((3 << (ARMLCD0_DB4 * 2)) | (3 << (ARMLCD0_DB5 * 2)) | (3 << (ARMLCD0_DB6 * 2)) | (3 << (ARMLCD0_DB7 * 2)))
#define PUPDR_DATA_PULLUP_Msk ((1 << (ARMLCD0_DB4 * 2)) | (1 << (ARMLCD0_DB5 * 2)) | (1 << (ARMLCD0_DB6 * 2)) | (1 << (ARMLCD0_DB7 * 2)))
#define PUPDR_NC_RESET_Msk (3 << (ARMLCD0_NC * 2))
#define PUPDR_NC_PULLUP_Msk (1 << (ARMLCD0_NC * 2))
#define OSPEEDR_PINS_RESET_Msk ((3 << (ARMLCD0_RS * 2)) | (3 << (ARMLCD0_RW * 2)) | (3 << (ARMLCD0_EN * 2)) | (3 << (ARMLCD0_DB4 * 2)) | (3 << (ARMLCD0_DB5 * 2)) | (3 << (ARMLCD0_DB6 * 2)) | (3 << (ARMLCD0_DB7 * 2)))
#define OSPEEDR_PINS_25MHZ_Msk ((1 << (ARMLCD0_RS * 2)) | (1 << (ARMLCD0_RW * 2)) | (1 << (ARMLCD0_EN * 2)) | (1 << (ARMLCD0_DB4 * 2)) | (1 << (ARMLCD0_DB5 * 2)) | (1 << (ARMLCD0_DB6 * 2)) | (1 << (ARMLCD0_DB7 * 2)))

/*** File Variable ***/
static ARMLCD0 setup_armlcd0;
static GPIO_TypeDef* ireg;
static uint32_t armlcd0_detect;

/*** File Header ***/
void ARMLCD0_inic(void);
void ARMLCD0_write(char c, unsigned short D_I);
char ARMLCD0_read(unsigned short D_I);
void ARMLCD0_BF(void);
void ARMLCD0_putch(char c);
char ARMLCD0_getch(void);
void ARMLCD0_string(const char* s); // RAW
void ARMLCD0_string_size(const char* s, uint32_t size); // RAW
void ARMLCD0_hspace(uint32_t n);
void ARMLCD0_clear(void);
void ARMLCD0_gotoxy(unsigned int y, unsigned int x);
void ARMLCD0_reboot(void);
void ARMLCD0_delayMiliseconds(unsigned int ms);
void ARMLCD0_delayMicroseconds(unsigned int us);

/*** LCD0 Procedure & Function Definition ***/
ARMLCD0 ARMLCD0_enable(GPIO_TypeDef* reg)
{
	ireg = reg;
	delay_Configure();

	if(reg == (GPIO_TypeDef*)GPIOA_BASE) RCC->AHB1ENR |= (1 << 0);
	if(reg == (GPIO_TypeDef*)GPIOB_BASE) RCC->AHB1ENR |= (1 << 1);
	if(reg == (GPIO_TypeDef*)GPIOC_BASE) RCC->AHB1ENR |= (1 << 2);
	if(reg == (GPIO_TypeDef*)GPIOD_BASE) RCC->AHB1ENR |= (1 << 3);
	if(reg == (GPIO_TypeDef*)GPIOE_BASE) RCC->AHB1ENR |= (1 << 4);
	#ifdef STM32F446xx
		if(reg == (GPIO_TypeDef*)GPIOF_BASE) RCC->AHB1ENR |= (1 << 5);
		if(reg == (GPIO_TypeDef*)GPIOG_BASE) RCC->AHB1ENR |= (1 << 6);
	#endif
	if(reg == (GPIO_TypeDef*)GPIOH_BASE) RCC->AHB1ENR |= (1 << 7);

	setup_armlcd0.write = ARMLCD0_write;
	setup_armlcd0.read = ARMLCD0_read;
	setup_armlcd0.BF = ARMLCD0_BF;
	setup_armlcd0.putch = ARMLCD0_putch;
	setup_armlcd0.getch = ARMLCD0_getch;
	setup_armlcd0.string = ARMLCD0_string; // RAW
	setup_armlcd0.string_size = ARMLCD0_string_size; // RAW
	setup_armlcd0.hspace = ARMLCD0_hspace;
	setup_armlcd0.clear = ARMLCD0_clear;
	setup_armlcd0.gotoxy = ARMLCD0_gotoxy;
	setup_armlcd0.reboot = ARMLCD0_reboot;

	ARMLCD0_inic();
	
	return setup_armlcd0;
}

ARMLCD0* lcd0(void){ return (ARMLCD0*) &setup_armlcd0; }

void ARMLCD0_inic(void)
{
	// uint8_t repeat;
	// LCD INIC
	ireg->MODER &= (uint32_t) ~MODER_CMD_RESET_Msk;
	ireg->MODER |= MODER_CMD_OUTPUT_Msk; // control pins as output
	
	ireg->PUPDR &= (uint32_t) ~PUPDR_DATA_RESET_Msk;
	ireg->PUPDR |= PUPDR_DATA_PULLUP_Msk; // enable pull up resistors

	ireg->MODER &= (uint32_t) ~MODER_NC_RESET_Msk;
	ireg->PUPDR &= (uint32_t) ~PUPDR_NC_RESET_Msk;
	ireg->PUPDR |= PUPDR_NC_PULLUP_Msk; // pull up resistors

	ireg->OSPEEDR &= (uint32_t) ~OSPEEDR_PINS_RESET_Msk;
	ireg->OSPEEDR |= OSPEEDR_PINS_25MHZ_Msk; // set speed
	 
	armlcd0_detect = ireg->IDR & ARMLCD0_NC_Msk;
	
	// INICIALIZACAO LCD datasheet
	ARMLCD0_delayMiliseconds(20); // using clock at 16Mhz
	ARMLCD0_write(0x30, ARMLCD0_INST); // 0x30 function set
	ARMLCD0_delayMicroseconds(37);
	ARMLCD0_write(0x28, ARMLCD0_INST); // 0x28 function set
	ARMLCD0_delayMicroseconds(37);
	ARMLCD0_write(0x28, ARMLCD0_INST); // 0x28 function set
	ARMLCD0_delayMicroseconds(37);
	ARMLCD0_write(0x0C, ARMLCD0_INST); // 0x0C Display ON/OFF control
	ARMLCD0_delayMicroseconds(37);
	ARMLCD0_write(0x01, ARMLCD0_INST); // 0x01 Display clear
	ARMLCD0_delayMiliseconds(1.5);
	ARMLCD0_write(0x04, ARMLCD0_INST); // 0x05 Entry mode set
	ARMLCD0_BF();

	ARMLCD0_clear();
	ARMLCD0_gotoxy(0,0);
}

void ARMLCD0_write(char c, unsigned short D_I)
{ // write to LCD
	clear_hpins(ireg, ARMLCD0_RW_Msk); // lcd as input
	clear_reg(&ireg->MODER, MODER_DATA_RESET_Msk);
	set_reg(&ireg->MODER, MODER_DATA_OUTPUT_Msk); // mcu as output
	
	if(D_I) set_hpins(ireg, ARMLCD0_RS_Msk); else clear_hpins(ireg, ARMLCD0_RS_Msk);
	

	if(c & 0x80) set_hpins(ireg, ARMLCD0_DB7_Msk); else clear_hpins(ireg, ARMLCD0_DB7_Msk);
	if(c & 0x40) set_hpins(ireg, ARMLCD0_DB6_Msk); else clear_hpins(ireg, ARMLCD0_DB6_Msk);
	if(c & 0x20) set_hpins(ireg, ARMLCD0_DB5_Msk); else clear_hpins(ireg, ARMLCD0_DB5_Msk);
	if(c & 0x10) set_hpins(ireg, ARMLCD0_DB4_Msk); else clear_hpins(ireg, ARMLCD0_DB4_Msk);
	set_hpins(ireg, ARMLCD0_EN_Msk);
	clear_hpins(ireg, ARMLCD0_EN_Msk);
	
	if(D_I) set_hpins(ireg, ARMLCD0_RS_Msk); else clear_hpins(ireg, ARMLCD0_RS_Msk);
	

	if(c & 0x08) set_hpins(ireg, ARMLCD0_DB7_Msk); else clear_hpins(ireg, ARMLCD0_DB7_Msk);
	if(c & 0x04) set_hpins(ireg, ARMLCD0_DB6_Msk); else clear_hpins(ireg, ARMLCD0_DB6_Msk);
	if(c & 0x02) set_hpins(ireg, ARMLCD0_DB5_Msk); else clear_hpins(ireg, ARMLCD0_DB5_Msk);
	if(c & 0x01) set_hpins(ireg, ARMLCD0_DB4_Msk); else clear_hpins(ireg, ARMLCD0_DB4_Msk);
	set_hpins(ireg, ARMLCD0_EN_Msk);
	clear_hpins(ireg, ARMLCD0_EN_Msk);
}

char ARMLCD0_read(unsigned short D_I)
{ // Read from LCD
	uint32_t data = 0; uint8_t c = 0;
	clear_reg(&ireg->MODER, MODER_DATA_INPUT_Msk); // mcu as input
	set_hpins(ireg, ARMLCD0_RW_Msk); // lcd as output
	
	if(D_I) set_hpins(ireg, ARMLCD0_RS_Msk); else clear_hpins(ireg, ARMLCD0_RS_Msk);
	
	set_hpins(ireg, ARMLCD0_EN_Msk);
	data = ireg->IDR; // read data
	clear_hpins(ireg, ARMLCD0_EN_Msk);
	
	if(data & (ARMLCD0_DB7_Msk)) c |= 1 << 7; else c &= ~(1 << 7);
	if(data & (ARMLCD0_DB6_Msk)) c |= 1 << 6; else c &= ~(1 << 6);
	if(data & (ARMLCD0_DB5_Msk)) c |= 1 << 5; else c &= ~(1 << 5);
	if(data & (ARMLCD0_DB4_Msk)) c |= 1 << 4; else c &= ~(1 << 4);
	
	if(D_I) set_hpins(ireg, ARMLCD0_RS_Msk); else clear_hpins(ireg, ARMLCD0_RS_Msk);
	
	set_hpins(ireg, ARMLCD0_EN_Msk);
	data = ireg->IDR; // read data
	clear_hpins(ireg, ARMLCD0_EN_Msk);

	if(data & ( ARMLCD0_DB7_Msk)) c |= 1 << 3; else c &= ~(1 << 3);
	if(data & ( ARMLCD0_DB6_Msk)) c |= 1 << 2; else c &= ~(1 << 2);
	if(data & ( ARMLCD0_DB5_Msk)) c |= 1 << 1; else c &= ~(1 << 1);
	if(data & ( ARMLCD0_DB4_Msk)) c |= 1 << 0; else c &= ~(1 << 0);

	return c;
}

void ARMLCD0_BF(void)
//	It has to read at minimum one equal and exit
//	immediately if not equal, weird property.
{
	uint8_t i;
	char inst = 0x80;
	for(i=0; 0x80 & inst; i++){
		inst = ARMLCD0_read(ARMLCD0_INST);
		if(i > 2) // 1
			break;
	}
}

char ARMLCD0_getch(void)
{
	char c;
	c = ARMLCD0_read(ARMLCD0_DATA);
	ARMLCD0_BF();
	return c;
}

void ARMLCD0_putch(char c)
{
	ARMLCD0_write(c, ARMLCD0_DATA);
	ARMLCD0_BF();
}

void ARMLCD0_string(const char* s)
{
	char tmp;
	while(*s){
		tmp = *(s++);
		ARMLCD0_putch(tmp);
	}
}

void ARMLCD0_string_size(const char* s, uint32_t size)
{
	char tmp;
	uint32_t pos = 0;
	while(*s){
		tmp=*(s++);
		pos++;
		if(pos > size) // 1 TO SIZE+1
			break;
		ARMLCD0_putch(tmp);
	}
	while(pos < size){ // TO SIZE
		ARMLCD0_putch(' ');
		pos++;
	}
}

void ARMLCD0_hspace(uint32_t n)
{
	for(; n; n--){
		ARMLCD0_putch(' ');
	}
}

void ARMLCD0_clear(void)
{
	ARMLCD0_write(0x01, ARMLCD0_INST);
	ARMLCD0_delayMicroseconds(2000);
}

void ARMLCD0_gotoxy(unsigned int y, unsigned int x)
{
	switch(y){
		case 0:
			ARMLCD0_write((char)(0x80 + x), ARMLCD0_INST);
			ARMLCD0_BF();
		break;
		case 1:
			ARMLCD0_write((char)(0xC0 + x), ARMLCD0_INST);
			ARMLCD0_BF();
		break;
		case 2:
			ARMLCD0_write((char)(0x94 + x), ARMLCD0_INST); // 0x94
			ARMLCD0_BF();
		break;
		case 3:
			ARMLCD0_write((char)(0xD4 + x), ARMLCD0_INST); // 0xD4
			ARMLCD0_BF();
		break;
		default:
		break;
	}
}

void ARMLCD0_reboot(void)
{
	// low high detect pin NC
	uint32_t i;
	uint32_t tmp;
	tmp = ireg->IDR & ARMLCD0_NC_Msk;
	i = tmp ^ armlcd0_detect;
	i &= tmp;
	if(i)
		ARMLCD0_inic();
	armlcd0_detect = tmp;
}

void ARMLCD0_delayMiliseconds(unsigned int ms) {
    volatile unsigned int count = ms * get_systick_ms( );
    while (count--);
}

void ARMLCD0_delayMicroseconds(unsigned int us) {
    volatile unsigned int count = us * get_systick_us( );
    while (count--);
}

/******************************************************************************
void ARMLCD0_BF(void)
//	It has to read at minimum one equal and exit
//	immediately if not equal, weird property.
{
	for( ; 0x80 & ARMLCD0_read(ARMLCD0_INST) ; );
}

void ARMLCD0_BF(void)
//	It has to read at minimum one equal and exit
//	immediately if not equal, weird property.
{
	uint8_t i;
	char inst = 0x80;
	for(i=0; 0x80 & inst; i++){
		inst = ARMLCD0_read(ARMLCD0_INST);
		if(i > 3)
			break;
	}
}
*******************************************************************************/

/***EOF***/

