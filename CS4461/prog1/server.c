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


void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;
    struct sockaddr_storage their_addr;
    char buf[MAXBUFLEN];
    socklen_t addr_len;
    char s[INET6_ADDRSTRLEN];
    char words[1000][1000];
    int n = 0, i = 0;

    /*Setting memory to 0 for saftey reasons*/
    for(i = 0; i < 1000; i++)
      memset(words[i], 0, 1000);
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
              
	      /*After getting a packet save it*/
              memset(words[n], 0, 1000);
              strcpy(words[n], buf);
              n++;

	      /*Check if this word is last*/
              if(buf[(int)strlen(buf)-1]=='\n') {
		/*If its the last word print out the message*/
                words[n-1][strlen(words[n-1])-1]='\"';
                  printf("server: received message is \"");
                  for(i = 0; i < n; i++)
                    printf("%s ", words[i]);
                  printf("\n");
                  n=0;
              }
	  /*Reset buffer*/
          memset(buf, 0, MAXBUFLEN);
  }
    /*Close socket*/
    close(sockfd);

    return 0;
}
