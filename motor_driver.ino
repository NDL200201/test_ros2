/***************************************************************
   Motor driver definitions
   
   Add a "#elif defined" block to this file to include support
   for a particular motor driver.  Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   *************************************************************/

#ifdef USE_BASE
   
#ifdef POLOLU_VNH5019
  /* Include the Pololu library */
  #include "DualVNH5019MotorShield.h"

  /* Create the motor driver object */
  DualVNH5019MotorShield drive;
  
  /* Wrap the motor driver initialization */
  void initMotorController() {
    drive.init();
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) drive.setM1Speed(spd);
    else drive.setM2Speed(spd);
  }

  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined POLOLU_MC33926
  /* Include the Pololu library */
  #include "DualMC33926MotorShield.h"

  /* Create the motor driver object */
  DualMC33926MotorShield drive;
  
  /* Wrap the motor driver initialization */
  void initMotorController() {
    drive.init();
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) drive.setM1Speed(spd);
    else drive.setM2Speed(spd);
  }

  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined L298_MOTOR_DRIVER
  void initMotorController() {
    digitalWrite(RIGHT_MOTOR_ENABLE, HIGH);
    digitalWrite(LEFT_MOTOR_ENABLE, HIGH);
  }
  
  void setMotorSpeed(int i, int spd) {
    unsigned char reverse = 0;
    pinMode(LEFT_ENC_PIN_A, INPUT_PULLUP);  
    attachInterrupt(digitalPinToInterrupt(LEFT_ENC_PIN_A), L_ENA, CHANGE); 
    pinMode(LEFT_ENC_PIN_B, INPUT_PULLUP);  
    attachInterrupt(digitalPinToInterrupt(LEFT_ENC_PIN_B), L_ENA, CHANGE);

    pinMode(RIGHT_ENC_PIN_A, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(RIGHT_ENC_PIN_A), R_ENA, CHANGE);
    pinMode(RIGHT_ENC_PIN_B, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(RIGHT_ENC_PIN_B), R_ENA, CHANGE);
    
   ledcSetup(pwmChannel1, freq, resolution); //Đặt kênh, tần số và độ phân giải
   ledcSetup(pwmChannel2, freq, resolution);
   ledcAttachPin(RIGHT_MOTOR_ENABLE, pwmChannel1); //Đặt chân đầu ra và các thuộc tính của PWM
   ledcAttachPin(LEFT_MOTOR_ENABLE, pwmChannel2);
    if (spd < 0)
    {
      spd = -spd;
      reverse = 1;
    }
    if (spd > 255)
      spd = 255;
    // có thể add hết cấu hình ledcWrite tại đây
    if (i == LEFT) { 
      // if      (reverse == 0) { ledcWrite(LEFT_MOTOR_FORWARD, spd); ledcWrite(LEFT_MOTOR_BACKWARD, 0); }
      if      (reverse == 0) { ledcWrite(pwmChannel2, spd); ledcWrite(pwmChannel2, 0); }
      //else if (reverse == 1) { ledcWrite(LEFT_MOTOR_BACKWARD, spd); ledcWrite(LEFT_MOTOR_FORWARD, 0); }
    }
    else /*if (i == RIGHT) //no need for condition*/ {
      // if      (reverse == 0) { ledcWrite(RIGHT_MOTOR_FORWARD, spd); ledcWrite(RIGHT_MOTOR_BACKWARD, 0); }
      // else if (reverse == 1) { ledcWrite(RIGHT_MOTOR_BACKWARD, spd); ledcWrite(RIGHT_MOTOR_FORWARD, 0); }
      if      (reverse == 0) { ledcWrite(pwmChannel1, spd); ledcWrite(pwmChannel1, 0); }// coi kỹ có nên set điều kiện của reverse hay không
    }
  }
  
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#else
  #error A motor driver must be selected!
#endif

#endif
