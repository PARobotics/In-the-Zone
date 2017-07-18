#ifndef MAIN_H
#define MAIN_H

/*
  MAIN.H
  Holds various variables and wrapper functions
*/

// ** Constants **
#define CONE_LIFT1_MAX_V 60
#define CONE_LIFT1_MIN_V -40
#define CONE_LIFT1_DEFAULT_V 30
#define CONE_LIFT1_KX 0.1
#define CONE_LIFT1_KV 0.1

#define CONE_LIFT2_MAX_V 80
#define CONE_LIFT2_MIN_V -20
#define CONE_LIFT2_DEFAULT_V 50
#define CONE_LIFT2_KX 0.1
#define CONE_LIFT2_KV 0.1


// ** Custom Easy Names **
#define DOWN_WITHOUT_GOAL 10

// ** Global variables **
int LIFT1_VALUE = 0;
int LIFT2_VALUE = 0;
int LIFT1_VALUE0 = 0;
int LIFT2_VALUE0 = 0;
int LIFT1_SPEED = 0;
int LIFT2_SPEED = 0;
int timeI = 0;
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
