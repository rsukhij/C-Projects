#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
/**
*Struct representing the 
*record of a book
*/
typedef struct Book {
    /** The id of the book */ 
    int id; 
    /** The title of the book */
    char title[40];
    /** the author of the book */
    char author[22]; 
    /** the reading level of the book */
    double level; 
    /** the word count of the book */
    int wordCount;
} Book;

/**Struct representing a Catalog of Books
*
*/
typedef struct Catalog { 
    /** Pointer to an array of pointers to books */
    Book **books; 
    /** the number of books */
    int count; 
    /** the capacity of the catalog */
    int capacity; 
} Catalog;

/**
*Dynamically allocates storage for the catalog, intializes its
* fields and returns a pointer to it. 
*@return the pointer to the catalog intialized
*/
Catalog *makeCatalog();

/**
* Frees the all the memory used to store the catalog
* @param cat the pointer to the catalog
*/
void freeCatalog(Catalog *cat); 

/**
* Reads all the books from a given file. Makes an instance of the 
* Book struct for each book and stores a pointer to that book in the 
* array field within the catalog. 
* @param cat the catalog being filled
* @param filename the string name of the file
*/
void readCatalog(Catalog *cat, char const *filename ) ; 

/**
* Lists all the books in the Catalog, sorted by ID number
* @param cat the catalog being listed
*/
void listAll(Catalog *cat); 

/**
* Lists all the book within the reading level bounds given
* @param cat the catalog being listed 
* @param min the minimum(inclusive) reading level bound
* @param max the maximum(inclusive) reading level bound
*/
void listLevel(Catalog *cat, double min , double max); 





