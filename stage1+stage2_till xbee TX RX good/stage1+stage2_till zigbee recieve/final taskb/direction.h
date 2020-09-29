int t=0;


void array_init()
{
	for(int i=0;i<=10;i++)
	{
		red_nodes[i]=0;
		blue_nodes[i]=0;
	}
	for(int i=0;i<=20;i++)
	{	
		red_side[i]=0;
		blue_side[i]=0;
	}
}

void do_task()
{	
	if(task==1)
	{	
		red_nodes[r]=path1.path[t];
		red_side[rs]=side;
		r++;
		rs++;
		
	}
	else if(task==3)
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
	//buzzer_beep();
}

void direction(void)
{	buzzer_pin_config();
	int w=0;
	if(t==max)
	{	
		if(stage==1)
		{
			if(dir==1)
			{	//buzzer_beep();
				right_degrees(180);
				stop1();
				_delay_ms(500);
			}
			else if(dir==2)
			{
				right_degrees(90);
				stop1();
				_delay_ms(500);
			}
			else if(dir==4)
			{
				left_degrees(90);
				stop1();
				_delay_ms(500);
			}
			
			dir=3;
			lcd_print(2,4,dir,3);
			_delay_ms(1000);
			g=1;
		}
		else if (stage==2)
		{	buzzer_beep();
			init_devices_xbee();
			_delay_ms(100);
			red_nodes[0]=51;
			red_nodes[r]=52;
			red_side[0]=51;
			red_side[rs]=52;
			for(int i=0;i<=10;i++)
			{	if(red_nodes[i]==0)
				{
					
					break;
					
				}
				USARTWriteChar(red_nodes[i]);
				
				_delay_ms(1000);
				buzzer_beep();
				
			}
			
			for(int i=0;i<10;i++)
			{	if(red_side[i]==0)
				{
					break;
				}
				USARTWriteChar(red_side[i]);
				_delay_ms(1000);
				buzzer_beep();
			}
			
			
			blue_nodes[0]=53;
			blue_nodes[b]=54;
			blue_side[0]=53;
			blue_side[bs]=54;
			for(int i=0;i<=10;i++)
			{	if(blue_nodes[i]==0)
				{
					
					break;
					
				}
				USARTWriteChar(blue_nodes[i]);
				
				_delay_ms(1000);
				buzzer_beep();
				
			}
			
			for(int i=0;i<10;i++)
			{	if(blue_side[i]==0)
				{
					break;
				}
				USARTWriteChar(blue_side[i]);
				_delay_ms(1000);
				buzzer_beep();
			}
			
			while (1)
			{
				if(next>2)
				{	buzzer_beep();
					buzzer_beep();
					break;
				}
			}
			stage=3;
			g=1;
			
		}
		
		
		
		
		
		
	}
	if(t<max)
	{
		w=(path1.path[t]-path1.path[t+1]);
		t++;
		lcd_print(2,9,w,3);
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
		lcd_print(2,4,dir,3);
	}
}


void success(int x)
{
	switch (x)
	{
		case 1:
		forward();
		velocity(125,125);
		_delay_ms(100);
		break;
		case 2:
		forward();
		velocity(130,30);
		_delay_ms(1050);
		
		break;
		case 3:
		forward();
		velocity(30,130);
		_delay_ms(1050);
		 break;
		
	}
	
	while(1)
	{
		
		Left_white_line = ADC_Conversion(3);	//Getting data of Left WL Sensor
		Center_white_line = ADC_Conversion(2);	//Getting data of Center WL Sensor
		Right_white_line = ADC_Conversion(1);	//Getting data of Right WL Sensor

		

		print_sensor(1,1,3);	//Prints value of White Line Sensor1
		print_sensor(1,5,2);	//Prints Value of White Line Sensor2
		print_sensor(1,9,1);	//Prints Value of White Line Sensor3

		if(Center_white_line<0x28 && Left_white_line<0x28 && Right_white_line<0x28)
		{
			switch (x)
			{
				case 1:
				forward();
				velocity(125,125);
				_delay_ms(100);
				break;
				case 2:
				forward();
				velocity(130,30);
				_delay_ms(100);
				
				break;
				case 3:
				forward();
				velocity(30,130);
				_delay_ms(100);
				break;
				
			}
		}


		

		else if((Left_white_line<0x28)) //&& (flag==0))
		{
			//flag=1;
			forward();
			velocity(130,30);
			_delay_ms(300);
			break;
		}

		else if((Right_white_line<0x28))// && (flag==0))
		{
			//	flag=1;
			
			forward();
			velocity(30,130);
			_delay_ms(300);
			break;
		}
		else if(Center_white_line>0x28)
		{
			//flag=1;
			forward();
			velocity(135,135);
			_delay_ms(300);
			break;
		}
		
		

	}
	
}