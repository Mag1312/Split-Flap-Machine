#include <variables.h>
#include <time.h>
#include <arduino.h>


void timeCalculation()
{
  millisNow = millis();
  long millisDifference = millisNow - millisAtGetTime;
  if(millisDifference >= 60000)
  {
    unixTimeNow = unixTime + (millisDifference/1000);

    time_t now = unixTimeNow;
    struct tm *timeInfo = localtime(&now);
    minutes = timeInfo->tm_min;
    hours = timeInfo->tm_hour;
    if((minutes%10) != minute5)
    {
      minute5 = minutes % 10;
      minute4 = minutes / 10;
      hour1 = hours % 10;
      hour2 = hours / 10;

      displayTime();
      millisAtGetTime = millis();
    }
  }

}