#ifndef USART_H
#define USART_H

#include <avr/io.h>

extern volatile char usart_received_char;

void init_usart(unsigned int baudrate);
void usart_transmit(unsigned int data);
void usart_transmit_string(char s[]);
unsigned char usart_receive(void);
#endif
