#include <SoftwareSerial.h>

//Sensor pins
#define sensorPower 7
#define sensorPin A0

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); // SIM800L Tx AND Rx is connected to Arduino #3 and #2

// Value for storing waterLevel
int Val = 0;

void setup() {
  // Set Digital 7 as an output
  pinMode(sensorPower, OUTPUT);

  // Set to  LOW so no power flows through the sensor
  digitalWrite(sensorPower, LOW);
  
  // Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);

  // Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing");
  delay(1000);

  // Arduino Interacting with GSM and SIM CARD
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+254708103807\""); // the country code and the phone number that will receive the SMS
  updateSerial();
  //mySerial.println("ALERT !!! Soap level is below minumum for Dispenser number 1");  // text content
  //updateSerial();
  //mySerial.write(26); // ‘Ctrl+z’ is actually a 26th non-printing character described as ‘substitute’ in ASCII table
  
}

void loop() {
  // The main code to run repeatedly
  // Get the reading from the readSensor function
  int level = readSensor();

  if (level < 50) {
    mySerial.print(level);
    mySerial.println("ALERT !!! Soap level is below minimum, please refill dispenser");
    updateSerial();
    mySerial.write(26); // ‘Ctrl+z’ is actually a 26th non-printing character described as ‘substitute’ in ASCII table
  }
  else {
    
  }
  //Serial.print("Water Level: ");
  //Serial.println(level);          
}

// This function is used to get the reading from the sensor
int readSensor() {
  digitalWrite(sensorPower, HIGH); // Turn the sensor ON.
  delay(10);                       // Wait 10 millisenconds.
  Val = analogRead(sensorPin);     // Read the analog value(i.e pin A0) from sensor.
  digitalWrite(sensorPower, LOW);  // Turn the sensor OFF.
  return Val;                      // Send current reading.
  
}

void updateSerial() {
  delay(60000); // Also here is where we can set the time duration of when the next reading will begin
                // 60000 milliseconds makes up 1 minutes. 300000 ,illiseconds makes up 5 minutes
                
  while (Serial.available()) {
    mySerial.write(Serial.read()); // Foward what Serial received to software serial port
  }
  while(mySerial.available()) {
    Serial.write(mySerial.read()); // Forward what Software serial received to serial port
  }
}
