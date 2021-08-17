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