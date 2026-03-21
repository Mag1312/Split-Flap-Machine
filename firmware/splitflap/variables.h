
#ifndef VARIABLES_H   // Start of include guard
#define VARIABLES_H
#include <stepper.h>

int steps_per_rev = 4096;
int stepPins[7] = {4,6,8,10,12,14,16};
int dirPins[7] = {5,7,9,11,13,15,17};

int enablePin = 2;
int sleepPin = 3;

const char* ssid = "SSID";
const char* password = "PASSWORD";

int hallSensor[7] = {35, 36, 37, 38, 39, 40, 41};
int splitCalNum[7] = {0, 0, 0, 0, 0, 0, 0}; 
int pos[7], toMove[7], safetyCount[7] = {0, 0, 0, 0, 0, 0, 0};
int seconds, minutes,hours;
int steps_per_flap = steps_per_rev/37;
char hour1, hour2, minute4, minute5;
int seconds, minutes, hours, days, months, wdays, years;
char monthStr, wdayStr;
char setOfMonths[] = {"JAN", "FEB", "MAR", "MAY", "JUN", "JUL", "AUG, "SEP", "OCT", "NOV", "DEC};
char setOfWDays[] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
char wdays_array[wdays.lenth() + 1];
char months_array[months.length() + 1];
int i,j;
int display[7];
char weather_array[main.length() + 1];
char wordToBeDisplayed = "";
char word_Array[7];
char link;

char ascii[36] = {
48,49,50,51,52,53,54,55,56,57,58,
65,66,67,68,69,70,71,72,73,74,75,76,77,
78,79,80,81,82,83,84,85,86,87,88,89,90
};

unsigned long unixTime = 0;
unsigned long millisAtGetTime = 0;
unsigned long millisAtDisplayTime;
unsigned long millisNow;
unsigned long unixTimeNow;

#endif 
