#include "buffer.h"
#include "sha1.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Component for the that adds functionality for interacting 
 * with the input file buffer.
 * @author Rohan Sukhija 
 */

Buffer *makeBuffer()
{
    Buffer *b = malloc(sizeof(Buffer));
    b->cap = SHA1_BLOCK;
    b->len = 0;
    b->data = malloc(sizeof(char) * SHA1_BLOCK);
    return b;
}

void appendBuffer(Buffer *b, unsigned char byte)
{
    if (b->len == b->cap) {
        b->data = realloc(b->data, b->cap * 2);
        b->cap *= 2;
    }
    b->data[b->len] = byte;
    b->len++;
}

void freeBuffer(Buffer *b)
{
    free(b->data);
    free(b);
}

Buffer *readFile(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        return NULL;
    }
    Buffer *b = makeBuffer();
    unsigned char c;
    while (fread(&c, 1, 1, fp) == 1) {
        appendBuffer(b, c);
    }
    fclose(fp);
    return b;
}