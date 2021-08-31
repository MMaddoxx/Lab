#include<stdio.h>
#include<windows.h>
#include<conio.h>
void drawship();
int main()
{
    int a,b;
    printf("Input location of ship : ");
    scanf("%d %d",&a,&b);
    drawship(a,b);
    getch();
}
void drawship(int x , int y)
{
    COORD c ={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    printf("<-o->");
}