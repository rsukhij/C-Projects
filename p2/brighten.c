
#include "image.h"
#include <stdlib.h>

int main() 
{
    checkType();
    int height = readDimension();
    int width = readDimension();
    checkRange();
    unsigned char pixels[height][width][DEPTH];
    readPixels(height, width, pixels);
    for(int i = 0; i < height ;i++){
        for(int j = 0; j < width ; j++){
            for(int k = 0; k < DEPTH ; k++){
                if((int) pixels[i][j][k] > (int) 222){
                    pixels[i][j][k] = (unsigned char) 255;
                }
                else{
                    pixels[i][j][k] += (int) 32;
                }
            }
        }
    }
    writeImage(height, width, pixels);
    return 0;
}
