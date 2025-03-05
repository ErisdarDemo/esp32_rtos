/**************************************************************************************************/
/** @file     freertos.c
 *  @brief    Code for freertos applications
 *  @details  x
 *
 *  @section 	Opens
 * 		includes sec header
 *
 *  @note	freertos.c uses main.h as the interface file
 */
/**************************************************************************************************/

//************************************************************************************************//
//                                            INCLUDES                                            //
//************************************************************************************************//

//Standard Library Includes
#include <string.h>
#include <stdio.h>

//RTOS Includes
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"

//Project Includes	
#include "../Rtos/freertos.h"						/* @open 	clean that shit up				  */
#include "../main.h"


//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
//************************************************************************************************//

//-----------------------------------------  Definitions -----------------------------------------//

//Task Definitions
#define SYSTEM_TASK_LOOP_DELAY_CTS		pdMS_TO_TICKS(2500)
#define DATA_TASK_LOOP_DELAY_CTS		pdMS_TO_TICKS(2500)
#define DISPLAY_TASK_LOOP_DELAY_CTS		pdMS_TO_TICKS(2500)
#define CONTROL_TASK_LOOP_DELAY_CTS		pdMS_TO_TICKS(2500)


//************************************************************************************************//
//                                             OS VARIABLES                                       //
//************************************************************************************************//

//--------------------------------------------- Tasks --------------------------------------------//

//Tasks
//osThreadId_t sysTaskHandle;				    	/* System Operations Task					  */
//osThreadId_t dataTaskHandle;						/* Data Operations Task						  */
//osThreadId_t dispTaskHandle;						/* Console/UI Task							  */
//osThreadId_t ctrlTaskHandle;						/* Control Flow Taslk						  */


//Config
//const osThreadAttr_t sysTask_attributes = {
//  .name       = SYS_TASK_NAME,
//  .stack_size = DFLT_STACK_SIZE,
//  .priority   = (osPriority_t) osPriorityNormal,
//};

//const osThreadAttr_t dataTask_attributes = {
//  .name       = DATA_TASK_NAME,
//  .stack_size = DFLT_STACK_SIZE,
//  .priority   = (osPriority_t) osPriorityLow,
//};

//const osThreadAttr_t dispTask_attributes = {
//  .name       = DISP_TASK_NAME,
//  .stack_size = DFLT_STACK_SIZE,
//  .priority   = (osPriority_t) osPriorityLow,
//};

//const osThreadAttr_t ctrlTask_attributes = {
//  .name       = CTRL_TASK_NAME,
//  .stack_size = DFLT_STACK_SIZE,
//  .priority   = (osPriority_t) osPriorityLow,
//};


//-------------------------------------------- Timers --------------------------------------------//

//Timers
//osTimerId_t osTimerHandle;							/* Sample FreeRTOS Timer					  */

//Config
//const osTimerAttr_t osTimer_attributes = {
//  .name = OS_TIMER_NAME
//};


//------------------------------------------- Mutexes --------------------------------------------//

//Mutexes
//osMutexId_t dataMutexHandle;						/* Sample FreeRTOS Mutex					  */

//Config
//const osMutexAttr_t dataMutex_attributes = {
//  .name = DATA_MUTEX_NAME
//};


//------------------------------------------ Semaphores -------------------------------------------//

//Semaphores
//osSemaphoreId_t ctrlSemHandle;						/* Sample FreeRTOS Binary Semaphore		 	 */
//osSemaphoreId_t cntrSemHandle;						/* Sample FreeRTOS Counting Semaphore		 */

//Config
//const osSemaphoreAttr_t ctrlSem_attributes = {
//  .name = CTRL_SEM_NAME
//};

//const osSemaphoreAttr_t cntrSem_attributes = {
//  .name = CNTR_SEM_NAME
//};


//-------------------------------------------- Events --------------------------------------------//

//Events
//osEventFlagsId_t dataStoreHandle;					/* @Sample FreeRTOS Event					  */

//Config
//const osEventFlagsAttr_t dataStore_attributes = {
//  .name = DATA_EVENT_NAME
//};


//************************************************************************************************//
//                                          PUBLIC FUNCTIONS                                      //
//************************************************************************************************//

/**************************************************************************************************/
/** @fcn        void sysTask(void *argument)
 *  @brief      Function implementing the sysTask thread.
 *  @details    GPIO & UART demos
 *
 *  @param    [in]  (void *) argument - x
 *
 *  @section 	WDT Refresh
 *  	Update counter value to !127, the refresh window is between
 *  	!35 ms (!~728 * (!127-!80)) and !46 ms (!~728 * !64)
 */
/**************************************************************************************************/
void sysTask(void *argument) {

	//Locals
#ifdef USES_STM32
	HAL_StatusTypeDef stat = HAL_ERROR;				/* status of HAL operations for review 		  */
#endif

	//Loop
	for(;;) {

		//Notify
		printf("Calling System Task\n\r");

		//Wiggle
	    //@open

		//Refresh
		//@open refresh WDT

		//Console Sync
		printf("\n");
		
		//Delay
		vTaskDelay(SYSTEM_TASK_LOOP_DELAY_CTS);
		
	}
}


/**************************************************************************************************/
/** @fcn        void dataTask(void *argument)
 *  @brief      Function implementing the dataTask thread.
 *  @details    Timer demo
 *
 *  @param    [in]  (void *) argument - x
 */
/**************************************************************************************************/
void dataTask(void *argument) {

	//Locals
	uint32_t timer_val     = 0; 					/* time check value 						  */
	char buff[100]         = {0};					/* print buffer								  */
	static int devTimerVal = 0;						/* temp for dev							      */

	//Init
	memset(&buff, 0x00, sizeof(buff));

	//Loop
	for(;;) {

		//Notify
		printf("Calling Data Task\n\r");

		//Latch
		timer_val = devTimerVal++;					/* @open grab timer value					  */

		//Print
		printf("Timer: 0x%"PRIu32"\n", timer_val);
		
		//Console Sync
		printf("\n");

		//Delay
		vTaskDelay(DATA_TASK_LOOP_DELAY_CTS);
	}
}


/**************************************************************************************************/
/** @fcn        void dispTask(void *argument)
 *  @brief      Function implementing the dispTask thread.
 *  @details    Semaphore demo
 *
 *  @param    [in]  (void *) argument - x
 */
/**************************************************************************************************/
void dispTask(void *argument) {

	//Loop
	for(;;) {

		//Notify
		printf("\n\nCalling Disp Task\n\n");
        
        if(print_real_time_stats(STATS_TICKS) == ESP_OK) {
			
            printf("Real time stats obtained\n");
            
        } else {
			
            printf("Error getting real time stats\n");
            
        }		
		
		//Console Sync
		printf("\n");
		
		//Delay
		vTaskDelay(DISPLAY_TASK_LOOP_DELAY_CTS);
	}
}


/**************************************************************************************************/
/** @fcn        void ctrlTask(void *argument)
 *  @brief      Function implementing the ctrlTask thread.
 *  @details    x
 *
 *  @param    [in]  (void *) argument - x
 *
 *  @section 	Opens
 *      Turn off input name recommendations
 */
/**************************************************************************************************/
void ctrlTask(void *argument) {

	//Loop
	for(;;) {

		//Notify
		printf("Calling Control Task\n\r");
		
		
		//Console Sync
		printf("\n");

		//Delay
		vTaskDelay(DISPLAY_TASK_LOOP_DELAY_CTS);
	}
}


/**************************************************************************************************/
/** @fcn        void osTimer_Callback(void *argument)
 *  @brief      osTimer_Callback function
 *  @details    x
 *
 *  @param    [in]  (void *) argument - x
 *
 *  @section 	Opens
 *  	Prints notice
 */
/**************************************************************************************************/
void osTimer_Callback(void *argument) {
	return;
}

