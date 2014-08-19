// robot remote commands
// This version is for serial commands

// Command constants 
// Default setting is PID , and special command set different states.

const char MOVE_FORWARD = 'f'; // move forward
const char MOVE_BACK    = 'b'; // move backwards
const char MOVE_LEFT    = 'l'; // move left
const char MOVE_RIGHT   = 'r'; // move right 
const char PIVOT_CW     = 'c'; // rotate 90 degrees CW
const char PIVOT_CCW    = 'C'; // rotate 90 degrees CCW
const char PIVOT_CW_45  = 'q'; // rotate 45 degrees CW
const char PIVOT_CCW_45 = 'Q'; // rotate 45 degrees CCW
const char PIVOT_CW_135 = 'j'; // rotate 135 degrees CW
const char PIVOT_CCW_135= 'J'; // rotate 135 degrees CCW
const char TURNAROUND   = 't'; // rotate 180 degrees (default CW)
const char PIVOT        = 'p'; // rotation angle (minus rotates CCW)
const char GRAB_ONE_TUBE= 'g'; // grab only one tube
const char GRAB_TWO_TUBE= 'G'; // grab the second tube
const char HALT_SLOW    = 'h'; // stop moving
const char HALT_FAST    = 'H'; // stop moving

// not used in this example
const char MOVE_SPEED        = 's'; 
const char MOVE_SLOWER       = 'v'; // reduce speed 
const char MOVE_FASTER       = '^'; // increase speed 
 
int commandState = MOV_STOP;    // what robot is told to do

void remoteService() {
    if(Serial1.available() ) {
        int cmd = Serial1.read();
        Serial.println(cmd);
        processCommand(cmd);   
    }  
}

void processCommand(int cmd) {
  int val = 0;
  if( cmd == PIVOT || cmd == SPEED) {
    val =  Serial1.parseInt();
  }
  processCommand(cmd, val);
}
r
void processCommand(int cmd, int val) {
  byte speed;
  Serial.write(cmd); // echo
  switch(cmd)
  { 
    case GRAB_ONE_TUBE : changeCmdState(GRAB_ONE);     grabOneTube();        break;
 //    case GRAB_TWO_TUBE: changeCmdState(GRAB_TWO);     grabOneTube();        break;  
    case MOVE_FORWARD  : changeCmdState(MOV_FORWARD);  moveForward(val);     break;
    case MOVE_BACK     : changeCmdState(MOV_BACK);     moveBackward(val);    break;
    case PIVOT_CCW     : changeCmdState(MOV_ROTATE_L); turnCountClockwise(); break;
    case PIVOT_CW      : changeCmdState(MOV_ROTATE_R); turnClockwise();      break;
 //  case MOVE_LEFT    : changeCmdState(MOV_LEFT);     moveLeft();          break;
 //  case MOVE_RIGHT   : changeCmdState(MOV_RIGHT);    moveRight();         break;
    case PIVOT         : changeCmdState(MOV_ROTATE);   turnToRight(val);     break; 
    case HALT_SLOW     : changeCmdState(MOV_STOP);     stopSlowly();         break;
    case HALT_FAST     : changeCmdState(MOV_STOP);     stopFastly();         break;
 //  case SPEED        : speed = val;                  moveSetSpeed(speed); break;
  }    
}

void changeCmdState(int newState) {
  if(newState != commandState)  {
    Serial.print("Changing Cmd state from "); Serial.print( states[commandState]);
    Serial.print(" to "); Serial.println(states[newState]);
    commandState = newState;
  } 
}
