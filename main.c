#include <ctype.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

int validate_number(int n);
int validate_string (char x[30]);

void main()
{
    char x[30];
    int n,h,z;

    do{
    scanf("%d",&n);
    h=validate_number(n);
    }while (h==1);

    do{
    gets(x);
    gets(x);
    z=validate_string(x);
    }while (z==1);

    getch();
}

int validate_number(int n)
{
    int i,c=0,j;
    for (i=0;i<9;i++)
{
    j=n%10;
    n=n/10;
    c++;
    if (isalpha(j))
    {
    printf("Invalid Phone Number\n");
    return 1;
    }
}
if (c+2!=11||n!=01)
{
    printf("Invalid Phone Number\n");
    return 1;
}
else
    return 0;
}

int validate_string(char x[30])
{
 int i,y=0,p;
 p=strlen(x);
    for (i = 0; i < p ; i++)
    {
        if ((x[i] >= 'a' && x[i] <= 'z') || (x[i] >= 'A' && x[i] <= 'Z') || (x[i] == ' '))
        {
            continue;
        }
        else
        {
    printf("Invalid Text\n");
    return 1;
        }
    }

}
