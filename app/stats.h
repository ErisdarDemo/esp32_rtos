/**************************************************************************************************/
/** @file     stats.h
 *  @brief    Demo Application Component Interface File
 *  @details  x
 *
 *  @section    Notes
 *      Interface file headers like this are not recommended in preference for the source header
 */
/**************************************************************************************************/
#ifndef APP_STATS_H_
#define APP_STATS_H_

//FreeRTOS Includes
#include "freertos/FreeRTOS.h"

//Global Routines
extern esp_err_t print_real_time_stats(TickType_t xTicksToWait); /* and section divs (e.g. 
                                                                    'DECLARATIONS' here) are also 
                                                                    not recommended for lightweight 
                                                                    interface files like this 
                                                                    either - 'KISS'               */
#endif /* APP_STATS_H_ */
