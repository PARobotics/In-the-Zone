#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    PWR,            sensorPotentiometer)
#pragma config(Sensor, in2,    Gyro,           sensorGyro)
#pragma config(Sensor, in3,    MobileGoal,     sensorPotentiometer)
#pragma config(Sensor, dgtl1,  wheelEncoderLeft, sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  wheelEncoderRight, sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  mobileGoalLimitSwitch, sensorTouch)
#pragma config(Sensor, dgtl6,  secondLiftEncoder, sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           M_MOBILE_GOAL_LIFT, tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           M_WHEEL_R2,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           M_WHEEL_R1,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           M_TURNTABLE,   tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port5,           M_FIRST_LIFT1, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           M_FIRST_LIFT2, tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port7,           M_SECOND_LIFT, tmotorVex393_MC29, openLoop, encoderPort, dgtl6)
#pragma config(Motor,  port8,           M_WHEEL_L1,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           M_WHEEL_L2,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          M_CLAW,        tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
  MAIN.C
  Primary file: Holds the entire competition sequence. You compile and flash THIS file.
  Jeffrey Shen
*/

#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(1200)

#include "Vex_Competition_Includes.c"
#include "main.h"
#include "parallax-lib/bin/constants.h"
#include "auton.c"

sensor firstLiftJoint;
sensor secondLiftJoint;
sensor turntable;
sensor baseLeft;
sensor baseRight;
sensor mobileGoalLift;
sensor gyro;
pid baseLeftPID;
pid baseRightPID;
pid gyroPID;
pid mobileGoalPID;

#include "parallax-lib/main.c"
#include "mobile_goal.c"
#include "cone_lift.c"

void pre_auton(){
	bStopTasksBetweenModes = false; //Make sure all tasks we create actually execute in user control

	startTask(mobileGoalTask);
	startTask(coneLiftTask, 9); //TODO: Change task priority

	baseLeftPID.kp = BASE_LEFT_KP;
	baseLeftPID.kd = BASE_LEFT_KD;
	baseRightPID.kp = BASE_RIGHT_KP;
	baseRightPID.kd = BASE_RIGHT_KD;
	gyroPID.kp = GYRO_KP;
	gyroPID.kd = GYRO_KD;

	initializeSensor(&baseLeft, M_PI / 9.0, dgtl1, &baseLeftPID);
	initializeSensor(&baseRight, -1.0 * M_PI / 9, dgtl3, &baseRightPID);
	initializeSensor(&gyro, 1.0, in2, &gyroPID);

	makeLED(dgtl12, OFF);

	initializeDrive(0.0, &baseLeft, &baseRight, &gyro);
	initialize();
}

task autonomous(){
	stopTask(usercontrol);
	autonProcedure();
}

/*
	USER CONTROL
*/

task usercontrol(){
  int V, H, T, F, S;

  stopTask(autonomous);

  moveFirstLiftJoint(0);
  moveSecondLiftJoint(0);

  while(true){

		// ** Primary joystick **

  	V = vexRT[Ch3];
		H = vexRT[Ch1];

		if(abs(V) < 15) V = 0;
		if(abs(H) < 15) H = 0;
		move(V, H, 0);

    if(vexRT[Btn6U] == 1){
      MOBILE_GOAL_COMMAND = UP;
    }
		else if(vexRT[Btn6D] == 1){
			MOBILE_GOAL_COMMAND = DOWN;
		}
		else if(vexRT[Btn5U] == 1){
			MOBILE_GOAL_COMMAND = UP;
		}
		else if(vexRT[Btn5D] == 1){
			MOBILE_GOAL_COMMAND = DOWN_WITHOUT_GOAL;
		}

		if(getPrButton(Btn7U_Main) == PUSHED_RELEASED){
			playSoundFile("yeahboi.wav");
			resetPrButton(Btn7U_Main);
		}

		// ** Partner Joystick**

		T = vexRT[Ch4Xmtr2]; //Turntable channel
		F = vexRT[Ch1Xmtr2]; //First lift joint channel
		S = vexRT[Ch2Xmtr2]; //Second lift joint channel

		//Prevent tiny accidental motions
		if(abs(T) < 15) T = 0;
		if(abs(F) < 15) F = 0;
		if(abs(S) < 15) S = 0;

		// TURNTABLE CONTROLS

		if(vexRT[Btn5UXmtr2] == 1){ //Turntable to mobile goal
			moveTurntableToGoal();
		}
		else if(vexRT[Btn5DXmtr2] == 1){ //Turntable to grabbing position
			moveTurntableToFront();
		}
		else{
			moveTurntable(T);
		}

		// CLAW CONTROLS

		if(vexRT[Btn6UXmtr2] == 1){
      openClaw();
    }
    else if(vexRT[Btn6DXmtr2] == 1){
      closeClaw();
    }
    else if(clawIsClosed){ //Apply a small voltage to keep claw closed
    	moveClaw(20);
    }
		else if(clawIsOpened){ //Apply a small voltage to keep claw open
			moveClaw(-10);
		}

		// LIFT CONTROLS

		if(vexRT[Btn7UXmtr2] == 1){ //Hovering preset
			moveLiftToPreset(975, 3170);
		}
		else if(vexRT[Btn7LXmtr2] == 1){ //Grabbing cone preset
			grabAndStoreCone();
			//moveLiftToPreset();
		}
		else if(vexRT[Btn7RXmtr2] == 1){ //On the ground preset
			deployClaw();
		}
		else if(getPrButton(Btn8U_Partner) == PUSHED_RELEASED){ //Move lift up by one
			moveLiftUp();
			resetPrButton(Btn8U_Partner);
		}
		else if(getPrButton(Btn8D_Partner) == PUSHED_RELEASED){ //Move lift down by one
			moveLiftDown();
			resetPrButton(Btn8D_Partner);
		}

		//Manual lift controls
		if(F != 0){
			CONE_LIFT_COMMAND = HOLD;
			holdFirstJoint = 0;
			moveFirstLiftJoint(F);
		}
		else if(CONE_LIFT_COMMAND == HOLD && holdFirstJoint == 0){
			moveFirstLiftJoint(0);
			currentlyCarrying = 0;
			holdFirstJoint = 1;
		}

		if(S != 0){
			CONE_LIFT_COMMAND = HOLD;
			holdSecondJoint = 0;
			moveSecondLiftJoint(S);
		}
		else if(CONE_LIFT_COMMAND == HOLD && holdSecondJoint == 0){
			moveSecondLiftJoint(0);
			currentlyCarrying = 0;
			holdSecondJoint = 1;
		}

		if(getPrButton(Btn8L_Partner) == PUSHED_RELEASED){ //Toggle lift hold
			if(CONE_LIFT_COMMAND != HOLD) CONE_LIFT_COMMAND = HOLD;
			else CONE_LIFT_COMMAND = STOP;

			resetPrButton(Btn8L_Partner);
		}

		userControlUpdate();
	}
}
