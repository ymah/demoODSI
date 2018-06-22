/*
 * FIFO.h
 *
 *  Created on: 2 mai 2018
 *      Author: swhx7055
 */

#ifndef SUPPORT_FILES_FIFO_INCLUDE_FIFO_H_
#define SUPPORT_FILES_FIFO_INCLUDE_FIFO_H_

#include "stdint.h"

#define FIFO_BUFFER_SIZE			4096

typedef struct FIFO fifo_t;

struct FIFO
{
	uint32_t index;
	uint32_t length;
	char buffer[FIFO_BUFFER_SIZE];
};

void fifo_init(fifo_t *fifo);
int fifo_push(fifo_t *fifo, char *data, uint32_t size_to_push);
uint32_t fifo_pull(fifo_t *fifo, char *data, uint32_t size_to_pull);
uint32_t fifo_peek(fifo_t *fifo, char *data, uint32_t size_to_pull);
uint32_t fifo_get_size(fifo_t *fifo);
uint32_t fifo_get_length(fifo_t *fifo);

#endif /* SUPPORT_FILES_FIFO_INCLUDE_FIFO_H_ */
