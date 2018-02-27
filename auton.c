#ifndef AUTON_C
#define AUTON_C

/*
	Auto A
	Scores 3 cones on a mobile goal
*/

void autoA(){
  openClaw();
  CONE_LIFT_COMMAND = UP;
  wait1Msec(1000);
  CONE_LIFT_COMMAND = DOWN;
  moveSwingArm(DOWN);
  wait1Msec(2000);
  moveSwingArm(STOP);
}

void autoB(){
  //Deploy Robot
  closeClaw();
  swingArmDown();

  //Move lift up
  liftVal = 1; //Find the actual value
  CONE_LIFT_COMMAND = PRESET;
  wait1Msec(500);

  //Drive forwards
  MOVE_MONITOR = START;
  refreshDrive();
  moveFwd();
  moveBy(200, 5000); //Find actual value
  moveStop();

  //Score the cone
  liftVal = 1; //Find the actual value
  CONE_LIFT_COMMAND = PRESET;
  wait1Msec(500);
  openClaw();
  MOVE_MONITOR = STOP;
}

void autoC(){

}

void prgSkills(){

}


#endif
