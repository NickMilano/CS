// -----------------------------------------------------------
//   NAME : Nick Milano                         User ID: nrmilano
//   DUE DATE : 4/5/2019
//   PROGRAM ASSIGNMENT #4
//   FILE NAME : thread-support.cpp
//   PROGRAM PURPOSE :
// 	Implementations of functions
// -----------------------------------------------------------
#include <stdio.h>
#include "thread.h"

//----------------------------------------------
// FUNCTION: goto_sleep
//
// PARAMETER USAGE:
// 	N/A
// FUNCTION CALLED:
//  N/A
//----------------------------------------------
void MotherEagle::goto_sleep() {
	//Printing
	sprintf(buff, "Mother eagle takes a nap.\n");
	cout << buff;

	//Wait for signal from baby
	Awake->Wait();
	//Make sure no babies are still eating
	for(j=1; j <= pots; j++)
		Eating->Wait();
}

//----------------------------------------------
// FUNCTION: food_ready
//
// PARAMETER USAGE:
// 	N/A
// FUNCTION CALLED:
//  N/A
//----------------------------------------------
void MotherEagle::food_ready() {
	//Reset potCount to full
	potCount = pots;

	//Allowing more babies to eat
	for(j=0; j <= pots; j++)
		Queue->Signal();
	//Release signaling baby
	Food->Signal();
}

//----------------------------------------------
// FUNCTION: ready_to_eat
//
// PARAMETER USAGE:
// 	N/A
// FUNCTION CALLED:
//  N/A
//----------------------------------------------
void BabyEagle::ready_to_eat() {
	//Let "pot" amount of babies in
	Queue->Wait();
	//Locking 1 at a time
	PotMutex->Wait();
	//Checking if mom is done feeding
	if(done) {
		//If there are pots left eat then exit
		if(potCount > 0) {
			//Printing
			sprintf(buff, "%*c Baby eagle %d is eating using feeding pot %d.\n", number
				, ' ', number, potCount);
			cout << buff;
			potCount--;
			//Releasing and return beacuse there is food left
			PotMutex->Signal();
			Queue->Signal();
			return;
		} else {
			//If no pots are left just release and exit
			PotMutex->Signal();
			Queue->Signal();
			Exit();
		}
	}

	//If there is no food and the mom is not done
	if(potCount == 0 && done == 0) {
		//Print we are waking the mother
		sprintf(buff, "%*c Baby eagle %d sees all feeding pots are empty and wakes up the mother.\n", number
                                , ' ', number);
		cout << buff;
		//No food pots wake up mom
		Awake->Signal();
		//Wait for mom to signal back that she is done
		Food->Wait();
	}

	//If we have food and mom isnt done we can just eat
	sprintf(buff, "%*c Baby eagle %d is eating using feeding pot %d.\n", number
                                , ' ', number, potCount);
	cout << buff;

	//Protected variable counting down
	potCount--;

	//Release Mutex so next baby can eat
	PotMutex->Signal();
}

//----------------------------------------------
// FUNCTION: finish_eating
//
// PARAMETER USAGE:
// 	N/A
// FUNCTION CALLED:
//  N/A
//----------------------------------------------
void BabyEagle::finish_eating() {
	//Signals done eating to mom
	Eating->Signal();
}
