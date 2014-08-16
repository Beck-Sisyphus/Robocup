#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Servo.h> //include the Servo library;

//Parts required:Me Servo Driver and two servo 	
//Me Servo Driver PWM1 connect servo1,PWM2connect servo2

MePort port(PORT_1);
Servo arm;  // create servo object to control a servo; The Right side one, now is the blue holding motor
Servo hand;  // create servo object to control another servo
int servo1pin =  port.pin1();//attaches the servo on PORT_1 SLOT1 to the servo object
int servo2pin =  port.pin2();//attaches the servo on PORT_1 SLOT2 to the servo object

const int handOpen = 50;
const int handClose = 115;
const int rise = 90;
const int fall = 40;
const int knock = 0;

void setup()
{
    hand.attach(servo1pin);  // attaches the servo on servopin1
    arm.attach(servo2pin);  // attaches the servo on servopin2
    Serial.begin(9600);
    Serial1.begin(115200);
}

/*
The complete thread to grab the tube
* 1. rise the arm
* 2. moveforward to touch the tube
* 3. detect the color
* 4. fall the arm
* 5. open
*  5.1 knock the grand so the tube can get titer
* 6. detect if we get the tube
* 7. left
*/

const int startGrabSignal = 101;
const int getColorSignal = 102;

void loop() {
    arm.write(rise);
    hand.write(handClose);
    int receivedCommand = Serial.read();
    delay(1000);
    arm.write(fall); 
    delay(1000);  
    hand.write(handOpen);
    delay(1000);
    arm.write(knock);
    delay(200);        
    arm.write(fall);
    delay(1000);
    arm.write(rise);
    delay(3000);  
}

/* Experience note 1:

By the curved designed hand, when pos = 115, the hand is completely handClosed with no conflict
when pos = 50, the hand can early grab an object
*/
