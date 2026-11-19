/******************************************************************************
	CIRCBUFFER
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 15062023
Comment:
    Circular Buffer
******************************************************************************/
/*** File Library***/
#include "circbuffer.h"

/*** File Header ***/
uint8_t CIRC_get(CIRCBUFFER_par* par);
void CIRC_put(CIRCBUFFER_par* par, CIRCBUFF_var data);
void CIRC_putstr(CIRCBUFFER_par* par, const CIRCBUFF_var* str);
void CIRC_getstr(CIRCBUFFER_par* par, CIRCBUFF_var* str);
CIRCBUFFER_par circ_par_inic( uint8_t size_buff, CIRCBUFF_var* buff );

/*** CIRCBUFF Auxiliar ***/
CIRCBUFFER_par circ_par_inic( uint8_t size_buff, CIRCBUFF_var* buff )
{
	CIRCBUFFER_par circ_par;
	// inic VAR
	circ_par.tail = buff;
	circ_par.head = buff;
	circ_par.orig = buff;
	circ_par.end = buff + size_buff; // generic
	return circ_par;
}
/*** CIRCBUFF Procedure & Function Definition ***/
circbuff CIRCBUFF_enable( uint8_t size_buff, CIRCBUFF_var* buff )
{
	// OBJECT STRUCT
	struct circ_buf_template circ;
	// inic VAR
	circ.par = circ_par_inic( size_buff, buff );
	// function pointers
	circ.get = CIRC_get;
	circ.put = CIRC_put;
	circ.putstr = CIRC_putstr;
	circ.getstr = CIRC_getstr;
	return circ; // return copy
}

uint8_t CIRC_get( CIRCBUFFER_par* par ){
	CIRCBUFF_var* next;

	if( par->tail != par->end ){
		next = par->tail + 1;
	}else{
		next = par->orig;
	}

	if( par->tail != par->head ){
		par->tail = next;
	}else{
		*par->tail = 0;
	}

	return *par->tail;
}

void CIRC_put( CIRCBUFFER_par* par, CIRCBUFF_var data ){
	CIRCBUFF_var* next;

	if( par->head != par->end ){
		next = par->head + 1;
	}else{
		next = par->orig;
	}
	
	if( next != par->tail ){
		*next = data;
		par->head = next;
	}else{
		*next = 0;
	}
}

void CIRC_putstr( CIRCBUFFER_par* par, const CIRCBUFF_var* str ){
	uint8_t i;
	for( i = 0; *(str + i) ; CIRC_put(par, *(str + i)), i++ );

}

void CIRC_getstr( CIRCBUFFER_par* par, CIRCBUFF_var* str ){
	uint8_t i;
	for(i = 0; par->tail != par->head  ; *(str + i) = CIRC_get(par), i++, *(str + i) = '\0');
}

/***EOF***/

