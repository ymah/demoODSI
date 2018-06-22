/*
 * Debug.h
 *
 *  Created on: 30 nov. 2017
 *      Author: hzgf0437
 */

#include <stdarg.h>
#include <stdarg.h>

#ifndef UTILS_INCLUDE_DEBUG_H_
#define UTILS_INCLUDE_DEBUG_H_

#define CRITICAL 1 // Error output
#define INFO 2 // Information output
#define TRACE 3 //verbose output

#ifndef LOGLEVEL
#define LOGLEVEL TRACE
#endif

#define DEBUG(l,a,...) if (l<=LOGLEVEL){debug1( "[" #l "] [%s:%d]: " a "\r\n", __FILE__, __LINE__, ##__VA_ARGS__ );}

void debug(const char*string);
void debug1(const char *format, ...);


#endif /* UTILS_INCLUDE_DEBUG_H_ */
