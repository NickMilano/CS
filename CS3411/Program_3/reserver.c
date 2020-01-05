/*-------------------------------------
 * Nick Milano
 * Program 3
 * reserver.c
 * C code that acts as the server, assigns
 * a random port when starts up, server will
 * not close until it recieves SIGINT (Ctrl+C)
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

/*Functions from original program used for testing*/
void printsin(s_in, s1, s2)
struct sockaddr_in *s_in; char *s1, *s2;
{
	printf ("Program: %s\n%s ", s1, s2);
	printf ("(%d,%d)\n", s_in->sin_addr.s_addr, s_in->sin_port);
}

int main() {
	/*Init some variables for the socket and output*/
	int listener, conn, length, i=0;
	struct sockaddr_in s1, s2;
	char msg[200]="";
	char buf[100];
	char *argv2[200];
	char *token;

	/*Creating socket fd*/
	if((listener = socket( AF_INET, SOCK_STREAM, 0 ))==-1) return 1; /*Returns if error*/
	
	/*Setting up port*/	
	bzero((char *) &s1, sizeof(s1));
	s1.sin_family = (short) AF_INET;
	s1.sin_addr.s_addr = htonl(INADDR_ANY);
	s1.sin_port = htons(0); /* bind() will gimme unique port. */
	bind(listener, (struct sockaddr *)&s1, sizeof(s1)); /*Returns if error*/
	length = sizeof(s1);
	if(getsockname(listener, (struct sockaddr *)&s1, &length)==-1) return -1;
	/*Printing out the port so we know what port for clients*/
	sprintf(buf,"RSTREAM:: assigned port number %d\n", ntohs(s1.sin_port));
	write(1,buf,strlen(buf));

	if(listen(listener,1)==-1) return -1; /*Returns if error*/
	length = sizeof(s2);

    while (1==1) {
	/*Getting fd for accepted socket*/
        if((conn=accept(listener, (struct sockaddr *)&s2, &length))==-1)return-1;

	sprintf(buf,"Accepted connection from client\n");
	write(1,buf,strlen(buf));
        
        /*Reading in whole message from client*/
	read(conn, msg, 200);	
	i=0;
	/*Parsing input by commas*/
	token = strtok(msg,",");
	while(token != NULL) {
		argv2[i++]=token;
		token = strtok(NULL,",");
	}
	

	/*Fork to child and exec the commands*/
	if(fork()==0) {
		/*Setting the stdout and stderr to the socket fd*/
		dup2(conn,2);
		dup2(conn,1);
		execvp(argv2[0],argv2);
	} 
	/*End connection*/
        close(conn);
    }
}

