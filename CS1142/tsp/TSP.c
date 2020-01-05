 /********************************************************
 *  * Name        : Nick Milano
 *  * Username    : nrmilano
 *  *Description  : Implements different heuristics
 *  *             and finds the best solution for each
 * *******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

// Constants that define the method to use when adding points to the tour
#define INSERT_FRONT      0
#define NEAREST_NEIGHBOR  1
#define SMALLEST_INCREASE 2

// Node of a linked list that stores (x, y) location of points.
// You should NOT need to modify this.
typedef struct node
{
   double x;            // x-coordinate of this point in the tour
   double y;            // y-coordinate of this point in the tour
   struct node* next;   // Pointer to the next node in the linked list
} Node;

// Function prototypes, you should NOT need to modify these.
Node* addFront(Node* first, double x, double y);
void printNode(Node* node);
void printTour(Node* first);
int tourSize(Node* first);
double distance(Node* a, Node* b);
double tourDistance(Node* first);
void freeTour(Node* first);
Node* addNearestNeighbor(Node* first, double x, double y);
Node* addSmallestIncrease(Node* first, double x, double y);

// Add a new point to the front of the tour.
// Passed a pointer to the first node in the tour, NULL if creating a new tour.
// Returns pointer to the first node in the linked list after the addition.
Node* addFront(Node* first, double x, double y)
{
	Node* nextNode = malloc(sizeof(Node));
	nextNode->x = x;
	nextNode->y = y;
	nextNode->next = first;
	

   return nextNode;
}

// Print out the point stored at the given node.
// Round to 4 decimal places and output a line feed (\n), e.g.:
// (1.2345, 6.7890)
void printNode(Node* node)
{
	if(node == NULL)
		printf("Node is NULL");
	printf("(%.4f, %.4f)\n", node->x, node->y);

}

// Print out all the points in the tour from first to last.
// Passed a pointer to the first node in the tour.
// If the first is NULL, doesn't print anything.
void printTour(Node* first)
{
	if(first == NULL)
		return;

	Node* nextNode = NULL;
	nextNode = first->next;
	printf("(%.4f, %.4f)\n", first->x, first->y);
	while(nextNode != NULL) {
		printf("(%.4f, %.4f)\n", nextNode->x, nextNode->y);
		nextNode = nextNode->next;
	}
	free(nextNode);
	nextNode = NULL;
}

// Get the number of points in the tour.
// Passed a pointer to the first node in the tour.
// If first is NULL, return a size of 0.
int tourSize(Node* first)
{
	if(first == NULL)
		return 0;

	int size = 1;
        Node* nextNode = first-> next;
	while(nextNode != NULL) {
                size = size + 1;
                nextNode = nextNode->next;
        }
	
   return size;
}

// Calculate the Euclidean distance between two nodes.
// You can assume both a and b are both not NULL.
double distance(Node* a, Node* b)
{
	double dist = 0.0;
	dist = sqrt((a->x - b->x)*(a->x - b->x)+(a->y - b->y)*(a->y - b->y));
   return dist;
}

// Calculate the total distance between all points in the tour.
// Since the tour is circular, this includes the distance from the last point back to the start.
// Passed a pointer to the first node in the tour.
// If first is NULL, return a tour length of 0.0.
double tourDistance(Node* first)
{
	if(first == NULL || first->next == NULL)
		return 0.0;

	double dist = 0.0;
	dist = dist + distance(first, first->next);

        Node* nextNode = first-> next;
	Node* nextNode2 = nextNode->next;
        while(nextNode2 != NULL) {
                dist = dist + distance(nextNode, nextNode2);
                nextNode = nextNode->next;
		nextNode2 = nextNode2->next;
        }

	dist = dist + distance(first, nextNode);

  return dist;
}

// Add a new point after the point that it is closest to.
// If there is a tie, insert it after the first such point you find.
// Passed a pointer to the first node in the tour, NULL if creating a new tour.
// Returns pointer to the first node in the linked list after the addition.
Node* addNearestNeighbor(Node* first, double x, double y)
{
        Node* newNode = malloc(sizeof(Node));
        newNode->x = x;
        newNode->y = y;
	if(first == NULL) {
		newNode->next = NULL;
		first = newNode;
  		return first;
	}
	
	if(first->next == NULL) {
		first->next = newNode;
		newNode->next = NULL;
  		return first;
	}
	
	double dist = DBL_MAX;
	Node* nearestNode;
	nearestNode = first;
	Node* testNode;
	testNode = first;

	while(testNode != NULL) {
		if(distance(newNode, testNode) < dist) {
			dist = distance(newNode, testNode);
			nearestNode = testNode;
		}
		testNode = testNode->next;
	}
	
	if(nearestNode->next == NULL) {
		nearestNode->next = newNode;
		newNode-> next = NULL;
		return first;
	}

        testNode = nearestNode->next;
	nearestNode->next = newNode;
	newNode->next = testNode;

	return first;
}


// Add a new point after the point where it results in the least increase in tour length.
// If there is a tie, insert it after the first such point you find.
// Passed a pointer to the first node in the tour, NULL if creating a new tour.
// Returns pointer to the first node in the linked list after the addition.
Node* addSmallestIncrease(Node* first, double x, double y)
{
        Node* newNode = malloc(sizeof(Node));
        newNode->x = x;
        newNode->y = y;

        if(first == NULL) {
                newNode->next = NULL;
                first = newNode;
                return first;
        }


        if(first->next == NULL) {
                first->next = newNode;
                newNode->next = NULL;
                return first;
        }

        Node* testingNode = first;
        Node* bestNode = first;
	double bestDist = DBL_MAX;

	while(testingNode != NULL) {
		double testDist = 0.0;
		double newDist = 0.0;
		double altDist = 0.0;
	//	if(testingNode-> next != NULL) {
			Node* temp = testingNode-> next;
			testDist =  distance(testingNode, temp); //oldD
			newDist = distance(testingNode, newNode); 
			altDist = distance(newNode, temp);
		//	printNode(testingNode);
		//	printNode(temp);
			printf("first dist: %f new dist: %f alt dist: %f\n ", testDist, newDist, altDist);
			if((newDist+altDist)-testDist < bestDist) {                  
	//	if( (newDist <= bestDist) && (altDist < newDist+testDist)) {
				bestNode = testingNode;
				bestDist = newDist+altDist-testDist;
				printf("new distance %f\n", bestDist);
			} 
	//	} 
		
			double firstToLast = distance(first, testingNode);
			double firstToNewToLast = distance(first, newNode)+firstToLast;
		//	printf("current best distance %f\n", bestDist);
		//	double oldToFirst = distance(testingNode, first);
		//	double newToFirst = distance(newNode, first);
			newDist = distance(testingNode, newNode);
			printf("originalD %f\n", firstToLast);
			printf("newD %f\n", firstToNewToLast);
			printf("current best dist %f\n", bestDist);
                  //     printf("distance between newNode and first  %f\n", newToFirst );
                    //    printf("distance between testNode and first %f\n", oldToFirst);
			//testDist = distance(testingNode, newNode);
			//printf("current end distance %f\n", testDist);	
			if(firstToNewToLast - firstToLast <=  bestDist) {
//if((newDist <= bestDist) && (oldToFirst > newToFirst)) {
                                bestNode = testingNode;
				printf("%f\n", newDist);
                                bestDist = firstToNewToLast - firstToLast;
				printf("new best distance at end\n");
                        }

                  
				
                 
	testingNode = testingNode->next;
	}
	
	if(bestNode->next == NULL) {
		bestNode->next = newNode;
		newNode->next = NULL;
		return first;
	}
	printf("adding new node after: ");
	printNode(bestNode);
	printf("\n");
	testingNode = bestNode->next;
	bestNode->next = newNode;
	newNode->next = testingNode;
   return first;
}

// Deallocate all the memory of the Node structures in the linked list.
// Passed a pointer to the first node in the tour.
// If first is NULL, don't do anything.
void freeTour(Node* first)
{
	Node* current = first;

	while(current != NULL) {
		Node* after = current->next;
		free(current);
		current = after;
	}
	first = NULL;
}

// Main function, you should NOT need to modify this.
// You may want to comment it out temporarily and insert your own test code during development.
int main(int argc, char** argv)
{
   // Default to inserting nodes right after the first node
   int heuristic = INSERT_FRONT;

   // If we get a command line argument it is setting the heurstic
   if (argc > 1)
      heuristic = atoi(argv[1]);

   // Start with an empty linked list
   Node* first = NULL;

   // Variables for reading in the next point from standard input
   double x = 0.0;
   double y = 0.0;

   // Read in points until we run out of data
   while (scanf("%lf %lf", &x, &y) == 2)
   {
      // Add the point to the linked list according to the heursitic set by the command line arg
      if (heuristic == INSERT_FRONT)
        first = addFront(first, x, y);
      else if (heuristic == NEAREST_NEIGHBOR)
         first = addNearestNeighbor(first, x, y);
      else if (heuristic == SMALLEST_INCREASE)
         first = addSmallestIncrease(first, x, y);
      else
      {
         printf("Invalid heuristic of %d!\n", heuristic);
         return 1;
      }
   }

   printTour(first);
   printf("Tour distance = %.4f\n", tourDistance(first));
   printf("Number of points = %d\n", tourSize(first));

   freeTour(first);
   first = NULL;

   return 0;
}
