/*
 * validateTokenSimple.c
 *
 *  Created on: 19 nov. 2017
 *      Author: HZGF0437
 */

#include "stdint.h"

/*-----------------------------------------------------------*/

char token_validate_simple(char* token, uint32_t n)
{
    char result=2;
    char mask=1;
    uint32_t i=0;

    while(token[i]!=0 && (i+1)*sizeof(char)*8<n){
        i++;
    }

    if (token[i]!=0){
        /*printf("i=%d ; res=%d\n", i, token[i]);*/
        mask <<= (n-1)%8;
        /*printf("mask=%d \n",mask);*/
        result = token[i] & mask;
        result >>= (n-1)%8;
    }

    /*printf("end while, i=%d, result=%d \n", i, token[i]);*/
    return result;
}
