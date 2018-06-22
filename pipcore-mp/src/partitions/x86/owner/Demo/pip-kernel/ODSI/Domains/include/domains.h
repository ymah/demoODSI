/*
 * service_providers_domains.h
 *
 *  Created on: 20 avr. 2018
 *      Author: swhx7055
 */

#ifndef DOMAINS_INCLUDE_DOMAINS_H_
#define DOMAINS_INCLUDE_DOMAINS_H_
#include <stdint.h>
#define DEMO_OWNER_DOMAIN_ID							0
#define DEMO_SERVICE_PROVIDER_1_DOMAIN_ID				1
#define DEMO_SERVICE_PROVIDER_2_DOMAIN_ID				2
#define DEMO_SERVICE_PROVIDER_3_DOMAIN_ID				3

void od_Task( uint32_t * pvParameters );
void SP1D_Task( void *pvParameters );
void SP2D_Task( void *pvParameters );
void SP3D_Task( void *pvParameters );

#endif /* DOMAINS_INCLUDE_DOMAINS_H_ */
