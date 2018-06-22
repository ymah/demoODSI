/*
 * structcopy.h
 *
 *  Created on: 8 déc. 2017
 *      Author: HZGF0437
 */

#include "CommonStructure.h"
#include "stdint.h"

#ifndef UTILS_INCLUDE_STRUCTCOPY_H_
#define UTILS_INCLUDE_STRUCTCOPY_H_

command_t *commandinit(command_t *dest, char* data, uint32_t ins, uint32_t userID);
command_t *commandcpy(command_t *dest, command_t *src);
command_t *commandreset(command_t* dest);

incomingMessage_t *incomingMessagecpy(incomingMessage_t *dest, incomingMessage_t *src);
incomingMessage_t *incomingMessagereset(incomingMessage_t *dest);
incomingMessage_t *incomingMessageinit(incomingMessage_t *dest, uint32_t userID, uint32_t deviceID, uint32_t domainID, uint32_t tokenSize, char* token, char* data, uint32_t ins);

response_t * responsecpy(response_t *dest, response_t *src);
response_t* responsereset(response_t *dest);

event_t* eventcpy(event_t *dest, event_t *src);
event_t* eventreset(event_t *dest);

#endif /* UTILS_INCLUDE_STRUCTCOPY_H_ */
