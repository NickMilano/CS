/* Nick Milano - CS4461 - Programming Assignment 1 - client.c*/
/* Client based on talker.c from 6.3 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SERVERPORT "4950"

int main(int argc, char *argv[])
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;
    int i = 0, j = 0;
    char message[1000], *s, *send[1000];

    /*Zeroing out memory and making sure command args are correct*/
    memset(message, 0, 1000);
    if (argc != 3) {
        fprintf(stderr,"usage: talker hostname message\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    if ((rv = getaddrinfo(argv[1], SERVERPORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    /*loop through all the results and make a socket*/
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("talker: socket");
            continue;
        }

        break;
    }

    /*Error checking*/
    if (p == NULL) {
        fprintf(stderr, "talker: failed to create socket\n");
        return 2;
    }

    /*Splitting up the message into an array so we can send one at a time*/
    strcpy(message, argv[2]);
    s = strtok(message, " ");

    while(s != NULL) {
      send[i] = s;
      s = strtok(NULL, " ");
      i++;
    }
    
    /*Adding new line at end so server knows where the end is*/
    strcat(send[i-1], "\n");

    /*Loops for each word we split*/
    for(j = 0; j < i; j++) {
      if ((numbytes = sendto( sockfd, send[j], strlen(send[j]), 0,
                p->ai_addr, p->ai_addrlen)) == -1) {
                perror("talker: sendto");
                exit(1);
      }
      printf("client: packet %d sent to %s\n", j+1, argv[1]);
    }

    /*All packets were sent without errors, we can free up memory*/
    printf("client: all the packets have been successfully transferred.\n");
    freeaddrinfo(servinfo);
    close(sockfd);

    return 0;
}
