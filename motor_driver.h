
#ifdef L298_MOTOR_DRIVER
  #define RIGHT_MOTOR_BACKWARD 25 // In3 
  #define LEFT_MOTOR_BACKWARD  2  // In1 
  #define RIGHT_MOTOR_FORWARD  26 //In4
  #define LEFT_MOTOR_FORWARD   15 //In2
  #define RIGHT_MOTOR_ENABLE 12 // chân Enable B
  #define LEFT_MOTOR_ENABLE 13 //chân Enable A 
#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);