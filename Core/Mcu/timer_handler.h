/**
 * @todo 	style.h
 */
#ifndef CORE_MCU_TIMER_HANDLER_H_
#define CORE_MCU_TIMER_HANDLER_H_

//Standard Library Includes
#include <stdint.h>

//Definitions
#define TIMER_UNSET_VALUE		(INT64_MIN)

//Global Routines
extern void timer_init(void);
extern uint64_t timer_getCount(void);

#endif /* CORE_MCU_TIMER_HANDLER_H_ */
