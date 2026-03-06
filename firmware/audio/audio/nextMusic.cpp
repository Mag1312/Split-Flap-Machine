#include <arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Audio.h>

void playNext()
{
    currentSong++;

    if(currentSong >= songCount)
        currentSong = 0;

    audio.connecttoFS(SD, songs[currentSong].c_str());
}