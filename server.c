/* 
 * File: server.c
 * Modified by: Sarah Diesburg for CS 3470
 * Description: Prints what is received on a TCP socket.
 */


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>  
#include <strings.h>
#include <string.h> 
#include <unistd.h>

#define SERVER_PORT 65534
#define MAX_PENDING 5
#define MAX_LINE 256

int main()
{
	struct sockaddr_in sin;
	char buf[MAX_LINE];
	int len;
	int s, new_s;
	/* build address data structure */
	bzero((char *)&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(SERVER_PORT);

	bzero(buf, sizeof(buf));
	
	/* setup passive open */
	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("simplex-talk: socket");
		exit(1);
	}
	if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
		perror("simplex-talk: bind");
		exit(1);
	}
	listen(s, MAX_PENDING);
	/* wait for connection, then receive and print text */
	while(1) {
		if ((new_s = accept(s, (struct sockaddr *)&sin, &len)) < 0) {
			perror("simplex-talk: accept");
			exit(1);
		}
		while (len = recv(new_s, buf, sizeof(buf), 0)){

			/* Logic to strip the NULL chars */
			int i;
                        for(i=0;i<sizeof(buf);i++) {
                                if(buf[i] != '\0')
                                        printf("%c", buf[i]);
                        }
			
			/* No need to fputs, as we are already printing
			   one char at a time */	
			//fputs(buf, stdout);
			bzero(buf, sizeof(buf));
			fflush(stdout);
		}
		close(new_s);
	}
}

