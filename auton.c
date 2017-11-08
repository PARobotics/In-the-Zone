#ifndef AUTON_C
#define AUTON_C

void deployConeLift(){
	CONE_LIFT_COMMAND = MANUAL;
	moveLiftTo(400, 0, 1000);
	CONE_LIFT_COMMAND = HOLD;
	moveTurntableToFront();
	CONE_LIFT_COMMAND = MANUAL;
	moveLiftTo(0, 0, 300);
	CONE_LIFT_COMMAND = STOP;
}

void bringLiftBackToStart(){
	CONE_LIFT_COMMAND = MANUAL;
	moveLiftTo(0, 0, 500);
	CONE_LIFT_COMMAND = STOP;
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
