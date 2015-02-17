/*
 */

#include <avr/io.h>
#include <util/atomic.h>
#include <util/delay.h>
#include "animation.h"
#include "input.h"
#include "util.h"
#include "shared.h"


#define STATE_PARKING 1


// calculating timer top by timer overflow freqency
#define TICK_FREQ 50						// 50 Hz

#define TIMER_TOP ((F_CPU/TICK_FREQ)-1)
#if TIMER_TOP < SERVO_MAX					// Check servo range
#warning Timer top is too small
#endif



volatile uint8_t f_tick = 0;				// timer overflow flag


uint8_t state = 0;
uint16_t frame = 0;


void set_arm_pwm( uint16_t value );
void set_door_pwm( uint16_t value );


/*------------------------------------------------------------
	main
------------------------------------------------------------*/
int main(void)
{

	cli();

	// --- init pins ---
	// button pin
	CLR_BIT( DDRD, 4 );
	SET_BIT( PORTD, 4 );

	// arm pwm pin
	SET_BIT( DDRB, 3 );		// OC1A pin
	CLR_BIT( PORTB, 3 );

	// door pwm pin
	SET_BIT( DDRB, 4 );		// OC1B pin
	CLR_BIT( PORTB, 4 );

	// --- init pwm ---
	// timer0 setup
	TCCR1A =	_BV( COM1A1 ) | _BV( COM1B1 ) |
				_BV( WGM11 );

    TCCR1B =	_BV( WGM13 ) | _BV( WGM12 ) |	// fast pwm, top icr1
				_BV( CS10 );					// f_cpu

	TIMSK = _BV(TOIE1);							// timer ovf interrupt enable

	ICR1 = TIMER_TOP;							// pwm top

	set_arm_pwm( ARM_MIN );

    sei();

    uint16_t pos_arm = ARM_MIN;

    animation_set(0);

    uint8_t keyframe_index = 0;


    while(1)
	{

		if( !f_tick ) continue;
		f_tick = 0;

		inputs_check();

		// switch turned off
		if( inputs[0].push )
		{
			//set_arm_pwm( ARM_MIN );
			//pos = ARM_MIN;

			//set_door_pwm( DOOR_MIN );

			frame = 0;
			keyframe_index = 0;
			animation_next();

			state = STATE_PARKING;
			pos_arm = ARM_MAX;
		};

		if( state == STATE_PARKING )
		{
			pos_arm -= 50;
			if( pos_arm < ARM_MIN )
			{
				pos_arm = ARM_MIN;
				state = 0;
				set_door_pwm( DOOR_MIN );
			}
			set_arm_pwm( pos_arm );
		}


		// switch armed
		if( !inputs[0].state )
		{
			if( frame == animation[ keyframe_index ].frame  )
			{
				set_arm_pwm( animation[ keyframe_index ].arm );
				set_door_pwm( animation[ keyframe_index ].door );
				keyframe_index++;
			}
			frame++;


		}


	};


    return 0;
}

/*------------------------------------------------------------
	set arm position
------------------------------------------------------------*/
void set_arm_pwm( uint16_t value )
{
	ATOMIC_BLOCK( ATOMIC_RESTORESTATE )
	{
		OCR1AH = HI( value );
		OCR1AL = LO( value );
	}
}

/*------------------------------------------------------------
	set door postition
------------------------------------------------------------*/
void set_door_pwm( uint16_t value )
{
	ATOMIC_BLOCK( ATOMIC_RESTORESTATE )
	{
		OCR1BH = HI( value );
		OCR1BL = LO( value );
	}
}


/*------------------------------------------------------------
	timer 1 overflow interrupt
------------------------------------------------------------*/
ISR( TIMER1_OVF_vect )
{
    //
    f_tick = 1;
}
