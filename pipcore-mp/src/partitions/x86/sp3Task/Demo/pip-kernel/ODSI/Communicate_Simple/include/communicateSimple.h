/*
 * communicateSimple.h
 *
 *  Created on: 21 déc. 2017
 *      Author: HZGF0437
 */

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#ifndef COMMUNICATE_SIMPLE_INCLUDE_COMMUNICATESIMPLE_H_
#define COMMUNICATE_SIMPLE_INCLUDE_COMMUNICATESIMPLE_H_

uint32_t receive_simple(char* data, QueueHandle_t xQueue_P2IC);
void send_simple(char* data, QueueHandle_t xQueue_IC2P, uint32_t datasize);

#endif /* COMMUNICATE_SIMPLE_INCLUDE_COMMUNICATESIMPLE_H_ */
