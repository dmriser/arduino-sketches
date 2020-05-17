/*
 * Simple blink LED with bluetooth sketch.  This
 * uses HC-06 bluetooth sensor.
 * 
 * David Riser, May 2020
 * 
 */

enum pins {
  led = 13
};

const static int b_rate = 9600;

void setup(){
  pinMode(pins::led, OUTPUT);
  Serial.begin(b_rate);
}


void loop(){

    if (Serial.available() > 0){
        char data = Serial.read();

        if (data == '1'){
            digitalWrite(pins::led, HIGH);  
        }

        else if (data == '0'){
            digitalWrite(pins::led, LOW);  
        }
    }
    
}
