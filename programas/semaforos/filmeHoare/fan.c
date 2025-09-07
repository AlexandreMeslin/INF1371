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
void assiteFilme(void);
void telefona(void);

int main (void)
{
	int *pNFans, ipc_nFans;
	int mutex;
	int dem;
	int fila;

	mutex = criaSem(1);
	dem = criaSem(2);
	fila = criaSem(3);
	
	ipc_nFans = shmget(4, sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
	pNFans = (int *) shmat (ipc_nFans, 0, 0);
	
	for(EVER)
	{
		p(mutex);
		(*pNFans)++;
		v(mutex);
		v(dem);
		p(fila);
		assiteFilme();
		telefona();
	}
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

void assiteFilme(void)
{
	puts ("FAN: assistindo filme");
	sleep(10);
	puts ("FAN: fim do filme");
}

void telefona(void)
{
	puts ("FAN: telefonando para a mãe");
	sleep(2);
	puts ("FAN: fim do telefonema");
}
