#include <stdlib.h>

#ifndef _SHA1_H_
#define _SHA1_H_

#include "buffer.h"

/* Mechanism to conditionally expose static functions to other components.  For
   production, we can make make them static, but for testing we can disable
   the static keyword and expose functions to the test driver. */
#ifdef TESTABLE
#define test_static
#else
#define test_static static
#endif

/** Number of bytes in a block used in the SHA1 calculation. */
#define SHA1_BLOCK 64

/** Number of bytes in an SHA1 digest */
#define SHA1_DIGEST 20

/** Representation for the state of the SHA1 computation.  It's just 5
    unsigned 32-bit integers. Client code can create an instance
    (statically, on the stack or on the heap), but initState() needs
    to initialize it before it can be used. */
typedef struct {
  /** Fields h0 through h4 of the SHA1 state.  */
  unsigned int h0;
  unsigned int h1;
  unsigned int h2;
  unsigned int h3;
  unsigned int h4;
} SHA1State;

#endif

/**
 * Intializes the fields of a SHA1State with the 5 constants in the SHA1 algorithm
 * @param state the pointer to the SHA1State
 */ 
void initState( SHA1State *state );

/**
 * Pads the given buffer, bringing its length to a multiple of 64 bytes
 * and adding byte values as described in the SHA1 algorithm
 * @param b the buffer to pad
 */
void padBuffer( Buffer *b);

/**
 * Performs 80 SHA1 iterations on the given block of bytes,
 * updating the given state.
 * @param data the block of bytes
 * @param state the given SHA1 state
 */
void sha1Block( unsigned char data[ SHA1_BLOCK ], SHA1State *state );

/**
 * Used to create the digest. Trasnfer 20 bytes inthe h0, h1, h2, h3, h4
 * state variable into a 20 byte unsigned char array, in big-endian order.
 *@param digest the digest value to add to
 * @param state the SHA1 state.
 */
void sha1Encode( unsigned char digest[ SHA1_DIGEST ], SHA1State *state);