#include "stc12.h"
#include "uart.h"
#include "ttos.h"


void timer_init(void)
{
    TMOD |= 0x01;
    TH0 = 0x0FC;
    TL0 = 0x66;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

void task1()
{
	uart_write_byte('A');
}

void task2()
{
	uart_write_byte('B');
}

void task3()
{
	uart_write_byte('C');
}

void main()
{
	uart_init();
	timer_init();
	uart_write_str("uart init ok.\r\n");
	os_init();
	os_add_task(task1,100,1000);
	os_add_task(task2,200,2000);
	os_add_task(task3,300,3000);
	os_start();
}

void Timer1Interrupt(void) interrupt 1
{
    TH0 = 0x0FC;
    TL0 = 0x66;
    os_systick();
}

