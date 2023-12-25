#include <stdio.h>
#include <stdlib.h>
#include <nfc/nfc.h>
#include <wiringPi.h>
#include <string.h>
#include "nfc.h"
#include "rgb_led.h"
#include "bt.h"
#include "speaker.h"
#include "mutex.h"

#define NFC_UID "ac08796d"

// PN532 초기화 함수
void initializePn532() {
    nfc_context *context; // NFC 컨텍스트(환경)
    nfc_device *pnd; // NFC 장치(리더기)

    // libnfc 초기화 및 리더기 설정
    nfc_init(&context);
    if (context == NULL) {
        fprintf(stderr, "libnfc 초기화에 실패했습니다. (malloc)\n");
        exit(EXIT_FAILURE);
    }

    // 첫 번째로 발견된 NFC 장치 열기
    pnd = nfc_open(context, NULL);
    if (pnd == NULL) {
        fprintf(stderr, "NFC 장치 열기에 실패했습니다.\n");
        nfc_exit(context);
        exit(EXIT_FAILURE);
    }

    // PN532 NFC 리더기 초기화
    nfc_device_set_property_int(pnd, NP_HANDLE_CRC, 1); // CRC 사용 (CRC: 데이터 전송 시 오류 검출을 위한 코드)
    nfc_device_set_property_int(pnd, NP_ACTIVATE_FIELD, 1); // 필드 활성화(활성화하지 않으면 통신 불가)

    printf("PN532 NFC 리더기 초기화 완료\n");
}

// NFC 카드 읽기 함수
void *readNfcCard() {
    nfc_target nt; // NFC 타겟(카드)
    nfc_context *context; // NFC 컨텍스트(환경)
    nfc_device *pnd; // NFC 장치(리더기)
    nfc_modulation modulation; // NFC 모듈레이션(통신 속도, 통신 방식)

    // libnfc 초기화 및 리더기 설정
    nfc_init(&context);
    if (context == NULL) {
        fprintf(stderr, "libnfc 초기화에 실패했습니다. (malloc)\n");
        exit(EXIT_FAILURE);
    }

    // 첫 번째로 발견된 NFC 장치 열기
    pnd = nfc_open(context, NULL);
    if (pnd == NULL) {
        fprintf(stderr, "NFC 장치 열기에 실패했습니다.\n");
        nfc_exit(context);
        exit(EXIT_FAILURE);
    }

    // NFC 타겟 대기
    printf("NFC 카드를 기다리는 중...\n");

    // ISO14443A (MIFARE)를 위한 모드 설정 (ISO14443A: NFC 표준 중 하나)
    modulation.nmt = NMT_ISO14443A;
    modulation.nbr = NBR_106; // 통신 속도 106kbps

    const char *expectedUID = NFC_UID; // 기대하는 카드 UID

    // NFC 타겟 선택
    while (true) {
        if (nfc_initiator_select_passive_target(pnd, modulation, NULL, 0, &nt) > 0) { // NFC 타겟이 발견되면
          char currentUID[32];  // 현재 카드 UID
          getCurrentUid(nt.nti.nai.abtUid, currentUID); // 현재 카드 UID 가져오기
          // 카드 UID 출력
          printf("카드 UID: %s\n", currentUID); // 현재 카드 UID 출력
          compareUid(currentUID, expectedUID); // 현재 카드 UID와 저장해 놓은 카드 UID 비교
        }
        delay(1000);
    }

    // NFC 장치 닫기
    nfc_close(pnd);
    nfc_exit(context);
}

void getCurrentUid(unsigned char* abtUid, char* currentUID) {
  sprintf(currentUID, "%02x%02x%02x%02x", abtUid[0], abtUid[1], abtUid[2], abtUid[3]); // abtUid[0]~abtUid[3]까지 16진수로 변환하여 currentUID에 저장
}

void compareUid(char* currentUID, const char* expectedUID) {
  if (strcmp(currentUID, expectedUID) == 0) { // 현재 카드 UID와 저장해 놓은 카드 UID가 같으면
    printf("올바른 카드를 감지했습니다.\n");
    pthread_mutex_lock(&mutex); // 뮤텍스 잠금
    RGBled(0, 255, 255); // LED 점등
    serialWrite(fd_serial, IN_CHAR); // 블루투스로 'I' 전송
    servoOpen(); // 서보모터 열기
    pthread_mutex_unlock(&mutex); // 뮤텍스 잠금 해제
    delay(1000);
  } else {  
    printf("올바르지 않은 카드를 감지했습니다.\n");
    RGBled(255, 255, 0); // LED 점등
    delay(1000);
  }
}