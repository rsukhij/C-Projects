/** Maximum intensity value expected for images. */
#define STD_RANGE 255

/** Number of color components per pixel */
#define DEPTH 3

/** Exit code for a bad magic number at the top. */
#define BAD_HEADER 100

/** Exit code for bad or missing pixel data */
#define BAD_PIXEL 101

#define MAGIC_NUMBER "P3"

void checkType();

int readDimension();

void checkRange();

void readPixels( int height, int width, unsigned char pix[ height ][ width ][ DEPTH ] );

void writeImage( int height, int width, unsigned char pix[ height ][ width ][ DEPTH ] );