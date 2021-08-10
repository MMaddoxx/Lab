#include<stdio.h>
int main()
{
    int num1,num2,i,ans;
    printf("Enter first number : ");
    scanf("%d",&num1);
    printf("Enter secound number : ");
    scanf("%d",&num2);
    for(i=1;i<=num1&&i<=num2;i++)
    {
        if(num1%i==0&&num2%i==0)
        {
            ans=i;
        }
    }
    printf("Greatest common divisor = %d",ans);
}