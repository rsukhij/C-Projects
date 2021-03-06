#include "image.h"
#include <stdlib.h>

/**
 * Brightens PPM pixel data input by adding 25
 * to each RGB value up to 255. Outputs brightened
 * image to PPM file
 * @author Rohan Sukhija
 */

#define INTENSITY_INCREASE 32

/**
 * Brightens PPM pixel data input by adding 25
 * to each RGB value up to 255. Outputs brightened
 * image to PPM file
 * @return 0 if program finishes successfully
 */
int main()
{
    checkType();
    int width = readDimension();
    int height = readDimension();
    checkRange();
    unsigned char pixels[height][width][DEPTH];
    readPixels(height, width, pixels);
    for (int i = 0; i < height ;i++){
        for (int j = 0; j < width ; j++){
            for (int k = 0; k < DEPTH ; k++){
                if ((int) pixels[i][j][k] >= (int) (STD_RANGE - INTENSITY_INCREASE)){
                    pixels[i][j][k] = (unsigned char) STD_RANGE;
                }
                else {
                    pixels[i][j][k] += (int) INTENSITY_INCREASE;
                }
            }
        }
    }
    writeImage(height, width, pixels);
    return 0;
}
