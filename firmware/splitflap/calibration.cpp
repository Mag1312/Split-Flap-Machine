#include <stepper.h>
#include <Arduino.h>

int steps_per_rev = 4096;
Stepper s1(steps_per_rev, 16, 18, 17, 19);
int h1 = 4, pos;

void calibration()
{

 Serial.begin(115200);
 pinMode(h1,INPUT_PULLUP);
 s1.setSpeed(10);


  // code for calibration.
  int safetyCount = 0;

  if(digitalRead(h1) == LOW )
  {
    s1.setSpeed(5); // slower speed for precision
    while(digitalRead(h1) == LOW && safetyCount < 5000)
    {
      // rotates motor and checks for hall sensor output
      s1.step(1);
      safetyCount++;
    }
    if(safetyCount >= 5000)
    {
      Serial.println("Homing Failed");
      while(1);
    }
    safetyCount = 0;
    s1.setSpeed(10);
    pos = 0; //sets relative position to 0

  }
  else
  {
    // This first rotates the motor until hall sensor is activated and then
    // again rotates it until it doesn't detect and sets the position.
    while(digitalRead(h1) == HIGH && safetyCount < 5000)
    {
      s1.step(1);
      safetyCount++;
    }
    if(safetyCount >= 5000)
    {
      Serial.println("Homing Failed");
      while(1);
    }
    safetyCount = 0;
    s1.setSpeed(5);
    while(digitalRead(h1) == LOW && safetyCount < 5000)
    {
      s1.step(1);
      safetyCount++;
    }
    if(safetyCount >= 5000)
    {
      Serial.println("Homing Failed");
      while(1);
    }
    s1.setSpeed(10);
    pos = 0;
  }
}

void setupCalibration()
{
 
}
