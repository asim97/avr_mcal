/*
 * SCH_scheduler.h
 *
 * Created: 3/24/2018 3:48:59 AM
 *  Author: mabdelr2
 */ 


#ifndef SCH_SCHEDULER_H_
#define SCH_SCHEDULER_H_

#include "MCU.h"
#include "TIM_timers.h"
#include "SCH_tasks.h"

typedef void (*TaskFunction)();
extern void SCH_vidTimIsr(void);

#endif /* SCH_SCHEDULER_H_ */