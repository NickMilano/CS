// -----------------------------------------------------------
// NAME : Nick Milano                         User ID: nrmilano
// DUE DATE : 4/5/2019
// PROGRAM ASSIGNMENT #4
// FILE NAME : thread-main.cpp
// PROGRAM PURPOSE :
// Implementation of the hungry eagle game
// thread-main.cpp sets up global variables along with handling
// the command line arguments. Also sets up semaphores and starts
// and handles all the threads needed.
// -----------------------------------------------------------

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "thread.h"

int pots, potCount=0, eagles, feeds, done=0;
Semaphore *Queue;
Semaphore *Awake;
Semaphore *Eating;
Semaphore *PotMutex;
Semaphore *Food;

using namespace std;

//----------------------------------------------
// FUNCTION: main
//
// PARAMETER USAGE:
// 	argc - number of commandline arguments
//	argv - command line args
//----------------------------------------------
int main(int argc, char* argv[]) {
	//Init Vars
	char buff[200];
	int i = 0;

	//Logic to setup passed variables
	if(atoi(argv[1])==0)
		pots = 10;
	else
		pots = atoi(argv[1]);

        if(atoi(argv[2])==0)
                eagles = 10;
        else
                eagles = atoi(argv[2]);

        if(atoi(argv[3])==0)
                feeds = 10;
        else
                feeds = atoi(argv[3]);

	//Setting up semaphores
	Queue = new Semaphore("Queue",pots);
	Awake = new Semaphore("Awake",0);
	Eating = new Semaphore("Eating", pots);
	PotMutex = new Semaphore("Mutex",1);
	Food = new Semaphore("Food",0);

	//Output from main to show vars from args and start
	cout << "MAIN: There are " << eagles << " baby eagles, " << pots << " feeding pots,"
		<< " and " << feeds << " feedings." << endl;
	cout << "MAIN: Game starts!!!!!" << endl;

	//Starting Threads
	MotherEagle mother(feeds);
	mother.Begin();

	BabyEagle *babies[eagles];
	for(i=1; i <= eagles; i++) {
		babies[i] = new BabyEagle(i);
		babies[i]->Begin();
	}

	//Joining all threads so none exit early
	mother.Join();
	for(i=1; i <= eagles; i++) {
		babies[i]->Join();
	}

	return 0;

}
