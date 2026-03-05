#include <variables.h>
#include <time.h>
#include <arduino.h>

void displayDayInfo()
{
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

    // This code will display in the format "DD MMM "   ex - "25 JAN "



  display[0] = days/10;
  display[1] = days%10;
  display[2] = 10;
  display[6] = 10;

  for(i=3; i <= 5; i++)
  {
    for(j=11; j <= 36; j++)
    {
      if(month_array[i-3] == ascii[j])
      {
        display[i] = j;
        break;
      }
    }
  }
  
  for(i=0; i<= 6; i++)
  {
    toMove[i] = display[i] * steps_per_flap;
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