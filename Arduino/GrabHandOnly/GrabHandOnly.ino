/*************************************************************************
* File Name          : TestServoDriver.ino
* Author             : Evan
* Updated            : xiayu
* Version            : V1.0.1
* Date               : 6/23/2013
* Description        :  Using Me Servo Driver module connecting two servos.
                        The module only can be connected to  PORT_1 and PORT_2 .
                        
* License            : CC-BY-SA 3.0
* Copyright (C) 2013 Maker Works Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/
#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

//Parts required:Me Servo Driver and two servo 	
//Me Servo Driver PWM1 connect servo1,PWM2connect servo2

#include <Servo.h> //include the Servo library;
MePort port(PORT_1);
Servo arm;  // create servo object to control a servo; The Right side one, now is the blue holding motor
Servo hand;  // create servo object to control another servo
int servo2pin =  port.pin1();//attaches the servo on PORT_1 SLOT1 to the servo object
int servo1pin =  port.pin2();//attaches the servo on PORT_1 SLOT2 to the servo object

int handOpen = 50;
int handClose = 115;
int rise = 90;
int fall = 20;

int counter = 0;

void setup()
{
  arm.attach(servo1pin);  // attaches the servo on servopin1
  hand.attach(servo2pin);  // attaches the servo on servopin2
  Serial.begin(9600);
}

/*
The complete thread to grab the tube
* 1. rise the arm
* 2. moveforward to touch the tube
* 3. detect the color
* 4. fall the arm
* 5. open
* 6. detect if we get the tube
* 7. left
*/
void loop()
{
    arm.write(20);
    delay(500);
   // arm.write(handOpen);// 
    hand.write(handOpen);
    delay(1000);  // Wait for the servo rotation to the set position
    arm.write(90);
    //hand.write(handClose);
    delay(10000);  // Wait for the servo rotation to the set position
}

/* Experience note 1:

By the curved designed hand, when pos = 115, the hand is completely handClosed with no conflict
when pos = 50, the hand can early grab an object
*/
