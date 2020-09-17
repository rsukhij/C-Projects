#include "image.h"
#include <stdlib.h>
#include <stdio.h>


void checkType()
{
    char p[] = "00";
    int i = scanf("%s", p);
    if(i == 1 && p[0] == MAGIC_NUMBER[0] && p[1] == MAGIC_NUMBER[1]){
        return;
    }
    exit(BAD_HEADER);
}

int readDimension()
{
    int num = 0;
    if ( scanf("%d", &num) != 1 || num < 1){
        exit(BAD_HEADER);
    }
    return num;
}

void checkRange()
{
    int range = 0; 
    scanf("%d", &range);
    if( range != STD_RANGE){
        exit(BAD_HEADER);
    }
}

void readPixels( int height, int width, unsigned char pix[ height ][ width ][ DEPTH ] )
{
    int pixelCount = height * width * DEPTH; 
    int actualCount = 0;
    for(int i = 0; i < height ;i++){
        for(int j = 0; j < width ; j++){
            for(int k = 0; k < DEPTH ; k++){
                int num = 0; 
                scanf("%d", &num);
                pix[i][j][k] = num;
                actualCount++;
            }
        }
    }
    if(pixelCount != actualCount){
        exit(BAD_PIXEL);
    }

}

void writeImage( int height, int width, unsigned char pix[ height ][ width ][ DEPTH ] ){
    printf("P3\n%d %d\n%d", height, width, STD_RANGE);
    for(int i = 0; i < height ;i++){
        printf("\n");
        for(int j = 0; j < width ; j++){
            for(int k = 0; k < DEPTH ; k++){
               int num = pix[i][j][k];
               printf("%3d ",num);
            }
        }
    }
}
