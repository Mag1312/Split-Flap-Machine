# Split-Flap-Machine

This split flap machine is a hobby project by Mag, It is a device which displays time, date, weekday, weather, any word which is less than 7 letters and can even play your favourite songs from a MicroSD Card.

## Introduction

The Split Flap Machine's main attraction, The split flap consists of 37 flaps, 10 numbers (0-9), 26 alphabets (A-Z) and a blank flap. It is made possible mainly with the use of 28byj48 stepper motor, A4988 driver, Hall sensor and an ESP 32. The split flap drum has a small neodimium magnet which gets detected by the hall sensor and sends an update, the place where the magnet's field is not felt by the sensor, is the 0 position. Whenever something is to be displayed, the drum/spool is rotated with respect to this position to display.

The music system works from the webserver, where there are controls to play music. These controls can be used to play music from the MicroSD card.

This all works on a 10000MaH battery.

## Detailed Explanation

The split flap machine consists of 7 split flap units, consisting of 37 flaps, a spool and a stand. A single split flap unit uses a 28byj48 stepper motor, A4988 stepper driver, ky035 hall sensor and a ball bearing.
As mentioned earlier, after the startup a calibration function runs which runs in the following process.

Rotate spool until magnet detected --> Rotate spool until magnet is not detected --> set position = 0

After which to display a character, it first checks the ascii value of the character to be displayed in a seperate array, the position of the array of the ascii value is taken. the position of array times the number of steps per flap is multiplied to get the required position to revolve to display the character. Afterwhich the motor rotates the spool until the position is achieved. There is a killswitch if the spool rotates more than 1 revolution the program fails and freezes.

![image of a unit of split flap display](images/Full_SFM.png)

You can better understand this in my firmware, go check it out. This is the central operation around which all functions work.

The song system uses a MicroSD card, PCM5102A DAC Module, PAM8406 Amplifier and 2x 8ohm 3Watt speakers. This has been chosen for the highest quality and a mid-high battery life.

The system uses a 10000MaH battery pack with a buck converter to convert voltage.

#

Read Timeline.md for more understanding.

If you have any regards or have found an issue please contact +91 9346651359 (or) email to magazine2512@gmail.com.
