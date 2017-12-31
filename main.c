#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    PWR,            sensorPotentiometer)
#pragma config(Sensor, dgtl1,  mobileGoalLimitSwitch, sensorTouch)
#pragma config(Sensor, dgtl2,  liftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  LIFT,           sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           M_SWING_ARM,   tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           M_WHEEL_R3,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           M_WHEEL_R1,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           M_WHEEL_L3,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           M_WHEEL_L1,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           M_WHEEL_R2,    tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port7,           M_WHEEL_L2,    tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port8,           M_MOBILE_GOAL, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           M_LIFT,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          M_CLAW,        tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
  MAIN.C
  Primary file: Holds the entire competition sequence. You compile and flash THIS file.
  Jeffrey Shen
*/

#pragma DebuggerWindows("debugStream") //Include when debugging (automatically enables debug window)

#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(1200)

#include "Vex_Competition_Includes.c"
#include "main.h"
#include "parallax-lib/bin/constants.h"
#include "auton.c"

sensor liftSensor;
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

	startTask(mobileGoalTask, 9);
	startTask(coneLiftTask, 9);

	baseLeftPID.kp = BASE_LEFT_KP;
	baseLeftPID.kd = BASE_LEFT_KD;
	baseRightPID.kp = BASE_RIGHT_KP;
	baseRightPID.kd = BASE_RIGHT_KD;
	gyroPID.kp = GYRO_KP;
	gyroPID.kd = GYRO_KD;

	initializeSensor(&baseLeft, -1.0 * M_PI / 9.0, dgtl1, &baseLeftPID);
	initializeSensor(&baseRight, 1.0 * M_PI / 9, dgtl3, &baseRightPID);
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
  int V, H, X;

  stopTask(autonomous);

  while(true){

		// ** Primary joystick **

  	V = vexRT[Ch3];
  	X = vexRT[Ch4];
		H = vexRT[Ch1];

		if(abs(V) < 15) V = 0;
		if(abs(H) < 15) H = 0;
		if(abs(X) < 15) X = 0;

		move(V, H, X);

    //Lift
		if(vexRT[Btn6U] == 1) CONE_LIFT_COMMAND = UP;
		else if(vexRT[Btn6D] == 1) CONE_LIFT_COMMAND = DOWN;
		else if(CONE_LIFT_COMMAND != PRESET) CONE_LIFT_COMMAND = STOP;

		//Claw
		if(vexRT[Btn5U] == 1) closeClaw();
		else if(vexRT[Btn5D] == 1) openClaw();

		if(clawIsClosed == 1){
			moveClaw(35);
		}
		else if(clawIsOpened == 1){
			moveClaw(-20);
		}

		//Mobile Goal
		if(vexRT[Btn7L] == 1) MOBILE_GOAL_COMMAND = DOWN;
		else if(vexRT[Btn7D] == 1) MOBILE_GOAL_COMMAND = UP;
		else if(vexRT[Btn7U] == 1) MOBILE_GOAL_COMMAND = DOWN_WITHOUT_GOAL;

		//YEAH BOIII :)
		if(getPrButton(Btn7R_Main) == PUSHED_RELEASED){
			playSoundFile("yeahboi.wav");
			resetPrButton(Btn7R_Main);
		}

		userControlUpdate();
	}
}
