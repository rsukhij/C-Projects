/**
 * Program that reads file contents into a 
 * 2d array and also outputs the contents of 
 * a 2d array to a output file
 * @author Rohan Sukhija
 */

#include "text.h"
#include <stdio.h>
#include <stdlib.h>

int lines = 0;
char (*input)[MAX_STR + 1];

void readFile(FILE *fp)
{
    char val = 0;
    int size = (MAX_STR + 1) * sizeof(char);
    input = malloc(size);
    int j = 0;
    while (fscanf(fp, "%c", &val) != EOF) {
        if (val == '\n') {
            input = realloc(input, size + (MAX_STR + 1) * sizeof(char));
            size += (MAX_STR + 1) * sizeof(char);
            input[lines][j] = '\0';
            j = 0;
            lines++;
        }
        else {
            input[lines][j] = val;
            j++;
        }
        if (j == MAX_STR + 1) {
            fprintf(stderr, "%s", "Line too long\n");
            exit(1);
        }
        if (lines > MAX_LINES) {
            fprintf(stderr, "%s", "Too many lines\n");
            exit(1);
        }
    }
    input[lines][j] = '\0';
}

void writeFile(FILE *fp)
{
    for (int i = 0; i < lines; i++) {
        fprintf(fp, "%s\n", input[i]);
    }
}
