 /******************************************************
 * Name        : Nick Milano
 * Username    : nrmilano
 * Description : implementation of all stats functions
 *******************************************************/

#include <stdio.h>
#include "Stats.h"


void initStats(Stats* stats) {
	stats->letters = 0;
	stats->spaces = 0;
	stats->numbers = 0;
	stats->other = 0;
}

void updateStats(Stats* stats, char ch) {
	if(ch == ' ') {
		stats->spaces = stats->spaces + 1;
	} else if(ch >='0' && ch <='9') {
		stats->numbers = stats->numbers + 1;
	} else if((ch >='A' && ch <='Z') || (ch >='a' && ch<='z')) {
		stats->letters = stats->letters + 1;
	} else {
		stats->other = stats->other + 1;
	}
}

void printStats(Stats* stats) {
	int total = stats->letters + stats->spaces + stats->numbers + stats->other;
	double percentL = ((double)stats->letters/total)*100;
	double percentS = ((double)stats->spaces/total)*100;
	double percentN = ((double)stats->numbers/total)*100;
	double percentO = ((double)stats->other/total)*100;
	printf("Output %d characters: %.2f%% letters, %.2f%% spaces, %.2f%% numbers, %.2f%% other\n", total, percentL, percentS, percentN, percentO);
}


