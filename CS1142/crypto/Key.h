 /******************************************************
 * Name        : Nick Milano
 * Username    : nrmilano
 * Description : header file for the key data type along with
 *		function descriptions
 *******************************************************/
#ifndef KEY_H
#define KEY_H

#include "Key.h"
#include "Stats.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
	char* data;	//Stores the actual data for this key
	int size;	//How many bytes of memory this key can store
	int pos;	//Current character to use next
} Key;

bool initKey(Key* key, const char* filename);                //Initialize Key

void freeKey(Key* key);	 // Deallocate any memory used by key

char applyKey(Key* key, Stats* stats, char ch, bool debug);  // Process ch using the current position in the key, advance key, update stats, optionally print debug line, returns output character.

#endif
