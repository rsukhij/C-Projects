
/**
 * Performs the HMAS-SHA1. Takes the key as a string, a pointer to the 
 * input buffer, and pointer to the array that stores the digest. 
 * @param kstr the key string
 * @param b the input buffer 
 * @param digest the array that sotres the digest
 */
void hmacSHA1( char *kstr, Buffer *b, unsigned char digest[ SHA1_DIGEST ]);
