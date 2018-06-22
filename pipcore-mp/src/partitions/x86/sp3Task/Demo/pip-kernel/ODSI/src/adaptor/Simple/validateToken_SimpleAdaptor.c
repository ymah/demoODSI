/*
 * validateToken_Interface.c
 *
 *  Created on: 19 nov. 2017
 *      Author: HZGF0437
 */

/*-----------------------------------------------------------*/

/* Standard includes. */
#include "validateToken_Interface.h"
#include "string.h"
#include "stdint.h"

/* Kernel includes. */

/*-----------------------------------------------------------*/

char token_validate(char* token, char* key){
	uint32_t ikey;
	ikey=atoi(key);
	return token_validate_simple(token, ikey);
}

/*-----------------------------------------------------------*/
