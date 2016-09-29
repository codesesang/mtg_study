/*  Version: 2012.6.15
 *
 * File:   clccclcc_tg2.h
 * Author: clccclcc
 *
 * Start From 2009.5.30
 */

/*  버젼 히스토리 

# 2012.6.5 
- 윈도우 전용 2인 키보드 구현(김시훈)


# 2010.6.15 
- For XP,Vista,Windows 7
- double buffering 지원
- 텍스트 컬러(배경,글자색) 출력함수 지원 _DrawTextColor()
- 전체 콘솔의 컬러 지정 : _SetColor(0xf1)
	
*/


#ifndef _CLCCCLCC_TG2_H
#define	_CLCCCLCC_TG2_H

#ifdef	__cplusplus
extern "C" {
#endif
    

    //#define _LINUX_  //curses lib
    //#define _LINUX1_ // standard c
    #define _MSWINDOWS_ // consol api

    ////////////////////////////////////////////
    // Window

    void _BeginWindow();
    void _EndWindow();

	// I/O functions
 #ifdef _MSWINDOWS_
	int _SetColor(int color);
#endif

	void _DrawText(int x,int y,char* msg);
	void _Invalidate();
#ifdef _MSWINDOWS_
	void _DrawTextOrg(int x,int y,char* msg);
	void _DrawTextColorOrg(int x,int y,char* msg,int color);

	void _DrawTextOrg(int x,int y,char* msg);
	void _DrawTextColor(int x,int y,char* msg,int color); 

	void _InvalidateBack();
	
	void _BitBlt();
#endif

#ifdef _LINUX_
    void _DrawChar(int x,int y,int key);
    void _ShowCharCode();    
#endif

    extern void Draw();


    // Key input
    char _GetKey();

#ifdef _MSWINDOWS_
	int _KeyState(char key); //added by  2012.6.3
#endif

    // Time control
    long _GetTickCount();
    void _Delay(int time);

	// messagebox 
	void _MessageBox(int x,int y,int w,int h,char* msg);
 #ifdef _MSWINDOWS_
	void _MessageBoxEx(int x,int y,int w,int h,char* msg);
	void _MessageBoxColor(int x,int y,int w,int h,char* msg,int color);
	void _MessageBoxExColor(int x,int y,int w,int h,char* msg,int color);	
#endif

	// OS Special Functions
 
 

#ifdef	__cplusplus
}
#endif

#endif	/* _CLCCCLCC_TG2_H */

