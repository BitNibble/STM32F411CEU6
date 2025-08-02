/********************************************************************
	EXPLODE
Author:   <sergio.salazar.santos@gmail.com>
License:  Free beer
Hardware: all
Date:     16032021
Comment:
	Pin Analysis
	Tested Atemga128 16Mhz and Atmega328 8Mhz and STM32F446RE
********************************************************************/
#include "explode.h"

void EXPLODE_update(explode_par* par, IO_var x);
IO_var EXPLODEhh(explode_par* par);
IO_var EXPLODEll(explode_par* par);
IO_var EXPLODElh(explode_par* par);
IO_var EXPLODEhl(explode_par* par);
explode_par setup_explode_par(void);

/*** EXPLODE Procedure & Function Definition ***/
EXPLODE EXPLODE_enable( void )
{
	EXPLODE setup = {
		.par = setup_explode_par(),
		.update = EXPLODE_update
	};
	return setup;
}
/*** Auxilar ***/
explode_par setup_explode_par(void)
{
	explode_par setup = {
		.XI = 0,
		.XF = 0,
		.HH = 0,
		.LL = 0,
		.LH = 0,
		.HL = 0
	};
	return setup;
}
// boot
void EXPLODE_update(explode_par* par, IO_var x)
{
	par->XI = par->XF;
	par->XF = x;
	par->HH = EXPLODEhh(par);
	par->LL = EXPLODEll(par);
	par->LH = EXPLODElh(par);
	par->HL = EXPLODEhl(par);
}
// hh
IO_var EXPLODEhh(explode_par* par)
{
	return (par->XI & par->XF);
}
// ll
IO_var EXPLODEll(explode_par* par)
{
	return ~(par->XI | par->XF);
}
// lh
IO_var EXPLODElh(explode_par* par)
{
	return ((par->XI ^ par->XF) & par->XF);
}
// hl
IO_var EXPLODEhl(explode_par* par)
{
	return ((par->XF ^ par->XI) & par->XI);
}
/***EOF***/

