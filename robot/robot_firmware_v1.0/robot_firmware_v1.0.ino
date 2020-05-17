
/*
 * 
 * David Riser, May 2020
 * 
 * This sketch will drive the robot forward 
 * until it detects an object, and then it will take
 * a random turn.  Now includes bluetooth ON/OFF.
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

enum modes {
    off = 0,
    on = 1  
};

enum motor {
    low = 160,
    high = 240,
    offset = 0  
};

// Constants, these don't change throughout
// the execution.
const int seconds             = 1000;
const int baudRate            = 9600;
const int objectTurnDist      = 3200;
const int medianFilterSamples = 8;
const int reverseDuration     = 1500; // Duration of reverse in milliseconds
const int turnsBeforeReverse  = 4;    
const int randomTurnMin       = 500;  // Duration of turn in milliseconds (min)
const int randomTurnMax       = 1500; // Duration of turn in milliseconds (max)
const int maxSonarDist        = 500;  // Distance in centimeters
const int startDelay          = 10;   // Start delay in seconds
const char activateChar       = '1';
const char deactivateChar     = '0';

// Globals that can change state during
// operation.

namespace globals {
    int mode = modes::off;
    NewPing sonar(pins::trigger, pins::echo, maxSonarDist); 
}


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
  analogWrite(pins::enable_a, speed + motor::offset);
  analogWrite(pins::enable_b, speed);
  delay(timer);
  stop();
}

void go(int speed){
  analogWrite(pins::enable_a, speed + motor::offset);
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
    goFor(motor::low, random(randomTurnMin,randomTurnMax));
}

void activate(){
  setForward();
  go(motor::low);
  
  int dist = globals::sonar.ping_median(medianFilterSamples);
  int stuckIter = 0;
  while (dist < objectTurnDist){

    // If we are really in trouble, 
    // try going backwards.  Don't 
    // do this much because we have no
    // sensors out back to protect us.
    if (stuckIter > turnsBeforeReverse){
      stop();
      setReverse();
      goFor(motor::low, reverseDuration);
      stop();

      stuckIter = 0;
    }

    // Normally we just need to turn randomly and 
    // check for a clear path. 
    stop();
    turnRandomly();
    stop();

    dist = globals::sonar.ping_median(medianFilterSamples);
    stuckIter++; 
  }  
}

void setup() {
  pinMode(pins::enable_a, OUTPUT);
  pinMode(pins::input_1, OUTPUT);
  pinMode(pins::input_2, OUTPUT);
  pinMode(pins::enable_b, OUTPUT);
  pinMode(pins::input_3, OUTPUT);
  pinMode(pins::input_4, OUTPUT);

  // Allow a slight delay upon start.
  delay(startDelay * seconds);

  // Make sure that the robot is
  // initialized in the stop position
  // and is ready to go forward.
  stop();

  // Set for listening to bluetooth 1/0
  Serial.begin(baudRate);
}

void loop() {

  // Await a bluetooth initialization
  // signal before starting to drive.
  if (Serial.available() > 0){
      char data = Serial.read();

      if (data == activateChar){
          globals::mode = modes::on;
      }
      else if (data == deactivateChar){
          globals::mode = modes::off;  
      }
  }  

  // Only drive if mode is activated 
  // by bluetooth.
  if (globals::mode == modes::on){
      activate();  
  }
  
}
