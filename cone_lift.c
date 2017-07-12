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

int getTurntableDegrees(){ //Returns the degree value of the turntable in units of 0.1 degrees
  int raw = getTurntableValue();
  int degrees = (raw * 360 * 10 / RPM_393) % 3600; //Make sure degrees dont overflow past 360 degrees

  if(degrees < 0) degrees += 3600;

  return degrees;
}

void moveTurntable(int val){ //Manually controls the turntable rotation
  if(val == CLOCKWISE) motor[M_TURNTABLE] = 127;
  else if(val == COUNTERCLOCKWISE) motor[M_TURNTABLE] = -127;
  else if(val == STOP) motor[M_TURNTABLE] = 0;
  else motor[M_TURNTABLE] = val;
}

void moveTurntableBy(int degrees, int status, int tlimit){ //Automatically rotates the turntable by x degrees (parameter is in units of 0.1 degrees)
  int initial = getTurntableValue();
  int target = initial + degrees * 5 * 10 * RPM_393 / 360; //1:5 gear ratio, underclocked
  int distanceToTarget = abs(target - initial);
  int currentVal = initial;

  int t0 = time1[T1];

  moveTurntable(status);

  while(vexRT[BAILOUT_BUTTON] == 0 && !isTimedOut(t0 + tlimit)){
    currentVal = getTurntableValue();

    if(distanceToTarget < 5 * RPM_393 / 360){ //Within 1 degree: STOP
      moveTurntable(STOP);
      break;
    }
    else if(distanceToTarget < 5 * 5 * RPM_393 / 360){ //Within 5 degree: Start BRAKING
      moveTurntable(SIGN(status) * 60);
    }
    else{
      moveTurntable(status);
    }

    distanceToTarget = abs(target - currentVal);
    wait1Msec(10);
  }
}

void moveTurntableToGoal(){ //Automatically snaps the turntable back to the mobile goal position
  int currentTheta = getTurntableDegrees();
  int desiredTheta = 0;

  if(currentTheta - desiredTheta <= 1800){
    //Counterclockwise
    moveTurntableBy(currentTheta - desiredTheta, COUNTERCLOCKWISE, 1500);
  }
  else{
    //Clockwise
    moveTurntableBy(3600 - (currentTheta - desiredTheta), CLOCKWISE, 1500);
  }
}

void moveTurntableToFront(){ //Automatically snaps the turntable to the front
  int currentTheta = getTurntableDegrees();
  int desiredTheta = 1800;

  if(currentTheta - desiredTheta <= 1800){
    //Counterclockwise
    moveTurntableBy(currentTheta - desiredTheta, COUNTERCLOCKWISE, 1500);
  }
  else{
    //Clockwise
    moveTurntableBy(3600 - (currentTheta - desiredTheta), CLOCKWISE, 1500);
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
}

void moveSecondLiftJoint(int status){ //Manually controls the second lift joint
  if(status == UP) motor[M_SECOND_LIFT] = 127;
  else if(status == DOWN) motor[M_SECOND_LIFT] = -127;
  else if(status == STOP) motor[M_SECOND_LIFT] = 0;
}

int getFirstLiftValue(){ //Returns the raw tick value of the first lift joint
  return nMotorEncoder[M_FIRST_LIFT1];
}

int getSecondLiftValue(){ //Returns the raw tick value of the second lift joint
  return nMotorEncoder[M_SECOND_LIFT];
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

#endif
