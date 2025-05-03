#ifndef GFXFF
#define GFXFF 1
#endif

#include <TFT_eSPI.h>
#include <WiFi.h>
#include "doto-regular18pt7b.h"
#include "include/config.h"  // Zawiera WiFi SSID i hasła

TFT_eSPI tft = TFT_eSPI();

void connectToWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID_1, WIFI_PASSWORD_1);
  Serial.print("Connecting to network: ");
  Serial.println(WIFI_SSID_1);

  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nNetwork 1 connected");
    return;
  }

  WiFi.begin(WIFI_SSID_2, WIFI_PASSWORD_2);
  Serial.print("\nConnecting to network: ");
  Serial.println(WIFI_SSID_2);
  startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nNetwork 2 connected");
  } else {
    Serial.println("\nUnable to connect to WiFi");
  }
}

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(&doto_regular18pt7b);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.drawCentreString("VDGS Display", 160, 40, 1);
  tft.drawCentreString("by PLVACC",    160, 75, 1);

  connectToWiFi();

  if (WiFi.status() != WL_CONNECTED) {
    tft.drawCentreString("No WiFi", 160, 120, 1);
  }
}

void loop() {
  // tu można dodać inne funkcje prezentacji
}
