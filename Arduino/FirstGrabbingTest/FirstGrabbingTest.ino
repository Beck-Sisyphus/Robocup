#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Servo.h> // include the Servo library for grabbing
#include <PID_v1.h>
#include "robotDefines.h"

void setup()
{
    Serial.begin(9600);
    Serial1.begin(115200);
    while (!Serial) {;}
    while (!Serial1) {;}
    Serial.println("Goodnight moon!");
    moveBegin();
    servoBegin();
}

int distance = 0;
void loop()
{
    servoHold();
    delay(processSpeed);
    startSlowly();
    distance += 740;
    moveStraight(distance);
    delay(processSpeed * 10);
    distance += 370;
    moveStraight(distance);
    delay(processSpeed * 5);
    grabOneTube();
    delay(processSpeed);
}

