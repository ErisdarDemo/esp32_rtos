#ifndef LBR_UTILS_H_
#define LBR_UTILS_H_

//************************************************************************************************//
//                                            INCLUDES                                            //
//************************************************************************************************//

//FreeRTOS Includes
#include "freertos/FreeRTOS.h"


//************************************************************************************************//
//                                       FUNCTION DECLARATIONS                                    //
//************************************************************************************************//

//Math Utilities
extern int numPlaces(int n);

//Print Utilities
extern void printTaskHeader(char *titleStr);
extern void printLoopHeader(void);

//State Utilities
int getLoopCt(void);

//Static Utilities
extern esp_err_t print_real_time_stats(TickType_t xTicksToWait);


#endif /* LBR_UTILS_H_ */

