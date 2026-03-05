#include <arduino.h>
#include <stepper.h>
#include <variables.h>
#include <AccelStepper.h>

displayTime()
{

  hour1 = '0'+(hours/10);   //Converts numbers to their ascii value
  hour2 = '0'+(hours%10);
  minute4 = '0'+(minutes/10);
  minute5 = '0'+(minutes%10);

// absolute position of letters and numbers with respect to 0 position.

   /*
    *  A    |   B   |   C   |   D   |   E   |   F   |   G   |   H   |   I   |   J   |   K   |   L   |   M   |
    * 107.03 116.76  126.49  136.22  145.95  155.68  165.41  175.14  184.87  194.60  204.33  214.06  223.79    
    *  N    |   O   |   P   |   Q   |   R   |   S   |   T   |   U   |   V   |   W   |   X   |   Y   |   Z   |
    * 233.52 243.25  252.98  262.71  272.44  282.17  291.90  301.63  311.36  321.09  330.82  340.55  350.28
    *  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  Blank  |
    *  0    9.73 19.46 29.19 38.92 48.65 58.38 68.11 77.84 87.57  97.3

    Even though these values are in decimals for a unit to display a number it should be in the range between the value shown in the table and the value of next letter/number
    */

  for(i=0; i<=35; i++)
  {
    if(hour1 == ascii[i])
    {
      toMove[1] = i * steps_per_flap;
    }
    if(hour2 == ascii[i])
    {
      toMove[2] = i * steps_per_flap;
    }
    if(minute4 == ascii[i])
    {
      toMove[4] = i * steps_per_flap;
    }
    if(minute5 == ascii[i])
    {
      toMove[5] = i * steps_per_flap;
    }
  }
  toMove[0] = 10 * steps_per_flap;
  toMove[3] = toMove[0];
  toMove[6] = toMove[0];

  while(posIndicator[0]!= 1 || posIndicator[1]!= 1 || posIndicator[2]!= 1 || posIndicator[3]!= 1 || posIndicator[4]!= 1 || posIndicator[5]!= 1 || posIndicator[6]!= 1)
  {
    for(i=0; i<=6; i++)
    {
      if(posIndicator[i]!=1)
      {
        s[i].step(1);
        pos[i]++;
        if(pos[i] > (toMove[i]-2) && pos[i] < (toMove[i]+2))
        {
          posIndicator[i] = 1;
        }
        else
        {
          if(pos[i] >= steps_per_rev)
          {
            pos[i] = pos[i] - steps_per_rev;
          }
        }

      }
    }
  }

  millisAtDisplayTime = millis();
  
}