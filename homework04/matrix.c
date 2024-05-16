#include "matrix.h"

/* Debugging code that prints the BFS result for a particular iteration
   input parameters:
       int  rows	# of vertices
       int* color	array of color for the vertices
       int* distance	array of distance for the vertices
   return parameters:
       none
 */
void print_bfs_matrix_result(int rows, int* color, int* distance)
{
    assert(color);
    assert(distance);

    fprintf(stdout, "---- Print BFS Matrix Result ----\n");
    fprintf(stdout, "Vert\tCol\tDis\n");
    for(int i = 0; i < rows; i++) {
        fprintf(stdout, "%d\t%d\t%d\n", i, color[i], distance[i]);
    }
    fprintf(stdout, "--------\n\n");
}


/* Debugging code that prints a vector
   input parameters:
       int* vector	vector whose content we wish to print
       int  rows	# of elements in the vector
   return parameters:
       none
 */
void print_vector(int* vector, int rows)
{
    assert(vector);

    fprintf(stdout, "---- Print Vector ----\n");
    for(int i = 0; i < rows; i++) {
        fprintf(stdout, "%d\n", vector[i]);
    }
    fprintf(stdout, "--------\n\n");
}


/* Debugging code that prints the content of a 2D matrix
   input parameters:
       int* matrix	2D matrix we wish to print2D matrix we wish to print
       int  rows	# of rows of the input matrix
       int  cols	# of cols of the input matrix
   return parameters:
       none
 */
void print_matrix(int **matrix, int rows, int cols)
{
    assert(matrix);

    fprintf(stdout, "---- Print Matrix ----\n");
    fprintf(stdout, "This matrix is %d x %d\n", rows, cols);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            fprintf(stdout, "%d ", matrix[i][j]);
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "--------\n\n");

}



void matrix_transpose(int** dst, int** src, int rows, int cols)
/* This function takes in a 2D matrix (src), transposes it and 
   then stores it in a destination 2D matrix (dst).
   Transpose operation takes each src[i][j] element and stores it
   in dst[j][i]
   
   input parameters:
       int** dst	Where you store the transpose of src
                        Dimensions are cols x rows
       int** src	Matrix you want to transpose
                        Dimensions are rows x cols
       int   rows	# of rows of input matrix (src)
       int   cols	# of cols of input matrix (src)
   return parameters:
       none
 */
{
    assert(dst);
    assert(src);
    assert(rows == cols);

    // INSERT YOUR CODE HERE
    for( int i=0; i<rows; i++){
        for(int j=0; j<cols; j++)
	{
		int tmp= src[i][j];
            dst[j][i]= tmp;
        }
    }
}







void reset_vector(int* vector, int rows)
/* This function 'resets a vetor to have all
   zero value
   input parameters:
       int* vector	the input vector to reset
       int  rows	the number of elements in the vector
   return parameters:
       none
 */
{
    assert(vector);

    for(int i = 0; i < rows; i++) {
        vector[i] = 0;
    }
}



void bfs_spmv(int** int_array, int rows, int cols, int source,
              int* color, int* distance)
/* SpMV-based BFS implementation
   input parameters:
   These are 'consumed' by this function
       int** int_array	input array representing the adjacency
                        matrix
       int   rows	# of rows of the adajcency matrix
       int   cols	# of cols of the adajcency matrix
       int   source	source vertex for the BFS
   These are 'produced' by this function
       int*  color	color array
       int*  distance	distance array
   return parameters:
       none
  */
{
    // check the input parameters to see if they are valid
    if(rows != cols) {
        fprintf(stderr, "Not an adjacency matrix\n");
	exit(EXIT_FAILURE);
    }
    if(source >= rows) {
        fprintf(stderr, "Invalid source vertex\n");
	exit(EXIT_FAILURE);
    }
    assert(int_array);
    assert(color);
    assert(distance);

    fprintf(stdout, "Breadth first search on the graph using SpMV ... ");

    // Transpose the adjacency matrix
    int** mat_trans = NULL;
    init_2d_array(&mat_trans, cols, rows);
    matrix_transpose(mat_trans, int_array, rows, cols);

    #if DEBUG
        print_matrix(mat_trans, cols, rows);
    #endif

    // Initialize the various data structures
    int* vec = (int*) malloc(sizeof(int) * rows);
    assert(vec);
    for(int i = 0; i < rows; i++) {
        if(i == source) {
            vec[i] = 1;
            color[i] = 2;
            distance[i] = 0;
        } else {
            vec[i] = 0;
            color[i] = 0;
            distance[i] = -1;
        }
    }
    int* res = (int*) malloc(sizeof(int) * cols);
    assert(res);
    reset_vector(res, cols);


    int iter = 1;
    int done = 0;
    int *src = vec;
    int *dst = res;

    // Do BFS until done
    while(!done) {
        // INSERT YOUR CODE HERE
// Initialize variables for the next iteration
    done = 1;
    
    // Perform SpMV
    for (int i = 0; i < rows; i++) {
        if (src[i] != 0) {
            for (int j = 0; j < rows; j++) {
                if (mat_trans[i][j] != 0 && color[j] == 0) {
                    // Neighbors found
                    done = 0;
                    dst[j] = 1;
                    color[j] = 1;  // Mark as visited
                    distance[j] = iter;  // Set the distance
                }
            }
        }
    }

    // Swap source and destination vectors for the next iteration
    int *temp = src;
    src = dst;
    dst = temp;

    iter++;
}
    

    fprintf(stdout, "done\n");

    #if DEBUG
        print_bfs_matrix_result(rows, color, distance);
    #endif

    free_2d_array(mat_trans, cols);
    free(vec);
    free(res);
}


/* This function allocates memory for a 2D array of size rows x cols
   input parameters
       int*** arr		reference to the 2D array you want to init
       int    rows		# of rows in the 2D array
       int    cols		# of columns in the 2D array
   return parameters:
        none
 */
void init_2d_array(int*** arr, int rows, int cols)
{
    int** tmpArr = (int**) malloc(sizeof(int*) * rows);
    assert(tmpArr);
    for(int i = 0; i < rows; i++) {
        tmpArr[i] = (int*) malloc(sizeof(int) * cols);
        assert(tmpArr[i]);
    }
    *arr = tmpArr;

}


/* This function frees memory allocated to a 2D array.
   input parameters:
       int** arr	the 2D array to deallocate
       int   rows	# of rows of the matrix
   return parameters:
       none
 */
void free_2d_array(int** arr, int rows)
{
    for(int i = 0; i < rows; i++) {
        // free each row
        free(arr[i]);
    }
    // free the matrix
    free(arr);
}
