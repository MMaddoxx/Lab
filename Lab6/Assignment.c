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
void firebullet();
void erasebullet();
int main()
{
    setcursor(0);
    char ch=' ',mem;
    int x=38,y=20,a,b,count=0;
    bool ammo=0;
    draw_ship(x,y);
    do
    {
        if(kbhit())
        {
            ch=getch();
            do//สำหรับการขยับ
            {
                if(kbhit())//ถ้าระหว่างขยับกดแป้นพิมพ์เข้ามา
                {
                    mem=ch;
                    ch=getch();
                    if(ch=='s')//หยุดถ้าพิมพ์s
                    {
                        break;
                    }
                    if(ch=='\''&&ammo==0&&count<=4)
                    {
                        a=x+2;
                        b=y-1;
                        ch=mem;
                        ammo=1;
                    }
                }
                if(ch=='a')//ขยับซ้าย
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
                if(ch=='d')//ขยับขวา
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
                if(ammo==1&&b>=3)
                {
                    erasebullet(a,b);
                    firebullet(a,--b);
                    if(b==2)
                    {
                        erasebullet(a,b);
                        ammo=0; 
                        count++;
                    }
                    
                }
                if(count==5)
                {
                    setcolor(4,7);
                    gotoxy(0,0);
                    printf("Out Of Ammo!!!");
                    count++;
                }
                fflush(stdin);
                Sleep(50);
            }while (ch!='s'&&ch!='x');
        }
        
        fflush(stdin);//เคลียข้อมูลที่รับเข้ามา      
    } while (ch!='x');
    printf("%d",count);
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
    printf("|");
}
void erasebullet(int x,int y)
{
    gotoxy(x,y);
    printf(" ");
}