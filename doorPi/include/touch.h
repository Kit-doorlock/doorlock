#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include "bt.h"
#include "servo.h"

#define SCL_PIN 8
#define SDO_PIN 7

#define PW_LEN 4
#define TOUCH_NUM "13131313"

void touchInit(void);
void *readNumPad();
void getPassword(char*);
unsigned char readKeypad(void);
void compareNum(char*, const char*);