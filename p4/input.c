
#include "input.h"

char *readLine( FILE *fp ) 
{
    char a = fgetc(fp); 
    char *str = malloc(sizeof(char));
    if(a == EOF){
        return NULL;
    }
    str[0] = a;
    str = realloc(str,2*sizeof(char));
    int i = 1; 
    while(((a= fgetc(fp)) != '\n') && (a != EOF)){
        str[i] = a;
        str = realloc(str,2*sizeof(char) + i*sizeof(char));
        i++;
    }
    str = realloc(str, 2*sizeof(char) + i*sizeof(char));
    str[i] = '\0';
    return str;
}          


