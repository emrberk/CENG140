#include <stdio.h>
#include <stdlib.h>
#include "../the2.h"

int main()
{
    double **matrix, **convoluted, **kernel;
    int i, row_size = 0, row_count = 0, kernel_height = 3, kernel_width = 3;

    /* 
    Initialize following kernel matrix:
        [[0, 1, 0], 
         [0, 1, 0], 
         [0, 1, 0]] 
    */
	kernel = calloc(kernel_height,sizeof(double*));
	for(i=0;i<kernel_height;i++) {
		kernel[i] = calloc(kernel_width,sizeof(double));
	}
	for(i=0;i<kernel_height;i++) {
		kernel[i][0] = 0;
		kernel[i][1] = 1;
		kernel[i][2] = 0;
	}

    matrix = initialize_the_data(&row_count, &row_size);
    convoluted = convolution(matrix, row_count, row_size, kernel, kernel_height, kernel_width);

    print_first_n_row(convoluted, row_count - kernel_height + 1, row_size - kernel_width + 1);

    return 0;
}
