#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

//creating objects
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //this may need to move, may need reconfiguring
Adafruit_DCMotor *Left = AFMS.getMotor(1); //motor from port 1
Adafruit_DCMotor *Right = AFMS.getMotor(2); //motor from port 2

  int vSpeed = 20;        // MAX 255
  int serial_value=0;            //serial variable
  int serial_status = 0;
  int serial_test = 0;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  AFMS.begin();  //begins motor shield

  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
if (Serial.available()> 0) {
  serial_test = Serial.parseInt();
  if (serial_test > 0) {
    serial_value=serial_test; //make sure you are not getting zeros, look at documentation for this command
    Serial.println(serial_value);
    vSpeed=serial_value;}
}

  Left->run(FORWARD);
  Right->run(FORWARD);

  Left->setSpeed(vSpeed); //speed set Left
  Right->setSpeed(vSpeed); //turn set Right

}
