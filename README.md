# Lake-Water-Level-Cavanaugh
I began by seting up the DS18B20 temperature sensor with the ESP8266 shown in the TempSensor8266.ino file. 
After gaining comfort with the ESP8266 and how it differs from an Arduino Nano or Arduino Uno I then followed [the tutorial by Random Nerd Tutorials](https://randomnerdtutorials.com/esp32-esp8266-publish-sensor-readings-to-google-sheets/)  to setup measurement recordings using Google Sheets.

Along the way I was able to combine what I knew about the temperature sensor and the above Google Sheets example and recorded temperatures. That quickly became another project for my aquarium in monitoring the temperature throughout the day. Back to the lake level project. One important thing to note was the need to connect the RST pin to GPIO 16 on the ESP8266 after programming to enable the `
ESP.deepSleep()` cycle. This was a new thing for me and the [article here](https://randomnerdtutorials.com/esp8266-deep-sleep-with-arduino-ide/) goes into more depth.

I received the HC-SR04 Ultrasonic Distance sensor and took a step back. I have found that its important to not pile too much into a project at one time without any opportunity for debugging and solving unexpected problems. With that I moved back to the TempSensor8266.ino file and copied that over to a new project SonarTemp8266.ino, and made sure the sensor interface with the ESP8266 works. I followed the [guide by Makerguides.com here](https://www.makerguides.com/jsn-sr04t-arduino-tutorial/)

Learned that D2 pin does not mean pin 2, in fact it correlates to 4 in the Arduino IDE. I followed the [image here](https://www.electronicwings.com/nodemcu/nodemcu-gpio-with-arduino-ide). The GPIO pin number matters over the digital pin number. 

Here is the datasheet for the [HC-SR04 Ultrasonic Distance sensor](https://www.makerguides.com/wp-content/uploads/2019/02/HCSR04-Datasheet.pdf)

I encountered a problem with the baud rate or symbol rate that the ESP8266 uses for the temperature sensor is different than that of the sonar sensor. The sonar sensor operates at 9600 baud while the temperature sensor examples that I was working off of used 115200. This became quite an obstacle for me as using two separate baud rates on a single device depends on the hardware available. My solution was picking the more standard baud of 9600 as I learned the temperature sensor actually works at both rates. This solution is shown in the SonarTemp.ino.

I got the two sensors working and sending outputs that looked like this 
```` 
22.13ºC
71.82ºF
Distance = 28.34 in
```` 
So awesome! 

Using a tape measure and a cardboard box, I placed the box at the end of the tape measure and moved the sonar sensor along the tape measure taking note of the difference in length in the measured distance and the actual length. An adjustment of 1.17 in was added to the output distance value. 

The sonar sensor had a bit of an angle to the  direction of propagation. As a verification of distance measurements and their accuracy, I measured the distance from the hardwood floor, to the bottom edge of the table top, where the sensor would rest at 28.4 in. The measured distance from sensor to floor came in at 28.34 in, a 0.06 in difference I can live with.

With both major sensing components working synchronously, I moved on to outputting measurements to the Google Sheets document. 

Moved Echo pin on the HC-SR04 from GPPIO pin 0 to 10, as pin 0 has to do with the FLASH function of the ESP8266 and that interfered with the uploading and flashing of new code. 

To get the resource variable from [Webhooks](https://ifttt.com/maker_webhooks) and place the resource variable in my code. Mine was something like `"/trigger/lake_water_level/with/key/nAZjOphL3d-ZO4N3k64-1A7gTlNSrxMJdmqy3"`