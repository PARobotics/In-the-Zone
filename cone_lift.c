#ifndef CONE_LIFT_C
#define CONE_LIFT_C

/*
  CONE_LIFT.C
  Contains all the code for the cone claw and lift
*/

// ** Turntable **
int ticksToDegrees(int ticks){
  int degrees = (ticks * 360 * 10 * 12 / RPM_393_HS / 66) % 3600; //Make sure degrees dont overflow past 360 degrees

  if(degrees < 0) degrees += 3600;

  return degrees;
}

int degreesToTicks(int degrees){
  int ticks = degrees * 66 * RPM_393_HS / 360 / 10 / 12;

  return ticks;
}

int getTurntableDegrees(){ //Returns the degree value of the turntable in units of 0.1 degrees
  return ticksToDegrees(turntable.val);
}

void moveTurntable(int val){ //Manually controls the turntable rotation
  if(val == CLOCKWISE) motorReq[M_TURNTABLE] = 127;
  else if(val == COUNTERCLOCKWISE) motorReq[M_TURNTABLE] = -127;
  else if(val == STOP) motorReq[M_TURNTABLE] = 0;
  else motorReq[M_TURNTABLE] = val;
}

void moveTurntableBy(int degrees, int status, int tlimit){ //Automatically rotates the turntable by x degrees (parameter is in units of 0.1 degrees)
  updateSensorValue(&turntable);

  int target = turntable.val + status * abs(degreesToTicks(degrees));

  int t0 = time1[T1];

  moveTurntable(status * 80);

  int distanceToTarget = 0;

  int vcmd;

  while(vexRT[BAILOUT_BUTTON] == 0 && !isTimedOut(t0 + tlimit)){ //TODO: Make this a real p control
    updateSensorValue(&turntable);

    vcmd = sensorPDControl(&turntable, target, 0);

    #if DEBUG_CONE_LIFT == 1
      writeDebugStreamLine("[TURNTABLE] %4d %4d %4d %3d", target, turntable.val, turntable.speed, vcmd);
    #endif

    moveTurntable(vcmd);

    wait1Msec(10);
  }

  moveTurntable(STOP);
}

void moveTurntableToGoal(){ //Automatically snaps the turntable back to the mobile goal position
  int currentTheta = getTurntableDegrees();

  if(currentTheta <= 1800){
    //Counterclockwise
    moveTurntableBy(currentTheta, COUNTERCLOCKWISE, 1500);
  }
  else{
    //Clockwise
    moveTurntableBy(3600 - currentTheta, CLOCKWISE, 1500);
  }
}

void moveTurntableToFront(){ //Automatically snaps the turntable to the front
  int currentTheta = getTurntableDegrees();
  int desiredTheta = 1800;

  if(currentTheta <= 1800){
  	//Clockwise
  	moveTurntableBy(desiredTheta - currentTheta, CLOCKWISE, 1500);
	}
	else{
		moveTurntableBy(currentTheta - desiredTheta, COUNTERCLOCKWISE, 1500);
	}
}

// ** Claw **
void moveClaw(int status){ //Manually opens and closes the claw
  if(status == CLOSE) motorReq[M_CLAW] = 127;
  else if(status == OPEN) motorReq[M_CLAW] = -127;
  else if(status == STOP) motorReq[M_CLAW] = 0;
  else motorReq[M_CLAW] = status;
}

void openClaw(){ //Automatically opens the claw
  int t0 = time1[T1];
  moveClaw(OPEN);
  clawIsClosed = 0;
  clawIsOpened = 1;
  while(!isTimedOut(t0 + 150)){
    moveClaw(OPEN);
    wait1Msec(10);
  }
  moveClaw(STOP);
}

void closeClaw(){ //Automatically closes the claw
  int t0 = time1[T1];
  moveClaw(CLOSE);
  clawIsClosed = 1;
  clawIsOpened = 0;
  while(!isTimedOut(t0 +400)){
    moveClaw(100);
    wait1Msec(10);
  }
}

// ** Lift **
void moveFirstLiftJoint(int status){ //Manually controls the first lift joint
  if(status == UP){
    motorReq[M_FIRST_LIFT1] = 127;
    motorReq[M_FIRST_LIFT2] = 127;
  }
  else if(status == DOWN){
    motorReq[M_FIRST_LIFT1] = -127;
    motorReq[M_FIRST_LIFT2] = -127;
  }
  else if(status == STOP){
    motorReq[M_FIRST_LIFT1] = 0;
    motorReq[M_FIRST_LIFT2] = 0;
  }
  else{
    motorReq[M_FIRST_LIFT1] = status;
    motorReq[M_FIRST_LIFT2] = status;
  }
}

void moveSecondLiftJoint(int status){ //Manually controls the second lift joint
  if(status == UP) motorReq[M_SECOND_LIFT] = 127;
  else if(status == DOWN) motorReq[M_SECOND_LIFT] = -127;
  else if(status == STOP) motorReq[M_SECOND_LIFT] = 0;
  else motorReq[M_SECOND_LIFT] = status;
}

void moveLiftUp(){ //Increments the cone lift's height up one
  if(coneNum < 10){
    coneNum++;
    CONE_LIFT_COMMAND = MOVE;
  }
}

void moveLiftDown(){ //Decrements the cone lift's height up one
  if(coneNum > 0){
    coneNum--;
    CONE_LIFT_COMMAND = MOVE;
  }
}

void moveLiftToPreset(int firstVal, int secondVal){
  firstLiftVal = firstVal;
  secondLiftVal = secondVal;
  CONE_LIFT_COMMAND = PRESET;
}

void moveLiftTo(int firstVal, int secondVal, int tlimit){ //Swings the lift to the preset
  int tnow = time1[T1];
  int appliedVoltages[2] = {0, 0};

  int dbgCnt = 0;

  while(BAILOUT == 0 &&!isTimedOut(tnow + tlimit)){
  	updateSensorValue(&firstLiftJoint);
    updateSensorValue(&secondLiftJoint);

    appliedVoltages[0] = sensorHold(&firstLiftJoint, firstVal, CONE_LIFT1_DEFAULT_V, CONE_LIFT1_MIN_V, CONE_LIFT1_MAX_V);
    appliedVoltages[1] = sensorHold(&secondLiftJoint, secondVal, CONE_LIFT2_DEFAULT_V, CONE_LIFT2_MIN_V, CONE_LIFT2_MAX_V);

    #if DEBUG_CONE_LIFT == 1
      if(dbgCnt == 10){
        writeDebugStreamLine("[LIFT 1] %d %d %d %d", firstVal, firstLiftJoint.val, firstLiftJoint.speed, appliedVoltages[0]);
  		  writeDebugStreamLine("[LIFT 2] %d %d %d %d", secondVal, secondLiftJoint.val, secondLiftJoint.speed, appliedVoltages[1]);

        dbgCnt = 0;
      }
      else dbgCnt++;
    #endif

    moveFirstLiftJoint(appliedVoltages[0]);
    moveSecondLiftJoint(appliedVoltages[1]);

    wait1Msec(10);
  }

  CONE_LIFT_COMMAND = HOLD;
}

task coneLiftTask(){ //Controls the position of the lift continuously
  int targetVals[2] = {0, 0};
  int appliedVoltages[2] = {0, 0};

  //Store values for the lifting up and down
  int firstLiftValsForLifting[] = {1116, 1210, 1269, 1283, 1337, 1320, 1320, 1276, 1250, 1195, 1162};
  int secondLiftValsForLifting[] = {3050, 3010, 2950, 2870, 2800, 2700, 2580, 2470, 2300, 2140, 1720};

  pid firstPid, secondPid, turntablePid;
  firstPid.kp = CONE_LIFT1_KX;
  firstPid.kd = CONE_LIFT1_KV;

  secondPid.kp = CONE_LIFT2_KX;
  secondPid.kd = CONE_LIFT2_KV;

  turntablePid.kp = TURNTABLE_KP;
  turntablePid.kd = TURNTABLE_KD;

  initializeSensor(&firstLiftJoint, 720.0 / RPM_393_HS, I2C_2, &firstPid); //Overclocked 1 to 5 gear ratio
  initializeSensor(&secondLiftJoint, 10.0, dgtl6, &secondPid); //Underclocked 1 to 3 gear ratio
  initializeSensor(&turntable, 1.0, I2C_1, &turntablePid); //Underclocked 1 to 3 gear ratio

  writeDebugStreamLine("Default: %d Min: %d Max: %d KP : %.2f KD: %.2f", CONE_LIFT1_DEFAULT_V, CONE_LIFT1_MIN_V, CONE_LIFT2_MAX_V, CONE_LIFT2_KX, CONE_LIFT2_KV);

  int dbgCnt = 0;

  while(true){
  	updateSensorValue(&firstLiftJoint);
    updateSensorValue(&secondLiftJoint);

    if(CONE_LIFT_COMMAND != HOLD){
      currentlyCarrying = 0;
      holdFirstJoint = 1;
      holdSecondJoint = 1;
    }

    if(CONE_LIFT_COMMAND == HOLD){ //Keeps the lift at the same place
      if(currentlyCarrying == 0){
        //Initially set desired values
        targetVals[0] = firstLiftJoint.val;
        targetVals[1] = secondLiftJoint.val;
        currentlyCarrying = 1;
        secondJointHasStalled = 0;
      }

      appliedVoltages[0] = sensorHold(&firstLiftJoint, targetVals[0], CONE_LIFT1_DEFAULT_V, -127, 127);
      appliedVoltages[1] = sensorHold(&secondLiftJoint, targetVals[1], CONE_LIFT2_DEFAULT_V, -127, 127);

      //Detect stalling on joint 2
      if(appliedVoltages[1] == 127 && secondLiftJoint.speed == 0){ //If the joint should be applying a high voltage, but it is not moving.
        secondJointHasStalled = 1;
        CONE_LIFT_COMMAND = STOP;
      }

      appliedVoltages[1] = BOUND(appliedVoltages[1], -127, 30);

      #if DEBUG_CONE_LIFT == 1
        if(dbgCnt == 10){
          writeDebugStreamLine("[LIFT 1] %d %d %d %d", targetVals[0], firstLiftJoint.val, firstLiftJoint.speed, appliedVoltages[0]);
  			  writeDebugStreamLine("[LIFT 2] %d %d %d %d", targetVals[1], secondLiftJoint.val, secondLiftJoint.speed, appliedVoltages[1]);
          dbgCnt = 0;
        }
        else dbgCnt++;
      #endif

      if(holdFirstJoint == 1) moveFirstLiftJoint(appliedVoltages[0]);
    	if(holdSecondJoint == 1) moveSecondLiftJoint(appliedVoltages[1]);
    }
    else if(CONE_LIFT_COMMAND == MOVE){
      moveLiftTo(firstLiftValsForLifting[coneNum], secondLiftValsForLifting[coneNum], 2000);
    }
    else if(CONE_LIFT_COMMAND == PRESET){
      moveLiftTo(firstLiftVal, secondLiftVal, 3000);
      CONE_LIFT_COMMAND = STOP;
    }
    else if(CONE_LIFT_COMMAND == STOP){
      moveFirstLiftJoint(0);
    	moveSecondLiftJoint(0);
    }

    wait1Msec(10);
  }
}

#endif
