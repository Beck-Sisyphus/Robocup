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

void loop() {
    moveForward(40);
    servoRise();
    delay(processSpeed * 3);
    Serial1.flush();
    while (!remoteService()) {
       Serial.print("Wait");
       delay(100); 
    }
    grabOneTube();
    delay(processSpeed * 10);
    Serial.println();
    releaseOneTube();
    delay(processSpeed * 10);
    moveBackward(40);
}

