#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NO_SERVICE 0

int main(int argc, char *argv[]) {
	char hostbuffer[NI_MAXHOST];
	struct addrinfo dicas;
	struct addrinfo *res0;
	struct addrinfo *res;
	char *endereco;

	if(argc != 2) {
		fprintf(stderr, "Uso: getaddrinfo <hostname>\n");
		exit(1);
	}
	
	memset(&dicas, 0, sizeof(dicas));
	dicas.ai_family = PF_UNSPEC;
	dicas.ai_flags = AI_CANONNAME;
	dicas.ai_socktype = SOCK_STREAM;
	if(getaddrinfo(argv[1], NO_SERVICE, &dicas, &res0) != 0) {
		fprintf(stderr, "host %s not found\n", argv[1]);
		exit(1);
	}
	printf("Hostname:\t%s\n", res0->ai_canonname);
	printf("Addresses:\t");
	for(res = res0; res != 0; res = res->ai_next) {
		endereco = (res->ai_family == AF_INET ?
				(char *) &((struct sockaddr_in *) res->ai_addr)->sin_addr :
				(char *) &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr);
		if(inet_ntop(res->ai_family, endereco, hostbuffer, sizeof(hostbuffer)) == 0) {
			perror("inet_ntop:");
			exit(1);
		}
		printf("%s ", hostbuffer);
	}
	printf("\n");
	freeaddrinfo(res0);
	exit(0);
}

