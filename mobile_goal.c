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
  else motor[M_MOBILE_GOAL_LIFT] = status;
}

int mobileGoalIsInPlace(){ //Returns if the mobile goal has been loaded onto the robot.
  return SensorValue(mobileGoalLimitSwitch);
}

void automaticMobileGoalLift(){ //Automatically raises mobile goal into place
  int t0 = time1[T1];
  moveMobileGoalLift(UP);
  while(!isTimedOut(t0 + 5000) && mobileGoalIsInPlace() == 0 && vexRT[BAILOUT_BUTTON] == 0){
 		moveMobileGoalLift(UP);
    wait1Msec(10);
  }
  moveMobileGoalLift(STOP);
}

void automaticMobileGoalScore(){ //Automatically lowers mobile goal into place
	int t0 = time1[T1];
  moveMobileGoalLift(DOWN);
  while(!isTimedOut(t0 + 1200)){
 		moveMobileGoalLift(DOWN);
    wait1Msec(10);
  }
  t0 = time1[T1];
  while(!isTimedOut(t0 + 300)){
  	moveMobileGoalLift(-30);
    wait1Msec(10);
	}
	t0 = time1[T1];
  while(!isTimedOut(t0 + 200)){
  	moveMobileGoalLift(30);
    wait1Msec(10);
	}
  moveMobileGoalLift(STOP);
}

#endif
