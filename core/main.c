/**************************************************************************************************/
/** @file     main.c
 *  @brief    Template for Application RTOS development 
 *  @details  x
 *
 *  @author   Justin Reina, Firmware Engineer
 *  @created  3/31/25
 *  @last rev 4/1/25
 *
 *  @note   Private functions & variables are declared static
 *
 *  @section    Opens
 *      mutex demo
 *      event demo
 *      queue demo ('v1')
 *      binary semaphores demo (Console sleeping till available)
 *      sync with stm32 'v1' demo
 *      C++ base version ('v2')
 *
 *  @section    For Consideration
 *      Absolute paths for includes in project
 *      Tasks have mutual exclusion to console printing (system.c: consoleSemaphore)
 *
 *  @section    Legal Disclaimer
 *      ©2025 Justin Reina. All rights reserved. All contents of this source file and/or any other
 *      related source files are the explicit property of Justin Reina. Do not distribute.
 *      Do not copy.
 */
/**************************************************************************************************/

//************************************************************************************************//
//                                            INCLUDES                                            //
//************************************************************************************************//

//Standard Library Includes
#include <stdio.h>
#include <inttypes.h>
#include <sys/unistd.h>

//Library Includes
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

//SDK Includes
#include "sdkconfig.h"

//FreeRTOS Includes
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//Project Includes
#include "utils.h"
#include "system.h"
#include "rtos.h"
#include "main.h"


//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
//************************************************************************************************//

//-----------------------------------------  Definitions -----------------------------------------//

//Timing
#define SLEEP_DELAY_S       (10)


//************************************************************************************************//
//                                          PUBLIC FUNCTIONS                                      //
//************************************************************************************************//

/**************************************************************************************************/
/** @fcn        void app_main(void)
 *  @brief      FreeRTOS task for main application
 *  @details    Called by FreeRTOS scheduler when started, running on core for main thread
 *
 *  @section    Purpose
 *      Unlike normal FreeRTOS tasks, or embedded C main functions, the app_main() task is allowed 
 *      to return. If this happens, The task is cleaned up and the system will continue running 
 *      with other RTOS tasks scheduled normally. Therefore, it is possible to implement app_main 
 *      as either a function that creates other application tasks and then returns, or as a main 
 *      application task itself. app_main() has a fixed RTOS priority, one higher than the minimum
 *
 *  @pre    second stage bootloader
 *  @post   no return
 *
 *  @section    Opens
 *      Consider safety catch on FreeRTOS api
 */
/**************************************************************************************************/
void app_main(void) {
    
    //-------------------------------------- Initialization --------------------------------------//

    //Init        
    system_initialize();

   
    //--------------------------------------- Application ----------------------------------------//

    for(;;) {
        
        //------------------------------------- Update -------------------------------------------//

            
        //------------------------------------- Reset --------------------------------------------//
        
        //Delay
        sleep(SLEEP_DELAY_S);
    }   
}


//************************************************************************************************//
//                                         PRIVATE FUNCTIONS                                      //
//************************************************************************************************//


