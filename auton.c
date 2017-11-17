#ifndef AUTON_C
#define AUTON_C

/*
	Auto A
	Scores 3 cones on a mobile goal
*/

void autoA(){
	MOVE_MONITOR = START;
	// ** Score Preload **
	//Get into position
	openClaw();
	refreshDrive();
	moveFwd();
	moveBy(70,1000);
	refreshDrive();
	moveBkwd();
	moveBy(10, 500);
	moveStop();

	refreshDrive();
	rotate(-127);
	rotateByPID(450, -1, 1000);
	moveStop();
	wait1Msec(100);

	refreshDrive();
	moveFwd();
	moveByPID(400, 1, 2000);
	moveStop();
	closeClaw();

	moveLiftToCone(1);
	wait1Msec(100);

	refreshDrive();
	rotate(-127);
	rotateByPID(400, -1, 1000);
	moveStop();

	while(CONE_LIFT_COMMAND == PRESET) wait1Msec(10);

	refreshDrive();
	moveFwd();
	moveByPID(110,1, 700);
	moveStop();

	moveLiftToCone(0);
	while(CONE_LIFT_COMMAND == PRESET) wait1Msec(10);
	openClaw();

	refreshDrive();
	moveBkwd();
	moveByPID(110, -1, 700);
	moveStop();

	liftVal = 30;
	CONE_LIFT_COMMAND = PRESET;

	refreshDrive();
	rotate(127);
	rotateByPID(400, 1, 1000);
	moveStop();

	CONE_LIFT_COMMAND = STOP;

	openClaw();

	refreshDrive();
	moveFwd();
	moveByPID(100, 1, 1000);
	closeClaw();

	refreshDrive();
	moveBkwd();
	moveByPID(100, -1, 1000);
	moveStop();
	closeClaw();

	moveLiftToCone(2);
	wait1Msec(100);

	refreshDrive();
	rotate(-127);
	rotateByPID(380, -1, 1000);
	moveStop();

	refreshDrive();
	moveFwd();
	moveByPID(110, 1, 700);
	moveStop();

	moveLiftToCone(0);
	while(CONE_LIFT_COMMAND == PRESET) wait1Msec(10);
	openClaw();



	MOVE_MONITOR = STOP;
}

void autoB(){

}

void autoC(){

}

void prgSkills(){

}


#endif
