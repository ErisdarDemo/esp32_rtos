/**************************************************************************************************/
/** @file     main.h
 *  @brief    Header for main.c file
 *  @details  This file contains the common defines of the application
 *
 *	@section 	Opens
 *		magic nums
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

//Utility Includes
#include "System/utils.h"

//FreeRTOS Includes
#include "freertos/FreeRTOS.h"


//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
//************************************************************************************************//

//Code Definitions
#define _nop() 					__asm__ __volatile__("NOP")

//Names
#define APP_TAG					"APP_MAIN"

//Messages
#define APP_MAIN_ABORT_MSG		"app_main() unexpectedly returned and exited"


//************************************************************************************************//
//                                       FUNCTION DECLARATIONS                                    //
//************************************************************************************************//

//Project
extern esp_err_t print_real_time_stats(TickType_t xTicksToWait);


//************************************************************************************************//
//                                             VARIABLES                                          //
//************************************************************************************************//

#ifdef CMSIS_OS2_BUG

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

#endif


//************************************************************************************************//
//                                           DIRECTIVES                                           //
//************************************************************************************************//

#ifdef __cplusplus
}
#endif


#endif /* CORE_MAIN_H_ */
