/*
 * Temporary file for use only during development when there are no library or
 * header files.
 */


#ifndef STDLIB_H
#define STDLIB_H
#include <stddef.h>


/*
 *  Extremely crude standard library implementations in lieu of having a C
 *  library.
 */
void *mymemset( void *pvDest, int iValue, size_t xBytes );
void *mymemcpy( void *pvDest, const void *pvSource, size_t xBytes );
int mymemcmp( const void *pvMem1, const void *pvMem2, unsigned long ulBytes );

#endif /* STDLIB_H */

