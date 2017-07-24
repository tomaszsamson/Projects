#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/msg.h>
#define FIFO "fifo"
struct msgbf
{
	long mtype;
	char mtext[128];
};
char przelacznik = '1';
int PIDS[3];
int kontrolka=0;

void sig_handler1(int signum)//konczy
{
	
	printf("\nP2: Dostalem rozkaz zakonczenia pracy, przekazuje go procesowi macierzystemu!\n");
	przelacznik = '0';
	kill(getppid(), SIGTERM);
	
}
void sig_handler2(int signum)//wznawia
{
	
	
	signal(SIGUSR2, sig_handler2);
	if(przelacznik == '0' && kontrolka == 0)
	{
		kontrolka = 1;
	
		kill(PIDS[0], SIGUSR2);
		przelacznik ='1';
		kill(PIDS[2], SIGUSR2);
		printf("\nP2: Wznawiam dzialanie!\n");
		sleep(1);
	}
	
}
void sig_handler3(int signum)//zatrzymuje
{
	
	
	signal(SIGUSR1, sig_handler3);
	if(przelacznik == '1')
	{
		przelacznik ='0';
		kill(PIDS[2], SIGUSR1);
		kill(PIDS[0], SIGUSR1);
		printf("\nP2: Wstrzymuje dzialanie!\n");
	}
	
}
void sig_handler4(int signum) // wiadomosc o zakonczeniu procesu
{
	printf("P2: Koncze dzialanie!\n");
	unlink("./fifo");
	kill(PIDS[1], SIGQUIT);
}

int main()
{
	signal(SIGQUIT, sig_handler4); 
	signal(SIGUSR1, sig_handler3);
	signal(SIGUSR2, sig_handler2);
	signal(SIGINT, sig_handler1);

    FILE* fp;
	int PIDS[3];
    long int iloraz;
    int i=0,j,temp, dlugosc, z=0;
    char heksa[128], string[128], obrot[128];
    struct msgbf buf;

	fp = fopen("PIDS.txt", "a");
	fprintf(fp, "%d\n", getpid());
	fclose(fp);
	sleep(1);
	fp = fopen("PIDS.txt", "r");
	fscanf(fp, "%d%d%d", &PIDS[0], &PIDS[1],&PIDS[2] );
	fclose(fp);

	umask(0);
	mkfifo(FIFO, 0666);
	int msgid=msgget(46555, IPC_CREAT | 0600);
	if(msgid==-1)
	{
		perror("P2: Tworzenie kolejki\n");
		kill(getppid(), SIGTERM);
	}


  	sleep(3);
	while(1)
	{ //WHILE GLOWNY
		if(przelacznik == '1') //	PRZELACZNIK
		{
			
		
			msgrcv(msgid, &buf, sizeof(buf.mtext), 0, 0);
			for(j = 0; j < 128; j++ )
			{
				string[j] = 0;
				obrot[j] = 0;
			}
			j = 0;
			dlugosc=strlen(buf.mtext);
	for(j=0; j< dlugosc; j++)//FOR
		{
						iloraz = buf.mtext[j];
						while(iloraz!=0)
       						{ //WHILE WEWN
       		 					temp = iloraz % 16;
       							 if( temp < 10)
        							   temp =temp + 48;
       							 else
           							 temp = temp + 55;		
     							 obrot[z++]= temp;		
      							iloraz = iloraz / 16;
						} //WHILE WEWN
					for( z-=1;z >= 0; z--)//ODWROCENIE
					{
						string[i++]=obrot[z];
					} // /ODWROCENIE
					string[i++]=' ';
				
				z=0;
				}// /FOR
			i=0;
			if(przelacznik=='1')
			{
				if(kontrolka!=0) kontrolka--;
				else
				{
					fp = fopen(FIFO, "w");
					if(fp!=NULL)
					{
					
						fputs(string, fp);
						fclose(fp); 
					}
				}
			}
	}//	/PRZELACZNIK
	if(kontrolka==1)kontrolka--;
	sleep(1);
		
        }//WHILE GLOWNY
	

return 0;
}
