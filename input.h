/*------------------------------------------------------------

------------------------------------------------------------*/

#ifndef INPUT_H
#define INPUT_H

#define MAX_INPUTS 		1



typedef struct {
	unsigned	char state		:1;
	unsigned	char prev_state :1;
	unsigned	char push		:1;
	unsigned	char pop		:1;

				char pin;
				char mask;
} INPUT;

INPUT inputs[ MAX_INPUTS ];

void inputs_check ( void );




#endif
