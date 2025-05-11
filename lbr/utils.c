/**************************************************************************************************/
/** @file     utils.c
 *  @brief    Common code utilities
 *  @details  x
 *
 *  @section    Opens
 *      Get these stats printing again, not sure what is hanging. Check the real_time_stats
 *      ESP demo
 */
/**************************************************************************************************/

//************************************************************************************************//
//                                            INCLUDES                                            //
//************************************************************************************************//

//Standard Library Includes
#include <limits.h>
#include <string.h>
#include <stdio.h>

 #include "sdkconfig.h"
 #include <inttypes.h>

//FreeRTOS Includes
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"

#include "esp_err.h"


//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
//************************************************************************************************//

//-----------------------------------------  Definitions -----------------------------------------//
#define PRINTTASK_LEN   		(73)                /* num of chars on the print header           */
#define TASK_STR        		(" Task")           /* Common task display header string          */
#define LOOPHEADER_LEN  		(80)

//Error Support
#define ARRAY_SIZE_OFFSET       (5)                 /* Soln ++ iff ESP_ERR_INVALID_SIZE           */

//String Defs
#define EOS_CHAR                (0x00)
#define DFLT_STR_BUFF_SIZE      (10)


//************************************************************************************************//
//                                             VARIABLES                                          //
//************************************************************************************************//

//Header Variables
static int loopCt = 0;                              /* loop cycle count to display on console     */


//************************************************************************************************//
//                                          PUBLIC FUNCTIONS                                      //
//************************************************************************************************// 
 
/**************************************************************************************************/
/** @fcn        int numPlaces (int n)
 *  @brief      determine number of characters in a printed number
 *  @details    x
 *
 *  @param    [in]  (int) n - number to evaluate for length
 */
/**************************************************************************************************/
int numPlaces(int n) {
    
    //Locals
    int r = 1;
    
    if(n < 0) {
        n = (n == INT_MIN) ? INT_MAX: -n;
    }
    
    while(n > 9) {
        
        n /= 10;
        
        r++;
    }
    
    return r;
}


/**************************************************************************************************/
/** @fcn        void printTaskHeader(char *titleStr)
 *  @brief      x
 *  @details    x
 *
 *  @param    [in]  (char *) titleStr - x
 *
 *  @assum  console available for print output
 */
/**************************************************************************************************/
void printTaskHeader(char *titleStr) {
    
    //Locals
    int spaceLen = 0;                               /* Title bar equal side spacing count         */
    int diffVal  = 0;                               /* Extra title bar space needed?              */
    
    
    //Calc Space Needed
    spaceLen = (PRINTTASK_LEN - (2*2) - strlen(titleStr) - strlen(TASK_STR)) / 2;
    
    //Extra Space Check
    diffVal  =  PRINTTASK_LEN - (2*2) - strlen(titleStr) - strlen(TASK_STR) - (2*spaceLen);
    
    
    //---------------------------------------- Upper Bar -----------------------------------------//
    printf("\n//");
    for(int i=0; i<(PRINTTASK_LEN-4); i++) { printf("-"); }
    printf("//\n");
        
        
    //---------------------------------------- Title Bar -----------------------------------------//
    printf("//");                                   /* upper line                                 */
    for(int i=0;i<spaceLen; i++) {printf(" "); }
    
    printf("%s", titleStr);                         /* title line                                 */
    printf("%s", TASK_STR);
    
    for(int i=0;i<spaceLen; i++) {printf(" "); }    /* lower line                                 */
    if(diffVal != 0) { printf(" "); }
    printf("//\n");
    
        
    //---------------------------------------- Lower Bar -----------------------------------------//
    printf("//");
    for(int i=0; i<(PRINTTASK_LEN-4); i++) { printf("-"); }
    printf("//\n");

    
    return;
}


/**************************************************************************************************/
/** @fcn        void printLoopHeader(void)
 *  @brief      print output loop break header
 *  @details    x
 *
 *  @assum  console available for print output
 */
/**************************************************************************************************/
void printLoopHeader(void) {
    
    //Locals
    int spaceLen = 0;                               /* Title bar equal side spacing count         */
    int numDigs  = numPlaces(loopCt);
    
    //Calc Space Needed
    spaceLen = (PRINTTASK_LEN - (2*2) - numDigs);
    
    
    //---------------------------------------- Upper Bar -----------------------------------------//
    printf("\n//");
    for(int i=0; i<(LOOPHEADER_LEN-4); i++) { printf("*"); }
    printf("//\n");
            
            
    //---------------------------------------- Title Bar -----------------------------------------//
    //...
    printf("// Loop: %d", loopCt++);
    for(int i=0; i<spaceLen; i++) { printf(" "); }
    printf("//\n");
    
    
    //---------------------------------------- Lower Bar -----------------------------------------//
    printf("//");
    for(int i=0; i<(LOOPHEADER_LEN-4); i++) { printf("*"); }
    printf("//\n");

    
    return;
}


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
    TaskStatus_t *start_array = NULL;
    TaskStatus_t *end_array   = NULL;
    UBaseType_t start_array_size;
    UBaseType_t end_array_size;
    configRUN_TIME_COUNTER_TYPE start_run_time;
    configRUN_TIME_COUNTER_TYPE end_run_time;
    esp_err_t stat;

    //Allocate array to store current task states
    start_array_size = (uxTaskGetNumberOfTasks() + ARRAY_SIZE_OFFSET);
    start_array = malloc(sizeof(TaskStatus_t) * start_array_size);

    //Safety
    if(start_array == NULL) {
        stat = ESP_ERR_NO_MEM;
        goto exit;
    }
    
    //Get current task states
    start_array_size = uxTaskGetSystemState(start_array, start_array_size, &start_run_time);

    //Safety
    if(start_array_size == 0) {
        stat = ESP_ERR_INVALID_SIZE;
        goto exit;
    }

    vTaskDelay(xTicksToWait);

    //Allocate array to store tasks states post delay
    end_array_size = (uxTaskGetNumberOfTasks() + ARRAY_SIZE_OFFSET);
    end_array = malloc(sizeof(TaskStatus_t) * end_array_size);
    
    //Safety
    if(end_array == NULL) {
        stat = ESP_ERR_NO_MEM;
        goto exit;
    }

    //Get post delay task states
    end_array_size = uxTaskGetSystemState(end_array, end_array_size, &end_run_time);

    //Safety
    if(end_array_size == 0) {
        stat = ESP_ERR_INVALID_SIZE;
        goto exit;
    }
    
    //Calculate total_elapsed_time in units of run time stats clock period.
    uint32_t total_elapsed_time = (end_run_time - start_run_time);

    //BUG
    if(total_elapsed_time == 0) {
        total_elapsed_time = 100;
    }
    
    if(total_elapsed_time == 0) {
        stat = ESP_ERR_INVALID_STATE;
        goto exit;
    }

    printf("| Task           | Run Time | Percentage\n");   /* @open  dynamic spacing             */
    
    //Match each task in start_array to those in the end_array
    for(int i = 0; i < start_array_size; i++) {
        
        int k = -1;
        
        for(int j = 0; j < end_array_size; j++) {
            
            if(start_array[i].xHandle == end_array[j].xHandle) {
                
                k = j;
                
                //Mark that task have been matched by overwriting their handles
                start_array[i].xHandle = NULL;
                end_array[j].xHandle   = NULL;
                
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
            int sizeOneMax   = 14;                  /* clean spacing                              */
            int sizeOneSpace = (sizeOneMax-sizeOne+1);

            int sizeTwo      = num_elapsed_digits;
            int sizeTwoMax   = 8;                   /* clean spacing                              */                    
            int sizeTwoSpace = (sizeTwoMax-sizeTwo);
            
            char stringOne[DFLT_STR_BUFF_SIZE] = {0};
            char stringTwo[DFLT_STR_BUFF_SIZE] = {0};
            
            //Gen Spaces
            for(int i=0; i<sizeOneSpace; i++) { stringOne[i] = ' '; }
            for(int i=0; i<sizeTwoSpace; i++) { stringTwo[i] = ' '; }
            stringOne[sizeOneSpace] = EOS_CHAR;
            stringTwo[sizeTwoSpace] = EOS_CHAR;

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
    
    stat = ESP_OK;
    
exit:   
    //------------------------------------ Common return path ------------------------------------//
    free(start_array);
    free(end_array);

    return stat;
}


/**************************************************************************************************/
/** @fcn        int getLoopCt(void)
 *  @brief      x
 *  @details    x 
 *  
 *  @return (int) active demo loop count
 */
/**************************************************************************************************/
int getLoopCt(void) {
    return loopCt;
}

