// -----------------------------------------------------------
//  NAME : Nick Milano                         User ID: nrmilano
//  DUE DATE : 4/26/2019
//  PROGRAM ASSIGNMENT #6
//  FILE NAME : thread.cpp
//  PROGRAM PURPOSE :
// 	class implementation of threads
// -----------------------------------------------------------

#include <iostream>
#include <stdio.h>
#include "thread.h"
#include "ThreadClass.h"

//Defining END and our Prime Array
const int END = -1;
int Primes[100];


//----------------------------------------------
// FUNCTION: MasterThread - constructor
//
// PARAMETER USAGE:
//	Name - sets thread name
// 	n - max number that we will loop to while sending
//  idMaster - storage for id for ease of printing
// FUNCTION CALLED:
//  N/A
//----------------------------------------------
MasterThread::MasterThread(char *Name, int n, int idMaster):Thread(Name){
  //Init vars
  char buff[200];

  //Set vars
  UserDefinedThreadID = idMaster;
  numbers = n;

  //We do not need to worry about locking for printing as
  //the entire message will be prepared before printing
  //therefore it cannot be interrupted and have some
  //random output
  sprintf(buff, "Master starts\n");
  cout << buff;
}


//----------------------------------------------
// FUNCTION: PrimeThread - constructor
//
// PARAMETER USAGE:
//	count - varaible to keep track of this threads position
// 	previousID - id of the previous thread so we can create a channel
//  id - our id
// FUNCTION CALLED:
//  N/A
//----------------------------------------------
PrimeThread::PrimeThread(int count, int previousID, int id) {
  //Init vars
  char buff[200];

  //Setting the threads name for ThreadMentor visuals
  ThreadName.seekp(0, ios::beg);
  ThreadName << "Prime" << id << '\0';

  //Setting vars
  UserDefinedThreadID = id;
  threadID = id;
  arrayPos = count;
  prevID = previousID;

  //Storing our ID which is our prime number in the global array
  Primes[arrayPos] = threadID;
  //When created we have no neighbor
  neighbor = NULL;

  //Creating the channel between us and the previous thread
  sprintf(buff, "Channel %d - %d", prevID, id);
  channel = new SynOneToOneChannel(buff, prevID, threadID);

  //Printing
  sprintf(buff,"%*c P%d starts and memorizes %d\n", 1+(arrayPos+1)*2, ' ',
    threadID, threadID);
  cout << buff;
}

//Destructor
PrimeThread::~PrimeThread() { delete channel; }

//----------------------------------------------
// FUNCTION: MasterThread::ThreadFunc()
//
// PARAMETER USAGE:
//	N/A
// FUNCTION CALLED:
//  N/A
//----------------------------------------------
void MasterThread::ThreadFunc() {
  Thread::ThreadFunc();
  //Init vars
  int i;
  char buff[200];

  //Start by zeroing out the Primes Array so we know where to end later
  for(i = 0; i < 100; i++)
    Primes[i]=0;

  //Start the first prime thread P2
  P2 = new PrimeThread(0, 1, 2);
  P2->Begin();

  //Loop from 3 up to the max number
  for(i = 3; i <= numbers; i++) {
    //Printing
    sprintf(buff, "Master sends %d to P2\n", i);
    cout << buff;

    //Send the value to P2
    P2->channel->Send(&i, sizeof(int));
  }

  //After sending all numbers we send END
  sprintf(buff, "Master sends END\n");
  cout << buff;

  //Send END then wait for P2 to be done
  i=END;
  P2->channel->Send(&i, sizeof(int));
  P2->Join();

  //When P2 is done we know all other threads are done so we can print
  //our final results
  sprintf(buff, "Master prints the complete result:\n  ");
  cout << buff;

  //Loop to print out all values
  //Since we init Primes to 0 at start we just loop until we hit 0's
  i = 0;
  while(Primes[i] != 0) {
    sprintf(buff, "%d ", Primes[i]);
    cout << buff;
    i++;
  }

  //Terminate master and Exit
  sprintf(buff, "\n");
  cout << buff;
  sprintf(buff, "Master terminates\n");
  cout << buff;
  Exit();
}

//----------------------------------------------
// FUNCTION: PrimeThread::ThreadFunc()
//
// PARAMETER USAGE:
//	N/A
// FUNCTION CALLED:
//  N/A
//----------------------------------------------
void PrimeThread::ThreadFunc() {
  Thread::ThreadFunc();
  //Init vars
  int num;
  char buff[200];

  //Enter infinite loop
  while(1) {
    //Wait to receive the next number
    channel->Receive(&num, sizeof(int));

    //If we receive end break from the loop
    if(num == END)
      break;

    //Otherwise print what we received
    sprintf(buff,"%*c P%d receives %d\n", 1+(arrayPos+1)*2, ' ', threadID, num);
    cout << buff;

    //Simple check to see if the number is prime
    if((num % threadID) != 0) {
      //Check if we have a neighbor already or not
      if(neighbor == NULL) {
        //No neighbor, we need to create one
        sprintf(buff,"%*c P%d creates P%d\n", 1+(arrayPos+1)*2, ' ',
          threadID, num);
        cout << buff;

        //Creating a new PrimeThread as our neighbor
        //We increase the position by 1, and pass it our ID
        //along with the number as the ID = the prime number
        neighbor = new PrimeThread(arrayPos+1, threadID, num);
        neighbor->Begin();
      } else {
        //We already have a neighbor, just pass the number
        sprintf(buff,"%*c P%d sends %d to P%d\n", 1+(arrayPos+1)*2, ' ',
          threadID, num, Primes[arrayPos+1]);
        cout << buff;

        //Sending number
        neighbor->channel->Send(&num, sizeof(int));
      }
    } else {
      //Number is not prime get rid of it
      sprintf(buff,"%*c P%d ignores %d\n", 1+(arrayPos+1)*2, ' ',
        threadID, num);
      cout << buff;
    }
  }
  //Got end time to terminate
  sprintf(buff,"%*c P%d receives END\n", 1+(arrayPos+1)*2, ' ', threadID);
  cout << buff;
  //Check if we need to send END to a neighbor
  if(neighbor != NULL) {
    //Send our neighbor END then wait for it to Exit
    neighbor->channel->Send(&num, sizeof(int));
    neighbor->Join();
  }
  //We can exit now
  Exit();
}
