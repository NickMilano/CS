
 /******************************************************
 * Name        : Nick Milano
 * Username    : nrmilano
 *Description : Uses Greedy Alg to find
 *                shortest path from East to West
 *******************************************************/

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void initArray(int height, int width, int arr[height][width]) {
        int dataIn = 0;
        for(int i = 0; i < height; i++) {
                for(int j = 0; j < width; j++) {
                        scanf("%d", &dataIn);
                        arr[i][j] = dataIn;
                }
        }
}

double getAvg(int height, int width, int arr[height][width]) {
	double avg = 0;   
	for(int i = 0; i < height; i++) {
        	for(int j = 0; j < width; j++) {
                       avg = avg + arr[i][j];
                }
        }
	
	return (avg/(height*width));
}

int getMin(int height, int width, int arr[height][width]) {
        int min = INT_MAX;
        for(int i = 0; i < height; i++) {
                for(int j = 0; j < width; j++) {
                       if(arr[i][j] < min) {
				min = arr[i][j];
			}
                }
        }

        return min;
}

int getMax(int height, int width, int arr[height][width]) {
        int max  = INT_MIN;
        for(int i = 0; i < height; i++) {
                for(int j = 0; j < width; j++) {
                       if(arr[i][j] > max) {
                                max = arr[i][j];
                        }
                }
        }

        return max;
}

void verbPrint(char direction, int currW, int currH, int currPos, int arrW) {
	
	if(arrW == 1) {
              printf("(%d,%d) %d", currW, currH, currPos);
		return;
	}

	if(currW == arrW ) {
		printf(", (%d,%d) %d, ", currW, currH, currPos);
	} else if(currW == 0) {
		printf("(%d,%d) %d", currW, currH, currPos);;
	} else {
		printf(" %c, (%d,%d) %d", direction, currW, currH, currPos);
	}	
}
struct restruct {
	int a;
	int b;
};

struct restruct greedy(int height, int width, int arr[height][width], int verb) {
	struct restruct best;
	int bestRow = 0;
	int bestCost = INT_MAX;
	best.a = bestRow;
	best.b = bestCost;
	int currPos = arr[0][0];
	int currRow = 0;
	int currW = 0;
	int currH = 0;
	int currCost = 0;
	int upCost = 0;
	int downCost = 0;
	int straightCost = 0;
	
	while(currRow < height) {
        	if(verb == 1)
                        verbPrint('x',currW, currH, currPos, width);
	while(currW < width-1){
                        if(currH==0) {
                                straightCost = currPos - arr[currH][currW+1];
                                downCost = currPos - arr[currH+1][currW+1];
				if(abs(straightCost) <= abs(downCost)) {;
					currPos = arr[currH][currW+1];
					currCost = currCost + abs(straightCost);
					currW = currW + 1;
                 			if(verb == 1)
						verbPrint('F',currW, currH, currPos, width);
				} else {
					currPos = arr[currH+1][currW+1];
					currCost = currCost + abs(downCost);
					currW = currW +1;
					currH = currH +1;
					if(verb == 1)
 						verbPrint('D',currW, currH, currPos, width);
				}


                        } else if(currH==height-1) {
                                straightCost = currPos - arr[currH][currW+1];
                                upCost = currPos - arr[currH-1][currW+1];
                                if(abs(straightCost) <= abs(upCost)) {
                                        currPos = arr[currH][currW+1];
                                        currCost = currCost + abs(straightCost);
                                        currW = currW + 1;
					if(verb == 1)
                                               verbPrint('F',currW, currH, currPos, width);
                                } else {
                                        currPos = arr[currH-1][currW+1];
                                        currCost = currCost + abs(upCost);
                                        currW = currW +1;
                                        currH = currH -1;
                                        if(verb == 1)
                                                verbPrint('U',currW, currH, currPos, width);
                                }


                        }  else {
                                straightCost = currPos - arr[currH][currW+1];
                                downCost = currPos - arr[currH+1][currW+1];
                                upCost = currPos - arr[currH-1][currW+1];
				if(abs(straightCost) <=abs(downCost) && abs(straightCost) <= abs(upCost)){
				        currPos = arr[currH][currW+1];
                                        currCost = currCost + abs(straightCost);
                                        currW = currW + 1;
                                        if(verb == 1)
                                               verbPrint('F',currW, currH, currPos, width);;
				} else if(abs(downCost) <= abs(straightCost) && abs(downCost) <= abs(upCost)){;
					currPos = arr[currH+1][currW+1];
                                        currCost = currCost + abs(downCost);
                                        currW = currW +1;
                                        currH = currH +1;
                                        if(verb == 1)
                                               verbPrint('D',currW, currH, currPos, width);
                                } else {
                                        currPos = arr[currH-1][currW+1];
                                        currCost = currCost + abs(upCost);
                                        currW = currW +1;
                                        currH = currH -1;
                                         if(verb == 1)
                                                verbPrint('U',currW, currH, currPos, width);
                                }

                        }

	}
	if(verb == 1)
		printf(", cost %d\n",currCost);
	if(currCost<bestCost) {
	        bestCost = currCost;
     		bestRow = currRow;

	}

	
	currRow = currRow + 1;
	currW = 0;
	currCost = 0;
	currH = currRow;
	currPos = arr[currH][currW];
}
	best.a=bestRow;
	best.b=bestCost;
	return best;
}

int main(int argc, char *argv[]) {
	int verb = 0;

	if(argc >= 2 && atoi(argv[1])!=0) 
		verb = 1;
	
        int width = 0;
        scanf("%d", &width);
        int height = 0;
        scanf("%d", &height);

        int points = width*height;
        printf("Data points: %d\n", points);

        int data[height][width];
 	initArray(height, width, data);
        
	double average = getAvg(height, width, data);
	printf("Avg elevation: %.2f\n", average);

	int min = getMin(height, width, data);
	printf("Min elevation: %d\n", min);

	int max = getMax(height, width, data);
        printf("Max elevation: %d\n", max);
	
	struct restruct best;	
	best = greedy(height, width, data, verb);
	printf("Best: row %d, cost %d\n", best.a, best.b);
}





