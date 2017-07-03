#ifndef CONE_LIFT_C
#define CONE_LIFT_C

/*
  CONE_LIFT.C
  Contains all the code for the cone claw and lift
*/

void moveTurntable(int status){ //Manually controls the turntable rotation
  if(status == CLOCKWISE) motor[M_TURNTABLE] = 127;
  else if(status == COUNTERCLOCKWISE) motor[M_TURNTABLE] = -127;
  else if(status == STOP) motor[M_TURNTABLE] = 0;
}

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



#endif
