// Water meter sensor using ESP8266 and a MAG3110 Magnetometer
// Dan Kouba, 2017

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <SparkFun_MAG3110.h>

// WiFi credentials from file so they can be hidden
#include "wifi_credentials.h"

MAG3110 mag = MAG3110(); //Instantiate MAG3110
long int last_time = 0;

void setup() {
    Serial.begin(115200);

    // WiFi Setup
    Serial.println(F("ESP8266 Booting"));
    WiFi.mode(WIFI_STA);
    WiFi.begin(HIDDEN_SSID, HIDDEN_PASS);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println(F("WiFi Connection Failed! Rebooting..."));
        delay(5000);
        ESP.restart();
    }

    // Setup OTA callback functions
    ArduinoOTA.onStart([]() {
        Serial.println(F("OTA Start"));
    });

    ArduinoOTA.onEnd([]() {
        Serial.println(F("\nOTA End"));
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("OTA Progress: %u%%\r", (progress / (total / 100)));
    });

    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("OTA Error[%u]: ", error);

        switch(error) {
            case OTA_AUTH_ERROR:
                Serial.println(F("OTA: Auth Failed"));
                break;
            case OTA_BEGIN_ERROR:
                Serial.println(F("OTA: Begin Failed"));
                break;
            case OTA_CONNECT_ERROR:
                Serial.println(F("OTA: Connect Failed"));
                break;
            case OTA_RECEIVE_ERROR:
                Serial.println(F("OTA: Receive Failed"));
                break;
            case OTA_END_ERROR:
                Serial.println(F("OTA: End Failed"));
                break;
        }
    });

    ArduinoOTA.begin();
    Serial.println(F("WiFi Connected!"));
    Serial.print(F("IP address: "));
    Serial.println(WiFi.localIP());

    // Initializes the mag sensor
    Serial.print(F("Initializing MAG3110..."));
    while(!mag.initialize()){
        Serial.print(".");
    }
    Serial.println(F("success"));

    mag.setDR_OS(MAG3110_DR_OS_80_16);  // Set data rate to 80Hz, OSR 16
    mag.rawData(true);
    mag.start();                        // Puts the sensor in active mode
}

void loop() {

    // OTA update function
    ArduinoOTA.handle();

    float x, y, z;
    //Only read data when it's ready
    if(mag.dataReady()) {

        //Read the data
        long int cur_time = micros() - last_time;
        mag.readMicroTeslas(&x, &y, &z);

        //Serial.print(micros() - last_time);
        //Serial.print(",");
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.print(",");
        Serial.println(z);

        last_time = micros();
    }
}
