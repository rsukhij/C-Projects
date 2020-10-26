#include "catalog.h"
#include "input.h"

static int *list;
int size;

Catalog *makeCatalog()
{
    Catalog *new = malloc(sizeof(Catalog));
    new->books = malloc(sizeof(Book*)*5);
    new->count = 0;
    new->capacity = 5;
    for(int i = 0 ; i < new->capacity ; i++){
        (new->books)[i] = calloc(1, sizeof(Book));
    }
    return new;
}

void freeCatalog( Catalog *cat)
{
    Book **books = (cat->books);
    for(int i = 0 ; i < cat->capacity ; i++){
        free(books[i]);
    }
    free(books);
    free(cat);

}

static int cmpIDfunc ( const void *a, const void * b) 
{
    Book *book1 = *((Book **)a);
    Book *book2 = *((Book **)b);
    return ( book1->id - book2->id );

}

static int cmpLevel (const void *a, const void * b){
    Book *book1 = *((Book **)a);
    Book *book2 = *((Book **)b);
    if((book1->level - book2->level) != 0.0){
        return (book1->level - book2->level)*100;
    }
    return (book1->id - book2->id)*100;
}

static void checkDuplicate(int id, Catalog *cat)
{
    for( int i = 0; i < cat->count ; i++ ){
        int sum = 0;
        if(cat->books[i]->id == id){
                sum++;
        }
        if (sum > 0 ) {
            fprintf(stderr, "%s%d\n","Duplicate book id: ",cat->books[i]->id);
            exit(1);
        }
    }
}

void readCatalog(Catalog *cat, char const *filename){
    FILE *fp = fopen(filename, "r");
    
    Book *book;
    char *str; 
    char a;
    int i = cat->count;
    while((str = readLine(fp)) != NULL){
        if(cat->count == cat->capacity){
            cat->capacity = cat->capacity*2;
            cat->books = realloc(cat->books,sizeof(Book*)*cat->capacity);
            for(int i =cat->capacity/2 ; i <cat->capacity; i++){
                (cat->books)[i] = calloc(1, sizeof(Book));
            }
        }
        book = (cat->books)[i];
        int sum = 0; 
        int posIncr = 0;
        int pos = 0;
        sum += sscanf(str + pos ,"%d%c%n", &(book->id),&a,&posIncr);
        checkDuplicate(book->id, cat);
        pos += posIncr;
        sum += sscanf(str + pos ,"%39[^\t]%n", (book->title),&posIncr);
        pos += posIncr;
        if(strlen(book->title) == 39){
            int j =0; 
            sscanf(str + pos, "%*[^\t]%n",&j);
            pos += j+1;
        }
        else{
            pos += 1;
        }
        sum += sscanf(str + pos,"%21[^\t]%n", (book->author), &posIncr);
        pos += posIncr;
        if(strlen(book->author) == 21){
            int j =0; 
            sscanf(str + pos, "%*[^\t]%n",&j);
            pos += j+1;
        }
        else{
            pos += 1;
        }
        sum += sscanf(str + pos,"%lf%n", &(book->level),&posIncr);

        pos += posIncr;
        sum += sscanf(str + pos,"%d", &(book->wordCount));
        if(sum != 6){
            fprintf(stderr, "%s%s\n","Invalid book list: ",filename);
            exit(1);
        }
        i++;
        (cat->count)++;
        
    }
    fclose(fp);


}

static bool trueForAll( Book const *book, void const *data ){
    return true;
}

static void listCatalog( Catalog *cat, bool (*test)( Book const *book, void const *data ), void const *data )
{
    printf("   ID                                  Title               Author Level   Words\n");
    for(int i = 0 ; i < cat->count; i++){
        if(test(cat->books[i],data)){
            printf("%5d ",cat->books[i]->id);
            if(strlen(cat->books[i]->title) == 39){
                printf("%.36s.. ",cat->books[i]->title);
            }
            else{
                 printf("%38s ",cat->books[i]->title);
            }
            if(strlen(cat->books[i]->author) == 21){
                printf("%.18s.. ",cat->books[i]->author);
            }
            else{
                printf("%20s ",cat->books[i]->author);
            }
            printf("%5.1lf ",cat->books[i]->level);
            printf("%7d\n",cat->books[i]->wordCount);
        }
    }

}

void listAll( Catalog *cat )
{
    qsort(cat->books, cat->count, sizeof(Book*), cmpIDfunc);
    listCatalog(cat, trueForAll, NULL);
}

static bool ifInList( Book const *book, void const *data ){
    const Catalog *c = data;
    int a;
    for(int i = 0; i < c->count ; i++){
        if(book->id == c->books[i]->id){
            a = i;
            break;
        }
    }
    return list[a];
}

void listLevel( Catalog *cat, double min , double max)
{
    qsort(cat->books, cat->count, sizeof(Book*), cmpLevel);
    list = calloc(sizeof(int), cat->count);
    size = 0;
    for(int i = 0; i < cat->count ;i++ ){
        if(cat->books[i]->level >= min && cat->books[i]->level <= max){
            list[i] = 1;
            size++;
        }
    }
    if(size == 0){
        printf("No matching books\n");
        return;
    }
    listCatalog(cat, ifInList, cat);

}