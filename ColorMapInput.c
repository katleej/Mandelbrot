/*********************
**  Color Map generator
** Skeleton by Justin Yokota
**********************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "ColorMapInput.h"


/**************
**This function reads in a file name colorfile.
**It then uses the information in colorfile to create a color array, with each color represented by an int[3].
***************/
uint8_t** FileToColorMap(char* colorfile, int* colorcount)
{
    //YOUR CODE HERE
    FILE* file = fopen(colorfile, "r");
    int count = 0; 
    colorcount = &count; 
    fscanf(file, "%d", &count);
    uint8_t** result = (uint8_t**) malloc(*colorcount * sizeof(uint8_t*));  
    for (uint8_t i = 0; i < *colorcount; i++) {
	uint8_t* color = (uint8_t*) malloc(3 * sizeof(uint8_t));  
	fscanf(file, "%hhu", &color[0]);
	fscanf(file, "%hhu", &color[1]); 
	fscanf(file, "%hhu", &color[2]); 
 	result[i] = color; 
        }
    return result;
}


