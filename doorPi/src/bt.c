// **************************
// ** 데이터 보내는 코드**
// **************************
#include "bt.h"

int fd_serial; //디바이스 파일 서술자 

void serialWrite(const int fd, const unsigned char c)
{   //write 함수를 통해 1바이트 씀 
    write(fd, &c, 1); // 1바이트 쓰기
    fflush(stdout); // 표준 출력 버퍼 비우기
    delay(100);
}

int btInit() {
    static const char* UART2_DEV = "/dev/ttyAMA1"; //UART2 연결을 위한 장치 파일

    if ((fd_serial = serialOpen (UART2_DEV, BAUD_RATE)) < 0)
    {// 시리얼 포트 여는거
        printf ("Unable to open serial device.\n");
        return 1;
    }
    return fd_serial;
}
