
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
//#include "lcd.h"
unsigned char l=0;
unsigned char t=0;
	
unsigned char stage=1;
unsigned char task=0;
unsigned char side=0;
unsigned char r=1;

unsigned char rs=1;

unsigned char gn=1;////////blue bot
unsigned char gs=1;
volatile char red_nodes[12],blue_nodes[12],red_side[20],blue_side[20],green_nodes[12],green_side[12];
volatile unsigned char data[21]; //to store received data from UDR1
volatile unsigned char mark=2;
volatile unsigned char b=0;//blue bot
volatile unsigned char bs=0;
volatile unsigned char next=0;

unsigned char ADC_Conversion(unsigned char);
unsigned char ADC_Value;

void servo100()
{
	for(int i=95;i<=180;i=i+3)
	{
		init_devices_sharp();
		//			lcd_set_4bit();
		//			lcd_init();
		for (int i=0;i<2;i++)
		{
			Center_ultrasonic_Sensor = ADC_Conversion_sharp(1) * 2;
			//lcd_print(2,12,Center_ultrasonic_Sensor,3);       // In Inches
			
		}
		_delay_ms(100);
		
		init_devices_servo();
		servo_1(i);
		_delay_ms(10);
		
		
		if(Center_ultrasonic_Sensor>200 )
		{	
				servo_1(i);
				_delay_ms(1000);
				//buzzer_beep();
				side=100;
				color_sensor_work();
				
				_delay_ms(100);
				do_task();
				_delay_ms(500);
				
				break;
			
			
			 
		}
		
	}
	servo_1(95);
	_delay_ms(500);
	
}
void servo101()
{
	for(int i=95;i>=10;i=i-3)
	{
		init_devices_sharp();
		//			lcd_set_4bit();
		//			lcd_init();
		for (int i=0;i<2;i++)
		{
			Center_ultrasonic_Sensor = ADC_Conversion_sharp(1) * 2;
			//lcd_print(2,12,Center_ultrasonic_Sensor,3);       // In Inches
			
		}
		_delay_ms(100);
		
		init_devices_servo();
		servo_1(i);
		_delay_ms(10);
		
		
		if(Center_ultrasonic_Sensor>200 )
		{	servo_1_free();
			_delay_ms(1000);
			//buzzer_beep();
			side=101;
			color_sensor_work();
			
			_delay_ms(100);
			do_task();
			_delay_ms(500);
			
			break;
		}
		
	}
	servo_1(95);
	_delay_ms(100);
}


//Function to configure LCD port
/*void lcd_port_config (void)
{
 DDRC = DDRC | 0xF7;    //all the LCD pin's direction set as output
 PORTC = PORTC & 0x80;  // all the LCD pins are set to logic 0 except PORTC 7
}*/

//ADC pin configuration
void adc_pin_config (void)
{
 DDRA = 0x00;   //set PORTF direction as input
 PORTA = 0x00;  //set PORTF pins floating
}

//Function to configure ports to enable robot's motion
void motion_pin_config (void)
{
 DDRB = DDRB | 0x0F;    //set direction of the PORTB3 to PORTB0 pins as output
 PORTB = PORTB & 0xF0;  //set initial value of the PORTB3 to PORTB0 pins to logic 0
 DDRD = DDRD | 0x30;    //Setting PD5 and PD4 pins as output for PWM generation
 PORTD = PORTD | 0x30;  //PD5 and PD4 pins are for velocity control using PWM
}

//Function to Initialize PORTS
void port_init()
{
 //lcd_port_config();
 adc_pin_config();		
 motion_pin_config();
}

//TIMER1 initialize - prescale:64
// WGM: 5) PWM 8bit fast, TOP=0x00FF
// desired value: 450Hz
// actual value: 450.000Hz (0.0%)
void timer1_init(void)
{
 TCCR1B = 0x00; //stop
 TCNT1H = 0xFF; //setup
 TCNT1L = 0x01;
 OCR1AH = 0x00;
 OCR1AL = 0xFF;
 OCR1BH = 0x00;
 OCR1BL = 0xFF;
 ICR1H  = 0x00;
 ICR1L  = 0xFF;
 TCCR1A = 0xA1;
 TCCR1B = 0x0D; //start Timer
}


//Function to Initialize ADC
void adc_init()
{
 ADCSRA = 0x00;
 ADMUX = 0x20;		//Vref=5V external --- ADLAR=1 --- MUX4:0 = 0000
 ACSR = 0x80;
 ADCSRA = 0x86;		//ADEN=1 --- ADIE=1 --- ADPS2:0 = 1 1 0
}

//This Function accepts the Channel Number and returns the corresponding Analog Value 
unsigned char ADC_Conversion(unsigned char Ch)
{
 unsigned char a;
 Ch = Ch & 0x07;  			
 ADMUX= 0x20| Ch;	   		
 ADCSRA = ADCSRA | 0x40;	//Set start conversion bit
 while((ADCSRA&0x10)==0);	//Wait for ADC conversion to complete
 a=ADCH;
 ADCSRA = ADCSRA|0x10;      //clear ADIF (ADC Interrupt Flag) by writing 1 to it
 return a;
}

// This Function prints the Analog Value Of Corresponding Channel No. at required Row
// and Coloumn Location. 
/*void print_sensor(char row, char coloumn,unsigned char channel)
{
 ADC_Value = ADC_Conversion(channel);
 lcd_print(row, coloumn, ADC_Value, 3);
}*/

//Function used for setting motor's direction
void motion_set (unsigned char Direction)
{
 unsigned char PortBRestore = 0;

 Direction &= 0x0F; 			// removing upper nibbel as it is not needed
 PortBRestore = PORTB; 			// reading the PORTB's original status
 PortBRestore &= 0xF0; 			// setting lower direction nibbel to 0
 PortBRestore |= Direction; 	// adding lower nibbel for direction command and restoring the PORTB status
 PORTB = PortBRestore; 			// setting the command to the port
}
void back (void) //both wheels backward
{
	motion_set(0x09);
}
void forward (void) //both wheels forward
{
  motion_set(0x06);
}

void stop (void) //hard stop
{
  motion_set(0x00);
}

//Function for velocity control
void velocity (unsigned char left_motor, unsigned char right_motor)
{
 OCR1AH = 0x00;
 OCR1AL = left_motor; 
 OCR1BH = 0x00;
 OCR1BL = right_motor;
}

void init_devices (void)
{
 cli();          //Clears the global interrupts
 port_init();
 timer1_init();
 adc_init();
 sei();          //Enables the global interrupts
}

//Main Function
int line_follower()
{	buzzer_pin_config();
		 unsigned char THRESHOLD	=	60 ;       // set the pots such that all three sensor
	// calibrated to show its min value on LCD.
	// i.e on LCD Sensor values are betwn 0 To 25
	// on white line
	 unsigned char	VELOCITY_MAX	= 50;
	 unsigned char	VELOCITY_MIN	= 35;
	 unsigned char	VELOCITY_LOW	= 0;
	 unsigned char Left_white_line = 0;
	 unsigned char Center_white_line = 0;
	 unsigned char Right_white_line = 0;


 //unsigned char flag ;

 //init_devices();

 /*lcd_set_4bit();
 lcd_init();*/

//velocity(VELOCITY_MAX,VELOCITY_MAX);    // Set the speed to max velocity
// lcd_print (2,1,VELOCITY_MAX,3);
// lcd_print (2,5,VELOCITY_MAX,3);
// forward();                              // start to move froward


	Left_white_line = ADC_Conversion(3);	//Getting data of Left WL Sensor
	Center_white_line = ADC_Conversion(4);	//Getting data of Center WL Sensor
	Right_white_line = ADC_Conversion(5);	//Getting data of Right WL Sensor
 
	//print_sensor(1,1,3);		//Prints value of White Line Sensor Left
	//print_sensor(1,5,4);		//Prints value of White Line Sensor Center
	//print_sensor(1,9,5);		//Prints value of White Line Sensor Right

	//flag=0;

	

	
	if(Center_white_line<THRESHOLD && Left_white_line<THRESHOLD && Right_white_line<THRESHOLD)               // Is middle Whiteline is within threshold limit
	{
		//flag=1;
		forward();
		velocity(VELOCITY_MAX,VELOCITY_MAX);      // Run robot at max velocity
		//lcd_print (2,1,VELOCITY_MAX,3);
		//lcd_print (2,5,VELOCITY_MAX,3);
	}
	else if(Center_white_line>THRESHOLD && Left_white_line<THRESHOLD && Right_white_line<THRESHOLD)               // Is middle Whiteline is within threshold limit
	{
		//flag=1;
		forward();
		velocity(VELOCITY_MAX,VELOCITY_MAX);      // Run robot at max velocity
		
	}


	
	else if(Center_white_line<THRESHOLD && Left_white_line<THRESHOLD && Right_white_line>THRESHOLD)  // Is left Whiteline is not within threshold limit
	{
		//	flag=1;
		forward();
		velocity(VELOCITY_MAX,VELOCITY_MIN);      // Run robot left wheel at max velocity and right wheel
		
	}
	
	else if(Center_white_line>THRESHOLD && Left_white_line<THRESHOLD && Right_white_line>THRESHOLD)  // Is left Whiteline is not within threshold limit
	{
		//	flag=1;
		forward();
		velocity(VELOCITY_MAX,VELOCITY_MIN);      // Run robot left wheel at max velocity and right wheel
		
	}

	
	else if(Center_white_line<THRESHOLD && Left_white_line>THRESHOLD && Right_white_line<THRESHOLD ) // Is right Whiteline is not within threshold limit
	{
		//flag=1;
		forward();
		velocity(VELOCITY_MIN,VELOCITY_MAX);      // Run robot right wheel at max velocity and left wheel
		
	}
	else if(Center_white_line>THRESHOLD && Left_white_line>THRESHOLD && Right_white_line<THRESHOLD ) // Is right Whiteline is not within threshold limit
	{
		//flag=1;
		forward();
		velocity(VELOCITY_MIN,VELOCITY_MAX);      // Run robot right wheel at max velocity and left wheel
		
	}


	else if(Center_white_line>THRESHOLD && Left_white_line>THRESHOLD && Right_white_line>THRESHOLD)
	                                // if all Whiteline sensor are not within threshold limit    
	{	buzzer_beep();
		
		stop_pos();   
		//velocity(VELOCITY_LOW,VELOCITY_LOW);      // stop the robot
		_delay_ms(1300);
	//	lcd_print(2,1,path1.path[l],3);	
		l++;
		
		if(stage==2)
			{	
				servo100();
				servo101();
						
			}
			
			if(stage==3)
			{	unsigned char count=0;
				unsigned char i;
				if(path1.path[t]==2 )
				{	
					init_devices_pos();
					left_degrees(100);
					stop_pos();
					_delay_ms(500);
					dir=3;
					
				}	
				else if(path1.path[t]==48 )
				{
					init_devices_pos();
					left_degrees(100);
					stop_pos();
					_delay_ms(500);
					dir=1;
					
				}	
				
				for ( i=0;i<b;i++)
				{
					
					if(path1.path[t]==blue_nodes[i])
					{
						if (path1.path[t]==blue_nodes[i+1])
						{	
							count++;
						}
						count++;
						break;
					}
				}
				if (count>0)
				{buzzer_beep();
					buzzer_beep();
					
				}
				if(count==1)
				{
					if(blue_side[i]==100)
					{
						servo100();
					}
					else if(blue_side[i]==101)
					{
						servo101();
					}
					
				}
				if(count==2)
				{
					servo100();
					servo101();
				}
				count=0;
			}
			
			init_devices();
			direction();
			
	}


 
}
