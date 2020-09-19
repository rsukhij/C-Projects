#include <stdlib.h>
#include <stdio.h>
#include "image.h"
/**
 * Program that processes PPM pixel data to
 * create and output a new PPM file with a
 * 4 pixel black border
 * @author Rohan Sukhija
*/

/** The size of the border to put around the image. */
#define PADDING 4

/**
 * Process PPM pixel data to output a new PPM file
 * with a 4 pixel black border
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
    unsigned char newpixels[height + PADDING + PADDING][width + PADDING + PADDING][DEPTH];

    for (int i = 0; i < height + PADDING + PADDING; i++) {
        for (int j = 0; j < width + PADDING + PADDING; j++) {
            for (int k = 0; k < DEPTH; k++) {
                newpixels[i][j][k] = 0;
            }
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < DEPTH; k++) {
                newpixels[i+PADDING][j+PADDING][k] = pixels[i][j][k];
            }
        }
    }
    writeImage(height + PADDING + PADDING, width + PADDING + PADDING, newpixels);
    return 0;
}
