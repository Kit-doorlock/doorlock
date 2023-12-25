#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include "bt.h"
#include "servo.h"
#include "touch.h"
#include "rgb_led.h"
#include "mutex.h"

#define SCL_PIN 8
#define SDO_PIN 7

#define PW_LEN 4
#define TOUCH_NUM "13131313"

void touchInit()
{
    pinMode(SCL_PIN, OUTPUT); // SCL (SCK)
    pinMode(SDO_PIN, INPUT); // SDO (MISO)
    printf("HW136 터치패드 초기화 완료\n");
}

void *readNumPad(){
    wiringPiSetupGpio();
    initMyTone(); // 터치패드 인식 시 소리 출력을 위한 초기화
    printf("터치패드 인식 기다리는 중...\n");
    const char *expectedNum = TOUCH_NUM;

    while(1){
        char password[32];
        getPassword(password); // 터치패드 인식
        printf("인식 번호: %s\n", password);
        compareNum(password, expectedNum); // 인식 번호와 기대 번호 비교
        printf("터치패드 인식 기다리는 중...\n");
    }
}

void getPassword(char *password)
{
    wiringPiSetupGpio();
    unsigned char Key[PW_LEN];

    for(int i = 0; i < PW_LEN; i++){
        while (readKeypad() == 0x00); // 키 입력 대기
        Key[i] = readKeypad(); // 키 입력
        printf("%d", Key[i]); // 키 입력 출력
        fflush(stdout); // 키 입력 출력 버퍼 비우기
        RGBled(255, 0, 255); // 터치패드 인식 시 RGB LED 색 변경
        delay(1000);
    }
    printf("\n");

    sprintf(password, "%02d%02d%02d%02d", Key[0], Key[1], Key[2], Key[3]); // 터치패드 인식 번호 문자열로 변환
    // printf("%s\n", password);
}

unsigned char readKeypad()
{
    unsigned char Count;
    unsigned char Key_State = 0;

    for (Count = 1; Count <= 16; Count++) // 16개의 키 입력 대기
    {
        digitalWrite(SCL_PIN, LOW); // SCL 핀 LOW

        if (!digitalRead(SDO_PIN)) // SDO 핀이 LOW면
            Key_State = Count; // Key_State에 Count 저장

        digitalWrite(SCL_PIN, HIGH); // SCL 핀 HIGH
    }

    return Key_State;
}

void compareNum(char* password, const char* expectedNum) {
    if (strcmp(password, expectedNum) == 0) { // 인식 번호와 기대 번호가 같으면
        printf("올바른 번호를 감지했습니다.\n");
        pthread_mutex_lock(&mutex); // 뮤텍스 잠금
        RGBled(0, 255, 255); // LED 점등
        serialWrite(fd_serial, IN_CHAR); // 블루투스로 'I' 전송
        servoOpen(); // 서보모터 열기
        pthread_mutex_unlock(&mutex); // 뮤텍스 잠금 해제
        delay(1000);
    } else {
        printf("올바르지 않은 번호를 감지했습니다.\n");
        RGBled(255, 255, 0); // LED 점등
        delay(1000);
    }
}