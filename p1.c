#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <fcntl.h>
struct msgbf
{
	long mtype;
	char mtext[128];
};
int PIDS[3];
char przelacznik = '1';
int kontrolka = 0;
int msgid;
char tryb= '0';


void sig_handler1(int signum)//konczy
{
	kontrolka = 1;
	przelacznik = '0';
	printf("\nP1: Dostalem rozkaz zakonczenia pracy, przekazuje go procesowi macierzystemu!\n");
	
	kill(getppid(), SIGQUIT);
	
}

void sig_handler2(int signum)//wznawia		
{
	
	
	signal(SIGUSR2, sig_handler2);
	if(przelacznik == '0')
	{
		kill(PIDS[1], SIGUSR2);
		if(tryb=='2') sleep(1);
		if(przelacznik == '0')printf("\nP1: Wznawiam dzialanie!\n");
		przelacznik ='1';
		kill(PIDS[2], SIGUSR2);
		if(tryb=='1' || tryb =='2')kontrolka = 1;
		
		sleep(2);
	}
	
	
}

void sig_handler3(int signum)//zatrzymuje
{
	
	
	signal(SIGUSR1, sig_handler3);
	if(przelacznik == '1')
	{
		przelacznik ='0';
		kill(PIDS[2], SIGUSR1);
		kill(PIDS[1], SIGUSR1);
		printf("\nP1: Wstrzymuje dzialanie!\n");
	}
	
}
void sig_handler4(int signum) // usuwanie kolejki inaczej zostaja resztki z poprzednich uzyc
{
	printf("P1: Koncze dzialanie!\n");
	system("ipcrm -Q 46555");
	kill(PIDS[0], SIGQUIT);
}

int main()
{
	signal(SIGQUIT, sig_handler4); 
	signal(SIGUSR1, sig_handler3);
	signal(SIGUSR2, sig_handler2);
	signal(SIGINT, sig_handler1); 
	
	
	
	char liczba[128];
	struct msgbf buf;
	buf.mtype = 1;
	FILE* fp;
	int des2;
	int* pdes;
	pdes = &des2;

	fp = fopen("PIDS.txt", "w");
	fprintf( fp, "%d\n", getpid() );
	fclose(fp);
	sleep(2);
	fp = fopen("PIDS.txt", "r");
	fscanf(fp, "%d%d%d", &PIDS[0], &PIDS[1],&PIDS[2] );
	fclose(fp);

	while(tryb!='1' && tryb!='2' && tryb!='3')
	{
	printf("1. Tryb interaktywny\n");
	printf("2. Tryb odczytu z pliku\n");
	printf("3. Tryb odczytu z pliku /dev/urandom\n");
	scanf("%c", &tryb);
	system("clear");
	}
	if(tryb =='2')
	{
		printf("Podaj nazwe pliku do odczytu wraz z rozszerzeniem: ");
		scanf("%s", &liczba);
		
		fp = fopen(liczba, "r");
		if(fp==NULL)
		{
			perror("P1: Nie udalo sie otworzyc pliku!\n");
			kill(getppid(), SIGTERM);
		}
		
			
	}
	else if (tryb =='3')
	{
		fp = fopen("/dev/urandom", "r");
		
		if(fp == NULL)
		{
			perror("P1: Nie udalo sie otworzyc generatora liczb losowych!\n");
			kill(getppid(), SIGTERM);
		}
	}


	msgid=msgget(46555, IPC_CREAT | 0600);
	if(msgid==-1)
	{
		perror("P1: Tworzenie kolejki\n");
		kill(getppid(), SIGTERM);
	}
	

	
	while(1) //GLOWNY WHILE
	{
	
		if(przelacznik == '1')//	PRZELACZNIK
		{
			if(kontrolka==0)
			{
				if(tryb =='1')//	1. TRYB
				{
					printf("Podaj wiadomosc: ");
					scanf("%s", &buf.mtext);
					if(buf.mtext[0] != 0 )
					if(msgsnd(msgid, &buf, sizeof(buf.mtext), 0)!=0)
					{
						perror("P1: Nie wpisalo (z klawiatury)\n");
						kill(getppid(), SIGTERM);
					}
				
			
					
				
				}// 		/1.TRYB
			
				if(tryb=='2' ) //	2. TRYB
				{
				
					if(fscanf(fp, "%s", &buf.mtext) != EOF )
					msgsnd(msgid, &buf, sizeof(buf.mtext), 0);
					else kill(getppid(), SIGTERM);
				
				
	
				}// 		/2.TRYB
				if(tryb=='3')//		3. TRYB
				{
				
					fread(pdes, 1,  4, fp); 
					if(des2 < 0) des2 = -des2;
					sprintf(buf.mtext, "%d", des2);
					if(msgsnd(msgid, &buf, sizeof(buf.mtext), 0)!=0)
					{
						perror("P1: Nie wpisalo do kolejki\n");
						kill(getppid(), SIGTERM);
					}
			
				
				}// 		/3.TRYB

			}
			else
			{
		 kontrolka--;
			sleep(1);
			}
		}//		/PRZELACZNIK
		

		sleep(1);
	}//KONIEC GLOWNEGO WHILE'A
	if(tryb=='2' || tryb == '3') fclose(fp);
	
}
