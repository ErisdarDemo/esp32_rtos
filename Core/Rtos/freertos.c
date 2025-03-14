/**************************************************************************************************/
/** @file     freertos.c
 *  @brief    Code for freertos applications
 *  @details  x
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
#include "Rtos/freertos.h"
#include "Mcu/timer_handler.h"
#include "Mcu/uart_handler.h"
#include "main.h"


//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
//************************************************************************************************//

//-----------------------------------------  Definitions -----------------------------------------//

//Graphic Definitions]
#define LOOPHEADER_LEN                  (80)

//Task Definitions
#define SPIN_TASK_LOOP_DELAY_CTS        pdMS_TO_TICKS(300)
#define STATS_TASK_LOOP_DELAY_CTS       pdMS_TO_TICKS(3000)
#define SYSTEM_TASK_LOOP_DELAY_CTS      pdMS_TO_TICKS(6000)
#define DATA_TASK_LOOP_DELAY_CTS        pdMS_TO_TICKS(6000)
#define DISPLAY_TASK_LOOP_DELAY_CTS     pdMS_TO_TICKS(6000)
#define CONTROL_TASK_LOOP_DELAY_CTS     pdMS_TO_TICKS(6000)


//************************************************************************************************//
//                                             OS VARIABLES                                       //
//************************************************************************************************//

//Tasks
static char task_names[NUM_OF_SPIN_TASKS][configMAX_TASK_NAME_LEN];

//Semaphores
static SemaphoreHandle_t sync_spin_task;
static SemaphoreHandle_t sync_stats_task;


//--------------------------------------------- Tasks --------------------------------------------//

//Tasks
static BaseType_t sysTaskHandle;                    /* System Operations Task                     */
static BaseType_t dataTaskHandle;                   /* Data Operations Task                       */
static BaseType_t dispTaskHandle;                   /* Console/UI Task                            */
static BaseType_t ctrlTaskHandle;                   /* Control Flow Taslk                         */

BaseType_t timerTaskHandle;                         /* Software Timer task                        */
BaseType_t uartTaskHandle;                          /* Uart Flow Task                             */


//************************************************************************************************//
//                                        FUNCTION DECLARATIONS                                   //
//************************************************************************************************//

//Tasks
static void sysTask(void  *argument);
static void dataTask(void *argument);
static void dispTask(void  *argument);
static void ctrlTask(void *argument);
static void spinTask(void *arg);
static void statsTask(void *arg);


//************************************************************************************************//
//                                          PUBLIC FUNCTIONS                                      //
//************************************************************************************************//

/**************************************************************************************************/
/** @fcn        void rtos_init(void)
 *  @brief      Initialize RTOS components for operation
 *  @details    x
 *
 *  @pre    sys_init()
 *  @post   RTOS is configured and tasks operational
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
        snprintf(task_names[i], configMAX_TASK_NAME_LEN, "%s%d",SPIN_TASK_NAME, i);
        
        //Init
        xTaskCreatePinnedToCore(spinTask,
                                task_names[i],
                                SPIN_TASK_DEPTH,
                                NULL,
                                SPIN_TASK_PRIO,
                                NULL, tskNO_AFFINITY);
    }

    //Create and start stats task
    xTaskCreatePinnedToCore(statsTask,
                            STATS_TASK_NAME,
                            STATS_TASK_DEPTH,
                            NULL,
                            STAT_TASK_PRIO,
                            NULL,
                            tskNO_AFFINITY);
                         
    xSemaphoreGive(sync_stats_task);

    //Create and start system task
    sysTaskHandle = xTaskCreatePinnedToCore(sysTask,
                                            SYS_TASK_NAME,
                                            SYS_STACK_DEPTH,
                                            NULL,
                                            SYS_TASK_PRIO,
                                            NULL,
                                            tskNO_AFFINITY);
    
    //Create and start data task
    dataTaskHandle = xTaskCreatePinnedToCore(dataTask,
                                             DATA_TASK_NAME,
                                             DATA_STACK_DEPTH,
                                             NULL,
                                             DATA_TASK_PRIO,
                                             NULL,
                                             tskNO_AFFINITY);

    //Create and start display task
    dispTaskHandle = xTaskCreatePinnedToCore(dispTask,
                                             TASK_TASK_NAME,
                                             DISP_STACK_DEPTH,
                                             NULL,
                                             DISP_TASK_PRIO,
                                             NULL,
                                             tskNO_AFFINITY);
    
    //Create and start control task
    ctrlTaskHandle = xTaskCreatePinnedToCore(ctrlTask,
                                             CTRL_TASK_NAME,
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
/** @fcn        static void sysTask(void *argument)
 *  @brief      Function implementing the sysTask thread
 *  @details    x
 *
 *  @param    [in]  (void *) argument - x
 */
/**************************************************************************************************/
static void sysTask(void *argument) {

    //Loop
    for(;;) {

        //Print Header
        printLoopHeader();

        //Console Sync
        printf("\n");
        
        //Delay
        vTaskDelay(SYSTEM_TASK_LOOP_DELAY_CTS);
        
    }
}


/**************************************************************************************************/
/** @fcn        static void dataTask(void *argument)
 *  @brief      Function implementing the dataTask thread
 *  @details    Timer demo
 *
 *  @param    [in]  (void *) argument - x
 */
/**************************************************************************************************/
static void dataTask(void *argument) {

    //Locals
    uint64_t timer_val     = 0;                     /* time check value                           */
    char buff[100]         = {0};                   /* print buffer                               */


    //Init
    memset(&buff, 0x00, sizeof(buff));

    //Loop
    for(;;) {

        //Notify
        printTaskHeader("Data");

        //Latch timer ( %lx or %llx) 
        timer_val = timer_getCount();

        //Print
        printf("Timer: %llu\n", timer_val);
        
        //Console Sync
        printf("\n");

        //Delay
        vTaskDelay(DATA_TASK_LOOP_DELAY_CTS);
    }
}


/**************************************************************************************************/
/** @fcn        static void dispTask(void *argument)
 *  @brief      Function implementing the dispTask thread
 *  @details    Semaphore demo
 *
 *  @param    [in]  (void *) argument - x
 */
/**************************************************************************************************/
static void dispTask(void *argument) {

    //Locals
    esp_err_t ret;                                  /* return status value                        */
    
    
    //Loop
    for(;;) {

        //Notify    
        printTaskHeader("Display");
        
        //Print
        ret = print_real_time_stats(PRINT_STATS_DELAY_CTS);
        
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
/** @fcn        static void ctrlTask(void *argument)
 *  @brief      Function implementing the ctrlTask thread
 *  @details    x
 *
 *  @param    [in]  (void *) argument - x
 */
/**************************************************************************************************/
static void ctrlTask(void *argument) {

    //Loop
    for(;;) {

        //Notify
        printTaskHeader("Control");
        
        //Console Sync
        printf("...!\n");

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
static void spinTask(void *arg) {

    xSemaphoreTake(sync_spin_task, portMAX_DELAY);

    for(;;) {
        
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
static void statsTask(void *arg) {
    
    //------------------------------------ Semaphore Practice ------------------------------------//

    //Grab
    xSemaphoreTake(sync_stats_task, portMAX_DELAY);

    //Start all the spin tasks
    for(int i = 0; i < NUM_OF_SPIN_TASKS; i++) {
        
        //Allow
        xSemaphoreGive(sync_spin_task);
    }


    //------------------------------------------ Print -------------------------------------------//
    for(;;) {
            
        //Loop
        vTaskDelay(STATS_TASK_LOOP_DELAY_CTS);
    }
    
    return;
}

