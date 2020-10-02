/**
 * Removes lines from global array.
 * @param start the starting line to remove
 * @param end the ending line to remove
 */
void removeLines( int start, int end );

/**
 * Edits a single line of the global array by cutting out a portion of
 * its contents
 * @param lno the index of the line
 * @param start the starting column to remove
 * @param end the ending column to remove
 */
void editLine( int lno, int start, int end );

/**
 * Removes columns from the global array
 * @param start the starting column to remove
 * @param end the ending column to remove
 */
void removeCols( int start, int end );
