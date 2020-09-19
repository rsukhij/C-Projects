#include "image.h"

/**
 * Applies a Gaussian blur on pixel data and outputs
 * new PPM file with blur added.
 * @author Rohan Sukhija
 */

/** The weightage(out of 16) of a Gaussian blur corner pixel */
#define CORNER 1
/** The weightage(out of 16) of a Gaussian blur edge pixel */
#define EDGE 2
/** The weightage(out of 16) of a Gaussian blur center pixel */
#define CENTER 4

/** Checks if a particular array element is within the bounds 
 *  of the array. 
 * @param num the particular element in the array
 * @param height the height of the array
 * @param width the width of the array
 * @param i the index of the row of the element
 * @param j the index of the column of the element
 * @return num if the element is within bounds, -1 
 * if not. 
 */
int bound(int num, int height, int width, int i, int j)
{
    if (i < 0 || i >= height || j < 0 || j >= width){
        return -1;
    }
    return num;
}

/**
 * Applies a Gaussian blur on pixel data and outputs
 * new PPM file with blur added.
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
    unsigned char blur[height][width][DEPTH];
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            for (int k = 0; k < DEPTH; k++){
                int sum = 0;
                int totalWeight = 0;
                sum += CENTER * pixels[i][j][k];
                totalWeight += CENTER;
                if (bound(pixels[i - 1][j - 1][k], height, width, i - 1, j - 1) != -1) {
                    sum += CORNER * pixels[i - 1][j - 1][k];
                    totalWeight += CORNER;
                }
                if (bound(pixels[i - 1][j][k], height, width, i - 1, j) != -1){
                    sum += EDGE * pixels[i - 1][j][k];
                    totalWeight += EDGE; }
                if (bound(pixels[i - 1][j + 1][k], height, width, i - 1, j + 1) != -1){
                    sum += CORNER * pixels[i - 1][j + 1][k];
                    totalWeight += CORNER;
                }
                if (bound(pixels[i][j + 1][k], height, width, i, j + 1) != -1){
                    sum += EDGE * pixels[i][j + 1][k];
                    totalWeight += EDGE;
                }
                if (bound(pixels[i + 1][j + 1][k], height, width, i + 1, j + 1) != -1){
                    sum += CORNER * pixels[i + 1][j + 1][k];
                    totalWeight += CORNER;
                }
                if (bound(pixels[i + 1][j][k], height, width, i + 1, j) != -1){
                    sum += EDGE * pixels[i + 1][j][k];
                    totalWeight += EDGE;
                }
                if (bound(pixels[i + 1][j - 1][k], height, width, i + 1, j - 1) != -1) {
                    sum += CORNER * pixels[i + 1][j - 1][k];
                    totalWeight += CORNER;
                }
                if (bound(pixels[i][j - 1][k], height, width, i, j - 1) != -1){
                    sum += EDGE * pixels[i][j - 1][k];
                    totalWeight += EDGE;
                }
                blur[i][j][k] = sum / totalWeight;
            }
        }
    }
    writeImage(height, width, blur);
    return 0;
}