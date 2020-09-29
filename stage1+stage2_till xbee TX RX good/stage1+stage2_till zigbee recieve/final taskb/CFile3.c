int t=0;
int dir=1;///green home
void direction(void);


void direction(void)
{	int w=0;
	if(t=max)
	{
		g=1;
	}
	while(t<max)
	{
		w=path[t]-path[t+1];
		t++;
		switch (w)
		{
			case 1:
			{
				if(dir==1)
				success(3);
				else if(dir==2)
				success(2);
				else if(dir==4)
				success(1);
			
				dir=4;
				break;
			}	
			case (-1):
			{
				if(dir==1)
				success(2);
				else if(dir==2)
				success(1);
				else if(dir==3)
				success(3);
				
				dir=2;
				break;
				
			}	
			case (7):
			{
				if(dir==1)
				success(1);
				else if(dir==2)
				success(3);
				else if(dir==4)
				success(2);
				
				dir=1;
				break;
				
			}
			case (-7):
			{
				if(dir==2)
				success(2);
				else if(dir==3)
				success(1);
				else if(dir==4)
				success(3);
				
				dir=3;
				break;
				
			}	
			
		}
	}
}

void success(int x)
{
	switch (x)
	{
		case 1:
		forward();
		break;
		case 2:
		soft_right();
		break;
		case 3:
		soft_left();
		break;
				
	}
	for(;;)
	//////////////////////////////////6
}