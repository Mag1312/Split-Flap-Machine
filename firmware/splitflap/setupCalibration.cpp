#include <stepper.h>
#include <Arduino.h>
#include <variables.h>


void fullCalibration(int pin)
{

  for(pin; pin <= 6; pin++)
  {
   pinMode(hallSensor[pin], INPUT_PULLUP);

    // code for calibration.
  
    if(digitalRead(hallSensor[pin]) == LOW && splitCalNum[pin] != 2)
    {
      splitCalNum[pin] = 1;
      digitalWrite(stepPins[pin], HIGH); //moves by 1 step
      delay(10000);
      digitalWrite(stepPins[pin], LOW)
      safetyCount[pin]++;

      if(digitalRead(hallSensor[pin]) == HIGH)
      {
        splitCalNum[pin] = 2;
        pos[pin] = 0; //sets relative position to 0
      }

      if(safetyCount[pin] >= 5000)
      {
        Serial.println("Homing Failed");
        Serial.println(pin);
        while(1);
      }
    }

    else
    {
      digitalWrite(stepPins[pin], HIGH); //moves by 1 step
      delay(10000);
      digitalWrite(stepPins[pin], LOW)
      safetyCount[pin]++;

      if(digitalRead(hallSensor[pin]) == LOW)
      {
        splitCalNum[pin] = 1;
      }

      if(safetyCount[pin] >= 5000)
      {
        Serial.println("Homing Failed");
        Serial.println(pin);
        while(1);
      }
    }
  }
  
}

void setupCalibration()
{
 digitalWrite(enablePin, LOW);
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
 digitalWrite(enablePin, HIGH);
}
