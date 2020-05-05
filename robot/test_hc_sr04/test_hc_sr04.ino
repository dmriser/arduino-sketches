/* 
 *  Sketch to test the HC-SR04 sonar sensor.
 *  
 */

enum pins {
  trigger = 9,
  echo = 10
};

void setup(){  
    pinMode(pins::trigger, OUTPUT);
    pinMode(pins::echo, INPUT);
    Serial.begin(9600);
}

void loop(){

  // Short pulse to clean followed 
  // by longer sense pulse.  The trigger
  // pulse needs to be at least 10 microseconds.
  digitalWrite(pins::trigger, LOW);
  delayMicroseconds(5);
  digitalWrite(pins::trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pins::trigger, LOW);

  float duration = pulseIn(pins::echo, HIGH);
  Serial.println(duration / 74.0);
  delay(100);
}
