// -----------------------------------------------------------
//  NAME : Nick Milano                         User ID: nrmilano
//  DUE DATE : 4/5/2019
//  PROGRAM ASSIGNMENT #4
//  FILE NAME : thread.h
//  PROGRAM PURPOSE :
// 	class definitions for threads
// -----------------------------------------------------------
#include "ThreadClass.h"

//Global Variables
extern int pots, potCount, eagles, feeds, done;
extern Semaphore *Queue;
extern Semaphore *Awake;
extern Semaphore *Eating;
extern Semaphore *PotMutex;
extern Semaphore *Food;

//Mother eagle class - defines public/private funcs and vars
class MotherEagle:public Thread {
	public:
		MotherEagle(int x);
		void goto_sleep();
		void food_ready();
	private:
		int i, j, k, feed;
		char buff[150];
		void ThreadFunc();
};

//Baby eagle class - defines public/private fucs and vars
class BabyEagle:public Thread {
	public:
		BabyEagle(int i);
		void ready_to_eat();
		void finish_eating();
	private:
		int number, i, j, k;
		char buff[150];
		void ThreadFunc();
};
