#ifndef __UART_H__
#define __UART_H__

void uart_init();
void uart_write_byte(unsigned char c);
void uart_write_str(unsigned char *str);
void uart_write_uint16(unsigned int n);
void uart_write_float(float n);

extern unsigned char rx;
extern bit rx_flag;

#endif
