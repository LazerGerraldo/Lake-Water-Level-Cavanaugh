/*
 * Jamie Bernard
 * 4/7/2021 
 *  Sonar sensor and temperature sensors hooked up to ESP8266 to measure and record 
 *  temperature of body of water, and distance of 
 */
 
#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif

// Define Trig and Echo pin for JSN-SR04T
#define trigPin 14
#define echoPin 12

// DS18B20 connections
#include <OneWire.h>            // include temp sensor
#include <DallasTemperature.h>  // include temp sensor
#include <Wire.h>

// Replace with your SSID and Password
const char* ssid     = "SSID";
const char* password = "Password";

// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;
// Setup a oneWire instance to communicate with DS18B20
OneWire oneWire(oneWireBus);
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

// Define variables:
float distInch;  // distance measured in in
int sensorHeight = 1013; // altitude adjustment of lake level
// Time to sleep
uint64_t TIME_TO_SLEEP = 1800000; // in milliseconds 12 hours 43200000 milliseconds, 60000 milliseconds in one minute for testing

// Replace with your unique IFTTT URL resource
const char* resource = "See Example resource variable below, should be your own api key";
// How your resource variable should look like, but with your own API KEY (that API KEY below is just an example):
//const char* resource = "/trigger/bme280_readings/with/key/nAZjOphL3d-ZO4N3k64-1A7gTlNSrxMJdmqy3";

// Maker Webhooks IFTTT
const char* server = "maker.ifttt.com";
#define SEALEVELPRESSURE_HPA (1013.25)

void setup() {
  delay(2000);
  
  // Define inputs and outputs of JSN-SR04T
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Begin Serial communication at a baudrate of 9600:
  Serial.begin(9600);
  // Start the DS18B20 sensor
  sensors.begin();
  Serial.println("********runing setup********");
}

void loop() {
//  setup();
  initWifi();
  makeIFTTTRequest();

  Serial.println("********Sleeping********");
  delay(TIME_TO_SLEEP);
  Serial.println("********AWAKE********");
  Serial.println("........starting loop again");
}

// Establish a Wi-Fi connection with your router
void initWifi() {
  Serial.print("Connecting to: "); 
  Serial.print(ssid);
  WiFi.begin(ssid, password);  

  int timeout = 10 * 4; // 10 seconds
  while(WiFi.status() != WL_CONNECTED  && (timeout-- > 0)) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");

  if(WiFi.status() != WL_CONNECTED) {
     Serial.println("Failed to connect, going back to sleep");
  }

  Serial.print("WiFi connected in: "); 
  Serial.print(millis());
  Serial.print(", IP address: "); 
  Serial.println(WiFi.localIP());
}

// Make an HTTP request to the IFTTT web service
void makeIFTTTRequest() {
  Serial.print("Connecting to "); 
  Serial.print(server);
  
  WiFiClient client;
//  int retries = 5;
//  while(!!!client.connect(server, 80) && (retries-- > 0)) {
//    Serial.print(".");
//  }
  while(!!!client.connect(server, 80)) { // keep trying to connect to wifi until connection is made
    Serial.print(".");
  }
  Serial.println();
  if(!!!client.connected()) {
    Serial.println("Failed to connect...");
  }
  
  Serial.print("Request resource: "); 
  Serial.println(resource);

  //  run sonar sensor
  distInch = Sonar();
  
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);

  // output object to 
  String jsonObject = String("{\"value1\":\"") + sensors.getTempFByIndex(0) + "\",\"value2\":\"" + sensors.getTempCByIndex(0) + "\",\"value3\":\"" + distInch + "\"}";
                      
  // Comment the previous line and uncomment the next line to publish temperature readings in Fahrenheit                    
  /*String jsonObject = String("{\"value1\":\"") + (1.8 * bme.readTemperature() + 32) + "\",\"value2\":\"" 
                      + (bme.readPressure()/100.0F) + "\",\"value3\":\"" + bme.readHumidity() + "\"}";*/
                      
  client.println(String("POST ") + resource + " HTTP/1.1");
  client.println(String("Host: ") + server); 
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);
        
  int timeout = 5 * 10; // 5 seconds             
  while(!!!client.available() && (timeout-- > 0)){
    delay(100);
  }
  if(!!!client.available()) {
    Serial.println("No response...");
  }
  while(client.available()){
    Serial.write(client.read());
  }
  
  Serial.println("\nclosing connection");
  client.stop(); 
}

// funciton to read and average sonar values over a set time period, returns the difference between the height 
//calibration (how high the sensor is above sea level) and the measured sonar distance
float Sonar(){
  long duration; // duration (length of JSN-SR04T sonar pulse) in microseconds
  float distance;  // distance measured by JSN-SR04T in cm
  float sumS = 0;   // sum of  given measurements
  int counts = 0; // number of measurements taken
  float level = 0;  // overall lake level

  // takes 50 measurments over the span of 
  while (counts <= 50){
    // Clear the trigPin by setting it LOW:
    digitalWrite(trigPin, LOW);   
    delayMicroseconds(5);
  
    // Trigger the sensor by setting the trigPin high for 10 microseconds:
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds:
    duration = pulseIn(echoPin, HIGH);
    distance = (duration*0.034/2.0) / 2.54 + 1.17; // divide by 2.54 for cm to inches add 1.17 inch calibration offset value
    distance = distance / 12.0; // convert from inches to feet
    
    if (distance <= 6){
      //debugging printing for absolute distance measurment in feet
//      Serial.print("Distance ");
//      Serial.println(distance);

      sumS = sumS + distance; // add current reading to sum of readings
      counts++;               // increment count
      level = sumS / counts;  // average total sum of measurements by number of measurements
    }
    delay(100);
  }
  Serial.println(level);
//  return level + sensorHeight;  // add sensorHeight offset value to final measured value
  return sensorHeight - level;    // subtract reading from sensor level
}
