#include <WiFi.h>
#include <time.h>
#include <WiFiClientSecure.h>
#include <variables.h>

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
}
