/* 
 *  Sketch to test the HC-SR04 sonar sensor.  This
 *  time do some filtering. 
 */

#include <NewPing.h>

enum pins {
  trigger = 9,
  echo = 3
};

const int MAX_DIST = 400; 

NewPing sonar(pins::trigger, pins::echo, MAX_DIST);

void setup(){
  Serial.begin(9600);
}

void loop(){
  //delay(50);
  Serial.println(sonar.ping_median(8));
}
