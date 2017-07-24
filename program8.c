#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
int des, des1,des2,des3;
int a,b,c,i=0;
char operand;
char temp;

char buff[20],buff1[20],buff2[20], buff3[20];
des = open ("plik1.txt", O_CREAT | O_RDWR | O_APPEND, 0666);
if (des<0)
{
write (2, "ERROR\n", 6);
return 1;
}
read(des, buff, sizeof(buff));

sscanf(buff, "%d", &a);
printf ("%d\n", a);
des1 = open ("plik2.txt", O_CREAT | O_RDWR | O_APPEND, 0666);
if (des1<0)
{
write (2, "ERROR\n", 6);
return 1;
}
read(des1, buff1, sizeof(buff1));

sscanf(buff1, "%d", &b);
printf ("%d\n", b);
des2 = open ("plik3.txt", O_CREAT | O_RDWR | O_APPEND, 0666);
if (des2<0)
{
write (2, "ERROR\n", 6);
return 1;
}
read(des2, buff2, sizeof(buff2));

sscanf(buff2, "%c", &operand);
printf ("%c\n", operand);
if(operand == 43)
{
c=a+b;
}
else if (operand==45){
c=a-b;
}
else if (operand==42)
{
c=a*b;
}
else if (operand==47)
{
c=a/b;
}
else if (operand==37)
{
c=a%b;
}


printf ("%d\n" ,c);

FILE * fp;
fp=fopen("plik4.txt", "w+");
fprintf(fp, "%d", c);
close(des);
close(des1);
close(des2);
fclose (fp);
return 0;
}
