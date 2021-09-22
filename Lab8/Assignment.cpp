#include<stdio.h>
#include<Windows.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#define screen_x 80
#define screen_y 25
#define scount 40
#define esc 27
///////////////////PROTORYPE FUNCTION ////////////////////////////////
int setConsole();//ตั้งกรอบหน้าจอ
int setMode();
void setcursor(bool visible);//เปิดปิดcursor
void clearbuffer();//ล้างbuffer 
void init_star();//สุ่มตอนเริ่มต้น
void fill_buffer_to_console();//เอาbufferขึ้นจอ
void fill_star_to_buffer();//เอาดาวไปใส่ในbuffer
void star_fall();
void draw_ship(int x,int y,int color);
void gotoxy(SHORT x,SHORT y);
void setcolor(int fg,int bg);
char cursor(SHORT x,SHORT y);
//////////////////////GLOBAL VARIABLE/////////////////////////////////
unsigned int score = 0;
struct starfall
{
    int x;
    int y;
};
struct starfall star[scount];
bool playing = true;
HANDLE wHnd;
HANDLE rHnd;
CHAR_INFO consoleBuffer[screen_x * screen_y];
COORD bufferSize = {screen_x,screen_y};
COORD characterPos = {0,0};
SMALL_RECT windowSize = {0,0,screen_x-1,screen_y-1};
DWORD fdwMode;
DWORD numEvents = 0;
DWORD numEventsRead = 0;
//////////////////////////////MAIN////////////////////////////////////
int main()
{
    char ch;
    int posx,posy,color=7,hit=0;
    setcursor(0);
    setMode();
    setConsole();
    init_star();
    fill_star_to_buffer();
    fill_buffer_to_console();
    while(playing)
    {
        GetNumberOfConsoleInputEvents(rHnd,&numEvents);
        if(numEvents!=0)
        {
            INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
            ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);
            for(DWORD i=0;i<numEventsRead;++i)
            {
                if(eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown == true)
                {
                    if(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
                    {
                        playing = false;
                    }
                    if(eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'c')
                    {
                        srand(time(NULL));
                        color=(rand()%14)+1;
                    }
                }
                else if (eventBuffer[i].EventType==MOUSE_EVENT)
                {
                    posx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
                    posy = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
                    if(eventBuffer[i].Event.MouseEvent.dwButtonState&FROM_LEFT_1ST_BUTTON_PRESSED)
                    {
                        srand(time(NULL));
                        color=(rand()%14)+1;
                    }           
                }
            }
            delete[] eventBuffer;
        }
        clearbuffer();
        star_fall();
        fill_star_to_buffer();
        fill_buffer_to_console();
        if(cursor(posx,posy)=='*'||cursor(posx+1,posy)=='*'||cursor(posx+2,posy)=='*'||cursor(posx-1,posy)=='*'||cursor(posx-2,posy)=='*')
        {
            Beep(400,200);
            init_star();
            fill_star_to_buffer();
            fill_buffer_to_console();
            hit++;
            if(hit>=10)
            {
                playing=false;
            }       
        }
        else
        {
            draw_ship(posx,posy,color);
        }
        Sleep(100);
    }
    return 0;
}
//////////////////////////FUNCTION////////////////////////////////////
void setcursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 18;
    SetConsoleCursorInfo(console,&lpCursor);//0คือปิด 1 คือเปิด
}
int setConsole()
{
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleWindowInfo(wHnd,TRUE,&windowSize);
    SetConsoleScreenBufferSize(wHnd,bufferSize);
}
int setMode()
{
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT ;
    SetConsoleMode(rHnd,fdwMode);
    return 0;
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
    for(int i=0;i<40;i++)
    {
        star[i].x=rand()%80;
        star[i].y=(rand()%5)+1;
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
            star[i].y=0;
        }
        else
        {
            star[i].y=star[i].y+1;  
        }
    }
}
void fill_star_to_buffer()
{
    for(int i=0;i<40;i++)
    {
        consoleBuffer[star[i].x+screen_x * star[i].y].Char.AsciiChar = '*';
        consoleBuffer[star[i].x+screen_x * star[i].y].Attributes=7;
    }
}
void draw_ship(int x,int y,int color)
{
    gotoxy(x-2,y);
    setcolor(color,0);
    printf("<-0->");
}
void gotoxy(SHORT x,SHORT y)
{
    COORD c={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void setcolor(int fg,int bg)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,bg*16+fg);
}
char cursor(SHORT x,SHORT y)
{
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    char buf[2];
    COORD c ={x,y};
    DWORD num_read;
    if(!ReadConsoleOutputCharacter(hStd,(LPTSTR)buf,1,c,(LPDWORD)&num_read))
    {
        return '\0';
    }
    else
    {
        return buf[0];
    }
}