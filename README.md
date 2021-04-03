# Lake-Water-Level-Cavanaugh
I began by seting up the DS18B20 temperature sensor with the ESP8266 shown in the TempSensor8266.ino file. 
After gaining comfort with the ESP8266 and how it differs from an Arduino Nano or Arduino Uno I then followed the tutorial https://randomnerdtutorials.com/esp32-esp8266-publish-sensor-readings-to-google-sheets/ by Random Nerd Tutorials to setup measurment recordings using Google Sheets.
Along the way I was able to combine what I knew about the temperature sensor and the above Google Sheets example and recorded temperatures. That quickly became another project for my aquarium in monitoring the temperature throughout the day. Back to the lake level project. 

I recieved the HC-SR04 Ultrasonic Distance formula and took a step back. I have found that its important to not pile too much into a project at one time without any opportunity for debugging and solving unexpected problems. With that I moved back to the TempSensor8266.ino file and copied that over to a new project SonarTemp8266.ino and made sure the sensor interface with the ESP8266 works. 
