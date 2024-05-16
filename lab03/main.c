/*
* CS 330: Lab 03
* Description: Explore varying pointer indirection levels by allocating,
*              initializing, populating, printing, and freeing an "array," in three
*              different ways. There is a fourth way, given as an example.
* Authors: Jared Hall, S. Isaac Geronimo Anderson
* Instructions:
*   1. Make sure you read through the provided code and test it before begining.
*   2. Complete the 3 empty "allocate_and_initialize_..." functions where
*      specified in each function, using malloc for allocating an array of
*      "size" bytes.
*   3. Complete the "free_..." functions (3) for freeing each array.
*
*   4. Complete the "populate_..." functions (3) so they iterate from i = 0 to
*      i < size, and set the array index i to hold the value i.
*
*   5. Compile the code with the following command: gcc -g -Wall -std=c11 -D_DEFAULT_SOURCE main.c
*   6. Run the code with the following command: ./a.out 10
*   7. Your output should match the output shown in ex1.png
*/

// ================================= Includes, Macros, & Globals ======================
#include <stdio.h>
#include <stdlib.h>

// ======================================================================================

// ========================== Function Signatures & Structures ==========================
int allocate_and_initialize_indirectly(int **array, int size);
int allocate_and_initialize_doubly_indirectly(int ***array, int size);
int allocate_and_initialize_chained(int *******array, int size);
void free_indirectly(int *array);
void free_doubly_indirectly(int **array);
void free_chained(int ******array);
void print_indirectly(int *array, int size);
void print_doubly_indirectly(int **array, int size);
void print_chained(int ******array, int size);
void populate_indirectly(int *array, int size);
void populate_doubly_indirectly(int **array, int size);
void populate_chained(int ******array, int size);
void usage(int argc, char **argv);


// ======================================================================================

// ================================= Function: Main =====================================
void usage(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s size\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    return;
}

int main(int argc, char **argv) {
    usage(argc, argv);
    printf("Running test program with array size: %s\n", argv[1]);
    
    int *indirect = NULL;
    int **doubly_indirect = NULL;
    int ******chain = NULL;
    int size = atoi(argv[1]);

    printf("Step-01: Allocating memory...");
    if(allocate_and_initialize_indirectly(&indirect, size) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    } 
    if(allocate_and_initialize_doubly_indirectly(&doubly_indirect, size) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }
    if(allocate_and_initialize_chained(&chain, size) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }
    printf("Complete.\n");

    printf("Step-02: Populating Arrays...");
    if (indirect) {populate_indirectly(indirect, size);}
    if (doubly_indirect) {populate_doubly_indirectly(doubly_indirect, size);}
    if (chain) {populate_chained(chain, size);}
    printf("Complete.\n");

    printf("Step-03: Printing arrays...\n\n");
    if (indirect) {print_indirectly(indirect, size);}
    if (doubly_indirect) {print_doubly_indirectly(doubly_indirect, size);}
    if (chain) {print_chained(chain, size);}
    printf("\n");

    printf("Step-04: Freeing arrays...");
    if (indirect) {free_indirectly(indirect);}
    if (doubly_indirect) {free_doubly_indirectly(doubly_indirect);}
    if (chain) {free_chained(chain);}
    printf("Complete.\n");

    return EXIT_SUCCESS;
}
// ======================================================================================

// ================================ Allocation Functions ================================
int allocate_and_initialize_indirectly(int **array, int size) {
    /* The argument values are technically copies of the originals, so if we
    * update them directly, nothing in the calling function will change. That
    * is why we call this function with the address of the array pointer, thus
    * giving us a pointer to that pointer. We dereference it once, which
    * allows us to update the array in the calling function even though it is
    * in a different scope from us (this function).
    *
    * Hint: 
    * The typical format for malloc calls is: var = (<type>) malloc(<size>).
    * So if i wanted to alocate memory for a pointer i need to a) determine the type of pointer i want,
    * b) determine the size of the memory to allocate. Keep this in mind when filling in the codes.
    */

    // ================== YOUR CODE HERE (In-Lab) ==============================
    //malloc genrak form: var=(tyoe)malloc(size)
    
    // =========================================================================
    *array = (int*)malloc(size * sizeof(int));
    if(*array == NULL) {
        return EXIT_FAILURE;
    } else {
        return EXIT_SUCCESS;
    }
}

int allocate_and_initialize_doubly_indirectly(int ***array, int size) {
    /*
    * In this function you will need two malloc calls: one for a double pointer,
    * and one for the single pointer.
    * 
    * Hint: allocate memory for the double pointer first, then the single pointer
    *
    */
    
    // ======================= YOUR CODE HERE (2 lines) =======================
    // ========================================================================
  
      *array = (int**)malloc(size * sizeof(int*));
    **array = (int*)malloc(size * sizeof(int));
       
	if(*array == NULL || **array == NULL) {
        return EXIT_FAILURE;
    } else {
        return EXIT_SUCCESS;
    }
}

int allocate_and_initialize_chained(int *******array, int size) {
    /*
    * In this function you will need six malloc calls: one each for the pointers up to 6 stars.
    * We simply generalize the ideas in the doubly-indirectly case, so we
    * allocate space for the first pointer in the chain (size 1), then the
    * next, and so on, until we get to the last level, when we use size
    * "size."
    * 
    * Hint: allocate memory for the double pointer first, then the single pointer
    *
    */
  
  
      *array = (int******)malloc(size * sizeof(int*****));
    **array = (int*****)malloc(size * sizeof(int****));
    ***array = (int****)malloc(size * sizeof(int***));
    ****array = (int***)malloc(size * sizeof(int**));
    *****array = (int**)malloc(size * sizeof(int*));
    ******array = (int*)malloc(size * sizeof(int));

    // ======================= YOUR CODE HERE (6 lines) =======================
          // ========================================================================

    if(*array == NULL || **array == NULL || ***array == NULL || ****array == NULL) {
        return EXIT_FAILURE;
    } else if(*****array == NULL || ******array == NULL) {
        return EXIT_FAILURE;
    } else {
        return EXIT_SUCCESS;
    }
}
// ======================================================================================

// ============================== Deallocation Functions ================================

void free_indirectly(int *array) {
    // ======================= YOUR CODE HERE (In-Lab) =======================
        free(array);
    // =======================================================================
    return;
}

void free_doubly_indirectly(int **array) {
    //For this function you will need 2 frees: one for the inner pointer one for the outer.

    // ======================= YOUR CODE HERE (2 lines) =======================
    free(*array);
    free(array);
    // ========================================================================
    return;
}

void free_chained(int ******array) {
    // For this function we will extend the logic of the previous function for the 6 star pointer.

    // ======================= YOUR CODE HERE (6 lines) =======================
    
   free(*****array);
    free(****array);
    free(***array);
    free(**array);
    free(*array);
    free(array);
    // ========================================================================

    return;
}
// ======================================================================================

// ============================== Populate Functions ====================================
void populate_indirectly(int *array, int size) {
    // ======================= YOUR CODE HERE (In-Lab) =======================
for( int i=0; i < size; i++){
    array[i]=i;
}
    // =======================================================================
    return;
}

void populate_doubly_indirectly(int **array, int size) {
    
    // ======================= YOUR CODE HERE (2 lines) =======================
for( int i=0; i < size; i++){
    (*array)[i]=i;
}
    // ========================================================================
    return;
}

void populate_chained(int ******array, int size) {
    // Hint read the provided print functions, they might give you a hint.

    // ======================= YOUR CODE HERE (2 lines) =======================
        for (int i = 0; i < size; ++i)
       ( *****array)[i]=i;
 	

    // ========================================================================

    return;
}
// ======================================================================================

// ============================== Print Functions =======================================
void print_indirectly(int *array, int size) {
    for (int i = 0; i < size; ++i)
        printf("%d ", array[i]);
    printf("\n");

    return;
}

void print_doubly_indirectly(int **array, int size) {
    for (int i = 0; i < size; ++i)
        printf("%d ", (*array)[i]);
    printf("\n");
    return;
}

void print_chained(int ******array, int size) {
    for (int i = 0; i < size; ++i)
        printf("%d ", (*****array)[i]);
    printf("\n");
    return;
}
// ======================================================================================

// ================================== End of Program ====================================
