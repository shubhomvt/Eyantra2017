/*
 * TASK1B.c
 *
 * Created: 04/11/2017 22:58:28
 *  Author: Avinash Dubey
 */

//////////////////BLUE FEEDER BOT
#include <avr/io.h>
#define F_CPU 7372800UL
#include <util/delay.h>
#include "buzzer.h"
//#include "lcd.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "lcd.h"
#include "adjescent.h"s
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
	
	_delay_ms(500);*/
	
	start=des;
}


//Do not make changes in main function

int main(void)
{   DDRB=0x20; 
	init_devices_pos();
     ReachDestinationAvoidingNode(start,des);//6-46
	 buzzer_on();
	   _delay_ms(1000);
	   buzzer_off();
	stage=2;
	//start=5;
	des=4;
	array_init();
		ReachDestinationAvoidingNode(start,des);//46-4
	//stage=4;
	//des=2;
	//ReachDestinationAvoidingNode(start,des);//4-2
	
 	stage=3;
	//start=2;////////
	/////////////stage==3/////start=4///
	des=44;
	ReachDestinationAvoidingNode(start,des);///2-44//4-44
	
	//stage=4;
	//des=48;
	des=13;
	buzzer_on();
	_delay_ms(1000);
	buzzer_on();
	ReachDestinationAvoidingNode(start,des);//44-48//44-13
	buzzer_on();
	_delay_ms(1000);
	buzzer_off();
	//des=13;
	//stage=3;
	
// 	ReachDestinationAvoidingNode(start,des);//48-13
// 	buzzer_on();
// 	_delay_ms(1000);
// 	buzzer_on();
// 	stage=4;
	des=14;
	ReachDestinationAvoidingNode(start,des);//13-14
	

	buzzer_on();
	_delay_ms(2000);
	buzzer_on();
   forward();
   velocity(0,0);
   _delay_ms(1500);
   while(1);
	
	
	
	
}
