/*
 * SCH_scheduler.c
 *
 * Created: 3/24/2018 3:49:23 AM
 *  Author: mabdelr2
 */ 


#include "SCH_scheduler.h"



extern void SCH_vidSchInit(void)
{
	TIM_vidInitT0();
	
	TIM_vidT0AttachInterrupt(SCH_vidTimIsr);
	
}

void SCH_vidTimIsr(void)
{
	static uint32 u32SysTicks = 0;
	
	if (u32SysTicks % SCH_u32TASK1_PERIOD == 0){
		SCH_vidTask1();
	}
	
	if (u32SysTicks % SCH_u32TASK2_PERIOD == 0){
		SCH_vidTask2();
	}
	
	if (u32SysTicks % SCH_u32TASK3_PERIOD == 0){
		SCH_vidTask3();
	}

	//TODO:: reset u32SysTicks upon reaching the slowest task 
}
