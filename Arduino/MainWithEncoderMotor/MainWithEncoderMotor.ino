#include <Makeblock.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Servo.h>

MePort port(PORT_1);
MeEncoderMotor motorLeft(0x8, 0x00);   //  Motor at slot1
MeEncoderMotor motorRight(0x8, 0x01);   //  motor at slot2

Servo arm;  // create servo object to control a servo; The Right side one, now is the blue holding motor
Servo hand;  // create servo object to control another servo
int servo2pin =  port.pin1();//attaches the servo on PORT_1 SLOT1 to the servo object
int servo1pin =  port.pin2();//attaches the servo on PORT_1 SLOT2 to the servo object

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
    arm.attach(servo1pin);  // attaches the servo on servopin1
    hand.attach(servo2pin);  // attaches the servo on servopin2
    Serial.begin(9600);
}

void loop()
{
    // startSlowly();
    // moveStraight();
    // stopSlowly();
    // turnToDegree(90);
    turnRight();
    // delay(3000);
    grabOneTube(); 
}

// pre: the diameter of the wheel is motorDiameter
//      the radius to turn is DiameterToTurn
//      the angle the motor should turn could be calculated as 
//      motorDiameter * angleMotor =  angleTurning * DiameterToTurn
const int motorDiameter = 63; // in millimeter
const int DiameterToTurn = 1800; // in millimeter

int angleNow = 0;
// post: Turning left for the given angle
void turnToDegree(int angleTurning) {
    // stopSlowly();
    int angleTotal = angleTurning * DiameterToTurn / motorDiameter;
    int turnsTotal = angleTotal / 360;
    int angleLeft = angleTotal % 360;
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

void moveStraight() {
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

// These constants are for grabing
const int handOpen = 50;
const int handClose = 115;
const int rise = 90;
const int fall = 30;

void grabOneTube() {
    arm.write(fall);
    // delay(500);
    // hand.write(handOpen);
    delay(1000); 
    hand.write(handClose);
}
