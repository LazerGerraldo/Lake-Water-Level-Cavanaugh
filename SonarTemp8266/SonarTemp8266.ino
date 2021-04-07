/* Arduino example sketch to control a JSN-SR04T ultrasonic distance sensor with Arduino. No library needed. More info: https://www.makerguides.com */

// Define Trig and Echo pin:
#define trigPin 2
#define echoPin 0
#include <OneWire.h>
#include <DallasTemperature.h>

// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;     

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
// Define variables:
long duration;
int distance;
int distOffset; // calibration distance value for lake level

void setup() {
  // Define inputs and outputs of JSN-SR04T
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Begin Serial communication at a baudrate of 9600:
  Serial.begin(9600);
  // Start the DS18B20 sensor
  sensors.begin();
}

void loop() {
  // Clear the trigPin by setting it LOW:
  digitalWrite(trigPin, LOW);
  
  delayMicroseconds(5);

 // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance:
  distance = (duration*0.034/2) + 2.97; // add 2.97 for calibration difference

  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
  Serial.print(temperatureF);
  Serial.println("ºF");
  
  // Print the distance on the Serial Monitor (Ctrl+Shift+M):
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.print(distance / 2.54); // convert to inches and add the calibration value
  Serial.println(" in");
  delay(100);
}
