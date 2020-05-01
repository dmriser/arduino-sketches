
/* 

  Sketch adapted to control L298N.  
  Source: https://howtomechatronics.com/tutorials/arduino/arduino-dc-motor-control-tutorial-l298n-pwm-h-bridge/

*/

const int enA = 9;
const int in1 = 6; 
const int in2 = 7;
const int motorLow = 50;
const int motorHigh = 120;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Initialize the direction
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void loop() {

  // PWM to L298N (0-255)
  analogWrite(enA, motorLow);
  
  // We are going forward/backward for 5 seconds
  // then we change directions.
  delay(5000);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
}
