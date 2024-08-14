/*
 * Voltmeter.c
 *
 *  Created on: Aug 12, 2024
 *      Author: Ahmed Mostafa
 */



#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>
#include <stdlib.h>

#define ENABLE_PIN            5
#define REGISTER_SELECTION_PIN 6

void send_command(unsigned char command);
void send_character(unsigned char character);
void send_string(char *string_of_characters);

int main(void) {
    DDRB = 0xFF;   // Configure PORTB as output
    DDRA = 0x00;   // Configure PORTA as input (for ADC)
    DDRD = 0xFF;   // Configure PORTD as output
    _delay_ms(50);

    // Initialize ADC
    ADMUX |= (1 << REFS0);  // Reference voltage: AVcc with external capacitor at AREF pin
    ADCSRA |= (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);  // Enable ADC and set prescaler to 128

    float voltage = 0;
    char voltage_display[7];

    // Initialize LCD
    send_command(0x01); // Clear Screen
    _delay_ms(2);
    send_command(0x38); // 8-bit mode, 2-line display
    _delay_ms(2);
    send_command

