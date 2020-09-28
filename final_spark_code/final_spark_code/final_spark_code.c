/*
 * TASK1B.c
 *
 * Created: 04/11/2017 22:58:28
 *  Author: Avinash Dubey
 */

////RED
#include <avr/io.h>
#define F_CPU 7372800UL
#include <util/delay.h>
#include "buzzer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "lcd.h"
#include "adjescent.h"
#include "pos_encoder.h"
#include "servo_motor.h"
#include "sharp_header.h"

//#include "line_follower_new.h"
#include "line.h"
#include "color_header_spark.h"
#include "zigbee.h"
#include "direction.h"
//#include "adjsrc4.h"


void ReachDestinationAvoidingNode(unsigned char Xd,unsigned char Yd)
{
	
	

	path1 = main_function7( start,des);
	
	
	

	init_devices();
//	lcd_set_4bit();
	//lcd_init();

	

	while(1)
	{
		line_follower();
		if (g==1)
		{
			
			break;
		}
			
		
		
	}
	
	g=0;
	l=0;
	t=0;
	/*back();
	velocity(100,100);
	
	_delay_ms(1500);*/
	start=des;
}


//Do not make changes in main function

int main(void)
{   DDRB=0x20; 
	init_devices_zigbee();
	init_devices_pos();
	stage=1;
	t=0;
     ReachDestinationAvoidingNode(start,des);//22-6
	 buzzer_on();
	   _delay_ms(1000);
	   buzzer_off();
	stage=2;
	//start=5;
	des=48;
	array_init();
		ReachDestinationAvoidingNode(start,des);//6-48
		buzzer_on();
		_delay_ms(1000);
		buzzer_off();
	//stage=4;
	//des=2;
	//ReachDestinationAvoidingNode(start,des);//4-2
	
 	stage=3;
	//start=2;////////
	/////////////stage==3/////start=4///
	des=4;
	ReachDestinationAvoidingNode(start,des);///48-4
	buzzer_on();
	_delay_ms(1000);
	buzzer_off();
	
	//stage=4;
	//des=48;
	_Bool red_des_count=0;
	for (unsigned char i=0;i<=10;i++)
	{
		switch (red_nodes[i])
		{
			case 2:
			des=2;
			red_des_count=1;
			break;
			case 9:
			des=9;
			red_des_count=1;
			break;
			case 16:
			des=16;
			red_des_count=1;
			break;
			case 23:
			des=23;
			red_des_count=1;
			break;
			case 30:
			des=30;
			red_des_count=1;
			break;
			case 37:
			des=37;
			red_des_count=1;
			break;
			
			
		}
	}
	if (red_des_count==1)
	{
		ReachDestinationAvoidingNode(start,des);//4-X
		buzzer_on();
		_delay_ms(1000);
		buzzer_off();
		des=8;
		ReachDestinationAvoidingNode(start,des);//X-8
		buzzer_on();
		_delay_ms(500);
		buzzer_off();
		_delay_ms(500);
		buzzer_on();
		_delay_ms(500);
		buzzer_off();
		_delay_ms(500);
	}
	else if (red_des_count==0)
	{	des=8;
		ReachDestinationAvoidingNode(start,des);//4-8
		buzzer_on();
		_delay_ms(500);
		buzzer_off();
		_delay_ms(500);
		
		buzzer_on();
		_delay_ms(500);
		buzzer_off();
		_delay_ms(500);
	}
	
	
	
	
	
	forward();
	velocity(0,0);
	while(1);
	
	
	
	
}
