/*
  ------------------------------------------------------------
  ANSI C IMAGE PROCESSING TEMPLATE USING DIP LIBRARY
  by D.K. Iakovidis
  ------------------------------------------------------------
*/

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include "dip.h"			

int main(void)
{
     unsigned char *inputFilename = "image268x324.raw",
                   *outputFilename = "average_blur.raw",
                   *img_name = "average_blur";
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

//   outputImage = prewitt(inputImage, rows, columns);
//   outputImage = sobel(inputImage, rows, columns);
//	 outputImage = robert_cross(inputImage, rows, columns);
//   outputImage = LoG(inputImage, rows, columns);
//   outputImage = gaussian_blur(inputImage, rows, columns);
//	 outputImage = sharpening(inputImage, rows, columns);
	 outputImage = average_blur(inputImage, rows, columns);
	 
     saveImage(outputFilename, outputImage, rows, columns);      
     deallocateImage(inputImage, rows);
     deallocateImage(outputImage, rows);  
     
     
     //convert raw to png throught python file
    char command[200];
    sprintf(command, "python raw_to_png.py %s.raw %s.png --width %d --height %d --bit_depth 8",
            img_name, img_name, columns, rows);
	
    system(command);

    return 0;
}
