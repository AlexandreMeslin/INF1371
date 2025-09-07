#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define EVER ;;
#define NLUGARES 10

union semun
{
	int val;
	struct semid_ds *buf;
	ushort *array;
};

int setSemValue(int semId, int valor);
int criaSem(int chave);
void delSemValue(int semId);
int p(int semId);
int v(int semId);
void exibeFilme(void);

int *pNFans, ipc_nFans;

int main (void)
{
	int i;
	int mutex;
	int dem;
	int fila;

	mutex = criaSem(1);	setSemValue(mutex, 1);
	dem = criaSem(2);	setSemValue(dem, 0);
	fila = criaSem(3);	setSemValue(fila, 0);

	ipc_nFans = shmget(4, sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
	pNFans = (int *) shmat (ipc_nFans, 0, 0);
	*pNFans = 0;

	for(EVER)
	{
		while(*pNFans < NLUGARES)
		{
			p(dem);
			p(mutex);
			*pNFans -= NLUGARES;
			v(mutex);
			for (i=0; i<NLUGARES; i++)
				v(fila);
			exibeFilme();
		}
	}
}

void exibeFilme(void)
{
	printf ("DEMONSTRADOR: exibindo o filme com %d fans\n", *pNFans);
	sleep(10);
	puts ("DEMONSTRADOR: fim da exibicão do filme ");
}

int setSemValue(int semId, int valor)
{
	union semun semUnion;

	semUnion.val = valor;
	return semctl(semId, 0, SETVAL, semUnion);
}

int criaSem(int chave)
{
	return semget (chave, 1, 0666 | IPC_CREAT);
}

void delSemValue(int semId)
{
	union semun semUnion;

	semctl(semId, 0, IPC_RMID, semUnion);
}

int p(int semId)
{
	struct sembuf semB;

	semB.sem_num = 0;
	semB.sem_op = -1;
	semB.sem_flg = SEM_UNDO;
	semop(semId, &semB, 1);
	return 0;
}

int v(int semId)
{
	struct sembuf semB;

	semB.sem_num = 0;
	semB.sem_op = 1;
	semB.sem_flg = SEM_UNDO;
	semop(semId, &semB, 1);
	return 0;
}
