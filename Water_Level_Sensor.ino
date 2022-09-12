// Sensor pins
#define sensorPower 7
#define sensorPin A0

// Value for storing waterLevel
int Val = 0;

void setup() {
  // Set Digital 7 as an output
  pinMode(sensorPower, OUTPUT);

  // Set to LOW so no power flows through the sensor
  digitalWrite(sensorPower, LOW);

  // Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
}

void loop() {
  //get the reading from the function below and print it
  int level = readSensor();

  Serial.print("Water level: ");
  Serial.println(level);

  if (level < 50 ) {
    Serial.print("ALERT");
  }else {
    Serial.print("Continue");
  }
  
  delay(1000); // Also here is where we can set the time duration of when the next reading will begin
               // 1000 milliseconds makes up 1 second
}

//This is a function used to get the reading
int readSensor() {
  digitalWrite(sesnsorPower, HIGH); // Turn the sensor ON
  delay(10);                        // wait 10 milliseconds.
  Val = analogRead(sensorPin);      // Read the analog value from sensor
  digitalWrite(sensorPower, LOW);   // Turn the sensor OFF
  return Val;                       // Send current reading
}
