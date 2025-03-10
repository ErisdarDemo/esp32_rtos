/**************************************************************************************************/
/** @file     main.h
 *  @brief    Header for main.c file
 *  @details  This file contains the common defines of the application
 */
/**************************************************************************************************/
#ifndef CORE_MAIN_H_
#define CORE_MAIN_H_

//************************************************************************************************//
//                                           DIRECTIVES                                           //
//************************************************************************************************//

#ifdef __cplusplus
extern "C" {
#endif


//************************************************************************************************//
//                                            INCLUDES                                            //
//************************************************************************************************//

//FreeRTOS Includes
#include "cmsis_os2.h"

//Utility Includes
#include "System/utils.h"

//FreeRTOS Includes
#include "freertos/FreeRTOS.h"


//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
//************************************************************************************************//

//--------------------------------------- RTOS Definitions ---------------------------------------//

//Code Definitions
#define _nop() 				__asm__ __volatile__("NOP")


//Design Specifications
#define DFLT_STACK_SIZE		(128 * 4)				/* @open 	capture meaning of each num		  */

//Task Definitions
#define SYS_TASK_NAME		"sysTask"
#define DATA_TASK_NAME		"dataTask"
#define DISP_TASK_NAME		"dispTask"
#define CTRL_TASK_NAME		"ctrlTask"

//Timer Definitions
#define OS_TIMER_NAME		"osTimer"

//Mutex Definitions
#define  DATA_MUTEX_NAME	"dataMutex"

//Semaphore Definitions
#define CTRL_SEM_NAME		"ctrlSem"
#define CTRL_MAX_CT 		(1)						/* @open  	value descrip					  */
#define CTRL_INIT_CT 		(1)						/* @open  	value descrip					  */

#define CNTR_SEM_NAME		"cntrSem"
#define CNTR_MAX_CT 		(10)					/* @open  	value descrip					  */
#define CNTR_INIT_CT 		(0)						/* @open  	value descrip					  */

//Event Definitions
#define DATA_EVENT_NAME		"dataStore"


//************************************************************************************************//
//                                       FUNCTION DECLARATIONS                                    //
//************************************************************************************************//

//Project
extern esp_err_t print_real_time_stats(TickType_t xTicksToWait);


//------------------------------------------- FreeRTOS -------------------------------------------//

//Task Prototypes
extern void sysTask(void *argument);
extern void dataTask(void *argument);
extern void dispTask(void *argument);
extern void ctrlTask(void *argument);

//Timer Prototypes
extern void osTimer_Callback(void *argument);


//************************************************************************************************//
//                                             VARIABLES                                          //
//************************************************************************************************//

//Tasks
extern osThreadId_t sysTaskHandle;
extern osThreadId_t dataTaskHandle;
extern osThreadId_t dispTaskHandle;
extern osThreadId_t ctrlTaskHandle;

//Attributes
extern const osThreadAttr_t sysTask_attributes;
extern const osThreadAttr_t dataTask_attributes;
extern const osThreadAttr_t dispTask_attributes;
extern const osThreadAttr_t ctrlTask_attributes;

//Timers
extern osTimerId_t osTimerHandle;

//Mutexes
extern osMutexId_t dataMutexHandle;

//Semaphores
extern osSemaphoreId_t ctrlSemHandle;
extern osSemaphoreId_t cntrSemHandle;

//Events
extern osEventFlagsId_t dataStoreHandle;

//Config
extern const osTimerAttr_t osTimer_attributes;
extern const osMutexAttr_t dataMutex_attributes;
extern const osSemaphoreAttr_t ctrlSem_attributes;
extern const osSemaphoreAttr_t cntrSem_attributes;
extern const osEventFlagsAttr_t dataStore_attributes;


//************************************************************************************************//
//                                           DIRECTIVES                                           //
//************************************************************************************************//

#ifdef __cplusplus
}
#endif


#endif /* CORE_MAIN_H_ */
