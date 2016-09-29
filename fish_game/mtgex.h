
// last update  2013.5.27.b   by clccclcc

#ifndef _CLCCCLCC_MTG2EX_H
#define	_CLCCCLCC_MTG2EX_H

#include "mtg.h"

#ifdef	__cplusplus
extern "C" {
#endif



#define MTG_PAINT		0x0001
#define MTG_KEYDOWN		0x0002
#define MTG_TIMER		0x0003
#define MTG_CREATE		0x0004
#define MTG_DESTROY		0x0005


void MTGRun();
int MTGExit();

int MTGProc(int msg,int wparam,long lparam);

int MTGSetTimer(int id,int time);
int MTGKillTimer(int id);

int MTGSetColor(int color);
void MTGTextOut(int x,int y,char* msg);
void MTGTextOutColor(int x,int y,char* msg,int color);
void MTGInvalidate();


void MTGSleep(int time);

void MTGPrint(int x,int y,char* msg);
void MTGPrintColor(int x,int y,char* msg,int color);

void MTGMessageBox(int x,int y,int w,int h,char* msg);
void MTGMessageBoxEx(int x,int y,int w,int h, char* msg);
void MTGMessageBoxColor(int x,int y,int w,int h,char* msg,int color);

int MTGGetKeyState(char key);


#ifdef	__cplusplus
}
#endif

#endif

