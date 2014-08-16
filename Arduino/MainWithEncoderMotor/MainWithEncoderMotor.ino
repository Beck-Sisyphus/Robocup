#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Servo.h> // include the Servo library for grabbing

MePort port(PORT_1);
MeEncoderMotor motorLeft(0x8, 0x00);    //  Motor at PORT_2, slot1
MeEncoderMotor motorRight(0x8, 0x01);   //  motor at PORT_2, slot2

Servo arm;  // create servo object to control a servo; The Right side one, now is the blue holding motor
Servo hand;  // create servo object to control another servo
int servo1pin =  port.pin1();//attaches the servo on PORT_1 SLOT1 to the servo object
int servo2pin =  port.pin2();//attaches the servo on PORT_1 SLOT2 to the servo object

// These constants are for running
const int carSpeed = 60;
const int slowTime = 100;// in millisecond

void setup()
{
    motorLeft.begin();
    motorRight.begin();
    Serial.begin(9600);
    Serial1.begin(115200);
    
    // This part only works for grabing
    hand.attach(servo1pin);  // attaches the servo on servopin1
    arm.attach(servo2pin);  // attaches the servo on servopin2
}

void loop()
{
    // startSlowly();
    moveStraight(300);
    // stopSlowly();
    // turnToDegree(90);
    // turnRight();
    // delay(3000);
    // grabOneTube(); 
}

// pre: the diameter of the wheel is motorDiameter
//      the radius to turn is DiameterToTurn
//      the angle the motor should turn could be calculated as 
//      motorDiameter * angleMotor =  angleTurning * DiameterToTurn
// 63 * 3.1416 millimeter per turn
// 63 * 3.1416 / 360 millimeter per degree
// 360 / 63 * 3.1416 degree per millimeter 

const int motorDiameter = 63; // in millimeter
const int Pi = 314;
const float mapConstant = 1.8189;

void moveStraight(int millimeter) {
    int degreeToTurn = millimeter * 1.8189;
    Serial.println(degreeToTurn);
    motorLeft.MoveTo(degreeToTurn, carSpeed);
    motorRight.MoveTo(-degreeToTurn, -carSpeed);
    serialFeedback();
    delay(1000);
}

int angleNow = 0;
// post: Turning left for the given angle
void turnToDegree(int angleTurning) {
    // stopSlowly();
    // int angleTotal = angleTurning * DiameterToTurn / motorDiameter;
    // int turnsTotal = angleTotal / 360;
    // int angleLeft = angleTotal % 360;
    angleNow += 180;
    motorLeft.MoveTo(angleNow, 70);
    motorRight.MoveTo(angleNow, 70);
    serialFeedback();
    delay(1000);
}

const int to90Degree = 587;
const int to270Degree = 1761;
void turnRight() {
    angleNow += to90Degree;
    motorRight.MoveTo(angleNow, 70); 
    serialFeedback();
    delay(1000);
}

void startSlowly() {
    for (int i = 0; i <= carSpeed / 10 ; i++) {
        int current = i * 10;
        motorLeft.RunSpeedAndTime(-current, slowTime);  
        motorRight.RunSpeedAndTime(current, slowTime);
        Serial.print("current speed: ");
        Serial.println(current);
        delay(slowTime);
    }
    motorLeft.RunSpeed(carSpeed);
    motorRight.RunSpeed(carSpeed);
    delay(slowTime);
}

// post: return the distance it takes to stop this car, 
//              in millimeter
int stopSlowly() {
    float currentSpeedL = motorLeft.GetCurrentSpeed();
    float currentSpeedR = motorRight.GetCurrentSpeed();
    float startSpeed = min(currentSpeedL, currentSpeedR); 
    for (int i = startSpeed / 10; i >= 0 ; i--) {
        int current = i * 10;
        motorLeft.RunSpeedAndTime(-current, slowTime);  
        motorRight.RunSpeedAndTime(current, slowTime);
        Serial.print("current speed: ");
        Serial.println(current);
        delay(slowTime);
    }
    motorLeft.RunSpeed(0);
    motorRight.RunSpeed(0);
    delay(slowTime);
    return 0;
}

void serialFeedback() {
    Serial.println("Right: ");
    Serial.println(motorLeft.GetCurrentPosition());
    Serial.println("Left: ");
    Serial.println(motorRight.GetCurrentPosition());
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

// These constants are for grabing
const int handOpen = 50;
const int handClose = 115;
const int rise = 90;
const int fall = 40;
const int knock = 0;
const int startGrabSignal = 101;
const int getColorSignal = 102;

void grabOneTube() {
    arm.write(fall);
    hand.write(handClose);
    int receivedCommand = Serial1.read();
    if (receivedCommand == startGrabSignal){
        
        arm.write(rise);
        delay(500); 
        
        // moveStraight(40); // this command wasn't built yet
        delay(1000);
        
        receivedCommand = Serial1.read();
        while (receivedCommand != getColorSignal) {
            delay(100);
            receivedCommand = Serial1.read();
        }
        
        arm.write(fall);
        delay(1000);
        
        hand.write(handOpen);
        delay(1000);  
        
        arm.write(knock);
        delay(200);        
        arm.write(fall);
        delay(1000);
        arm.write(rise);
        delay(1000);
    }
}
