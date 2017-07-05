#ifndef CONE_LIFT_C
#define CONE_LIFT_C

/*
  CONE_LIFT.C
  Contains all the code for the cone claw and lift
*/

//Turntable
void moveTurntable(int val){ //Manually controls the turntable rotation
  if(val == CLOCKWISE) motor[M_TURNTABLE] = 127;
  else if(val == COUNTERCLOCKWISE) motor[M_TURNTABLE] = -127;
  else if(val == STOP) motor[M_TURNTABLE] = 0;
  else motor[M_TURNTABLE] = val;
}

void moveTurntableBy(int degrees, int status){ //Automatically rotates the turntable by x degrees (parameter is in units of 0.1 degrees)
  int initial = getTurntableValue();
  int target = initial + degrees * 5 * 10 * RPM_393 / 360; //1:5 gear ratio CHECK OVERCLOCKING HERE
  int distanceToTarget = abs(target - initial);
  int currentVal = initial;

  int t0 = time1[T1];

  moveTurntable(status);

  while(vexRT[BAILOUT_BUTTON] == 0 && !isTimedOut(t0 + 3000)){
    currentVal = getTurntableValue();

    if(distanceToTarget < 5 * RPM_393 / 360){ //Within 1 degree: STOP
      moveTurntable(STOP);
    }
    else if(distanceToTarget < 5 * 5 * RPM_393 / 360){ //Within 5 degree: Start BRAKING
      moveTurntable(60);
    }

    distanceToTarget = abs(target - currentVal);
    wait1Msec(10);
  }

}

int getTurntableValue(){ //Returns the raw tick value of the turntable
  return nMotorEncoder[M_TURNTABLE];
}

//Lift
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

void moveSecondLiftJoint(int status){
  if(status == UP) motor[M_SECOND_LIFT] = 127;
  else if(status == DOWN) motor[M_SECOND_LIFT] = -127;
  else if(status == STOP) motor[M_SECOND_LIFT] = 0
}

int getFirstLiftValue(){
  return nMotorEncoder[M_FIRST_LIFT1];
}

int getSecondLiftValue(){
  return nMotorEncoder[M_SECOND_LIFT];
}

//Claw
void moveClaw(int status){
  if(status == CLOSE) motor[M_CLAW] = 127;
  else if(status == OPEN) motor[M_CLAW] = -127;
  else if(status == STOP) motor[M_CLAW] = 0;
}

#endif
