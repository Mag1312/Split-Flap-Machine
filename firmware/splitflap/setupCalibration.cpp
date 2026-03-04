#include <stepper.h>
#include <Arduino.h>

int steps_per_rev = 4096;
Stepper s[7] = { {steps_per_rev, 4, 6, 5, 7},
{steps_per_rev, 8, 10, 9, 11},
{steps_per_rev, 12, 14, 13, 15},
{steps_per_rev, 19, 23, 20, 24},
{steps_per_rev, 25, 27, 26, 28},
{steps_per_rev, 29, 31, 30, 32},
{steps_per_rev, 33, 39, 38,40}};
int hallSensor[7] = {41, 42, 47, 48, 16, 17, 18};
int splitCalNum[7] = {0, 0, 0, 0, 0, 0, 0}; 
int pos[7], safetyCount[7] = {0, 0, 0, 0, 0, 0, 0};

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

    if(safetyCount[pin] >= 5000)
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

    if(safetyCount[pin] >= 5000)
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
