/*
arduino_servo

Demonstrates the control of servo motors connected to an Arduino board
running the StandardFirmata firmware.  Moving the mouse horizontally across
the sketch changes the angle of servo motors on digital pins 4 and 7.  For
more information on servo motors, see the reference for the Arduino Servo
library: http://arduino.cc/en/Reference/Servo

To use:
* Using the Arduino software, upload the StandardFirmata example (located
  in Examples > Firmata > StandardFirmata) to your Arduino board.
* Run this sketch and look at the list of serial ports printed in the
  message area below. Note the index of the port corresponding to your
  Arduino board (the numbering starts at 0).  (Unless your Arduino board
  happens to be at index 0 in the list, the sketch probably won't work.
  Stop it and proceed with the instructions.)
* Modify the "arduino = new Arduino(...)" line below, changing the number
  in Arduino.list()[0] to the number corresponding to the serial port of
  your Arduino board.  Alternatively, you can replace Arduino.list()[0]
  with the name of the serial port, in double quotes, e.g. "COM5" on Windows
  or "/dev/tty.usbmodem621" on Mac.
* Connect Servos to digital pins 4 and 7.  (The servo also needs to be
  connected to power and ground.)
* Run this sketch and move your mouse horizontally across the screen.
  
For more information, see: http://playground.arduino.cc/Interfacing/Processing
*/

import processing.serial.*;

import cc.arduino.*;

Arduino arduino;
  int enA = 6;
  int enB = 5;
  int in1 = 7;
  int in2 = 8;
  int in3 = 9;
  int in4 = 11;
  
void setup() {
  size(360, 200);
  
  // Prints out the available serial ports.
  println(Arduino.list());
  
  // Modify this line, by changing the "0" to the index of the serial
  // port corresponding to your Arduino board (as it appears in the list
  // printed by the line above).
  arduino = new Arduino(this, Arduino.list()[0], 57600);
  
  // Alternatively, use the name of the serial port corresponding to your
  // Arduino (in double-quotes), as in the following line.
  //arduino = new Arduino(this, "/dev/tty.usbmodem621", 57600);

  // Configure digital pins 4 and 7 to control servo motors.
  arduino.digitalWrite(enA, Arduino.INPUT);
  arduino.digitalWrite(enB, Arduino.INPUT);
  arduino.pinMode(in1, Arduino.INPUT);
  arduino.pinMode(in2, Arduino.INPUT);
  arduino.pinMode(in3, Arduino.INPUT);
  arduino.pinMode(in4, Arduino.INPUT);

}

void draw() {
  background(constrain(mouseX / 2, 0, 180));
  
  // Write an value to the servos, telling them to go to the corresponding
  // angle (for standard servos) or move at a particular speed (continuous
  // rotation servos).
  arduino.analogWrite(enA, constrain(mouseX / 2, 0, 255));
  arduino.analogWrite(enB, constrain(mouseX / 2, 0, 255));
  arduino.digitalWrite(in1, Arduino.HIGH);
  arduino.digitalWrite(in4, Arduino.HIGH);
  arduino.digitalWrite(in2, Arduino.LOW);
  arduino.digitalWrite(in3, Arduino.LOW);
  //arduino.servoWrite(6, constrain(180 - mouseX / 2, 0, 180));
  //arduino.servoWrite(11, constrain(180 - mouseX / 2, 0, 180));
}