#include "catalog.h"
#include "input.h"

/**
 * Implements function to convert a line in a file
 * stream to a string
 * @author Rohan Sukhija
 */

char *readLine(FILE *fp)
{
    char a = fgetc(fp);
    char *str = malloc(sizeof(char));
    if (a == '\n') {
        str[0] = '\0';
        return str;
    }
    if (a == EOF) {
        free(str);
        return NULL;
    }
    str[0] = a;
    str = realloc(str, GROW_MAG * sizeof(char));
    int i = 1;
    while (((a = fgetc(fp)) != '\n') && (a != EOF)) {
        str[i] = a;
        str = realloc(str, GROW_MAG * sizeof(char) + i * sizeof(char));
        i++;
    }
    str = realloc(str, GROW_MAG * sizeof(char) + i * sizeof(char));
    str[i] = '\0';
    return str;
}
