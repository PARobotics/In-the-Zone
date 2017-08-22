#ifndef AUTON_C
#define AUTON_C

void deployConeLift(){ //Swings cone lift out into ready position
  //Stage 1: Release the rubber bands
  CONE_LIFT_COMMAND = MANUAL;
  moveLiftTo(0, 500, 500);

  //Stage 1: Move the first lift up to clear out of the way
  CONE_LIFT_COMMAND = MANUAL;
  moveLiftTo(440, 0, 1000);

  //Stage 2: Rotate the turntable
  moveTurntableToFront();

  //Stage 3: Deploy the second lift
  CONE_LIFT_COMMAND = MANUAL;
  moveLiftTo(918, 3150, 2000);
  openClaw();

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
