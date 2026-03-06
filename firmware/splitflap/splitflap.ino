#include <WiFi.h>
#include <time.h>
#include <WiFiClientSecure.h>
#include <variables.h>
#include <WebServer.h>

WebServer server(80);

// Function Prototypes
void calibration();
void wifiConnect();
void getTime();
unsigned long getUnixTime();
void UnixConversion();
int dayUpdate = 0;

void setup() 
{
  setupCalibration();
  wifiConnect();
  getTime();
  displayDayInfo();
  delay(10000);
  displayWeekDay();
  displayTime();

  server.on("/", handleRoot);
  server.on("/time/now", handleTimeNow);
  server.on("/info/now", handleInfoNow);
  server.on("/displayWord", handleDisplayWord);
  server.on("/play/now", handlePlayNow);
  server.on("/stop/now", handleStopNow);
  server.on("/next/now", handleNextNow);
  server.on("/previous/now", handlePreviousNow);


  Serial.println("IP Address: ")
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("HTTP server started");

  Serial2.begin(115200, SERIAL_8N1, 16, 17);
}

void loop()
{
  timeCalculation();
  if(minute4 == 0 && dayUpdate == 0)
  {
    displayDayInfo();
    delay(10000);
    displayWeekDay();
    delay(5000);
    displayWeather()
    dayUpdate++;
  }
  else if(minute4 != 0 && dayUpdate == 1)
  {
    dayUpdate = 0;
  }
  
  server.handleClient();
}
