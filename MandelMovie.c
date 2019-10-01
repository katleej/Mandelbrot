/*********************
**  Mandelbrot fractal movie generator
** clang -Xpreprocessor -fopenmp -lomp -o Mandelbrot Mandelbrot.c
** by Dan Garcia <ddgarcia@cs.berkeley.edu>
** Modified for this class by Justin Yokota and Chenyu Shi
**********************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "ComplexNumber.h"
#include "Mandelbrot.h"
#include "ColorMapInput.h"
#include <sys/types.h>

void printUsage(char* argv[])
{
  printf("Usage: %s <threshold> <maxiterations> <center_real> <center_imaginary> <initialscale> <finalscale> <framecount> <resolution> <output_folder> <colorfile>\n", argv[0]);
  printf("    This program simulates the Mandelbrot Fractal, and creates an iteration map of the given center, scale, and resolution, then saves it in output_file\n");
}


/*
This function calculates the threshold values of every spot on a sequence of frames. The center stays the same throughout the zoom. First frame is at initialscale, and last frame is at finalscale scale.
The remaining frames form a geometric sequence of scales, so 
if initialscale=1024, finalscale=1, framecount=11, then your frames will have scales of 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1.
As another example, if initialscale=10, finalscale=0.01, framecount=5, then your frames will have scale 10, 10 * (0.01/10)^(1/4), 10 * (0.01/10)^(2/4), 10 * (0.01/10)^(3/4), 0.01 .
*/
void MandelMovie(double threshold, u_int64_t max_iterations, ComplexNumber* center, double initialscale, double finalscale, int framecount, u_int64_t resolution, u_int64_t ** output){
    //YOUR CODE HERE
    double a = pow((finalscale/initialscale),1/(framecount-1))
    for (int i = 0; i < framecount; i++) {
	double nth_scale = initialscale * pow(a, i); 
	Mandelbrot(threshold, max_iterations, center, nth_scale, resolution, output[i]);  
    }
}

/**************
**This main function converts command line inputs into the format needed to run MandelMovie.
**It then uses the color array from FileToColorMap to create PPM images for each frame, and stores it in output_folder
***************/
int main(int argc, char* argv[])
{
	//Tips on how to get started on main function: 
	//MandelFrame also follows a similar sequence of steps; it may be useful to reference that.
	//Mayke you complete the steps below in order. 

	//STEP 1: Convert command line inputs to local variables, and ensure that inputs are valid.
	/*
	Check the spec for examples of invalid inputs.
	Remember to use your solution to B.1.1 to process colorfile.
	*/

	//YOUR CODE HERE 
	if (argc != 11) {
	    printf("%s: Wrong number of arguments, especting 10\n", argv[0]);
	}
	double threshold, initialscale, finalscale, framecount; 
	u_int64_t max_iterations, resolution
	ComplexNumber* center; 

	threshold = atof(argv[1]); 
	max_iterations = (u_int64_t) atoi(argv[2]); 
	center = newComplexNumber(atof(argv[3]), atof(argv[4])); 
	initialscale = atof(argv[5]); 
	finalscale = atof(argv[6]); 
	framecount = atof(argv[7]); 
	resolution = (u_int64_t) atoi(argv[8]); 
	output_folder = argv[9]; 
	colorfile = argv[10]; 

	if (threshold <= 0 || initialscale <= 0 || finalscale <= 0 || max_iterations <= 0) {
		printf("The threshold, scale, max_iterations must be > 0");
		printUsage(argv); 
		return 1; 
	}


	//STEP 2: Run MandelMovie on the correct arguments.
	/*
	MandelMovie requires an output array, so make sure you allocate the proper amount of space. 
	If allocation fails, free all the space you have already allocated (including colormap), then return with exit code 1.
	*/

	//YOUR CODE HERE 
	u_int64_t** output;
	output = (u_int64_t **) malloc(framecount * size_of(u_int64_t*)); 
	if (output == NULL) {
		printf("Unable to allocate %lu bytes\n", framecount * sizeof(u_int64_t*));
		return 1; 
	} 

	MandelMovie(threshold, max_iterations, center, initialscale, finalscale, framecount, resolution, output);
	printf("Calculation complete, outputting to file %s/n", argv[9]); 

	//STEP 3: Output the results of MandelMovie to .ppm files.
	/*
	Convert from iteration count to colors, and output the results into output files.
	Use what we showed you in Part B.1.2, create a seqeunce of ppm files in the output folder.
	Feel free to create your own helper function to complete this step.
	As a reminder, we are using P6 format, not P3.
	*/

	//YOUR CODE HERE
	double length_of_square = resolution * 2 + 1; 
	FILE* color_file = fopen(colorfile, "r");
	for (int i = 0; i < framecount; i++) {
		//first create a file with that specific name
		int one, two, three, four, five = 0;
		////////fix this part to make sure it does for everything///// 
		char file_name[15];
		sprintf(file_name, output_folder + "/frame%d%d%d%d%d.ppm", one, two, three, four, five);  
		FILE* ppm_file = fopen(file_name, "w"); 

		//let's now call each frame 
		u_int64_t* one_frame = output[i];
		//loop through individual pixels in the frame 
		for (int j = 0; j < length_of_sqaure * length_of_sqaure; i++) {
			//if it is zero then it is black
			if (output[i][j] == 0) {
				fprintf(ppm_file, "%c\%c\%c", 0,0,0); 
			} else {
				//first get total number of colors
				int total_colors = 0; 
				fscanf(color_file, "%d", &total_colors);
				//access an array of colors
				int* colorcount = (int*) malloc(sizeof(int*)); 
				uint8_t** color_array = FileToColorMap(colorfile, colorcount); 
				int index = output[i][j] % total_colors; 
				//get color of that specific index
				uint8_t* color_of_index = color_array[index-1]; 
				fprintf(ppm_file, "%c\%c\%c", color_of_index[0], color_of_index[1], color_of_index[2]); 	
			}
		}		
	}
	 




	//STEP 4: Free all allocated memory
	/*
	Make sure there's no memory leak.
	*/
	//YOUR CODE HERE 
	free(output); 




	return 0;
}

