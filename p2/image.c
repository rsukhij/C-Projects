#include "image.h"
#include <stdlib.h>
#include <stdio.h>

/** Program that takes care of IO and error handling
 * for the border, brighten, and blur programs
 * @author Rohan Sukhija
 */

void checkType()
{
    char p[] = "00";
    int i = scanf("%s", p);
    if (i == 1 && p[0] == MAGIC_NUMBER[0] && p[1] == MAGIC_NUMBER[1]){
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
    if ( range != STD_RANGE){
        exit(BAD_HEADER);
    }
}

void readPixels( int height, int width, unsigned char pix[ height ][ width ][ DEPTH ] )
{
    for (int i = 0; i < height ;i++){
        for (int j = 0; j < width ; j++){
            for (int k = 0; k < DEPTH ; k++){
                int num = 0;
                scanf("%d", &num);
                if (num < 0 || num > STD_RANGE){
                    exit(BAD_PIXEL);
                }
                pix[i][j][k] = num;
            }
        }
    }
    int i;
    if (scanf("%d", &i) != EOF){
        exit(BAD_PIXEL);
    }

}

void writeImage( int height, int width, unsigned char pix[ height ][ width ][ DEPTH ] ){
    printf("P3\n%d %d\n%d\n", width, height, STD_RANGE);
    for (int i = 0; i < height ;i++){
        for (int j = 0; j < width ; j++){
            for (int k = 0; k < DEPTH ; k++){
               int num = (int) pix[i][j][k];
               if (j == 0 && k==0){
                   printf("%d", num);
               } else {
                    printf(" %d", num);
               }
            }
        }
        printf("\n");
    }
}
