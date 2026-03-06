#include <WiFi.h>
#include <time.h>
#include <WiFiClientSecure.h>
#include <variables.h>
#include <WebServer.h>

void displayWord()
{
  strcpy(word_Array, wordToBeDisplayed.c_str);
  for(i = 0; i < 7; i++)
  {
    for(j = 0; j < 37; j++)
    {
      if(word_array[i] == ascii[j])
      {
        display[i] = j;
        toMove[i] = display[i] * steps_per_flap;
        break;
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