/**************************************************************************************************/
/** @file     timer_handler.c
 *  @brief    Timer Application API
 *  @details  FreeRTOS timer right now
 *  
 *  @section    Opens
 *      handle pause command from the user with led on the test UI to pause demo
 */
/**************************************************************************************************/

//************************************************************************************************//
//                                            INCLUDES                                            //
//************************************************************************************************//

//Standard Library Includes
#include <stdint.h>
#include <stdio.h>

//RTOS Includes
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

//Project Includes
#include "rtos.h"
#include "timer_handler.h"


//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
//************************************************************************************************//

#define TIMER_NAME          "timer1Sec"
#define TIMER_DELAY_CTS     pdMS_TO_TICKS(1000)
#define TIMER_ID            ((void *)0)


//************************************************************************************************//
//                                           VARIABLES                                            //
//  @section    Opens                                                                             //
//      consider moving to hardware                                                               //
//************************************************************************************************//

//Timer
static int64_t timerValue = TIMER_UNSET_VALUE;      /*  software timer value for api              */
 

//************************************************************************************************//
//                                          PUBLIC FUNCTIONS                                      //
//************************************************************************************************// 
 
 /**************************************************************************************************/
/** @fcn        static void timer_callback(xTimerHandle pxTimer)
 *  @brief      x
 *  @details    x
 *
 *  @param [in] (xTimerHandle) pxTimer - x
 */
/**************************************************************************************************/
static void timer_callback(TimerHandle_t pxTimer) {

    //Increment
    timerValue++;

    return;
}
 
 
/**************************************************************************************************/
/** @fcn        void timer_init(void)
 *  @brief      Initialize the timer & timer api for use
 *  @details    x
 *  
 *  @pre    x
 *  @post   timer driver utilities & api are prepared for use
 *
 *  @section    Reference
 *      mcuoneclipse/Examples/MCUXpresso/FRDM-K64F_FreeRTOS_Timer/main.c
 *
 *  @section 	Opens
 *      Non-blocking safety catch  
 */
/**************************************************************************************************/
void timer_init(void) {

    //Local Variables   
    TimerHandle_t timerHandle;                      /* timer for api                              */
    BaseType_t stat;                                /* sdk response values                        */


    //Init State
    timerValue = 0; 

    //Init Counter Task
    timerHandle = xTimerCreate(
           TIMER_NAME,                              /* name                                       */
           TIMER_DELAY_CTS,                         /* period/time                                */
           pdTRUE,                                  /* auto reload                                */
           TIMER_ID,                                /* timer ID                                   */
           timer_callback);                         /* callback                                   */
   
    //Safety
    if(timerHandle == NULL) {
        for(;;);                                    /* catch!                                     */
    }
    
    
    //Start Counter Task
    stat = xTimerStart(timerHandle, 0); 
    
    //Safety
    if(stat != pdPASS) {
      for(;;);                                      /* catch!                                     */
    }
    
    
    //Notify
    printf("Timer initialization complete.\n");
    
    return;
    
}
  

/**************************************************************************************************/
/** @fcn        uint64_t timer_getCount(void)
 *  @brief      Get timer value
 *  @details    TIMER_UNSET_VALUE for un-initialized timer 
 *  
 *  @return (uint64_t) software timer value
 */
/**************************************************************************************************/
  uint64_t timer_getCount(void) {
    return timerValue;
  }

