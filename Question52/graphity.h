#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<process.h>    
#include<unistd.h>     
#define cl system("cls")

void settitle(char *s)
{

    SetConsoleTitle(s);	
}
void gotoxy(long x, long y) 
      {
           COORD pos = {x, y};
           SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
      }
      
void centre()
{
	COORD pos = {30, 10};
           SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void red()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY );
}
void pink()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
}
void green()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN );
}
void yellow()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY );
}
void blue()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
}
//fullscreen
void AltEnter()
{

    keybd_event(VK_MENU,0x38,0,0);

    keybd_event(VK_RETURN,0x1c,0,0);

    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);

    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);

}

void fullscreen()
{
	AltEnter();
}

//font
int GetFontSize(HANDLE windowHandle, COORD *size)
    {
    CONSOLE_FONT_INFOEX font = { sizeof(CONSOLE_FONT_INFOEX) };
 
    if (!GetCurrentConsoleFontEx(windowHandle, 0, &font))
        {
        return 0;
        }
 
    *size = font.dwFontSize;
 
    return 1;
    }
 
int SetFontSize(HANDLE windowHandle, COORD size)
    {
    CONSOLE_FONT_INFOEX font = { sizeof(CONSOLE_FONT_INFOEX) };
 
    if (!GetCurrentConsoleFontEx(windowHandle, 0, &font))
        {
        return 0;
        }
 
    font.dwFontSize = size;
 
    if (!SetCurrentConsoleFontEx(windowHandle, 0, &font))
        {
        return 0;
        }
 
    return 1;
    }
    
void font(long x, long y)
{
	
    
 HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD size;
    // Set up the required window size:
    SMALL_RECT windowSize = {0, 0, 50, 10};
    SetConsoleWindowInfo(h, 1, &windowSize);
    COORD bufferSize = {10, 10};
    SetConsoleScreenBufferSize(h, bufferSize);
 
    if (GetFontSize(h, &size))
        {
        size.X = x;
        size.Y = y;
        SetFontSize(h, size);
        }
}

//animation

COORD cursorpos(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
    {
        return cbsi.dwCursorPosition;
    }
    else
    {
        // The function failed. Call GetLastError() for details.
        COORD invalid = { 0, 0 };
        return invalid;
    }
}

void loading(short n)
{
//save current color
	HANDLE                      m_hConsole;
    WORD                        m_currentConsoleAttr;
CONSOLE_SCREEN_BUFFER_INFO   csbi;

//retrieve and save the current attributes
m_hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
if(GetConsoleScreenBufferInfo(m_hConsole, &csbi))
    m_currentConsoleAttr = csbi.wAttributes;
//
	cl;
	cl;
	pink();
	font(20,40);
	int i;
	for(i=0;i<n;i++)
	{
	centre();
	printf("Loading.");
	sleep(1);
	centre();
	printf("Loading..");
	sleep(1);
	centre();
	printf("Loading...");
	sleep(1);
	cl;
    }
    
    
//set the ttribute to the original one
SetConsoleTextAttribute (
            m_hConsole,
            m_currentConsoleAttr);
	
}
//clearing the screen

void cls()
{
	fullscreen();
	fullscreen();
}
