# Smart Parking System
This project uses a combination of distance measurement as well as image processing to provide real time parking updates.

## Overview
This is a simple smart parking system which utilises a combination of ultrasonic sensors as well as a camera (esp32 cam for car detection using opencv) to give users real time updates on the parking spot availability. It also provides a prediction system where users can check the probability of the spot being occupied at a given time on any day of the week.

## Parts Used
1. NodeMCU (ESP8266)
2. Ultrasonic Sensor
3. ESP32 CAM
4. 16x2 LCD Display

## Steps
The code for the camera and the ultrasonic has been written. The Ultrasonic was connected to the NodeMCU esp8266 along with an lcd to display whether a spot is occupied or not. The esp32 cam was connected directly to the laptop.



## TO DO
1. Add at least one more ultrasonic sensor, in order to increase the capacity.
2. Change the way the number of spots are displayed on the lcd.
3. Could add a few ir sensors to detect a car at the entrance of the parking lot, this will open and close the gate which could remain closed if all spots are occupied
