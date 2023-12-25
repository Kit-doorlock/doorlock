#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include "servo.h"

void servoInit()
{
    pinMode(SERVO_PIN, OUTPUT); // 서보모터 핀을 출력으로 설정
    softPwmCreate(SERVO_PIN, NEUTRAL_DEGREE, SERVO_RANGE); // softPWM 핀 초기화
}

void servoOpen()
{
    softPwmWrite(SERVO_PIN, MAX_DEGREE); // 서보모터를 최대로 회전
    delay(4000);

    softPwmWrite(SERVO_PIN, NEUTRAL_DEGREE); // 서보모터를 중앙으로 회전
    delay(1000);
}
