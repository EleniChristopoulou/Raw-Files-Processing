/*
  ------------------------------------------------------------
  ANSI C IMAGE PROCESSING TEMPLATE USING DIP LIBRARY
  by D.K. Iakovidis
  ------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dip.h"			

int main(void)
{
     unsigned char *inputFilename = "image268x324.raw",
                   *outputFilename = "scale.raw";
     int rows = 324, 
         columns = 268;
         
     unsigned char **inputImage, **outputImage, **outputImage2;

     inputImage = allocateImage(rows, columns);     
     
     inputImage = loadImage(inputFilename, rows, columns);
//   outputImage = rotate(inputImage, rows, columns, 90);
//   outputImage = translate(inputImage, rows, columns, 50, 0);
//   outputImage = translate(inputImage, rows, columns, 0, 50);
//   outputImage = translate(inputImage, rows, columns, 50, 50);
//	 outputImage = scale(inputImage, rows, columns, -1, -1);
     
     saveImage(outputFilename, outputImage, rows, columns);      
     deallocateImage(inputImage, rows);
     deallocateImage(outputImage, rows);      

     return 0;
}