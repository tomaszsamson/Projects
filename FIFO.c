#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define FIFO "my_fifo"

void client(const char *IN){
FILE *fp;
int liczba;
printf("client IN: %s\n", IN);
while(1){
fp = fopen(FIFO, "r");
fscanf (fp, "%d", &liczba);
printf("dostalem wartosc: %d\n", liczba);
fclose(fp);
sleep(2);
}
}

void server(const char *IN_OUT){
FILE *fp;
int liczba;
printf("server IN_OUT: %s\n", IN_OUT);

while(1){
fp = fopen(FIFO, "r");
fscanf (fp, "%d", &liczba);
fclose (fp);
printf("kwadrat\n");
liczba *= liczba;
fp = fopen (FIFO, "w");
fprintf (fp, "%d", liczba);
fclose(fp);
sleep(2);
}
}

void hand (const char *OUT) {
FILE *fp;
int liczba;
printf ("hand OUT: %s\n", OUT);
while (1) {
fprintf (stdout, "wprowadz liczbe: ");
fscanf (stdin, "%d", &liczba);
fp = fopen (FIFO, "w");
fprintf (fp, "%d", liczba);
fclose (fp);
printf ("%d\n", liczba);
sleep (2);
}
}

int main(int argc, const char *argv[]){
char string[256], *str;
str = string;
if(argc == 3){
fprintf(stderr, "ARGV: [ %s %s ]\n", argv[1], argv[2]);
if(!strcmp(argv[2],"CLIENT")) { client(argv[1]); }
else if (!strcmp(argv[2], "SERVER")) { server(argv[1]); }
else if (!strcmp(argv[2], "HAND")) { hand (argv[1]); }
exit(0);
}
umask(0);
    mknod(FIFO, S_IFIFO|0666, 0);
fprintf(stderr, "PIPE utworzony\n");
if(fork()){
execl(argv[0], argv[0], FIFO, "CLIENT", NULL);
} else if (fork()){
execl(argv[0], argv[0], FIFO, "SERVER", NULL);
} else {
execl(argv[0], argv[0], FIFO, "HAND", NULL);
}
return 0;
}
