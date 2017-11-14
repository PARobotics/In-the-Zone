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
	moveBy(50, 1000);
	refreshDrive();
	moveBkwd();
	moveBy(10, 500);
	moveStop();

	refreshDrive();
	rotate(-127);
	rotateBy(450, 1000);
	moveStop();
	wait1Msec(100);

	refreshDrive();
	moveFwd();
	moveBy(360, 3000);
	moveStop();
	closeClaw();

	moveLiftToCone(1);
	wait1Msec(100);

	refreshDrive();
	rotate(-127);
	rotateBy(450, 1000);
	moveStop();

	refreshDrive();
	moveFwd();
	moveBy(120, 1500);
	moveStop();

	moveLiftToCone(0);
	while(CONE_LIFT_COMMAND == PRESET) wait1Msec(10);
	openClaw();

	refreshDrive();
	moveBkwd();
	moveBy(30, 1000);
	moveStop();

	liftVal = 0;
	CONE_LIFT_COMMAND = PRESET;

	refreshDrive();
	rotate(-127);
	rotateBy(450, 1000);
	moveStop();

	refreshDrive();
	moveFwd();
	moveBy(30, 1000);
	closeClaw();
	refreshDrive();
	moveBkwd();
	moveBy(30, 1000);
	moveStop();
	closeClaw();

	moveLiftToCone(2);
	refreshDrive();
	rotate(127);
	rotateBy(450, 1000);
	moveStop();


	/*
	// ** Score Cone #2 **
	//Back up + start going down
	refreshDrive();
	moveBkwd();
	moveBy(50, 1000);
	moveStop();
	liftVal = 0;
	CONE_LIFT_COMMAND = PRESET;

	//Rotate 45 to right
	refreshDrive();
	rotate(127);
	rotateBy(450, 1000);
	moveStop();
	wait1Msec(100);

	//Move forward + close claw
	refreshDrive();
	moveFwd();
	moveBy(50, 1000);
	moveStop();
	closeClaw();

	//Start lifting to #2 height + moving into position
	moveLiftToCone(2);
	refreshDrive();
	moveBkwd();
	moveBy(50, 1000);
	moveStop();
	rotate(-127);
	rotateBy(450, 1000);
	moveStop();
	moveFwd();
	moveBy(80, 1000);
	moveStop();

	//Move cone down and open claw
	moveLiftToCone(1);
	while(CONE_LIFT_COMMAND == PRESET) wait1Msec(10);
	openClaw();

	// ** Score Cone #3 **
*/
	MOVE_MONITOR = STOP;
}

void autoB(){

}

void autoC(){

}

void prgSkills(){

}


#endif
