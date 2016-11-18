/*

 Demo to use MAX30100 heart beat & SpO2 sensor and publish to Firebase Realtime Database.
 I use ESPectro Core development board, but basically you can use any ESP8266-based board.

 Created by Andri Yadi, Makestro.com on 11/6/16.

*/

#include <Arduino.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "ESP8266WebServer.h"
#include <FirebaseArduino.h>

#define REPORTING_PERIOD_MS     1000

// Set Firebase Host and Auth key. Key is buried under "Project Settings" of a project.
// Here's how to get the key: https://raw.githubusercontent.com/andriyadi/Firebase_ESP8266_Demo/master/HowToGetTheKey.gif
#define FIREBASE_HOST "[FIREBASE_PROJECT_NAME].firebaseio.com"
#define FIREBASE_AUTH "[FIREBASE_PROJECT_KEY]"

// Set your WiFi credentials
#define WIFI_SSID       "[I_WONT_TELL_YOU]"
#define WIFI_PASSWORD   "[I_WONT_TELL_YOU_AS_WELL]"

// PulseOximeter is the higher level interface to the sensor. Let's create the object here
PulseOximeter pox;

uint32_t tsLastReport = 0;
volatile boolean heartBeatDetected = false;

// Callback method will be fired when a pulse is detected
void onBeatDetected()
{
    heartBeatDetected = true;
    Serial.println("Beat!");
}

void setup()
{
    Serial.begin(115200);

    // Connect to wifi.
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());

    // Begin connection to Firebase
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

    // Create the Firebase Realtime Database keys (if not yet) and set default values
    Firebase.set("sensor/HeartBeat", 0);
    Firebase.set("sensor/SpO2", 0);

    // Show the last error
    if (Firebase.failed()) {
        Serial.print("setting /message failed:");
        Serial.println(Firebase.error());
    }

    // Initialize the PulseOximeter instance and register a beat-detected callback
    pox.begin();
    pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop()
{
    // Make sure to call update as soon as possible
    pox.update();

    // Asynchronously dump heart rate and oxidation levels to the serial, and publish to Firebase
    // For both, a value of 0 means "invalid"
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {

        float bpm = pox.getHeartRate();
        float spO2 = pox.getSpO2();

        Serial.print("Heart rate:");
        Serial.print(bpm);
        Serial.print("bpm / SpO2:");
        Serial.print(spO2);
        Serial.println("%");

        tsLastReport = millis();

        // If the values are valid and heart beat detected, publish to Firebase
        if (heartBeatDetected && bpm != 0) {
            Firebase.setFloat("sensor/HeartBeat", bpm);
            Firebase.setInt("sensor/SpO2", spO2);
        }
    }
}