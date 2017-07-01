#ifndef CONFIG_C
#define CONFIG_C

void move(int V, int H, int X){
  motor[M_WHEEL_L1] = BOUND(V + H, -127, 127);
  motor[M_WHEEL_L2] = BOUND(V + H, -127, 127);
  motor[M_WHEEL_R1] = BOUND(V - H, -127, 127);
  motor[M_WHEEL_R2] = BOUND(V - H, -127, 127);
}

#endif
