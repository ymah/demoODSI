/*
 * esp8266.c
 *
 *  Created on: 23 avr. 2018
 *      Author: swhx7055
 */

#include "Galileo_Gen2_Board.h"
#include <Quark_x1000_support.h>
#include <esp8266.h>
#include <string.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/*
 * returns 1 if the beginning of response is equal to contain
 */
int esp8266_response_contains(const char *response, const char *contain)
{
	int ret = 0;

	char response_cpy[BUFFER_SIZE]; // buffer to copie the response
	unsigned long contain_size = strlen(contain); // get the size of the wanted string

	// mettre le buffer � zero
	memset(response_cpy, 0, sizeof(response_cpy));

	// test if the size of response_cpy "BUFFER_SIZE" is bigger than the size of "contain"
	if(sizeof(response_cpy) > contain_size)
	{
		unsigned int i = 0;
		while( (response[i] == '\n' || response[i] == '\r') && i < contain_size)
		{
			i++;
		}
		// copy response in response _cpy
		memcpy(response_cpy, &(response[i]), contain_size);
		// write '\0' at the end of response_cpy
		response_cpy[contain_size] = '\0';
		// test if response contains contain

		printf("[Network Manager][response contains] %s %d\r\n", response_cpy, contain_size);

		if(memcmp(response_cpy, contain, contain_size) == 0)
		{
			ret = 1;
		}
	}

	return ret;
}

/*
 * init reset pin
 * set pin as output and deactivate reset
 */
void esp8266_init_reset_pin()
{
	Galileo_Gen2_Set_IO_Direction(ESP8266_HARD_RESET_PIN, GPIO_OUTPUT);
	Galileo_Gen2_Set_IO_Level(ESP8266_HARD_RESET_PIN, HIGH);
}

/*
 * hard reset esp8266
 */
void esp8266_hard_reset()
{
	//  Block for 500ms.
	printf("Reset ESP8266\r\n");

	const TickType_t xDelay = 500;
	printf("Reset Low\r\n");
	Galileo_Gen2_Set_IO_Level(ESP8266_HARD_RESET_PIN, LOW);
	vTaskDelay_ms( xDelay );
	printf("Reset high\r\n");
	Galileo_Gen2_Set_IO_Level(ESP8266_HARD_RESET_PIN, HIGH);
	vTaskDelay_ms( xDelay );
	printf("Finished reset ESP8266\r\n");
}

/*
 * sends the tcp header
 * @param length_int 2048 max
 *
 * returns 1 if succeeded.
 */
int esp8266_send_tcp_header(int length_int)
{
	int ret = 0;
	char rcv_buf[20];
	char length_string[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	char header_string[20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	// test if length_int is less than the send max size and bigger than 0
	if( (length_int < 1) || (length_int > ESP8266_SEND_BUFFER_MAX_SIZE) )
	{
		return ret;
	}

	// mettre le buffer � zero
	memset(rcv_buf, 0, sizeof(rcv_buf));

	// convert tcp paylaod length from int to string
	itoa(length_int, length_string, 10);
	// copy the header prefix in the header string
	strcpy(header_string, ESP8266_AT_SEND_DATA_LINK0_PREFIX);
	// concatenate the header with the length string
	strcat(header_string, length_string);
	// send the header
	vGalileo_UART0_write(header_string, strlen(header_string));
	vGalileo_UART0_write("\r\n", 2);

	const TickType_t xDelay_1_ms = 1;
	vTaskDelay_ms( xDelay_1_ms );

	ret = 1;

	return ret;
}
