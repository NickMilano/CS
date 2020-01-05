 /******************************************************
 * Name        : Nick Milano
 * Username    : nrmilano
 * Description : header file for the stats data type along with
 *		function descriptions
 *******************************************************/
#ifndef STATS_H
#define STATS_H

#include <stdio.h>

typedef struct {
   int letters;   // Count of letter characters in the output file
   int spaces;	  // Count of space characters in the output file
   int numbers;	  // Count of number characters in the output file
   int other; 	  // Count of any chracters not a letter, space, or number
} Stats;

void initStats(Stats* stats);             // Initialize a stats structure
void updateStats(Stats* stats, char ch);  // Update stats based on ch output character
void printStats(Stats* stats);            // Print out statistics about the characters processed

#endif
