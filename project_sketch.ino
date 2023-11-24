#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

const char *ssid = "OnePlus Nord 2T 5G";
const char *password = "hahahaha";
const char *thingSpeakApiKey = "389IL0OK3MHOAR6E";
const int trigPin = 12; // D6
const int echoPin = 14; // D5
const int distanceThreshold = 15;

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

WiFiClient client;

unsigned long hashString(const char *str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++) {
        hash = ((hash << 5) + hash) + c; 
    }

    return hash;
}

void setup() {
  Serial.begin(115200);
  Serial.println("Connecting to Wi-Fi...");

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


  lcd.init();
  lcd.backlight();
  lcd.clear();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi Connected");

  ThingSpeak.begin(client); // Pass the global WiFiClient object to ThingSpeak

  // You might need to add a delay here to ensure the WiFi connection is stable
  delay(2000);
}

void loop() {
  Serial.println("Measuring distance...");

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_VELOCITY / 2;
  distanceInch = distanceCm * CM_TO_INCH;

  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

  
/*
  if (distanceCm < distanceThreshold) {
    lcd.setCursor(7, 0);
    lcd.println(" Occupied");
    Serial.println("Parking spot is occupied");

    int response = ThingSpeak.writeField(2354454, 1, 1, thingSpeakApiKey);
    Serial.println("ThingSpeak response: " + String(response));
  } else {
    lcd.setCursor(7, 0);
    lcd.println("Available");
    Serial.println("Parking spot is available");

    int response = ThingSpeak.writeField(2354454, 1, 0, thingSpeakApiKey);
    Serial.println("ThingSpeak response: " + String(response));
  }
*/
  if (distanceCm < distanceThreshold) {
    lcd.setCursor(7, 0);
    lcd.println(" Occupied");
    Serial.println("Parking spot is occupied");

    // Hash the status before sending it to ThingSpeak
    unsigned long hashedStatus = hashString("1");
    String hashedStatusString = String(hashedStatus);
    int response = ThingSpeak.writeField(2354454, 1, hashedStatusString, thingSpeakApiKey);
    Serial.println("ThingSpeak response: " + String(response));
  } else {
    lcd.setCursor(7, 0);
    lcd.println("Available");
    Serial.println("Parking spot is available");

    // Hash the status before sending it to ThingSpeak
    unsigned long hashedStatus = hashString("0");
    String hashedStatusString = String(hashedStatus);
    int response = ThingSpeak.writeField(2354454, 1, hashedStatusString, thingSpeakApiKey);
    Serial.println("ThingSpeak response: " + String(response));
  }

  lcd.display();
  delay(1000);
}
