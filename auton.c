#ifndef AUTON_C
#define AUTON_C

void deployConeLift(){ //Swings cone lift out into ready position

  //Stage 1: Move the first lift up to clear out of the way
  moveLiftTo(440, 0, 1000);
  CONE_LIFT_COMMAND = HOLD;

  //Stage 2: Rotate the turntable
  moveTurntableToFront();

  //Stage 3: Deploy the second lift
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
