#ifndef AUTON_C
#define AUTON_C

/*
	Auto A
	Scores 3 cones on a mobile goal
*/

void autoA(){
  openClaw();
  CONE_LIFT_COMMAND = UP;
  wait1Msec(100);
  CONE_LIFT_COMMAND = DOWN;
  swingArmDown();
}

void autoB(){

}

void autoC(){

}

void prgSkills(){

}


#endif
