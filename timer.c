/*
 * timer.c
 *
 *  Created on: 29. stu 2016.
 *      Author: Bruno
 */

#include <avr/io.h>
#include "config.h"
#include "timer.h"

void timer_init(void) {

	TCCR1B |= (1 << WGM12); // configure timer1 for CTC mode
	TIMSK1 |= (1 << OCIE1A); // enable the CTC interrupt
	OCR1A = TIMER_COUNTER; // set the CTC compare value
	TCCR1B &= ~((1<<CS10)|(1<<CS11));
	TCCR1B |= (1 << CS12); // start the timer at 16MHz/256

}
