#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;
sbit LED9 = P0^7;
sbit LED8 = P0^6;
sbit LED7 = P0^5;
sbit LED6 = P0^4;

sbit KEY1 = P2^0;
sbit KEY2 = P2^1;
sbit KEY3 = P2^2;
sbit KEY4 = P2^3;

void main()
{
    
    ENLED = 0;   //选择独立LED进行显示
    ADDR3 = 1;
    ADDR2 = 1;
    ADDR1 = 1;
    ADDR0 = 0;

    P2 = 0xEF;   //P2.3置0，即KeyOut1输出低电平

	while (1)
    {
        //将按键扫描引脚的值传递到LED上
        LED9 = KEY1;  //按下时为0，对应的LED点亮
        LED8 = KEY2;
        LED7 = KEY3;
        LED6 = KEY4;
    }
}