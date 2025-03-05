/*
 * freertos.h
 *
 *  Created on: Mar 6, 2025
 *      Author: Justin
 */

#ifndef CORE_RTOS_FREERTOS_H_
#define CORE_RTOS_FREERTOS_H_

//@todo style!!

//Task Definitions
#define NUM_OF_SPIN_TASKS   (6)
#define SPIN_ITER           (500000)  	/* Actual ct used will depend on compiler optimization	  */
#define SPIN_TASK_PRIO      (2)

//Statistic Definitions
#define STATS_TASK_PRIO     (3)
#define STATS_TICKS         pdMS_TO_TICKS(1000)

//Task Priorities
#define SYSTEM_TASK_PRIO	(2)
#define DATA_TASK_PRIO		(2)
#define DISPLAY_TASK_PRIO	(2)
#define CONTROL_TASK_PRIO	(2)


#endif /* CORE_RTOS_FREERTOS_H_ */
