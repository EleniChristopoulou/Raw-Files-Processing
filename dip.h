/*
  ------------------------------------------------------------
  DYNAMIC ANSI C IMAGE MANAGEMENT LIBRARY
  by D.K. Iakovidis
  ------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>

unsigned char **allocateImage(int rows, int columns)
{
      unsigned char **image = (unsigned char **)malloc(rows * sizeof(unsigned char *));
      int i;
      for (i = 0; i < rows; i++)
      {
          image[i] = (unsigned char *)malloc(columns * sizeof(unsigned char));
      }
      return image;
}

void deallocateImage(unsigned char **image, int rows)
{
     int i;
     for (i = 0; i < rows; i++)
     {
         free(image[i]);
     }
     free(image);     
}

unsigned char **loadImage(char *filename, int rows, int columns)
{
    FILE *inputFile;
    unsigned char **image = allocateImage(rows, columns);

    int i,j;    
	if ( ((inputFile = fopen(filename,"rb")) != NULL))
	{
		for  (i = 0; i < rows; i++)
		{
			for  (j = 0; j < columns; j++)
			{
				fscanf(inputFile, "%c", &image[i][j]);
			}
		}
	} 
	else
	{
		printf("Error loading image.");
	}
	fclose(inputFile);
	return image;
}


void saveImage(char *filename, unsigned char **image, int rows, int columns)
{
    FILE *outputFile;
     
    int i,j;
   	if ( ((outputFile = fopen(filename,"wb")) != NULL))
	{
		for  (i = 0; i < rows; i++)
		{
			for  (j = 0; j < columns; j++)
			{
				fprintf(outputFile, "%c", image[i][j]);
			}
		}
	} 
	else
	{
		printf("Error saving image.");
	}
	fclose(outputFile);
}

/*
  ------------------------------------------------------------
  C IMAGE TRANSFORMATION LIBRARY
  by Christopoulou Eleni
  ------------------------------------------------------------
*/

/*
	if dy > 0
		image is translated upwards
	if dy < 0
		image is translated downwards
		
	if dx > 0
		image is translated towards the left
	if dx < 0
		image is translated towards the right
*/
unsigned char **translate(unsigned char **inputImage, int rows, int columns, double dx, double dy)
{
     int i,j;
     double ii,jj;
     unsigned char **outputImage = allocateImage(rows, columns);
     
     for (i = 0; i < rows; i++)
     {
         for (j = 0; j < columns; j++)
         {
             outputImage[i][j] = 0;
             
            ii = dy + i;
            jj = dx + j; 
			 
			 if((ii<rows) && (ii>0) && (jj<columns) && (jj>0))	 outputImage[i][j] = inputImage[(int)ii][(int)jj];
         }
     }
     return outputImage;
}

/*
	theta in degrees
	
	working clockwise for theta > 0
	working counter-clockwise for theta < 0
*/
unsigned char **rotate(unsigned char **inputImage, int rows, int columns, double theta)
{
	theta *= M_PI/180;	//converting degrees to radians in oder to work
	
     int i,j,  i0 = rows/2, j0 = columns/2;
     double ii,jj;
     unsigned char **outputImage = allocateImage(rows, columns);
     
     for (i = 0; i < rows; i++)
     {
         for (j = 0; j < columns; j++)
         {
            outputImage[i][j] = 0;
             
            ii = cos(theta)*(i-i0) - sin(theta)*(j-j0) + i0;
            jj = sin(theta)*(i-i0) + cos(theta)*(j-j0) + j0;
			 
			 if((ii<rows) && (ii>0) && (jj<columns) && (jj>0))	 outputImage[i][j] = inputImage[(int)ii][(int)jj];
         }
     }
     
     return outputImage;
}

/*
	theta in degrees
	
	sx > 1 --> slimmer
	sy > 1 --> shorter
	
	
	SPECIAL COMBOS:
	sy = -1
	sx = 1 flipped donwards
	
	sy = 1
	sx = -1 mirrored
*/
unsigned char **scale(unsigned char **inputImage, int rows, int columns, double sx, double sy)
{
	
      int i,j,  i0 = rows/2, j0 = columns/2;
     double ii,jj;
     unsigned char **outputImage = allocateImage(rows, columns);
     
     for (i = 0; i < rows; i++)
     {
         for (j = 0; j < columns; j++)
         {
            outputImage[i][j] = 0;
             
            ii = (i-i0)*sy + i0;
            jj = (j-j0)*sx + j0;
			 
			 if((ii<rows) && (ii>0) && (jj<columns) && (jj>0))	 outputImage[i][j] = inputImage[(int)ii][(int)jj];
         }
     }
     
     return outputImage;
}


