#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h> /* atoi( ) */

#define SERVO_PIN 20

#define SERVO_RANGE 200
#define MAX_DEGREE 25
#define NEUTRAL_DEGREE 4
#define MIN_DEGREE 5

void servoInit(void);

void servoOpen(void);