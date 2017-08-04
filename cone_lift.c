#ifndef CONE_LIFT_C
#define CONE_LIFT_C

/*
  CONE_LIFT.C
  Contains all the code for the cone claw and lift
*/

// ** Turntable **
int getTurntableValue(){ //Returns the raw tick value of the turntable
  return nMotorEncoder[M_TURNTABLE];
}

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
  int raw = getTurntableValue();
  int degrees = ticksToDegrees(raw);

  return degrees;
}

void moveTurntable(int val){ //Manually controls the turntable rotation
  if(val == CLOCKWISE) motor[M_TURNTABLE] = 127;
  else if(val == COUNTERCLOCKWISE) motor[M_TURNTABLE] = -127;
  else if(val == STOP) motor[M_TURNTABLE] = 0;
  else motor[M_TURNTABLE] = val;
}

void moveTurntableBy(int degrees, int status, int tlimit){ //Automatically rotates the turntable by x degrees (parameter is in units of 0.1 degrees)
  int currentVal = getTurntableValue();
  int target = currentVal + status * abs(degreesToTicks(degrees));

  writeDebugStreamLine("initial: %d target: %d", currentVal, target);

  int t0 = time1[T1];

  moveTurntable(status * 80);

  int distanceToTarget = 0;

  while(vexRT[BAILOUT_BUTTON] == 0 && !isTimedOut(t0 + tlimit)){
    currentVal = getTurntableValue();

    distanceToTarget = target - currentVal;
    if(status == COUNTERCLOCKWISE) distanceToTarget = currentVal - target;

    if(distanceToTarget < degreesToTicks(20)) break;
    else if(distanceToTarget < degreesToTicks(40)) moveTurntable(-1 * status * 10);
    else if(distanceToTarget < degreesToTicks(70)) moveTurntable(status * 10);
    else if(distanceToTarget < degreesToTicks(150)) moveTurntable(status * 20);
    else if(distanceToTarget < degreesToTicks(450)) moveTurntable(status * 30);
    else if(distanceToTarget < degreesToTicks(600)) moveTurntable(status * 60);
    else moveTurntable(status * 80);

    wait1Msec(10);
  }

  moveTurntable(STOP);
}

void moveTurntableToGoal(){ //Automatically snaps the turntable back to the mobile goal position
  int currentTheta = getTurntableDegrees();

  if(currentTheta <= 1800){
    //Counterclockwise
    moveTurntableBy(currentTheta, COUNTERCLOCKWISE, 1000);
  }
  else{
    //Clockwise
    moveTurntableBy(3600 - currentTheta, CLOCKWISE, 1000);
  }
}

void moveTurntableToFront(){ //Automatically snaps the turntable to the front
  int currentTheta = getTurntableDegrees();
  int desiredTheta = 1800;

  if(currentTheta <= 1800){
  	//Clockwise
  	moveTurntableBy(desiredTheta - currentTheta, CLOCKWISE, 1000);
	}
	else{
		moveTurntableBy(currentTheta - desiredTheta, COUNTERCLOCKWISE, 1000);
	}
}

// ** Lift **
void moveFirstLiftJoint(int status){ //Manually controls the first lift joint
  if(status == UP){
    motor[M_FIRST_LIFT1] = 127;
    motor[M_FIRST_LIFT2] = 127;
  }
  else if(status == DOWN){
    motor[M_FIRST_LIFT1] = -127;
    motor[M_FIRST_LIFT2] = -127;
  }
  else if(status == STOP){
    motor[M_FIRST_LIFT1] = 0;
    motor[M_FIRST_LIFT2] = 0;
  }
  else{
    motor[M_FIRST_LIFT1] = status;
    motor[M_FIRST_LIFT2] = status;
  }
}

void moveSecondLiftJoint(int status){ //Manually controls the second lift joint
  if(status == UP) motor[M_SECOND_LIFT] = 127;
  else if(status == DOWN) motor[M_SECOND_LIFT] = -127;
  else if(status == STOP) motor[M_SECOND_LIFT] = 0;
  else motor[M_SECOND_LIFT] = status;
}

int getFirstLiftValue(){ //Returns the raw tick value of the first lift joint
  return nMotorEncoder[M_FIRST_LIFT2];
}

int getSecondLiftValue(){ //Returns the raw tick value of the second lift joint
  return nMotorEncoder[M_SECOND_LIFT];
}

void moveLiftUp(){
  if(coneNum < 10){
    coneNum++;
    CONE_LIFT_COMMAND = MOVE;
  }
}

void moveLiftDown(){
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

void moveLiftTo(int firstVal, int secondVal){ //Swings the lift to the preset
  //Move first joint to correct point
  int entered = 0;
  int tnow = time1[T1];

  while(true){
    if(BAILOUT == 1 || isTimedOut(tnow + 3000) || abs(secondVal - secondLiftJoint.val) <= 1) break;

    moveFirstLiftJoint(sensorHold(&firstLiftJoint, firstVal, CONE_LIFT1_DEFAULT_V, CONE_LIFT1_MIN_V, CONE_LIFT1_MAX_V));

    //Move second joint to correct point
    if(abs(firstVal - firstLiftJoint.val) <= 1 || entered == 1){
      moveSecondLiftJoint(sensorHold(&secondLiftJoint, secondVal, CONE_LIFT2_DEFAULT_V, CONE_LIFT2_MIN_V, CONE_LIFT2_MAX_V));
      entered = 1;
    }
  }

  //Hold both joints
  CONE_LIFT_COMMAND = HOLD;
}

// ** Claw **
void moveClaw(int status){ //Manually opens and closes the claw
  if(status == CLOSE) motor[M_CLAW] = 127;
  else if(status == OPEN) motor[M_CLAW] = -127;
  else if(status == STOP) motor[M_CLAW] = 0;
  else motor[M_CLAW] = status;
}

void openClaw(){ //Automatically opens the claw
  int t0 = time1[T1];
  moveClaw(OPEN);
  clawIsClosed = 0;
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
  while(!isTimedOut(t0 +400)){
    moveClaw(100);
    wait1Msec(10);
  }
}

task coneLiftTask(){ //Controls the position of the lift continuously
  int currentlyCarrying = 0;
  int targetVals[2] = {0, 0};
  int appliedVoltages[2] = {0, 0};

  //Store values for the lifting up and down
  int firstLiftValsForLifting[] = {117, 131, 134, 134, 135, 137, 136, 133, 129, 121, 118};
  int secondLiftValsForLifting[] = {365, 299, 289, 285, 275, 269, 254, 245, 226, 211, 171};

  pid firstPid, secondPid;
  firstPid.kp = CONE_LIFT1_KX;
  firstPid.kd = CONE_LIFT1_KV;

  secondPid.kp = CONE_LIFT2_KX;
  secondPid.kd = CONE_LIFT2_KV;

  initializeSensor(&firstLiftJoint, 72.0 / RPM_393_HS, I2C_2, firstPid); //Overclocked 1 to 5 gear ratio
  initializeSensor(&secondLiftJoint, 1.0, dgtl6, secondPid); //Underclocked 1 to 3 gear ratio

  while(0){
  	updateSensorValue(&firstLiftJoint);
    updateSensorValue(&secondLiftJoint);

    if(CONE_LIFT_COMMAND != HOLD) currentlyCarrying = 0;

    if(CONE_LIFT_COMMAND == HOLD){ //Keeps the lift at the same place
      if(currentlyCarrying == 0){
        //Initially set desired values
        targetVals[0] = getFirstLiftValue();
        targetVals[1] = getSecondLiftValue();
        currentlyCarrying = 1;
      }

      appliedVoltages[0] = sensorHold(&firstLiftJoint, targetVals[0], CONE_LIFT1_DEFAULT_V, CONE_LIFT1_MIN_V, CONE_LIFT1_MAX_V);
      appliedVoltages[1] = sensorHold(&secondLiftJoint, targetVals[1], CONE_LIFT2_DEFAULT_V, CONE_LIFT2_MIN_V, CONE_LIFT2_MAX_V);

      writeDebugStreamLine("%d %d %d %d", targetVals[0], targetVals[1], appliedVoltages[0], appliedVoltages[1]);

      moveFirstLiftJoint(appliedVoltages[0]);
    	moveSecondLiftJoint(appliedVoltages[1]);
    }
    else if(CONE_LIFT_COMMAND == MOVE){
      moveLiftTo(firstLiftValsForLifting[coneNum], secondLiftValsForLifting[coneNum]);
    }
    else if(CONE_LIFT_COMMAND == PRESET){
      moveLiftTo(firstLiftVal, secondLiftVal);
    }
    else{
      appliedVoltages[0] = 0;
      appliedVoltages[1] = 0;
      moveFirstLiftJoint(appliedVoltages[0]);
    	moveSecondLiftJoint(appliedVoltages[1]);
    }

    wait1Msec(10);
  }
}

#endif
