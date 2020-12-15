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

First of all me and my partner though of a block diagram of how should the system work. Then we implemented it.

![Block_diagram](https://github.com/ErnestasKatvickis/Digital-electronics-2/blob/master/Project/Block_diagram.png)

According to this diagram we wrote our program code.
First of all, it was necessary to write functions. First two functions were necessary for scanning the keyboard and determine the pressed key. For that we wrote two functions: scanKeyboard() and determineKey(). The function worked and now we can determine witch key is pressed. Next step was to write a code, so that pressed key would be stored in an entered_num massive of 4 numbers. Then we wrote a function ArrayComparison() to compare the entered password to the ones that are saved by the program. Afterwards we needed to set all I/O ports on the ATmega328 microcontroller so it would work properly, so we wrote a function setup(). To make main file less complex we created functions such as RedBlink() and GreenBlink() for LEDs to blink, Unlock() to unlock the door, Buzzer_sound() for the buzzer sound when the wrong password is inserted. All these functions can be found in the [function library.](https://github.com/ErnestasKatvickis/Digital-electronics-2/blob/master/Project/Door_Lock/Door_Lock/function.c)

In the main file we enabled the interrupt, LCD and UART. Then we tried to implement the code in the while(1) forewer loop. But we didn't know how to make a time limit in it. We tried using interrupts, but that didnt work properly. So we transfered all the code from while loop to the interrupt. We used TIM0_overflow_16ms. In the main function. And we used ADC convertion in the ISR(TIM0_interrupt) function. And in the ISR(ADC_vect) we wrote all the code. In the code we first defined all the variables necessary. Then we wrote the part were the keypad is scaned and the pressed key is determined. Afterwards we compare the entered password to the saved ones. If its correct the doors unlock. If it is incorrect then we start again from the start unless there were made 4 attempts. If 4 attempts were made than the program delay the input possibility by 3 seconds. There is another possibility aswell where the user doesn't enter the code at all. Than the program says that the user exceeded time limit and starts from the start. All the main code is in the [main.c file.](https://github.com/ErnestasKatvickis/Digital-electronics-2/blob/master/Project/Door_Lock/Door_Lock/main.c)


## Animation

When the password is correct

![GIF](https://github.com/ErnestasKatvickis/Digital-electronics-2/blob/master/Project/GIF.gif)

When the password is incorrect

![GIF2](https://github.com/ErnestasKatvickis/Digital-electronics-2/blob/master/Project/GIF2.gif)

When the time limit is exceeded

![GIF3](https://github.com/ErnestasKatvickis/Digital-electronics-2/blob/master/Project/GIF3.gif)

## References

[1](https://github.com/tomas-fryza/Digital-electronics-2)/n
[2](https://www.microchip.com/wwwproducts/en/ATmega328p)
