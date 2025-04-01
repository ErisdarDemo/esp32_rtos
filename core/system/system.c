/**************************************************************************************************/
/** @file     system.c
 *  @brief    Application system component
 *  @details  x
 */
/**************************************************************************************************/

//Standard Library includes
#include <stdio.h>

//Project Includes
#include "mcu.h"
#include "rtos.h"


/**************************************************************************************************/
/** @fcn        void system_initialize(void)
 *  @brief      Prepare the system for application
 *  @details    x
 *
 *  @pre 	app_main()
 *	@post	System is initialized and prepared for Application requirements
 */
/**************************************************************************************************/
void system_initialize(void) {

	//----------------------------------------- Init MCU -----------------------------------------// 
    mcu_print_info();
	        
	        
    //---------------------------------------- Init RTOS -----------------------------------------//
	rtos_init();

	
	//Notify
	printf("System initialization complete\n");
	
	return;
}

