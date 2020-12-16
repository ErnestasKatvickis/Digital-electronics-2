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

```c
void Unlock()
	{
		GPIO_write_high(&PORTC,Lock);
		_delay_ms(100);
		GPIO_write_low(&PORTC,Lock);
	}
```
Output to the lock is high
Output is set low again

```c
	void Buzzer_sound()
	{
		GPIO_write_high(&PORTC,Buzzer);
		_delay_ms(300);
		GPIO_write_low(&PORTC,Buzzer);
	}
```
Output to the buzzes is set to high
Output is set low again

```c
	void RedBlink()
	{
		GPIO_toggle(&PORTD,LED_RED);
		_delay_us(1);
		lcd_gotoxy(0,1);
		lcd_puts("                                      ");
		GPIO_toggle(&PORTD,LED_RED);
	}
```
Red LED is turned on and after short delay and the text is cleaned in the 2nd line. After cleaning Red LED is turned off

```c
	void GreenBlink()
	{
		GPIO_toggle(&PORTD,LED_GREEN);
		_delay_us(1);
		lcd_gotoxy(0,1);
		lcd_puts("                                      ");
		GPIO_toggle(&PORTD,LED_GREEN);
	}
```
First, green LED is turned on and then the text in the 2nd line is deleted. After deleting green LED is turned off

```c
	uint8_t scanKeyboard()
	{
		
		
		PORTC  |= (1<< COLUMN1) | (1<<COLUMN2) | (1<< COLUMN3);

		
		uint8_t rowState = PORTB;
		uint8_t masker = 0b00001111;
		// Reading 4, 5, 6 ports of PORTC
		for(int i = 4; i < 7; i++)
		{
			PORTC &= ~(1 << i);
			
			/*Read all rows simultaneously and record 
			  the data to be used in if statements later
			  for indicating the specific key pressed*/
			rowState = (masker & PINB);
			
			if(rowState != PORTB)
			{
				return PORTC | rowState;
			}
			else {}


			//Reset
			PORTC |= (1<< COLUMN1) | (1<<COLUMN2) | (1<< COLUMN3);
			rowState = PORTB;
		}
		return 0;
```
First, we scan three columns of keypad. Columns are connected to C4, C5, C6 ports. Then we determine variable that will store the state of the row pins and mask fot the variable

## Animation

When the password is correct

![GIF](https://github.com/ErnestasKatvickis/Digital-electronics-2/blob/master/Project/GIF.gif)

When the password is incorrect

![GIF2](https://github.com/ErnestasKatvickis/Digital-electronics-2/blob/master/Project/GIF2.gif)

When the time limit is exceeded

![GIF3](https://github.com/ErnestasKatvickis/Digital-electronics-2/blob/master/Project/GIF3.gif)

## References

