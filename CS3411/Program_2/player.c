/* Programming Assignment 2 - player.c 
 * Nick Milano
 * CS3411
 * Simple player program that simulates a player
 * in the card game, player simply stays in a loop
 * attempting to read in the 4 cards, adds them then send them
 * to the dealer                                               */

#include <stdio.h>
#include <unistd.h>

int main() {
	/*init vars*/
	int cards[4];
	int sum;

	while(1) {
		/*Reads in 4 cards adds them together and writes them*/
		sum = read(0, cards, sizeof(int)*4);
		sum = cards[0]+cards[1]+cards[2]+cards[3];
		write(1, &sum, sizeof(sum));	
	}
	return 0;
}
