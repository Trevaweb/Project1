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

#define SERVER_PORT 65369
#define MAX_PENDING 5
#define MAX_LINE 256

char translate_to_pirate(char *buf);

int main(int argc, char * argv[])
{
	struct sockaddr_in sin;
	char buf[MAX_LINE];
	int len,len1;
	int s, new_s;
    char *flag;
	/* build address data structure */
	bzero((char *)&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(SERVER_PORT);

	bzero(buf, sizeof(buf));
	
	if(argc==2) {
		flag = argv[1];
	} else {
		flag = "NA";
	}
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
			
			if(strncmp (flag,"-p",2) == 0){
			    //printf("translate");
				translate_to_pirate(buf);
				//send back to client	
				len1 = strlen(buf) +1;
				send(new_s, buf, len1, 0);
			
			}

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

char translate_to_pirate(char *buf){

	char *words[17][2] = {
				{"hello","ahoy"},
				{"hi","yo-ho-ho"},
				{"my","me"},
				{"friend","bucko"},
				{"sir","mate"},
				{"miss","proud beauty"},
				{"stranger","scurvy dog"},
				{"officer","foul blaggart"},
				{"where","whar"},
				{"is","be"},
				{"the","thar"},
				{"you","ye"},
				{"water","rum"},
				{"nearby","broadside"},
				{"restroom","head"},
				{"restaurant","galley"},
				{"hotel","fleabag inn"}};

	/*const char s[2] = " ";
	char *token;

	token = strtok(buf,s);
	printf("Token: %s", token);
	while (token != NULL){
		if(strcmp(token,"\0")== 0){
			break;
		}
		/*int i;
		for(i=0;i<sizeof(words);i++){
			if(strncmp(token,words[i][0],strlen(token)) == 0){
				printf("Normal Word: %s\n Pirate Word: %s\n", token, words[i][0]);
			}
		} 
		
		token = strtok(NULL, s);
	}	*/
	printf("here");
	int i;
	for(i=0;i<=sizeof(words);i++){
		if(strcmp(buf,words[i][0]) == 0){
			printf("Normal Word: %s\n Pirate Word: %s\n", buf, words[i][0]);
		}
	} 


}