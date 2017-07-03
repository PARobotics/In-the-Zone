#ifndef MOBILE_GOAL_C
#define MOBILE_GOAL_C

/*
  MOBILE_GOAL.C
  Contains all the code for the mobile goal lift.
*/

void moveMobileGoalLift(int status){ //Manually sets value for mobile goal lift
  if(status == UP) motor[M_MOBILE_GOAL_LIFT] = 127;
  else if(status == DOWN) motor[M_MOBILE_GOAL_LIFT] = -127;
  else if(status == STOP) motor[M_MOBILE_GOAL_LIFT] = 0;
}

int mobileGoalIsInPlace(){ //Returns if the mobile goal has been loaded onto the robot.
  return SensorValue(mobileGoalLimitSwitch);
}

void automaticMobileGoalLift(){
  int t0 = time1[T1];
  moveMobileGoalLift(UP);
  while(!isTimedOut(t0 + 5000) && !mobileGoalIsInPlace() && vexRT[BAILOUT_BUTTON] == 0){
    wait1Msec(10);
  }
  moveMobileGoalLift(STOP);
}

#endif
