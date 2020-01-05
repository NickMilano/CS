/* Nick Milano - CS4461 - Programming Assignment 1 - client.c*/
/* Client based on talker.c from 6.3
 Client may possibly double send due to unreliable send as well as
 slow response from server, server handles any duplicate packets to make
 sure output is not effected*/

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
#include "unreliable.h"

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
    int i = 0, j = 0, seqNum = 1, packetsToSend = 0, waitingAcks = 0, expectedACK = 1;
    char message[1000], *s, *send[1000];
    char packets[1000][1000];
    char buff[4];
    char buf[MAXBUFLEN];
    int acks[1000];

    /*Zeroing out memory and making sure command args are correct*/
    memset(message, 0, 1000);

    bzero(buf, MAXBUFLEN);

    for(i = 0; i < 1000; i++)
      memset(send,0,1000);

    for(i = 0; i < 1000; i++)
      acks[i] = 0;

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

    /*Setting up select and timeout*/
    fd_set readfds;
    struct timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;
    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds);

    /*Splitting up the message into an array so we can send one at a time*/
    strcpy(message, argv[2]);
    s = strtok(message, " ");
    i=0;
    while(s != NULL) {
      strcat(packets[i+1], " ");
      strcat(packets[i+1], s);
      send[i] = s;
      s = strtok(NULL, " ");
      i++;
    }
    /*Doing some output*/
    packetsToSend=i+1;
    printf("client: the message includes %d words\n", packetsToSend-1);
    sprintf(buff, " %d", i);
    strcat(packets[0], buff);
    /*Adding new line at end so server knows where the end is*/
    /*strcat(packets[i], "\n");*/

    addr_len = sizeof their_addr;

    /*Sending the "SYN" packet first*/
    j = 0;
    printf("client: SeqNums in the window: [1][2][3]\n");
    if((numbytes = unreliable_sendto(sockfd, packets[expectedACK-1], strlen(packets[expectedACK-1]), 0,
            p->ai_addr, p->ai_addrlen)) == -1) {
            perror("client: unreliable_sendto");
            exit(1);
    }

    /*Using select to detect timeouts/failed packets sent*/
    while(select(sockfd+1, &readfds, NULL, NULL, &timeout) == 0) {
      /*Getting timeouts keep trying to resend*/
      if((numbytes = unreliable_sendto(sockfd, packets[expectedACK-1], strlen(packets[expectedACK-1]), 0,
              p->ai_addr, p->ai_addrlen)) == -1) {
              perror("client: unreliable_sendto");
              exit(1);
      }

      timeout.tv_sec = 3;
      timeout.tv_usec = 0;
      FD_ZERO(&readfds);
      FD_SET(sockfd, &readfds);

    }

    /*Once we break the while loop we know we have something on the socket so read it*/
    recvfrom(sockfd, buf, MAXBUFLEN-1, 0, (struct sockaddr*) &their_addr, &addr_len);
    printf("client: received %s\n", buf);
    /*Setting some variables*/
    acks[1]=1;
    expectedACK++;
    j=1;

    /*Loop while we still need to send packets or some packets have not been ACKd by server*/
    while(j < packetsToSend || waitingAcks > 0){
      /*If theres room in the window send packet*/
      while(waitingAcks < WINDOW) {
        if(acks[expectedACK] == 1) {
          /*Packet was acked out of order, since we know the server ACKd it we can skip over it*/
          expectedACK++;
          waitingAcks--;
          /*Window printing logic*/
          if(expectedACK == packetsToSend)
            printf("client: SeqNums in the window: [%d][][]\n", expectedACK);
          else if(expectedACK+1 == packetsToSend)
            printf("client: SeqNums in the window: [%d][%d][]\n", expectedACK, expectedACK+1);
          else if(expectedACK+2 <= packetsToSend)
            printf("client: SeqNums in the window: [%d][%d][%d]\n", expectedACK, expectedACK+1, expectedACK+2);
          break;
        }

        /*we dont need to resend the last packet it gets caught later*/
        if(j == packetsToSend)
          break;

        /*Send nexpt packet*/
        if((numbytes = unreliable_sendto(sockfd, packets[j], strlen(packets[j]), 0,
                p->ai_addr, p->ai_addrlen)) == -1) {
                perror("client: unreliable_sendto");
                exit(1);
        }

        /*increment*/
        j++;
        waitingAcks++;
      }

      /*Error checking to make sure we arent done*/
      if(waitingAcks == 0 && j == packetsToSend) {
        break;
      }

      /*Reset timeout*/
      timeout.tv_sec = 2;
      timeout.tv_usec = 0;
      FD_ZERO(&readfds);
      FD_SET(sockfd, &readfds);

      /*Attempt to listen for a response*/
      rv = select(sockfd+1, &readfds, NULL, NULL, &timeout);

      if(rv > 0) {
        /*We have received something*/
        recvfrom(sockfd, buf, MAXBUFLEN-1, 0, (struct sockaddr*) &their_addr, &addr_len);
        printf("client: received %s\n", buf);
        /*Get the SeqNum for the ack and check it*/
        seqNum = getSeq(buf);
        if(acks[seqNum] == 1) {
          /*duplicate ACK*/
        } else {
          /*new ack*/
          acks[seqNum]=1;
          if(seqNum == expectedACK) {
            /*Got the correct ACK*/
            expectedACK++;
            waitingAcks--;
            printf("client: ACK confirmed for packet %d\n", seqNum);
            /*Window logic*/
            if(expectedACK == packetsToSend)
              printf("client: SeqNums in the window: [%d][][]\n", expectedACK);
            else if(expectedACK+1 == packetsToSend)
              printf("client: SeqNums in the window: [%d][%d][]\n", expectedACK, expectedACK+1);
            else if(expectedACK+2 <= packetsToSend)
              printf("client: SeqNums in the window: [%d][%d][%d]\n", expectedACK, expectedACK+1, expectedACK+2);
          } else {
            /*Got a packet out of order it must have dropped*/
            printf("client: ACK confirmed for packet %d, was expecting %d, resending\n", seqNum, expectedACK);
            if((numbytes = unreliable_sendto(sockfd, packets[expectedACK-1], strlen(packets[expectedACK-1]), 0,
                    p->ai_addr, p->ai_addrlen)) == -1) {
                    perror("client: unreliable_sendto");
                    exit(1);
            }
          }
        }
      } else {
        /*Timeout resend*/
        if(acks[expectedACK] != 1) {
        printf("client: No ACK receieved resending\n");
        if((numbytes = unreliable_sendto(sockfd, packets[expectedACK-1], strlen(packets[expectedACK-1]), 0,
                p->ai_addr, p->ai_addrlen)) == -1) {
                perror("client: unreliable_sendto");
                exit(1);
        }
      }
        timeout.tv_sec = 2;
        timeout.tv_usec = 0;
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);
      }
    }

    /*All packets were sent without errors, we can free up memory*/
    printf("client: all the packets have been successfully transferred.\n");
    freeaddrinfo(servinfo);
    close(sockfd);

    return 0;
}
