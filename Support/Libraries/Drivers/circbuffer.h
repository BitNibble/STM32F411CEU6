/******************************************************************************
	CIRCBUFFER
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 15062023
Comment:
	Circular Buffer
*******************************************************************************/
#ifndef _CIRCBUFFER_H_
	#define _CIRCBUFFER_H_

/*** Library ***/
#include <inttypes.h>
/*** Define & Macro ***/
#define CIRCBUFF_var char
/*** CIRCBUFFER par TypeDef ***/
typedef struct
{
	CIRCBUFF_var* tail;
	CIRCBUFF_var* head;
	CIRCBUFF_var* orig;
	CIRCBUFF_var* end;
}CIRCBUFFER_par;

/*** CIRCBUFFER TypeDef ***/
struct circ_buf_template
{
	CIRCBUFFER_par par;
	uint8_t (*get)(CIRCBUFFER_par* par);
	void (*put)(CIRCBUFFER_par* par, CIRCBUFF_var data);
	void (*putstr)(CIRCBUFFER_par* par, const CIRCBUFF_var* str);
	void (*getstr)(CIRCBUFFER_par* par, CIRCBUFF_var* str);
};
typedef struct circ_buf_template circbuff;

circbuff CIRCBUFF_enable(uint8_t size_buff, CIRCBUFF_var* buff);

#endif

/***EOF***/

/******
1º Sequence
2º Scope
	- Library Scope
	- File Scope
	- Function Scope
	- Precedence Scope
3º Pointer and Variable
4º Casting
******/

