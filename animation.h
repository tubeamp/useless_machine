#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <stdint.h>

typedef struct{
	uint16_t frame;
	uint16_t door;
	uint16_t arm;
} frame_t;

void animation_set	( uint8_t i );
void animation_next	( void );

extern frame_t* animation;


#endif // _ANIMATION_H_

