/*
 * @Author: Zhaojc
 * @Date: 2022-05-26 15:33:15
 * @LastEditTime: 2022-05-26 17:08:14
 * @Descripttion: Traffic light test
 */

#include <reg52.h>

sbit ADDR0 = P1 ^ 0;
sbit ADDR1 = P1 ^ 1;
sbit ADDR2 = P1 ^ 2;
sbit ADDR3 = P1 ^ 3;
sbit ENLED = P1 ^ 4;

sbit LED_SEC = P0 ^ 0;


unsigned char T0RH = 0;
unsigned char T0RL = 0;
void ConfigTimer0(unsigned int ms);
unsigned char cnt = 0;
unsigned char sec = 0;
void main()
{
    EA = 1;
    ENLED = 0;
    ADDR3 = 1;
    ADDR2 = 1;
    ADDR1 = 1;
    ADDR0 = 0;
    P0 &= 0x00;
    P0 |= 0xFE;
    ConfigTimer0(20);
    while (1)
        ;
}

void InterruptTimer0() interrupt 1
{
    TF0 = 0;
    TH0 = T0RH;
    TL0 = T0RL;
    cnt++;
    if (cnt >= 50)
    {
        cnt = 0;
        LED_SEC = ~LED_SEC;
        sec++;
        if (sec < 10)
        {
            P0 &= 0x01;
            P0 |= 0xFC;
        }
        else if (sec < 20)
        {
            P0 &= 0x01;
            P0 |= 0xFA;
        }
        else if (sec < 22)
        {
            P0 &= 0x01;
            P0 |= 0xF6;
        }
        else
        {
            sec = 0;
            P0 &= 0x01;
            P0 |= 0xFE;
        }
    }
}

/**
 * @description: 配置定时器0
 * @param {unsigned int} ms
 * @return {*}
 */
void ConfigTimer0(unsigned int ms)
{
    unsigned long tmp;

    tmp = 11059200 / 12;
    tmp = (tmp * ms) / 1000;
    tmp = 65536 - tmp;
    T0RH = (unsigned char)(tmp >> 8);
    T0RL = (unsigned char)tmp;
    TH0 = T0RH;
    TL0 = T0RL;
    TMOD = 0x01;
    ET0 = 1;
    TR0 = 1;
}
