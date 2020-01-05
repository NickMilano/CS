// -----------------------------------------------------------
// NAME : Nick Milano                         User ID: nrmilano
// DUE DATE : 4/19/2019
// PROGRAM ASSIGNMENT #5
//  FILE NAME : thread.cpp
//  PROGRAM PURPOSE :
// 	class implementation of threads
// -----------------------------------------------------------
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "thread.h"

static ChristmasMonitor Christmas("ChristmasMonitor");

//----------------------------------------------
// FUNCTION: SantaThread- constructor
//
// PARAMETER USAGE:
// 	trips - sets up number of trips we will do
// FUNCTION CALLED:
//  N/A
//----------------------------------------------
SantaThread::SantaThread(char *Name,int trips):Thread(Name),tripCount(trips) {
};

//----------------------------------------------
// FUNCTION: ElvesThread- constructor
//
// PARAMETER USAGE:
// 	number - sets the elfID for printing purposes
// FUNCTION CALLED:
//  N/A
//----------------------------------------------
ElvesThread::ElvesThread(char *Name,int number):Thread(Name),elfID(number) {
};

//----------------------------------------------
// FUNCTION: ReindeerThread- constructor
//
// PARAMETER USAGE:
// 	number - sets up reindeerID for printing
// FUNCTION CALLED:
//  N/A
//----------------------------------------------
ReindeerThread::ReindeerThread(char *Name, int number, int x):Thread(Name), reindeerID(number), maxReindeer(x) {
};

void SantaThread::ThreadFunc() {
	Thread::ThreadFunc();

	//Init some vars
	int i=0,j,k, status;
	char buff[100];

	//Started
	sprintf(buff, "Santa thread starts\n");
	cout << buff;

	while(i<tripCount) {
		//Going to sleep until needed
		status = Christmas.Sleep();
		//cout << status << endl;
		//Woken up what to do?
		if(status==1) {
			//Get Sleigh ready and attach reindeer
			Christmas.ReleaseRein();
			Christmas.AttachRein();
			//Time to deliver
			Christmas.Deliver(i+1);
			srand(time(NULL));
			j = rand() % 10;
			for(k=0; k < j; k++)
				Delay();
			//Another trip is done let the reindeer on vacation
			i++;
			Christmas.DetachSleigh(i, tripCount);
		}

		if(status==2) {
			//Santa is going to help the elves
			sprintf(buff, "Santa is helping elves\n");
			cout << buff;
			//Delay for random time "solving problem"
			srand(time(NULL));
			j = rand() % 10;
			for(k=0; k < j; k++)
				Delay();
			//Problem is solved we can release the elves
			Christmas.ReleaseElves();
			i++;
		}

	}
	// sprintf(buff, "After (%d) deliveries, Santa retires and is on vacation!\n", tripCount);
	// cout << buff;
	// exit(0);
}

void ElvesThread::ThreadFunc() {
	Thread::ThreadFunc();

	//Init some vars
	int i=0,j,k;
	char buff[100];

	//Started
	sprintf(buff, "          Elf %d starts.\n", elfID);
	cout << buff;

	while(1) {
	//Making Toys
	srand(time(NULL));
	j = rand() % 10;
	for(k=0; k < j; k++)
		Delay();

	//Have a question for Santa
	Christmas.AskQuestion(elfID);

	//Problem is solved, resting
	srand(time(NULL));
	j = rand() % 10;
	for(k=0; k < j; k++)
		Delay();
	}
}

void ReindeerThread::ThreadFunc() {
	Thread::ThreadFunc();

	//Init some vars
	int i=0,j,k;
	char buff[100];
	//Started
	sprintf(buff, "     Reindeer %d starts\n", reindeerID);
	cout << buff;

	while(1) {
	//Tanning on the beach
	srand(time(NULL));
	j = rand() % 10;
	for(k=0; k < j; k++)
		Delay();

	Christmas.ReindeerBack(reindeerID, maxReindeer);
	Christmas.WaitOthers(reindeerID,maxReindeer);

	Christmas.WaitSleigh();
	Christmas.FlyOff();
	}
}

ChristmasMonitor::ChristmasMonitor(char* Name): Monitor(Name, HOARE) {
	Question = new Condition("Question");
	ReindeerWaiting = new Condition("ReindeerWaiting");
	Sleeping = new Condition("Sleeping");
	ElfQueue = new Condition("ElfQ");
	SantaWait = new Condition("SantaWait");
	SantaGo = new Condition("SantaGo");
	WaitForSanta = new Condition("WFS");
	Takeoff = new Condition("Takeoff");
	Sleigh = new Condition("Sleigh");
	Answer = new Condition("Answer");
	WakingReindeer = new Condition("WakingReindeer");

	elfWaiting=0;
	elfQueue=0;
	reinWaiting=0;
	elfReady=0;
	reinReady=0;
	reinBack=0;
	wakingID=0;
	reinNeedSleigh=0;
	reinAttached=0;
	sleighNeeded=0;
	totalRein=0;
	sleeping=0;
	needSleigh=0;
	reindeerFlyoff=0;
	waitingForSanta=0;
	readyToGo=0;
	status=0;
};

void ChristmasMonitor::AskQuestion(int id) {

	MonitorBegin();
	sprintf(buff, "          Elf %d has a problem\n", id);
	cout << buff;

	if(elfWaiting > 2 || answer==1 || elfQueue>0) {
		//There is already elves asking question wait for next group
		sprintf(buff, "          Elf %d in Q\n", id);
	cout << buff;
		elfQueue++;
		ElfQueue->Wait();
		sprintf(buff, "          Elf %d out Q\n", id);
		cout << buff;
		elfQueue--;
	}

	if(elfWaiting <= 2) {
		elfIDs[elfWaiting]=id;
		elfWaiting++;
		if(elfWaiting < 3 && elfQueue != 0)
			ElfQueue->Signal();
		answer=0;
		if(elfWaiting==3) {
			sprintf(buff, "          Elves %d, %d, %d wake up Santa\n", elfIDs[0], elfIDs[1], elfIDs[2]);
			cout << buff;
			elfReady=1;
			Sleeping->Signal();
		}

		if(answer==0)
			Question->Wait();
		}

		if(elfWaiting==3) {
			sprintf(buff, "          Elves %d, %d, %d return to work\n", elfIDs[0], elfIDs[1], elfIDs[2]);
			cout << buff;

		}

		elfWaiting--;

	if(elfWaiting==0) {
		answer=0;
		ElfQueue->Signal();
	} else {
		Question->Signal();
	}



	MonitorEnd();
}

void ChristmasMonitor::ReleaseElves() {
	MonitorBegin();
	sprintf(buff, "Santa answers the question posted by elves %d, %d, %d\n", elfIDs[0], elfIDs[1], elfIDs[2]);
	cout << buff;
	elfReady=0;
	answer=1;
	Question->Signal();
	MonitorEnd();
}



int ChristmasMonitor::Sleep() {
	MonitorBegin();
	if(reinReady==1) {
		sleeping=0;
		status=1;
		sprintf(buff, "Santa has no time to sleep the Reindeer need him\n");
		cout << buff;
	} else if(elfReady==1) {
		sleeping=0;
		status=2;
		sprintf(buff, "Santa has no time to sleep the Elves need him\n");
		cout << buff;
	} else {
		sleeping = 1;
			sprintf(buff, "Santa is sleeping\n");
			cout << buff;
		Sleeping->Wait();
			sprintf(buff, "Santa is awake\n");
			cout << buff;
		sleeping = 0;
		if(reinReady==1)
			status=1;
		else if(elfReady==1)
			status=2;
	}

	MonitorEnd();
	return status;
}

void ChristmasMonitor::ReindeerBack(int id, int max) {
	MonitorBegin();
	reinBack++;
	if(reinBack < max) {
		sprintf(buff,"     Reindeer %d returns\n", id);
		cout << buff;
	} else {
		sprintf(buff,"     The last reindeer %d wakes up the Santa\n", id);
		cout << buff;
		wakingID=id;
		reinBack=0;
	}
	MonitorEnd();
}

void ChristmasMonitor::WaitOthers(int id, int max) {
	MonitorBegin();
	totalRein = max;
//	cout << "max:" << max << endl;
	reinWaiting++;
	//		cout<< "# Rein waiting before: " << reinWaiting << endl;
	reinReady=0;
	needSleigh=0;
	if(id != wakingID) {
		if(reinWaiting < max){
		//	cout<< "waiting guy wait"<< endl;
			ReindeerWaiting->Wait(); //cout<< "waiting guy released"<< endl;
		}else {
			WakingReindeer->Signal();
		}
	} else {
		if(reinWaiting < max) {
			//cout<< "signalling guy wait!"<< endl;
			WakingReindeer->Wait();
			reinReady=1;
			needSleigh=0;
			Sleeping->Signal();
		} else {
			reinReady=1;
			needSleigh=0;
			Sleeping->Signal();
		}
		if(needSleigh==0)
			ReindeerWaiting->Wait();

		//cout<< "signal guy released"<< endl;
	}
	reinWaiting--;
	//cout<< "# Rein waiting after decreaase: " << reinWaiting << endl;
	//Find other reindeer that need to be released
	if(reinWaiting == 0)
		needSleigh=0;
	else
		ReindeerWaiting->Signal();
	if(reinWaiting>0)
		ReindeerWaiting->Signal();
		//cout<< "# Rein waiting after: " << reinWaiting << endl;
	MonitorEnd();
}

void ChristmasMonitor::WaitSleigh() {
	MonitorBegin();
	reinNeedSleigh++;
	if(reinNeedSleigh < totalRein) {
		Sleigh->Wait();
		//reinAttached++
		reinNeedSleigh--;
	} else {
		sleighNeeded=0;
		SantaWait->Signal();
		if(sleighNeeded==0)
			Sleigh->Wait();
		//reinAttached++;
		reinNeedSleigh--;
	}

	if(reinNeedSleigh == 0)
		sleighNeeded=0;
	else
		Sleigh->Signal();
	MonitorEnd();
}

void ChristmasMonitor::FlyOff() {
	MonitorBegin();
	readyToGo++;
	if(readyToGo < totalRein) {
		Takeoff->Wait();
		readyToGo--;
	} else {
		reindeerFlyoff=0;
		SantaGo->Signal();
		if(reindeerFlyoff==0)
			Takeoff->Wait();
		readyToGo--;
	}

	if(readyToGo == 0)
		reindeerFlyoff=0;
	else
		Takeoff->Signal();
	MonitorEnd();
}

void ChristmasMonitor::AttachRein() {
	MonitorBegin();
	//If not all reindeer are ready we wait
	if(reinNeedSleigh != totalRein)
		SantaWait->Wait();
	//Attach reindeer to sleigh
	sleighNeeded=1;
	Sleigh->Signal();
	MonitorEnd();
}

void ChristmasMonitor::Deliver(int num) {
	MonitorBegin();
	if(readyToGo != totalRein)
		SantaGo->Wait();
	sprintf(buff, "The team flies off (%d)!\n", num);
	cout << buff;
	MonitorEnd();
}

void ChristmasMonitor::DetachSleigh(int num, int numTrips) {
	MonitorBegin();
	if(num==numTrips) {
		sprintf(buff, "After (%d) deliveries, Santa retires and is on vacation!\n", num);
		cout << buff;
		exit(0);
	}
	reindeerFlyoff=1;
	reinWaiting=0;
	wakingID=-1;
	Takeoff->Signal();
	MonitorEnd();
}


void ChristmasMonitor::ReleaseRein() {
	MonitorBegin();
	sprintf(buff, "Santa is preparing sleighs\n");
	cout << buff;
	reinReady=0;
	needSleigh=1;
	ReindeerWaiting->Signal();
	MonitorEnd();
}
