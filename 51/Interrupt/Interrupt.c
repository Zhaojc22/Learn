#include<reg52.h>

sbit LED = P0^0;
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char T0RH = 0;
unsigned char T0RL = 0;

unsigned char cnt = 0;
void ConfigTimer0(unsigned int ms);
void main()
{

	EA = 1;
	ENLED = 0;
	ADDR3 = 1;
	ADDR2 = 1;
	ADDR1 = 1;
	ADDR0 = 0;


	ConfigTimer0(20);
	while(1)
	{		
	}
}

void InterruptTimer0() interrupt 1
{
	TF0 = 0;
	TH0 = T0RH;
	TL0 = T0RL;
	cnt++;
	if(cnt >= 50)
	{
	 	cnt = 0;
		LED = ~LED;
	}

}

void ConfigTimer0(unsigned int ms)
{	unsigned long tmp = 0;

	tmp = 11059200 / 12;
	tmp = (tmp * ms) / 1000;
	tmp = 65536 - tmp;
	T0RH = (unsigned char)(tmp >> 8);
	T0RL = (unsigned char)tmp;
	TMOD = 0x01;
	TH0 = T0RH;
 	TL0 = T0RL;
	ET0 = 1;
	TR0 = 1;
}
