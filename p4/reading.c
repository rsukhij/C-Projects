#include "catalog.h"
#include "input.h"

static int *list;
static int position = 0;
static int size = 0;


static int addToList(int id, Catalog *cat){
    for(int i =0 ; i< position; i++){
        if(list[i] == id ){
            return -2;
        }
    }
    bool ok = false; 
    for(int i =0 ; i < cat->count ;i++){
        if(cat->books[i]->id == id ){
            ok = true; 
        }
    }
    if(!ok){
        return -1;
    }
    list[position++] = id;
    size++;
    return 1;
}

static int removeFromList(int id, Catalog *cat){
    for(int i =0 ; i< position; i++){
        if(list[i] == id ){
            list[i] = 0;
            size--;
            return 1;
        }
    }
    return -1;

}

static int cmpID ( const void *a, const void * b) 
{
    Book *book1 = *((Book **)a);
    Book *book2 = *((Book **)b);
    return ( book1->id - book2->id );

}

static bool existsInList(int id){
    for(int i =0 ; i< position; i++){
        if(list[i] == id ){
            return true;
        }
    }
    return false;
}

static Book* findBook(int id , Catalog *cat){
    for( int i =0 ; i < cat->count;i++){
        if(id == cat->books[i]->id){
            return cat->books[i];
        }
    }
    return NULL;
} 

static void printList(Catalog *cat){
    printf("   ID                                  Title               Author Level   Words\n");
    int sumCount = 0;
    double sumLevel = 0;
    for(int i = 0 ; i < position ; i++){
        if(list[i] != 0 && existsInList(list[i])){
            Book *book = findBook(list[i], cat);
            sumCount+= book->wordCount;
            sumLevel += book->level;
            printf("%5d ",book->id);
            if(strlen(book->title) == 39){
                printf("%.36s.. ",book->title);
            }
            else{
                 printf("%38s ",book->title);
            }
            if(strlen(book->author) == 21){
                printf("%.18s.. ",book->author);
            }
            else{
                printf("%20s ",book->author);
            }
            printf("%5.1lf ",book->level);
            printf("%7d\n",book->wordCount);
        }
    }
    printf("                                                                  ");
    printf("%5.1lf %7d\n",sumLevel/size,sumCount);                                                                  
}



int main( int argc, char *argv[]) 
{
    if(argc < 2) { 
        fprintf(stderr, "usage: reading <book-list>*\n");
        exit(1);
    }
    

    Catalog *c = makeCatalog();

    for ( int i =1; i < argc; i++){

        FILE *fp = fopen(argv[i], "r");
        if(!fp){
            fclose(fp);
            fprintf(stderr, "%s%s\n","Can't open file: ", argv[i]);
            exit(1);
        }
        readCatalog(c, argv[i]);
        fclose(fp);
    }
    list = calloc(c->count*10, sizeof(int));
    while(true){
        printf("cmd> ");
        char *str = readLine(stdin);
        printf("%s\n", str);
        if(str == NULL){
            return 0;
        }
        char command[10] = {'\0'};
        char temp[100] = {'\0'};
        double min; 
        double max; 
        int id;

        freeCatalog(c);
        c = makeCatalog();
        for ( int i = 1; i < argc; i++){
            readCatalog(c, argv[i]);
        }
        if(sscanf(str,"%s%s", command, temp) == 1){
            if(strcmp(command, "catalog") == 0){
                listAll(c);
            }
            else if(strcmp(command, "list") == 0){
                if(size != 0){
                    printList(c);

                }
                else{
                    printf("List is empty\n");
                }
            }
            else if(strcmp(command, "quit") == 0){
                return 0;
            }
            else {
                printf("Invalid command\n");
            }
        }
        else if(sscanf(str,"%s%lf%lf%s", command, &min, &max, temp) == 3){
            if(strcmp(command, "level") == 0){
                listLevel(c, min, max);
            }
             else {
                printf("Invalid command\n");
            }
        }
        else if(sscanf(str,"%s%d%s", command, &id, temp) == 2){
            if(strcmp(command, "add") == 0){
                int status = addToList(id, c);
                if(status == -1){
                    printf("Book %d is not in the catalog\n",id);
                }
                else if(status == -2){
                    printf("Book %d is already on the reading list\n",id);
                }
            }
            else if(strcmp(command, "remove") == 0){
                int status = removeFromList(id, c);
                if(status < 0){
                    printf("Book %d is not on the reading list\n",id);
                }

            }
            else {
                printf("Invalid command\n");
            }
        }
        else{
            printf("Invalid command\n");
        }
        if (feof(stdin)){
            return 0;
        }   
        printf("\n");
        
    }
    free(list);
    freeCatalog(c);
    return 0;
}

