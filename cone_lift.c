#ifndef CONE_LIFT_C
#define CONE_LIFT_C

/*
  CONE_LIFT.C
  Contains all the code for the cone claw and lift
*/

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
  while(!isTimedOut(t0 + 150)){
    moveClaw(CLOSE);
    wait1Msec(10);
  }
  moveClaw(20);
}

// ** Lift **
void moveLift(int status){
  if(status == UP){
    moveLift(127);
  }
  else if(status == DOWN){
    moveLift(-127);
  }
  else{
    motorReq[M_LIFT_1] = status;
    motorReq[M_LIFT_2] = status;
    motorReq[M_LIFT_3] = status;
    motorReq[M_LIFT_4] = status;
  }
}

task coneLiftTask(){

  pid liftPid;
  liftPid.kp = 0;
  liftPid.kd = 0;

  initializeSensor(&liftSensor, 1.0, I2C_1, &liftPid);

  int dbgCnt = 0;

  while(true){
  	updateSensorValue(&liftSensor);

    if(CONE_LIFT_COMMAND == HOLD){ //Keeps the lift at the same place
      #if DEBUG_CONE_LIFT == 1
        if(dbgCnt == 10){
          dbgCnt = 0;
        }
        else dbgCnt++;
      #endif
    }
    else if(CONE_LIFT_COMMAND == UP){
      moveLift(UP);
    }
    else if(CONE_LIFT_COMMAND == DOWN){
      moveLift(DOWN);
    }
    else if(CONE_LIFT_COMMAND == PRESET){
      moveLift(SIGN(liftVal - liftSensor.val));
      if(abs(liftSensor.val - liftVal) < 10) CONE_LIFT_COMMAND = STOP;
    }
    else if(CONE_LIFT_COMMAND == STOP){
      moveLift(STOP);
    }

    wait1Msec(10);
  }
}

#endif
