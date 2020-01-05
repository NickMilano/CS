// -----------------------------------------------------------
//  NAME : Nick Milano                         User ID: nrmilano
//  DUE DATE : 4/5/2019
//  PROGRAM ASSIGNMENT #4
//  FILE NAME : thread.cpp
//  PROGRAM PURPOSE :
// 	class implementation of threads
// -----------------------------------------------------------
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "thread.h"

//----------------------------------------------
// FUNCTION: MotherEagle - constructor
//
// PARAMETER USAGE:
// 	f - sets number of feeds to f
// FUNCTION CALLED:
//  N/A
//----------------------------------------------
MotherEagle::MotherEagle(int f):feed(f) {
}

//----------------------------------------------
// FUNCTION: BabyEagle - constructor
//
// PARAMETER USAGE:
// 	i - sets baby number to this for printing etc
// FUNCTION CALLED:
//  N/A
//----------------------------------------------
BabyEagle::BabyEagle(int i):number(i) {
}

//----------------------------------------------
// FUNCTION: MotherEagle
//
// PARAMETER USAGE:
// 	N/A
// FUNCTION CALLED:
//  goto_sleep, food_ready
//----------------------------------------------
void MotherEagle::ThreadFunc() {
	Thread::ThreadFunc();

	//Started
	sprintf(buff, "Mother eagle started.\n");
	cout << buff;

	//Loop for number of feeds
	for(i=0; i < feed;) {
		//start by sleeping
		goto_sleep();
		//Once released we wait some random amount of time
		srand(time(NULL));
		j = rand() % 10;
		for(k=0; k < j; k++)
			Delay();
		//Start feeding
		sprintf(buff, "Mother eagle says \"Feeding (%d)\"\n", i+1);
		cout << buff;
		//Increment i here to prevent race conditions
		i++;
		//We check i == feed here because if it is the last feed
		//we want done to be set to 1 before the babies return
		//if the babies are released in food_ready and mother pauses
		//there is a potential for race condition
		if(i == feed)
			done = 1;
		//Release baby and food is ready
		food_ready();
		//Random wait
    srand(time(NULL));
    j = rand() % 10;
    for(k=0; k < j; k++)
      Delay();
	}

	//Retired
	sprintf(buff,"Mother eagle retires after serving %d feedings. Game ends!!!\n",feed);
	cout << buff;
}

//----------------------------------------------
// FUNCTION: BabyEagle
//
// PARAMETER USAGE:
// 	N/A
// FUNCTION CALLED:
//  ready_to_eat, finish_eating
//----------------------------------------------
void BabyEagle::ThreadFunc() {
	Thread::ThreadFunc();

	//Started
	sprintf(buff, "%*c Baby eagle %d started.\n", number, ' ', number);
	cout << buff;

	//Infinite loop
	while(1) {
		//Playing for random time
    srand(time(NULL));
    j = rand() % 10;
    for(k=0; k < j; k++)
      Delay();

		//Ready to eat
    sprintf(buff, "%*c Baby eagle %d ready to eat.\n", number, ' ', number);
	  cout << buff;
		ready_to_eat();
		//Eating for random time
    srand(time(NULL));
    j = rand() % 10;
    for(k=0; k < j; k++)
      Delay();
		//Done Eating
		finish_eating();
    sprintf(buff, "%*c Baby eagle %d finishes eating.\n", number, ' ', number);
    cout << buff;

	}
}
