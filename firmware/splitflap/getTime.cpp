#include <Arduino.h>
#include <WifiClientSecure.h>
#include <time.h>
#include <variables.h>
extern WifiClientSecure client;

// Watch "https://www.youtube.com/watch?v=9OcewS8sa68" for complete understanding


unsigned long getUnixTime()
{

  if(unixTime > 0)
  {
    timestamp = unixTime + (millis() - millisAtGetTime);
    return timestamp;
  }
  
  else
  {
    client.setInsecure(); // skips certificate validation

    if(client.connect("aisenseapi.com", 443))
    {
      client.println("GET /services/v1/timestamp HTTP/1.1");
      client.println("Host: aisenseapi.com");
      client.println("Connection: close");
      client.println();

      while(client.connected() || client.available())
      {
        String line = client.readStringUntil('\n');
        if(line.indexOf("timestamp") >= 0)
        {
          int start = line.indexOf(":") + 1;
          int end = line.indexOf("}", start);
          unsigned long timestamp = line.substring(start, end).toInt();
          client.stop();
          return timestamp;
          millisAtGetTime = millis();
        }
      }
    }
    return 0;
  }

void UnixConversion()
{
  time_t now = unixTime;
  struct tm *timeInfo = localtime(&now);
  minutes = timeInfo->tm_min;
  hours = timeInfo->tm_hour;
  seconds = timeInfo->tm_sec;
  days = timeInfo->tm_mday;
  months = timeInfo->tm_mon;
  wdays = timeInfo->tm_wday;
  years = 1900 + (timeInfo->tm_year);

  // this converts months to character array

   std::strcpy(months_array, setOfMonths[months].c_str());
   std::strcpy(wdays_array, setOfWDays[wdays].c_str());
  
}

void getTime()
{
  unixTime = getUnixTime();
  delay(3000);
  if(unixTime > 0)
  {
    Serial.print("Unix time :");
    Serial.println(unixTime);
  }
  else
  {
    Serial.print("Failed to get Unix Time");
  }

  UnixConversion();
  Serial.print("Hours : ");
  Serial.println(hours);
  Serial.print("Minutes : ");
  Serial.println(minutes);
  Serial.print("Seconds :");
  Serial.print(seconds);
  Serial.print("Date :");
  Serial.print(days);
  Serial.print(setOfMonths[months]);

}