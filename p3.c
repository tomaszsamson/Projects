#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#define FIFO "fifo"
int PIDS[3];
char przelacznik = '1';
char string[15][128];
int i=0;

void sig_handler1(int signum)//konczy
{
	
	printf("\nP3: Dostalem rozkaz zakonczenia pracy, przekazuje go procesowi macierzystemu!\n");
	przelacznik = '0';
	kill(getppid(), SIGTERM);
	
}

void sig_handler2(int signum)//wznawia		 
{
	
	
	signal(SIGUSR2, sig_handler2);
	if(przelacznik == '0')
	{
		
		kill(PIDS[1], SIGUSR2);	
		
		kill(PIDS[0], SIGUSR2);
		sleep(1);
		if(przelacznik == '0')	printf("\nP3: Wznawiam dzialanie!\n");
		przelacznik ='1';
			
		sleep(1);
	}	
}
void sig_handler3(int signum)//zatrzymuje
{
	
	
	signal(SIGUSR1, sig_handler3);
	if(przelacznik == '1')
	{
		kill(PIDS[0], SIGUSR1);
		przelacznik ='0';
		
		kill(PIDS[1], SIGUSR1);
		printf("\nP3: Wstrzymuje dzialanie!\n");
	}
	
}

void sig_handler4(int signum)//wypisuje "resztki"
{

	
//	printf("I = %d\n", i);
	if(i!=0)
	{
		
		int k;
		printf("\nP3 Wypisuje: ");
		fflush(stdout);
		for(k=0; k <= i-1; k++)
		{
			
			printf("%s ", string[k]);
			fflush(stdout);
			
		}
		printf("\n");
		
		
	}
	
	i=0;
	printf("P3: Koncze dzialanie!\n"); 
	kill(PIDS[2], SIGQUIT);
	
	
}

void sig_handler5(int signum)//wypisuje "resztki"
{
	
	

	if(i!=1)
	{
		
		int k;
		printf("\nP3 Wypisuje: ");
		fflush(stdout);
		for(k=0; k <= i-2; k++)
		{

			
			printf("%s ", string[k]);
			fflush(stdout);
			
		}
		printf("\n");
		i=0;
		 
	}
	printf("P3: Koncze dzialanie!\n"); 
	kill(PIDS[2], SIGQUIT);
	
	
}


int main()
{
	signal(SIGTERM, sig_handler5);
	signal(SIGQUIT, sig_handler4);
	signal(SIGUSR1, sig_handler3);
	signal(SIGUSR2, sig_handler2);
	signal(SIGINT, sig_handler1);

	FILE* fp;
	int j = 0 ;
	char str[128];

	fp = fopen("PIDS.txt", "a");
	fprintf(fp, "%d\n", getpid());
	fclose(fp);
	sleep(1);
	fp = fopen("PIDS.txt", "r");
	fscanf(fp, "%d%d%d", &PIDS[0], &PIDS[1],&PIDS[2] );
	fclose(fp);
	

	for(i = 0; i < 15; i ++)
	{

		for(j = 0; j < 128; j++ )
		{
	
			string[i][j] = 0;
		}
 	}
	i=0;
	while(1)
	{
		if(przelacznik =='1')//		PRZELACZNIK
		{
			fp = fopen (FIFO, "r");
			if(fp!=NULL)
			{
				
				
					if(przelacznik =='1')
					{
					fgets(str, 128, fp);
					if(str[0] != 0)
					{
					printf("\nP3: Odczytalem %s\n",str );
					strcpy(string[i],str);
					

					i++;
					}
					}
				
			}
		
			if(i==15)// 		IF
			{
					fprintf(stderr, "\nWYPISUJE: %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s\n", string[0], string[1], string[2], string[3], string[4], string[5], string[6], string[7], string[8], string[9], string[10], string[11], string[12], string[13], string[14]);
					i=0;
			
			}// 		/IF
		
		}//		/PRZELACZNIK
		fclose(fp);
		str[0] = 0;
		
		sleep(1);
		
	}

	return 0;
	
}
