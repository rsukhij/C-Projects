/** 
*/

#include "sha1.h"
#include "buffer.h"
#include <stdio.h>


/** Constants, to mix in some random-looking bits during the SHA1
    calculation.  80 constants for 80 iterations.  The constants for one 
    round (iterations 0-19, 20-39, 40-59, 60-79) all have the same value. **/
static unsigned int k[ 80 ] =
    {
    0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999,
    0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1,
    0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC,
    0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6,
    };


void padBuffer( Buffer *b)
 {
     unsigned long long length= b->len*8;
     if(b->cap - b->len < 9){
        b->data = realloc(b->data,b->cap*2);
        b->cap *= 2;
     }
     b->data[b->len] = 0x80;
     b->len++;
     while(((b->len + 8) % SHA1_BLOCK) != 0){
        b->data[b->len] = '\0';
        b->len++;
     } 
     long long unsigned int * pointer = &length;
     for( int i = 7 ; i >= 0; i--) { 
         char byte =  *( ((char*) pointer) + i );
         b->data[b->len+7-i] = byte;
     }
     b->len += 8;
}

void initState( SHA1State *state ) 
{
    state->h0 = 0x67452301;
    state->h1 = 0xEFCDAB89;
    state->h2 = 0x98BADCFE;
    state->h3 = 0x10325476;
    state->h4 = 0xC3D2E1F0;
}

test_static unsigned int fVersion0( unsigned int b, unsigned int c, unsigned int d )
{
    return (b&c)|(~b&d);
}

test_static unsigned int fVersion1( unsigned int b, unsigned int c, unsigned int d )
{
    return b ^ c ^ d;
}
test_static unsigned int fVersion2( unsigned int b, unsigned int c, unsigned int d ){
    return (b&c)|(b&d)|(c&d);
}

test_static unsigned int fVersion3( unsigned int b, unsigned int c, unsigned int d )
{
    return b ^ c ^ d;

}

test_static unsigned int rotateLeft(unsigned int num, int s)
{
    return (num << s) | (num >> (32 - s));
}

test_static void sha1Iteration( unsigned int data[ 16 ], unsigned int *a, unsigned int *b,
unsigned int *c, unsigned int *d, unsigned int *e, int i )
{
    unsigned int w[80];
    for(int j = 0; j < 16 ; j++){
        w[j] = data[j];
    } 
    for(int j =16 ; j <= 79; j++ ){
        w[j] = rotateLeft(w[j-16]^w[j-14]^w[j-8]^w[j-3],1);
    }
    unsigned int temp;
    if(i >= 0 && i <= 19){
    temp = *e + rotateLeft(*a,5) + w[i] + k[i] + fVersion0(*b, *c, *d);
    }
    else if(i >= 20 && i <= 39){
     temp = *e + rotateLeft(*a,5) + w[i] + k[i] + fVersion1(*b, *c, *d);
    }
    else if(i >= 40 && i <= 59){
     temp = *e + rotateLeft(*a,5) + w[i] + k[i] + fVersion2(*b, *c, *d);
    } else {
     temp = *e + rotateLeft(*a,5) + w[i] + k[i] + fVersion3(*b, *c, *d);
    }
    *e = *d; 
    *d = *c;
    *c = rotateLeft(*b, 30);
    *b = *a;
    *a = temp;
}


void sha1Block( unsigned char data[ SHA1_BLOCK ], SHA1State *state )
{
    unsigned int a = state->h0;
    unsigned int b = state->h1;
    unsigned int c = state->h2;
    unsigned int d = state->h3;
    unsigned int e = state->h4;
    unsigned int *first = (unsigned int*) data;
    for(int i =0; i < 80; i++){
        sha1Iteration(first, &a,&b, &c,&d,&e,i);
    }
    state->h0 += a; 
    state->h1 += b;
    state->h2 += c;
    state->h3 += d;
    state->h4 += e;
}

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

void sha1Encode( unsigned char digest[ SHA1_DIGEST ], SHA1State *state)
{
    swapBytes4(&state->h0);
    swapBytes4(&state->h1);
    swapBytes4(&state->h2);
    swapBytes4(&state->h3);
    swapBytes4(&state->h4);
    unsigned int array[5] = {state->h0,state->h1,state->h2,state->h3,state->h4};
    int count = 0; 
    for(int i = 0 ; i < 5 ; i++){
        for(int j = 0; j < 4; j++){
            digest[count] =  *( ((char*) &array[i]) + j );
            count ++;
        }
    }

}






