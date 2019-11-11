Mandelbrot image creator. The center-most pixel will contain the result of evaluating the Mandelbrot function (with given threshold and max iterations) with C as the input variable center and Z as 0. The bottom-left corner will evaluate the Mandelbrot function at C = (center - (scale + scale * i)), with other pixels linearly interpolated between the edge and the center. This creates .ppm files for each Mandelbrot frame that results in a sequence of Mandelbrot images.

**I did not write everything in this code. Some of the codes were provided by the staff of CS61C UC Berkeley**
