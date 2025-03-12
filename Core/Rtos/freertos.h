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

//-----------------------------------------  Definitions -----------------------------------------//

//Task Priority Definitions
#define STAT_TASK_PRIO     	(3)
#define SPIN_TASK_PRIO      (2)
#define SYS_TASK_PRIO		(4)
#define DATA_TASK_PRIO		(4)
#define DISP_TASK_PRIO		(4)
#define CTRL_TASK_PRIO		(4)
#define UART_TASK_PRIO		(4)

//Spin Task Definitions
#define NUM_OF_SPIN_TASKS   (6)
#define SPIN_ITER           (500000)				/* sourced from stats task rate			      */
#define STATS_TICKS         pdMS_TO_TICKS(1000)

//Timing Definitions
#define RTOS_BOOT_DELAY_MS	(100)

//Stack Definitions
#define SYS_STACK_DEPTH 	(4096)
#define DATA_STACK_DEPTH 	(4096)
#define DISP_STACK_DEPTH 	(4096)
#define CTRL_STACK_DEPTH 	(4096)
#define UART_STACK_DEPTH 	(4096)


//************************************************************************************************//
//                                            VARIABLES                                           //
//************************************************************************************************//

//RTOS Variables
extern BaseType_t uartTaskHandle;


//************************************************************************************************//
//                                       FUNCTION DECLARATIONS                                    //
//************************************************************************************************//

//Init
extern void rtos_init(void);


#endif /* CORE_RTOS_FREERTOS_H_ */

