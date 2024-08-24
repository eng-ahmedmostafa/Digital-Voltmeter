/*
 * Voltmeter.c
 *
 *  Created on: Aug 12, 2024
 *      Author: Ahmed Mostafa
 */



#i#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define F_CPU 1000000UL

#define ENABLE_PIN            5U
#define REGISTER_SELECT_PIN   6U

/* Function Prototypes */
static void send_command(uint8_t command);
static void send_character(uint8_t character);
static void send_string(const char *string_of_characters);

int main(void)
{
    /* Configure data direction registers */
    DDRB = 0xFFU;  /* Set PORTB as output */
    DDRA = 0x00U;  /* Set PORTA as input */
    DDRD = 0xFFU;  /* Set PORTD as output */

    /* Initial delay to stabilize the system */
    _delay_ms(50);

    /* ADC Configuration */
    ADMUX = (1U << REFS0);  /* Set reference voltage to AVCC */
    ADCSRA = (1U << ADEN) | (1U << ADATE) | (1U << ADPS0) | (1U << ADPS1) | (1U << ADPS2);

    /* Variable Declarations */
    float voltage = 0.0F;
    char voltageshow[7];

    /* LCD Initialization */
    send_command(0x01U); /* Clear Screen */
    _delay_ms(50);
    send_command(0x38U); /* 8-bit mode, 2-line display */
    _delay_ms(50);
    send_command(0x0FU); /* Display on, cursor on */
    _delay_ms(50);

    ADCSRA |= (1U << ADSC); /* Start ADC Conversion */

    while(1)
    {
        /* Calculate the voltage */
        voltage = (static_cast<float>(ADC) / 204.8F) * 18.0F;

        /* Display messages on the LCD */
        send_string("CIRCUIT DIGEST  ");
        send_command(0xC0U); /* Move cursor to second line */
        send_string("VOLTAGE=");
        send_command(0xC8U); /* Move cursor to position 8 on the second line */

        /* Convert float to string and display */
        (void)dtostrf(voltage, 5, 2, voltageshow);
        send_string(voltageshow);
        send_string("V   ");

        /* Reset the cursor to the beginning */
        send_command(0x80U);
    }

    return 0;
}

/* Function to send a command to the LCD */
static void send_command(uint8_t command)
{
    PORTB = command;
    PORTD &= ~(1U << REGISTER_SELECT_PIN);
    PORTD |= (1U << ENABLE_PIN);
    _delay_ms(2);
    PORTD &= ~(1U << ENABLE_PIN);
    PORTB = 0U;
}

/* Function to send a character to the LCD */
static void send_character(uint8_t character)
{
    PORTB = character;
    PORTD |= (1U << REGISTER_SELECT_PIN);
    PORTD |= (1U << ENABLE_PIN);
    _delay_ms(2);
    PORTD &= ~(1U << ENABLE_PIN);
    PORTB = 0U;
}

/* Function to send a string to the LCD */
static void send_string(const char *string_of_characters)
{
    while((*string_of_characters) != '\0')
    {
        send_character((uint8_t)(*string_of_characters));
        string_of_characters++;
    }
}
