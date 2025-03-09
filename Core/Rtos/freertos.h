#ifndef CORE_RTOS_FREERTOS_H_
#define CORE_RTOS_FREERTOS_H_

//************************************************************************************************//
//                                            INCLUDES                                            //
//************************************************************************************************//

//RTOS Includes
#ifdef MAYBE
	#include "freertos/FreeRTOS.h"
	#include "freertos/FreeRTOSConfig.h"
	#include "freertos/task.h"
#endif


//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
// @open 	group task defs to a structure														  //
//************************************************************************************************//

//-----------------------------------------  Definitions -----------------------------------------//

//Task Priority Definitions
#define STAT_TASK_PRIO     	(3)
#define SPIN_TASK_PRIO      (2)
#define SYS_TASK_PRIO		(2)
#define DATA_TASK_PRIO		(2)
#define DISP_TASK_PRIO		(2)
#define CTRL_TASK_PRIO		(2)

//Spin Task Definitions
#define NUM_OF_SPIN_TASKS   (6)
#define SPIN_ITER           (500000)  	/* Actual ct used will depend on compiler optimization	  */
#define STATS_TICKS         pdMS_TO_TICKS(1000)


//************************************************************************************************//
//                                       FUNCTION DECLARATIONS                                    //
//************************************************************************************************//

//Init
extern void rtos_init(void);


#endif /* CORE_RTOS_FREERTOS_H_ */

