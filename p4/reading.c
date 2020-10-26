#include "catalog.h"
#include "input.h"


/** The reading list array containing ids of books in reading list */
static int *list;
/** The current adding position of the reading list */
static int position = 0;
/** The size of the reading list */
static int size = 0;

/**
 * Adds book to reading list
 * @param id the id of the book
 * @param cat the catalog
 * @return -2 if the book is already in the list
 * -1 if the book is not in the catalog
 * 1 if the book was successfully added
 */
static int addToList(int id, Catalog *cat)
{
    for (int i = 0; i < position; i++) {
        if (list[i] == id) {
            return ERROR_2;
        }
    }
    bool ok = false;
    for (int i = 0; i < cat->count; i++) {
        if (cat->books[i]->id == id) {
            ok = true;
        }
    }
    if (!ok) {
        return -1;
    }
    list[position++] = id;
    size++;
    return 1;
}

/**
 * Removes book list
 * @param id the id of the book
 * @param cat the catalog of books
 * @return 1 if the book was successfully removed
 * -1 if the id is not in the reading list
 */
static int removeFromList(int id, Catalog *cat)
{
    for (int i = 0; i < position; i++) {
        if (list[i] == id) {
            list[i] = 0;
            size--;
            return 1;
        }
    }
    return -1;
}

/**
 * Returns if the id is in list
 * @param id the id
 * @return if the id is in the list
 */
static bool existsInList(int id)
{
    for (int i = 0; i < position; i++) {
        if (list[i] == id) {
            return true;
        }
    }
    return false;
}

/**
 * Finds the book in the catalog
 * @param id the id of the book
 * @param cat the catalog of books
 * @return the book in the catalog
 */
static Book *findBook(int id, Catalog *cat)
{
    for (int i = 0; i < cat->count; i++) {
        if (id == cat->books[i]->id) {
            return cat->books[i];
        }
    }
    return NULL;
}

/**
 * Prints the list
 * @param cat the catalog
 */
static void printList(Catalog *cat)
{
    printf("   ID                                  Title               Author Level   Words\n");
    int sumCount = 0;
    double sumLevel = 0;
    for (int i = 0; i < position; i++) {
        if (list[i] != 0 && existsInList(list[i])) {
            Book *book = findBook(list[i], cat);
            sumCount += book->wordCount;
            sumLevel += book->level;
            printf("%5d ", book->id);
            if (strlen(book->title) == 39) {
                printf("%.36s.. ", book->title);
            }
            else {
                printf("%38s ", book->title);
            }
            if (strlen(book->author) == 21) {
                printf("%.18s.. ", book->author);
            }
            else {
                printf("%20s ", book->author);
            }
            printf("%5.1lf ", book->level);
            printf("%7d\n", book->wordCount);
        }
    }
    printf("                                                                  ");
    printf("%5.1lf %7d\n", sumLevel / size, sumCount);
}

/**
 * Parses commandline arguments and commands
 * and executes reading program
 * @param argc the number of commandline arguments
 * @param argv the array of string containing commandline arguments
 * @return the exit code
 */
int main(int argc, char *argv[])
{
    if (argc <= 1) {
        fprintf(stderr, "usage: reading <book-list>*\n");
        exit(1);
    }

    Catalog *c = makeCatalog();

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (!fp) {
            fprintf(stderr, "%s%s\n", "Can't open file: ", argv[i]);
            freeCatalog(c);
            exit(1);
        }
        readCatalog(c, argv[i]);
        fclose(fp);
    }
    list = calloc(c->count * ARRAY_MAG, sizeof(int));
    while (true) {
        printf("cmd> ");

        char *str = readLine(stdin);
        if (str == NULL) {
            free(list);
            freeCatalog(c);
            return 0;
        }

        printf("%s\n", str);
        char command[ARRAY_MAG] = {'\0'};
        char temp[ARRAY_MAG * ARRAY_MAG] = {'\0'};
        double min;
        double max;
        int id;

        if (sscanf(str, "%s%s", command, temp) == 1) {
            if (strcmp(command, "catalog") == 0) {
                listAll(c);
            }
            else if (strcmp(command, "list") == 0) {
                if (size != 0) {
                    printList(c);
                }
                else {
                    printf("List is empty\n");
                }
            }
            else if (strcmp(command, "quit") == 0) {
                free(list);
                free(str);
                freeCatalog(c);
                return 0;
            }
            else {
                printf("Invalid command\n");
            }
        }
        else if (sscanf(str, "%s%lf%lf%s", command, &min, &max, temp) == 1 + 1 + 1) {
            if (strcmp(command, "level") == 0) {
                listLevel(c, min, max);
            }
            else {
                printf("Invalid command\n");
            }
        }
        else if (sscanf(str, "%s%d%s", command, &id, temp) == 1 + 1) {
            if (strcmp(command, "add") == 0) {
                int status = addToList(id, c);
                if (status == -1) {
                    printf("Book %d is not in the catalog\n", id);
                }
                else if (status == ERROR_2) {
                    printf("Book %d is already on the reading list\n", id);
                }
            }
            else if (strcmp(command, "remove") == 0) {
                int status = removeFromList(id, c);
                if (status < 0)
                {
                    printf("Book %d is not on the reading list\n", id);
                }
            }
            else {
                printf("Invalid command\n");
            }
        }
        else {
            printf("Invalid command\n");
        }
        printf("\n");
        free(str);
    }
    free(list);
    freeCatalog(c);
    return 0;
}
