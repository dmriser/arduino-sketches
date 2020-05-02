
/* 

  Sketch adapted to control L298N.  
  Source: https://howtomechatronics.com/tutorials/arduino/arduino-dc-motor-control-tutorial-l298n-pwm-h-bridge/

*/

const int enA = 9;
const int in1 = 6; 
const int in2 = 7;
const int motorLow = 30;
const int motorHigh = 80;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Allow a slight delay upon start.
  delay(1000);

  // Initialize the direction
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // PWM to L298N (0-255)
  analogWrite(enA, motorLow);
}

void loop() {

  // Initialize the direction
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(5000);

  // We are going forward/backward for 5 seconds
  // then we change directions.
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(5000);    
}
