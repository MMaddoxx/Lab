#include<stdio.h>
int main()
{
    int n,i=0,x=2,ans[999],a;
    printf("Enter number : ");
    scanf("%d",&n);
    while (n!=1)
    {
        while (n%x==0)
        {
            ans[i]=x;
            n=n/x;
            i++;     
        }
        x++;
    }
    printf("Factoring Result : ");
    for(a=0;a<=i-1;++a)
    {
        if(a<i-1)
        {
            printf("%d x ",ans[a]);
        }
        if(a==i-1)
        {
            printf("%d",ans[a]);
        }
    }
}