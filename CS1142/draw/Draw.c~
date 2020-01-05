// Student stub code for ASCII Drawing assignment

#include <stdio.h>
#include <stdlib.h>

// TODO: add a parameter list and the implementation for the following 6 functions:
void initImage() 
{
}

void printImage() 
{
}

void drawPoint() 
{
} 

void drawRectangle() 
{
}

void getImageStats() 
{
}

void floodFill() 
{
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
