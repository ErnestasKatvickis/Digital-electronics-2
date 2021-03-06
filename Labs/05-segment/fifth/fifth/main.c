/***********************************************************************
 * 
 * Decimal counter with 7-segment output.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "segment.h"        // Seven-segment display library for AVR-GCC
#define F_CPU 16000000
#include <util/delay.h>

/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Display decimal 
 * counter values on SSD (Seven-segment display) when 16-bit 
 * Timer/Counter1 overflows.
 */
int main(void)
{
    // Configure SSD signals
    SEG_init();

    // Test of SSD: display number '3' at position 0
    SEG_update_shift_regs(3, 0);

    /* Configure 16-bit Timer/Counter1
     * Set prescaler and enable overflow interrupt */
	TIM1_overflow_1s();
	TIM1_overflow_interrupt_enable();
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
 * ISR starts when Timer/Counter1 overflows. Increment decimal counter
 * value and display it on SSD.
 */
ISR(TIMER1_OVF_vect)
{
    // WRITE YOUR CODE HERE
	/*int poss = 0;
	
	for(int i = 0; i < 60; i++)
	{
		SEG_update_shift_regs(i%10, poss);
		_delay_ms(100);
		
		SEG_update_shift_regs(i/10, poss+1);
		_delay_ms(100);
	}*/
	 SEG_update_shift_regs(0,0);
	 _delay_ms(200);
	 SEG_update_shift_regs(1,0);
	 _delay_ms(200);
	 SEG_update_shift_regs(2,0);
	 _delay_ms(200);
	 SEG_update_shift_regs(3,0);
	 _delay_ms(200);
	 SEG_update_shift_regs(4,0);
	 _delay_ms(200);
	 SEG_update_shift_regs(5,0);
	 _delay_ms(200);
}



