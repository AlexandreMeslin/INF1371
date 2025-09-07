#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

int main (int argc, char *argv[])
{
	struct hostent *pHost;
	unsigned endereco;
	
	if (argc != 2)
	{
		puts("Uso: porEndereco <endereco>");
		abort();
	}

	endereco = inet_addr(argv[1]);
	pHost = gethostbyaddr(&endereco, sizeof endereco, AF_INET);

	if (!pHost)
	{
		fprintf(stderr, "Não encontrei informações sobre %s\n", argv[1]);
		abort();
	}

	printf("Nome: %s\nEndereço IP: %s\n", pHost->h_name, inet_ntoa(*((struct in_addr *)pHost->h_addr)));

	printf("Alias: ");
	while (*pHost->h_aliases)
		printf("%s ", *pHost->h_aliases++);
	putchar('\n');

	printf("Endereços: ");
	while (*pHost->h_addr_list)
		printf("%s ", inet_ntoa(*(struct in_addr *) *pHost->h_addr_list++));
	putchar('\n');

	return 0;
}
