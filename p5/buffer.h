/**
 * Header file for the buffer component
 * @author Rohan Sukhija
 */

#ifndef _BUFFER_H_
#define _BUFFER_H_

/** Representation for the contents of an input file, copied to memory. */
typedef struct {
  /** Array of bytes from the file (not stored as a string - no NULL termination). */
  unsigned char *data;

  /** Number of currently used bytes in the data array. */
  unsigned int len;

  /** Capacity of the data array (it's typically over-allocated. */
  unsigned int cap;
} Buffer;

#endif

/**
 * Dynamically allocates a Buffer struct, 
 * initializes its fields
 * @return a pointer to the Buffer struct
 */
Buffer *makeBuffer();

/**
 * Adds a single byte to the end of the given buffer
 * and enlarges the data array if necessary
 * @param b the pointer to the buffer 
 * @param byte the byte to add to the buffer
 */
void appendBuffer(Buffer *b, unsigned char byte);

/**
 * Free all the memory for the
 * given buffer
 * @param b a pointer to the buffer to free
 */
void freeBuffer( Buffer *b);

/**
 * Creates a new buffer, reads the contents of the file with the
 * given name, and stores it in the buffer.
 * @param filename the name of the file to read
 * @return the pointer to the buffer read
 */
Buffer *readFile( const char *filename);