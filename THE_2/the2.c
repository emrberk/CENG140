#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "the2.h"
/*
INPUT:
    int *row_count: vertical size of the matrix to be assigned (passed by reference from the main function)
    int *row_size: horizontal size of the matrix to be assigned (passed by reference from the main function)

OUTPUT:
    double **matrix: created data matrix

METHOD:
    This function creates the matrix streamed via stdin. 
    During this process, assigns row_count and row_size variables.
*/
double **initialize_the_data(int *row_count, int *row_size) { 
    int i,j;
    double **matrix, value, oldvalue;
    matrix = malloc(sizeof(double*));
    for (i=0;;i++) {
        matrix = realloc(matrix, (i+1)*sizeof(double*));
        matrix[i] = malloc(sizeof(double));
        for(j=0;;j++) {
            matrix[i] = realloc(matrix[i], (j+1)*sizeof(double));
            scanf("%lf",&value);
            if (value == -1 && oldvalue == -1) {
                *row_count = i;
                return matrix;
            }
            if (value == -1) {
                oldvalue = value;
                *row_size = j;
                break;
            }
            else {
                oldvalue = value;
                matrix[i][j] = value;
            }
        }
    }
}
    
/*
INPUT:
    double **matrix: data matrix
    int n: number of rows to be printed
    int row_size: horizontal size of the matrix

METHOD:
    This function prints first n row of the matrix.
*/
void print_first_n_row(double **matrix, int n, int row_size) {
    int i,j;
    for (i=0;i<n;i++) {
        for(j=0;j<row_size;j++) {
            printf("%.4f",matrix[i][j]);
            if (j!=row_size-1) {
                printf(" ");
            }
        }
	   if(i != n-1) {
            printf("\n");
	   }
    }
}
/*
INPUT:
    double **matrix: data matrix
    int row_size: horizontal size of the data matrix
    int row1: index of the first row in the calculation
    int row2: index of the second row in the calculation

METHOD:
    This function calculates dot product of the row1 and the row2 and prints it in the following format:
        Dot product of rows <row1>, <row2>: <dot_product>
*/
void calculate_dot_product(double **matrix, int row_size, int row1, int row2) {
    int i;
    double sum = 0;
    for(i=0;i<row_size;i++) {
        sum += matrix[row1][i]*matrix[row2][i];
    }
    printf("Dot product of rows %d, %d: %.4f", row1, row2, sum);
}
/*
INPUT:
    double **matrix: data matrix
    int row_count: vertical size of the data matrix
    int row_size: horizontal size of the data matrix

OUTPUT:
    double **covariance_matrix: Created covariance matrix with size of row_size X row_size

METHOD:
    This function creates covariance matrix of the original data matrix and returns it.

*/
double covariance(double **matrix, int x, int y, int row_count, int row_size) {
    double covariance=0, meanX = 0, meanY = 0;
    int i;
    for(i=0;i<row_count;i++) {
        meanX += matrix[i][x];
    }
    meanX /= row_count;
    for(i=0;i<row_count;i++) {
        meanY += matrix[i][y];
    }
    meanY /= row_count;
    for(i=0;i<row_count;i++) {
        covariance += (matrix[i][x]-meanX)*(matrix[i][y]-meanY);
    }
    covariance /= row_count-1;
    return covariance;
}
double **calculate_covariance_matrix(double **matrix, int row_count, int row_size) { 
    double **covariance_matrix;
    int i,j;
    covariance_matrix = malloc(row_count*sizeof(double*));
    for(i=0;i<row_count;i++) {
        covariance_matrix[i] = malloc(row_size*sizeof(double));
    }
    for(i=0;i<row_count;i++) {
        for (j=0;j<row_size;j++) {
            covariance_matrix[i][j] = covariance(matrix,i,j,row_count,row_size);
        }
    }
    return covariance_matrix;
}
    
/*
INPUT:
    double **matrix: data matrix
    int row_count: vertical size of the data matrix
    int row_size: horizontal size of the data matrix

OUTPUT:
    double **result: Created result matrix with size of row_size X row_size

METHOD:
    This function calculates x^T * x. First finds the transpose of the original data matrix and apply matrix multiplication.
    At the end it returns the calculated matrix with size of row_size X row_size.

*/
double **calculate_x_transpose_times_x(double **matrix, int row_count, int row_size) { 
    double **transposed_matrix; 
    double **result_matrix;
    double sum=0;
    int i,j,k;
    transposed_matrix = malloc(row_size*sizeof(double*));
    for(i=0;i<row_size;i++) {
        transposed_matrix[i] = malloc(row_count*sizeof(double));
    }
    result_matrix = malloc(row_size*sizeof(double*));
    for(i=0;i<row_size;i++) {
        result_matrix[i] = malloc(row_size*sizeof(double));
    }
    for(i=0;i<row_count;i++) {
        for(j=0;j<row_size;j++) {
            transposed_matrix[j][i] = matrix[i][j];
        }
    }
    for(k=0;k<row_size;k++) {    
        for(i=0;i<row_size;i++) {
            for(j=0;j<row_count;j++) {
                sum += transposed_matrix[k][j]*matrix[j][i];
            }
            result_matrix[k][i] = sum;
            sum = 0;
        }
    }
    return result_matrix;
}
/*
INPUT:
    double **matrix: data matrix
    int *group_count: number of the groups to be assigned (passed by reference from the main function)
    int row_count: vertical size of the data matrix
    int row_size: horizontal size of the data matrix
    int group_column: index of the column to apply grouping over
    int operation: index of the operation to apply during grouping
        SUM -> 0
        AVG -> 1
        MAX -> 2
        MIN -> 3

OUTPUT:
    double **grouped_matrix: Created grouped matrix with size of group_count X row_size

METHOD:
    This function applies grouping over desired column index, creates a grouped matrix. It returns this grouped matrix.
    During this process it calculates group count and assigns to the variable.

*/
int in_array(double *array, double value, int size) {
    int i;
    for(i=0;i<size;i++) {
        if(array[i]==value) {
            return 1;
        }
    }
    return 0;
}
int findindex(double *array, double value, int size) {
    int i;
    for(i=0;i<=size;i++) {
        if(array[i]==value)
            return i;
    }
    return 0;
}
double **sum_avg(double **matrix, int *group_count, int row_count, int row_size, int group_column, int operation) {
    double **groups_matrix;
    double *values;
    int *counts;
    int i=0, j=0;
    int index;
    int group = -1;
    double current_val=MAX_VAL, prev_val=MAX_VAL;
    groups_matrix = calloc(1,sizeof(double*));
    groups_matrix[0] = calloc(row_size,sizeof(double));
    values = calloc(1,sizeof(double));
    values[0] = MAX_VAL;
    counts = calloc(1,sizeof(int));
    for(i=0;i<row_count;i++) {
        current_val = matrix[i][group_column];
        if(current_val != prev_val && !in_array(values,current_val,group+1)) {
            group += 1;
            groups_matrix = realloc(groups_matrix, (group+1)*sizeof(double*));
            groups_matrix[group] = realloc(groups_matrix[group], row_size*sizeof(double));
            values = realloc(values,(group+1)*sizeof(double));
            counts = realloc(counts,(group+1)*sizeof(int));
            counts[group] = 1;
            values[group] = current_val;
            for(j=0;j<row_size;j++) {
                groups_matrix[group][j] += matrix[i][j];
            }
            groups_matrix[group][group_column] = current_val;
        }
        else {
            index = findindex(values,current_val,group+1);
            counts[index] += 1; 
            for(j=0;j<row_size;j++) {
                groups_matrix[index][j] += matrix[i][j];
            }
            groups_matrix[index][group_column] = current_val;
        }
        prev_val = current_val;
    }
    *group_count = group+1;
    if (operation==0) {
        return groups_matrix;
    }
    else {
        for(i=0;i<*group_count;i++) {
            for(j=0;j<row_size;j++) {
                groups_matrix[i][j] /= counts[i];
            }
            groups_matrix[i][group_column] = values[i];    
        }
        return groups_matrix;
    }
}
double **min_max(double **matrix, int *group_count, int row_count, int row_size, int group_column, int operation) {
    int i=0, j=0;
    double **groups_matrix;
    double *values;
    int index;
    int group = -1;
    double current_val=MAX_VAL, prev_val=MAX_VAL;
    groups_matrix = calloc(1,sizeof(double*));
    groups_matrix[0] = calloc(row_size,sizeof(double));
    values = calloc(1,sizeof(double));
    values[0] = MAX_VAL;
    for(i=0;i<row_count;i++) {
        current_val = matrix[i][group_column];
        if(current_val != prev_val && !in_array(values,current_val,group+2)) {
            group += 1;
            groups_matrix = realloc(groups_matrix, (group+1)*sizeof(double*));
            groups_matrix[group] = realloc(groups_matrix[group], row_size*sizeof(double));
            values = realloc(values,(group+1)*sizeof(double));
            values[group] = current_val;
            for(j=0;j<row_size;j++) {
                    groups_matrix[group][j] = matrix[i][j];
            }
            groups_matrix[group][group_column] = current_val;
        }
        else {
            index = findindex(values,current_val,group+2);
            for(j=0;j<row_size;j++) {
                if ((operation==2 &&matrix[i][j]>groups_matrix[index][j]) || (operation==3 && matrix[i][j]<groups_matrix[index][j])) {
                    groups_matrix[index][j] = matrix[i][j];
                }
            }
            groups_matrix[index][group_column] = current_val;
        }
        prev_val = current_val;
    }
    *group_count = group+1;
    return groups_matrix;
}
double **group_by(double **matrix, int *group_count, int row_count, int row_size, int group_column, int operation) {
    if (operation==0 || operation == 1) {
        return sum_avg(matrix,group_count,row_count,row_size,group_column,operation);
    }
    else {
        return min_max(matrix,group_count,row_count,row_size,group_column,operation);
    }
}
    
/*
INPUT:
    double **matrix: data matrix
    int row_count: vertical size of the data matrix
    int row_size: horizontal size of the data matrix
    double **kernel: kernel matrix
    int kernel_height: vertical size of the kernel matrix
    int kernel_width: horizontal size of the kernel matrix

OUTPUT:
    double **convoluted_matrix: Created convoluted matrix

METHOD:
    This function applies convolution over data matrix using kernel matrix and returns created matrix.

*/
double inner_product(double **matrix1, double **matrix2, int height, int width) {
    double sum =0;
    int i,j;
    for(i=0;i<height;i++) {
        for(j=0;j<width;j++) {
            sum += matrix1[i][j]*matrix2[i][j];
        }
    }
    return sum;
}
double **convolution(double **matrix, int row_count, int row_size, double **kernel, int kernel_height, int kernel_width) { 
    int i=0, j=0;
    int endRow, endCol;
    int convolution_height = row_count-kernel_height+1;
    int convolution_width = row_size-kernel_width+1;
    double **window_matrix = calloc(kernel_height,sizeof(double*));
    double **convolution_matrix = calloc(convolution_height,sizeof(double*));
    for(i=0;i<convolution_height;i++) {
        convolution_matrix[i] = calloc(convolution_width,sizeof(double));
    }
    for(i=0;i<kernel_height;i++) {
        window_matrix[i] = calloc(kernel_width,sizeof(double));
    }
    for(endCol=kernel_height;endCol<=row_count;endCol++) {
        for(endRow=kernel_width;endRow<=row_size;endRow++) {
            for(i=0;i<kernel_height;i++) {
                for(j=0;j<kernel_width;j++) {
                    window_matrix[i][j] = matrix[endCol-kernel_height+i][endRow-kernel_width+j];
                }
            }
            convolution_matrix[endCol-kernel_height][endRow-kernel_width] = inner_product(window_matrix, kernel, kernel_height, kernel_width);
        }
    }
    return convolution_matrix;
}
