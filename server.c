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

void translate_to_pirate(char *buf);
void translate_to_normal(char *buf);

int main(int argc, char *argv[])
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
			
			
			/* Logic to strip the NULL chars */
			int i;
            for(i=0;i<sizeof(buf);i++) {
                if(buf[i] != '\0')
                    printf("%c", buf[i]);
            }
			

			if(strncmp (flag,"-p",2) == 0){
				translate_to_pirate(buf);
				len1 = strlen(buf) +1;
				send(new_s, buf, len1, 0);
			
			} else if(strncmp (flag,"-n",2) == 0){
				translate_to_normal(buf);
				len1 = strlen(buf) +1;
				send(new_s, buf, len1, 0);
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

void translate_to_pirate(char *buf){

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

	char newPhrase[MAX_LINE];
	const char s[2] = " ";
	char *token;
	bzero(newPhrase,sizeof(newPhrase));
	token = strtok(buf,s);
	
	while (token != NULL){
		int found = 0;
		if(strcmp(token,"\0")== 0){
			break;
		}
		
		int i;
		for(i=0;i<17;i++){
			int len = strlen(words[i][0]);
			if(strncmp(token,words[i][0], len) == 0){
				strcat(newPhrase,words[i][1]);
				strcat(newPhrase," ");
				found = 1;
			}
		}
		if (!found){
			strcat(newPhrase,token);
			strcat(newPhrase," ");
		}	
		token = strtok(NULL, s);
	}	
	bzero(buf,sizeof(buf));
	strcpy(buf,newPhrase);	
}

void translate_to_normal(char *buf){

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

	char newPhrase[MAX_LINE];
	const char s[2] = " ";
	char *token;
	bzero(newPhrase,sizeof(newPhrase));
	token = strtok(buf,s);
	
	while (token != NULL){
		int found = 0;
		if(strcmp(token,"\0")== 0){
			break;
		}
		
		int i;
		for(i=0;i<17;i++){
			int len = strlen(words[i][01]);
			if(strncmp(token,words[i][1], len) == 0){
				strcat(newPhrase,words[i][0]);
				strcat(newPhrase," ");
				found = 1;
			}
		}
		if (!found){
			strcat(newPhrase,token);
			strcat(newPhrase," ");
		}	
		token = strtok(NULL, s);
	}	
	bzero(buf,sizeof(buf));
	strcpy(buf,newPhrase);	
}