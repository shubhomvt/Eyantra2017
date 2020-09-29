/********************************************************************************
 Written by: Vinod Desai, NEX Robotics Pvt. Ltd.
 Edited by: Sachitanand Malewar, NEX Robotics Pvt. Ltd.
 AVR Studio Version 4.17, Build 666
 Date: 26th December 2010
 Application example: Robot control over serial port via XBee wireless communication module 
 					  (located on the ATMEGA260 microcontroller adaptor board)
 Concepts covered:  serial communication
 
 Serial Port used: UART0
 There are two components to the motion control:
 1. Direction control using pins PORTA0 to PORTA3
 2. Velocity control by PWM on pins PL3 and PL4 using OC5A and OC5B.
 In this experiment for the simplicity PL3 and PL4 are kept at logic 1.
 
 Pins for PWM are kept at logic 1.
  
 Connection Details:  	
 						
  Motion control:		L-1---->PA0;		L-2---->PA1;
   						R-1---->PA2;		R-2---->PA3;
   						PL3 (OC5A) ----> Logic 1; 	PL4 (OC5B) ----> Logic 1; 
  Serial Communication:	PORTD 2 --> RXD1 UART1 receive for RS232 serial communication
						PORTD 3 --> TXD1 UART1 transmit for RS232 serial communication
						PORTH 0 --> RXD2 UART 2 receive for USB - RS232 communication
						PORTH 1 --> TXD2 UART 2 transmit for USB - RS232 communication
						PORTE 0 --> RXD0 UART0 receive for ZigBee wireless communication
						PORTE 1 --> TXD0 UART0 transmit for ZigBee wireless communication
						PORTJ 0 --> RXD3 UART3 receive available on microcontroller expansion socket
						PORTJ 1 --> TXD3 UART3 transmit available on microcontroller expansion socket
Serial communication baud rate: 9600bps
To control robot use number pad of the keyboard which is located on the right hand side of the keyboard.
Make sure that NUM lock is on.
Commands:
			Keyboard Key   ASCII value	Action
				8				0x38	Forward
				2				0x32	Backward
				4				0x34	Left
				6				0x36	Right
				5				0x35	Stop
				7				0x37	Buzzer on
				9				0x39	Buzzer off
 Note: 
 
 1. Make sure that in the configuration options following settings are 
 	done for proper operation of the code
 	Microcontroller: atmega2560
 	Frequency: 14745600
 	Optimization: -O0 (For more information read section: Selecting proper optimization 
 						options below figure 2.22 in the Software Manual)
 2. Difference between the codes for RS232 serial, USB and wireless communication is only in the serial port number.
 	Rest of the things are the same. 
 3. For USB communication check the Jumper 1 position on the ATMEGA2560 microcontroller adaptor board
 4. Auxiliary power can supply current up to 1 Ampere while Battery can supply current up to 
 	2 Ampere. When both motors of the robot changes direction suddenly without stopping, 
	it produces large current surge. When robot is powered by Auxiliary power which can supply
	only 1 Ampere of current, sudden direction change in both the motors will cause current 
	surge which can reset the microcontroller because of sudden fall in voltage. 
	It is a good practice to stop the motors for at least 0.5seconds before changing 
	the direction. This will also increase the useable time of the fully charged battery.
	the life of the motor.
*********************************************************************************/

/********************************************************************************
   Copyright (c) 2010, NEX Robotics Pvt. Ltd.                       -*- c -*-
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
   * Source code can be used for academic purpose. 
	 For commercial use permission form the author needs to be taken.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. 
  Software released under Creative Commence cc by-nc-sa licence.
  For legal information refer to: 
  http://creativecommons.org/licenses/by-nc-sa/3.0/legalcode
********************************************************************************/


#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h> //included to support power function
//#include "lcds.h"

volatile int data[21]; //to store received data from UDR1
volatile unsigned char mark=2;
volatile unsigned char gn=0;
volatile unsigned char gs=0;
volatile unsigned char next=0;
//volatile unsigned int a;
/*void lcd_port_config (void)
{
	DDRC = DDRC | 0xF7; //setting all the LCD pin's direction set as output
	PORTC = PORTC & 0x80; //setting all the LCD pins are set to logic 0 except PORTC 7
}*/

void buzzer_pin_config_xbee (void)
{
 DDRC = DDRC | 0x08;		//Setting PORTC 3 as outpt
 PORTC = PORTC & 0xF7;		//Setting PORTC 3 logic low to turnoff buzzer
}

void motion_pin_config_xbee (void)
{
 DDRA = DDRA | 0x0F;
 PORTA = PORTA & 0xF0;
 DDRL = DDRL | 0x18;   //Setting PL3 and PL4 pins as output for PWM generation
 PORTL = PORTL | 0x18; //PL3 and PL4 pins are for velocity control using PWM.
}

//Function to initialize ports
void port_init_xbee()
{
	motion_pin_config_xbee();
	buzzer_pin_config_xbee();
	//lcd_port_config();//lcd pin configuration
}

/*void buzzer_on (void)
{
 unsigned char port_restore = 0;
 port_restore = PINC;
 port_restore = port_restore | 0x08;
 PORTC = port_restore;
}

void buzzer_off (void)
{
 unsigned char port_restore = 0;
 port_restore = PINC;
 port_restore = port_restore & 0xF7;
 PORTC = port_restore;
}*/


//Function To Initialize UART0
// desired baud rate:9600
// actual baud rate:9600 (error 0.0%)
// char size: 8 bit
// parity: Disabled
void uart0_init(void)
{
 UCSR0B = 0x00; //disable while setting baud rate
 UCSR0A = 0x00;
 UCSR0C = 0x06;
 UBRR0L = 0x5F; //set baud rate lo
 UBRR0H = 0x00; //set baud rate hi
 UCSR0B = 0x98;
}
unsigned char conversion(unsigned char hex)
{	unsigned char node;	
	
	switch(hex)
	{
		case 0x04:
		node=4;
		break;
		case 0x0B:
		node=11;
		break;
		case 0x12:
		node=18;
		break;
		case 0x19:
		node=25;
		break;
		case 0x20:
		node=32;
		break;
		case 0x27:
		node=39;
		break;
		case 0x2E:
		node=46;
		break;
		
		case 0x06:
		node=6;
		break;
		case 0x0D:
		node=13;
		break;
		case 0x14:
		node=20;
		break;
		case 0x1B:
		node=27;
		break;
		case 0x22:
		node=34;
		break;
		case 0x29:
		node=41;
		break;
		case 0x30:
		node=45;
		break;
		
		case 0x64:
		node=100;
		break;
		case 0x65:
		node=101;
		break;
			
	}
	/*lcd_cursor(1,1);  //set the cursor on row 1, column 1
	
	lcd_print(2,12,node,5);  //Print the count on second row
	_delay_ms(1000);	// Display for 1000ms or 1 second
	lcd_wr_command(0x01); //Clear the LCD*/
	return node;
}



SIGNAL(SIG_USART0_RECV) 		// ISR for receive complete interrupt
{	
	unsigned char k;
	
	lcd_set_4bit();
	lcd_init();
	k=UDR0;
	if(k==0x37)
	{
		mark=1;
	}
	if (k==0x38)
	{
		mark=0;
		next++;
		buzzer_beep();
	}
	if (mark==1)
	{
		if(k>0x00 && k<0x31)
		{
			green_nodes[gn]=conversion(k);
			
			lcd_cursor(1,1);  //set the cursor on row 1, column 1
			
			lcd_print(2,12,conversion(k),5);  //Print the count on second row
			_delay_ms(1000);	// Display for 1000ms or 1 second
			lcd_wr_command(0x01); //Clear the LCD
			gn++;
			
		}
		else if(k==0x64 || k==0x65)
		{
			green_side[gs]=conversion(k);
			
			lcd_cursor(1,1);  //set the cursor on row 1, column 1
			
			lcd_print(2,12,conversion(k),5);  //Print the count on second row
			_delay_ms(1000);	// Display for 1000ms or 1 second
			lcd_wr_command(0x01); //Clear the LCD
			gs++;
			/*lcd_cursor(1,1);  //set the cursor on row 1, column 1
			
			lcd_print(2,12,green_nodes[gn],5);  //Print the count on second row
			_delay_ms(1000);	// Display for 1000ms or 1 second
			lcd_wr_command(0x01); //Clear the LCD
			*/
		}
		
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*for(int i=0;i<3;i++)
	{
		data[i] = UDR0;
		
	}*/
	/*if(data[0] == 0x38){
		a=8;*/
	/*lcd_cursor(1,1);  //set the cursor on row 1, column 1
	//lcd_string("Blue Pulses"); // Display "Blue Pulses" on LCD
	lcd_print(2,1,a,5);  //Print the count on second row
	_delay_ms(1000);	// Display for 1000ms or 1 second
	lcd_wr_command(0x01); //Clear the LCD
	}	
	*/

	 				//making copy of data from UDR0 in 'data' variable 

	//UDR0 = data; 				//echo data back to PC

		/*if(data[0] == 0x100 && data[1] == 0x63) //ASCII value of 8
		{
			PORTA=0x06;  //forward
		}*/
	

}


//Function To Initialize all The Devices
void init_devices_xbee()
{
 cli(); //Clears the global interrupts
 port_init_xbee();  //Initializes all the ports
 uart0_init(); //Initailize UART1 for serial communiaction
 sei();   //Enables the global interrupts
}

void USARTWriteChar(char data)
{
	//Wait until the transmitter is ready
 /*  while(!(UCSRA & (1<<UDRE)))
	{
		//Do nothing
	*/

	//Now write the data to USART buffer
  
	UDR0=data;
		
	
}

//Main Function


