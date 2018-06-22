/*
 * routeCommand_Interface.h
 *
 *  Created on: 20 nov. 2017
 *      Author: hzgf0437
 */

/*FreeRTOS include*/
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#ifndef ROUTECOMMAND_INTERFACE_H_
#define ROUTECOMMAND_INTERFACE_H_

event_t routeCommand(event_t ReceivedValue);
event_t routeCommand_SP1D(event_t ReceivedValue);
event_t routeCommand_SP2D(event_t ReceivedValue);
event_t routeCommand_SP3D(event_t ReceivedValue);

#endif /* ROUTECOMMAND_INTERFACE_H_ */
