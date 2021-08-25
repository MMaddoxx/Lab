#include<stdio.h>
#include<math.h>
#include<conio.h>
int main()
{
    int i=0,j=0;
    float num[3],a,s=0;
    printf("Enter length of the sides of the triangle : ");
    scanf("%f %f %f",&num[0] ,&num[1] ,&num[2]);
    for (i = 0; i < 3; i++)//เอาไว้เรียงตัวเลขที่inputเข้ามาจากน้อยไปหามาก
    {
        for (j = i+1 ; j < 3; j++)
        {
            if (num[i] > num[j])
            {
                a =  num[i];
                num[i] = num[j]; 
                num[j] = a;
            }
        }
    }
    if(num[2]<num[1]+num[0])//เป็นสามเหลี่ยม
    {
        s=(num[0]+num[1]+num[2])/2;  
        printf("It is Triange and the area is %.2f",sqrt(s*(s-num[0])*(s-num[1])*(s-num[2])));
    }
    else //ถ้าไม่เป็นสามเหลี่ยม
    {
        printf("0");
    }
    getch();
    return 0;
}