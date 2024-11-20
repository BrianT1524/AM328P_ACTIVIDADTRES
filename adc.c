#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "usart.h"


volatile uint16_t POT = 0;
volatile uint16_t POT2 = 0;
volatile char select = 0;  


// Interrupciones
ISR (ADC_vect)
{

    uint8_t LowPart = ADCL;
    uint16_t TenBitResult = ADCH << 2 | LowPart >> 6;
    

    if (select == 0) {
        POT = TenBitResult;  
    } else {
        POT2 = TenBitResult;  
    }
 
    select ^= 1;  
    // Registro de configuración
    ADMUX = (ADMUX & 0xF0) | select;  
    // Registro de control
    ADCSRA |= 1 << ADSC;
}

void ADC_WithInterrupt(void)
{
    ADCSRA |= (1 << ADEN);   // Enable del ADC
    ADCSRA |= 1 << ADPS2 | 1 << ADPS1 | 1 << ADPS0;  // Prescaler = 128
    ADMUX |= (1 << ADLAR);   /* Justificación a la izquierda (Esto es para los 8 bits 
    mas significativos ADCH bit9-2, ADCL bit1-0)*/
    ADMUX |= (1 << REFS0);   // Voltaje de referencia AVcc (5V)
    ADCSRA |= (1 << ADIE);   // Habilita la interrupción 

    // Selecciona el canal inicial y comienza la primera conversión
    select = 0;
    ADMUX = (ADMUX & 0xF0) | select;
    ADCSRA |= 1 << ADSC; //Esto comienza la conversion
}
