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

#endif
