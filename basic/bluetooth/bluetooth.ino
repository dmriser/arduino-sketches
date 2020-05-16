/*
 * Simple blink LED with bluetooth sketch.  This
 * uses HC-06 bluetooth sensor.
 * 
 * David Riser, May 2020
 * 
 */

#include <SoftwareSerial.h>

enum pins {
  led = 13,
  tx = 1,
  rx = 0
};

const static int b_rate = 9600;

SoftwareSerial bluetooth(pins::tx, pins::rx);

void setup(){
  pinMode(pins::led, OUTPUT);

  // Start serial for testing.
  Serial.begin(b_rate);

  // Start the bluetooth with a default
  // baud rate defined above.  Send a 
  // simple test message to the connected
  // device.
  bluetooth.begin(b_rate);
  bluetooth.println("Arduino setup function done!");
}


void loop(){

    if (bluetooth.available()){
        Serial.write(bluetooth.read());
    }

    if (Serial.available()){
        bluetooth.write(Serial.read());  
    }
}
