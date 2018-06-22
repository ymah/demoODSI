/*
 * communicate_Simple.h
 *
 *  Created on: 21 déc. 2017
 *      Author: HZGF0437
 */

#include "stdint.h"
/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#ifndef CLIENT_SIMPLE_INCLUDE_COMMUNICATE_SIMPLE_H_
#define CLIENT_SIMPLE_INCLUDE_COMMUNICATE_SIMPLE_H_

receive(char*  data, QueueHandle_t xQueue_P2IC);

send (char* data, uint32_t dest, QueueHandle_t xQueue_IC2P);


#endif /* CLIENT_SIMPLE_INCLUDE_COMMUNICATE_SIMPLE_H_ */
