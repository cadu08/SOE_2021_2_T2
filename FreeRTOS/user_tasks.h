#ifndef USER_TASKS_H
#define	USER_TASKS_H

#include <xc.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

void rot_read();
void rot_process(); 

void temp_read();
void temp_process();

#endif	/* USER_TASKS_H */
