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

}

void autoC(){

}

void prgSkills(){

}


#endif
