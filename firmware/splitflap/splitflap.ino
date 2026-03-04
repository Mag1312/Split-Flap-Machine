#include <WiFi.h>
#include <time.h>
#include <WiFiClientSecure.h>

// Function Prototypes
void calibration();
void wifiConnect();
void getTime();
unsigned long getUnixTime();
void UnixConversion();

void setup() 
{
  setupCalibration();
  wifiConnect();
  getTime();
}
