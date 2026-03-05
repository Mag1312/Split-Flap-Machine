#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <variables.h>

WiFiClientSecure client;

void wifiConnect()
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print("\nStatus : NOT CONNECTED");
  }
  Serial.println("\nStatus : CONNECTED");
}


