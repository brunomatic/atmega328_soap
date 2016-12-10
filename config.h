#ifndef CONFIG_H
#define CONFIG_H

/**
 * General settings
 */
#define DEBUG 1								// debug levels 4-highest(+EEPROM dumping) 0-no debug info
#define CLEAR_EEPROM 0						// 1 - writes serial number and erases EEPROM on startup, 0 - EEPROM intacted
#define FREQUENCY	16000000L				// MCU frequency in Hz

/**
 *  Pin layout definition
 */
#define IR_EMITTER	PB3
#define IR_DETECTOR	PB2
#define INFO_LED	PB5
#define PUMP		PB0

/**
 * UART settings
 */
#define BAUD	57600						// Baudrate for UART - tested: 9600 - 57600
#define UBRR_CONST FREQUENCY/16/BAUD-1		// UART baudrate generator constant


/**
 * EEPROM settings
 */
#define EEPROM_SIZE	512						// Size of MCU EEPROM in bytes
#define EEPROM_OFFSET 4						// Initial offset of EEPROM, if specified 0-EEPROM_OFFSET is not used by MCU EEPROM control
#define SN		0x00000001					// Serial number of device
#define PARAMETERS_EEPROM	2				// Number of parameters periodically stored to EEPROM by EEPROM control
#define STORE_EEPROM_CYCLES	3000			// Storing period ( each cycle 100ms) default: 3000(five minutes),max: 2^16


/**
 * IR gate settings
 */
#define IR_GATE_DELAY 8						// Delay between activating IR emitter and reading receiver in us

#define SAMPLE_INTERVAL 100000				// Sample interval in us
#define PUMP_CYCLES 30						// Pump active intervals
#define PUMP_WAIT_CYCLES 300				// Pump reactivation wait time( between activations )

/**
 *  Timer settings
 */
#define TIMER_PRESCALER 256
#define TIMER_COUNTER ((SAMPLE_INTERVAL)/(1000000/(FREQUENCY/TIMER_PRESCALER)))


/**
 * Battery settings
 */
#define MIN_VOLTAGE	1750					// Minimal operating voltage in mV
#define LOW_BATTERY_VOLTAGE 2000			// Low battery warning - info led blinks if voltage below this
#define BATTERY_CHECK_CYCLES 300//6000			// Battery check period - default: 6000(ten minutes), max:2^16


/**
 * Power save system settings
 */
#define POWER_SAVE_MODE	SLEEP_MODE_IDLE		// MCU power save mode between wake ups

#endif
