#ifndef MOBILE_GOAL_C
#define MOBILE_GOAL_C

/*
  MOBILE_GOAL.C
  Contains all the code for the mobile goal lift.
*/

void moveMobileGoalLift(int status){ //Manually sets value for mobile goal lift
  if(status == UP) motorReq[M_MOBILE_GOAL_LIFT] = 127;
  else if(status == DOWN) motorReq[M_MOBILE_GOAL_LIFT] = -127;
  else if(status == STOP) motorReq[M_MOBILE_GOAL_LIFT] = 0;
  else motorReq[M_MOBILE_GOAL_LIFT] = status;
}

int mobileGoalIsInPlace(){ //Returns if the mobile goal has been loaded onto the robot.
  return SensorValue(mobileGoalLimitSwitch);
}

task mobileGoalTask(){
  while (true) {
    if(MOBILE_GOAL_COMMAND == UP){ //Automatically raises mobile goal into place
      int t0 = time1[T1];
      moveMobileGoalLift(UP);
      while(!isTimedOut(t0 + 5000) && mobileGoalIsInPlace() == 0 && vexRT[BAILOUT_BUTTON] == 0){
     		moveMobileGoalLift(UP);
        wait1Msec(10);
      }
      moveMobileGoalLift(STOP);
      MOBILE_GOAL_COMMAND = STOP;
    }
    else if(MOBILE_GOAL_COMMAND == DOWN){ //Automatically lowers mobile goal stack into place
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
      MOBILE_GOAL_COMMAND = STOP;
    }
    else if(MOBILE_GOAL_COMMAND == DOWN_WITHOUT_GOAL){ //Pushes the lift to ground if it doesn't have a mobile goal
      int t0 = time1[T1];
      moveMobileGoalLift(DOWN);
      while(!isTimedOut(t0 + 2500)){
        moveMobileGoalLift(DOWN);
        wait1Msec(10);
      }
      moveMobileGoalLift(STOP);
      MOBILE_GOAL_COMMAND = STOP;
    }
    else if(MOBILE_GOAL_COMMAND == MANUAL_UP){
      moveMobileGoalLift(UP);
      MOBILE_GOAL_COMMAND = STOP;
    }
    else if(MOBILE_GOAL_COMMAND == MANUAL_DOWN){
      moveMobileGoalLift(DOWN);
      MOBILE_GOAL_COMMAND = STOP;
    }
    else{
      moveMobileGoalLift(STOP);
    }

		wait1Msec(50);
  }
}

#endif
