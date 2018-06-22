/*
 * InternalCommunication_Interface.h
 *
 *  Created on: 21 déc. 2017
 *      Author: HZGF0437
 */

/*FreeRTOS include*/
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "stdint.h"

#ifndef SRC_INCLUDE_INTERNALCOMMUNICATION_INTERFACE_H_
#define SRC_INCLUDE_INTERNALCOMMUNICATION_INTERFACE_H_

event_t myreceive(char* data, QueueHandle_t xQueue_P2IC);

void mysend (uint32_t dest, char* data, QueueHandle_t xQueue_IC2P, uint32_t datasize);


#endif /* SRC_INCLUDE_INTERNALCOMMUNICATION_INTERFACE_H_ */
