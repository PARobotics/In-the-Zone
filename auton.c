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
  SWING_ARM_COMMAND = DOWN;
	wait1Msec(1000);

  MOVE_MONITOR = START;
  refreshDrive();
  moveFwd();
  wait1Msec(200);
  moveStop();

  liftVal = 105; //Find the actual value
  CONE_LIFT_COMMAND = PRESET;
  wait1Msec(500);
  //Drive forwards while lifting

  refreshDrive();
  moveFwd();
  moveBy(180, 2000); //Find actual value
  moveStop();

  //Score the cone
  liftVal = 50; //Find the actual value
  CONE_LIFT_COMMAND = PRESET;
  wait1Msec(500);
  openClaw();

  moveBkwd();
  wait1Msec(300);
  moveStop();
  MOVE_MONITOR = STOP;
}

void autoC(){

}

void prgSkills(){

}


#endif
