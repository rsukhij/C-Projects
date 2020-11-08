#include "buffer.h"
#include "sha1.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hmac-sha1.h"

static void swapBytes4(unsigned int *val)
{
    char *p = (char *)val; 
    char t = p[0];
    p[0] = p[3];
    p[3] = t; 
    t = p[1];
    p[1] = p[2];
    p[2] = t;
}

int main(int argc, char *argv[])
{
    
    if(argc != 2 && argc != 4 ){
        fprintf(stderr,"usage: hash [-hmac <key>] <filename>\n");
        exit(1);
    }
    if(argc == 2){
        Buffer *b = readFile(argv[1]);
        if(b == NULL){
            fprintf(stderr,"Can't open file: %s\n", argv[1]);
            exit(1);
        }
        SHA1State *state = malloc(sizeof(SHA1State));
        initState(state);
        padBuffer(b);
        for( int i = 0; i < b->len/SHA1_BLOCK ; i++){
            unsigned char array[SHA1_BLOCK];
            for( int j = i*SHA1_BLOCK; j < (i+1)*SHA1_BLOCK; j++ ){
                array[j%SHA1_BLOCK] = b->data[j];
            }
            unsigned int *swap =(unsigned int *) array;
            for( int k = 0; k < 16; k++){
                swapBytes4(&swap[k]);
            }
            sha1Block(array,state);
        }
        unsigned char digest[SHA1_DIGEST];
        sha1Encode(digest,state);
        for( int i = 0; i < SHA1_DIGEST ; i++){
            printf("%02X", digest[i]);
        }
        printf("\n");
    }
    else {
        if(strcmp(argv[1], "-hmac") != 0){
            fprintf(stderr,"usage: hash [-hmac <key>] <filename>\n");
            exit(1);
        }
        Buffer *b = readFile(argv[3]);
        if(b == NULL){
            fprintf(stderr,"Can't open file: %s\n", argv[3]);
            exit(1);
        }
        unsigned char digest[SHA1_DIGEST];
        hmacSHA1(argv[2], b, digest );
        for( int i = 0; i < SHA1_DIGEST ; i++){
            printf("%02X", digest[i]);
        }
        printf("\n");


    }
    return 0;

}