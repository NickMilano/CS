/************************************
 * Name        : Nick Milano
 * Username    : nrmilano
 * Description : Greets 3 people with a given greeting
 ***********************************/

#include <stdio.h>

int main(int argc, char** argv) {

  //Checks for proper amount of inputs
  if(argc < 5) {
    printf("Greetings <greeting> <name1> <name2> <name3>\n");
    return 0;
}

  //Prints each name with the given greeting
  printf("%s %s!\n", argv[1], argv[2]);
  printf("%s %s!\n", argv[1], argv[3]);
  printf("%s %s!\n", argv[1], argv[4]);
 
}
