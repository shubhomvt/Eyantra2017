

void array_init()
{
	for(int i=0;i<=10;i++)
	{
		blue_nodes[i]=0;
		green_nodes[i]=0;
	}
	for(int i=0;i<=20;i++)
	{
		blue_side[i]=0;
		green_side[i]=0;
	}
}
void do_task()
{	
	if(task==1)//red
	{	
		for(int i=0;i<=150;i++)   //back
		{
			PORTB=PORTB|0x20;//0010 0000 pb5
			_delay_ms(0.5);
			PORTB=PORTB & 0xDF;//1101 1111
			_delay_ms(19.5);
			
		}


		for(int i=0;i<=150;i++)  //front
		{
			PORTB=PORTB|0x20;//0010 0000 pb5
			_delay_ms(0.85);
			PORTB=PORTB & 0xDF;//1101 1111
			_delay_ms(19.15);
			
		}
		
		
	}
	else if(task==2)//green
	{
		green_nodes[gn]=path1.path[t];
		green_side[gs]=side;
		gn++;
		gs++;
		
	}
	if(task==3)
	{
		blue_nodes[b]=path1.path[t];
		blue_side[bs]=side;
		b++;
		bs++;
	}		
	 
	//buzzer_beep();
		
	/*data[0]=71;
	data[1]=60;
	data[2]=2;
	data[3]=8;
	data[4]=15;
	data[5]=100;
	data[6]=255;
	data[7]=0;*/
	
	/*for(int i=0;i<20;i++)
	{	if(data[i]==0)
		{
			break;
		}
		USARTWriteChar(data[i]);
		_delay_ms(1000);
	}*/
	
	
	/*if(red_nodes[0]==45&& red_nodes[1]==44)
	{
		buzzer_beep();
	}
	if(red_side[0]==1 && red_side[1]==1)
	{
		buzzer_beep();
	}*/
	task=0;
	side=0;
	PORTC=PORTC& 0x8F;
	//buzzer_beep();
}

void direction(void)
{	init_devices_buzzer();
	int w=0;
	if(t==max)
	{	if(stage==1)
		{	
			if(dir==1)
			{	//buzzer_beep();
				right_degrees(190);
				stop_pos();
				_delay_ms(500);
			}
			else if(dir==2)
			{
				right_degrees(100);
				stop_pos();
				_delay_ms(500);
			}
			else if(dir==4)
			{
				left_degrees(100);
				stop_pos();
				_delay_ms(500);
			}
			
			dir=3;
		//	lcd_print(2,4,dir,3);
			back_mm(100);
			stop_pos();
			_delay_ms(500);
			g=1;
			buzzer_beep();
		}
		else if(stage==2)

		{	
			
			
			_delay_ms(100);
			while (1)
			{
				if(next>1)
				{
					break;
					
				}
			}
			
			green_nodes[0]=55;
			green_nodes[gn]=56;
			green_side[0]=55;
			green_side[gs]=56;
			for(int i=0;i<=10;i++)
			{	if(green_nodes[i]==0)
				{
					
					break;
					
				}
				USARTWriteChar(green_nodes[i]);
				
				_delay_ms(1000);
				//buzzer_beep();
				
			}
			buzzer_on();
			_delay_ms(1000);
			buzzer_off();
			for(int i=0;i<10;i++)
			{	if(green_side[i]==0)
				{
					break;
				}
				USARTWriteChar(green_side[i]);
				_delay_ms(1000);
				//buzzer_beep();
			}
			buzzer_on();
			_delay_ms(1000);
			buzzer_off();
			blue_nodes[0]=53;
			blue_nodes[b]=54;
			blue_side[0]=53;
			blue_side[bs]=54;
			for(int i=0;i<=10;i++)
			{	if(blue_nodes[i]==0)
				{
					
					break;
					
				}
				USARTWriteChar(blue_nodes[i]+7);
				
				_delay_ms(1000);
				//buzzer_beep();
				
			}
			buzzer_on();
			_delay_ms(1000);
			buzzer_off();
			for(int i=0;i<10;i++)
			{	if(blue_side[i]==0)
				{
					break;
				}
				if(blue_side[i]==100)
				{
					USARTWriteChar(101);
					_delay_ms(1000);
				}
				else if(blue_side[i]==101)
				{
					USARTWriteChar(100);
					_delay_ms(1000);
				}
				
				//buzzer_beep();
			}
			buzzer_on();
			_delay_ms(1000);
			buzzer_off();
			while (1)
			{
				if(next>3)
				{	buzzer_beep();
					buzzer_beep();
					break;
				}
				
			}
			
			g=1;
		/*	buzzer_beep();
			buzzer_beep();
			/*buzzer_on();
			_delay_ms(1000);
			buzzer_off();*/
			
			
		}
		else if(stage==3)
		{
			g=1;
			/*buzzer_beep();
			buzzer_beep();
			buzzer_beep();*/
		
		}		
		else if(stage==4)
		{
			g=1;
		}		
		
		
		
	}
	if(t<max)
	{
		w=(path1.path[t]-path1.path[t+1]);
		t++;
		//lcd_print(2,9,w,3);
		//buzzer_beep();
		
		/*lcd_port_config ();
			init_devices();
			lcd_set_4bit();
			lcd_init();
			
		
		lcd_print(2,1,w,3);
		_delay_ms(4000);*/
		switch (w)
		{ 
			case 1:
			
				if(dir==1)
				success(3);
				else if(dir==3)
				success(2);
				else if(dir==4)
				success(1);
				
				dir=4;
				break;
			
			case (-1):
			
				if(dir==1)
				success(2);
				else if(dir==2)
				success(1);
				else if(dir==3)
				success(3);
				
				dir=2;
				break;
				
			
			case (7):
			
				if(dir==1)
				success(1);
				else if(dir==2)
				success(3);
				else if(dir==4)
				success(2);
				
				dir=1;
				break;
				
			
			case (-7):
			
				if(dir==2)
				success(2);
				else if(dir==3)
				success(1);
				else if(dir==4)
				success(3);
				
				dir=3;
				break;
				
			
			
		}
//		lcd_print(2,5,dir,2);
	}
}


void success(int x)
{
	unsigned char Left_white_line = 0;
	unsigned char Center_white_line = 0;
	unsigned char Right_white_line = 0;
	
	buzzer_on();
	_delay_ms(500);
	buzzer_off();
	
	switch (x)
	{
		case 1:
		velocity(VELOCITY_MAX,VELOCITY_MAX+q);      // Run robot at max velocity
		forward();
		_delay_ms(300);
		break;
		case 2:
		velocity(VELOCITY_MAX,VELOCITY_MIN+q);      // Run robot left wheel at max velocity and right wheel
		right();
		_delay_ms(900);
		
		break;
		case 3:
		velocity(VELOCITY_MIN,VELOCITY_MAX+q);      // Run robot right wheel at max velocity and left wheel
		left();
		_delay_ms(900);
		break;
		
	}
	
	while(1)
	{
		
		Left_white_line = ADC_Conversion(3);	//Getting data of Left WL Sensor
		Center_white_line = ADC_Conversion(2);	//Getting data of Center WL Sensor
		Right_white_line = ADC_Conversion(1);	//Getting data of Right WL Sensor

		

		//		print_sensor(1,1,3);	//Prints value of White Line Sensor1
		//print_sensor(1,5,2);	//Prints Value of White Line Sensor2
		//	print_sensor(1,9,1);	//Prints Value of White Line Sensor3

		if(Center_white_line<THRESHOLD && Left_white_line<THRESHOLD && Right_white_line<THRESHOLD)
		{	buzzer_on();
			_delay_ms(500);
			buzzer_off();
			switch (x)
			{
				case 1:
				velocity(VELOCITY_MAX,VELOCITY_MAX+q);      // Run robot at max velocity
				forward();
				_delay_ms(200);
				break;
				case 2:
				velocity(VELOCITY_MAX,VELOCITY_MIN+q);      // Run robot left wheel at max velocity and right wheel
				right();
				_delay_ms(500);
				
				break;
				case 3:
				velocity(VELOCITY_MIN,VELOCITY_MAX+q);      // Run robot right wheel at max velocity and left wheel
				left();
				_delay_ms(500);
				break;
				
			}
		}


		

		else if((Left_white_line>THRESHOLD)) //&& (flag==0))
		{
			//flag=1;
			velocity(VELOCITY_MIN,VELOCITY_MAX+q);      // Run robot right wheel at max velocity and left wheel
			left();
			_delay_ms(300);
			break;
		}

		else if((Right_white_line>THRESHOLD))// && (flag==0))
		{
			//	flag=1;
			
			velocity(VELOCITY_MAX,VELOCITY_MIN +q);      // Run robot left wheel at max velocity and right wheel
			right();
			_delay_ms(300);
			break;
		}
		else if(Center_white_line>THRESHOLD)
		{
			//flag=1;
			velocity(VELOCITY_MAX,VELOCITY_MAX+q);      // Run robot at max velocity
			forward();
			_delay_ms(300);
			break;
		}
		
		

	}
	
}