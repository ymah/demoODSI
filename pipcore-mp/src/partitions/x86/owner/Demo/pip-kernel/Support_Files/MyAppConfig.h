/*
 * MyAppConfig.h
 *
 *  Created on: 19 nov. 2017
 *      Author: HZGF0437
 */

#ifndef MYAPPCONFIG_H_
#define MYAPPCONFIG_H_

/* Priorities at which the tasks are created. */
#define	NW_MANAGER_TASK_PRIORITY		    ( tskIDLE_PRIORITY + 1 )
#define	IC_MANAGER_TASK_PRIORITY		    ( tskIDLE_PRIORITY + 2 )
#define TOKEN_VALIDATE_TASK_PRIORITY		( tskIDLE_PRIORITY + 3 )
#define ADMIN_MANAGER_TASK_PRIORITY         ( tskIDLE_PRIORITY + 4 )
#define CONFIG_MANAGER_TASK_PRIORITY        ( tskIDLE_PRIORITY + 5 )
#define KEY_MANAGER_TASK_PRIORITY           ( tskIDLE_PRIORITY + 6 )

/* The rate at which data is sent to the queue.  The 2000ms value is converted
to ticks using the portTICK_PERIOD_MS constant. */
#define NW_MANAGER_SEND_FREQUENCY_MS			( 2000 / portTICK_PERIOD_MS )

/* The number of items the queue can hold.  This is 1 as the receive task
will remove items as they are added, meaning the send task should always find
the queue empty. */
#define mainQUEUE_LENGTH					( 1 )


/* Domain & partition details*/
#define DOM_ID_OWNER                          ( "O1\0" )
#define DOM_ID_UPDATE                         ( "O2\0" )
#define NB_CHILD_DOM_DEFAULT                  ( 0 )


/*Key details*/
#define TOKEN_KEY_ID                         ( "Key1\0" )
#define TOKEN_KEY                            ( "17\0" )

#define DEFAULT_BUFLEN 512
#define DEFAULT_IP NULL
#define DEFAULT_PORT "1337"

#endif /* MYAPPCONFIG_H_ */
