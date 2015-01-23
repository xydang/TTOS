#include "ttos.h"

task_t task_pool[OS_MAX_TASKS];

void os_init()
{
	uint8_t i;
	for(i=0;i<OS_MAX_TASKS;i++){
		os_del_task(i);
	}
}

void os_start()
{
	uint8_t i;
	while(1){
		for(i=0;i<OS_MAX_TASKS;i++){
			if(task_pool[i].run>0){
				(*task_pool[i].task)();
				task_pool[i].run=0;
			}
			if(task_pool[i].period==0){
				os_del_task(i);
			}
		}
	}
}

uint8_t os_add_task(void (*task)(void),uint16_t delay,uint16_t period)
{
	uint8_t i=0;
	while((task_pool[i].task!=0)&&(i<OS_MAX_TASKS)){
		i++;
	}
	if(i==OS_MAX_TASKS){
		//task is full
		return OS_MAX_TASKS;
	}
	task_pool[i].task=task;
	task_pool[i].delay=delay;
	task_pool[i].period=period;
	task_pool[i].run-=1;
	return i;
}

uint8_t os_del_task(uint8_t task_id)
{
	uint8_t sta;
	if(task_pool[task_id].task==0){
		sta=TASK_DEL_ERROR;
	}else{
		sta=TASK_NORMOL;
	}
	task_pool[task_id].task=0x0000;
	task_pool[task_id].delay=0;
	task_pool[task_id].period=0;
	task_pool[task_id].run=0;
	return sta;
}

void os_systick()
{
	uint8_t i;
	for(i=0;i<OS_MAX_TASKS;i++){
		if(task_pool[i].task){
			if(task_pool[i].delay==0){
				task_pool[i].run+=1;
				if(task_pool[i].period){
					task_pool[i].delay=task_pool[i].period;
				}
			}else{
				task_pool[i].delay-=1;
			}
		}
	}
}
