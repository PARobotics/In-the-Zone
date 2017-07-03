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




#endif
