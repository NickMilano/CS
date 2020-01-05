 /******************************************************
 * Name        : Nick Milano
 * Username    : nrmilano
 * Description : implementation for all key functions
 *******************************************************/

#include "Key.h"
#include "Stats.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool initKey(Key* key, const char* filename) {

	key->pos = 0;
	key->size = 0;
	key->data = malloc(sizeof(char));
	FILE* fp = fopen(filename, "rb");

	if(fp == NULL) {
		return false;
	} else {
		int i = 0;
		int ch = '\0';
		key->data[0] = ch;
		while((ch = fgetc(fp)) != EOF) {
			key->data = realloc(key->data, sizeof(char)*(2+i));
			key->data[i] = ch;
			i++;
			key->size = i;
		}
	}

	fclose(fp);
	fp = NULL;

	return true;
}

void freeKey(Key* key) {
	free(key->data);
}

char applyKey(Key* key, Stats* stats, char ch, bool debug) {
	unsigned char updatedChar = '\0';
	unsigned char savedChar = ch;
	int keyInt = 0;
	int updatedInt = 0;
	int savedInt = savedChar;
	if(key->pos == key->size) {
		key->pos = 0;
	}
	unsigned char currentKeyChar = key->data[key->pos];
	keyInt = currentKeyChar;

	updatedChar = ch^currentKeyChar;
	updatedInt = updatedChar;

        char testChar = updatedChar;
	if(updatedChar < 32 || updatedChar > 126) {
		updatedChar = '~';
	}
	if(savedChar < 32 || savedChar > 126) {
		savedChar = '~';
	}
	if(currentKeyChar < 32 || currentKeyChar > 126) {
		currentKeyChar = '~';
	}
	updateStats(stats, updatedChar);
	if(debug == true) {	
		printf("%d '%c' ^ %d '%c' -> %d '%c'\n", savedInt, savedChar, keyInt, currentKeyChar, updatedInt, updatedChar);
	}
	key->pos = key->pos + 1;
	return testChar;

}

