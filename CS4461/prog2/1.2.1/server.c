/* Nick Milano - CS4461 - Programming Assignement 1 - server.c*/
/* Server based on listner.c from 6.3 */

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

#define MYPORT "4950"

#define MAXBUFLEN 100
#define WINDOW 3

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

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

int main(void)
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;
    struct sockaddr_storage their_addr;
    char buf[MAXBUFLEN];
    char buff[1000];
    socklen_t addr_len;
    char s[INET6_ADDRSTRLEN];
    char words[1000][1000];
    int i = 0, j = 0, expecting = 0, goodPackets = 0, seqNum = 0;

    /*Setting memory to 0 for saftey reasons*/
    for(i = 0; i < 1000; i++)
      memset(words[i], 0, 1000);
    memset(buf, 0, MAXBUFLEN);
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    /*Error checking*/
    if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }


    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("listener: socket");
            continue;
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("listener: bind");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "listener: failed to bind socket\n");
        return 2;
    }

    freeaddrinfo(servinfo);

    /*Infinite loop to recieve packets*/
    while(1) {

      printf("server: waiting for incoming packets...\n");

      addr_len = sizeof their_addr;
      if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
          (struct sockaddr *)&their_addr, &addr_len)) == -1) {
            perror("recvfrom");
            exit(1);
          }

          printf("server: packet recieved from from %s\n",
          inet_ntop(their_addr.ss_family,
              get_in_addr((struct sockaddr *)&their_addr),
              s, sizeof s));

              /*Grabbing the SeqNum*/
              seqNum = getSeq(buf);

              if(strcmp(words[seqNum],buf) == 0){
                /*already had this packet reACKing for client*/
                printf("server: duplicate packet. reACKing\n");
                sprintf(buff, "%d ACK", seqNum);
                if((numbytes = sendto(sockfd, buff, strlen(buff), 0,
                        (struct sockaddr *) &their_addr, addr_len)) == -1) {
                        perror("talker: sendto");
                        exit(1);
                }
              } else {
              /*new packet*/
              /*if seqNum is 1 this is the SYN packet*/
              if(seqNum == 1)
                expecting = atoi(buf+2); /*set up expecting for how many words we expect*/

              /*If for some reason an extra packet is sent after all packets are received
              expecting should be reset to 0 and we can just ignore this packet*/
              if(expecting == 0) {
                printf("server: did not receive SYN ignoring\n");
              } else {
                /*Otherwise we can continue*/
                strcpy(words[seqNum], buf); /*Copy the message into the array*/
                /*Print out some info*/
                printf("server: length of the packet is %d bytes\n", (int)strlen(buf));
                printf("server: packet contains \"%s\"\n", buf);

                /*Sending ACK*/
                sprintf(buff, "%d ACK", seqNum);
                printf("server: sending ACK for SeqNum %d\n", seqNum);

                /*This was a unique packet so increment counter*/
                goodPackets++;
                  if((numbytes = sendto(sockfd, buff, strlen(buff), 0,
                      (struct sockaddr *) &their_addr, addr_len)) == -1) {
                      perror("talker: sendto");
                      exit(1);
                  }
                }
            }

            /*If we have all the packets we need from the client we can print the message*/
            if(goodPackets == expecting+1 && expecting != 0) {
              /*Bunch of printing logic*/
                printf("server: the message is \"");
                for(i=2; i < expecting+2; i++) {
                  for(j=2; j < (int)strlen(words[i]); j++) {
                      printf("%c", words[i][j]);
                  }
                  if(i != expecting+1)
                    printf(" ");
                }
                printf("\"\n");
                /*Reset variables for next message*/
                goodPackets = 0;
                expecting = 0;
                for(i = 0; i < 1000; i++)
                  memset(words[i], 0, 1000);
              }

	  /*Reset buffer*/
    memset(buf, 0, MAXBUFLEN);
  }
    /*Close socket*/
    close(sockfd);

    return 0;
}
