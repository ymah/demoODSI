/*
 * NWManager_Interface.h
 *
 *  Created on: 18 déc. 2017
 *      Author: HZGF0437
 */


#ifndef NWMANAGER_INCLUDE_NWMANAGER_INTERFACE_H_
#define NWMANAGER_INCLUDE_NWMANAGER_INTERFACE_H_

/* Kernel includes. */
#include "stdint.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/**
 * Initializes ListenSocket with TCP/IP address & port
 * @return ListenSocket
 */
void* initialize();

/**
 * Listens to socket
 * @param LSocket
 * @return status code
 */
uint32_t ext_listen( void* LSocket);


/**
 * Receives a connection on the ListenSocket and sends back a ConnectionSocket from which the data can be retrieved
 * @param ListenSocket
 * @return ConnectionSocket
 */
void* get_connection(void* ListenSocket);

/**
 * Send data to the ClientSocket
 * @param ClientSocket
 * @param outData
 * @param size
 */
void ext_send(void* ClientSocket, char* outData, uint32_t size);

/**
 * Receive until the peer shuts down the connection
 * @param ClientSocket
 * @param data
 * @return
 */
uint32_t ext_receive(void* ClientSocket, char* data);

/**
 * Close the socket
 * @param Socket Socket to be closed
 */
void mycloseSocket(void* Socket);

/*
 * Check if "+IPD," is sent from esp8266 over serial communication
 * This function consumes the comma ',' after "+IPD"
 *
 * @returns 1 if "+IPD," is received
 */
int esp8266_check_IPD_reception(char *rcv_buf);

/*
 * Attempts to read TCP header
 *
 * @param header point to an array of 12 bytes minimum in order to hold the header
 * @return the payload size of tcp segment
 */
unsigned int esp8266_get_tcp_header(char *header);

/*
 * attempts to get tcp payload of the received tcp segment from the ESP8266 module
 *
 * @param (out) payload point to an array in order to hold the payload
 * @param (in) payload size
 * @return payload size
 */
int esp8266_get_tcp_payload(unsigned int payload_size);

uint32_t try_to_send_tcp_header();
void send_tcp_payload(uint32_t size);
void remove_tcp_payload_from_send_fifo(uint32_t size);

#endif /* NWMANAGER_INCLUDE_NWMANAGER_INTERFACE_H_ */
