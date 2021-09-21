#include<stdio.h>
#include<Windows.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#define screen_x 80
#define screen_y 25
#define scount 18
#define esc 27
/////////////////////////////////////////////////////////////////////
///////////////////PROTORYPE FUNCTION ZONE///////////////////////////
void setcursor(bool visible);
int setConsole();
void clearbuffer();
void init_star();
void fill_buffer_to_console();
void fill_star_to_buffer();
void star_fall();
//////////////////////////////////////////////////////////////////////
//////////////////////GLOBAL VARIABLE ZONE////////////////////////////
unsigned int score = 0;
struct starfall
{
    int x;
    int y;
};
struct starfall star[scount];
HANDLE wHnd;
CHAR_INFO consoleBuffer[screen_x * screen_y];
COORD bufferSize = {screen_x,screen_y-1};
COORD characterPos = {0,0};
SMALL_RECT windowSize = {0,0,screen_x,screen_y};
//////////////////////////////////////////////////////////////////////
//////////////////////////////MAIN////////////////////////////////////
int main()
{
    char ch;
    setcursor(0);
    setConsole(screen_x,screen_y);
    init_star();
    fill_star_to_buffer();
    fill_buffer_to_console();
    while(ch!=27)
    {
        if(kbhit())
        {
            ch=getch();
            if(ch==esc)
            {
                break;
            }
        }
        clearbuffer();
        star_fall();
        fill_star_to_buffer();
        fill_buffer_to_console();
        Sleep(100);
    }
    return 0;
}
//////////////////////////////////////////////////////////////////////
//////////////////////////FUNCTION////////////////////////////////////
void setcursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 18;
    SetConsoleCursorInfo(console,&lpCursor);//0คือปิด 1 คือเปิด
}
int setConsole(int x, int y)
{
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleWindowInfo(wHnd,TRUE,&windowSize);
    SetConsoleScreenBufferSize(wHnd,bufferSize);
}
void clearbuffer()
{
    for(int y=0;y<screen_y;++y)
    {
        for(int x=0;x<screen_x;++x)
        {
            consoleBuffer[x+screen_x * y].Char.AsciiChar = ' ';
        }
    }
}
void init_star()
{
    int x,y;
    srand(time(NULL));
    for(int i=0;i<18;i++)
    {
        star[i].x=rand()%81;
        star[i].y=(rand()%7)+1;
    }
}
void fill_buffer_to_console()
{
    WriteConsoleOutputA(wHnd, consoleBuffer, bufferSize, characterPos, &windowSize);
}
void star_fall()
{
    int i;
    for(i=0;i<scount;i++)
    {
        if(star[i].y>=screen_y-1)
        {
            star[i].x=rand()%screen_x;
            star[i].y=1;
        }
        else
        {
            star[i].y=star[i].y+1;  
        }
    }
}
void fill_star_to_buffer()
{
    for(int i=0;i<18;i++)
    {
        consoleBuffer[star[i].x+80 * star[i].y].Char.AsciiChar = '*';
        consoleBuffer[star[i].x+80 * star[i].y].Attributes=7;
    }
}