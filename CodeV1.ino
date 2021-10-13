#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

//creating objects
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //this may need to move, may need reconfiguring
Adafruit_DCMotor *Left = AFMS.getMotor(1); //motor from port 1
Adafruit_DCMotor *Right = AFMS.getMotor(2); //motor from port 2

  int vSpeed = 110;        // MAX 255
  int turn_speed = 230;    // MAX 255, for wheel on inside of turn 
  int turn_delay = 10;
  int n1=500;              //sensor1 value for yes/no line detection
  int n2=500               //sensor2 value for yes/no line detection

//Motor shield commands
//myMotor->setSpeed(150); //speed set 0-255
//myMotor->run(FORWARD); //inputs FORWARD, BACKWARD, RELEASE

//Sensor Connection
  const int left_sensor_pin =A0;
  const int right_sensor_pin =A1;

  int left_sensor_state;
  int right_sensor_state;

void setup() {

  Serial.begin(9600);
  AFMS.begin();  //begins motor shield

  delay(3000);
  
}

void loop() {


left_sensor_state = analogRead(left_sensor_pin);
right_sensor_state = analogRead(right_sensor_pin);

Serials();

if(right_sensor_state > n1 && left_sensor_state < n2)
{
  Serial.println("turning right");

  Left->run(FORWARD);
  Right->run(FORWARD);

  Left->setSpeed(vSpeed); //speed set Left
  Right->setSpeed(turn_speed); //turn set Right

  
  }
if(right_sensor_state < n1 && left_sensor_state > n2)
{
  Serial.println("turning left");
  
  Left->run(FORWARD);
  Right->run(FORWARD);

  Right->setSpeed(vSpeed); //speed set Right
  Left->setSpeed(turn_speed); //turn set Left

  delay(turn_delay);
  }

if(right_sensor_state > n1 && left_sensor_state > n2)
{
  Serial.println("going forward");

  Left->run(FORWARD);
  Right->run(FORWARD);
  
  Left->setSpeed(vSpeed); //speed set Left
  Right->setSpeed(vSpeed); //speed set Right

  delay(turn_delay);
  
  }

if(right_sensor_state < n1 && left_sensor_state < n2)
{ 
  Serial.println("stop");

  Left->run(RELEASE);
  Right->run(RELEASE);
  
  Left->setSpeed(0); //speed set Left, stop
  Right->setSpeed(0); //speed set Right, stop
  
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
