#include "catalog.h"
#include "input.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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
    const Book *book1 = a;
    const Book *book2 = b;
    const int aa = book1->id;
    const int bb = book2->id;
    return ( aa - bb );
}

static int cmpLevel (const void *a, const void * b){
    const Book *book1 = a;
    const Book *book2 = b;
    if((book1->level - book2->level) != 0){
        return (book1->level - book2->level);
    }
    return (book1->id - book2->id);
}


void readCatalog(Catalog *cat, char const *filename){
    FILE *fp = fopen(filename, "r");
    
    Book *book;
    char *str; 
    char a;
    int i = 0;
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
        pos += posIncr;
        sum += sscanf(str + pos ,"%38[^\t]%c%n", (book->title),&a,&posIncr);
        printf("%s\n",book->title);
        printf("%d\n",sum);

        pos += posIncr;
        if(posIncr == 39){
            int j =0; 
            sscanf(str + pos, "%*[^\t]%n",&j);
            pos += j+1;
        }
        sum += sscanf(str + pos,"%20[^\t]%n", (book->author), &posIncr);

        printf("%s\n",book->author); 
        pos += posIncr;
        if(posIncr == 20){
            int j =0; 
            sscanf(str + pos, "%*[^\t]%n",&j);
            pos += j+1;
        }
        sum += sscanf(str + pos,"%lf%n", &(book->level),&posIncr);


        pos += posIncr;
        sum += sscanf(str + pos,"%d", &(book->wordCount));


        pos += posIncr;
        if(sum != 7){
            fprintf(stderr, "%s%s\n","Invalid book list: ",filename);
            exit(1);
        }
        i++;
        (cat->count)++;
        
    }
    for( int i = 0; i < cat->count ; i++ ){
        int sum = 0;
        for(int j = 0; j < cat->count; j++ ){
            if(cat->books[i]->id == cat->books[j]->id){
                sum++;
            }
        }
        if (sum > 1 ) {
            fprintf(stderr, "%s%d\n","Duplicate book id: ",cat->books[i]->id);
            exit(1);
        }
    }
    fclose(fp);
    printf("%d\n",cat->count);
    qsort(cat->books, cat->count, sizeof(Book*), cmpIDfunc);


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
            if(strlen(cat->books[i]->title) == 38){
                printf("%.36s.. ",cat->books[i]->title);
            }
            else{
                 printf("%38s ",cat->books[i]->title);
            }
            if(strlen(cat->books[i]->author) == 20){
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
    listCatalog(cat, trueForAll, NULL);
}