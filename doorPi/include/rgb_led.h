#include <stdio.h>
#include <unistd.h>
#include <softPwm.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "speaker.h"

#define UC unsigned char

#define R_PIO 11
#define G_PIO 9
#define B_PIO 10

void ledInit(void);
void ledColorSet(UC, UC, UC);
void RGBled(UC, UC, UC);