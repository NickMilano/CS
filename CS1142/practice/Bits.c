/************************************************************
 * Name        : Nick Milano
 * Username    : nrmilano
 * Description : Calculates number of bits to represent a given number
 ***********************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

  //Checks for proper amount of inputs
  if(argc < 2) {
    printf("Bits <integer N>\n");
    return 0;
  }

  //Declaring variables
  int n = atoi(argv[1]);
  int divides = 0;

  //Checks if the input is positive
  if(n < 0) {
    printf("Illegal input\n");
    return 0;
  }

  //Calculating number of bits needed
  while(n >= 1) {
    n = n/2;
    divides = divides + 1;
  }

  //Printing
  printf("%d\n", divides);

}
