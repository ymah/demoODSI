/*
 * routeCommandSimple.h
 *
 *  Created on: 20 nov. 2017
 *      Author: hzgf0437
 */

/*FreeRTOS include*/
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "stdint.h"

#ifndef ROUTECOMMANDSIMPLE_H_
#define ROUTECOMMANDSIMPLE_H_

event_t routeCommandSimple(event_t ReceivedValue);
event_t routeCommandSimple_SP1D(event_t ReceivedValue);
event_t routeCommandSimple_SP2D(event_t ReceivedValue);
event_t routeCommandSimple_SP3D(event_t ReceivedValue);

#endif /* ROUTECOMMANDSIMPLE_H_ */
