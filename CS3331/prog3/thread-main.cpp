// ----------------------------------------------------------- 
//  NAME : Nick Milano                         User ID: nrmilano 
//  DUE DATE : 3/22/2019                                       
//  PROGRAM ASSIGNMENT #3                                        
//  FILE NAME : thread-main.cpp            
//  PROGRAM PURPOSE :                                           
//  Does thread creation for an implementation of even odd sort
//  in a concurrent fashion.        
// ----------------------------------------------------------- 

#include <iostream>
#include "thread.h"
using namespace std;

//Global array and flag variable to be shared between threads
int *x;
int flag = 0;

//------------------------------
// FUNCTION: main
// 	Does the input and  much of the output for the program
// 	along with managing the different threads
// 	for each iteration and pass
// PARAMETER USAGE:
// 	argc - number of commandline arguments
// 	argv - command line args
//------------------------------
int main(int argc, char *argv[]) {

	//init some vars for loops and counting
	int n, i, j, counter = 20;

	//read in the size of the array
	cin >> n;

	//populating array x
	x = new int[n];
	for(i=0; i<n; i++)
		cin >> x[i];
	
	//basic output, dont need a buffer in main because
	//it does not print while threads are running
	cout << "Concurrent Even-Odd Sort" << endl << endl;
	cout << "Number of input data = " << n << endl;
	cout << "Input array:" << endl;
        for(i=0; i<n; i++) {
                if(i == counter) {
                        counter += 20;
                        cout << endl;
                }
                cout << "  "  << x[i];
        }
	//resetting counter and doing some spacing
	counter = 20;
	cout << endl << endl << endl;

	SortThread *thread[n];
	
	//main loop for thread creation
	for(i=0; i<n; i++) {
		//Output
		cout << "Iteration " << i+1 << ":" << endl;
		cout << "    Even Pass:" << endl;

		//Creating the even pass threads and starting them
		for(j=0; j<n-1; j+=2) {
			thread[j] = new SortThread(j);
			thread[j]->Begin();
		}
		
		//joins each thread so they wait until they all complete
		for(j=0; j<n-1; j+=2)
			thread[j]->Join();

		//Output and same thread logic for odd pass
                cout << "    Odd Pass:" << endl;
                for(j=1; j<n-1; j+=2) {
                        thread[j] = new SortThread(j);
                        thread[j]->Begin();
                }

                for(j=1; j<n-1; j+=2)
                        thread[j]->Join();

		//Printing out array after both even and odd pass complete
                cout << "Result after Iteration " << i+1 << ":" << endl;
                for(j=0; j<n; j++) {
                	if(j == counter) {
                        	counter += 20;
                        	cout << endl;
                	}	
                	cout << "  "  << x[j];
        	}
	        counter = 20;

	        cout << endl << endl << endl;

		//Check if any swaps were made
		if(flag==0)
			break; //if no swaps break from loop
		else
			flag=0; //else reset the swap flag
		
	}
	
	//Printing out the final results
	cout << "Final result after iteration " << i+1 << ":" << endl;
	for(i=0; i<n; i++) {
		if(i == counter) {
			counter += 20;
			cout << endl;
		}
		cout << "  "  << x[i];
	}
        cout << endl << endl << endl;

	//Exit
	Exit();
	return 0;

}
