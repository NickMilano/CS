// -----------------------------------------------------------
// NAME : Nick Milano                         User ID: nrmilano
// DUE DATE : 3/22/2019
// PROGRAM ASSIGNMENT #3
// FILE NAME : thread.cpp
// PROGRAM PURPOSE :
// Header file for SortThread
// -----------------------------------------------------------

#include "ThreadClass.h"

//Global vars from main
extern int *x;
extern int flag;

//SortThread Class - defines some private vars for indexing
//along with the ThreadFunc, constructor is used to initialize i
//which will be the main way of indexing
class SortThread : public Thread {
	
	public:
		SortThread(int i); //constructor
	
	private:
		void ThreadFunc(); // thread body
		int i, j, temp;
};
