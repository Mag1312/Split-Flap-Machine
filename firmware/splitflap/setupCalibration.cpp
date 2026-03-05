#include <stepper.h>
#include <Arduino.h>
#include <variables.h>


void fullCalibration(int pin)
{

  for(pin; pin <= 6; pin++)
  {
   pinMode(hallSensor[pin], INPUT_PULLUP);
   s[pin].setSpeed(5);
  }

  // code for calibration.
  
  if(digitalRead(hallSensor[pin]) == LOW )
  {
    splitCalNum[pin] = 1;
    s[pin].step(1);
    safetyCount[pin]++;

    if(digitalRead(hallSensor[pin]) == HIGH)
    {
      splitCalNum[pin] = 2;
      s[pin].setSpeed(10);
      pos[pin] = 0; //sets relative position to 0
    }

    if(safetyCount[pin] >= 2500)
    {
      Serial.println("Homing Failed");
      Serial.println(pin);
      while(1);
    }
  }

  else
  {
    s[pin].step(1);
    safetyCount[pin]++;
    s[pin].step(1);

    if(digitalRead(hallSensor[pin]) == LOW)
    {
      splitCalNum[pin] = 1;
    }

    if(safetyCount[pin] >= 2500)
    {
      Serial.println("Homing Failed");
      Serial.println(pin);
      while(1);
    }
  }
  
}

void setupCalibration()
{
 int pin_num;
 for(pin_num = 0; ; pin_num++)
 {
  if(pin_num > 6)
  {
    pin_num = pin_num - 6;
  }

  if(splitCalNum[pin_num] != 2)
  {
   fullCalibration(pin_num);
  }

  if(splitCalNum[0] == 2 && splitCalNum[1] == 2 && splitCalNum[2] == 2 && splitCalNum[3] == 2 && splitCalNum[4] == 2 && splitCalNum[5] == 2 && splitCalNum[6] == 2 )
  {
    return;
  }
 }
}
