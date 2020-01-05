/* Programming Assignment 2 - dealer.c
 * Nick Milano 
 * CS3411
 * Program simulates a simple card game that involves
 * using fork() and exec() to represent the players,
 * dealer handles all the printing and hosting of
 * the game */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <limits.h>

/*Simple function to swap around the cards in the deck
 * useful so we dont have to remake a deck everytime we need one
 * and we can simply call shuffle on our deck to recieve a "new deck"*/
void shuffle(int deck[]) {
	/*init vars*/
	int i = 0, n = 0, temp = 0;

	/*We loop 52 times and swap 52 times with the card at position i with a random card*/ 	
        for(i=0; i<52; i++) {
                n = i + (rand() % (52-i));
                temp = deck[i];
                deck[i]=deck[n];
                deck[n]=temp;
        }

}

/*Creates a deck*/
void makeDeck(int deck[]){
	/*init vars*/
	int i = 0, n = 1;
	/*loops 52 times and inserts 1-13 4 times into the array passed*/
	for(i = 0; i < 52; i++) {
		if(n == 14)
			n = 1;
		deck[i]=n;
		n++;
	}
	/*calls shuffle function so the deck will be random*/
	shuffle(deck);
}

/*main dealer logic in main*/
int main(int argc, char *argv[]) {
	/*init vars*/
	int i = 0, playersTiedCount = 0,playersTiedCount2 = 0, count = 0, cardsLeft=52, card=0;
	int players = atoi(argv[1]);
	int playersLeft = atoi(argv[1]);
	int forkReturn;
	int **pipes;
	int *playersStored = malloc(players*sizeof(int));
	int *playersTied = malloc((players+1)*sizeof(int));
	int toPlayer[4];
	char buff[100];
	int score[1];
	int deck[52];
	int lowest[2];

	/*setting a random seed*/
	srand(time(NULL));
	playersTied[0]=-1; /*logic for tied players set*/

	/*mallocing room for the pipes*/
	pipes = malloc((2*players)*sizeof(int*));
	for(i = 0; i < 2*players; i++)
		pipes[i] = malloc(2*sizeof(int));

	/*setting up the pipes*/
	for(i = 0; i < players*2; i++)
		pipe(pipes[i]);

	/*fork() exec() loop to create players*/
	for(i = 1; i <= players; i++) {
		forkReturn=fork(); /*save the return value so we can save the child pid*/
		if(forkReturn < 0) {
			perror("Fork");
			exit(1);
		} else if(forkReturn == 0) {
			/*child process*/
			/*use dup 2 to change the ins and outs of the child*/
			dup2(pipes[i*2-2][0],0);
			dup2(pipes[i*2-1][1],1);
			/*closing pipes*/
			close(pipes[i*2-2][0]);
			close(pipes[i*2-2][1]);
                        close(pipes[i*2-1][0]);
                        close(pipes[i*2-1][1]);
			/*run the player program*/
			execv("player", argv);
			printf("Error exec child process\n");
			exit(1);
		} else if(forkReturn > 0) {
			/*parent saves the child pid*/
			playersStored[i-1]=forkReturn;
			}
	}
	
	/*closing rest of pipes*/
	for(i = 1; i <= players; i++) {
		close(pipes[i*2-2][0]);
		close(pipes[i*2-1][1]);
	}

/*game logic loop, loops until only 1 player is left*/
while(playersLeft > 1) {
	/*creates deck and init some vars*/	
	makeDeck(deck);
	card = 0;
	cardsLeft = 52;
	i=1;
	/*dealing loop*/
	for(i=1; i<=players; i++) {
		/*logic to check if the current player is in or out*/
		while(playersStored[i-1]==-1 && i <= players)
			i++;
		if(i > players)
			break;
		/*checks if we are out of cardsm if we are reshuffle the deck*/
		if(cardsLeft==0) {
			shuffle(deck);
			card = 0;
			cardsLeft = 52;
		}
		/*Gets 4 cards from the deck*/
		toPlayer[0] = deck[card];
                toPlayer[1] = deck[card+1];
                toPlayer[2] = deck[card+2];
                toPlayer[3] = deck[card+3];
		/*output from dealer showing what cards will be dealt*/
		sprintf(buff,"Dealing [%d, %d, %d, %d] to player %d.\n", toPlayer[0], toPlayer[1], toPlayer[2], toPlayer[3], i);
		write(1, buff, strlen(buff));
		/*writing to pipe to send the cards to the player*/
		write(pipes[i*2-2][1], toPlayer, sizeof(int)*4);
		/*incrementing some counting vars*/
		card = card + 3;
		cardsLeft = cardsLeft - 4;
	}
	/*Set lowest to max int so we will guarnteed have a lower number*/
	lowest[0]=INT_MAX;
	/*determine a loser loop*/
	for(i=1; i<=players; i++) {
		/*logic to check if the current player is in or out*/
                while(playersStored[i-1]==-1 && i <= players)
                        i++;
                if(i > players)
                        break;
		/*read from the current players pipe*/
		count = read(pipes[i*2-1][0], score, sizeof(int));
  		if(count >= 0) {
			/*Print the players total*/
    			sprintf(buff,"Player %d reports a total of %d\n", i,score[0]);
			write(1, buff, strlen(buff));
			/*Check if this player is the lowest score*/
			if(score[0] < lowest[0]) {
				/*We set the players score to the lowest score, and their position in lowest array*/
				lowest[0] = score[0];
				lowest[1] = i-1;
				/*We also set the player in the tied array because if another player ties this score we want this player saved*/
				playersTied[0] = i-1;
				/*error checking logic incase we have 3 ties, then find a lower tie that wont overwrite these players in the array*/
				if(playersTiedCount > 2) {
					for(count = 2; count < players+1; count++)
						playersTied[count] = 0;
				}	
				playersTiedCount = 1;
			} else if(score[0] > lowest[0]) {
			/*do nothing because its winning*/
			} else if(score[0] == lowest[0]) {
			/*tied with lowest, added to the tied array and increase our players tied*/
				playersTied[playersTiedCount] = i-1;
				playersTiedCount++;
			} else {
    				printf("IO Error\n");
  			}
	
		}
	}		
	/*tied logic loop*/
	if(playersTiedCount > 1) {
		/*print out tie and setup var*/
		sprintf(buff,"We have a tie! Redealing.\n");
		write(1, buff, strlen(buff));
		playersTiedCount2=playersTiedCount;
		/*check for any potential no longer tied players*/
		while(playersTiedCount > 1) {
			for(i=0; i < playersTiedCount; i++) {
				/*decrease the tied count if the player is -1*/
				if(playersTied[i]==-1)
					playersTiedCount2--;
				}
			/*break from the loop if we hit 1 or 0 ties*/
			if(playersTiedCount2 <=1) break;
			/*make deck and set vars*/
        		makeDeck(deck);
        		card = 0;
        		cardsLeft = 52;
        		i=0;
			count = 0;

        		for(i=1; i<=playersTiedCount; i++) {
				/*skips players that are no longer tied*/
                		while(playersTied[i-1]==-1 && i <= playersTiedCount)
                        	i++;

                		if(i >  playersTiedCount)
                        	break;
				
				/*checks if we are out of cards and resets if we are*/
                		if(cardsLeft==0) {
                        		shuffle(deck);
                        		card = 0;
                        		cardsLeft = 52;
                		}
				/*Gets 4 cards from the deck*/
				toPlayer[0] = deck[card];
				toPlayer[1] = deck[card+1];
				toPlayer[2] = deck[card+2];
				toPlayer[3] = deck[card+3];
				/*Prints out the cards and sends them to the player*/
				sprintf(buff,"Dealing [%d, %d, %d, %d] to player %d.\n", toPlayer[0], toPlayer[1], toPlayer[2], toPlayer[3],playersTied[i-1]+1 );
				write(1, buff, strlen(buff));
				write(pipes[(playersTied[i-1]+1)*2-2][1], toPlayer, sizeof(int)*4);
				/*increasing counting vars*/
				card = card + 3;
				cardsLeft = cardsLeft - 4;
			}
			/*loser loop*/
			lowest[0]=INT_MAX;
			for(i=1; i<=playersTiedCount; i++) {
				/*skips all players at -1*/
				while(playersTied[i-1]==-1 && i <= playersTiedCount)
					i++;
				if(i > playersTiedCount)
					break;
				/*reads the score from the player*/
				count = read(pipes[(playersTied[i-1]+1)*2-1][0], score, sizeof(int));
				if(count >= 0) {
					sprintf(buff,"Player %d reports a total of %d\n", playersTied[i-1]+1,score[0]);
					write(1, buff, strlen(buff));
					/*new lowest score*/
					if(score[0] < lowest[0]) {
						lowest[0] = score[0];
						lowest[1] = playersTied[i-1];
						/*if we are not the first loop set all the players before to -1 because they will no longer be a potential lowest*/
						if(i>1) 
							for(count=0; count < i-1; count++)
								playersTied[count]=-1;		
					} else if(score[0] > lowest[0]) {
						/*set the player to -1 since they can no longer be the loser*/
						playersTied[i-1]=-1;
						
					} else if(score[0] == lowest[0]) {
					       /*if we tie again do nothing*/
					} else {
						printf("IO Error\n");
					}

				}			
			}
		}
	
	}
	/*print out the losing player and send them SIGTERM*/
	sprintf(buff,"Player %d is knocked out!\n", lowest[1]+1);
	write(1, buff, strlen(buff));
	kill(playersStored[lowest[1]],SIGTERM);
	/*we set the player to -1 so they are now skipped in every loop from now on*/
	playersStored[lowest[1]]=-1;
	/*one less player left*/
	playersLeft--;
	
}
	/*loop through all the players and find the one who didnt lose print them out*/
	for(i=0; i<players; i++) {
		if(playersStored[i] != -1) {
			sprintf(buff,"Player %d wins!\n", i+1);
			write(1, buff, strlen(buff));
		}
	}
	/*Ending the game, and freeing mem*/
	sprintf(buff,"Ending the game.\n");
	write(1, buff, strlen(buff));
	for(i=0; i < 2*players; i++)
		free(pipes[i]);
	free(pipes);	
	free(playersStored);
	free(playersTied);
	return 0;

}
