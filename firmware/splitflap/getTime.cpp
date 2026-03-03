#include <Arduino.h>
#include <WifiClientSecure.h>
#include <time.h>
extern WifiClientSecure client;

// Watch "https://www.youtube.com/watch?v=9OcewS8sa68" for complete understanding

unsigned long UnixTime;
int seconds, minutes,hours;

unsigned long getUnixTime()
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
      }
    }
  }
  return 0;
}

void UnixConversion()
{
  time_t now = UnixTime;
  struct tm *timeInfo = localtime(&now);
  char sec[5];
  char min[5];
  char hou[5];
  strftime(sec, sizeof(sec), "%S", timeInfo);
  strftime(min, sizeof(min), "%M", timeInfo);
  strftime(hou, sizeof(hou), "%H", timeInfo);
  seconds = atoi(sec);
  minutes = atoi(min);
  hours = atoi(hou);
}

void getTime()
{
  UnixTime = getUnixTime();
  delay(3000);
  if(UnixTime > 0)
  {
    Serial.print("Unix time :");
    Serial.println(UnixTime);
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

}