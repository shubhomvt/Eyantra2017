/*
 * TASK1B.c
 *
 * Created: 04/11/2017 22:58:28
 *  Author: Avinash Dubey
 */


#include <avr/io.h>
#define F_CPU 14745600
#include <util/delay.h>
#include "buzzer.h"
#include "IncFile1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "position_encoder.h"
#include "servo.h"
#include "sharp_sensor.h"
#include "line_follower_new.h"
#include "colour_sensor_header.h"
#include "zigbee.h"
#include "direction.h"


void ReachDestinationAvoidingNode(unsigned char Xd,unsigned char Yd)
{
	
	

	path1 = main_function7( start,des);
	
	init_devices();
	lcd_set_4bit();
	lcd_init();

/*	buzzer_on();
	_delay_ms(2000);
	buzzer_off();
	_delay_ms(2000);
	for(int i=0;i<=max;i++)
	{
	lcd_print(2,1,path1.path[i],2);
	_delay_ms(1000);	
	}*/
	
	while(1)
	{
		line_follower();
		if (g==1)
		{
			
			break;
		}
		
		
		
		
		
	}
	/*buzzer_on();
	_delay_ms(500);
	buzzer_off();*/
	
	g=0;
	l=0;
	t=0;
	back();
	velocity(100,100);
	//_delay_ms(1500);
	start=des;



}


//Do not make changes in main function

int main(void)
{		init_devices1();//pos
	init_devices_xbee();
		buzzer_beep();
		_delay_ms(1000);
	start=40;
	des=2;
	ReachDestinationAvoidingNode(start,des);//40-2
	  buzzer_on();
	  _delay_ms(1000);
	  buzzer_off();
	 stage=2;
	 des=44;
		 array_init();
		 ReachDestinationAvoidingNode(start,des);//2-44
		 buzzer_on();
		 _delay_ms(1000);
		 buzzer_off();
		 stage=3;
		 des=4;
		  ReachDestinationAvoidingNode(start,des);//44-4
		  buzzer_on();
		  _delay_ms(1000);
		  buzzer_off();
		  des=41;
		  ReachDestinationAvoidingNode(start,des);//4-41
		  buzzer_on();
		  _delay_ms(1000);
		  buzzer_off();
		  des=42;
		  ReachDestinationAvoidingNode(start,des);//41-42
		  buzzer_on();
		  _delay_ms(1000);
		  buzzer_off();
		  des=46;
		  ReachDestinationAvoidingNode(start,des);//42-46
		  buzzer_on();
		  _delay_ms(1000);
		  buzzer_off();
	 

}
