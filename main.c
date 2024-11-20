#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "usart.h"
#include "adc.h"

void valor_potenciometro(uint16_t valor, char pot_label) {
    char buffer[10];
    usart_transmit(pot_label);
    usart_transmit(':');
    itoa(valor, buffer, 10);
    usart_transmit_string(buffer);
    usart_transmit('\n');
    usart_transmit_string ("Todos puro 10");
}

int main(void) {
    init_usart(832);      
    ADC_WithInterrupt();   
    sei();                 

    while (1) {

        usart_transmit_string ("Todos puro 10");
        if (usart_received_char == '1') {
            valor_potenciometro(POT, '1');  
        } else if (usart_received_char == '2') {
            valor_potenciometro(POT2, '2'); 
        } else if (usart_received_char != 0) {
            usart_transmit_string("ERROR\n");
        }
        usart_received_char = 0;  
    }

    return 0;
}
