  
/***********************************************************************
 * 
 * Alternately toggle two LEDs when a push button is pressed.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_1   PB1     // AVR pin where green LED is connected
#define LED_2   PB3 
#define LED_3   PB5 
#define LED_4   PC1 
#define LED_5   PC3 
#define BLINK_DELAY 150
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions

/* Functions ---------------------------------------------------------*/
/**
 * Main function where the program execution begins. Toggle two LEDs 
 * when a push button is pressed.
 */
int main(void)
{
    // Set pins as output in Data Direction Register...
    DDRB = DDRB | (1<<LED_1);
	DDRB = DDRB | (1<<LED_2);
	DDRB = DDRB | (1<<LED_3);
	DDRC = DDRC | (1<<LED_4);
	DDRC = DDRC | (1<<LED_5);
    // ...and turn LEDs off in Data Register
    PORTB = PORTB & ~(1<<LED_1); //TURN OFF
	PORTB = PORTB & ~(1<<LED_2);
	PORTB = PORTB & ~(1<<LED_3);
	PORTC = PORTC & ~(1<<LED_4);
	PORTC = PORTC & ~(1<<LED_5);

    // Infinite loop
    while (1)
    {

			PORTB = PORTB ^ (1<<LED_1); //TURN ON FIRST LED
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB ^ (1<<LED_1); //TURN OFF FIRST LED
			PORTB = PORTB ^ (1<<LED_2); //AT THE SAME TIME THE SECOND ONE TURNS ON
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB ^ (1<<LED_2);
			PORTB = PORTB ^ (1<<LED_3);
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB ^ (1<<LED_3);
			PORTC = PORTC ^ (1<<LED_4);
			_delay_ms(BLINK_DELAY);
			PORTC = PORTC ^ (1<<LED_4);
			PORTC = PORTC ^ (1<<LED_5);
			_delay_ms(BLINK_DELAY);
			PORTC = PORTC ^ (1<<LED_5);
			PORTC = PORTC ^ (1<<LED_4);
			_delay_ms(BLINK_DELAY);
			PORTC = PORTC ^ (1<<LED_4);
			PORTB = PORTB ^ (1<<LED_3);
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB ^ (1<<LED_3);
			PORTB = PORTB ^ (1<<LED_2);
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB ^ (1<<LED_2);
		
    }

    // Will never reach this
    return 0;
}

