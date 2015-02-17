#include <avr/io.h>
#include "input.h"
#include "util.h"



/*------------------------------------------------------------
	checking inputs
------------------------------------------------------------*/
void inputs_check( void )
{
	for ( int i = 0; i < MAX_INPUTS; i++ )
	{
		// reading port
		uint8_t in = PIND;


		// saving previous state
		inputs[i].prev_state = inputs[i].state;

		// state
		inputs[i].state = !CHK_BIT( in, 4 );//!( in & inputs[i].mask );	// 0 - pressed, 1 - released

		// push
		if ( ( inputs[i].prev_state == 0 ) && ( inputs[i].state == 1 ) )
			inputs[i].push = 1;
		else
			inputs[i].push = 0;

		// pop
		if ( ( inputs[i].prev_state == 1 ) && ( inputs[i].state == 0 ) )
			inputs[i].pop = 1;
		else
			inputs[i].pop = 0;
	}


}
