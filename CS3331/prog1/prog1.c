/* ----------------------------------------------------------- */
/* NAME : Nick Milano                        User ID: nrmilano */
/* DUE DATE : 02/11/2019                                       */
/* PROGRAM ASSIGNMENT # 1                                      */
/* FILE NAME : prog1.c				               */
/* PROGRAM PURPOSE :                                           */
/*    prog1 takes 4 parameters from the command line then      */
/*    uses them to create 4 child processes to compute 	       */
/*    the fibonacci sequence, buffons needle problem,	       */
/*    points under sin(x), and bernoullis approx of e          */
/* ----------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <time.h>

/* ----------------------------------------------------------- */
/* FUNCTION  integrate :                                       */
/*    finds number of points under sin(x) and computes the area*/
/* PARAMETER USAGE :                                           */
/*    s - number of points to create and trest                 */
/* FUNCTION CALLED :                                           */
/*    none                                                     */
/* ----------------------------------------------------------- */
void integrate(int s) {

	/*Init some variables*/
	char buf[1000];
	int i=0;
	double pi=acos(-1), a=0, b=0, t=0;

	/*Setting a seed*/
	srand(time(NULL));
	
	/*Formatted Output and printing it to stdout*/
	sprintf(buf, "            Integration Process Started\n            Input Number  %d\n", s);
        write(1, buf, strlen(buf));

	/*Main loop for s loops*/
	for(i=0; i<s; i++) {
	
		/*generating points a and b*/
       		a=(pi)*((float) rand()/RAND_MAX);
	        b=(float) rand()/RAND_MAX;
		
		/*check if the point hit or not*/
		if(b <= sin(a))
			t=t+1; /*increment t if we hit*/
	

	}
	
	/*More output*/
        sprintf(buf, "            Total Hit %.0f\n            Estimated Area is  %.7f\n", t, (t/s)*pi);
        write(1, buf, strlen(buf));
        sprintf(buf, "            Integration Process Exits\n");
        write(1, buf, strlen(buf));

	/*exiting the child process*/
	exit(0);

}

/* ----------------------------------------------------------- */
/* FUNCTION  needle :                                          */
/*    solves buffons needle problem                            */
/* PARAMETER USAGE :                                           */
/*    r - number of test to perform                            */
/* FUNCTION CALLED :                                           */
/*    none                                                     */
/* ----------------------------------------------------------- */
void needle(int r) {

	/*Init some vars*/
	char buf[1000];
	int L=1, G=1,i=0;
	double d=0, a=0, pi=acos(-1), prob=0, t=0;
	
	/*Setting seed*/
	srand(time(NULL));

	/*Output*/
        sprintf(buf, "         Buffon's Needle Process Started\n         Input Number  %d\n", r);
        write(1, buf, strlen(buf));	

	/*Main for loop for r loops*/
	for(i=0; i<r; i++) {
		/*Generating d and a*/	
		d=(float) rand()/RAND_MAX;
        	a=(2*pi)*((float) rand()/RAND_MAX);
		/*Checking if needle hit*/
		if(d+L*sin(a) < 0 || d+L*sin(a) > G) {
			t=t+1; /*increment if hit*/
		}
	}
	
	/*Final outputs*/
	prob=t/r;
        sprintf(buf, "         Estimated Probability %.5f\n",prob);
        write(1, buf, strlen(buf));
        sprintf(buf, "         Buffon's Needle Process Exits\n");
        write(1, buf, strlen(buf));
	/*Exiting child process*/
	exit(0);
	
}


/* ----------------------------------------------------------- */
/* FUNCTION  approx :                                          */
/*    approximates e                                           */
/* PARAMETER USAGE :                                           */
/*    m - max value of the exponent when calculating           */
/* FUNCTION CALLED :                                           */
/*    none                                                     */
/* ----------------------------------------------------------- */
void approx(unsigned long m) {

	/*Init some vars*/
	char buf[1000];
	unsigned long i = 1;
	double calc = 0, diff = 0;
	double e = exp(1.0);

	/*output*/
	sprintf(buf, "   Approximation of e Process Started\n   Maximum of the Exponent %lu\n", m);
	write(1, buf, strlen(buf));
	
	/*Doing the first 10 integrations*/
	while(i<11) {
	
		/*Integration logic*/
		calc = pow((1+(1.0/i)),i);
		diff = fabs(e-calc);
		sprintf(buf, "   %18lu   %.15f   %.15f\n", i, calc, diff);
		write(1, buf, strlen(buf));
		i = i+1;
	}
	
	i=16;
	/*Rest of integrations up to m*/
	while(i<m) {

		/*Integration logic*/
                calc = pow((1+(1.0/i)),i);
                diff = fabs(e-calc);
                sprintf(buf, "   %18lu   %.15f   %.15f\n", i, calc, diff);
                write(1, buf, strlen(buf));
                i = i*2;
	
	}

	/*sprintf(buf, "   Approximation of e Process Exits\n");
	write(1, buf, strlen(buf));*/
	exit(0);

}

/* ----------------------------------------------------------- */
/* FUNCTION fibonacci :                                        */
/*    calculates the fibonacci sequence through recursion      */
/* PARAMETER USAGE :                                           */
/*    n - what fibonacci number we will calculate              */
/* FUNCTION CALLED :                                           */
/*    none                                                     */
/* ----------------------------------------------------------- */
long  fibonacci(int n) {
	
	/*Basic fib recursion method*/
	if(n==0) {
		return 0; /*Exit condition*/
	}

	if(n==1) {
		return 1;/*Exit condition*/
	}

	else {
		return fibonacci(n-1)+fibonacci(n-2);/*Recursive call*/
	}
}

/* ----------------------------------------------------------- */
/* FUNCTION  fib :                                             */
/*    does the printing for fibonacci function                 */
/* PARAMETER USAGE :                                           */
/*    n - what fibonacci number we will calculate              */
/* FUNCTION CALLED :                                           */
/*    fibonacci                                                */
/* ----------------------------------------------------------- */
void fib(int n ) {
	/*Init var*/
        char buf[1000];

	/*Mostly output, makes a call to the fibonacci function to get the output*/
        sprintf(buf, "      Fibonacci Process Started\n      Input Number %d\n", n);
        write(1, buf, strlen(buf));

        sprintf(buf, "      Fibonacci Number f(%d) is %ld\n", n, fibonacci(n));
        write(1, buf, strlen(buf));

        sprintf(buf, "      Fibonacci Process Exits\n");
        write(1, buf, strlen(buf));
        exit(0);


}

/* ----------------------------------------------------------- */
/* FUNCTION main :                                             */
/*    start of program, calls all other functions              */
/* PARAMETER USAGE :                                           */
/*    argc - number of arguments              		       */
/*    argv - command line arguments                            */
/* FUNCTION CALLED :                                           */
/*      fib, needle, integrate, approx                         */
/* ----------------------------------------------------------- */
int main(int argc, char **argv) {

	/*Init vars and get command line args*/
	int buffon = atoi(argv[3]), integ = atoi(argv[4]), status, i=0;
	unsigned long e = atol(argv[1]);
	int fibo = atoi(argv[2]);
	char buf[1000];
	pid_t pid;

	/*Printing main process output*/
	sprintf(buf,"Main Process Started\nBuffon's Needle Iterations = %d\nIntegration Iterations     = %d\nApprox. e Iterations       = %lu\n", buffon, integ, e);	
	write(1, buf, strlen(buf));

	/*Fork for fib process*/
	if((pid=fork()) < 0) {
		sprintf(buf, "fork failed\n");
		write(1, buf, strlen(buf));
	}else if (pid==0) {
		sprintf(buf,"Fibonacci Process Created\n");
		write(1, buf, strlen(buf));
		fib(fibo);
	}	

	/*Fork for needle problem*/
        if((pid=fork()) < 0) {
                sprintf(buf, "fork failed\n");
                write(1, buf, strlen(buf));
        }else if (pid==0) {
                sprintf(buf,"Buffon's Needle Process Created\n");
                write(1, buf, strlen(buf));
                needle(buffon);
        }
	
	/*Fork for integration process*/
        if((pid=fork()) < 0) {
                sprintf(buf, "fork failed\n");
                write(1, buf, strlen(buf));
        }else if (pid==0) {
                sprintf(buf,"Integration Process Created\n");
                write(1, buf, strlen(buf));
                integrate(integ);
        }

	/*Fork for approximation of e*/
        if((pid=fork()) < 0) {
                sprintf(buf, "fork failed\n");
                write(1, buf, strlen(buf));
        }else if (pid==0) {
                sprintf(buf,"Approximation of e Process Created\n");
                write(1, buf, strlen(buf));
                approx(e);
        }

	/*Main waits for all children to finish then exits*/
	sprintf(buf,"Main Waits\n");
	write(1, buf, strlen(buf));
	for(i=0; i<4; i++)
		wait(&status);
	sprintf(buf, "Main Process Exits\n");
	write(1, buf, strlen(buf));
	exit(0);
	

	return 0;

}
