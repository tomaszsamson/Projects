#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main()
{
int liczba = 0;
int semid = semget(45100, 3, IPC_CREAT|0600);	
if (semid == -1)
	{
		perror("Tworzenie tablicy semaforow");    //tutaj w zasadzie s¹ komentarze
		exit(1);
	}
if(semctl(semid, 0, SETVAL, (int)1) == -1)
	{
		perror("Nadanie wartosci semaforowi 0");
		exit(0);
	}
if(semctl(semid, 1, SETVAL, (int)0) == -1)
	{
		perror("Nadanie wartosci semaforowi 1");
		exit(0);
	}
if(semctl(semid, 2, SETVAL, (int)0) == -1)
	{
		perror("Nadanie wartosci semaforowi 2");
		exit(0);
	}
int shmid = shmget(45200, sizeof(int), IPC_CREAT|0600);
if(shmid == -1)
	{
		perror("Utworzenie segmentu pamieci wspoldzielonej");
		exit(0);
	}
int *buf = shmat(shmid, NULL, 0);
if(buf == NULL)
	{
		perror ("Przylaczenie segmentu pamieci wspoldzielonej");
		exit(1);
	}
struct sembuf semafor;
void podnies(int semid, int semnum)
{
	semafor.sem_num = semnum;
	semafor.sem_op = 1;			//funkcja podnosz¹ca semafor
	semafor.sem_flg = 0;
if(semop(semid, &semafor, 1) == -1)
	{
		perror("Podnoszenie semafora");
		exit(1);
	}
}
void opusc(int semid, int semnum)
{
	semafor.sem_num = semnum;
	semafor.sem_op = -1;
	semafor.sem_flg = 0;			//funkcja opuszczaj¹ca semafor
if(semop(semid, &semafor, 1) == -1)
	{
		perror("Opuszczanie semafora");
		exit(1);
	}
}
if (fork() == 0)
	{
		execlp("./k1", "./k1", (char)0);
	}
if (fork() == 0)			//tworzenie procesów potomnych I uruchomianie w ich miejsce programów k1 I k2
	{
		execlp("./k2", "./k2", (char)0);
	} 
while(1)
	{
		opusc(semid,0);
		printf("Producent: zapisuje %d \n",liczba);
		*buf=liczba;
		liczba++;
		if(liczba==101) liczba=0;
		podnies(semid,1);
		sleep(1);
	}
}

////////////////////////k1

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main()
{
int liczba1;
int semid = semget(45100, 3, 0600);	
if (semid == -1)
	{
		perror("Tworzenie tablicy semaforow");
		exit(1);
	}
int shmid = shmget(45200, sizeof(int), 0600);
if(shmid == -1)
	{
		perror("Utworzenie segmentu pamieci wspoldzielonej");
		exit(0);
	}

int *buf = shmat(shmid, NULL, 0);
if(buf == NULL)
	{
		perror ("Przylaczenie segmentu pamieci wspoldzielonej");
		exit(1);
	}
struct sembuf semafor;

void podnies(int semid, int semnum)
{
	semafor.sem_num = semnum;
	semafor.sem_op = 1;
	semafor.sem_flg = 0;
if(semop(semid, &semafor, 1) == -1)
	{
		perror("Podnoszenie semafora");
		exit(1);
	}
}

void opusc(int semid, int semnum)
{
	semafor.sem_num = semnum;
	semafor.sem_op = -1;
	semafor.sem_flg = 0;
if(semop(semid, &semafor, 1) == -1)
	{
		perror("Opuszczanie semafora");
		exit(1);
	}
}

	while(1)
	{
		opusc(semid,1);
		liczba1=*buf;
		printf("Proces 1: odczytalem liczbe %d\n", liczba1);
		podnies(semid,2);
		sleep(1);		
	}
}




/////////////////////////k2


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main()
{
int liczba2;
int semid = semget(45100, 3, IPC_CREAT|0600);	
if (semid == -1)
	{
		perror("Tworzenie tablicy semaforow");
		exit(1);
	}
int shmid = shmget(45200, sizeof(int), IPC_CREAT|0600);
if(shmid == -1)
	{
		perror("Utworzenie segmentu pamieci wspoldzielonej");
		exit(0);
	}
int *buf = shmat(shmid, NULL, 0);
if(buf == NULL)
	{
		perror ("Przylaczenie segmentu pamieci wspoldzielonej");
		exit(1);
	}
struct sembuf semafor;

void podnies(int semid, int semnum)
{
	semafor.sem_num = semnum;
	semafor.sem_op = 1;
	semafor.sem_flg = 0;
if(semop(semid, &semafor, 1) == -1)
	{
		perror("Podnoszenie semafora");
		exit(1);
	}
}

void opusc(int semid, int semnum)
{
	semafor.sem_num = semnum;
	semafor.sem_op = -1;
	semafor.sem_flg = 0;
if(semop(semid, &semafor, 1) == -1)
	{
		perror("Opuszczanie semafora");
		exit(1);
	}
}
	
	while(1)
	{
		opusc(semid,2);
		liczba2=*buf;
		printf("Proces 2: odczytalem liczbe %d\n", liczba2);
		podnies(semid,0);
		sleep(1);		
	}
}
