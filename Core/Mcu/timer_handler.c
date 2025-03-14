/**************************************************************************************************/
/** @file     timer_handler.c
 *  @brief    Timer Application API
 *  @details  Single timer 'X' right now
 *	
 *	@section 	Opens
 *		handle pause command - "<P>, from the test app with led on the UI to pause the demo
 *		scrub freertos includes
 *		"../"!
 */
/**************************************************************************************************/

//************************************************************************************************//
//                                            INCLUDES                                            //
//************************************************************************************************//

//Standard Library Includes
#include <stdio.h>

//RTOS Includes
#include "freertos/FreeRTOS.h"

//Project Includes
#include "Rtos/freertos.h"


//************************************************************************************************//
//                                          PUBLIC FUNCTIONS                                      //
//************************************************************************************************// 
 
/**************************************************************************************************/
/** @fcn        void uart_init(void)
 *  @brief      Initialize the uart api for use
 *  @details    x
 *	
 *	@pre	start_cpu0 () - Application Startup & Port Initialization
 *	@post	uart driver utilities are prepared for use
 */
/**************************************************************************************************/
void timer_init(void) {
	
	printf("Timer initialization complete.\n");
	
	return;
	
 }
  
 
 /**************************************************************************************************/
/** @fcn        static void timerTask(void *argument)
 *  @brief      x 
 *  @details    x
 *
 *  @param    [in]  (void *) argument - x
 *
 *  @section 	Opens
 *		not sure if needed
 */
/**************************************************************************************************/
static void timerTask(void *argument) {

	//Loop
	for(;;) {
		
		printf("Timer - Loop\n");		
		
		//Delay
		vTaskDelay(TIMER_THREAD_DELAY_CTS);
	}
} 


 /**************************************************************************************************/
/** @fcn        void timer_initTasks(void)
 *  @brief      Initialize the uart api for use
 *  @details    x
 *	
 *	@pre	timer_init() & rtos_init()
 *	@post	timerTask in operation
 *
 *  @section 	Opens
 *		yep!
 */
/**************************************************************************************************/
void timer_initTasks(void) {
	
    //Create and start control task
    timerTaskHandle = xTaskCreatePinnedToCore(timerTask,
                                             TIMER_TASK_NAME, 
                                             TIMER_STACK_DEPTH,
                                             NULL,
                                             TIMER_TASK_PRIO,
                                             NULL,
                                             tskNO_AFFINITY);
	return;
 } 

