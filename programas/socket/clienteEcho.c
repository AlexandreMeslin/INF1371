#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>

#define MAXTAMLINHA 256

struct addrinfo *getEnderecoServidor (char *host, char *porta);
int getSocket(struct addrinfo *enderecoServidor);
void conecta (int fd, struct addrinfo *enderecoServidor);
void fazOResto(int fd);

int main (int argc, char *argv[]) {
	int socketfd;
	struct addrinfo *enderecoServidor = NULL;

	if(argc != 3) {
		fprintf(stderr, "Uso: clienteEcho host porta\n");
		exit(-1);
	}

	enderecoServidor = getEnderecoServidor(argv[1], argv[2]);
	socketfd = getSocket(enderecoServidor);
	conecta(socketfd, enderecoServidor);
	fazOResto(socketfd);

	close(socketfd);
	return 0;
}

struct addrinfo *getEnderecoServidor (char *host, char *porta) {
	struct addrinfo *enderecoServidor, dicas;
	
	memset(&dicas, 0, sizeof dicas);
	dicas.ai_flags = AI_ADDRCONFIG;
	dicas.ai_family = AF_INET;
	dicas.ai_socktype = SOCK_STREAM;
	printf("Tentando %s na porta %s\n", host, porta);
	
	if(getaddrinfo(host, porta, &dicas, &enderecoServidor) != 0) {
		fprintf(stderr, "Não obtive informações sobre nenhum servidor %s na porta %s\n", host, porta);
		exit(-2);
	}
	
	return enderecoServidor;
}

int getSocket(struct addrinfo *enderecoServidor) {
	int fd;
	
	fd = socket(enderecoServidor->ai_family, enderecoServidor->ai_socktype, enderecoServidor->ai_protocol);
	if(fd == -1) {
		fprintf(stderr, "Não consegui criar o socket\n");
		exit(-1);
	}

	return fd;
}

void conecta (int fd, struct addrinfo *enderecoServidor) {
	int erro;

	erro = connect(fd, enderecoServidor->ai_addr, enderecoServidor->ai_addrlen);
	if(erro == -1) {
		fprintf(stderr, "Erro ao tentar conexão com o servidor\n");
		exit(-1);
	}
	
	freeaddrinfo(enderecoServidor);
}

void fazOResto(int fd) {
	char bufferEntrada[MAXTAMLINHA], bufferSaida[MAXTAMLINHA];
	
	while(fgets(bufferSaida, MAXTAMLINHA, stdin) != NULL) {
		write(fd, bufferSaida, strlen(bufferSaida)+1);
		read(fd, bufferEntrada, MAXTAMLINHA);
		fputs(bufferEntrada, stdout);
	}
}
