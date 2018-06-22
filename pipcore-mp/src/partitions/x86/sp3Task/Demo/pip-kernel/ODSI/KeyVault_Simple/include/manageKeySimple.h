/*
 * manageKeySimple.h
 *
 *  Created on: 24 nov. 2017
 *      Author: hzgf0437
 */

#ifndef INCLUDE_PORTABLE_MANAGEKEYSIMPLE_H_
#define INCLUDE_PORTABLE_MANAGEKEYSIMPLE_H_

#include "CommonStructure.h"
#include "stdint.h"
//l_key is the pointer to the chained list of keys
// keyID

key_t* createKey(char* keyID, char* keyValue);
uint32_t addKey(key_t** l_key, char* keyID, char* keyValue);
uint32_t readKey(key_t* l_key, char* key_ID, char* keyValue);
uint32_t updateKey(key_t* l_key, char* key_ID, char* keyValue);
uint32_t deleteKey(key_t** l_key, char* key_ID);

#endif /* INCLUDE_PORTABLE_MANAGEKEYSIMPLE_H_ */
