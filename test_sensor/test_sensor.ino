// Define the analog input pins numbers for the sensors.
  const int left_sensor_pin =A0;
  const int right_sensor_pin =A1;

// Set pins as input and begin serial.
void setup() {
  // Set pins as input.
  pinMode(left_sensor_pin, INPUT);
  pinMode(right_sensor_pin, INPUT);
  // Initialize serial.
  long baudRate = 9600;
  Serial.begin(baudRate);
}

void loop() {
  // Read the voltages at the analog input pins.
  // A voltage of 0-5 V is mapped onto a 10-1023 scale.
  int reading_left = analogRead(left_sensor_pin);
  int reading_right = analogRead(right_sensor_pin);

  // Print the analog readings onto serial monitor.
  Serial.print(reading_left); Serial.print(", ");
  Serial.println(reading_right);
  delay(400);
}

// 800 is a good threshold?
