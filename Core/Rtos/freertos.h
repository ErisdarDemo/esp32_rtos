#ifndef CORE_RTOS_FREERTOS_H_
#define CORE_RTOS_FREERTOS_H_

//************************************************************************************************//
//                                            INCLUDES                                            //
//************************************************************************************************//

//FreeRTOS Includes
#include "freertos/task.h"


//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
//************************************************************************************************//

//--------------------------------------- Task Definitions ---------------------------------------//

//Task Names
#define SPIN_TASK_NAME			"spin"
#define STATS_TASK_NAME			"stats"
#define SYS_TASK_NAME			"system"
#define DATA_TASK_NAME			"data"
#define TASK_TASK_NAME			"display"
#define CTRL_TASK_NAME			"control"
#define TIMER_TASK_NAME			"timer"
#define UART_TASK_NAME			"uart"


//Task Priority Definitions
#define STAT_TASK_PRIO     		(3)
#define SPIN_TASK_PRIO      	(2)
#define SYS_TASK_PRIO			(4)
#define DATA_TASK_PRIO			(4)
#define DISP_TASK_PRIO			(4)
#define CTRL_TASK_PRIO			(4)
#define TIMER_TASK_PRIO			(4)
#define UART_TASK_PRIO			(4)

//Task Stack Definitions							(8192 kB)
#define SPIN_TASK_DEPTH 		(1024)				/* bytes 									  */
#define STATS_TASK_DEPTH 		(4096)				/* plenty of room							  */
#define SYS_STACK_DEPTH 		(4096)
#define DATA_STACK_DEPTH 		(4096)
#define DISP_STACK_DEPTH 		(4096)
#define CTRL_STACK_DEPTH 		(4096)
#define TIMER_STACK_DEPTH		(4096)
#define UART_STACK_DEPTH 		(4096)


//------------------------------------- Semaphore Definitions ------------------------------------//

//Mutex Definitions
#define  DATA_MUTEX_NAME		"dataMutex"

//Semaphore Definitions
#define CTRL_SEM_NAME			"ctrlSem"
#define CTRL_MAX_CT 			(1)					/* Binary counter							  */
#define CTRL_INIT_CT 			(1)					/* Init taken (not available)				  */

#define CNTR_SEM_NAME			"cntrSem"
#define CNTR_MAX_CT 			(10)				/* Counting Semaphore						  */
#define CNTR_INIT_CT 			(0)					/* Init empty (available)					  */


//--------------------------------------- Event Definitions --------------------------------------//

//Event Definitions
#define DATA_EVENT_NAME			"dataStore"


//----------------------------------------- Definitions ------------------------------------------//

//Timing Definitions
#define RTOS_BOOT_DELAY_MS		(100)
#define UART_THREAD_DELAY_CTS 	(pdMS_TO_TICKS(2000))
#define TIMER_THREAD_DELAY_CTS 	(pdMS_TO_TICKS(2000))
#define PRINT_STATS_DELAY_CTS	(pdMS_TO_TICKS(1000))

//Spin Task Definitions
#define NUM_OF_SPIN_TASKS   	(6)					/* # independent spin tasks created			  */
#define SPIN_ITER           	(500000)			/* sourced from stats task rate			      */


//************************************************************************************************//
//                                            VARIABLES                                           //
//************************************************************************************************//

//RTOS Variables
extern BaseType_t timerTaskHandle;
extern BaseType_t uartTaskHandle;


//************************************************************************************************//
//                                       FUNCTION DECLARATIONS                                    //
//************************************************************************************************//

//Init
extern void rtos_init(void);


#endif /* CORE_RTOS_FREERTOS_H_ */

