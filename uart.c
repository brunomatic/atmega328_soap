/*
 * usart.c
 *
 *  Created on: 29. stu 2016.
 *      Author: Bruno
 */

#include <avr/io.h>
#include <stdlib.h>
#include "config.h"
#include "uart.h"

void uart_init(uint8_t ubrr) {

	UBRR0H = (uint8_t) (ubrr >> 8);
	UBRR0L = (uint8_t) ubrr;

	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	UCSR0C = (0 << USBS0) | (3 << UCSZ00);
}

void uart_sendbyte(uint8_t data) {

	while (!(UCSR0A & (1 << UDRE0)));

	UDR0 = data;
}

void uart_send(uint8_t data[]) {

	uint16_t i = 0;
	while (!(0x00 == data[i])) {
		uart_sendbyte(data[i]);
		i++;
	}
}

void uart_send_u8(uint8_t before[], uint8_t number, uint8_t after[]){
	uint8_t temp[4];
	utoa(number, (char *)temp, 10);
	uart_send(before);
	uart_send(temp);
	uart_send(after);
}

void uart_send_u16(uint8_t before[], uint16_t number, uint8_t after[]){
	uint8_t temp[6];
	itoa(number, (char *)temp, 10);
	uart_send(before);
	uart_send(temp);
	uart_send(after);
}

void uart_send_u32(uint8_t before[], uint32_t number, uint8_t after[]){
	uint8_t temp[11];
	itoa(number, (char *)temp, 10);
	uart_send(before);
	uart_send(temp);
	uart_send(after);
}

