#include "Makeblock.h"
#include <SoftwareSerial.h>
#include <Wire.h>

MeEncoderMotor motorLeft(0x8, 0x00);   //  Motor at slot1
MeEncoderMotor motorRight(0x8, 0x01);   //  motor at slot2

const int carSpeed = 60;
const int slowTime = 100;// in millisecond

void setup()
{
    motorLeft.begin();
    motorRight.begin();
    Serial.begin(9600);
    Serial1.begin(115200);
}

void loop()
{
    // startSlowly();
    // straight();
    // stopSlowly();
    turnToDegree(90);
    //delay(3000);
}

// pre: the diameter of the wheel is motorDiameter
//      the radius to turn is DiameterToTurn
//      the angle the motor should turn could be calculated as 
//      motorDiameter * angleMotor =  angleTurning * DiameterToTurn
const int motorDiameter = 63; // in millimeter
const int DiameterToTurn = 1800; // in millimeter

// post: Turning left for the given angle
void turnToDegree(int angleTurning) {
    // stopSlowly();
    int angleTotal = angleTurning * DiameterToTurn / motorDiameter;
    int turnsTotal = angleTotal / 360;
    int angleLeft = angleTotal % 360;
    // motorLeft.RunTurns(turnsTotal, 70);
    // motorRight.RunTurns(turnsTotal, 70);
    // delay(2000);
    serialFeedback();
    motorLeft.MoveTo(angleTotal, 70);
    motorRight.MoveTo(angleTotal, 70);
    serialFeedback();
    delay(1000);
}

void straight() {
    // motorLeft.MoveTo(360*500, carSpeed);
    // motorRight.MoveTo(360*500, -carSpeed);
    motorLeft.RunTurns(50, -carSpeed);
    motorRight.RunTurns(50, carSpeed);
    // delayMicroseconds(1);
    delay(5000);
    // delay(1000);  
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
