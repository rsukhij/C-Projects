/**
 * Program that adds functionality to 
 * to edit the global array storing the
 * files contents
 * @author Rohan Sukhija
 */

#include "text.h"
#include "edit.h"
#include <string.h>


void removeLines(int start, int end)
{
    for (int i = start; i <= lines; i++) {
        strcpy(input[i - 1], input[i + end - start]);
    }
    lines -= end - start + 1;
}


void editLine(int lno, int start, int end)
{
    for (int i = start; i < MAX_STR; i++) {
        input[lno][i - 1] = input[lno][i + end - start];
        if (input[lno][i + end - start] == '\0') {
            return;
        }
    }
}


void removeCols(int start, int end)
{
    for (int i = 0; i < lines; i++) {
        editLine(i, start, end);
    }
}
