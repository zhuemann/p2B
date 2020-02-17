///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        (name of file with main function)
// This File:        (name of this file)
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Spring 2020
//
// Author:           Zach Huemann
// Email:            zhuemann@wisc.edu
// CS Login:         huemann
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   Avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
//typedef struct {
typedef struct MSquare {
    int size;     // dimension of the square
    int **msquare; // pointer to heap allocated magic square
} MSquare;

/* 
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize() {

    printf("Enter magic square's size (odd integer >=3)");
    printf("\n");

    char buf[10];
    fgets(buf, 10, stdin);
    int size = atoi(buf);

     if (size < 3) {
        printf("Size must be >= 3.\n");
        exit(1);
    }

    if (size%2 != 1) {
        printf("size must be odd.\n");
        exit(1);
    }

    return size;   
} 
   
/* 
 * Makes a magic square of size n using the Siamese algorithm
 * and returns a pointer to the completed MSquare struct.
 *
 * n the number of rosw and columns
 */
MSquare *generateMSquare(int n) {

    struct MSquare *outputSquareStruct = (struct MSquare*)malloc(sizeof(struct MSquare));
    outputSquareStruct-> msquare = (int **)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        *(outputSquareStruct->msquare+i) = (int *)malloc(n * sizeof(int));
    }

    outputSquareStruct->size = n;
    int **square = outputSquareStruct->msquare; 
    int startingPoint = n / 2;

    int maxValue = n*n;
    int i = 0;
    int j = 0;
    int iCorrection = 0; //corrections for when you index into a filled box
    int jCorrection = 0; //corrections for when you index into a filled box
    //loops through all the numbers you have to put into the magic square
    //the indexing is handled by variables called i and j
    //I know there is a more consice way to do the indexing but this is
    //equivalent so sorry for being hard to read
    for (int k = 0; k < maxValue; k++) {
	i = (maxValue - k + iCorrection) % n;
	j = (k + startingPoint + jCorrection)  % n;
	//if the space is already full you should drop down one box,
	//these corrections terms will do exactly that
        if (*(*(square + i) + j) != 0) {
	    iCorrection = iCorrection + 2;
	    jCorrection--;
	}
        //recalculates i and j for with correction terms
	i = (maxValue - k + iCorrection) % n;
	j = (k + startingPoint + jCorrection)  % n;
	*(*(square + i) + j) = k + 1;

    }

    return outputSquareStruct;    
} 

/*  
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * msquare the magic square to output
 * filename the name of the output file
 */
void outputMSquare(MSquare *msquare, char *filename) {
 
    FILE *fileptr = fopen(filename,"w");
    int size = msquare->size;
    int **square = msquare->msquare;
    fprintf(fileptr,"%d", size);

    //these for loops loop through the struct ant write the
    //the file name given. 
    for (int i = 0; i <size; i++) {

        fprintf(fileptr,"%s","\n");

        for(int j = 0; j < size; j++) {
	    fprintf(fileptr,"%d", *(*(square + i) + j));
	    if (j < size-1) {
	        fprintf(fileptr,"%s",",");
	    }
            	    
        }
    }
    //erorr handling for closing the file
    if (fclose(fileptr) != 0) {
	printf("Error wile closing the file.\n");
	exit(1);
    }

}

/*
 * Generates a magic square of the user specified size and
 * output the quare to the output filename
 */
int main(int argc, char *argv[]) {

    // Check input arguments to get output filename
    if (argc != 2) {
        printf("You did not include the correct number of arguements.\n");
	exit(1);
    }

    // Get magin square's size from user
    int size = getSize();

    // Generate the magic square
    struct MSquare *testSquare = generateMSquare(size);

    // Output the magic square
    outputMSquare(testSquare, argv[1]);


    // free all the memory malocs up
    for (int i = 0; i < size; i++) {
        int *pointerToBeFreed = *(testSquare->msquare + i);
       	free(pointerToBeFreed);
    }
    free(testSquare->msquare);
    //free(testSquare->size);
    free(testSquare);
    return 0;
} 


   
