#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
int PIDS[3];
char over = '0';
void sig_handler1(int signum) //TERM
{
	
	over = '1';
	printf("Macierzysty: Koncze dzialanie wszystkich procesow!\n");
	kill(PIDS[0], SIGQUIT);
	kill(PIDS[1], SIGQUIT);
	kill(PIDS[2], SIGQUIT);
	sleep(1);
	kill(getpid(), SIGQUIT);
	
}
void sig_handler2(int signum) //QUIT
{
	if(over != '1')
	{
	printf("Macierzysty: Koncze dzialanie wszystkich procesow!\n");
	kill(PIDS[0], SIGQUIT);
	kill(PIDS[1], SIGQUIT);
	kill(PIDS[2], SIGTERM);
	
	}
	sleep(1);
	kill(getpid(), SIGQUIT);
	
}


int main()
{

	FILE* fp;
	
	
	if(!fork()) //P1
	{
		execlp("./p1", NULL, "./p1", NULL);
	}
	sleep(1);
	if(!fork())//P2
	{
		execlp("./p2", NULL, "./p2", NULL);
	}
	
	if(!fork())//P3
	{
		execlp("./p3", NULL, "./p3", NULL);
	}   
	
	sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);
	sigaddset( &mask, SIGUSR2);
	sigaddset( &mask, SIGINT);
	sigaddset( &mask, SIGTSTP);
	
	sigprocmask(SIG_SETMASK, &mask, NULL);
	sleep(1);
	fp = fopen("PIDS.txt", "r");
	fscanf(fp, "%d%d%d", &PIDS[0],&PIDS[1], &PIDS[2] );
	fclose(fp);
	
	signal(SIGTERM, sig_handler1);
	signal(SIGQUIT, sig_handler2);
	while(1)
	{
		sleep(1);

	}
	
	return 0;
}
