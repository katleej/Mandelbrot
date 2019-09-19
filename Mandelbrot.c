/*********************
**  Mandelbrot fractal
** clang -Xpreprocessor -fopenmp -lomp -o Mandelbrot Mandelbrot.c
** by Dan Garcia <ddgarcia@cs.berkeley.edu>
** Modified for this class by Justin Yokota and Chenyu Shi
**********************/

#include <stdio.h>
#include <stdlib.h>
#include "ComplexNumber.h"
#include "Mandelbrot.h"

/*
This function returns the number of iterations before the initial point >= the threshold.
If the threshold is not exceeded after maxiters, the function returns 0.
*/
u_int64_t MandelbrotIterations(u_int64_t maxiters, ComplexNumber * point, double threshold)
{
	//YOUR CODE HERE
	struct ComplexNumber* z = newComplexNumber(0,0);
	struct ComplexNumber* m = ComplexSum(ComplexProduct(z,z), point); 
	u_int64_t count = 0;
 
	while (maxiters > 0) { 
		if (ComplexAbs(m) >= threshold) {
			free(m);
			free(z);  
			return count; 
		} else {
			m = ComplexSum(ComplexProduct(z,z), point); 
			z = ComplexSum(ComplexProduct(z,z), point); 
			count++; 
			maxiters--;
		} 
	} 			    
  return 0;
}

/*
This function calculates the Mandelbrot plot and stores the result in output.
The number of pixels in the image is resolution * 2 + 1 in one row/column. It's a square image.
Scale is the the distance between center and the top pixel in one dimension.
*/
void Mandelbrot(double threshold, u_int64_t max_iterations, ComplexNumber* center, double scale, u_int64_t resolution, u_int64_t * output){
	double x = Re(center);
	double y = Im(center); 
	double length_of_square = resolution * 2 + 1;
	double n = -1; 
	for (u_int64_t i = 0; i < pow(length_of_square, 2); i++) {
		if (i % ((u_int64_t) length_of_square) == 0) {
			n = n + 1;
		}
		double box_x = (x - scale) + (scale / resolution) * (i % ((u_int64_t) length_of_square));
		double box_y = (y + scale) - (scale / resolution) * n;  
		*output = MandelbrotIterations(max_iterations, newComplexNumber(box_x, box_y),threshold); 
		output++; 
	}
	//YOUR CODE HERE
}
