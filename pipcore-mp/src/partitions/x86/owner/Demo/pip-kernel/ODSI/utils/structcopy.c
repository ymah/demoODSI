/*
 * struct_copy.c
 *
 *  Created on: 8 déc. 2017
 *      Author: HZGF0437
 */

#include "structcopy.h"
#include "CommonStructure.h"
#include "string.h"
#include "stdint.h"
#include "mystdlib.h"
#include "string.h"

command_t *commandinit(command_t *dest, char* data, uint32_t ins, uint32_t userID){
	dest->userID= userID;
	strcpy(dest->data, data);
	dest->instruction=ins;
	return dest;
}

command_t *commandcpy(command_t *dest, command_t *src){
	dest->userID=src->userID;
	strcpy(dest->data,src->data);
	dest->instruction=src->instruction;

	return dest;
}

command_t *commandreset(command_t* dest){
	dest->userID = 0;
	mymemset(dest->data, 0, DATA_SIZE);
	dest->instruction=0;
	return dest;
}

incomingMessage_t *incomingMessageinit(incomingMessage_t *dest, uint32_t userID, uint32_t deviceID, uint32_t domainID, uint32_t tokenSize, char* token, char* data, uint32_t ins){
	dest->userID = userID;
	dest->deviceID = deviceID;
	dest->domainID = domainID;
	dest->tokenSize = tokenSize;
	mymemcpy(dest->token, token, TOKEN_SIZE);
	commandinit(&dest->command, data, ins, userID);

	return dest;
}

incomingMessage_t *incomingMessagecpy(incomingMessage_t *dest, incomingMessage_t *src){
	dest->userID=src->userID;
	dest->deviceID=src->deviceID;
	dest->domainID =src->domainID;
	dest->tokenSize = src->tokenSize;
	mymemcpy(dest->token,src->token, TOKEN_SIZE);
	commandcpy(&dest->command, &src->command);

	return dest;
}

incomingMessage_t *incomingMessagereset(incomingMessage_t *dest){
	dest->userID=0;
	dest->deviceID = 0;
	dest->domainID = 0;
	dest->tokenSize = 0;
	mymemset(dest->token, 0, TOKEN_SIZE);
	commandreset(&dest->command);
	return dest;
}

response_t* responseinit(response_t *dest, int responsecode, char* data, uint32_t userID){
	dest->responsecode=responsecode;
	mymemcpy(dest->data,data, DATA_SIZE);
	dest->userID= userID;
	return dest;
}

response_t* responsecpy(response_t *dest, response_t *src){
	dest->responsecode=src->responsecode;
	strcpy(dest->data,src->data);
	dest->userID=src->userID;
	return dest;
}

response_t* responsereset(response_t *dest){
	dest->responsecode=0XFF;
	strcpy(dest->data,"\0");
	dest->userID=0;
	return dest;
}

event_t * eventcpy(event_t *dest, event_t *src){
	dest->eventType=src->eventType;
	commandcpy(&dest->eventData.command,&src->eventData.command);
	incomingMessagecpy(&dest->eventData.incomingMessage,&src->eventData.incomingMessage);
	responsecpy(&dest->eventData.response,&src->eventData.response);
	strcpy(dest->eventData.nw.stream, src->eventData.nw.stream);
	return dest;
}

event_t * eventreset(event_t *dest){
	dest->eventType=0xFF;
	commandreset(&dest->eventData.command);
	incomingMessagereset(&dest->eventData.incomingMessage);
	responsereset(&dest->eventData.response);
	strcpy(dest->eventData.nw.stream,"\0");
	return dest;
}
