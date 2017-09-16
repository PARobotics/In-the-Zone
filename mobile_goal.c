#ifndef MOBILE_GOAL_C
#define MOBILE_GOAL_C

#define MOBILE_GOAL_BOTTOM_LIMIT  1600
#define MOBILE_GOAL_DEFAULT_V 20
#define MOBILE_GOAL_MIN_V -127
#define MOBILE_GOAL_MAX_V 127
#define MOBILE_GOAL_KP -0.1
#define MOBILE_GOAL_KD -0.02


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
	mobileGoalPID.kp = MOBILE_GOAL_KP;
	mobileGoalPID.kd = MOBILE_GOAL_KD;
	initializeSensor(&mobileGoalLift, 1.0, in3, &mobileGoalPID);
	int mobileGoalAppliedVoltage = 0;

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
      updateSensorValue(&mobileGoalLift);
      while(!isTimedOut(t0 + 2000) && vexRT[BAILOUT_BUTTON] == 0 && mobileGoalLift.val < MOBILE_GOAL_BOTTOM_LIMIT){
      	updateSensorValue(&mobileGoalLift);
      	mobileGoalAppliedVoltage = sensorHold(&mobileGoalLift, MOBILE_GOAL_BOTTOM_LIMIT, MOBILE_GOAL_DEFAULT_V, MOBILE_GOAL_MIN_V, MOBILE_GOAL_MAX_V);
     		moveMobileGoalLift(mobileGoalAppliedVoltage);

				#if DEBUG_MOBILE_GOAL == 1
					writeDebugStreamLine("[MOBILE_GOAL] %d %d %d %d", MOBILE_GOAL_BOTTOM_LIMIT, mobileGoalLift.val, mobileGoalLift.speed, mobileGoalAppliedVoltage);
				#endif

        wait1Msec(10);
      }
      coneNum = 0;
      moveMobileGoalLift(STOP);
      MOBILE_GOAL_COMMAND = STOP;
    }
    else if(MOBILE_GOAL_COMMAND == DOWN_WITHOUT_GOAL){ //Pushes the lift to ground if it doesn't have a mobile goal
      int t0 = time1[T1];
      moveMobileGoalLift(DOWN);
      updateSensorValue(&mobileGoalLift);
      while(!isTimedOut(t0 + 2500) && vexRT[BAILOUT_BUTTON] == 0 && mobileGoalLift.val < MOBILE_GOAL_BOTTOM_LIMIT){
      	updateSensorValue(&mobileGoalLift);
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
