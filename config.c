#ifndef CONFIG_C
#define CONFIG_C


//Configure preauton
void preAutonProcedure(){
  //This code runs during preauton
}

void userControlProcedure(){
  //This code executes inside the user control while loop
}


//Set up push release buttons
#define USE_PR_BUTTON  0
#define NUM_PR_BUTTONS  1 //Only include if using remote
void setUpButtons(){ //Only include if using remote

}

//Configure Sensors
#define USE_SECOND_BATTERY 1

#define USE_LCD  1

void lcdGenerateMessage(){
  sprintf(lcdStr1, "8900 %4.1fV %4.1fV", getMainBatteryVoltage() / 1000.0, getSecondBatteryVoltage() / 1000.0);
  sprintf(lcdStr2, "%d   ", getTurntableDegrees());
}

/*
  MOTOR CONTROL
*/

//Slew Rate
#define USE_SLEW  1 //Disable if slew interferes with move functions or slows robot down
int MOTOR_SLEW[MOTOR_NUM] = {255, 40, 40, 255, 255, 255, 255, 40, 40, 255};

#define USE_MONITOR 0//Toggles the monitor task (Necessary for move functions, should be disabled otherwise)


//Move functions

void getWheelVal(){
  DRV.raw[X_POS] = 0;
  DRV.raw[Y_POS] = 0;
  DRV.raw[THETA] = 0;
}

/*
  SENSORS
*/


/*
  DEBUGGING TOGGLES
*/
#define DEBUG  0
#define DEBUG_SLEW  0
#define DEBUG_REMOTE 0
#define DEBUG_MONITOR  0
#define DEBUG_WHEEL   0
#define DEBUG_SENSORS    0

#define USE_BAILOUT 0
#define BAILOUT_BUTTON Btn7D

void move(int V, int H, int X){
  motorReq[M_WHEEL_L1] = BOUND(V + H, -127, 127);
  motorReq[M_WHEEL_L2] = BOUND(V + H, -127, 127);
  motorReq[M_WHEEL_R1] = BOUND(V - H, -127, 127);
  motorReq[M_WHEEL_R2] = BOUND(V - H, -127, 127);
}

#endif
