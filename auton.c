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
	rotate(SIDE * 127);
	rotateByPID(450, SIDE, 1000);
	moveStop();
	wait1Msec(100);

	openClaw();

	refreshDrive();
	moveFwd();
	moveByPID(450, 1, 2000);
	moveStop();
	closeClaw();
	refreshDrive();
	moveBkwd();
	moveByPID(5, 1, 2000);
	moveStop();


	moveLiftToCone(1);
	wait1Msec(100);

	refreshDrive();
	rotate(SIDE * 127);
	rotateByPID(400, SIDE, 1000);
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
	rotate(SIDE * -127);
	rotateByPID(400, -1 * SIDE, 1000);
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

	refreshDrive();
	rotate(SIDE * 127);
	rotateByPID(380, SIDE, 1000);
	moveStop();

	refreshDrive();
	moveFwd();
	moveByPID(110, 1, 700);
	moveStop();

	moveLiftToCone(1);
	while(CONE_LIFT_COMMAND == PRESET) wait1Msec(10);
	openClaw();

	refreshDrive();
	moveBkwd();
	moveByPID(80, -1, 700);
	moveStop();

	liftVal = 30;
	CONE_LIFT_COMMAND = PRESET;

	refreshDrive();
	rotate(SIDE * 127);
	rotateByPID(500, SIDE, 1000);
	moveStop();

	refreshDrive();
	moveFwd();
	moveBySlowPID(120, 1, 1000);
	moveStop();

	closeClaw();
	refreshDrive();
	moveBkwd();
	moveBySlowPID(60, -1, 1000);
	moveStop();
	closeClaw();

	moveLiftToCone(3);
	wait1Msec(100);

	refreshDrive();
	rotate(SIDE * -127);
	rotateByPID(650, -1 * SIDE, 1000);
	moveStop();

	refreshDrive();
	moveFwd();
	moveByPID(100, 1, 1000);
	moveStop();

	moveLiftToCone(2);
	while(CONE_LIFT_COMMAND == PRESET) wait1Msec(10);
	openClaw();

	wait1Msec(100);

	refreshDrive();
	moveBkwd();
	moveByPID(100, -1, 1000);
	moveStop();

	MOVE_MONITOR = STOP;
}

void autoB(){

}

void autoC(){

}

void prgSkills(){

}


#endif
