/**************************************************************************************************/
/** @file     rtos.c
 *  @brief    Application RTOS components
 *  @details  x
 *
 *	@warn	 no magic nums
 */
/**************************************************************************************************/

//************************************************************************************************//
//                                            INCLUDES                                            //
//************************************************************************************************//

//Standard Library Includes
#include <string.h>
#include <stdio.h>

//FreeRTOS Includes
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"

//Project Includes	
#include "rtos.h"
#include "main.h"


//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
//************************************************************************************************//

//-----------------------------------------  Definitions -----------------------------------------//

//Task Names
#define STATS_TASK_NAME 				"statisticsTask"
#define SYS_TASK_NAME 					"systemTask"
#define DATA_TASK_NAME 					"dataTask"
#define DISP_TASK_NAME 					"displayTask"
#define CTRL_TASK_NAME 					"controlTask"

//Task Definitions
#define SPIN_STACK_SIZE_BYTES 			(1024)
#define STACK_SIZE_BYTES 				(4096)
#define NUM_SPIN_TASKS 					(6)

//Task Timing Definitions
#define SPIN_TASK_LOOP_DELAY_CTS		pdMS_TO_TICKS(100)
#define STATS_TASK_LOOP_DELAY_CTS		pdMS_TO_TICKS(2000)
#define SYSTEM_TASK_LOOP_DELAY_CTS		pdMS_TO_TICKS(4000)
#define DATA_TASK_LOOP_DELAY_CTS		pdMS_TO_TICKS(4000)
#define DISPLAY_TASK_LOOP_DELAY_CTS		pdMS_TO_TICKS(4000)
#define CONTROL_TASK_LOOP_DELAY_CTS		pdMS_TO_TICKS(4000)


//Timing Definitions
#define BOOT_DELAY_CTS					pdMS_TO_TICKS(100)


//************************************************************************************************//
//                                             OS VARIABLES                                       //
//************************************************************************************************//

//--------------------------------------------- Tasks --------------------------------------------//

//Tasks
BaseType_t sysTaskHandle;				    	    /* System Operations Task					  */
BaseType_t dataTaskHandle;							/* Data Operations Task						  */
BaseType_t dispTaskHandle;							/* Console/UI Task							  */
BaseType_t ctrlTaskHandle;	  						/* Control Flow Task						  */
BaseType_t statsTaskHandle;	  						/* Statistics Task						      */


//Config


//-------------------------------------------- Timers --------------------------------------------//

//Timers


//Config


//------------------------------------------- Mutexes --------------------------------------------//

//Mutexes


//Config


//------------------------------------------ Semaphores -------------------------------------------//

//Semaphores


//Config


//-------------------------------------------- Events --------------------------------------------//

//Events


//Config


//************************************************************************************************//
//                                        FUNCTION DECLARATIONS                                   //
//************************************************************************************************//

//Tasks
static void sysTask(void   *argument);
static void dataTask(void  *argument);
static void dispTask(void  *argument);
static void ctrlTask(void  *argument);
static void statsTask(void *argument);


//************************************************************************************************//
//                                          PUBLIC FUNCTIONS                                      //
//************************************************************************************************//

/**************************************************************************************************/
/** @fcn        void rtos_init(void)
 *  @brief      x
 *  @details    x
 *
 *  @pre 	system_initialize()
 *  @post	rtos tasks & mechanisms are operational 
 *
 * 	@section 	Opens
 *		Drop those magic numbers
 *		subroutine for task initialization using struct
 */
/**************************************************************************************************/
void rtos_init(void) {
	
	//Allow other core to finish initialization
  	vTaskDelay(BOOT_DELAY_CTS);
  	
  	
	//---------------------------------------- Semaphores ----------------------------------------//
	
	
	//------------------------------------------ Queues ------------------------------------------//
	
	
	//------------------------------------------ Events ------------------------------------------//
	
	
	//------------------------------------------ Tasks -------------------------------------------//
	
    //Create and start stats task
    statsTaskHandle = xTaskCreatePinnedToCore(statsTask,
                            				  STATS_TASK_NAME,
                            				  STACK_SIZE_BYTES,
                            				  NULL,
                            				  STAT_TASK_PRIO,
                            				  NULL,
                            				  tskNO_AFFINITY);
                                                  
      //Create and start system task
    sysTaskHandle = xTaskCreatePinnedToCore(sysTask,
                                            SYS_TASK_NAME,
                                            STACK_SIZE_BYTES,
                                            NULL,
                                            SYS_TASK_PRIO,
                                            NULL,
                                            tskNO_AFFINITY);
  
    //Create and start data task
    dataTaskHandle = xTaskCreatePinnedToCore(dataTask,
                                             DATA_TASK_NAME,
                                             STACK_SIZE_BYTES,
                                             NULL,
                                             DATA_TASK_PRIO,
                                             NULL,
                                             tskNO_AFFINITY);

    //Create and start display task
   dispTaskHandle = xTaskCreatePinnedToCore(dispTask,
                                             DISP_TASK_NAME,
                                             STACK_SIZE_BYTES,
                                             NULL,
                                             DISP_TASK_PRIO,
                                             NULL,
                                             tskNO_AFFINITY);
    
    //Create and start control task
  ctrlTaskHandle = xTaskCreatePinnedToCore(ctrlTask,
                                             CTRL_TASK_NAME,
                                             STACK_SIZE_BYTES,
                                             NULL,
                                             CTRL_TASK_PRIO,
                                             NULL,
                                             tskNO_AFFINITY);

	//Notify	
	printf("RTOS is initialized and prepared for use\n");
	
	return;
}


//************************************************************************************************//
//                                         PRIVATE FUNCTIONS                                      //
//************************************************************************************************//

/**************************************************************************************************/
/** @fcn        static void sysTask(void *argument)
 *  @brief      Function implementing the sysTask thread.
 *  @details    GPIO & UART demos
 *
 *  @param    [in]  (void *) argument - x
 */
/**************************************************************************************************/
static void sysTask(void *argument) {

	//Loop
	for(;;) {
			
		printf("sysTask()\n");
		
		//Delay
		vTaskDelay(SYSTEM_TASK_LOOP_DELAY_CTS);		
	}
}


/**************************************************************************************************/
/** @fcn        static void dataTask(void *argument)
 *  @brief      Function implementing the dataTask thread.
 *  @details    Timer demo
 *
 *  @param    [in]  (void *) argument - x
 */
/**************************************************************************************************/
static void dataTask(void *argument) {

	//Loop
	for(;;) {
		
		printf("dataTask()\n");
		
		//Delay
		vTaskDelay(DATA_TASK_LOOP_DELAY_CTS);
	}
}


/**************************************************************************************************/
/** @fcn        static void dispTask(void *argument)
 *  @brief      Function implementing the dispTask thread.
 *  @details    Semaphore demo
 *
 *  @param    [in]  (void *) argument - x
 */
/**************************************************************************************************/
static void dispTask(void *argument) {

	//Loop
	for(;;) {
		
		printf("dispTask()\n");
		
		//Delay
		vTaskDelay(DISPLAY_TASK_LOOP_DELAY_CTS);
	}
}


/**************************************************************************************************/
/** @fcn        static void ctrlTask(void *argument)
 *  @brief      Function implementing the ctrlTask thread.
 *  @details    x
 *
 *  @param    [in]  (void *) argument - x
 */
/**************************************************************************************************/
static void ctrlTask(void *argument) {

	//Loop
	for(;;) {
		
		printf("ctrlTask()\n");
		
		//Delay
		vTaskDelay(DISPLAY_TASK_LOOP_DELAY_CTS);
	}
}


/**************************************************************************************************/
/** @fcn        static void statsTask(void *argument)
 *  @brief      x
 *  @details    x
 *
 *  @param    [in]  (void *) argument - ?
 */
/**************************************************************************************************/
static void statsTask(void *argument) {
	
	//------------------------------------------ Print -------------------------------------------//
    for(;;) {
		
		printf("statsTask()\n");      
		  
        //Loop
        vTaskDelay(STATS_TASK_LOOP_DELAY_CTS);
    }
    
    return;
}

