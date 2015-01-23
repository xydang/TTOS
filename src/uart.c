#include "stc12.h"
#include "uart.h"

bit rx_flag;
unsigned char rx;

void uart_init()
{
    TMOD = 0x20;
    SCON = 0x50;
    TH1 = 0xFD;
    TL1 = TH1;
    PCON = 0x00;
    EA = 1;
    ES = 1;
    TR1 = 1;
}

void uart_write_byte(unsigned char c)
{
    SBUF = c;
    while(!TI);
    TI = 0;
}

void uart_write_str(unsigned char *str)
{
	for(; *str!='\0'; str++)
		uart_write_byte(*str);
}

void uart_write_uint16(unsigned int n)
{
	unsigned char buf[6];
	int i;
	buf[5]='\0';	
	for(i=4;i>-1;i--){
		buf[i]=n%10+'0';
		n/=10;
	}
	uart_write_str(buf);
}

void uart_write_float(float n)
{
	unsigned char buf[8];
	unsigned int i,j;
	if(n<0)
		n=-n;
	i=(unsigned int)n;
	j=n*1000-i*1000;
	buf[5]='\0';
	buf[0]=i/100+'0';
	buf[1]=(i%100)/10+'0';
	buf[2]=(i%100)%10+'0';
	buf[3]='.';
	buf[4]=j/100+'0';

	uart_write_str(buf);
}

void uart_interrupt() interrupt 4
{
    if(RI){
        RI = 0;
		rx=SBUF;
		rx_flag=1;	
    }else
        TI = 0;
}


