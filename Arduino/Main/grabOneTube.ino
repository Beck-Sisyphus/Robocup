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
// const int endGrabSignal = 102;
void servoBegin() {
    // This part only works for grabing
    hand.attach(servo1pin);  // attaches the servo on servopin1
    arm.attach(servo2pin);  // attaches the servo on servopin2
    head.attach(headServo);
}

void servoHold() {
    hand.write(handClose);
    delay(100);
    arm.write(rise);
    delay(100);
    head.write(90);
    delay(300);
}
void grabOneTube() {
   //moveStraight(40); 
   //delay(1000);
            
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
