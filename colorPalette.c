/*********************
**  Color Palette generator
** Skeleton by Justin Yokota
**********************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "ColorMapInput.h"

//You don't need to call this function but it helps you understand how the arguments are passed in 
void usage(char* argv[])
{
	printf("Incorrect usage: Expected arguments are %s <inputfile> <outputfolder> <width> <heightpercolor>", argv[0]);
}

//Creates a color palette image for the given colorfile in outputfile. Width and heightpercolor dictates the dimensions of each color. Output should be in P3 format
int P3colorpalette(char* colorfile, int width, int heightpercolor, char* outputfile)
{
	//YOUR CODE HERE
	FILE* input = fopen(colorfile, "r");
	FILE* output = fopen(outputfile, "w"); 
	int length_of_colorfile = 0;
	fscanf(input, "%d", &length_of_colorfile);
	if (!length_of_colorfile || heightpercolor < 1) {
	    return 1; 
	}
        int vertical_dim = heightpercolor * (length_of_colorfile);  

	//let's first print the first line of ppm file
	fprintf(output, "%s %d %d %d\n", "P3", width, vertical_dim, 255); 
	
	//now we will loop through the rest to complete this 
	int* colorcount = (int*) malloc(sizeof(int*)); 
	uint8_t** color_array = FileToColorMap(colorfile, colorcount);
	
	//make sure the colorfile is valid and if it is not, return 1
	if (color_array == NULL) {
	    return 1; 
	} 

	for (int i = 0; i < length_of_colorfile; i++) {
	    uint8_t one, two, three; 
	    one = color_array[i][0];
	    two = color_array[i][1];
	    three = color_array[i][2];
	    //make sure single line of color is replicated as much as width
	    for (int j = 0; j < heightpercolor; j++) {
	        int count = 0; 
		while (count < width) {
		//one starts in new line if the count is zero
			if (count != width - 1) {
			 fprintf(output, "%d %d %d ", one, two, three); 
		    } else {
		         fprintf(output, "%d %d %d\n", one, two, three); 
	            }
	           count++;
	        }     
	    }
        }	    
    free(color_array);
    fclose(input);
    fclose(output);
    return 0;
}

//Same as above, but with P6 format
int P6colorpalette(char* colorfile, int width, int heightpercolor, char* outputfile)
{
    //YOUR CODE HERE
    FILE* input = fopen(colorfile, "r");
    FILE* output = fopen(outputfile, "w");
    int length_of_colorfile = 0;
    fscanf(input, "%d", &length_of_colorfile);
    if (!length_of_colorfile || heightpercolor < 1) {
        return 1;
    }
    int vertical_dim = heightpercolor * (length_of_colorfile);

    //let's first print the first line of ppm file
    fprintf(output, "%s %d %d %d\n", "P6", width, vertical_dim, 255);
	
    //now we will loop through the rest to complete this 
        int* colorcount = (int*) malloc(sizeof(int*));
        uint8_t** color_array = FileToColorMap(colorfile, colorcount);

        //make sure the colorfile is valid and if it is not, return 1
        if (color_array == NULL) {
            return 1;
        }

        for (int i = 0; i < length_of_colorfile; i++) {
            //make sure single line of color is replicated as much as width
            int count = 0;
            while (count < width) {
            //one starts in new line if the count is zero
               fprintf(output, "%c", );
               count++;
            }
        }
    free(color_array);
    fclose(input);
    fclose(output);
    return 0;
}


//The one piece of c code you don't have to read or understand. Still, might as well read it, if you have time.
int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		usage(argv);
		return 1;
	}
	int width = atoi(argv[3]);
	int height = atoi(argv[4]);
	char* P3end = "/colorpaletteP3.ppm";
	char* P6end = "/colorpaletteP6.ppm";
	char buffer[strlen(argv[2]) + strlen(P3end)+1];
	sprintf(buffer, "%s%s", argv[2], P3end);
	int failed = P3colorpalette(argv[1], width, height, buffer);
	if (failed)
	{
		printf("Error in making P3colorpalette");
		return 1;
	}
	sprintf(buffer, "%s%s", argv[2], P6end);
	failed = P6colorpalette(argv[1], width, height, buffer);
	if (failed)
	{
		printf("Error in making P6colorpalette");
		return 1;
	}
	printf("P3colorpalette and P6colorpalette ran without error, output should be stored in %s%s, %s%s", argv[2], P3end, argv[2], P6end);
	return 0;
}




