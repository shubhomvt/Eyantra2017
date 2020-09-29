/*
 * servo_micro.c
 *
 * Created: 06-01-2018 02:34:54
 *  Author: lenovo
 */ 


#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//Configure PORTB 5 pin for servo motor 1 operation
void servo1_pin_config (void)
{
	DDRD  = DDRD | 0x80;  //making PORTB 5 pin output
	PORTD = PORTD | 0x80; //setting PORTB 5 pin to logic 1
}
void port_init_servo(void)
{
	servo1_pin_config(); //Configure PORTB 5 pin for servo motor 1 operation
	
}
void timer2_init(void)
{
 TCCR2= 0x00; //stop
 TCNT2 = 0xFE;
 OCR2 = 0x8F;
 TCCR2= (1<< COM21)|(1<<WGM20)|(1<<WGM21);
 
 //TCNT2 = 0xFF; //Counter high value to which OCR1xH value is to be compared with
 //TCNT1L = 0x01;	//Counter low value to which OCR1xH value is to be compared with
 //OCR2 = 0x8F;	//Output compare Register high value for servo 1
 
 
 
 
 TCCR2|= (1<<CS22)|(1<<CS20);
 
}
void init_devices_servo(void)
{
	cli(); //disable all interrupts
	port_init_servo();
	timer2_init();
	sei(); //re-enable interrupts
}

void servo_1(unsigned char degrees)
{
	float PositionPanServo = 0;
	PositionPanServo = ((float)degrees / 1.86) + 35.0;
	
	//OCR1AH = 0x00;
	OCR2 = (unsigned char) PositionPanServo;
}
void servo_1_free (void) //makes servo 1 free rotating
{
	//OCR1AH = 0x03;
	OCR2 = 0x8F; //Servo 1 off
}

/*void main(void)
{
	unsigned char i = 0;
	init_devices_servo();
	
	
	for (i = 0; i <90; i++)
	{
		servo_1(i);
		_delay_ms(30);
		
	}
	
	for(int i=90;i<=180;i++)
	{
		servo_1(i);
		_delay_ms(30);
	}														
	*/
	/*
	servo_1(0);//always put the( requiredangle*4)

	_delay_ms(50);
	servo_1(0);
	//servo_1_free();*/
	//while(1);*/
	
	
	
	
	
/***	DDRB=DDRB|0x20;
	//_delay_ms(1000);
	
	while(1)
	{
		for(int i=0;i<=150;i++)
		{
			PORTB=PORTB|0x20;//0010 0000 pb5
		_delay_ms(0.85);
		PORTB=PORTB & 0xDF;//1101 1111
		_delay_ms(19.15);
		
		}
		
		for(int i=0;i<=150;i++)
		{
			PORTB=PORTB|0x20;//0010 0000 pb5
			_delay_ms(0.65);
			PORTB=PORTB & 0xDF;//1101 1111
			_delay_ms(19.35);
			
			
		}
	
		
	}
	
	
}**/
