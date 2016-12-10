/*
 * power_control.c
 *
 *  Created on: 30. stu 2016.
 *      Author: Bruno
 */

#include <avr/sleep.h>
#include <avr/power.h>
#include "config.h"
#include "power_control.h"

void power_save(void) {
	set_sleep_mode(POWER_SAVE_MODE);
	sleep_enable();

	power_adc_disable();
	power_spi_disable();
	power_timer0_disable();
	power_timer2_disable();
	power_twi_disable();

	sleep_mode();
	sleep_disable();
}
