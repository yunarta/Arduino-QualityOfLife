//
// Created by yunarta on 3/15/25.
//

#include "QualityOfLife.h"
#include <WiFi.h>
#include <LittleFS.h>

ArduinoAppConfig Config;

void ArduinoAppConfig::begin() {
    File configFile = LittleFS.open("/config.json", "r");
    if (!configFile) {
#ifdef LOG_DEBUG
        Serial.println("[DEBUG] Failed to open /config.json");
#endif
        return;
    }
#ifdef LOG_DEBUG
    Serial.println("[DEBUG] /config.json opened successfully");
#endif

    DeserializationError error = deserializeJson(doc, configFile);
    configFile.close();

    if (error) {
#ifdef LOG_DEBUG
        Serial.println("[DEBUG] Failed to parse JSON configuration");
#endif
        return;
    }
#ifdef LOG_DEBUG
    Serial.println("[DEBUG] JSON configuration parsed successfully");
#endif
}

void connectToInternet() {
    WiFi.setTxPower(WIFI_POWER_19dBm);
#ifdef LOG_INFO
    Serial.println("[INFO] WiFi TX power set to 19 dBm");
#endif


    const char *ssid = Config.doc["network"]["ssid"];
    const char *password = Config.doc["network"]["password"];
#ifdef LOG_INFO
    Serial.print("[INFO] Connecting to WiFi SSID: ");
    Serial.println(ssid);
#endif

    WiFi.setTxPower(WIFI_POWER_19dBm);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    // Wait for connection
    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED) {
        if (millis() - startAttemptTime > 60000) {
#ifdef LOG_INFO
            Serial.println("[INFO] Failed to connect to WiFi, entering deep sleep");
#endif
            esp_deep_sleep_start();
        }
        delay(10);
    }
#ifdef LOG_INFO
    Serial.println("[INFO] WiFi connected successfully");
#endif

    configTime(8 * 3600, 0, "pool.ntp.org", "time.nist.gov");
#ifdef LOG_INFO
    Serial.println("[INFO] Time configuration updated using NTP servers");
#endif

    startAttemptTime = millis();
    while (time(nullptr) < 100000) {
        if (millis() - startAttemptTime > 2 * 60000) {
#ifdef LOG_INFO
            Serial.println("[INFO] Failed to synchronize time, entering deep sleep");
#endif
            esp_deep_sleep_start();
        }
        delay(10);
    }
#ifdef LOG_INFO
    Serial.println("[INFO] Time synchronized successfully");
#endif
}
