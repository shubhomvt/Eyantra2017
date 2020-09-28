/*
 * adjescency_matrix.c
 *
 * Created: 24-11-2017 19:26:29
 *  Author: Swathi S
 */

//////RED
//#include <avr/io.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "buzzer.h"


//#define X 49
//#define Y 7

unsigned char start=22;/////////////////red changed
unsigned char des=6;
unsigned char dir=2; 
 unsigned char g=0;
 unsigned char max =0;




struct Path_Array
{
unsigned char path[15];
};
struct Path_Array path1;




struct Path_Array main_function7(unsigned char start, unsigned char finish)
{
	struct Path_Array path;
unsigned char friend; 
signed char k =(((start-1)/7)-((finish-1)/7));
if(k>0)
{
	friend=((k*7)+finish);
}
else
{
	friend=(finish-(k*(-1))*7);
}
signed char l=0;
unsigned char m=0;
 unsigned char st =start;
l=(friend - start);

if(l>0)
{
	for(unsigned char i = 0;i<=l;i++)
	{path.path[i]=st;
	st++;
	}
	if(k>0)	
	{   
		if(friend > finish)
		{
			m=((friend-finish)/7);
			for(unsigned char i=0;i<m;i++)
			{
				path.path[l+i+1]=friend-((7*i)+7);
			}
		}
		
		else
		
		{
			m=((finish-friend)/7);
			//m =((friend-1)/7);
			for(unsigned char i=0;i<(m) ;i++)
			{
				path.path[l+i+1]=friend+((7*i)+7);
			}
		}
		
	}
	else if(k<0)
	{ if(friend > finish)
		{	
			m=((friend-finish)/7);
			for(unsigned char i=0;i<m;i++)
			{
				path.path[l+i+1]=friend-((7*i)+7);
			}
		}
		
		else
		
		{
			m=((finish-friend)/7);
			//m =((friend-1)/7);
			for(unsigned char i=0;i<(m) ;i++)
			{
				path.path[l+i+1]=friend+((7*i)+7);
			}
		}		
		
	}
	
}
else
{ l=(l*(-1));
	for(unsigned char i = 0;i<=(l);i++)
	{path.path[i]=st;
		st--;
	}
	if(k>0)
	{  
		if(friend > finish)
		{
			m=((friend-finish)/7);
			for(unsigned char i=0;i<m;i++)
			{
				path.path[l+i+1]=friend-((7*i)+7);
			}
		}
		
		else
		
		{
			m=((finish-friend)/7);
			//m =((friend-1)/7);
			for(unsigned char i=0;i<(m) ;i++)
			{
				path.path[l+i+1]=friend+((7*i)+7);
			}
		}
	}
	else  if(k<0)
	{
		if(friend > finish)
		{
			m=((friend-finish)/7);
			for(unsigned char i=0;i<m;i++)
			{
				path.path[l+i+1]=friend-((7*i)+7);
			}
		}
		
		else
		
		{
			m=((finish-friend)/7);
			//m =((friend-1)/7);
			for(unsigned char i=0;i<(m) ;i++)
			{
				path.path[l+i+1]=friend+((7*i)+7);
			}
		}
		
	}
	
}
 max = l+m;
 for(unsigned char i=(l+m+1);i<15;i++)
 {
	 path.path[i]=0;
 }

	
	return path;
}
