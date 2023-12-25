#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define SPK_PWM 18

void initMyTone()
{
    int duty = 0;
    int range = 200;
    int divisor = 96;

    pinMode(SPK_PWM, PWM_OUTPUT); // PWM 출력 설정
    pwmSetMode(PWM_MODE_MS); // PWM 모드 설정
    pwmSetRange(range); // PWM 범위 설정
    pwmSetClock(divisor); // PWM Clock 설정
    pwmWrite(SPK_PWM, duty); // 스피커 음소거
}

void myTone(int freq)
{
    int duty = 50;
    int divisor = 96000 / freq;
    pwmSetClock(divisor); 
    pwmWrite(SPK_PWM, duty); // 스피커 소리 출력
}