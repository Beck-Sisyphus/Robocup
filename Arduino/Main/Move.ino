// pre: the diameter of the wheel is motorDiameter
//      the radius to turn is DiameterToTurn
//      the angle the motor should turn could be calculated as 
//      motorDiameter * angleMotor =  angleTurning * DiameterToTurn
// 63 * 3.1416 millimeter per turn
// 63 * 3.1416 / 360 millimeter per degree
// 360 / 63 * 3.1416 degree per millimeter 
// const int motorDiameter = 63; // in millimeter
// const int Pi = 314;

const float mapConstant = 1.8189;

void moveBegin() {
  motorLeft.begin();
  motorRight.begin();
}    

// pre: give the distance between two points
void moveStraight(int millimeter) {
  int degreeToTurn = millimeter * mapConstant;
  // Serial.println(degreeToTurn);
  motorLeft.MoveTo(degreeToTurn, -carSpeed);
  motorRight.MoveTo(degreeToTurn, carSpeed);
  serialFeedback();
  delay(processSpeed);
}


// post: Turning left for the given angle
void turnToDegree(int angleTurning) {
  // stopSlowly();
  // int angleTotal = angleTurning * DiameterToTurn / motorDiameter;
  // int turnsTotal = angleTotal / 360;
  // int angleLeft = angleTotal % 360;
  int angleNow = 0;
  angleNow += 180;
  motorLeft.MoveTo(angleNow, carSpeed);
  motorRight.MoveTo(angleNow, carSpeed);
  serialFeedback();
  delay(processSpeed);
}

const int to90Degree = 587;
const int to270Degree = 1761;
void turnRight(int angleNow) {
  angleNow += to90Degree;
  motorRight.MoveTo(angleNow, carSpeed); 
  motorLeft.MoveTo(angleNow, carSpeed);
  serialFeedback();
  delay(processSpeed);
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
  Serial.print("Right: ");
  Serial.println(motorLeft.GetCurrentPosition());
  Serial.print("Left: ");
  Serial.println(motorRight.GetCurrentPosition());
}

