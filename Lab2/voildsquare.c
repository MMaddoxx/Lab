#include<stdio.h>
int main()
{
    int n,a,i;
    printf("Enter number :");
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        if(i==1||i==n)
        {
            for(a=1;a<=n;a++)
            {
                printf("*");
            }
            printf("\n");
        }
        else
        {
            printf("*");
            for(a=2;a<n;a++)
            {
                printf(" ");
            }
            printf("*\n");

        }

    }
}