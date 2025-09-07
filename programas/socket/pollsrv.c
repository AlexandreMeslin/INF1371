/* pollsrv.c */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define SOCKETNAME  "/faculty/rossa/system/mysocket"

int
main(void)
{
	char buf[1024];			/* Buffer for messages to others. */
	int s;				/* Listen socket */
	int ns;				/* Socket for first connection. */
	int ns2;			/* Socket for second connection. */
	int len;			/* len of sockaddr */
	int maxfd;			/* descriptors up to maxfd-1 polled*/
	int nread;			/* # chars on read()*/
	int nready;			/* # descriptors ready. */
	struct sockaddr_un name;
	fd_set fds;			/* Set of file descriptors to poll*/

	/* Remove any previous socket.*/
	unlink(SOCKETNAME);

	/* Create the socket. */

	if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		exit(1);
	}

	/* Create the address of the server.*/

	memset(&name, 0, sizeof(struct sockaddr_un));

	name.sun_family = AF_UNIX;
	strcpy(name.sun_path, SOCKETNAME);
	len = sizeof(name.sun_family) + strlen(name.sun_path);

	/*Bind the socket to the address.*/

	if (bind(s, (struct sockaddr *) &name, len) < 0) {
		perror("bind");
		exit(1);
	}
 	
	/* Listen for connections. */
	if (listen(s, 5) < 0){
		perror( "listen");
		exit(1);
	}


	/*Accept a connection.*/
	if ((ns = accept(s, (struct sockaddr *) &name, &len)) < 0) {
		perror("accept");
		exit(1);
	}

	/* Accept another connection. */
	if ((ns2 = accept(s, (struct sockaddr *) &name, &len)) < 0) {
		perror("accept");
		exit(1);
	}
	
	maxfd = (ns > ns2 ? ns : ns2) + 1;
	while(1){
		/* Set up polling using select. */
		FD_ZERO(&fds);
		FD_SET(ns,&fds);
		FD_SET(ns2,&fds);

		/* Wait for some input. */
		nready = select(maxfd, &fds, (fd_set *) 0, (fd_set *) 0,
				(struct timeval *) 0);
		/* If either descriptor has some input,
		read it and copy it to the other. */

		if( FD_ISSET(ns, &fds))
		{
			nread = recv(ns, buf, sizeof(buf), 0);
			/* If error or eof, terminate. */
			if(nread < 1){
				close(ns);
				close(ns2);
				exit(0);
			}
			send( ns2, buf, nread, 0);
		}

		if( FD_ISSET(ns2, &fds))
		{
			nread = recv(ns2, buf, sizeof(buf), 0);
			/* If error or eof, terminate. */
			if(nread < 1){
				close(ns);
				close(ns2);
				exit(0);
			}
			send( ns, buf, nread, 0);
		}
	}
}
