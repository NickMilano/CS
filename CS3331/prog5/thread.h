// -----------------------------------------------------------
// NAME : Nick Milano                         User ID: nrmilano
// DUE DATE : 4/19/2019
// PROGRAM ASSIGNMENT #5
//  FILE NAME : thread.h
//  PROGRAM PURPOSE :
// 	class definitions for threads
// -----------------------------------------------------------

#include "ThreadClass.h"


class ChristmasMonitor:public Monitor {
	public:
		ChristmasMonitor(char* Name);
		void AskQuestion(int id);
		void ReindeerBack(int id, int max);
		void WaitOthers(int id, int max);
		void WaitSleigh();
		void FlyOff();
		int Sleep();
		void ReleaseElves();
		void ReleaseRein();
		void AttachRein();
		void Deliver(int num);
		void DetachSleigh(int num,int numTrips);
	private:
		Condition *Question;
		Condition *ReindeerWaiting;
		Condition *WakingReindeer;
		Condition *Sleeping;
		Condition *ElfQueue;
		Condition *SantaWait;
		Condition *SantaGo;
		Condition *WaitForSanta;
		Condition *Takeoff;
		Condition *Sleigh;
		Condition *Answer;
		int elfWaiting;
		int elfQueue;
		int elfIDs[3];
		int answer;
		int reinWaiting;
		int elfReady;
		int reinReady;
		int reinBack;
		int wakingID;
		int needSleigh;
		int sleighNeeded;
		int reinNeedSleigh;
		int reinAttached;
		int reindeerFlyoff;
		int totalRein;
		int sleeping;
		int waitingForSanta;
		int readyToGo;
		int status;
		int i, j;
		char buff[100];

};

class SantaThread:public Thread {
	public:
		SantaThread(char *Name, int trips);
	private:
		int tripCount;
		void ThreadFunc();
};

class ElvesThread:public Thread {
	public:
		ElvesThread(char *Name, int number);
	private:
		int elfID;
		void ThreadFunc();
};

class ReindeerThread:public Thread {
	public:
		ReindeerThread(char *Name, int number, int x);
	private:
		int reindeerID;
		int maxReindeer;
		void ThreadFunc();
};
