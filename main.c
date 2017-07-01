
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
//#include "parallax-lib/main.c"
#include "main.h"
#include "mobile_goal.c"

void pre_auton(){

}

task autonomous(){

}

/*
	USER CONTROL
*/

task usercontrol(){
  while(true){
    if(vexRT[Btn6U] == 1){
      moveMobileGoalLift(UP);
    }
    else if(vexRT[Btn6D] == 1){
      moveMobileGoalLift(DOWN);
    }
    else{
      moveMobileGoalLift(STOP);
    }

		wait1Msec(10);
	}
}
