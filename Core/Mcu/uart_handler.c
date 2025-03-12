/**************************************************************************************************/
/** @file     uart_handler.c
 *  @brief    UART Application API
 *  @details  x
 *	
 *	@section 	Opens
 *		handle pause command - "<P>, from the test app with led on the UI to pause the demo
 */
/**************************************************************************************************/

//************************************************************************************************//
//                                            INCLUDES                                            //
//************************************************************************************************//

//Standard Library Includes
#include <stdio.h>
#include <stdio.h>

//RTOS Includes
#include "freertos/FreeRTOS.h"
//?#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"

//Project Includes
#include "../Rtos/freertos.h"
#include "../main.h"


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
void uart_init(void) {
	
	printf("Hi Uart\n");
	
	return;
	
 }


/**************************************************************************************************/
/** @fcn        void uart_rxTask(void *argument)
 *  @brief      Function implementing the uartTask thread 
 *  @details    Handle received bytes from the uart
 *
 *  @param    [in]  (void *) argument - x
 *
 *  @section 	Opens
 *		rx working (port is blocked?)
 *		#define delay value
 *		switch to explicit uart initialization
 */
/**************************************************************************************************/
#ifdef UART_RX_WORKING
#include <stdlib.h>
#define BUF_SIZE (1024)
#endif
void uart_rxTask(void *argument) {

	//Locals
	int len = 0;

#ifdef UART_RX_WORKING
	// Configure a temporary buffer for the incoming data
    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);
  #endif
   
	//Loop
	//@open set uart & buff length explicitly
	for(;;) {

#ifdef UART_RX_WORKING
		int len;		
		uart_get_buffered_data_len(ECHO_UART_PORT_NUM, (size_t*)&len);
		uart_read_bytes(ECHO_UART_PORT_NUM, data, (BUF_SIZE - 1), 20 / portTICK_PERIOD_MS);
#else	
		len++;
#endif
		printf("uart_rxTask(): %d bytes\n", len);
		
		//Delay
		vTaskDelay(pdMS_TO_TICKS(2000));
	}
} 


 /**************************************************************************************************/
/** @fcn        void uart_init(void)
 *  @brief      Initialize the uart api for use
 *  @details    x
 *	
 *	@pre	uart_init() & rtos_init()
 *	@post	uart prepared for data reception
 *
 *  @section 	Opens
 *		Consider relocation to freertos.c
 */
/**************************************************************************************************/
void uart_initTasks(void) {
	
    //Create and start control task
    uartTaskHandle = xTaskCreatePinnedToCore(uart_rxTask,
                                             "uart",
                                             UART_STACK_DEPTH,
                                             NULL,
                                             UART_TASK_PRIO,
                                             NULL,
                                             tskNO_AFFINITY);
	return;
 } 

