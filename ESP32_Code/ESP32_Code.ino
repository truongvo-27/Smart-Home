#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <SharpGP2Y10.h>
#include "DHT.h"

// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "ESP32"
#define WIFI_PASSWORD "0907923187a"

// Insert Firebase project API Key
#define API_KEY "AIzaSyBpPYuInq9aazvDD6ot28p4IT5kQwzYtk0"
// Insert RTDB URL
#define DATABASE_URL "https://smart-city-60734-default-rtdb.asia-southeast1.firebasedatabase.app/" 

#define DHTPIN 26  
#define DHTTYPE DHT11

#define CONTROL_LED_PIN_1 25  
#define CONTROL_LED_PIN_2 21  
#define CONTROL_LED_PIN_3 22
// Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;
int ledStatus1 = 0; // Local variable to store LED 1 status (0 = OFF, 1 = ON)
int ledStatus2 = 0; // Local variable to store LED 2 status (0 = OFF, 1 = ON)
int ledStatus3 = 0; // Local variable to store LED 3 status (0 = OFF, 1 = ON)

DHT dht(DHTPIN, DHTTYPE);
int voPin = 36;
int ledPin = 23;
SharpGP2Y10 dustSensor(voPin, ledPin);

// Function to update the LED status in Firebase (0 or 1)
void updateLEDStatusInFirebase(int led1, int led2, int led3) {
  if (Firebase.RTDB.setInt(&fbdo, "device/AirCon", led1)){
    Serial.println("LED 1 status updated in Firebase");
  } else {
    Serial.println("Failed to update LED 1 status in Firebase");
  }

  if (Firebase.RTDB.setInt(&fbdo, "device/AirPur", led2)){
    Serial.println("LED 2 status updated in Firebase");
  } else {
    Serial.println("Failed to update LED 2 status in Firebase");
  }

  if (Firebase.RTDB.setInt(&fbdo, "device/Light", led3)){
    Serial.println("LED 3 status updated in Firebase");
  } else {
    Serial.println("Failed to update LED 3 status in Firebase");
  }
}

// Function to control LEDs based on Firebase data (0 or 1)
void controlLEDFromFirebase() {
  if (Firebase.RTDB.getInt(&fbdo, "device/AirCon")) {
    if (fbdo.dataType() == "int") {
      int firebaseLEDStatus1 = fbdo.intData();
      digitalWrite(CONTROL_LED_PIN_1, firebaseLEDStatus1 == 1 ? HIGH : LOW);
      ledStatus1 = firebaseLEDStatus1;
      Serial.print("LED 1 status from Firebase: ");
      Serial.println(firebaseLEDStatus1 == 1 ? "ON" : "OFF");
    }
  } else {
    Serial.println("Failed to get LED 1 status from Firebase");
  }

  if (Firebase.RTDB.getInt(&fbdo, "device/AirPur")) {
    if (fbdo.dataType() == "int") {
      int firebaseLEDStatus2 = fbdo.intData();
      digitalWrite(CONTROL_LED_PIN_2, firebaseLEDStatus2 == 1 ? HIGH : LOW);
      ledStatus2 = firebaseLEDStatus2;
      Serial.print("LED 2 status from Firebase: ");
      Serial.println(firebaseLEDStatus2 == 1 ? "ON" : "OFF");
    }
  } else {
    Serial.println("Failed to get LED 2 status from Firebase");
  }

  if (Firebase.RTDB.getInt(&fbdo, "device/Light")) {
    if (fbdo.dataType() == "int") {
      int firebaseLEDStatus3 = fbdo.intData();
      digitalWrite(CONTROL_LED_PIN_3, firebaseLEDStatus3 == 1 ? HIGH : LOW);
      ledStatus3 = firebaseLEDStatus3;
      Serial.print("LED 3 status from Firebase: ");
      Serial.println(firebaseLEDStatus3 == 1 ? "ON" : "OFF");
    }
  } else {
    Serial.println("Failed to get LED 3 status from Firebase");
  }
}



void setup(){
Serial.begin(9600);
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("Connecting to Wi-Fi");
while (WiFi.status() != WL_CONNECTED){
Serial.print(".");
delay(300);
}
Serial.println();
Serial.print("Connected with IP: ");
Serial.println(WiFi.localIP());
Serial.println();

dht.begin();
pinMode(CONTROL_LED_PIN_1, OUTPUT);  // Set control LED pin 1 as output
pinMode(CONTROL_LED_PIN_2, OUTPUT);  // Set control LED pin 2 as output
pinMode(CONTROL_LED_PIN_3, OUTPUT);  // Set control LED pin 3 as output

/* Assign the api key (required) */
config.api_key = API_KEY;

/* Assign the RTDB URL (required) */
config.database_url = DATABASE_URL;

/* Sign up */
if (Firebase.signUp(&config, &auth, "", "")){
Serial.println("ok");
signupOK = true;
}
else{
Serial.printf("%s\n", config.signer.signupError.message.c_str());
}

/* Assign the callback function for the long running token generation task */
config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

Firebase.begin(&config, &auth);
Firebase.reconnectWiFi(true);
}


void loop(){
  float h = dht.readHumidity();  // Read humidity
  float t = dht.readTemperature(); // Read temperature
  float dustDensity = dustSensor.getDustDensity();  // Read dust density
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();

    // Write humidity and temperature to the database
    if (Firebase.RTDB.setFloat(&fbdo, "sensor/humidity", h)){
      Serial.println("Humidity data sent successfully");
    } else {
      Serial.println("Failed to send humidity data");
    }

    if (Firebase.RTDB.setFloat(&fbdo, "sensor/temperature", t)){
      Serial.println("Temperature data sent successfully");
    } else {
      Serial.println("Failed to send temperature data");
    }
    if (Firebase.RTDB.setFloat(&fbdo, "sensor/dust", dustDensity)){
      Serial.println("Dust data sent successfully");
    } else {
      Serial.println("Failed to send dust data");
    }

    // Update LED status in Firebase
    updateLEDStatusInFirebase(ledStatus1, ledStatus2, ledStatus3);
  }

  controlLEDFromFirebase();

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C  Dust Density: "));
  Serial.print(dustDensity);
  Serial.println(F(" mg/m3"));

  delay(1000);
}