/*Đoạn code này được sử dụng để đọc giá trị của encoder và đếm số xung tương ứng với mỗi vòng quay của encoder. Đoạn code này sử dụng ngắt Pin Change Interrupt để đọc giá trị của encoder. Khi một chân GPIO được cấu hình để sử dụng Pin Change Interrupt, nó sẽ tạo ra một ngắt khi trạng thái của chân GPIO đó thay đổi.

Đoạn code này bao gồm hai hàm ngắt (ISR) cho LEFT encoder và RIGHT encoder. Hàm ngắt cho LEFT encoder được gọi khi trạng thái của các chân GPIO được cấu hình cho LEFT encoder thay đổi. Tương tự, hàm ngắt cho RIGHT encoder được gọi khi trạng thái của các chân GPIO được cấu hình cho RIGHT encoder thay đổi.

Hai hàm ngắt này sử dụng một bảng tra cứu (lookup table) để xác định hướng quay của encoder dựa trên trạng thái hiện tại và trạng thái trước đó của các chân GPIO.*/
#ifdef USE_BASE

#ifdef ROBOGAIA
  /* The Robogaia Mega Encoder shield */
  #include "MegaEncoderCounter.h"

  /* Create the encoder shield object */
  MegaEncoderCounter encoders = MegaEncoderCounter(4); // Initializes the Mega Encoder Counter in the 4X Count mode
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return encoders.YAxisGetCount();
    else return encoders.XAxisGetCount();
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT) return encoders.YAxisReset();
    else return encoders.XAxisReset();
  }

#elif defined(ARDUINO_ENC_COUNTER)

  volatile long left_enc_pos = 0L;
  volatile long right_enc_pos = 0L;
  static const int8_t ENC_STATES [] = {0,1,-1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0};  //encoder lookup table
/*
void doEncoderA(){  

  // look for a low-to-high on channel A
  if (digitalRead(LEFT_ENC_PIN_A) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(LEFT_ENC_PIN_B) == LOW) {  
      left_enc_pos = left_enc_pos + 1;         // CW
    } 
    else {
      left_enc_pos = left_enc_pos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(LEFT_ENC_PIN_B) == HIGH) {   
      left_enc_pos = left_enc_pos + 1;          // CW
    } 
    else {
      left_enc_pos = left_enc_pos - 1;          // CCW
    }
  }
 
}

void doEncoderB(){  

  // look for a low-to-high on channel B
  if (digitalRead(LEFT_ENC_PIN_B) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(LEFT_ENC_PIN_A) == HIGH) {  
      left_enc_pos = left_enc_pos + 1;         // CW
    } 
    else {
      left_enc_pos = left_enc_pos - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(LEFT_ENC_PIN_A) == LOW) {   
      left_enc_pos = left_enc_pos + 1;          // CW
    } 
    else {
      left_enc_pos = left_enc_pos - 1;          // CCW
    }
  }
  

}

// ************** encoder 2 *********************

void doEncoderC(){  

  // look for a low-to-high on channel A
  if (digitalRead(RIGHT_ENC_PIN_A) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(RIGHT_ENC_PIN_B) == LOW) {  
      right_enc_pos = right_enc_pos - 1;         // CW
    } 
    else {
      right_enc_pos = right_enc_pos + 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(RIGHT_ENC_PIN_B) == HIGH) {   
      right_enc_pos = right_enc_pos - 1;          // CW
    } 
    else {
      right_enc_pos = right_enc_pos + 1;          // CCW
    }
  }
 
}

void doEncoderD(){  

  // look for a low-to-high on channel B
  if (digitalRead(RIGHT_ENC_PIN_B) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(RIGHT_ENC_PIN_A) == HIGH) {  
      right_enc_pos = right_enc_pos - 1;         // CW
    } 
    else {
      right_enc_pos = right_enc_pos + 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(RIGHT_ENC_PIN_A) == LOW) {   
      right_enc_pos = right_enc_pos - 1;          // CW
    } 
    else {
      right_enc_pos = right_enc_pos + 1;          // CCW
    }
  }
*/

  void R_ENA() {
    // Reading the current state of encoder A and B
      int RA = digitalRead(RIGHT_ENC_PIN_A);
      int RB = digitalRead(RIGHT_ENC_PIN_B);
    // If the state of A changed, it means the encoder has been rotated
    if ((RA == HIGH) != (RB == LOW)) {
      Rencoder_value--;
    } else {
      Rencoder_value++;
    } 
    //right_enc_pos += ENC_STATES[(Rencoder_value & 0x0f)];
    left_enc_pos =Lencoder_value++;
  }
  void L_ENA() {
      int LA = digitalRead(LEFT_ENC_PIN_A);
      int LB = digitalRead(LEFT_ENC_PIN_B);
    if ((LA == HIGH) != (LB == LOW)) {
      Lencoder_value--;
    } else {
      Lencoder_value++;
    }
   	//left_enc_pos += ENC_STATES[(Lencoder_value & 0x0f)];
    left_enc_pos=Lencoder_value++;
  }

  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return left_enc_pos;
    else return right_enc_pos;
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT){
      left_enc_pos=0L;
      return;
    } else { 
      right_enc_pos=0L;
      return;
    }
  }
#else
  #error A encoder driver must be selected!
#endif

/* Wrap the encoder reset function */
void resetEncoders() {
  resetEncoder(LEFT);
  resetEncoder(RIGHT);
}

#endif
// #endif