
/*
 * 
 * David Riser, May 2020
 * 
 * This simple sketch will drive the robot forward 
 * until it detects an object, and then it will take
 * a random turn.
 * 
 */

#include "NewPing.h"

enum pins {
  enable_a = 6,
  enable_b = 9,
  input_1 = 2,
  input_2 = 3,
  input_3 = 5,
  input_4 = 4,
  trigger = 10,
  echo = 11
};

// Max dist 500cm
NewPing sonar(pins::trigger, pins::echo, 500);

// This value is added to the left/right motor.
// I am not sure.
const int motorOffset = 0;
const int motorLow = 160;
const int motorHigh = 240;
const int seconds = 1000;

void setLeft() {
  digitalWrite(pins::input_1, LOW);
  digitalWrite(pins::input_2, HIGH);
  digitalWrite(pins::input_3, LOW);
  digitalWrite(pins::input_4, HIGH);
}

void setRight() {
  digitalWrite(pins::input_1, HIGH);
  digitalWrite(pins::input_2, LOW);
  digitalWrite(pins::input_3, HIGH);
  digitalWrite(pins::input_4, LOW);
}

void setReverse() {
  digitalWrite(pins::input_1, LOW);
  digitalWrite(pins::input_2, HIGH);
  digitalWrite(pins::input_3, HIGH);
  digitalWrite(pins::input_4, LOW);
}

void setForward() {
  digitalWrite(pins::input_1, HIGH);
  digitalWrite(pins::input_2, LOW);
  digitalWrite(pins::input_3, LOW);
  digitalWrite(pins::input_4, HIGH);
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

void turnRandomly(){
    
    if (random(2) < 1){ 
      setLeft(); 
    }
    else { 
      setRight(); 
    }

    // Turn a random amount, usually this is between
    // a quarter turn and three quarters.  It depends
    // on the speed setting.
    goFor(motorLow, random(500,1500));
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
  int stuckIter = 0;
  while (dist < 3200){

    // If we are really in trouble, 
    // try going backwards.  Don't 
    // do this much because we have no
    // sensors out back to protect us.
    if (stuckIter > 4){
      stop();
      setReverse();
      goFor(motorLow, 500);
      stop();

      stuckIter = 0;
    }

    // Normally we just need to turn randomly and 
    // check for a clear path. 
    stop();
    turnRandomly();
    stop();

    dist = sonar.ping_median(8);
    stuckIter++; 
  }
  
}
