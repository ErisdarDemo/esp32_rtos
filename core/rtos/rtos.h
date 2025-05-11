/**************************************************************************************************/
/** @file     rtos.h
 *  @brief    RTOS Interface File
 *  @details  x
 *
 *  @section    Opens
 *      Update to non-blocking clear of semaphore
 *		Consider integration of FreeRTOSConfig.h
 *
 *  @section    Notes
 *      Interface file headers like this are not recommended in preference for the source header
 */
/**************************************************************************************************/
#ifndef CORE_RTOS_RTOS_H_
#define CORE_RTOS_RTOS_H_

//************************************************************************************************//
//                                            INCLUDES                                            //
//************************************************************************************************//

//FreeRTOS Includes
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"


//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
//************************************************************************************************//

//-----------------------------------------  Definitions -----------------------------------------//

//Task Priority Definitions
#define STAT_TASK_PRIO              (3)
#define SYS_TASK_PRIO               (4)
#define DATA_TASK_PRIO              (4)
#define DISP_TASK_PRIO              (4)
#define CTRL_TASK_PRIO              (4)


//-------------------------------------------  Macros --------------------------------------------//

//Semaphores
#define semaphoreWait(semName)      xSemaphoreTake(semName, portMAX_DELAY)
#define semaphoreRelease(semName)   xSemaphoreGive(semName)

#define semaphoreClear(semName)     while(xSemaphoreTake(semName, 0) != pdFAIL);


//-------------------------------------------- Typedefs ------------------------------------------//

typedef struct rtosTaskConfig {
    
    TaskFunction_t pvTaskCode;                      /* Pointer to the task entry function         */
    
    const char *const pcName;                       /* A descriptive name for the task            */
    
    const uint32_t usStackDepth;                    /* Task stack size in bytes                   */
    
    void *const pvParameters;                       /* Param Pointer for the task being created   */
    
    UBaseType_t uxPriority;                         /* The priority at which the task should run  */
    
    TaskHandle_t *const pvCreatedTask;              /* Used to pass back a handle for ref         */
    
    const BaseType_t xCoreID;                       /* Task core affinity                         */

} RtosTaskConfig;


//************************************************************************************************//
//                                       FUNCTION DECLARATIONS                                    //
//************************************************************************************************//

//Init
extern void rtos_init(void);
extern void rtos_stop(void);


#endif /* CORE_RTOS_RTOS_H_ */

