# Digital Electronics 2 Project
### Team members

- Modestas Levišauskas
- Ernestas Katvickis [Link to GitHub project folder](https://github.com/ErnestasKatvickis/Digital-electronics-2/tree/master/Project)

### Projects objectives

Project objective is to create description of 4x3 keyboard control and in this project must be included an application of door lock system, display, door unlock relay, own library for keypad scanning, time limit for entering the correct 4-digit code, signaling of entering the wrong code, time delay for re-locking the lock approx. Also, another project objectives are self study, creation of own solution and presentation of results.

## Hardware description

We used SimulIDE for our scheme. The scheme consist of
- LCD display - shows to the user the status of situation. If the password is written incorrectly then the word "Incorrect" lights up on LCD;; 
- AVR microcontroller Atmega328P - control the whole system;
- 4x3 keyboard - is used for the intput of the password;
- Audio output device - is used to inform about wrong password;
- Relay - is used to unlock the door;
- BJT transistor - is used as a switch;
- Fix voltage - used as a power source;
- LED's - here are Red and Green LED's. Red one signal that a wrong password was entered and the Green one signal that a right password was entered;
- Resistors - are used to lower the current;
- Grounds - is used to end the circuit. 

![Scheme](https://github.com/ErnestasKatvickis/Digital-electronics-2/blob/master/Project/Scheme.png)

## Code description and simulation

```
void Unlock()
	{
		// Output to the lock is high
		GPIO_write_high(&PORTC,Lock);
		_delay_ms(100);
		// Output is set low again
		GPIO_write_low(&PORTC,Lock);
	}
	void Buzzer_sound()
	{
		// Output to the buzzes is set to high
		GPIO_write_high(&PORTC,Buzzer);
		_delay_ms(300);
		// Output is set low again
		GPIO_write_low(&PORTC,Buzzer);
	}
	void RedBlink()
	{
		// RED LED is turned on
		GPIO_toggle(&PORTD,LED_RED);
		// Short delay
		_delay_us(1);
		// The text is cleaned in the 2nd line
		lcd_gotoxy(0,1);
		lcd_puts("                                      ");
		// RED LED is turned off
		GPIO_toggle(&PORTD,LED_RED);
	}
	void GreenBlink()
	{
		// GREEN led is turned on
		GPIO_toggle(&PORTD,LED_GREEN);
		// Short delay
		_delay_us(1);
		// The text in the 2nd line is deleted
		lcd_gotoxy(0,1);
		lcd_puts("                                      ");
		// GREEN LED is tunred off
		GPIO_toggle(&PORTD,LED_GREEN);
	}
```

## Animation

When the password is correct

![GIF](https://github.com/ErnestasKatvickis/Digital-electronics-2/blob/master/Project/GIF.gif)

When the password is incorrect

![GIF2](https://github.com/ErnestasKatvickis/Digital-electronics-2/blob/master/Project/GIF2.gif)

## References

