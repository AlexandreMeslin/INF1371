/* pollcli.c */
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/un.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define SOCKETNAME  "/faculty/rossa/system/mysocket"

int
main(void)
{
	int s;		/* This end of connection*/
	int len;	/* length of sockaddr */
	int nread;	/* return from read() */
	int nready;	/* # fd's ready. */
	int maxfd;	/* fd's 0 to maxfd-1 checked. */
	char buf[1024];
	fd_set fds;	/* set of file descriptors to check. */
	struct sockaddr_un name;


	if( (s = socket(AF_UNIX, SOCK_STREAM, 0) ) < 0){
		perror("socket");
		exit(1);
	}

	/*Create the address of the server.*/

	memset(&name, 0, sizeof(struct sockaddr_un));

	name.sun_family = AF_UNIX;
	strcpy(name.sun_path, SOCKETNAME);
	len = sizeof(name.sun_family) + strlen(name.sun_path);


	/*Connect to the server.*/

	if (connect(s, (struct sockaddr *) &name, len) < 0){
		perror("connect");
		exit(1);
	}


	maxfd = s + 1;
	while(1){
		/* Set up polling. */
		FD_ZERO(&fds);
		FD_SET(s,&fds);
		FD_SET(0,&fds);

		/* Wait for some input. */
		nready = select(maxfd, &fds, (fd_set *) 0, (fd_set *) 0,
				(struct timeval *) 0);

		/* If either device has some input,
		read it and copy it to the other. */

		if( FD_ISSET(s, &fds))
		{
			nread = recv(s, buf, sizeof(buf), 0);
			/* If error or eof, terminate. */
			if(nread < 1){
				close(s);
				exit(0);
			}
			write(1, buf, nread);
		}

		if( FD_ISSET(0, &fds))
		{
			nread = read(0, buf, sizeof(buf));
			/* If error or eof, terminate. */
			if(nread < 1){
				close(s);
				exit(0);
			}
			send( s, buf, nread, 0);
		}
	}

}
