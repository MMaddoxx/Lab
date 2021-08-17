#include<stdio.h>
#include<string.h>
int main()
{
    char num[999];
    int a,i,stock=0;
    printf("Enter number : ");
    scanf("%s",num);
    while (strlen(num)!=1)//เช็ตว่าเหลือกี่ตัว
    {
        a=strlen(num);
        
        for(i=a;i>=1;i--)
        {
            stock=stock+num[i-1]-48;//ใช้stockเป็นint จะได้บกง่ายๆ
        }
        sprintf(num,"%d",stock);//ให้แปลstockให้กลับเป็นnum
        stock=0;//reset stock
    }
    printf("%s",num);
}