#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include "bt.h"
#include "btn.h"
#include "rgb_led.h"
#include "servo.h"
#include "mutex.h"

#define BTN_PIO 24

void btnInit(){ // 버튼 초기화
    pinMode(BTN_PIO, INPUT);
}

void* readBtn() {
    while(1) {
        int result = digitalRead(BTN_PIO); // 버튼 입력 감지
        if (result) 
        {
            printf("버튼 입력을 감지했습니다. status: %d\n", result);
            pthread_mutex_lock(&mutex); // 뮤텍스 잠금
            RGBled(0, 255, 255); // LED 점등
            serialWrite(fd_serial, OUT_CHAR); // 블루투스로 "O" 전송
            servoOpen(); // 서보모터 열기
            pthread_mutex_unlock(&mutex); // 뮤텍스 잠금 해제
            delay(100);
        }
    }
}