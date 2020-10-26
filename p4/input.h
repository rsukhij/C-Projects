#include <stdio.h>
#include <stdlib.h>

/**
* Reads a single line of input from a file and 
* return it as a string inside a block of dynamically
* allocated memory
* @param fp the file pointer to the file being read
* @return the string in dynamically allocated memory
* or NULL if the end of file
*/
char *readLine(FILE *fp);
