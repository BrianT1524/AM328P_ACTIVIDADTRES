
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "usart.h"

volatile char usart_received_char;

// Interrupciones
ISR (USART_RX_vect){
	usart_received_char = UDR0;
}

// Bloqueo de lectura
unsigned char usart_receive(void)
{
  while ((UCSR0A & 0x80) == 0x00); 
  return UDR0;
}

//Transimitir datos
void usart_transmit(unsigned int data)
{
  while ((UCSR0A & 0x20) == 0x00);  
  UDR0 = data; 
}

//Transmitir cadena
void usart_transmit_string(char s[])
{	
	int i = 0;
  while (i < 64){
	  if (s[i] == '\0') break;
	  usart_transmit(s[i++]);
  }
}

//Inicializar el USART
void init_usart(unsigned int baudrate)
{	
	UCSR0C &= (~(1<<UMSEL00) & ~(1<<UMSEL01));
	UCSR0A = (1<<U2X0);	
	UBRR0H = (unsigned char)(baudrate>>8);
	UBRR0L = (unsigned char)(baudrate);	
	UCSR0C = ((1<<UCSZ00) | (1<<UCSZ01));	
	UCSR0B = 1<<RXEN0 | 1<<TXEN0 | 1<<RXCIE0;
}
