#include<stdio.h>
int main()
{
    int n,i,a;
    printf("Input number : ");
    scanf("%d",&n);
    for(i=1;i<=n-1;i++)//ปีกบน
    {
        for (a=1;a<=i;a++)
        {
           printf("* ");//วาดด้านซ้าย
        }
        for(a=1;a<=2*n-1-(i*2);a++)
        {
           printf("  ");//เว้นวรรคตรงกลาง
        }
        for (a=1;a<=i;a++)
        {
           printf("* ");//วาดด้านขวา
        }
        printf("\n");
    }
    for(i=1;i<=2*n-1;i++)//ส่วนกลาง
    {
        printf("* ");
    }
    printf("\n");
    for(i=n-1;i>=1;i--)//ส่วนล่างทำคล้ายๆส่วนบนแค่กลับด้าน(สลับตัวเริ้ม i )
    {
        for (a=1;a<=i;a++)
        {
           printf("* ");
        }
        for(a=1;a<=2*n-1-(i*2);a++)
        {
           printf("  ");
        }
        for (a=1;a<=i;a++)
        {
           printf("* ");
        }
        printf("\n");
    }
}
