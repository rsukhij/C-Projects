#include "catalog.h"
#include "input.h"


int main( int argc, char *argv[]) 
{
    if(argc < 2) { 
        fprintf(stderr, "usage: reading <book-list>*\n");
        exit(1);
    }
    FILE *fp = fopen(argv[1], "r");
    if(!fp){
        fclose(fp);
        fprintf(stderr, "%s%s\n","Can't open file: ", argv[1]);
    }
    fclose(fp);
    Catalog *c = makeCatalog();
    readCatalog(c, argv[1]);
    listAll(c);
    return 0;
}