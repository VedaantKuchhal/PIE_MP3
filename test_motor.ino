#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor_left = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor_right = AFMS.getMotor(2);

void setup() {
  AFMS.begin();
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  myMotor_left->setSpeed(150);     // set the speed to 150/255
  myMotor_right->setSpeed(150); 
}

void loop() {
  Serial.print("tick");

  myMotor_right->run(FORWARD); // turn it on going forward
  myMotor_left->run(FORWARD);
  delay(1000);

  Serial.print("tock");
  myMotor_right->run(BACKWARD);     // the other way
  myMotor_left->run(BACKWARD);
  delay(1000);

  Serial.print("tack");
  myMotor_right->run(RELEASE);      // stopped
  myMotor_left->run(RELEASE);
  delay(1000);
}
