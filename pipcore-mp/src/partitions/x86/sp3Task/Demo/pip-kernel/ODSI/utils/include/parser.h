/*
 * parser.h
 *
 *  Created on: 14 déc. 2017
 *      Author: hzgf0437
 */

#include "CommonStructure.h"
#include "mystdlib.h"

#ifndef UTILS_INCLUDE_PARSER_H_
#define UTILS_INCLUDE_PARSER_H_

/**
 * convert value from host byte order to network byte order
 * @param hostlong uint32_t in host byte order
 * @return uint32_t in network by order
 */
uint32_t myhtonl(uint32_t hostlong);

/**
 * convert value from network byte order to host byte order
 * @param netlong uint32_t in network byte order
 * @return uint32_t in host byte order
 */
uint32_t myntohl(uint32_t netlong);

/**
 * Serialize the structure incomingMessage to a stream ready to be sent to network
 * @param message
 * @param data
 * @return size of stream
 */
uint32_t serialize_incomingMessage(incomingMessage_t message, char* data);

/**
 * Deserialize the stream from network to incomingMessage
 * @param data
 * @return incomingMessage
 */
incomingMessage_t deserialize_incomingMessage(char* data, uint32_t size_total);

/**
 * Deserialize the structure response_t to a stream ready to be sent to network
 * @param response
 * @param data
 * @param size
 * @return size of stream to sent on network
 */
uint32_t serialize_response(response_t response, char* data);
/**
 * Deserialize the stream received from network to a response_t
 * @param data
 * @return response in response_t structure
 */
response_t deserialize_response(char* data, uint32_t size_total);

#endif /* UTILS_INCLUDE_PARSER_H_ */
