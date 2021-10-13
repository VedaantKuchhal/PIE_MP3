#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

//creating objects
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //this may need to move, may need reconfiguring
Adafruit_DCMotor *myMotor = AFMS.getMotor(1); //motor from port 1

  int vSpeed = 110;        // MAX 255
  int turn_speed = 230;    // MAX 255 
  int turn_delay = 10;
  int n=500;               //sensor value for yes/no line detection


//Motor shield commands
//myMotor->setSpeed(150); speed set 0-255
//myMotor->run(FORWARD); inputs FORWARD, BACKWARD, RELEASE


  
//L293 Connection   (This may be unnessesary as we are using a defferent motor shield)
  const int motorA1      = 8;  
  const int motorA2      = 10; 
  const int motorAspeed  = 9;
  const int motorB1      = 12; 
  const int motorB2      = 13; 
  const int motorBspeed  = 11;

//Sensor Connection
  const int left_sensor_pin =A0;
  const int right_sensor_pin =A1;

  
  
  int left_sensor_state;
  int right_sensor_state;

void setup() {
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

  Serial.begin(9600);
  AFMS.begin();  //begins motor shield

  delay(3000);
  
}

void loop() {


left_sensor_state = analogRead(left_sensor_pin);
right_sensor_state = analogRead(right_sensor_pin);

if(right_sensor_state > n && left_sensor_state < n)
{
  Serial.println("turning right");

  digitalWrite (motorA1,LOW);
  digitalWrite(motorA2,HIGH);                       
  digitalWrite (motorB1,LOW);
  digitalWrite(motorB2,HIGH);

  analogWrite (motorAspeed, vSpeed);
  analogWrite (motorBspeed, turn_speed);
  
  }
if(right_sensor_state < n && left_sensor_state > n)
{
  Serial.println("turning left");
  
  digitalWrite (motorA1,HIGH);
  digitalWrite(motorA2,LOW);                       
  digitalWrite (motorB1,HIGH);
  digitalWrite(motorB2,LOW);

  analogWrite (motorAspeed, turn_speed);
  analogWrite (motorBspeed, vSpeed);

  delay(turn_delay);
  }

if(right_sensor_state > n && left_sensor_state > n)
{
  Serial.println("going forward");

  digitalWrite (motorA2,LOW);
  digitalWrite(motorA1,HIGH);                       
  digitalWrite (motorB2,HIGH);
  digitalWrite(motorB1,LOW);

  analogWrite (motorAspeed, vSpeed);
  analogWrite (motorBspeed, vSpeed);

  delay(turn_delay);
  
  }

if(right_sensor_state < n && left_sensor_state < n)
{ 
  Serial.println("stop");
  
  analogWrite (motorAspeed, 0);
  analogWrite (motorBspeed, 0);
  
  }

void Serials() {
    Serial.print(right_sensor_state);
    Serial.print(',');
    Serial.print(left_sensor_state);
    Serial.print(',');
    Serial.print(motorAspeed);
    Serial.print(',');
    Serial.print(motorBspeed);
    Serial.print(',');

}
 
}
