// -----------------------------------------------------------
// NAME : Nick Milano                         User ID: nrmilano
// DUE DATE : 3/22/2019
// PROGRAM ASSIGNMENT #3
// FILE NAME : thread.cpp
// PROGRAM PURPOSE :
// Main implementation of the even odd sort, does some basic
// output to show what thread it is
// -----------------------------------------------------------
#include <iostream>
#include <stdio.h>
#include "thread.h"
using namespace std;

//Basic constructor, sets up both variables i and j
//then does a simple print to show the thread is created
SortThread::SortThread(int i):i(i+1),j(i) {
	char buffer[30];
	sprintf(buffer, "        Thread %d Created\n", i+1);
	cout << buffer;

}

// -----------------------------------------------------------
// Thread body:
// prints out the comparison then does the comparison
// swaps if needed and updates the flag variable.
// exits after.
// -----------------------------------------------------------
void SortThread::ThreadFunc() {

	//Printing using sprintf and buffer to be thread safe
	//since the whole message is prepared beforehand the output
	//cannot be broken
	char buffer[50];
	Thread::ThreadFunc();
	sprintf(buffer, "        Thread %d compares x[%d] and x[%d]\n", i, j, i);
        cout << buffer;

	//Basic comparison/swap logic
	if(x[j] > x[i]) {
		sprintf(buffer, "        Thread %d swaps x[%d] and x[%d]\n", i, j, i);
	        cout << buffer;
		temp = x[i];
		x[i] = x[j];
		x[j] = temp;
		flag = 1;
	}

	//Printing
        sprintf(buffer, "        Thread %d Exits\n", i);
        cout << buffer;
	Exit();


}
