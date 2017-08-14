#ifndef AUTON_C
#define AUTON_C

void deployConeLift(){ //Swings cone lift out into ready position

  //Stage 1: Move the first lift up to clear out of the way
  CONE_LIFT_COMMAND = MANUAL;
  moveLiftTo(440, 0, 1000);

  //Stage 2: Rotate the turntable
  moveTurntableToFront();

  //Stage 3: Deploy the second lift
  CONE_LIFT_COMMAND = MANUAL;
  moveLiftTo(975, 3170, 2000);
  openClaw();

}

void autoA(){

}

void autoB(){

}

void autoC(){

}

void prgSkills(){

}


#endif
