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
#define USE_PR_BUTTON  1
#define NUM_PR_BUTTONS  8 //Only include if using remote

#define Btn5U_Partner 0
#define Btn5D_Partner 1
#define Btn7U_Partner 2
#define Btn7L_Partner 3
#define Btn7R_Partner 4
#define Btn8U_Partner 5
#define Btn8D_Partner 6
#define Btn8L_Partner 7

void setUpButtons(){ //Only include if using remote
  addPrButton(Btn5U_Partner, Btn5U);
  addPrButton(Btn5D_Partner, Btn5D);
  addPrButton(Btn7U_Partner, Btn7U);
  addPrButton(Btn7L_Partner, Btn7L);
  addPrButton(Btn7R_Partner, Btn7R);
  addPrButton(Btn8U_Partner, Btn8U);
  addPrButton(Btn8D_Partner, Btn8D);
  addPrButton(Btn8L_Partner, Btn8L);
}

//Configure Sensors
#define USE_SECOND_BATTERY 1

#define USE_LCD 1

void lcdGenerateMessage(){
  sprintf(lcdStr1, "8900 %4.1fV %4.1fV", getMainBatteryVoltage() / 1000.0, getSecondBatteryVoltage() / 1000.0);
  sprintf(lcdStr2, "%4d %4d %3d", getTurntableDegrees(), firstLiftJoint.val, secondLiftJoint.val);
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

#define DEBUG_SENSORS 1

#define BAILOUT_BUTTON Btn7D
void bailOut(){

}

void move(int V, int H, int X){
  motorReq[M_WHEEL_L1] = BOUND(V + H, -127, 127);
  motorReq[M_WHEEL_L2] = BOUND(V + H, -127, 127);
  motorReq[M_WHEEL_R1] = BOUND(V - H, -127, 127);
  motorReq[M_WHEEL_R2] = BOUND(V - H, -127, 127);
}


#endif
