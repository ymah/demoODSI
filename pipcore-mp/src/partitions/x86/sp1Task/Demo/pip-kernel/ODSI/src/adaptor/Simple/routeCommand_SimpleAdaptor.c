/*
 * routeCommandInterface.c
 *
 *  Created on: 20 nov. 2017
 *      Author: hzgf0437
 */

/*-----------------------------------------------------------*/

/* Standard includes. */

/*MyApp Config include*/
#include "CommonStructure.h"
#include "routeCommand_Interface.h"
#include "routeCommandSimple.h"

/*FreeRTOS include*/
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


/*-----------------------------------------------------------*/

//extern QueueHandle_t xQueue_ConfigManager;/* Queue AdminManager 2 ConfigManager. */


/*-----------------------------------------------------------*/
// TODO use references instead of copy
event_t routeCommand(event_t ReceivedValue)
{
	return routeCommandSimple( ReceivedValue);
}

event_t routeCommand_SP1D(event_t ReceivedValue)
{
	return routeCommandSimple_SP1D( ReceivedValue);
}

event_t routeCommand_SP2D(event_t ReceivedValue)
{
	return routeCommandSimple_SP2D( ReceivedValue);
}

event_t routeCommand_SP3D(event_t ReceivedValue)
{
	return routeCommandSimple_SP3D( ReceivedValue);
}
/*-----------------------------------------------------------*/



