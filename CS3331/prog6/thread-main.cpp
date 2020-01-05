// -----------------------------------------------------------
// NAME : Nick Milano                         User ID: nrmilano
// DUE DATE : 4/26/2019
// PROGRAM ASSIGNMENT #6
// FILE NAME : thread-main.cpp
// PROGRAM PURPOSE :
//	Handles command line input and sets up the master thread
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
// FUNCTION CALLED:
//	N/A
//----------------------------------------------
int main( int argc, char *argv[] ) {
    //Init vars
    int maxNum;

    //Logic to setup passed vars
    if (atoi(argv[1])==0)
        maxNum = 30;
    else
        maxNum = atoi(argv[1]);

    //Creating the master thread and starting it
    MasterThread master("Master", maxNum, 1);
    master.Begin();
    master.Join();

    Exit();
    return 0;
}
