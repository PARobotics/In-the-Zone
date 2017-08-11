#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    PWR,            sensorPotentiometer)
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
#include "auton.c"
#include "parallax-lib/bin/constants.h"

sensor firstLiftJoint;
sensor secondLiftJoint;
sensor turntable;

#include "parallax-lib/main.c"
#include "mobile_goal.c"
#include "cone_lift.c"

void pre_auton(){
	bStopTasksBetweenModes = false; //Make sure all tasks we create actually execute in user control

	startTask(mobileGoalTask);
	startTask(coneLiftTask, 9); //TODO: Change task priority

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

  playSoundFile("yeahboi.wav");

  moveFirstLiftJoint(0);
  moveSecondLiftJoint(0);

  while(true){

		// ** Primary joystick **

    /*V = vexRT[Ch3];
		H = vexRT[Ch1];

		if(abs(V) < 15) V = 0;
		if(abs(H) < 15) H = 0;
		move(V, H, 0);

    if(vexRT[Btn5U] == 1 || vexRT[Btn6U] == 1){
      MOBILE_GOAL_COMMAND = UP;
    }
    else if(vexRT[Btn6D] == 1){
      MOBILE_GOAL_COMMAND = DOWN;
    }
		else if(vexRT[Btn5D] == 1){
			MOBILE_GOAL_COMMAND = DOWN_WITHOUT_GOAL;
		}

		*/

		// ** Partner Joystick**

		T = vexRT[Ch4]; //Turntable channel
		F = vexRT[Ch1]; //First lift joint channel
		S = vexRT[Ch2]; //Second lift joint channel

		//Prevent tiny accidental motions
		if(abs(T) < 15) T = 0;
		if(abs(F) < 15) F = 0;
		if(abs(S) < 15) S = 0;

		// TURNTABLE CONTROLS

		if(vexRT[Btn5U] == 1){ //Turntable to mobile goal
			moveTurntableToGoal();
		}
		else if(vexRT[Btn5D] == 1){ //Turntable to grabbing position
			moveTurntableToFront();
		}
		else{
			moveTurntable(T);
		}

		// CLAW CONTROLS

		if(vexRT[Btn6U] == 1){
      openClaw();
    }
    else if(vexRT[Btn6D] == 1){
      closeClaw();
    }
    else if(clawIsClosed){ //Apply a small voltage to keep claw closed
    	moveClaw(10);
    }

		// LIFT CONTROLS

		if(vexRT[Btn7U] == 1){ //Hovering preset
			//moveLiftToPreset(129, 327);
			moveLiftToPreset(1290, 0);
		}
		else if(vexRT[Btn7L] == 1){ //Loader preset
			//moveLiftToPreset();
		}
		else if(vexRT[Btn7R] == 1){ //On the ground preset
			//moveLiftToPreset(72, 317);
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
			CONE_LIFT_COMMAND = MANUAL;
			moveFirstLiftJoint(SIGN(F) * 127);
		}
		else if(CONE_LIFT_COMMAND == MANUAL) 	moveFirstLiftJoint(0);

		if(S != 0){
			CONE_LIFT_COMMAND = MANUAL;
			moveSecondLiftJoint(SIGN(S) * 127);
		}
		else if(CONE_LIFT_COMMAND == MANUAL) 	moveSecondLiftJoint(0);

		if(F == 0 && S == 0 && CONE_LIFT_COMMAND == MANUAL) CONE_LIFT_COMMAND = HOLD;

		if(getPrButton(Btn8L_Partner) == PUSHED_RELEASED){ //Toggle lift hold
			CONE_LIFT_COMMAND = HOLD;
			resetPrButton(Btn8L_Partner);
		}

		userControlUpdate();
	}
}
