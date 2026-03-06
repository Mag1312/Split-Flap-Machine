#include <arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Audio.h>

void playMusic()
{
    if(songCount == 0)
        buildPlaylist("/music");

    currentSong = 0;

    audio.connecttoFS(SD, songs[currentSong].c_str());
    isPlaying = true;
}