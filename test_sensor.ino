//Sensor Connection
  const int left_sensor_pin =A0;
  const int right_sensor_pin =A1;
void setup() {
  // put your setup code here, to run once:
  pinMode(left_sensor_pin, INPUT);
  pinMode(right_sensor_pin, INPUT);
  long baudRate = 9600;
  Serial.begin(baudRate);
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading_left = analogRead(left_sensor_pin);
  int reading_right = analogRead(right_sensor_pin);
  Serial.print(reading_left); Serial.print(", ");
  Serial.println(reading_right);
  delay(400);
}

// 800 is a good threshold?
