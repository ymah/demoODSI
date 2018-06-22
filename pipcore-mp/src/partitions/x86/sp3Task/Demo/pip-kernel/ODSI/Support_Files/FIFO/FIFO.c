/*
 * FIFO.c
 *
 *  Created on: 2 mai 2018
 *      Author: swhx7055
 */

#include "FIFO.h"
#include "string.h"
#include "stdint.h"

// static functions prototypes
static inline uint32_t fifo_get_write_index(fifo_t *fifo);

/*
 * init fifo struct elements
 */
void fifo_init(fifo_t *fifo)
{
	fifo->index = 0;
	fifo->length = 0;
}

/*
 * push data into fifo if enough space available
 *
 * returns 1 if succeeded
 */
int fifo_push(fifo_t *fifo, char *data, uint32_t size_to_push)
{
	int ret = 0;
	uint32_t available_space = sizeof(fifo->buffer) - fifo->length;
	uint32_t data_index = 0;

	if(available_space < size_to_push)
	{
		return ret;
	}

	uint32_t remaining_bytes_to_push = size_to_push;
	uint32_t write_index = fifo_get_write_index(fifo);

	uint32_t write_index_to_bottom_size = sizeof(fifo->buffer) - write_index;

	if(remaining_bytes_to_push > write_index_to_bottom_size)
	{
		memcpy(&(fifo->buffer[write_index]), &(data[data_index]), write_index_to_bottom_size );
		data_index += write_index_to_bottom_size;
		write_index = 0;
		remaining_bytes_to_push -= write_index_to_bottom_size;
	}

	memcpy(&(fifo->buffer[write_index]), &(data[data_index]), remaining_bytes_to_push );

	// update fifo length
	fifo->length += size_to_push;

	ret = 1;

	return ret;
}

uint32_t fifo_pull(fifo_t *fifo, char *data, uint32_t size_to_pull)
{
	uint32_t data_index = 0;

	if(size_to_pull > fifo->length)
	{
		size_to_pull = fifo->length;
	}

	uint32_t remaining_bytes_to_pull = size_to_pull;

	uint32_t read_index_to_bottom_size = sizeof(fifo->buffer) - fifo->index;

	if(remaining_bytes_to_pull > read_index_to_bottom_size)
	{
		memcpy(&(data[data_index]), &(fifo->buffer[fifo->index]), read_index_to_bottom_size );
		data_index += read_index_to_bottom_size;
		fifo->index = 0;
		remaining_bytes_to_pull -= read_index_to_bottom_size;
	}

	memcpy(&(data[data_index]), &(fifo->buffer[fifo->index]), remaining_bytes_to_pull );

	// update fifo struct
	fifo->length -= size_to_pull;
	fifo->index += remaining_bytes_to_pull;

	return size_to_pull;
}

uint32_t fifo_peek(fifo_t *fifo, char *data, uint32_t size_to_peek)
{
	uint32_t data_index = 0;
	uint32_t fifo_index = fifo->index;

	if(size_to_peek > fifo->length)
	{
		size_to_peek = fifo->length;
	}

	uint32_t remaining_bytes_to_peek = size_to_peek;

	uint32_t read_index_to_bottom_size = sizeof(fifo->buffer) - fifo_index;

	if(remaining_bytes_to_peek > read_index_to_bottom_size)
	{
		memcpy(&(data[data_index]), &(fifo->buffer[fifo_index]), read_index_to_bottom_size );
		data_index += read_index_to_bottom_size;
		fifo_index = 0;
		remaining_bytes_to_peek -= read_index_to_bottom_size;
	}

	memcpy(&(data[data_index]), &(fifo->buffer[fifo_index]), remaining_bytes_to_peek );

	return size_to_peek;
}

inline uint32_t fifo_get_size(fifo_t *fifo)
{
	return sizeof(fifo->buffer);
}

inline uint32_t fifo_get_length(fifo_t *fifo)
{
	return fifo->length;
}

static inline uint32_t fifo_get_write_index(fifo_t *fifo)
{
	uint32_t write_index = fifo->index + fifo->length;

	if(write_index > (sizeof(fifo->buffer) - 1) )
	{
		write_index -= sizeof(fifo->buffer);
	}

	return write_index;
}
