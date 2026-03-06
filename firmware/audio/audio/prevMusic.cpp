#include <arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Audio.h>

void playNext()
{
    currentSong--;

    if(currentSong < 0)
        currentSong = 100;

    audio.connecttoFS(SD, songs[currentSong].c_str());
}