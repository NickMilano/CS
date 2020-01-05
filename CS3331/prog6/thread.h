// -----------------------------------------------------------
// NAME : Nick Milano                         User ID: nrmilano
// DUE DATE : 4/26/2019
// PROGRAM ASSIGNMENT #6
//  FILE NAME : thread.h
//  PROGRAM PURPOSE :
// 	class definitions for threads
// -----------------------------------------------------------

#include "ThreadClass.h"

//PrimeThread class - defines public/private funcs and vars
class PrimeThread:public Thread {
  public:
    PrimeThread(int count, int previousID, int id); //constructor
    ~PrimeThread(); //destructor
    SynOneToOneChannel *channel;
  private:
    void ThreadFunc();
    int arrayPos;
    int prevID;
    int threadID;
    PrimeThread *neighbor;
};

//MasterThread class - defines public/private funcs and vars
class MasterThread:public Thread {
  public:
    MasterThread(char *Name, int n, int idMaster); //constructor
  private:
    void ThreadFunc();
    int numbers;
    PrimeThread *P2;
};
