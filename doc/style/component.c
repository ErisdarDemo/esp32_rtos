/**************************************************************************************************/
/** @file       component.c
 *  @brief      Component source for operation & control
 *  @details    x
 *
 *  @author     Justin Reina, Firmware Engineer
 *  @created    4/3/25
 *  @last rev   4/19/25
 *
 *  @note   Contents from this template are recommended as needed
 *
 *  @section    Opens
 *      none currents
 *      
 *  @section    API Format
 *      Get/Set    - state
 *      Read/Write - activity
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
#include <string.h>

//Library Includes

//BSP Includes

//Project Includes
#include "component.h"


//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
//************************************************************************************************//

//-----------------------------------------  Definitions -----------------------------------------//


//-------------------------------------------- Macros --------------------------------------------//


//----------------------------------------- Enumerations -----------------------------------------//


//------------------------------------------- Typedefs -------------------------------------------//


//************************************************************************************************//
//                                            VARIABLES                                           //
//************************************************************************************************//

static CompConfig compConfig;                        /* configuration parameter for the component     */


//************************************************************************************************//
//                                       FUNCTION DECLARATIONS                                    //
//************************************************************************************************//


//************************************************************************************************//
//                                          PUBLIC FUNCTIONS                                      //
//************************************************************************************************//

/**************************************************************************************************/
/** @fcn        void component_init(CompConfig *cfg)
 *  @brief      Initialize component for use
 *  @details    x
 *
 *  @param    [in]  (CompConfig *) cfg - component initialization configuration
 *
 *  @pre    system_initialize()
 *  @post   Component is initialized for use
 *
 *  @section    Opens
 *      Define & implement routine
 *      Consider reporting status on post console/log report
 */
/**************************************************************************************************/
void component_init(CompConfig *cfg) {

    //Locals

    
    //---------------------------------------- Initialize ----------------------------------------//


    //------------------------------------------ Operate -----------------------------------------//


    //Notify
    printf("component_init(): Component initialization complete\n");
    
    return;
}


/**************************************************************************************************/
/** @fcn        void component_enable(void)
 *  @brief      Enable Component for use
 *  @details    x
 *
 *  @pre    component_init()
 *  @post   component is enabled for use & output is enabled
 *  
 *  @section    Opens
 *      Define & implement routine
 */
/**************************************************************************************************/
void component_enable(void) {

    //Notify
    printf("component_enable(): Component was enabled\n");

    return;
}


/**************************************************************************************************/
/** @fcn        void component_disable(void)
 *  @brief      Disable component from use
 *  @details    x
 *
 *  @pre    component_init()
 *  @post   component is disabled from use
 *  
 *  @section    Opens
 *      Define & implement routine
 */
/**************************************************************************************************/
 void component_disable(void) {
    
    //Notify
    printf("component_enable(): Component was disabled\n");

    return;
}


/**************************************************************************************************/
/** @fcn        void component_start(void)
 *  @brief      Begin component operations
 *  @details    x
 *
 *  @pre    component_init()
 *  @post   Component is operational & running
 *  
 *  @section    Opens
 *      Define & implement routine
 */
/**************************************************************************************************/
void component_start(void) {

    //Locals


    //---------------------------------------- Initialize ----------------------------------------//


    //------------------------------------------ Operate -----------------------------------------//


    return;
}


/**************************************************************************************************/
/** @fcn        void component_stop(void)
 *  @brief      Stop component operations
 *  @details    x
 *
 *  @pre    component_init()
 *  @post   Component is stopped from operation
 *  
 *  @section    Opens
 *      Define & implement routine
 */
/**************************************************************************************************/
void component_stop(void) {
    
    return;
}


/**************************************************************************************************/
/** @fcn        void *component_status(void)
 *  @brief      Current status of API performance
 *  @details    x
 *
 *  @return   (void *) component status for component api
 *
 *  @pre    any
 *  @post   x
 *  
 *  @section    Opens
 *      Define & implement state & routine
 */
/**************************************************************************************************/
void *component_status(void) {
    
    return NULL;
}


/**************************************************************************************************/
/** @fcn        void component_reset(void)
 *  @brief      Reset component state & operations
 *  @details    x
 *
 *  @pre    component_init()
 *  @post   Component is reset to its initial state condition
 *  
 *  @section    Opens
 *      Define & implement state & routine
 */
/**************************************************************************************************/
void component_reset(void) {
    
    return;
}
 
 
/**************************************************************************************************/
/** @fcn        void component_setConfig(CompConfig *cfg)
 *  @brief      Update configuration value
 *  @details    x
 *
 *  @param    [in]  (CompConfig *) cfg - Component configuration to apply
 *
 *  @pre    component_init()
 *  @post   config value is applied to the component
 *  
 *  @section    Opens
 *      Define & implement state & routine
 */
/**************************************************************************************************/
void component_setConfig(CompConfig *cfg) {

    //Copy value
    memcpy(cfg, &compConfig, sizeof(CompConfig));
    
    //Apply to component

    return;
}
 
 
/**************************************************************************************************/
/** @fcn        CompConfig *component_getConfig(void)
 *  @brief      Applied configuration for use
 *  @details    x
 *
 *  @return   (CompConfig *) component configuration access handle
 *
 *  @pre    any
 *  @post   x
 */
/**************************************************************************************************/
CompConfig *component_getConfig(void) {

    return &compConfig;
}


/**************************************************************************************************/
/** @fcn        void *component_getInfo(void)
 *  @brief      Retrieve component information
 *  @details    e.g. identifiers & specs
 *
 *  @return   (void *) component info access handle
 *
 *  @pre    any
 *  @post   x
 *
 *  @section    Opens
 *      Define & implement state & routine
 */
/**************************************************************************************************/
void *component_getInfo(void) {

    return NULL;
}


/**************************************************************************************************/
/** @fcn        int component_getState(void)
 *  @brief      Retrieve current operational state
 *  @details    e.g. output values
 *
 *  @return   (int) current component value
 *
 *  @pre    any
 *  post    x
 *
 *  @section    Opens
 *      Define & implement state & routine
 */
/**************************************************************************************************/
int component_getState(void) {

    return 0;
}


/**************************************************************************************************/
/** @fcn        void component_setState(int val)
 *  @brief      Apply current operational state
 *  @details    e.g. output values
 *
 *  @param    [in]  (int) val - update component value to set
 *
 *  @pre    component_init()
 *  @post   state value update is applied to the component
 *
 *  @section    Opens
 *      Define & implement state & routine
 */
/**************************************************************************************************/
 void component_setState(int val) {
    
    return;
}


/**************************************************************************************************/
/** @fcn        int component_read(void)
 *  @brief      Read component values
 *  @details    e.g. stream inputs or component state
 *
 *  @return   (int) current component value
 *
 *  @pre    component_init()
 *  @post   x
 *
 *  @section    Opens
 *      Define & implement state & routine
 */
/**************************************************************************************************/
int component_read(void) {

    return 0;
}


/**************************************************************************************************/
/** @fcn        void component_write(int val)
 *  @brief      Write component values
 *  @details    e.g. stream inputs or component state
 *
 *  @param    [in]  (int) update component value to apply
 *
 *  @pre    component_init()
 *  @post   written value is applied to the component
 *
 *  @section    Opens
 *      Define & implement state & routine
 */
/**************************************************************************************************/
void component_write(int val) {

    return;
}


/**************************************************************************************************/
/** @fcn        void *component_getLog(void)
 *  @brief      Retrieve log history for Component operations
 *  @details    x
 *
 *  @return   (void *) log file access handle
 *  
 *  @pre    component_init()
 *
 *  @section    Opens
 *      Define & implement state & routine
 */
/**************************************************************************************************/
void *component_getLog(void) {

    return NULL;
}


/**************************************************************************************************/
/** @fcn        void component_callback(void)
 *  @brief      Default interrupt callback
 *  @details    x
 *
 *  @section    Purpose
 *      Default interrupt handler for secure component use
 *
 *  @pre    component_init()
 *  @post   interrupt vector is reset
 *
 *  @section    Opens
 *      Define & implement component state & routine
 */
/**************************************************************************************************/
void component_callback(void) {

    //Locals


    //------------------------------------------ Prepare -----------------------------------------//


    //------------------------------------------ Operate -----------------------------------------//


    return;
}


//************************************************************************************************//
//                                         PRIVATE FUNCTIONS                                      //
//************************************************************************************************//


