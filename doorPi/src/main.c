// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <softPwm.h>
// #include <wiringPi.h>
// #include <wiringPiI2C.h>
// #include <nfc/nfc.h>
#include "rgb_led.h"
#include "nfc.h"
#include "touch.h"
#include "bt.h"
#include "btn.h"
#include "speaker.h"
#include "servo.h"
#include <pthread.h>
#include "mutex.h"

int main(void)
{    
    if (wiringPiSetupGpio() == -1) { // wiringPi 초기화
        fprintf(stderr, "wiringPi 초기화에 실패했습니다.\n");
        return 1;
    }

    // PN532 초기화 및 설정
    initializePn532();
    // 터치패드 초기화 및 설정
    touchInit();
    // 블루투스 초기화 및 설정
    btInit();
    // 수동부저 초기화 및 설정
    initMyTone();
    // 서보모터 초기화 및 설정
    servoInit();
    
    // 스레드 생성 및 실행
    pthread_t ptNfc, ptTouch, ptBtn;
    pthread_mutex_init(&mutex, NULL); // 뮤텍스 초기화
    pthread_create(&ptNfc, NULL, readNfcCard, NULL);
    pthread_create(&ptTouch, NULL, readNumPad, NULL);
    pthread_create(&ptBtn, NULL, readBtn, NULL);
    pthread_join(ptNfc, NULL); // 스레드 종료 대기
    pthread_join(ptTouch, NULL);
    pthread_join(ptBtn, NULL);
    pthread_mutex_destroy(&mutex); // 뮤텍스 제거
    
    return 0;
}