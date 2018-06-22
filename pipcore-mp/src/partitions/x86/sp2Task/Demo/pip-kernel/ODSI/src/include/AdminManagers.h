/*
 * AdminManagers.h
 *
 *  Created on: 19 nov. 2017
 *      Author: HZGF0437
 */

#ifndef ADMINMANAGER_H_
#define ADMINMANAGER_H_

#include "CommonStructure.h"

event_t AdminManagerFunction( event_t ReceivedEvent );
event_t AdminManager_SP1D_Function( event_t ReceivedEvent );
event_t AdminManager_SP2D_Function( event_t ReceivedEvent );
event_t AdminManager_SP3D_Function( event_t ReceivedEvent );

#endif /* ADMINMANAGER_H_ */
