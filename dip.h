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

/*
  ------------------------------------------------------------
  C Common Kernels in Image Processing: Edge Detection, Blurring, Sharpening LIBRARY
  by Christopoulou Eleni
  ------------------------------------------------------------
*/


/*
	Horizontal Edge Detection: The horizontal kernel detects changes in the horizontal direction. 
	It highlights edges where there is a significant change in pixel intensity in the horizontal direction.
	
	Vertical Edge Detection: The vertical kernel detects changes in the vertical direction. 
	It highlights edges where there is a significant change in pixel intensity in the vertical direction.
*/

unsigned char **prewitt(unsigned char **inputImage, int rows, int columns)
{
	double kernel_horizontal[3][3] = {		//Horizontal Edge Detection Kernel
		{-1,0,1},
		{-1,0,1},
		{-1,0,1}
	},kernel_vertical[3][3] = {		//Vertical Edge Detection Kernel
		{-1,-1,-1},
		{0,0,0},
		{1,1,1}
	};
    
	int i,j, k,l, num = 1;
    unsigned char **outputImage = allocateImage(rows, columns);
    
    double sum;
    
    
     for (i = num; i < rows - num; i++)
     {
         for (j = num; j < columns - num; j++)
         {
    		sum = 0.0;
    		
    		for(k=0; k<3; k++){
    			for(l=0; l<3; l++){
    				sum += inputImage[i+k-num][j+l-num] * kernel_vertical[k][l]; 
				}
			}
			
			if(sum > 255)	sum = 255;
			if(sum < 0)	sum = 0;
			
	        outputImage[i][j] = (unsigned char)sum;
         }
     }
     
     return outputImage;
}

/*
	Similar to the Prewitt operator, the Sobel operator is used for edge detection
	but it gives more weight to the center pixels.
*/

unsigned char **sobel(unsigned char **inputImage, int rows, int columns)
{
	double kernel_horizontal[3][3] = {		//Horizontal Edge Detection Kernel
		{-1,0,1},
		{-2,0,2},
		{-1,0,1}
	},kernel_vertical[3][3] = {		//Vertical Edge Detection Kernel
		{-1,-2,-1},
		{0,0,0},
		{1,2,1}
	};
    
	int i,j, k,l, num = 1;
    unsigned char **outputImage = allocateImage(rows, columns);
    
    double sum;
    
    
     for (i = num; i < rows - num; i++)
     {
         for (j = num; j < columns - num; j++)
         {
    		sum = 0.0;
    		
    		for(k=0; k<3; k++){
    			for(l=0; l<3; l++){
    				sum += inputImage[i+k-num][j+l-num] * kernel_vertical[k][l]; 
				}
			}
			
			if(sum > 255)	sum = 255;
			if(sum < 0)	sum = 0;
			
	        outputImage[i][j] = (unsigned char)sum;
         }
     }
     
     return outputImage;
}

/*
	The Roberts cross operator is another edge detection operator that uses smaller 2x2 kernels.
*/

unsigned char **robert_cross(unsigned char **inputImage, int rows, int columns)
{
	double kernel_horizontal[2][2] = {		//Horizontal Edge Detection Kernel
		{1,0},
		{0,-1}
	},kernel_vertical[2][2] = {		//Vertical Edge Detection Kernel
		{0,1},
		{-1,0}
	};
    
	int i,j, k,l, num = 1;
    unsigned char **outputImage = allocateImage(rows, columns);
    
    double sum;
    
    
     for (i = num; i < rows - num; i++)
     {
         for (j = num; j < columns - num; j++)
         {
    		sum = 0.0;
    		
    		for(k=0; k<2; k++){
    			for(l=0; l<2; l++){
    				sum += inputImage[i+k-num][j+l-num] * kernel_vertical[k][l]; 
				}
			}
			
			if(sum > 255)	sum = 255;
			if(sum < 0)	sum = 0;
			
	        outputImage[i][j] = (unsigned char)sum;
         }
     }
     
     return outputImage;
}

/*
	The Laplacian of Gaussian is used for edge detection and is particularly useful 
	for detecting edges and fine details.
*/

unsigned char **LoG(unsigned char **inputImage, int rows, int columns)
{
	double kernel3by3[3][3] = {	//if kernel5by5 is gonna be use num = 1
		{0,-1,0},
		{-1,4,-1},
		{0,-1,0}
	},kernel5by5[5][5] = {		//if kernel5by5 is gonna be use num = 3
		{0,0,-1,0,0},	
		{0,-1,-2,-1,0},	
		{-1,-2,16,-2,-1},		
		{0,-1,-2,-1,0},
		{0,0,-1,0,0}
	};
    
	int i,j, k,l, num = 3;
    unsigned char **outputImage = allocateImage(rows, columns);
    
    double sum;
    
    
     for (i = num; i < rows - num; i++)
     {
         for (j = num; j < columns - num; j++)
         {
    		sum = 0.0;
    		
    		for(k=0; k<3; k++){
    			for(l=0; l<3; l++){
    				sum += inputImage[i+k-num][j+l-num] * kernel5by5[k][l]; 
				}
			}
			
			if(sum > 255)	sum = 255;
			if(sum < 0)	sum = 0;
			
	        outputImage[i][j] = (unsigned char)sum;
         }
     }
     
     return outputImage;
}


/*
	The Gaussian blur is used to reduce image noise and detail. 
	It smooths the image by averaging the pixel values with a Gaussian function.
*/

unsigned char **gaussian_blur(unsigned char **inputImage, int rows, int columns)
{
	double kernel3by3[3][3] = {	//if kernel5by5 is gonna be use num = 1 & num2 = 16
		{1,2,1},
		{2,4,2},
		{1,2,1}
	},kernel5by5[5][5] = {		//if kernel5by5 is gonna be use num = 3 & num2 = 256
		{1,4,6,4,1},		
		{4,16,24,16,4},
		{6,24,36,24,6},		
		{4,16,24,16,4},
		{1,4,6,4,1}
	};
    
	int i,j, k,l, num = 1, num2 = 16;
    unsigned char **outputImage = allocateImage(rows, columns);
    
    double sum;
    
    
     for (i = num; i < rows - num; i++)
     {
         for (j = num; j < columns - num; j++)
         {
    		sum = 0.0;
    		
    		for(k=0; k<3; k++){
    			for(l=0; l<3; l++){
    				sum += inputImage[i+k-num][j+l-num] * kernel3by3[k][l] ; 
				}
			}
			
			sum /= num2;
			
			if(sum > 255)	sum = 255;
			if(sum < 0)	sum = 0;
			
	        outputImage[i][j] = (unsigned char)sum;
         }
     }
     
     return outputImage;
}


/*
	The sharpening kernel is used to enhance the edges and details in an image.
*/

unsigned char **sharpening(unsigned char **inputImage, int rows, int columns)
{
	double kernel[3][3] = {	
		{0,-1,0},
		{-1,5,-1},
		{0,-1,0}
	};
    
	int i,j, k,l, num = 1;
    unsigned char **outputImage = allocateImage(rows, columns);
    
    double sum;
    
    
     for (i = num; i < rows - num; i++)
     {
         for (j = num; j < columns - num; j++)
         {
    		sum = 0.0;
    		
    		for(k=0; k<3; k++){
    			for(l=0; l<3; l++){
    				sum += inputImage[i+k-num][j+l-num] * kernel[k][l] ; 
				}
			}
			
			if(sum > 255)	sum = 255;
			if(sum < 0)	sum = 0;
			
	        outputImage[i][j] = (unsigned char)sum;
         }
     }
     
     return outputImage;
}


/*
	The average blur is used to blur the image by averaging the pixel 
	values within a kernel.
*/

unsigned char **average_blur(unsigned char **inputImage, int rows, int columns)
{
	double kernel[3][3] = {	
		{1,1,1},
		{1,1,1},
		{1,1,1}
	};
    
	int i,j, k,l, num = 1;
    unsigned char **outputImage = allocateImage(rows, columns);
    
    double sum;
    
    
     for (i = num; i < rows - num; i++)
     {
         for (j = num; j < columns - num; j++)
         {
    		sum = 0.0;
    		
    		for(k=0; k<3; k++){
    			for(l=0; l<3; l++){
    				sum += inputImage[i+k-num][j+l-num] * kernel[k][l] ; 
				}
			}
			
			sum /= 9;
			
			if(sum > 255)	sum = 255;
			if(sum < 0)	sum = 0;
			
	        outputImage[i][j] = (unsigned char)sum;
         }
     }
     
     return outputImage;
}

