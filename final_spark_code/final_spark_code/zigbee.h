/********************************************************************************
 Platform: SPARK V
 Experiment: 10B_Serial_Comminucation_ZigBee_wireless
 Written by: Vinod Desai, NEX Robotics Pvt. Ltd.
 Edited By: Sachitanand Malewar, NEX Robotics Pvt. Ltd.
 Last Modification: 22nd September 2010
 AVR Studio Version 4.17, Build 666

 Concepts covered: serial communication using zigbee wireless module

 This experiment demonstrates Robot control over serial port via ZigBee wireless 
 comunication module 

 There are two components to the motion control:
 1. Direction control using pins PORTB0 to 	PORTB3
 2. Velocity control by PWM on pins PD4 and PD5.

 In this experiment for the simplicity PD4 and PD5 are kept at logic 1.
 
 Pins for PWM are kept at logic 1.
  
 Connection Details:   L-1---->PB0;		L-2---->PB1;
   					   R-1---->PB2;		R-2---->PB3;
   					   PD4 (OC1B) ----> Logic 1; 	PD5 (OC1A) ----> Logic 1; 

 Serial Communication: PORTD 0 --> RXD UART receive for RS232 serial communication
					   PORTD 1 --> TXD UART transmit for RS232 serial communication

 Make sure that J5 us set towards the back side of the robot 
 i.e. XBee wireless module is connected to the serial port of the microcontroller.
 For more details on the jumper settings refer to the hardware manual.

 Use baud rate as 9600bps.
 
 To control robot use number pad of the keyboard which is located on the right hand
 side of the keyboard. Make sure that NUM lock is on.

 For more detail on hardware connection and theory refer the hardware manual.

 Note: 
 
 1. Make sure that in the configuration options following settings are 
 	done for proper operation of the code

 	Microcontroller: atmega16
 	Frequency: 7372800
 	Optimization: -O0 (For more information read section: Selecting proper optimization
	              options below figure 4.22 in the hardware manual)
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

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*void motion_pin_config (void)
{
 DDRB = DDRB | 0x0F;   //set direction of the PORTB3 to PORTB0 pins as output
 PORTB = PORTB & 0xF0; // set initial value of the PORTB3 to PORTB0 pins to logic 0
 DDRD = DDRD | 0x30;   //Setting PD4 and PD5 pins as output for PWM generation
 PORTD = PORTD | 0x30; //PD4 and PD5 pins are for velocity control using PWM
}
*/

void buzzer_pin_config_zigbee (void)
{
 DDRC = DDRC | 0x08;		//Setting PORTC 3 as outpt
 PORTC = PORTC & 0xF7;		//Setting PORTC 3 logic low to turnoff buzzer
}

//Function to initialize ports
void port_init_zigbee()
{
 //motion_pin_config();
 buzzer_pin_config_zigbee();
}

//UART0 initialisation
// desired baud rate: 9600
// actual: baud rate:9600 (0.0%)
// char size: 8 bit
// parity: Disabled
void uart0_init_zigbee(void)
{
 UCSRB = 0x00; //disable while setting baud rate
 UCSRA = 0x00;
 UCSRC = 0x86;
 UBRRL = 0x2F; //set baud rate lo  //67 is for 16MHz 9600 baudrate
 UBRRH = 0x00; //set baud rate hi
 UCSRB = 0x98; 
}
unsigned char conversion(unsigned char hex)
{	unsigned char node;	
	
	switch(hex)
	{
		case 0x02:
		node=2;
		break;
		case 0x09:
		node=9;
		break;
		case 0x10:
		node=16;
		break;
		case 0x17:
		node=23;
		break;
		case 0x1E:
		node=30;
		break;
		case 0x25:
		node=37;
		break;
		case 0x2C:
		node=44;
		break;
		
		case 0x30:
		node=48;
		break;
		case 0x29:
		node=41;
		break;
		case 0x22:
		node=34;
		break;
		case 0x1B:
		node=27;
		break;
		case 0x14:
		node=20;
		break;
		case 0x0D:
		node=13;
		break;
		case 0x06:
		node=6;
		break;
		
		case 0x64:
		node=100;
		break;
		case 0x65:
		node=101;
		break;
			
	}
	
	return node;
}

//Function used for setting motor's direction
/*void motion_set_zigbee (unsigned char Direction)
{
 unsigned char PortBRestore = 0;

 Direction &= 0x0F; 			// removing upper nibbel as it is not needed
 PortBRestore = PORTB; 			// reading the PORTB's original status
 PortBRestore &= 0xF0; 			// setting lower direction nibbel to 0
 PortBRestore |= Direction; 	// adding lower nibbel for direction command and restoring the PORTB status
 PORTB = PortBRestore; 			// setting the command to the port
}*/

/*void forward (void)         //both wheels forward
{
  motion_set_zigbee(0x06);
}

void backward (void)        //both wheels backward
{
  motion_set_zigbee(0x09);
}

void left (void)            //Left wheel backward, Right wheel forward
{
  motion_set_zigbee(0x05);
}

void right (void)           //Left wheel forward, Right wheel backward
{   
  motion_set_zigbee(0x0A);
}

void stop (void)            //hard stop
{
  motion_set_zigbee(0x00);
}*/

void buzzer_on_zigbee (void)
{
 unsigned char port_restore = 0;
 port_restore = PINC;
 port_restore = port_restore | 0x08;
 PORTC = port_restore;
}

void buzzer_off_zigbee (void)
{
 unsigned char port_restore = 0;
 port_restore = PINC;
 port_restore = port_restore & 0xF7;
 PORTC = port_restore;
}

void init_devices_zigbee (void)
{
 cli();         //Clears the global interrupts
 port_init_zigbee();
 uart0_init_zigbee();
 sei();         //Enables the global interrupts
}

SIGNAL(SIG_UART_RECV) 
{	//init_devices_buzzer();
	
	          
 unsigned char k;
 k=UDR;         // Echo the received data plus 1
if(k==0x35)//53
{
	mark=1;
	buzzer_on();
	_delay_ms(300);
	buzzer_off();
	_delay_ms(300);
}
if (k==0x36)//54
{
	mark=0;
	next++;
	buzzer_on();
	_delay_ms(300);
	buzzer_off();
	_delay_ms(300);
}

	if (mark==1)
	{
		if(k>0x00 && k<0x31)//0-49
		{
			blue_nodes[b]=conversion(k);
			
			b++;
			buzzer_on();
			_delay_ms(300);
			buzzer_off();
			_delay_ms(300);
			
		}
		else if(k==0x64 || k==0x65)//100-101
		{
			blue_side[bs]=conversion(k);
			bs++;
			buzzer_on();
			_delay_ms(300);
			buzzer_off();
			_delay_ms(300);
		}
	}		
 
}

void USARTWriteChar(char data)
{
	//Wait until the transmitter is ready
 /*  while(!(UCSRA & (1<<UDRE)))
	{
		//Do nothing
	*/

	//Now write the data to USART buffer
  
	UDR=data;
		
	
}

//Main Function
/*int main()
{
	init_devices();
	unsigned char data[8];
	data[0]=71;
	data[1]=60;
	data[2]=2;
	data[3]=8;
	data[4]=15;
	data[5]=100;
	data[6]=255;
	data[7]=0;
	
	for(int i=0;i<8;i++)
	{
		USARTWriteChar(data[i]);
		_delay_ms(1000);
	}
	
	while(1);
}*/

