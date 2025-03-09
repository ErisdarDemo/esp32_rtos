/**************************************************************************************************/
/** @file     freertos.c
 *  @brief    Code for freertos applications
 *  @details  x
 *
 *  @section 	Opens
 * 		includes sec header
 *		unused-includes bug?
 *		switch to cmsis_os2 cleaner api for fcn calls
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

//Timing Definitions
#define MAGIC_NUM_ONE					(100)
#define MAGIC_NUM_TWO					(1000)


//************************************************************************************************//
//                                             OS VARIABLES                                       //
//************************************************************************************************//

//Tasks																@open static?
char task_names[NUM_OF_SPIN_TASKS][configMAX_TASK_NAME_LEN];

//Semaphores
SemaphoreHandle_t sync_spin_task;
SemaphoreHandle_t sync_stats_task;


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
//                                        FUNCTION DECLARATIONS                                   //
//************************************************************************************************//

//Tasks
void sysTask(void  *argument);
void dataTask(void *argument);
void dispTask(void  *argument);
void ctrlTask(void *argument);
void spin_task(void *arg);
void stats_task(void *arg);


//************************************************************************************************//
//                                          PUBLIC FUNCTIONS                                      //
//************************************************************************************************//

/**************************************************************************************************/
/** @fcn        void rtos_init(void)
 *  @brief      x
 *  @details    x
 *
 *  @pre 	x
 *  @post	x
 *
 *	@section 	Opens
 *		cmsis_os2!
 */
/**************************************************************************************************/
void rtos_init(void) {

	//Allow other core to finish initialization
  	vTaskDelay(pdMS_TO_TICKS(100));

    //Create semaphores to synchronize
    sync_spin_task = xSemaphoreCreateCounting(NUM_OF_SPIN_TASKS, 0);
    sync_stats_task = xSemaphoreCreateBinary();

    //Create spin tasks
    for(int i = 0; i < NUM_OF_SPIN_TASKS; i++) {

        snprintf(task_names[i], configMAX_TASK_NAME_LEN, "spin%d", i);

        xTaskCreatePinnedToCore(spin_task, task_names[i], 1024, NULL, SPIN_TASK_PRIO, NULL, tskNO_AFFINITY);
    }

    //Create and start stats task
    xTaskCreatePinnedToCore(stats_task, "stats", 4096, NULL, STAT_TASK_PRIO, NULL, tskNO_AFFINITY);
    xSemaphoreGive(sync_stats_task);

    //Create and start system task
    xTaskCreatePinnedToCore(sysTask, "system", 4096, NULL, SYS_TASK_PRIO, NULL, tskNO_AFFINITY);
    
    //Create and start data task
    xTaskCreatePinnedToCore(dataTask, "data", 4096, NULL, DATA_TASK_PRIO, NULL, tskNO_AFFINITY);

    //Create and start display task
    xTaskCreatePinnedToCore(dispTask, "data", 4096, NULL, DISP_TASK_PRIO, NULL, tskNO_AFFINITY);
    
    //Create and start control task
    xTaskCreatePinnedToCore(ctrlTask, "data", 4096, NULL, CTRL_TASK_PRIO, NULL, tskNO_AFFINITY);

	return;
}

	
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
 *
 *	@section 	Opens
 *		consider moving loop header to subroutine
 *		handle #defs!
 */
/**************************************************************************************************/
#define LOOPHEADER_LEN		(80)
void sysTask(void *argument) {

	//Locals
	static int loopCt = 0;
	
	//Locals
#ifdef USES_STM32
	HAL_StatusTypeDef stat = HAL_ERROR;				/* status of HAL operations for review 		  */
#endif

	//Loop
	for(;;) {

		//Loop header
		printf("\n//");
		for(int i=0; i<(LOOPHEADER_LEN-4); i++) { printf("*"); }
		printf("//\n");
		
		//Loop Notice
		printf("Loop: %d\n", loopCt++);

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
		printTaskHeader("Data");

		//Latch
#ifdef USES_STM32_HAL_TIMER
		timer_val = __HAL_TIM_GetCounter(&htim1);	/* grab current				                  */
#else
		timer_val = devTimerVal++;
#endif
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
 *
 *  @section 	Opens
 *		unroll nested conditionals .
 */
/**************************************************************************************************/
void dispTask(void *argument) {

	//Loop
	for(;;) {

		//Notify	
		printTaskHeader("Display");
        
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
		printTaskHeader("Control");
		
		//Console Sync
		printf("\n");

		//Delay
		vTaskDelay(DISPLAY_TASK_LOOP_DELAY_CTS);
	}
}


/**************************************************************************************************/
/** @fcn        static void spin_task(void *arg)
 *  @brief      x
 *  @details    x
 *
 *  @param    [in]  (void *) arg - ?
 */
/**************************************************************************************************/
void spin_task(void *arg) {
	
    xSemaphoreTake(sync_spin_task, portMAX_DELAY);
    
    for(;;) {
        //Consume CPU cycles
        for (int i = 0; i < SPIN_ITER; i++) {
            __asm__ __volatile__("NOP");
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}


/**************************************************************************************************/
/** @fcn        static void stats_task(void *arg)
 *  @brief      x
 *  @details    x
 *
 *  @param    [in]  (void *) arg - ?
 */
/**************************************************************************************************/
void stats_task(void *arg) {
	
    xSemaphoreTake(sync_stats_task, portMAX_DELAY);

    //Start all the spin tasks
    for(int i = 0; i < NUM_OF_SPIN_TASKS; i++) {
        xSemaphoreGive(sync_spin_task);
    }

    //Print real time stats periodically
    for(;;) {
        
        printf("\n\nSweating real time stats over %"PRIu32" ticks\n", STATS_TICKS);
        
        if (print_real_time_stats(STATS_TICKS) == ESP_OK) {
			
            printf("Real time stats obtained\n");
            
        } else {
			
            printf("Error getting real time stats\n");
            
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
    return;
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

