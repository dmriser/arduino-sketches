
/*

   For calibration of turning left/right with the robot
   that I have created.

*/

#include "NewPing.h"

enum pins {
  enable_a = 6,
  enable_b = 9,
  input_1 = 2,
  input_2 = 3,
  input_3 = 2,
  input_4 = 4,
  trigger = 10,
  echo = 11
};

// Max dist 500cm
NewPing sonar(pins::trigger, pins::echo, 500);

// This value is added to the left/right motor.
// I am not sure.
const int motorOffset = 0;
const int motorLow = 100;
const int motorHigh = 200;
const int seconds = 1000;

void setLeft() {
  digitalWrite(pins::input_1, LOW);
  digitalWrite(pins::input_2, HIGH);
  digitalWrite(pins::input_3, HIGH);
  digitalWrite(pins::input_4, LOW);
}

void setRight() {
  digitalWrite(pins::input_1, HIGH);
  digitalWrite(pins::input_2, LOW);
  digitalWrite(pins::input_3, LOW);
  digitalWrite(pins::input_4, HIGH);
}

void setForward() {
  digitalWrite(pins::input_1, LOW);
  digitalWrite(pins::input_2, HIGH);
  digitalWrite(pins::input_3, LOW);
  digitalWrite(pins::input_4, HIGH);
}

void setBackward() {
  digitalWrite(pins::input_1, HIGH);
  digitalWrite(pins::input_2, LOW);
  digitalWrite(pins::input_3, HIGH);
  digitalWrite(pins::input_4, LOW);
}

void stop() {
  analogWrite(pins::enable_a, 0);
  analogWrite(pins::enable_b, 0);
}

void goFor(int speed, int timer) {
  analogWrite(pins::enable_a, speed + motorOffset);
  analogWrite(pins::enable_b, speed);
  delay(timer);
  stop();
}

void go(int speed){
  analogWrite(pins::enable_a, speed + motorOffset);
  analogWrite(pins::enable_b, speed); 
}

void setup() {
  pinMode(pins::enable_a, OUTPUT);
  pinMode(pins::input_1, OUTPUT);
  pinMode(pins::input_2, OUTPUT);
  pinMode(pins::enable_b, OUTPUT);
  pinMode(pins::input_3, OUTPUT);
  pinMode(pins::input_4, OUTPUT);

  // Allow a slight delay upon start.
  delay(10 * seconds);

  // Make sure that the robot is
  // initialized in the stop position
  // and is ready to go forward.
  stop();
}

void loop() {
  
  setForward();
  go(motorLow);
  
  int dist = sonar.ping_median(8);
  if (dist < 3200){

    stop();
    if (random(0,1) < 0.5){ setLeft(); }
    else { setRight(); }
    goFor(motorLow, 500);
    stop();
    
  }
  
}
