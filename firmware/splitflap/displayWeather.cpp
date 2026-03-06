#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <variables.h>

  String URL = "http://api.openweathermap.org/data/2.5/weather?";
  String ApiKey = "eb327b9e60623b4a05eb7485dbb00595";
  String lat = "16.306624";
  String lon = "80.436595";

void displayWeather()
{
  if(WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;

    http.begin(URL + "lat=" + lat + "&lon=" + lon + "&apiid=" + Apikey);
    int httpCode = http.GET();

    if(httpCode > 0)
    {
      String JSON_Data = http.getString();
      Serial.println(JSON_Data);
      DynamicJsonDocument doc(2048);
      deserializeJson(doc, JSON_Data);
      JsonObject obj = doc.as<JsonObject>();

      const char* main = obj["weather"][0]["main"].as<const.char*>();

      strcpy(weather_array, main.c_str());

      for(i=0; i <= 6; i++)
      {
        for(j=11; j <= 36; j++)
        {
          if(weather_array[i] == ascii[j])
          {
            display[i] = j;
            toMove[i] = display[i] * steps_per_flap;
            break;
          }
        }
      }
      


      for(int i=0;i<7;i++)
      {
        posIndicator[i] = 0;
      }

      while(posIndicator[0]!= 1 || posIndicator[1]!= 1 || posIndicator[2]!= 1 || posIndicator[3]!= 1 || posIndicator[4]!= 1 || posIndicator[5]!= 1 || posIndicator[6]!= 1)
      {
        for(i=0; i<=6; i++)
        {
          if(posIndicator[i]!=1)
          {
            s[i].step(1);
            pos[i]++;
            if(pos[i] >= steps_per_rev)
            {
             pos[i] = pos[i] - steps_per_rev;
            }
            if(pos[i] >= toMove[i])
            {
              posIndicator[i] = 1;
            }
          }
        }
      }
    }
  }
}