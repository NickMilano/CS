 /******************************************************
 * Name        : Nick Milano
 * Username    : nrmilano
 * Description : main function of crypto program, checks for valid inputs
 *		and calls all neccessary functions
 *******************************************************/

#include "Key.h"
#include "Stats.h"
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char** argv)
{
	bool debug = false;
	if(argc < 4)  {
		printf("Crypto <input file> <output file> <key file> [debug]\n");
		return 0;	
	} else if(argc == 5) {
		debug = true;
	}
	
	FILE* finput = fopen(argv[1], "r");
	if(finput == NULL) {
		printf("Failed to open input file: %s\n", argv[1]);
		return 0;
	} else {
	fclose(finput);
	finput = NULL;
	}

	FILE* foutput = fopen(argv[2], "wb");
	if(foutput == NULL) {
		printf("Failed to open output file: %s\n", argv[2]);
		return 0;
	} else {
	fclose(foutput);
	foutput = NULL;
	}

	FILE* fp = fopen(argv[3], "rb");
	if(fp == NULL) {
	
		printf("Failed to load key file: %s\n", argv[3]);
		return 0;
	} else {
	fclose(fp);
	fp = NULL;
	}

	finput = fopen(argv[1], "r");
	foutput = fopen(argv[2], "wb");
	Key key;
	initKey(&key, argv[3]);

	Stats stats;
	initStats(&stats);

	int ch = '\0';

	while((ch = fgetc(finput)) != EOF) {
		ch = applyKey(&key, &stats, ch, debug);
		fputc(ch, foutput);
	}

	printStats(&stats);
	freeKey(&key);
	fclose(foutput);
	foutput = NULL;
	fclose(finput);
	finput = NULL;

   return 0;
}

