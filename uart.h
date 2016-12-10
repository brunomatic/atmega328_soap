/*
 * usart.h
 *
 *  Created on: 29. stu 2016.
 *      Author: Bruno
 */

#ifndef UART_H_
#define UART_H_

void uart_init(uint8_t ubrr);
void uart_send(uint8_t data[]);
void uart_send_integer(uint8_t number);
void uart_sendbyte(uint8_t data);
void uart_send_u8(uint8_t before[], uint8_t number, uint8_t after[]);
void uart_send_u16(uint8_t before[], uint16_t number, uint8_t after[]);
void uart_send_u32(uint8_t before[], uint32_t number, uint8_t after[]);

#endif /* UART_H_ */
