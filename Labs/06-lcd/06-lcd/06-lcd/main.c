/***********************************************************************
 * 
 * Stopwatch with LCD display output.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2017-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "Timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function
#include <stdint.h>

/* Function definitions ----------------------------------------------*/
/**20
 * Main function where the program execution begins. Update stopwatch
 * value on LCD display when 8-bit Timer/Counter2 overflows.
 */
int main(void)
{
    // Initialize LCD display
    lcd_init(LCD_DISP_ON);

    // Put string(s) at LCD display
    lcd_gotoxy(1, 0);
    lcd_puts("00:00.0");
    lcd_gotoxy(1, 1);
    lcd_putc('b');
    lcd_gotoxy(12,1);
    lcd_putc('c');

    // Configure 8-bit Timer/Counter2 for Stopwatch
    //Set prescaler and enable overflow interrupt every 16 ms
	TIM2_overflow_16ms();
	TIM2_overflow_interrupt_enable();
	TIM0_overflow_4ms();
	TIM0_overflow_interrupt_enable();

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**
 * ISR starts when Timer/Counter2 overflows. Update the stopwatch on
 * LCD display every sixth overflow, ie approximately every 100 ms
 * (6 x 16 ms = 100 ms).
 */
ISR(TIMER2_OVF_vect)
{
    static uint8_t number_of_overflows = 0;
	static uint8_t tens = 0;        // Tenths of a second
	static uint8_t secs = 0;        // Seconds
	static uint8_t min = 0;			// Minutes
	static uint16_t root = 0;		//square root of seconds
	char lcd_string[2] = "0";       // String for converting numbers by itoa()
	char lcd_strings[2] = "00";
	char lcd_string_min[2] = "00";
	char lcd_root[4] = "0000";
	static int place = 5;
	static int place_min = 2;
	
	number_of_overflows++;
	if (number_of_overflows >= 6)
	{
		// Do this every 6 x 16 ms = 100 ms
		number_of_overflows = 0;

        // WRITE YOUR CODE HERE
	 tens++;
	 
	 if(tens == 10)		
	 {
		 tens = 0;		
		 secs++;		// seconds get increased, if tens equal to 10
	 }
	 
	 if(secs == 10)		
	 place = 4;			// position will becomes 4, if seconds be equal to 10
	 
	 if(secs==60)		
	 {
		 place = 5;		// place will go back to 5, if seconds be equal to 60
		 secs = 0;		// seconds become 0, if seconds be equal to 60
		 min++;			// minutes increase, if seconds be equal to 60
		 lcd_gotoxy(4,0);	
		 lcd_putc('0');	
	 }
	 
	 if(min == 10)		
	 place_min = 1;		// change minutes position to 1
	 
	 root = secs*secs;		
	 
	 itoa(root, lcd_root,10);
	 itoa(tens,lcd_string,10);
	 itoa(secs,lcd_strings,10);
	 itoa(min,lcd_string_min,10);
	 lcd_gotoxy(place_min, 0);
	 lcd_puts(lcd_string_min);
	 lcd_gotoxy(3,0);
	 lcd_gotoxy(place, 0);
	 lcd_puts(lcd_strings);
	 lcd_gotoxy(6, 0);
	 lcd_putc('.');
	 lcd_gotoxy(7,0);
	 lcd_puts(lcd_string);
	 lcd_gotoxy(12,0);
	 lcd_puts(lcd_root);
 }
}
ISR(TIMER0_OVF_vect)
{
	static uint8_t symbol = 0;
	static uint8_t position = 0;
	static uint8_t number_of_overflows = 0;
	number_of_overflows++;
	if (number_of_overflows >=6)
	{
		lcd_gotoxy(1 + position, 1);
		lcd_putc(symbol);
		
		number_of_overflows = 0;

		symbol++;
		if( symbol == 4)			
		{
			position++;				
			symbol = 0;				
		}
		
		if (position == 9)			
		{
			position = 0;		
			for(int i = 0; i<=9; i++)
			{
				lcd_gotoxy(i,1);	
				lcd_putc(' ');		
			}
		}
	}
}