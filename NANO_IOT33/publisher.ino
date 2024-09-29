#include <WiFiNINA.h>
#include <Firebase_Arduino_WiFiNINA.h>
#include "Secrets.h"

// WiFi credentials
#define WIFI_SSID SECRET_SSID
#define WIFI_PASSWORD SECRET_PASS

// Firebase credentials
#define FIREBASE_HOST HOST
#define FIREBASE_AUTH SECRET_KEY // Use your database secret from Firebase

// LED pins
const int redPin = 2;
const int greenPin = 3;
const int bluePin = 4;

// Firebase reference
FirebaseData firebaseData;

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Connect to WiFi
  Serial.print("Connecting to WiFi");
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());

  // Initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH,WIFI_SSID,WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);
  Serial.println("Connected to Firebase");
}

void loop() {
  if (Firebase.getString(firebaseData, "/ledControl/color")) {
    String color = firebaseData.stringData();
    Serial.print("Received color: ");
    Serial.println(color);
    toggleLED(color);
  } else {
    Serial.println("Failed to get color from Firebase");
    Serial.println(firebaseData.errorReason());
  }
  delay(100);
}

void toggleLED(String color) {
  // Turn off all LEDs initially
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);

  // Turn on the LED according to the color received
  if (color == "red") {
    digitalWrite(redPin, HIGH);
  } else if (color == "green") {
    digitalWrite(greenPin, HIGH);
  } else if (color == "blue") {
    digitalWrite(bluePin, HIGH);
  }
}
