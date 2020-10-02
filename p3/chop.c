/**
 * Program that takes commandline arguments
 * to modify a textfile by selectively removing
 * lines and columns
 * @author Rohan Sukhija
 */

#include "text.h"
#include "edit.h"
#include <stdlib.h>
#include <string.h>

/** The minimum number of command line args the program
 * can accept
 */
#define MIN_ARG 3

/**
 * Prints the invalid argument message exits with error status
 */
void printInvalidArg()
{
    fprintf(stderr, "%s", "invalid arguments\n");
    fprintf(stderr, "%s", "usage: chop command* (infile|-) (outfile|-)\n");
    exit(1);
}

/**
 * Bounds the cols values to a max of the MAX_STR
 * @param a the pointer to the col value
 */
void boundCols(int *a)
{
    if (*a > MAX_STR) {
        *a = MAX_STR;
    }
}

/**
 * Bounds the row values to a max of the lines global variable
 * @param a the pointer to the row value
 */
void boundRows(int *a)
{
    if (*a > lines) {
        *a = lines;
    }
}

/**
 * Processes command-line arguments and reads file contents to
 * write the final output file
 * @param argc the number of commandline arguments
 * @param argv the array of commandline arguments
 */
int main(int argc, char *argv[]) {
    if (argc < MIN_ARG) {
        printInvalidArg();
    }
    FILE *inputFile = fopen(argv[argc - MIN_ARG + 1], "r");
    if (strcmp(argv[argc - MIN_ARG + 1], "-") == 0) {
        readFile(stdin);
    }
    else {
        if (inputFile == NULL) {
            fprintf(stderr, "Can't open file: %s\n", argv[argc - MIN_ARG + 1]);
            exit(1);
        }
        readFile(inputFile);
    }
    fclose(inputFile);
    for (int i = 1; i < argc - MIN_ARG + 1; i++) {
        if (strcmp("line", argv[i]) == 0) {
            int line = atoi(argv[++i]);
            if (line <= 0 || line > lines) {
                printInvalidArg();
            }
            removeLines(line, line);
        }
        else if (strcmp("lines", argv[i]) == 0) {
            int start = atoi(argv[++i]);
            int end = atoi(argv[++i]);
            boundRows(&end);
            if (start <= 0 || end <= 0 || start > lines || end < start) {
                printInvalidArg();
            }
            removeLines(start, end);
        }
        else if (strcmp("col", argv[i]) == 0) {
            int col = atoi(argv[++i]);
            if (col <= 0 || col > MAX_STR) {
                printInvalidArg();
            }
            removeCols(col, col);
        }
        else if (strcmp("cols", argv[i]) == 0) {
            int start = atoi(argv[++i]);
            int end = atoi(argv[++i]);
            boundCols(&end);
            if (start <= 0 || end <= 0 || start > MAX_STR || end < start) {
                printInvalidArg();
            }
            removeCols(start, end);
        }
        else {
            printInvalidArg();
        }
    }
    FILE *outputFile = fopen(argv[argc - 1], "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Can't open file: %s\n", argv[argc - 1]);
        exit(1);
    }

    if (strcmp(argv[argc - 1], "-") == 0) {
        writeFile(stdout);
    }
    else {
        writeFile(outputFile);
    }
    fclose(outputFile);
    return 0;
}
