#include "animation.h"
#include "shared.h"

#define MAX_ANIMATIONS 4

frame_t* animation;
uint8_t animation_index = 0;

frame_t animation0[] =
{
	{ 0, 	DOOR_MIN,	ARM_MIN },
	{ 1,	DOOR_MIN,	ARM_MAX }
};

frame_t animation1[] =
{
	{ 0, 	DOOR_MIN,	ARM_MIN },
	{ 50,	DOOR_MIN,	ARM_MAX }
};

frame_t animation2[] =
{
	{ 0, 	DOOR_MIN,	ARM_MIN },
	{ 50,	DOOR_MIN,	ARM_MAX-200 },
	{ 100,	DOOR_MIN, 	ARM_MIN	},
	{ 120,	DOOR_MAX, 	ARM_MIN	},
	{ 150,	DOOR_MIN, 	ARM_MIN	},
	{ 180,	DOOR_MIN,	ARM_MAX	}
};

frame_t animation3[] =
{
	{ 0, 	DOOR_MIN,	ARM_MIN },
	{ 50,	DOOR_MIN,	ARM_MAX-200 },
	{ 70,	DOOR_MIN, 	ARM_MAX-400	},
	{ 90,	DOOR_MIN, 	ARM_MAX-200	},
	{ 110,	DOOR_MIN, 	ARM_MAX-400	},
	{ 150,	DOOR_MIN,	ARM_MAX	}
};

// all animations
frame_t* animations[] =
{
	animation0,
	animation1,
	animation2,
	animation3
};

/*------------------------------------------------------------
	set animation
------------------------------------------------------------*/
void animation_set	( uint8_t i )
{
	animation_index = i;
	animation = animations[ animation_index ];
}

/*------------------------------------------------------------
	next animation
------------------------------------------------------------*/
void animation_next	( void )
{
	animation_index++;
	if( animation_index > MAX_ANIMATIONS-1 ) animation_index = 0;
	animation = animations[ animation_index ];
}
