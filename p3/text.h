#include <stdio.h>

/** The max characters per lines the program can process */
#define MAX_STR 100

/** The max lines the program can process */
#define MAX_LINES 10000

/** The number of lines in the file */
extern int lines;

/** The global array of char stored in static memory as a 
 * pointer to a dynamically allocated array 
 */
extern char (*input)[MAX_STR + 1];

/**
 * Reads a file input by translating its contents 
 * to the global array.
 * @param fp the pointer to the file
 */
void readFile( FILE *fp );

/**
 * Writes the contents of the global 2d array
 * to a file
 * @param fp the pointer to the file
 */
void writeFile( FILE *fp); 


