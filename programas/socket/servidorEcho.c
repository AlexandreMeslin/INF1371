#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define EVER ;;
#define MAXLISTEN 257
#define MAXTAMLINHA 256

typedef	union {
	struct sockaddr_in cliente4;
	struct sockaddr_in6 cliente6;
} tEndereco;

struct addrinfo *getEnderecoHost(char *porta);
int criaSocket(struct addrinfo *enderecoServidor);
void setModo(int fd);
void bindaSocket(int fd, struct addrinfo *enderecoServidor);
void escuta(int fd);
int conecta(int fd);
void fazTudo(int fd);

int main(int argc, char **argv) {
	struct addrinfo *enderecoHost = NULL;
	int socketfd, conexaofd;

	if (argc != 2) {
		fprintf(stderr, "Uso: %s <porta>\n", argv[1]);
		exit(-1);
	}

	enderecoHost = getEnderecoHost(argv[1]);
	socketfd = criaSocket(enderecoHost);
	setModo(socketfd);
	bindaSocket(socketfd, enderecoHost);
	escuta(socketfd);

	for(EVER) {
		if ((conexaofd = conecta(socketfd)) == -1)
			continue;

		fazTudo(conexaofd);
	}
}

struct addrinfo *getEnderecoHost(char *porta) {
	struct addrinfo *enderecoHost, dicas;

	memset(&dicas, 0, sizeof dicas);
	dicas.ai_flags = AI_ADDRCONFIG | AI_PASSIVE;
	dicas.ai_family = AF_INET;
	dicas.ai_socktype = SOCK_STREAM;
	if(getaddrinfo(NULL, porta, &dicas, &enderecoHost) != 0) {
		fprintf(stderr, "Não obtive informações sobre o servidor (?!?!?)\n");
		exit(-2);
	}

	return enderecoHost;
}

int criaSocket(struct addrinfo *enderecoServidor) {
	int fd;
	
	fd = socket(enderecoServidor->ai_family, enderecoServidor->ai_socktype, enderecoServidor->ai_protocol);
	if(fd == -1) {
		fprintf(stderr, "Não consegui criar o socket\n");
		exit(-1);
	}

	return fd;
}

void setModo(int fd) {	
	int optval=1;
	
	if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval , sizeof optval) == -1) {
		fprintf(stderr, "Problemas ao reutilizar o endereço\n");
		exit(-1);
	}
}

void bindaSocket(int fd, struct addrinfo *enderecoServidor) {
	if(bind(fd, enderecoServidor->ai_addr, enderecoServidor->ai_addrlen) == -1) {
		fprintf(stderr, "Erro ao dar bind no socket\n");
		exit(-1);
	}
}

void escuta(int fd) {
	if(listen(fd, MAXLISTEN) == -1) {
		fprintf(stderr, "Erro ao começar a escutar a porta\n");
		exit(-1);
	}
	puts("Iniciando o serviço");
}

int conecta(int fd) {
	int novofd;
	unsigned tamCliente;
	char hostname[NI_MAXHOST], hostaddr[NI_MAXHOST];
	tEndereco enderecoCliente;

	tamCliente = sizeof (tEndereco);
	novofd = accept(fd, (struct sockaddr *)&enderecoCliente, &tamCliente);
	
	getnameinfo((struct sockaddr*)&enderecoCliente, tamCliente, hostname, sizeof hostname, NULL, 0, 0);
	getnameinfo((struct sockaddr*)&enderecoCliente, tamCliente, hostaddr, sizeof hostaddr, NULL, 0, NI_NUMERICHOST);
	printf("server connected to %s (%s)\n", hostname, hostaddr);
	
	return novofd;
}

void fazTudo(int fd) {
	int n;
	char buffer[MAXTAMLINHA];

	while((n = read(fd, buffer, sizeof buffer)) > 0) {
		printf("Servidor recebeu %d bytes.\n", n);
		for(int i=0; i<n; i++) {
			printf("%02X ", buffer[i]);
		}
		putchar('\n');
		write(fd, buffer, n);
	}
		
	printf("Conexão terminada\n");
	close(fd);
}
