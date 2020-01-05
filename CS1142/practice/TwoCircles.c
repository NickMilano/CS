/****************************************************
 * Name        : Nick Milano
 * Username    : nrmilano
 * Description : Prints out 2 circles, their distance, and if they overlap
 ***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv) {

  if(argc < 7) {
    printf("TwoCircles <x1> <y1> <r1> <x2> <y2> <r2>\n");
    return 0;
  }

  //Initializing Variables
  double x1 = atof(argv[1]);
  double y1 = atof(argv[2]);
  double r1 = atof(argv[3]);
  double x2 = atof(argv[4]);
  double y2 = atof(argv[5]);
  double r2 = atof(argv[6]);

  //Printing out the inputted circles
  printf("Circle 1: (%.2f, %.2f) r = %.2f\n", x1, y1, r1);
  printf("Circle 2: (%.2f, %.2f) r = %.2f\n", x2, y2, r2);

  //Calculating and printing distance
  double distance = sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)));
  printf("Distance between centers = %.4f\n", distance);

  //Printing if circles intersect or not
  if(distance >= (r1+r2)) {
    printf("%.4f >= %.4f, circles do not intersect\n", distance, (r1+r2));
  }
  else {
    printf("%.4f < %.4f, circles intersect\n", distance, (r1+r2));
  }
}
