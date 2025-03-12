/**************************************************************************************************/
/** @file     freertos.c
 *  @brief    Code for freertos applications
 *  @details  x
 *
 *  @section 	Opens
 *		unused-includes bug?
 *		integrate disabled content (switch to structure definitions for task cfg)
 */
/**************************************************************************************************/

//************************************************************************************************//
//                                            INCLUDES                                            //
//************************************************************************************************//

//Standard Library Includes
#include <string.h>
#include <stdio.h>

//FreeRTOS Includes
#ifdef CMSIS_OS2_BUG
#include "cmsis_os2.h"
#endif

//RTOS Includes
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"

//Project Includes	
#include "../Rtos/freertos.h"
#include "../Mcu/uart_handler.h"
#include "../main.h"


//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
//************************************************************************************************//

//-----------------------------------------  Definitions -----------------------------------------//

//Graphic Definitions]
#define LOOPHEADER_LEN					(80)

//Task Definitions
#define SPIN_TASK_LOOP_DELAY_CTS		pdMS_TO_TICKS(100)
#define STATS_TASK_LOOP_DELAY_CTS		pdMS_TO_TICKS(2000)
#define SYSTEM_TASK_LOOP_DELAY_CTS		pdMS_TO_TICKS(4000)
#define DATA_TASK_LOOP_DELAY_CTS		pdMS_TO_TICKS(4000)
#define DISPLAY_TASK_LOOP_DELAY_CTS		pdMS_TO_TICKS(4000)
#define CONTROL_TASK_LOOP_DELAY_CTS		pdMS_TO_TICKS(4000)


//************************************************************************************************//
//                                             OS VARIABLES                                       //
//************************************************************************************************//

//Tasks
char task_names[NUM_OF_SPIN_TASKS][configMAX_TASK_NAME_LEN];		/* @open static?              */

//Semaphores
SemaphoreHandle_t sync_spin_task;
SemaphoreHandle_t sync_stats_task;


//--------------------------------------------- Tasks --------------------------------------------//

//Tasks
BaseType_t sysTaskHandle;				    	    /* System Operations Task					  */
BaseType_t dataTaskHandle;							/* Data Operations Task						  */
BaseType_t dispTaskHandle;							/* Console/UI Task							  */
BaseType_t ctrlTaskHandle;	  						/* Control Flow Taslk						  */
BaseType_t uartTaskHandle;	  						/* Uart Flow Task						      */


#ifdef CMSIS_OS2_BUG

//Config
const osThreadAttr_t sysTask_attributes = {
  .name       = SYS_TASK_NAME,
  .stack_size = DFLT_STACK_SIZE,
  .priority   = (osPriority_t) osPriorityNormal,
};

const osThreadAttr_t dataTask_attributes = {
  .name       = DATA_TASK_NAME,
  .stack_size = DFLT_STACK_SIZE,
  .priority   = (osPriority_t) osPriorityLow,
};

const osThreadAttr_t dispTask_attributes = {
  .name       = DISP_TASK_NAME,
  .stack_size = DFLT_STACK_SIZE,
  .priority   = (osPriority_t) osPriorityLow,
};

const osThreadAttr_t ctrlTask_attributes = {
  .name       = CTRL_TASK_NAME,
  .stack_size = DFLT_STACK_SIZE,
  .priority   = (osPriority_t) osPriorityLow,
};


//-------------------------------------------- Timers --------------------------------------------//

//Timers
osTimerId_t osTimerHandle;						/* Sample FreeRTOS Timer					  */

//Config
const osTimerAttr_t osTimer_attributes = {
  .name = OS_TIMER_NAME
};


//------------------------------------------- Mutexes --------------------------------------------//

//Mutexes
osMutexId_t dataMutexHandle;						/* Sample FreeRTOS Mutex					  */

//Config
const osMutexAttr_t dataMutex_attributes = {
  .name = DATA_MUTEX_NAME
};


//------------------------------------------ Semaphores -------------------------------------------//

//Semaphores
osSemaphoreId_t ctrlSemHandle;			  		    /* Sample FreeRTOS Binary Semaphore		 	  */
osSemaphoreId_t cntrSemHandle;					    /* Sample FreeRTOS Counting Semaphore	      */

//Config
const osSemaphoreAttr_t ctrlSem_attributes = {
  .name = CTRL_SEM_NAME
};

const osSemaphoreAttr_t cntrSem_attributes = {
  .name = CNTR_SEM_NAME
};


//-------------------------------------------- Events --------------------------------------------//

//Events
osEventFlagsId_t dataStoreHandle;					/* @Sample FreeRTOS Event					  */

//Config
const osEventFlagsAttr_t dataStore_attributes = {
  .name = DATA_EVENT_NAME
};

#endif


//************************************************************************************************//
//                                        FUNCTION DECLARATIONS                                   //
//************************************************************************************************//

//Tasks
void sysTask(void  *argument);
void dataTask(void *argument);
void dispTask(void  *argument);
void ctrlTask(void *argument);
void spinTask(void *arg);
void statsTask(void *arg);


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
 *		define task string names
 *		subroutine with your new struct
 */
/**************************************************************************************************/
void rtos_init(void) {

	//Allow other core to finish initialization
  	vTaskDelay(pdMS_TO_TICKS(RTOS_BOOT_DELAY_MS));

    //Create semaphores to synchronize
    sync_spin_task  = xSemaphoreCreateCounting(NUM_OF_SPIN_TASKS, 0);
    sync_stats_task = xSemaphoreCreateBinary();

    //Create spin tasks
    for(int i = 0; i < NUM_OF_SPIN_TASKS; i++) {
		
		//Name
        snprintf(task_names[i], configMAX_TASK_NAME_LEN, "spin%d", i);
        
		//Init
        xTaskCreatePinnedToCore(spinTask,
                                task_names[i],
                                1024,
                                NULL,
                                SPIN_TASK_PRIO,
                                NULL, tskNO_AFFINITY);
    }

    //Create and start stats task
    xTaskCreatePinnedToCore(statsTask,
                            "stats", 4096,
                            NULL,
                            STAT_TASK_PRIO,
                            NULL,
                            tskNO_AFFINITY);
                         
    xSemaphoreGive(sync_stats_task);

    //Create and start system task
    sysTaskHandle = xTaskCreatePinnedToCore(sysTask,
                                            "system",
                                            SYS_STACK_DEPTH,
                                            NULL,
                                            SYS_TASK_PRIO,
                                            NULL,
                                            tskNO_AFFINITY);
    
    //Create and start data task
    dataTaskHandle = xTaskCreatePinnedToCore(dataTask,
                                             "data",
                                             DATA_STACK_DEPTH,
                                             NULL,
                                             DATA_TASK_PRIO,
                                             NULL,
                                             tskNO_AFFINITY);

    //Create and start display task
    dispTaskHandle = xTaskCreatePinnedToCore(dispTask,
                                             "display",
                                             DISP_STACK_DEPTH,
                                             NULL,
                                             DISP_TASK_PRIO,
                                             NULL,
                                             tskNO_AFFINITY);
    
    //Create and start control task
    ctrlTaskHandle = xTaskCreatePinnedToCore(ctrlTask,
                                             "control",
                                             CTRL_STACK_DEPTH,
                                             NULL,
                                             CTRL_TASK_PRIO,
                                             NULL,
                                             tskNO_AFFINITY);
                                             
                                             
	//--------------------------------------- Module Tasks ---------------------------------------//
	uart_initTasks();                                             
                                             
	return;
}

	
/**************************************************************************************************/
/** @fcn        void sysTask(void *argument)
 *  @brief      Function implementing the sysTask thread
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

	//Loop
	for(;;) {

		//Print Header
		printLoopHeader();

		//Wiggle
	    //@open

		//Refresh
		//@open refresh WDT & check Errors

		//Console Sync
		printf("\n");
		
		//Delay
		vTaskDelay(SYSTEM_TASK_LOOP_DELAY_CTS);
		
	}
}


/**************************************************************************************************/
/** @fcn        void dataTask(void *argument)
 *  @brief      Function implementing the dataTask thread
 *  @details    Timer demo
 *
 *  @param    [in]  (void *) argument - x
 *
 *  @section 	Opens
 *		Use real timer
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

		//Latch timer
		timer_val = devTimerVal++;				   /* use a counter for now						 */

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
 *  @brief      Function implementing the dispTask thread
 *  @details    Semaphore demo
 *
 *  @param    [in]  (void *) argument - x
 */
/**************************************************************************************************/
void dispTask(void *argument) {

	//Locals
	esp_err_t ret;									/* return status value					 	  */
	
	
	//Loop
	for(;;) {

		//Notify	
		printTaskHeader("Display");
        
        //Print
        ret = print_real_time_stats(STATS_TICKS);
        
        if(ret == ESP_OK) {
			
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
 *  @brief      Function implementing the ctrlTask thread
 *  @details    x
 *
 *  @param    [in]  (void *) argument - x
 */
/**************************************************************************************************/
void ctrlTask(void *argument) {

	//Loop
	for(;;) {

		//Notify
		printTaskHeader("Control");
		
		//Console Sync
		uart_init();

		//Delay
		vTaskDelay(DISPLAY_TASK_LOOP_DELAY_CTS);
	}
}


/**************************************************************************************************/
/** @fcn        static void spinTask(void *arg)
 *  @brief      x
 *  @details    x
 *
 *  @param    [in]  (void *) arg - ?
 */
/**************************************************************************************************/
void spinTask(void *arg) {

    xSemaphoreTake(sync_spin_task, portMAX_DELAY);

    for(;;) {
		
		//Notify
		//? printTaskHeader("Spin");
		
        //Consume CPU cycles
        for(int i = 0; i < SPIN_ITER; i++) {
            _nop();
        }
        
        vTaskDelay(SPIN_TASK_LOOP_DELAY_CTS);
    }
}


/**************************************************************************************************/
/** @fcn        static void statsTask(void *arg)
 *  @brief      x
 *  @details    x
 *
 *  @param    [in]  (void *) arg - ?
 */
/**************************************************************************************************/
void statsTask(void *arg) {
	
	//------------------------------------ Semaphore Practice ------------------------------------//

	//Grab
#ifdef SEMAPHORE_BUG
    xSemaphoreTake(sync_stats_task, portMAX_DELAY);
#endif

    //Start all the spin tasks
    for(int i = 0; i < NUM_OF_SPIN_TASKS; i++) {
		
		//Release
#ifdef SEMAPHORE_BUG
        xSemaphoreGive(sync_spin_task);
#endif
    }


	//------------------------------------------ Print -------------------------------------------//
    for(;;) {
        
		//Notify
		printTaskHeader("Statistics");
        
        //Temp
        printf("Stats task\n");
        
        //Loop
        vTaskDelay(STATS_TASK_LOOP_DELAY_CTS);
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
 *  	Working w/notice
 */
/**************************************************************************************************/
void osTimer_Callback(void *argument) {
	return;
}

