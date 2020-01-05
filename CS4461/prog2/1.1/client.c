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
#define MAXBUFLEN 100
#define WINDOW 3

/*Simple function to grab seqNum from a buffer*/
int getSeq(char *buf) {
  int i = 0, j = 0;
  char arr[4];
  while(buf[i] != ' ') {
    arr[j]=buf[i];
    i++;
    j++;
  }
  return atoi(arr);
}

int main(int argc, char *argv[])
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr;
    socklen_t addr_len;
    int rv;
    int numbytes;
    int i = 0, j = 0, seqNum = 1, packetsToSend = 0, waitingAcks = 0, num = 0, expectedACK = 1;
    char message[1000], *s, *send[1000];
    char packets[1000][1000];
    char buff[4];
    char buf[MAXBUFLEN];

    /*Zeroing out memory and making sure command args are correct*/
    memset(message, 0, 1000);

    for(i = 0; i < 1000; i++)
      memset(send,0,1000);

      for(i=0; i< 1000; i++) {
        sprintf(buf, "%d", i+1);
        strcpy(packets[i], buf);
      }

    if (argc != 3) {
        fprintf(stderr,"usage: client hostname message\n");
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
            perror("client: socket");
            continue;
        }

        break;
    }

    /*Error checking*/
    if (p == NULL) {
        fprintf(stderr, "client: failed to create socket\n");
        return 2;
    }

    /*Splitting up the message into an array so we can send one at a time*/
    strcpy(message, argv[2]);
    s = strtok(message, " ");
    i=0;
    while(s != NULL) {
      strcat(packets[i+1], " ");
      strcat(packets[i+1], s);
      s = strtok(NULL, " ");
      i++;
    }
    /*Doing some output*/
    packetsToSend=i+1;
    printf("client: the message includes %d words\n", packetsToSend-1);
    sprintf(buff, " %d", i);
    strcat(packets[0], buff);

    addr_len = sizeof their_addr;

    j = 0;
    printf("client: SeqNums in the window: [1][2][3]\n");
    /*Loop while we have packets left to send or there are waiting ACKs*/
    while(j < packetsToSend || waitingAcks > 0){
      /*If there is room to send a packet we will*/
      if(waitingAcks < WINDOW && j < packetsToSend) {
        if(j >= packetsToSend)
          break;
        /*Sending packet*/
        if((numbytes = sendto( sockfd, packets[j], strlen(packets[j]), 0,
              p->ai_addr, p->ai_addrlen)) == -1) {
              perror("talker: sendto");
              exit(1);
        }
        /*Updating vars/output */
        printf("client: packet %d sent to %s\n", j+1, argv[1]);
        waitingAcks++;
        j++;
      } else{
        /*If theres no room to send we recieve*/
        if(j > packetsToSend)
          break;
          /*recieve packet*/
          recvfrom(sockfd, buf, MAXBUFLEN-1, 0, (struct sockaddr*) &their_addr, &addr_len);
          /*Update vars*/
          expectedACK++;
          num = getSeq(buf);
          waitingAcks--;
          printf("client: ACK received for SeqNum %d\n", num);
          seqNum++;
          if(seqNum > packetsToSend + 1)
            break;
            /*Window printing logic*/
            if(expectedACK == packetsToSend)
              printf("client: SeqNums in the window: [%d][][]\n", expectedACK);
            else if(expectedACK+1 == packetsToSend)
              printf("client: SeqNums in the window: [%d][%d][]\n", expectedACK, expectedACK+1);
            else if(expectedACK+2 <= packetsToSend)
              printf("client: SeqNums in the window: [%d][%d][%d]\n", expectedACK, expectedACK+1, expectedACK+2);
     }
    }
    /*All packets were sent without errors, we can free up memory*/
    printf("client: all the packets have been successfully transferred.\n");
    freeaddrinfo(servinfo);
    close(sockfd);

    return 0;
}
