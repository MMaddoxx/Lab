#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<stdbool.h>
#include<stdlib.h>
void gotoxy(int x,int y);
void draw_ship(int x, int y);
void setcursor(bool visible);
void setcolor(int fg,int bg);//fg คือสีตัวอักษร bg คือพื้นหลัง 
void erase_ship();
int main()
{
    setcursor(0);
    char ch=' ',mem;
    int x=38,y=20;
    draw_ship(x,y);
    do
    {
        if(kbhit())
        {
            ch=getch();
            do
            {
                if(kbhit())
                {
                    mem=getch();
                    if(mem=='s')//หยุดถ้าพิมพ์s
                    {
                        break;
                    }
                    else if(mem=='a')
                    {
                        ch='a';
                    }
                    else if(mem=='d')
                    {
                        ch='d';
                    }
                }
                if(ch=='a')
                {
                    if(x>1)
                    {
                        erase_ship(x,y);
                        draw_ship(--x,y);
                        if(x==1)//หยุดถ้าติดขอบ
                        {
                            break;
                        }
                    }
                }
                if(ch=='d')
                {
                    if(x<80)
                    {
                        erase_ship(x,y);
                        draw_ship(++x,y);
                        if(x==80)//หยุดถ้าติดขอบ
                        {
                            break;
                        }
                    }
                }
                fflush(stdin);
                Sleep(200);
            }while (ch!='s');
        }
    } while (ch!='x');
    return 0;
}
void gotoxy(int x,int y)
{
    COORD c={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void draw_ship(int x,int y)
{
    setcolor(4,0);
    gotoxy(x,y);
    printf("<-0->");
}
void setcursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console,&lpCursor);//0คือปิด 1 คือเปิด
}
void setcolor(int fg,int bg)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,bg*16+fg);
}
void erase_ship(int x, int y)
{
    COORD c ={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    printf("     ");
}