#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h> /* atoi( ) */

#define SPK_PWM 18

void initMyTone();
void myTone(int);