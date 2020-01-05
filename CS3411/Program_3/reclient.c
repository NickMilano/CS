/*-------------------------------------
 * Nick Milano
 * Program 3
 * reclient.c
 * C code that acts as the client, connects
 * to a given host and port then sends command
 * line args to the server, reads the output 
 * back from the server and prints it out
 * -----------------------------------*/
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>
int main(int argc, char **argv) {
	/*Init vars*/
	char *remhost; unsigned short remport;
	int sock, left, num, put, i;
	char ch;
	char msg[200]="";
	struct sockaddr_in remote;
	struct hostent *h;
	
	/*Simple logic to check for correct args*/
	if(argc < 4) {
		return -1; /*Returns out if not enough args*/
	} else {
		/*Else simple logic to put together the args into a string*/
		for(i=3; i<argc; i++) {
		strcat(msg,argv[i]);
		strcat(msg,",");
		}
	}
	/*Setting up socket so we can write to it*/
	/*Uses same error checking as server*/
	remhost = argv[1]; remport = atoi(argv[2]);

	if((sock = socket(AF_INET, SOCK_STREAM, 0))==-1)return -1;

	bzero((char *) &remote, sizeof(remote));
	remote.sin_family = (short) AF_INET;
	if((h = gethostbyname(remhost))==NULL) return -1;
	bcopy((char *)h->h_addr, (char *)&remote.sin_addr, 
		  h->h_length);
	remote.sin_port = htons(remport);
	if(connect(sock, (struct sockaddr *)&remote, sizeof(remote))==-1)return -1;

	/*Simple logic to write message to the port*/
	left = sizeof(msg); put = 0;
	while(left > 0) {
		if((num = write(sock, msg+put, left)) < 0) {
			perror("inet_wstream: write");
			exit(1);
		}
		else {
			left -= num;
			put += num;
		}
	}
	/*Read output from server and write it out one character at a time*/
	while(read(sock, &ch, 1)==1) {
		sprintf(msg,"%c",ch);
		write(1, msg, strlen(msg));
	}

	write(1,"\n",1);
	return 0;
}

