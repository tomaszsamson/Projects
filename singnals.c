#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
int zmienna = 0;
int zmienna2 = 0;
int ojciec = 0;
void hand(int sig)
{
Switch (sig){
Case SIGUSR1:
If (zmienna==getpid())
{
Printf("jestem process 1 i radze sobie z SIGUSR1\n");
}
Else if(zmienna2==getpid())
{
Printf("zawieszam dzialanie procesu 1(?)\n");
kill(zmienna, SIGSTOP);
}
else if(ojciec==getpid())
{
	printf("oberwalem SIGUSR1 i koncze dzialanie\n");
	kill (ojciec, SIGUSR1);
}
break;
case SIGUSR2: 
if (ojciec==getpid())
{
	printf("jestem ojcem i nie takie problemy rozwiazywalem, dam rade z SIGUSR2\n");

}
else if(zmienna2==getpid())
{
	printf ("wznawiam proces 1(?)\n");
	kill(zmienna, SIGCONT);
}
break;
case SIGTERM:
if(getpid()==zmienna)
{
	printf("zabijam potomkow!\n");
	kill(zmienna, SIGTERM);
	kill(zmienna2, SIGTERM);
}
break;
}}
int main()
{
	sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask,SIGINT);
	sigaddset(&mask,SIGQUIT);
	sigaddset(&mask, SIGTSTP);
	
	sigprocmask(SIG_BLOCK,&mask,NULL);
	ojciec = getpid();
	printf("jestem ojcem zz pidem %d\n",getpid());
	if (signal(SIGUSR1, hand)==SIG_ERR)
	printf("blad!\n");
		if (signal(SIGUSR2, hand)==SIG_ERR)
	printf("blad!\n");
		if (signal(SIGTERM, hand)==SIG_ERR)
	printf("blad!\n");
	if (fork()==0)
	{
		zmienna=getpid();
		printf("jestem procesem 1 z pidem %d, moj ojciec to %d\n", getpid(), getppid());
		while(1)
		{
			printf ("p1 obecny %d\n", zmienna);
			sleep(5);
		}
	}
		if (fork()==0)
	{
		zmienna2=getpid();
		printf("jestem procesem 2 z pidem %d, moj ojciec to %d\n", getpid(), getppid());
		while(1)
		{
			printf ("p2 obecny %d\n", zmienna2);
			sleep(5);
		}
	}
	sleep(60);
	return 0;
}
