#include "text.h"
#include "edit.h"
#include <stdlib.h>
#include <string.h>

#define MIN_ARG 3

void printInvalidArg()
{
    fprintf(stderr, "%s", "invalid arguments\n");
    fprintf(stderr, "%s", "usage: chop command* (infile|-) (outfile|-)\n");
    exit(1);
}

void boundCols(int *a)
{
    if (*a > MAX_STR)
    {
        *a = MAX_STR;
    }
}

void boundRows(int *a)
{
    if (*a > lines)
    {
        *a = lines;
    }
}

int main(int argc, char *argv[])
{
    if (argc < MIN_ARG)
    {
        fprintf(stderr, "%s", "invalid arguments\n");
    }
    FILE *inputFile = fopen(argv[argc - 2], "r");
    if (inputFile == NULL)
    {
        fprintf(stderr, "Can't open file: %s\n", argv[argc - 2]);
        exit(1);
    }
    if (strcmp(argv[argc - 2], "-") == 0)
    {
        readFile(stdin);
    }
    else
    {
        readFile(inputFile);
    }

    for (int i = 1; i < argc - 2; i++)
    {
        if (strcmp("line", argv[i]) == 0)
        {
            int line = atoi(argv[++i]);
            if (line <= 0 || line > lines)
            {
                printInvalidArg();
            }
            removeLines(line, line);
        }
        else if (strcmp("lines", argv[i]) == 0)
        {
            int start = atoi(argv[++i]);
            int end = atoi(argv[++i]);
            boundRows(&end);
            if (start <= 0 || end <= 0 || start > lines || end < start)
            {
                printInvalidArg();
            }
            removeLines(start, end);
        }
        else if (strcmp("col", argv[i]) == 0)
        {
            int col = atoi(argv[++i]);
            if (col <= 0 || col > MAX_STR)
            {
                printInvalidArg();
            }
            removeCols(col, col);
        }
        else if (strcmp("cols", argv[i]) == 0)
        {
            int start = atoi(argv[++i]);
            int end = atoi(argv[++i]);
            boundCols(&end);
            if (start <= 0 || end <= 0 || start > MAX_STR || end < start)
            {
                printInvalidArg();
            }
            removeCols(start, end);
        }
        else
        {
            printInvalidArg();
        }
    }
    FILE *outputFile = fopen(argv[argc - 1], "w");
    if (outputFile == NULL)
    {
        fprintf(stderr, "Can't open file: %s\n", argv[argc - 1]);
        exit(1);
    }

    if (strcmp(argv[argc - 1], "-") == 0)
    {
        writeFile(stdout);
    }
    else
    {
        writeFile(outputFile);
    }
    return 0;
}
