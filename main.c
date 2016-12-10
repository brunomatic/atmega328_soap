/*
 * main.c
 *
 *  Created on: 25. stu 2016.
 *      Author: Bruno
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "config.h"
#include "ir_gate.h"
#include "timer.h"
#include "tests.h"
#include "power_control.h"
#include "uart.h"
#include "battery.h"
#include "eeprom_control.h"

volatile uint16_t pump_cycles;
volatile uint16_t pump_wait_cycles;
volatile uint16_t eeprom_store_cycles;
volatile uint16_t battery_check_cycles;
uint16_t battery;
volatile uint8_t battery_low;

uint32_t data[PARAMETERS_EEPROM];

enum states {
	IDLE, PUMP_ACTIVE
};

enum states state;

ISR(TIMER1_COMPA_vect) {

	/**
	 * State machine for pump and info led control
	 */
	switch (state) {
	case IDLE:
		if (0 == pump_wait_cycles) {
			if (ir_gate_detect()) {
#if DEBUG > 0
				uart_send((uint8_t *) "Starting pump\r\n");
#endif
				PORTB |= (1 << INFO_LED) | (1 << PUMP);
				pump_cycles = PUMP_CYCLES;
				state = PUMP_ACTIVE;
			}
		} else {
			pump_wait_cycles--;
		}
		break;
	case PUMP_ACTIVE:
		if (0 == pump_cycles) {
#if DEBUG > 0
			uart_send((uint8_t *) "Stopping pump\r\n");
#endif
			PORTB &= ~((1 << INFO_LED) | (1 << PUMP));
			pump_wait_cycles = PUMP_WAIT_CYCLES;
			state = IDLE;
		} else {
			pump_cycles--;
			if (battery_low) {
				PORTB ^= (1 << INFO_LED);
			} else {
				PORTB |= (1 << INFO_LED);
			}
		}
		break;
	}


	/**
	 *  EEPROM store
	 */
	if (0 == eeprom_store_cycles) {
		write_to_eeprom(data);
#if DEBUG > 0
		uart_send((uint8_t *) "Storing data to EEPROM\r\n");
#endif
		eeprom_store_cycles = STORE_EEPROM_CYCLES;
	} else {
		eeprom_store_cycles--;
	}


	/**
	 *  Battery check
	 */
	if (0 == battery_check_cycles) {
		battery = readVcc();
		if (battery < LOW_BATTERY_VOLTAGE) {
			battery_low = 1;
		} else {
			battery_low = 0;
		}
#if DEBUG > 0
		uart_send_u16((uint8_t *) "Battery voltage: ", battery,
				(uint8_t *) " mV\r\n");
#endif
		battery_check_cycles = BATTERY_CHECK_CYCLES;
	} else {
		battery_check_cycles--;
	}

}

int main(void) {

	uint8_t test_output = 0;

	DDRB |= (1 << INFO_LED) | (1 << IR_EMITTER) | (1 << PUMP);

	DDRB &= ~(1 << IR_DETECTOR);

	uart_init(UBRR_CONST);

	init_eeprom_control();

#if DEBUG > 3
	dump_eeprom();
#endif

#if CLEAR_EEPROM
	init_eeprom();
#endif

	test_output = system_self_test();

	if (1 != test_output) {
		uart_send_u8((uint8_t *) "System self-test: FAIL, error: ", test_output,(uint8_t *)"\r\n");
		return 0;
	} else {
		uart_send((uint8_t *) "System self-test: OKAY\r\n");
	}

	data[0] = read_serial_eeprom();
	uart_send_u32((uint8_t *) "Serial number: ", data[0], (uint8_t *) " \r\n");

	data[0] = read_from_eeprom(0);
	uart_send_u32((uint8_t *) "Use count: ", data[0], (uint8_t *) " \r\n");

	data[1] = read_from_eeprom(1);
	uart_send_u32((uint8_t *) "On count: ", data[1], (uint8_t *) " \r\n");

	state = IDLE;
	pump_cycles = 0;
	pump_wait_cycles = 0;
	eeprom_store_cycles = 0;
	battery_check_cycles = 0;
	data[1]++;

	sei();

	timer_init();

	while (1) {
		power_save();
	}

	return 0;
}
