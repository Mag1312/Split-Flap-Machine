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
  for(int i = 0; i < 7; i++)
  {
    pinMode(stepPins[i], OUTPUT);
    pinMode(dirPins[i], OUTPUT);
  }

  pinMode(enablePin, OUTPUT);
  pinMode(sleepPin, OUTPUT);

  digitalWrite(enablePin, HIGH); // disabled
  digitalWrite(sleepPin, HIGH); // awake

  setupCalibration();
  wifiConnect();
  getTime();
  displayDayInfo();

  digitalWrite(sleepPin, LOW);
  delay(20000);
  digitalWrite(sleepPin, HIGH);

  displayWeekDay();

  digitalWrite(sleepPin, LOW);
  delay(20000);
  digitalWrite(sleepPin, HIGH);

  displayTime();

  digitalWrite(sleepPin, LOW); // sleep (no current passes)

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
    digitalWrite(sleepPin, HIGH);
    displayDayInfo();
    digitalWrite(sleepPin, LOW);
    delay(10000);
    digitalWrite(sleepPin, HIGH);
    displayWeekDay();
    digitalWrite(sleepPin, LOW);
    delay(5000);
    digitalWrite(sleepPin, HIGH);
    displayWeather()
    digitalWrite(sleepPin, LOW);
    dayUpdate++;
  }
  else if(minute4 != 0 && dayUpdate == 1)
  {
    dayUpdate = 0;
  }
  
  server.handleClient();
}
