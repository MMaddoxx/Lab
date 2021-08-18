#include<stdio.h>
int main()
{
    int i,n,check=0,a=0,ans[999];
    for(i=1;i<=10000;i++)//ไล่เลขตั้งแต่ 1 ถึง 10000
    {
        for(n=1;n<=i/2;n++)//หาตัวที่หารลงตัว โดยใช้เลขตั้งแต่ 1 ถึง i/2 
        {
            if(i%n==0)//ถ้าหารลงตัว 
            {
                check=check+n;
            }
        }
        if(i==check)//ถ้าผลรวมเท่ากับ i 
        {
            ans[a]=check;
            a++;
        }   
        check=0;
    }
    for(n=0;n<=a-1;n++)
    {
        printf("%d\t",ans[n]);
    }
}