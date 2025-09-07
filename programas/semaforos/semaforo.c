#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

/** inicializa o valor do semáforo */
int setSemValue(int semId);
/** remove o semáforo */
void delSemValue(int semId);
/** operação P */
int semaforoP(int semId);
/** operaćão V */
int semaforoV(int semId);
/** Cria um semáforo */
int criaSem(int chave, int cria);

int main(int argc, char *argv[]) {
	int i;
	char letra = 'o';
	int semId;

	if (argc > 1) {
		semId = criaSem(8752, IPC_CREAT); // semget (8752, 1, 0666 | IPC_CREAT);
		setSemValue(semId);
		letra = 'x';
		sleep(2);
	} else {
		while ((semId = criaSem(8752, 0)) < 0) {
			putchar('.');
			fflush(stdout);
			sleep(1);
		}
	}

	printf("semId = %d\n", semId);

	for (i = 0; i < 10; i++) {
		semaforoP(semId);
		putchar(toupper(letra));
		fflush(stdout);
		sleep(rand() % 3);
		putchar(letra);
		fflush(stdout);
		semaforoV(semId);
		sleep(rand() % 2);
	}

	printf("\nProcesso %d terminou\n", getpid());

	if (argc > 1) {
		sleep(10);
		delSemValue(semId);
	}

	return 0;
}

int setSemValue(int semId) {
	union semun semUnion;
	semUnion.val = 1;
	return semctl(semId, 0, SETVAL, semUnion);
}

int criaSem(int chave, int cria) {
	int semId;
	semId = semget(chave, 1, 0666 | cria);
	return semId;
}

void delSemValue(int semId) {
	union semun semUnion;
	semctl(semId, 0, IPC_RMID, semUnion);
}

int semaforoP(int semId) {
	struct sembuf semB;
	semB.sem_num = 0;			// número do semáforo
	semB.sem_op = -1;			// decrementa 1 unidade
	semB.sem_flg = SEM_UNDO;	// desfaz a operação se o processo terminar
	semop(semId, &semB, 1);		// 3o parâmetro é o tamanho do vetor de estruturas
	return 0;
}

int semaforoV(int semId) {
	struct sembuf semB;
	semB.sem_num = 0;			// número do semáforo
	semB.sem_op = 1;			// incrementa 1 unidade
	semB.sem_flg = SEM_UNDO;	// desfaz a operação se o processo terminar
	semop(semId, &semB, 1);		// 3o parâmetro é o tamanho do vetor de estruturas
	return 0;
}
