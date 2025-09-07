#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#define NO_SERVICE ((char *) 0)

int main(int argc, char *argv[]) {
	char hostbuffer[NI_MAXHOST];
	struct addrinfo hints;
	struct addrinfo *res0;
	struct addrinfo *res;
	const char *host;
	const char *addr;
	int erro;

	if(argc != 2) {
		fprintf(stderr, "Uso: getnameinfo <endereco ip>\n");
		return 1;
	}

    /*
	* Convert address to internal form.
    */
	host = argv[1];
	memset((char *) &hints, 0, sizeof(hints));
	hints.ai_family = (strchr(host, ':') ? AF_INET6 : AF_INET);
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags |= AI_NUMERICHOST;
	if((erro = getaddrinfo(host, NO_SERVICE, &hints, &res0)) != 0) {
		fprintf(stderr, "[getaddrinfo] %s: %s\n", host, gai_strerror(erro));
		return 1;
	}

    /*
	* Convert host address to name.
    */
	for(res = res0; res != 0; res = res->ai_next) {
		printf("res = %s\n", res->ai_addr);
		erro = getnameinfo(res->ai_addr, res->ai_addrlen,
				  hostbuffer, sizeof(hostbuffer),
				  NO_SERVICE, 0, NI_NAMEREQD);
		if(erro) {
			fprintf(stderr, "[getnameinfo] %s: %s\n", host, gai_strerror(erro));
			return 1;
		}
		printf("Hostname:\t%s\n", hostbuffer);
		addr = (res->ai_family == AF_INET ?
		(char *) &((struct sockaddr_in *) res->ai_addr)->sin_addr :
				(char *) &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr);
		if(inet_ntop(res->ai_family, addr, hostbuffer, sizeof(hostbuffer)) == 0) {
			perror("inet_ntop:");
			return 1;
		}
		printf("Address:\t%s\n", hostbuffer);
	}
	freeaddrinfo(res0);
	exit(0);
}
