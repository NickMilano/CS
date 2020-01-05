// Student stub code for ASCII Drawing assignment

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

char greyscale(double value) {
	if(value < 0.2) {
		return ' ';
	} else if(value >= 0.2 && value < 0.4) {
		return '.';
	} else if(value >= 0.4 && value < 0.6) {
		return 'o';
	} else if(value >= 0.6 && value < 0.8) {
		return 'O';
	} else {
		return '@';
	}
}
void initImage(int width, int height, double image[width][height]) {
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			image[j][i] = 0.0;
		}
	}
}

void printImage(int width, int height, double arr[width][height]) {
	char out = ' ';
	double val = 0.0;

	printf("+");
	for(int i = 0; i < width; i++) {
		printf("-");
	}
	printf("+\n");

	for(int j = 0; j < height; j++) {
		printf("|");
		for(int k = 0; k < width; k++) {
			val = arr[k][j];
			out = greyscale(val);
			printf("%c", out);
		}
		printf("|\n");
	}

	printf("+");
	for(int l = 0; l < width; l++) {
		printf("-");
	}
	printf("+\n");
}

void drawPoint(int width, int height, double image[width][height], int x, int y, double val) {
	if(x > width || x < 0 || y > height || y < 0)
		return;
	image[x][y] = val;
} 

void drawRectangle(int width, int height, double image[width][height], int left, int top, int rectangleWidth, int rectangleHeight, double color) {
	for(int i = 0; i < rectangleHeight; i++) {
		for(int j = 0; j < rectangleWidth; j++) {
			drawPoint(width, height, image, left+j, top+i, color);
		}
	}

}

void getImageStats(int width, int height, double image[width][height], double* minColor, double* maxColor, double* avgColor) {
	int size = width*height;
	*minColor = DBL_MAX;
	*maxColor = -DBL_MAX;	

	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			*avgColor = *avgColor + image[j][i];
			if(image[j][i] < *minColor)
				*minColor = image[j][i];
			if(image[j][i] > *maxColor)
				*maxColor = image[j][i];
		}
	}

	*avgColor = *avgColor/size;
}

void floodFill(int width, int height, double image[width][height], int x, int y, double color, double currColor) {
	currColor = image[x][y];
	if(currColor >= color || x >= width || x < 0 || y >= height || y < 0)
		return;
	drawPoint(width, height, image, x, y, color);
	floodFill(width, height, image, x+1, y, color, currColor);
	floodFill(width, height, image, x-1, y, color, currColor);
	floodFill(width, height, image, x, y+1, color, currColor);
	floodFill(width, height, image, x, y-1, color, currColor);
	
}

// Read in a set of drawing instructions from standard input.
// Print the resulting greyscale image as ASCII art. 
// DO NOT MODIFY!
int main(void)
{
   // Read in the size of the drawing canvas
   int width = 0;
   int height = 0;
   int result = scanf("%d %d", &width, &height);
   
   // Program only supports images that are 1x1 or bigger
   if ((width <= 0) || (height <= 0) || (result != 2))
   {
      printf("Failed to read a valid width and height from standard input!\n");
      return 0;
   }
   
   // Create the 2D arary and initialize all the greyscale values to 0.0
   double image[width][height];
   initImage(width, height, image);
   
   char command = '\0';
   double color = 0.0;
   
   // Keep reading in drawing commands until we reach the end of the input
   while (scanf(" %c", &command) == 1)
   {
      switch (command)
      {		
         case 'p': 	
         {
            // Draw a point, read in: x, y, color
            int x = 0;
            int y = 0;
            result = scanf("%d %d %lf", &x, &y, &color);
            if (result != 3)
            {
               printf("Invalid point command!\n");
               return 0;
            }
            
            drawPoint(width, height, image, x, y, color);
            break;
         }

         case 'r': 	
         {
            // Draw a rectangle, read in: x, y, w, h, color
            int left = 0;
            int top = 0;
            int rectangleWidth = 0;
            int rectangleHeight = 0;
            result = scanf("%d %d %d %d %lf", &left, &top, &rectangleWidth, &rectangleHeight, &color);
            if (result != 5)
            {
               printf("Invalid rectangle command!\n");
               return 0;
            }
         
            drawRectangle(width, height, image, left, top, rectangleWidth, rectangleHeight, color);
            break;
         }

         case 'f':
         {
            // Flood fill a color in, read in: x, y, color
            int x = 0;
            int y = 0;
            result = scanf("%d %d %lf", &x, &y, &color);
            if (result != 3)
            {
               printf("Invalid flood fill command!\n");
               return 0;
            }
            
            floodFill(width, height, image, x, y, color);
            break;
         }

         default:
         {
            printf("Unknown command!\n");
            return 0;
         }
      }
   }
   
   // Print the final image
   printImage(width, height, image);
   
   // Finally display some statistics about the image
   double minColor = 0.0;
   double maxColor = 0.0;
   double avgColor = 0.0;
   getImageStats(width, height, image, &minColor, &maxColor, &avgColor);
   printf("Color range [%.2f, %.2f], average %.4f\n", minColor, maxColor, avgColor);
}
