#include <stdio.h>

#define MAX_STR 100

#define MAX_LINES 10000

extern int lines;

extern char (*input)[MAX_STR + 1];

void readFile( FILE *fp );

void writeFile( FILE *fp); 


