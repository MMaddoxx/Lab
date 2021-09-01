#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
void drawship();
void erase_ship();
int main()
{
    char t;
    int x=1,y=20;
    printf("Press wasd to move and press x to quit");
    drawship(x,y);
    do
    {
        if(kbhit())
        {
            t=getch();
            if(t=='a')
            {
                if(x>1)
                {
                    erase_ship(x,y);
                    drawship(--x,y);
                    Sleep(500);
                }
            }
            if(t=='d')
            {
                if(x<80)
                {
                    erase_ship(x,y);
                    drawship(++x,y);
                    Sleep(500);
                }
            }
            if(t=='w')
            {
                if(y>3)
                {
                    erase_ship(x,y);
                    drawship(x,--y);
                    Sleep(500);
                }
            }
            if(t=='s')
            {
                erase_ship(x,y);
                drawship(x,++y);
                Sleep(500);
            }
        }
    } while (t!='x');
    return 0;
}
void drawship(int x , int y)
{
    COORD c ={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    printf("<-o->");
}
void erase_ship(int x, int y)
{
    COORD c ={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    printf("     ");
}