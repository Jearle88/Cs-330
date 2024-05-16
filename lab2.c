/*
* CS 330: Lab 02
* Destription: Operations on a 2-D array of pointers using function pointers.
* Authors: Jared Hall, Chris Misa, Jee Choi
* Instructions:
*   1. Make sure you read through the provided code and test it before begining.
*   2. Complete the functions: capitalize_first_col, apply_by_row
*   3. Add code to main to test the function calls.
*   4. Test your program on ix-dev then push the lab02 folder to bitbucket.
*
* Notes:
*   1. You can adapt the apply_by_row function to develop the apply_by_col function. 
*/
// ================================= Includes, Macros, & Globals ======================
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define STATIC_DATA_LENGTH 6
// ======================================================================================

// ========================== Function Signatures & Structures ==========================
int allocate_data(char ****data, int rows, int cols);
void free_data(char ***data, int rows, int cols);
void print_str(char *str, int row, int col, int rows, int cols);
void apply_by_row(void (*func)(char *, int, int, int, int), char ***data, int rows, int cols);
void capitalize_first_col(char *str, int row, int col, int rows, int cols);

char *static_data[STATIC_DATA_LENGTH] = {
    "this",
    "is",
    "a",
    "list",
    "of",
    "words"
};
// ======================================================================================

// ================================= Function: Main =====================================
int main(int argc, char **argv) {
    char ***data;
    int data_rows = 4;
    int data_cols = 3;
    int status = 1;

    status = allocate_data(&data, data_rows, data_cols);
    if(!status) {
        return status;
    }

    printf("\nOriginal Matrix:\n");
    apply_by_row(print_str, data, data_rows, data_cols);
    printf("\n");

    apply_by_row(capitalize_first_col, data, data_rows, data_cols);

    printf("After Matrix Alteration:\n");
    apply_by_row(print_str, data, data_rows, data_cols);
    printf("\n");

    return 0;
}
// ======================================================================================

// ================================ Function Definitions ================================
int allocate_data(char ****data, int rows, int cols) {
    /*
    * Desription: Allocates memory for our 2D matrix.
    * Inputs: 
    *   1. data: A 4-star pointer to the incomming matrix.
    *   2. rows: the total number of rows.
    *   3. cols: The total number of columns
    * 
    * Outputs: boolean value - 0 if memory allocation failed
    */
    *data = (char ***)malloc(sizeof(char **) * rows);
    if(*data == NULL) {
        fprintf(stderr, "Error: Cannot allocate memory for the rows.\n");
        return 0;
    }
    for(int i=0; i < rows; i++) {
        (*data)[i] = (char**)malloc(sizeof(char*) * cols);
        if((*data)[i] == NULL) {
            fprintf(stderr, "Error: Cannot allocate memory for the columns.\n");
            return 0;
        }
        for(int j = 0; j < cols; j++) {
            (*data)[i][j] = strdup(static_data[(i * cols + j) % STATIC_DATA_LENGTH]);
        }
    }
    return 1;
}

void free_data(char ***data, int rows, int cols) {
    /*
    * Desription: Frees memory for our 2D matrix.
    * Inputs: 
    *   1. data: A 4-star pointer to the incomming matrix.
    *   2. rows: the total number of rows.
    *   3. cols: The total number of columns
    * 
    * Outputs: None
    */
   for(int i = 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
        free(data[i][j]);
    }
    free(data[i]);
   }
   free(data);
}

void print_str(char *str, int row, int col, int rows, int cols){
    /*
    * Desription: formatted print of the contents in the string.
    * Inputs: 
    *   1. str: A string to print.
    *   2. row: the index of the current row.
    *   3. col: the index of the current column.
    *   4. rows: the total number of rows.
    *   5. cols: The total number of columns
    * 
    * Outputs: None
    * 
    * Notes: 
    *   1. This function gets passed into our functions in order to print their contents.
    */

   fprintf(stdout, "%s ", str);
   if((col + 1)%cols == 0) {
       fprintf(stdout, "\n");
   }
}

void apply_by_row(void (*func)(char *, int, int, int, int), char ***data, int rows, int cols) {
    /*
    * Desription: Applies the given function to each row in the provided matrix.
    * Inputs: 
    *   1. func: A function pointer to apply
    *   2. data***: A pointer to the matrix
    *   3. rows: the total number of rows.
    *   4. cols: The total number of columns
    * 
    * Outputs: None
    * 
    * Notes: 
    *   1. This function applys the print function to our data. Follow the pseudocodes.
    *   2. To call a function from a pointer you just use the name (e.g., func(<params>)).
    */

    //Step-01: Use a for loop to iterate through the rows of the matrix.
    //Step-02: Use a nested for loop to iterate through the columns of the matrix row.
    //Step-03: Call the function (given via a function pointer) on the data.
    int i, j;
     char *charData = (char*)data;
     void (*castedFunc)(char *, int, int, int, int) = (void (*)(char *, int, int, int, int))func;
    for(i=0; i<rows;i++){
        for(j=0; j<cols;j++){
            // Call the casted function on the data
            castedFunc(data[i][j], i, j, rows, cols);
        }
    }
}

void capitalize_first_col(char *str, int row, int col, int rows, int cols){
    /*
    * Desription: Capitalizes the letter in the first column in the matrix
    * Inputs: 
    *   1. str: A string to process.
    *   2. row: the index of the current row.
    *   3. col: the index of the current column.
    *   4. rows: the total number of rows.
    *   5. cols: The total number of columns
    * 
    * Outputs: None
    * 
    * Notes:
    *   1. You only need to use str and col. The others are just to match the signature of print_str.
    */

    //Step-01: If we are looking at column 0 and the string is not null...
    //Step-02: Get the size of the string
    //Step-03: For loop over every character in the string.
    //Step-04: Convert the caracter to upper-case.
    int i;
if (col==0 && str!= NULL){
    int len= strlen(str);
    for(i=0;i<len;i++){
      if( str[i]== str[0]){
       str[i]= toupper(str[i]);

      } 
    }
}
}

// ======================================================================================
