
#include <stdlib.h>
#include <time.h>

#include "mtg.h"

#include "mtgex.h"

//-----------------------------------------------------------------------------------------------//
// Local define
#define MTG_MAX_TIMER 10

struct S_MTG_TIMER
{
	int on; //1:on -1:off
	int time;
	long oldT;	
};

struct S_MTG_TIMER g_aTimer[MTG_MAX_TIMER];
int g_mtg_on=1;

//-----------------------------------------------------------------------------------------------//

int GameMainEx();
 
////////////////////////////////////////////////////////////
// public wrap interface 
void MTGSleep(int time)
{
	_Delay(time);
}
void MTGTextOut(int x,int y,char* msg)
{
	_DrawText(x,y,msg);
}
void MTGTextOutColor(int x,int y,char* msg,int color)
{
	_DrawTextColor(x,y,msg,color);
}

void MTGInvalidate()
{
	_Invalidate();
}
void MTGPrint(int x,int y,char* msg)
{
	_DrawTextOrg(x,y,msg);
}
void MTGPrintColor(int x,int y,char* msg,int color)
{
	_DrawTextColorOrg(x,y,msg,color);
}
int MTGSetColor(int color)
{
	return _SetColor(color);
}
void MTGMessageBox(int x,int y,int w,int h,char* msg)
{
	_MessageBox(x,y,w,h,msg);
	_Invalidate();
}
void MTGMessageBoxEx(int x,int y,int w,int h, char* msg)
{
	_MessageBoxEx( x, y, w, h,msg);
	_Invalidate();
}
void MTGMessageBoxColor(int x,int y,int w,int h,char* msg,int color)
{

	_MessageBoxColor(x,y,w,h,msg,color);
	_Invalidate();
}
int MTGGetKeyState(char key)
{
	return _KeyState(key);
}

//////////////////////////////
//
int MTGExit()
{
	g_mtg_on=-1;

	return 0;
}
int MTGSetTimer(int id,int time)
{
	if(MTG_MAX_TIMER <= id)
	{
		return -1;
	}

	g_aTimer[id].on=1;
	g_aTimer[id].time=time;
	g_aTimer[id].oldT=_GetTickCount();

	return 0;
}
int MTGKillTimer(int id)
{
	if(MTG_MAX_TIMER <= id)
	{
		return -1;
	}

	g_aTimer[id].on=-1;

	return 0;
}
void MTGRun()
{
	
	_BeginWindow();

	GameMainEx();

	_EndWindow();

}
///////////////////////////////////////////////////////////////////
int _MTGCheckTimer()
{
	int i;
	long newT;

	newT=_GetTickCount();
	for(i=0;i<MTG_MAX_TIMER;i++)
	{
		if(1==g_aTimer[i].on)
		{			
			if(g_aTimer[i].time <= (newT - g_aTimer[i].oldT))
			{
				g_aTimer[i].oldT=newT;
				MTGProc(MTG_TIMER,i,0);
			}
		}
	}

	return 0;
}

void _MTGIniApp()
{
	int i;
	
	//int timer
	for(i=0;i<MTG_MAX_TIMER;i++)
	{
		g_aTimer[i].on=-1;
	}
}



int GameMainEx()
{
	char key;
	
	_MTGIniApp();

	MTGProc(MTG_CREATE,0,0);
	_Invalidate();
	while(1)
	{

		_MTGCheckTimer();
		
		key=_GetKey();if(-1==key) continue;
		MTGProc(MTG_KEYDOWN,key,0);

		if(-1==g_mtg_on)
		{
			MTGProc(MTG_DESTROY,0,0);
			break;
		}
	}

	return 0;
}
void Draw()
{
	MTGProc(MTG_PAINT,0,0);
}


