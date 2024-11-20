#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

// Variables globales para almacenar los resultados de los potenciómetros
extern volatile uint16_t POT;     // Valor del primer potenciómetro
extern volatile uint16_t POT2;    // Valor del segundo potenciómetro

// Función para inicializar el ADC con interrupciones
void ADC_WithInterrupt(void);

#endif
