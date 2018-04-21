#include "RemoteTask.h"
#include "ControlMain.h"
#include "UltraSonic.h"
uint32_t 	USfdb1,USfdb2,USfdb3;//USfdb1-front,USfdb2-left,USfdb3-right
uint32_t    str;//determine what's the strategy
static int i = 0;//timer
void straight(void)
{
	SetCMState(1,0,0,8,8,8);
}
void right(void)
{
	SetCMState(0,1,0,8,8,8);
}
void left(void)
{
	SetCMState(0,-1,0,8,8,8);
}
void back(void)
{
	SetCMState(-1,0,0,8,8,8);
}
void rightforward(void)
{
	SetCMState(1,1,0,8,12,8);
}
void leftforward(void)
{
	SetCMState(-1,1,0,8,8,8);
}
void rotate_clock(void)
{
	SetCMState(0,0,1,8,8,8);
}
void rotate_unclock(void)
{
	SetCMState(0,0,-1,8,8,8);
}
void stop(void)
{
	SetCMState(0,0,0,8,8,8);

}
int strategy(uint32_t x,uint32_t y,uint32_t z)//????:???????????60?,????????
{
	uint32_t m;
	uint32_t front = x;
	uint32_t right = y;
	uint32_t left = z;
	if(front >= 150)//?????,??
	{
		m = 0;
	}
	else if(front <=150 && left >= 150 && right>=150)//????,?????,?????,??
	{
		m = 1;
	}
	else if(front >200 && right >=550 && right<=600)//??????,????????
	{
		m = 2;
	}
	else if(front >100 && front <=150 && left >= 150 && right <= 150)//?????,????????
	{	
		m = 3;
	}
	else if(front <100)//???,??(?????????????)
	{
		m = 4;
	}
	else
	{
		m = 5;
	}
	return m;	
}
void ControlLoopCode(void)
{	
	USfdb1=mm1;
	USfdb2=mm2;
	USfdb3=mm3;
	str = strategy(USfdb1,USfdb2,USfdb3);
	switch (str)
	{
		case 0:
		   straight();;break;

		case 1:
		
	
		   left();
		break;

		case 2:
		rightforward();
		   if(USfdb1<=100)
		   	{right();}
		break;

		case 3:
		   leftforward();
		   if(USfdb1<=100)
		   	{left();}
		break;

	    case 4:
		   back();
		break;

		default:
		   back();
		break;
	}
}
