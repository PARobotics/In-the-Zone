#ifndef MAIN_H
#define MAIN_H

/*
  MAIN.H
  Holds various variables and wrapper functions
*/

// ** Custom Easy Names **
#define DOWN_WITHOUT_GOAL 10

// ** Global variables **
int LIFT1_VALUE, LIFT2_VALUE, LIFT1_VALUE0, LIFT2_VALUE0, LIFT1_SPEED, LIFT2_SPEED, timeI;
int clawIsClosed = 0;

//Command Flags
int MOBILE_GOAL_COMMAND = 0;
int CONE_LIFT_COMMAND = 0;

// ** Wrapper functions **

//Mobile Goal
void moveMobileGoalLift(int status);
int mobileGoalIsInPlace();
void automaticMobileGoalLift();

//Cone lift
void moveTurntable(int val);
void moveFirstLiftJoint(int status);
int getTurntableValue();
int getTurntableDegrees();
void moveTurntableBy(int degrees, int status, int tlimit);
void moveTurntableToGoal();
void moveTurntableToFront();
void moveClaw(int status);
void moveSecondLiftJoint(int status);
int getFirstLiftValue();
int getSecondLiftValue();
void getLiftValue();
void openClaw();
void closeClaw();

#endif
