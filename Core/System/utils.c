/**************************************************************************************************/
/** @file     utils.c
 *  @brief    Common code utilities
 *  @details  x
 */
/**************************************************************************************************/


//************************************************************************************************//
//                                            INCLUDES                                            //
//************************************************************************************************//

//Standard Library Includes
#include <limits.h>
#include <string.h>
#include <stdio.h>


//************************************************************************************************//
//                                        DEFINITIONS & TYPES                                     //
//************************************************************************************************//

//-----------------------------------------  Definitions -----------------------------------------//
#define PRINTTASK_LEN   (73)                        /* num of chars on the print header           */
#define TASK_STR        (" Task")                   /* Common task display header string          */
#define LOOPHEADER_LEN  (80)


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

