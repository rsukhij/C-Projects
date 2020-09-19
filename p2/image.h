/** Maximum intensity value expected for images. */
#define STD_RANGE 255

/** Number of color components per pixel */
#define DEPTH 3

/** Exit code for a bad magic number at the top. */
#define BAD_HEADER 100

/** Exit code for bad or missing pixel data */
#define BAD_PIXEL 101

/** The magic number that starts each PPM file */
#define MAGIC_NUMBER "P3"

/** Checks the type of the file */
void checkType();

/** Reads one dimension of the PPM file
 * @return a dimension of the PPM file
 */
int readDimension();

/** Checks the maximum intensity of the PPM pixels*/
void checkRange();

/** Reads the pixels content and saves in a char array
 * @param height the height of the image in pixels
 * @param width the width of the image in pixels
 * @param pix the array being filled
 */
void readPixels( int height, int width, unsigned char pix[ height ][ width ][ DEPTH ] );

/** Writes the pixel array's content into a new formatted PPM file 
 * @param height the height of the image in pixels
 * @param width the width of the image in pixels
 * @param pix the array being outputted
 */
void writeImage( int height, int width, unsigned char pix[ height ][ width ][ DEPTH ] );