#include <string.h>
#include "sha1.h"
#include "buffer.h"
#include <stdio.h>

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

void hmacSHA1( char *kstr, Buffer *b, unsigned char digest[ SHA1_DIGEST ])
{
    unsigned char key[SHA1_BLOCK] = {'\0'};
    int k = 0;
    while(kstr[k]){
        key[k] = kstr[k];
        k++;
    }
    unsigned char opad[SHA1_BLOCK];
    unsigned char ipad[SHA1_BLOCK];
    for(int j = 0 ; j < SHA1_BLOCK ; j++){
        opad[j] = key[j] ^ 0x5c;
        ipad[j] = key[j] ^ 0x36;
    }
    Buffer *firstH = makeBuffer();
    for(int j = 0 ; j < SHA1_BLOCK ; j++){
        appendBuffer(firstH, ipad[j]);
    }
    for(int j = 0; j < b->len; j++ ){
        appendBuffer(firstH, b->data[j]);
    }
    padBuffer(firstH);
    SHA1State *state = malloc(sizeof(SHA1State));
    initState(state);
    for( int i = 0; i < firstH->len/SHA1_BLOCK ; i++){
        unsigned char array[SHA1_BLOCK];
        for( int j = i*SHA1_BLOCK; j < (i+1)*SHA1_BLOCK; j++ ){
            array[j%SHA1_BLOCK] = firstH->data[j];
        }
        unsigned int *swap =(unsigned int *) array;
        for( int k = 0; k < 16; k++){
            swapBytes4(&swap[k]);
        }
        sha1Block(array,state);
    }
    unsigned char firstDigest[SHA1_DIGEST];
    sha1Encode(firstDigest,state);
    Buffer *secondH = makeBuffer();
    for(int j = 0 ; j < SHA1_BLOCK ; j++){
        appendBuffer(secondH, opad[j]);
    }
    for(int j = 0; j < SHA1_DIGEST; j++ ){
        appendBuffer(secondH, firstDigest[j]);
    }
    padBuffer(secondH);
    initState(state);
    for( int i = 0; i < secondH->len/SHA1_BLOCK ; i++){
        unsigned char array[SHA1_BLOCK];
        for( int j = i*SHA1_BLOCK; j < (i+1)*SHA1_BLOCK; j++ ){
            array[j%SHA1_BLOCK] = secondH->data[j];
        }
        unsigned int *swap =(unsigned int *) array;
        for( int k = 0; k < 16; k++){
            swapBytes4(&swap[k]);
        }
        sha1Block(array,state);
    }
    sha1Encode(digest,state);



}
