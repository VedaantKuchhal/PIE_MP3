// Import libraries for serial communication and interfacing with the motor shield.
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create DC motor objects for left and right motors.
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); // Object for the Adafruit motorshield.
Adafruit_DCMotor *Left = AFMS.getMotor(1); // Motor for left wheel.
Adafruit_DCMotor *Right = AFMS.getMotor(2); // Motor for right wheel. 

int vSpeed = 20;        // Forward drive speed for motors.
int serial_value=0;     // Serial variable to input forward drive speed from serial.
int turn_speed = 150;   // Turning speed for wheel when robot needs to turn.
int turn_delay = 20;    // The delay in milliseconds between each loop to smooth motion.
int n1=850;             // Right sensor threshold value for yes/no line detection
int n2=750;             // Left sensor threshold value for yes/no line detection


// Pins for IR sensor input.
const int left_sensor_pin =A0;
const int right_sensor_pin =A1;

// Variables to store the analog values read from those pins
int left_sensor_state;
int right_sensor_state;

// Set up serial and Adafruit Motor Shield (AFMS), have a three second delay before starting.
void setup() {
  Serial.begin(9600); // Initialize serial with baud rate of 9600.
  AFMS.begin();  // Begin motor shield.
  delay(3000); // Wait for three seconds. 
}

// Loop for controlling robot and serial communication.
void loop() {

  // Check if serial channel is available.
  if (Serial.available()> 0) {
    // Read the next valid integer in incoming serial.
    serial_value = Serial.parseInt();
    // If the value is within the valid range, set the motor speed to this value.
    if (serial_value > 0 && serial_value < 256) {
      // Set the motor speed to the input value.
      vSpeed=serial_value;}
  }
  
  // Read the analog values (on a scale of 0-1023) read from the IR sensors.
  left_sensor_state = analogRead(left_sensor_pin);
  right_sensor_state = analogRead(right_sensor_pin);
  
  // When left IR sensor is over black tape, turn left.
  if(right_sensor_state < n1 && left_sensor_state > n2)
  {
    // Make sure both motors are rotating forward.
    Left->run(FORWARD);
    Right->run(FORWARD);
  
    // Set the motor speeds so that the robot turns to the left.
    Left->setSpeed(0); // left wheel stops spinning.
    Right->setSpeed(turn_speed); // right wheel turns quickly.
  
    // Print the sensor values and motor speeds to serial monitor.
    Serial.print(right_sensor_state); Serial.print(",");
    Serial.print(left_sensor_state); Serial.print(",");
    Serial.print(turn_speed); Serial.print(",");
    Serial.println(0);
  
    // Pause before next sampling.
    delay(turn_delay);
  }


  // When right IR sensor is over black tape, turn right.
  if(right_sensor_state > n1 && left_sensor_state < n2)
  {
    // Make sure both motors are rotating forward.
    Left->run(FORWARD);
    Right->run(FORWARD);
  
    // Set the motor speeds so that the robot turns to the right.
    Right->setSpeed(0); // right wheel stops spinning.
    Left->setSpeed(turn_speed); // left wheel turns quickly.
  
    // Print the sensor values and motor speeds to serial monitor.
    Serial.print(right_sensor_state); Serial.print(",");
    Serial.print(left_sensor_state); Serial.print(",");
    Serial.print(0); Serial.print(",");
    Serial.println(turn_speed);
  
    // Pause before next sampling.
    delay(turn_delay);
  }
  
    
  // When neither sensors are over the black tape, drive forward.
  if(right_sensor_state < n1 && left_sensor_state < n2)
  {
  
    // Make sure both motors are rotating forward.
    Left->run(FORWARD);
    Right->run(FORWARD);
  
    // Set both motor speeds to be equal so that the robot drives forward.
    Left->setSpeed(vSpeed);
    Right->setSpeed(vSpeed);
  
    // Print the sensor values and motor speeds to serial monitor.
    Serial.print(right_sensor_state); Serial.print(",");
    Serial.print(left_sensor_state); Serial.print(",");
    Serial.print(vSpeed); Serial.print(",");
    Serial.println(vSpeed);
  
    // Pause before next sampling.
    delay(turn_delay);
  }
  
  
  // When both sensors are over black tape, stop.
  if(right_sensor_state > n1 && left_sensor_state > n2)
  { 
    // Release both the motors so that they stop spinning.
    Left->run(RELEASE);
    Right->run(RELEASE);
  
    // Set both motor speeds to zero.
    Left->setSpeed(0);
    Right->setSpeed(0);
  
    // Print the sensor values and motor speeds to serial monitor.
    Serial.print(right_sensor_state); Serial.print(",");
    Serial.print(left_sensor_state); Serial.print(",");
    Serial.print(0); Serial.print(",");
    Serial.println(0);
  
    // Pause before next sampling.
    delay(turn_delay);
  }
}
