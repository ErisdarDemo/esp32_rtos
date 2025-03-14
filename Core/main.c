/**************************************************************************************************/
/** @file     main.c
 *  @brief    ESP32 FreeRTOS Template
 *  @details  Waveshare Module Support
 *
 *  @author   Justin Reina, Firmware Engineer
 *  @created  3/2/25
 *  @last rev 3/14/25
 *
 *   @section 	Opens
 *		add real timer
 *		Complete demo
 *		...
 *		Sync with STM32
 *			Publish & host 'v1'!
 * 			post both updates to new www rtos page
 *		
 *	 @section 	Development Flow
 *		1. Integrate existing STM 'v0'
 *		2. Update w/STM to 'v1'
 *		4. Adapt to Espressif SMP demo
 *		5. Integrate Bluetooth (branch)
 *		6. Integrate WiFi (branch)
 *
 *	 @section 	Sources
 *		FreeRTOS Real Time Stats Example 'real_time_stats_example_main'
 *		CubeMx_RTOS_Demo 'r0'
 *
 *	@section 	Forum Help
 *		Relocate main\ & build\ dirs
 *		Uart Rx & Rx Thread
 *
 *	@section 	Desires
 *		migration to cmsis_os2 (e.g. group task defs to a structure?)
 *
 *  @section    Legal Disclaimer
 * 		©2025 Justin Reina. All rights reserved. All contents of this source file and/or any other
 *      related source files are the explicit property of Justin Reina. Do not distribute.
 *      Do not copy.
 */
/**************************************************************************************************/

//************************************************************************************************//
//                                            INCLUDES                                            //
//************************************************************************************************//

//Standard Library Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

//SDK Includes
#include "sdkconfig.h"
#include "esp_err.h"

//FreeRTOS Includes
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"


//Project Includes
#include "System/utils.h"
#include "Rtos/freertos.h"
#include "Mcu/timer_handler.h"
#include "Mcu/uart_handler.h"
#include "main.h"


//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
//************************************************************************************************//

//-----------------------------------------  Definitions -----------------------------------------//

//Error Support
#define ARRAY_SIZE_OFFSET   (5)   		/* Soln ++ iff ESP_ERR_INVALID_SIZE					      */


//************************************************************************************************//
//                                       FUNCTION DECLARATIONS                                    //
//************************************************************************************************//

//Local Routines
static void sys_init(void);


//************************************************************************************************//
//                                          PUBLIC FUNCTIONS                                      //
//************************************************************************************************//

/**************************************************************************************************/
/** @fcn        esp_err_t print_real_time_stats(TickType_t xTicksToWait)
 *  @brief      Function to print the CPU usage of tasks over a given duration.
 *  @details    x
 *
 *  @section    Purpose
 *      This function will measure and print the CPU usage of tasks over a specified number of 
 *      ticks (i.e. real time stats). This is implemented by simply calling uxTaskGetSystemState() 
 *      twice separated by a delay, then calculating the differences of task run times before and 
 *      after the delay.
 *
 *  @param    [in]  (TickType_t) xTicksToWait - Period of stats measurement
 *
 *  @return   (esp_err_t) ?
 *             - ESP_OK                Success
 *             - ESP_ERR_NO_MEM        Insufficient memory to allocated internal arrays
 *             - ESP_ERR_INVALID_SIZE  Insufficient array size for uxTaskGetSystemState. 
 *             - ESP_ERR_INVALID_STATE Delay duration too short
 *
 *  @note    for 'ESP_ERR_INVALID_SIZE' - Trying increasing ARRAY_SIZE_OFFSET
 *
 *  @section    Notes
 *       If any tasks are added or removed during the delay, the stats of those tasks will not be 
 *       printed
 *
 *       This function should be called from a high priority task to minimize inaccuracies w/delays
 *
 *       When running in dual core mode, each core will correspond to 50% of the run time.
 */
/**************************************************************************************************/
esp_err_t print_real_time_stats(TickType_t xTicksToWait) {

	//Locals
    TaskStatus_t *start_array = NULL, *end_array = NULL;
    UBaseType_t start_array_size, end_array_size;
    configRUN_TIME_COUNTER_TYPE start_run_time, end_run_time;
    esp_err_t ret;

    //Allocate array to store current task states
    start_array_size = uxTaskGetNumberOfTasks() + ARRAY_SIZE_OFFSET;
    start_array = malloc(sizeof(TaskStatus_t) * start_array_size);
    
    //Notify
    printf("print_real_time_stats(): Getting real time stats\n");
    
    if (start_array == NULL) {
        ret = ESP_ERR_NO_MEM;
        goto exit;
    }
    
    
    //Get current task states
    start_array_size = uxTaskGetSystemState(start_array, start_array_size, &start_run_time);
    
    if (start_array_size == 0) {
        ret = ESP_ERR_INVALID_SIZE;
        goto exit;
    }

    vTaskDelay(xTicksToWait);

    //Allocate array to store tasks states post delay
    end_array_size = uxTaskGetNumberOfTasks() + ARRAY_SIZE_OFFSET;
    end_array = malloc(sizeof(TaskStatus_t) * end_array_size);
    
    if (end_array == NULL) {
        ret = ESP_ERR_NO_MEM;
        goto exit;
    }
    
    
    //Get post delay task states
    end_array_size = uxTaskGetSystemState(end_array, end_array_size, &end_run_time);
    
    if (end_array_size == 0) {
        ret = ESP_ERR_INVALID_SIZE;
        goto exit;
    }
    

    //Calculate total_elapsed_time in units of run time stats clock period.
    uint32_t total_elapsed_time = (end_run_time - start_run_time);
    if (total_elapsed_time == 0) {
        ret = ESP_ERR_INVALID_STATE;
        goto exit;
    }

    printf("| Task   | Run Time | Percentage\n");
    
    //Match each task in start_array to those in the end_array
    for (int i = 0; i < start_array_size; i++) {
		
        int k = -1;
        
        for (int j = 0; j < end_array_size; j++) {
			
            if (start_array[i].xHandle == end_array[j].xHandle) {
				
                k = j;
                
                //Mark that task have been matched by overwriting their handles
                start_array[i].xHandle = NULL;
                end_array[j].xHandle = NULL;
                
                break;
            }
        }
        
        //Check if matching task found
        if (k >= 0) {
			
			//Elapsed time count
            uint32_t task_elapsed_time = end_array[k].ulRunTimeCounter - start_array[i].ulRunTimeCounter;
            
            //Percentage complete
            uint32_t percentage_time = (task_elapsed_time * 100UL) / (total_elapsed_time * CONFIG_FREERTOS_NUMBER_OF_CORES);
			
			//----------------------------------- Calc Spacing -----------------------------------//
			 
			int num_elapsed_digits = numPlaces(task_elapsed_time);
 
			char *spaceOneStr = "!";
			char *spaceTwoStr = "?";

			int sizeOne      = strlen(start_array[i].pcTaskName);
			int sizeOneMax   = 6;
			int sizeOneSpace = (sizeOneMax-sizeOne+1);

			int sizeTwo      = num_elapsed_digits;
			int sizeTwoMax   = 8;					/* pick a big size for KISS					  */					
			int sizeTwoSpace = (sizeTwoMax-sizeTwo);
			
			char stringOne[10] = {0};				/* static size for KISS						  */
			char stringTwo[10] = {0};
			
			//Gen Spaces
			for(int i=0; i<sizeOneSpace; i++) { stringOne[i] = ' '; }
			for(int i=0; i<sizeTwoSpace; i++) { stringTwo[i] = ' '; }
			stringOne[sizeOneSpace] = 0x00;			// EOS
			stringTwo[sizeTwoSpace] = 0x00;			// EOS

			spaceOneStr = &stringOne[0];
			spaceTwoStr = &stringTwo[0];


			//----------------------------------- Print Console-----------------------------------//
			
            printf("| %s%s| %"PRIu32" %s| %"PRIu32"%%\n", start_array[i].pcTaskName, 
											              spaceOneStr, 
											              task_elapsed_time, 
											              spaceTwoStr, 
											              percentage_time);
        }
    }
    
    printf("\nTasks:\n");

    //Print unmatched tasks
    for (int i = 0; i < start_array_size; i++) {
        if (start_array[i].xHandle != NULL) {
            printf("| %s | Deleted\n", start_array[i].pcTaskName);
        }
    }
    for (int i = 0; i < end_array_size; i++) {
        if (end_array[i].xHandle != NULL) {
            printf("| %s | Created\n", end_array[i].pcTaskName);
        }
    }
    ret = ESP_OK;

exit:    //Common return path
    free(start_array);
    free(end_array);
    return ret;
}


/**************************************************************************************************/
/** @fcn        int app_main(void)
 *  @brief      x
 *  @details    xt
 */
/**************************************************************************************************/
void app_main(void) {
	
		//Launch
		sys_init();

		//Error Handling
		// @todo!
			
	    return;
}


/**************************************************************************************************/
/** @fcn        static int sys_init(void)
 *  @brief      Initialize the system for use
 *  @details    x
 *
 *	@section 	Opens
 *		Consider rtos_init() inegration
 *		Consider relocation to Core\System\system.c&h (cleaner here for now)
 */
/**************************************************************************************************/
static void sys_init(void) {
	
	//HW Init
	timer_init();
	uart_init();
			
	//OS Init
	rtos_init();
	
	return;
}

