#include <stdio.h>
#include <stdlib.h>
#include <nfc/nfc.h>
#include <wiringPi.h>
#include <string.h>
#include "bt.h"
#include "servo.h"

#define NFC_UID "ac08796d"

void initializePn532(void);
void *readNfcCard();
void getCurrentUid(unsigned char*, char*);
void compareUid(char*, const char*);