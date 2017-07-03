#ifndef MAIN_H
#define MAIN_H

/*
  MAIN.H
  Holds various variables and wrapper functions
*/


//Wrapper functions

//Mobile Goal
void moveMobileGoalLift(int status);
int mobileGoalIsInPlace();
void automaticMobileGoalLift();

//Cone lift
void moveTurntable(int status);
void moveFirstLiftJoint(int status);

#endif
