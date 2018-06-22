/*
 * esp8266_at_cmds.h
 *
 *  Created on: 26 mars 2018
 *      Author: swhx7055
 */

#ifndef ESP8266_INCLUDE_ESP8266_H_
#define ESP8266_INCLUDE_ESP8266_H_

// ESP8266 reset
#define ESP8266_HARD_RESET_PIN	GALILEO_GEN2_IO_4

// ESP8266
#define ESP8266_SEND_BUFFER_MAX_SIZE					2048 							// bytes
#define ESP8266_RCV_HEADER_MIN_SIZE						9								// bytes
#define ESP8266_RCV_HEADER_MAX_SIZE						12								// bytes
#define ESP8266_RCV_PAYLOAD_MAX_SIZE					4096							// bytes
#define ESP8266_AT_TCP_SRV_TIMEOUT						0 								// server never timeout

// ESP2866 USED AT commands
#define ESP8266_AT_SOFT_RESTART							"AT+RST\r\n"
#define ESP8266_AT_TEST_COMM							"AT\r\n"
#define ESP8266_AT_DISABLE_ECHOING	 					"ATE0\r\n"
#define ESP8266_AT_GET_CONN_STATUS						"AT+CIPSTATUS\r\n"
#define ESP8266_AT_DISABLE_TRANSPARENT_TRANS 			"AT+CIPMODE=0\r\n"				// mandatory to activate multiple connections
#define ESP8266_AT_ENABLE_MULTI_CONN					"AT+CIPMUX=1\r\n"				// mandatory to create TCP server
#define ESP8266_AT_SET_MAX_CONN_TO_ONE					"AT+CIPSERVERMAXCONN=1\r\n"		// must be called before server creation # range between 1 and 5 connections
#define ESP8266_AT_CREATE_TCP_SRV_PORT_8080				"AT+CIPSERVER=1,8080\r\n"
#define ESP8266_AT_SET_TCP_SRV_TIMEOUT_180				"AT+CIPSTO=180\r\n"				// value in seconds
#define ESP8266_AT_SET_TCP_SRV_TIMEOUT_NEVER			"AT+CIPSTO=0\r\n"				// never timeout
#define ESP8266_AT_HIDE_REMOTE_IP_PORT					"AT+CIPDINFO=0\r\n"				// Hide the remote IP and Port with +IPD
#define ESP8266_AT_SEND_DATA_LINK0_PREFIX				"AT+CIPSEND=0,"					// link (0~4),length (MAX 2048 bytes)

// ESP8266 success debugging printable messages
#define ESP8266_DEBUG_SUCCESS_OK_RECEIVED				"ESP8266 returns OK!\r\n"

// ESP8266 error debugging printable messages
#define ESP8266_DEBUG_ERROR_OK_MISSING					"ESP8266 doesn't return OK!\r\n"
#define ESP8266_DEBUG_ERROR_NO_VALID_VALUE				"ESP8266 doesn't return a valid value!\r\n"

#define BUFFER_SIZE			100

int esp8266_response_contains(const char *response, const char *contain);

void esp8266_init_reset_pin();
void esp8266_hard_reset();

int esp8266_send_tcp_header(int length_int);

#endif /* ESP8266_INCLUDE_ESP8266_H_ */


