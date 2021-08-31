#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
void drawship();
int main()
{
    int a,b=20;
    for (a=1;a<=80;a++)
    {
        drawship(a,b);
        Sleep(5);
        if(a<80)
        {
            system("cls");
        }
    }
    getch();
}
void drawship(int x , int y)
{
    COORD c ={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    printf("<-o->");
}
