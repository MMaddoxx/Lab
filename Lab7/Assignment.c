#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
unsigned int score = 0;
void gotoxy(int x,int y);
void draw_ship(int x, int y);
void setcursor(bool visible);
void setcolor(int fg,int bg);//fg คือสีตัวอักษร bg คือพื้นหลัง 
void erase_ship(int x, int y);
void firebullet(int x,int y);
void erasebullet(int x,int y);
void draw_ship(int x,int y);
char cursor(int x,int y);
void drawstar(int n);
void scorebox();
int main()
{
    setcursor(0);
    char ch=' ',mem;
    int x=38,y=20,a,b,count=0;
    bool ammo=0,firstdraw=0;
    drawstar(20);
    setcolor(12,0);
    gotoxy(0,21);
    printf("Press A and D to move Ship Press spacebar to fire and Press S  to stop the ship \nPress X to exit You can fire ONLY 1 bullet at the time");
    scorebox();
    draw_ship(x,y);
    do
    {
        if(kbhit())//ถ้าระหว่างขยับกดแป้นพิมพ์เข้ามา
        {
            mem=ch;
            ch=getch();
            if(ch!='s'&&ch!='a'&&ch!='d'&&ch!='x'&&ch!=' ')//เอาไว้ ignore ทุกตัวที่ไม่ใช่ตัวที่เป็นcommand
            {
                ch=mem;//เอามาฝาก
            }
            if(ch==' '&&ammo==0)
            {
                Beep(2500,200);
                a=x+2;
                b=y-1;
                ch=mem;//เอาคืนจะได้ขยับต่อ
                ammo=1;
            }
        }
        if(ch=='a')//ขยับซ้าย
        {
            if(x>7)//ขอบซ้าย
            {
                erase_ship(x,y);
                draw_ship(--x,y);
            }
        }
        if(ch=='d')//ขยับขวา
        {
            if(x<68)//ขอบขวา
            {
                erase_ship(x,y);
                draw_ship(++x,y);
            }
        }
        if(ammo==1&&b>=2)
        {
            erasebullet(a,b);
            if(cursor(a,--b)=='*')
            {
                erasebullet(a,b);//ลบดาว
                ammo=0;
                Beep(600,200);
                score++;
                drawstar(1);
                scorebox();
            }
            else
            {
                firebullet(a,b);
            }      
        }
        if(b==1&&ammo==1)//พอกระสุนถึงขอบก็บลทิ้งแล้วรีเซตให้ยิงนัดใหม่ได้
        {
            erasebullet(a,b);
            Beep(400,200);
            ammo=0;    
        }  
        fflush(stdin);
        Sleep(200);      
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
    setcolor(2,0);
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
void firebullet(int x,int y)
{
    setcolor(6,0);
    gotoxy(x,y);
    printf("^");
    Beep(1500,200);
}
void erasebullet(int x,int y)
{
    gotoxy(x,y);
    printf(" ");
}
void drawstar(int n)
{
    srand(time(NULL));
    int i;
    setcolor(7,0);
    for(i=1;i<=n;i++)
    {
        int sx=rand();
        int sy=rand();
        sx=(sx%(70-9))+9;
        sy=(sy%(5-1))+1;//แถวแรกจะนับเป็น 0 ดังนั้น max จึงเป็น 5
        if(cursor(sx,sy)!='*')
        {
            gotoxy(sx,sy);
            printf("*");
        }
        else 
        {
            i--;
        }
    }
}
char cursor(int x,int y)//เอาไว้ตรวจสอบการชน
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
void scorebox(void)
{
    setcolor(9,0);
    gotoxy(60,0);
    printf("Your Score %d",score);
}