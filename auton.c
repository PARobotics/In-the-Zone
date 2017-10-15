#ifndef AUTON_C
#define AUTON_C

void deployConeLift(){ //Swings cone lift out into ready position
  //Stage 1: Release the rubber bands
  CONE_LIFT_COMMAND = MANUAL;
  moveLiftTo(0, 500, 1000);

  //Stage 1: Move the first lift up to clear out of the way
  CONE_LIFT_COMMAND = MANUAL;
  moveLiftTo(440, 500, 1000);

  CONE_LIFT_COMMAND = HOLD;

  //Stage 2: Rotate the turntable
  moveTurntableToFront();

  //Stage 3: Deploy the second lift
  CONE_LIFT_COMMAND = MANUAL;
  moveLiftTo(918, 3150, 2000);
  openClaw();
}

void grabAndStoreCone(){
	CONE_LIFT_COMMAND = MANUAL;
	moveLiftTo(0, 980, 300);
	closeClaw();
	moveLiftTo(0, 0, 1000);
	CONE_LIFT_COMMAND = STOP;
}

void deployClaw(){
	CONE_LIFT_COMMAND = MANUAL;
	moveLiftTo(0, 900, 700);
	openClaw();
	CONE_LIFT_COMMAND = HOLD;
}

void autoA(){
  deployConeLift();
}

void autoB(){
  deployConeLift();
}

void autoC(){
  deployConeLift();
}

void prgSkills(){

}


#endif
