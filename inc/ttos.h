#ifndef __TTOS_H__
#define __TTOS_H__

#ifndef TRUE
#define FALSE 0
#define TRUE (!FALSE)
#endif

#define OSC_FREQ (11059200UL)
#define OSC_PER_INST (6)

#define OS_MAX_TASKS   (3)

#define TASK_ADD_ERROR  2
#define TASK_DEL_ERROR  3
#define TASK_NORMOL		1

typedef char           int8_t;
typedef unsigned char  uint8_t;
typedef int            int16_t;
typedef unsigned int   uint16_t;

typedef struct{
	void (*task)(void);
	uint16_t delay;
	uint16_t period;
	uint8_t  run;
}task_t;

void os_init();
void os_start();
void os_systick();
uint8_t os_add_task(void (* task)(void),uint16_t delay,uint16_t period);
uint8_t os_del_task(uint8_t task_id);


#endif
