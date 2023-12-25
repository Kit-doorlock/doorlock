#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include "bt.h"
#include "rgb_led.h"
#include "servo.h"

#define BTN_PIO 24

void btnInit();
void* readBtn();