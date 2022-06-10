#include<reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code LedChar[] = {
	0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
	0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
};
unsigned char LedBuffer[6] = {
  	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

void main()
{
	unsigned char LedPos = 0;
	unsigned int cnt = 0;
	unsigned long index = 0;

	ENLED = 0;
	ADDR3 = 1;

	TMOD = 0x01;
	TH0 = 0xFC;
	TL0 = 0x17;
	TR0 = 1;

	while(1)
	{
		if(TF0 == 1)
		{
			TF0 = 0;
			TH0 = 0xFC;
			TL0 = 0x17;

			cnt++;
			if(cnt >= 1000)
			{
				cnt = 0;
				index++;
				LedBuffer[0] = LedChar[index%10];
				LedBuffer[1] = LedChar[index/10%10];
				LedBuffer[2] = LedChar[index/100%10];
				LedBuffer[3] = LedChar[index/1000%10];
				LedBuffer[4] = LedChar[index/10000%10];
				LedBuffer[5] = LedChar[index/100000%10];
			}

			if(LedPos == 0)
			{	ADDR2 = 0; ADDR1=0; ADDR0=0; LedPos++; P0 = LedBuffer[0]; }
			else if(LedPos == 1)
			{	ADDR2 = 0; ADDR1=0; ADDR0=1; LedPos++; P0 = LedBuffer[1]; }
			else if(LedPos == 2)
			{	ADDR2 = 0; ADDR1=1; ADDR0=0; LedPos++; P0 = LedBuffer[2]; }
			else if(LedPos == 3)
			{	ADDR2 = 0; ADDR1=1; ADDR0=1; LedPos++; P0 = LedBuffer[3]; }
			else if(LedPos == 4)
			{	ADDR2 = 1; ADDR1=0; ADDR0=0; LedPos++; P0 = LedBuffer[4]; }
			else if(LedPos == 5)
			{	ADDR2 = 1; ADDR1=0; ADDR0=1; LedPos=0; P0 = LedBuffer[5]; }
		}
	}
}