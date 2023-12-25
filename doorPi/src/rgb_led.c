#include <stdio.h>
#include <unistd.h>
#include <softPwm.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "rgb_led.h"
#include "speaker.h"

#define UC unsigned char

#define R_PIO 11
#define G_PIO 9
#define B_PIO 10

void ledInit()
{
    // PWM 핀 초기화
    softPwmCreate(R_PIO, 0, 255);
    softPwmCreate(G_PIO, 0, 255);
    softPwmCreate(B_PIO, 0, 255);
}

void ledColorSet(UC R_no, UC G_no, UC B_no)
{
    // LED 색상 설정
    softPwmWrite(R_PIO, R_no);
    softPwmWrite(G_PIO, G_no);
    softPwmWrite(B_PIO, B_no);
}

void RGBled(UC R_no, UC G_no, UC B_no)
{
    pinMode(R_PIO, OUTPUT);
    pinMode(G_PIO, OUTPUT);
    pinMode(B_PIO, OUTPUT);

    ledInit();
    
    // LED 색상 설정
    ledColorSet(R_no, G_no, B_no);
    
    myTone(262); // 스피커로 소리 출력(도)
    delay(1000);
    initMyTone(); // 스피커 음소거
    ledColorSet(255, 255, 255); // LED 색상 변경
}
