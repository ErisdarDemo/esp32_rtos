/**************************************************************************************************/
/** @file     component.h
 *  @brief    Component interface for public API
 *  @details  interface file header is typically omitted in preference for source file header
 *
 *  @note   Consider replacing compConfig.comps with dynamic alloc as a ptr
 */
/**************************************************************************************************/
#ifndef DIR_COMPONENT_H
#define DIR_COMPONENT_H

//************************************************************************************************//
//                                            INCLUDES                                            //
//************************************************************************************************//

//Standard Library Includes

//Library Includes

//BSP Includes

//Project Includes


//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
//************************************************************************************************//

//-----------------------------------------  Definitions -----------------------------------------//

#define COMP_NUM_ITEMS    (1)


//-------------------------------------------- Macros --------------------------------------------//


//----------------------------------------- Enumerations -----------------------------------------//


//------------------------------------------- Typedefs -------------------------------------------//

//Setup
typedef struct compConfig {
    int comps[COMP_NUM_ITEMS];                      /* qualifying descrip for comps e.g.  pins    */
    
    int paramOne;                                   /* qualifying descrip for param               */
    int paramTwo;                                   /* qualifying descrip for param               */
    /* .... */  
} CompConfig;


//************************************************************************************************//
//                                            VARIABLES                                           //
//************************************************************************************************//


//************************************************************************************************//
//                                       FUNCTION DECLARATIONS                                    //
//************************************************************************************************//

//-------------------------------------------- Public --------------------------------------------//

//Setup
extern void component_init(CompConfig *cfg);
extern void component_enable(void);
extern void component_disable(void);

//Action
extern void  component_start(void);
extern void  component_stop(void);
extern void *component_status(void);                /* current status of API performance          */
extern void  component_reset(void);

//Configure
extern void        component_setConfig(CompConfig *cfg);
extern CompConfig *component_getConfig(void);       /* applied configuration for use              */
extern void       *component_getInfo(void);         /* current operational state                  */

//Get-Set
extern int  component_getState(void);
extern void component_setState(int val);

//Read-Write
extern int  component_read(void);
extern void component_write(int val);

//Log
extern void *component_getLog(void);

//Int
extern void component_callback(void);               /* default peripheral interrupt callback      */


//-------------------------------------------- Private -------------------------------------------//


#endif /*  DIR_COMPONENT_H */

