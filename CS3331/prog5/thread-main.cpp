// -----------------------------------------------------------
// NAME : Nick Milano                         User ID: nrmilano
// DUE DATE : 4/19/2019
// PROGRAM ASSIGNMENT #5
// FILE NAME : thread-main.cpp
// PROGRAM PURPOSE :
// -----------------------------------------------------------

#include <iostream>
#include <stdio.h>
#include "thread.h"
#include "ThreadClass.h"

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
	int elves, reindeers, trips;
	int i = 1;
	strstream name;

	//Logic to setup passed variables
	if(atoi(argv[1])==0)
		elves = 7;
	else
		elves = atoi(argv[1]);

        if(atoi(argv[2])==0)
                reindeers = 0;//9;
        else
                reindeers = atoi(argv[2]);

        if(atoi(argv[3])==0)
                trips= 5;
        else
                trips= atoi(argv[3]);

	//Setting up threads
	SantaThread santa("Santa",trips);
	santa.Begin();

	ElvesThread *elf[elves];
	for(i=1; i<=elves; i++) {
		name.seekp(0, ios::beg);
		name << "Elf" << i << '\0';
		elf[i] = new ElvesThread(name.str(), i);
		elf[i]->Begin();
	}

	ReindeerThread *rein[reindeers];
	for(i=1; i<=reindeers; i++) {
		name.seekp(0, ios::beg);
		name << "Reindeer" << i << '\0';
		rein[i] = new ReindeerThread(name.str(), i,reindeers);
		rein[i]->Begin();
	}

	//Joining all the threads
	santa.Join();

	for(i=1; i <= elves; i++) {
		elf[i]->Join();
	}

	for(i=1; i <= reindeers; i++) {
		rein[i]->Join();
	}

	return 0;
}
