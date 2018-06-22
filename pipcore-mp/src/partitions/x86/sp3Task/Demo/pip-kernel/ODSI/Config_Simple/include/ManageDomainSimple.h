/*
 * ManageDomain_Simple.h
 *
 *  Created on: 20 nov. 2017
 *      Author: hzgf0437
 */

#ifndef MANAGEDOMAIN_SIMPLE_H_
#define MANAGEDOMAIN_SIMPLE_H_

#include "CommonStructure.h"
#include "stdint.h"

uint32_t createDomain();
uint32_t readDomID(domain_t *dom, char* domID);
uint32_t updateDomID(domain_t *dom, char* domId);
uint32_t nbDomChild(domain_t *dom);

#endif /* MANAGEDOMAIN_SIMPLE_H_ */
