#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Audio.h>

Audio audio;

#define SD_CS 5
#define I2S_BCLK 26
#define I2S_LRC 25
#define I2S_DOUT 22

#define RXD2 16
#define TXD2 17

#define MAX_SONGS 100

#define VOL_PIN 34

String songs[MAX_SONGS];
int songCount = 0;
int currentSong = 0;
bool isPlaying = false;

void buildPlaylist(const char* path);

void audio_eof_mp3(const char *info)
{
    playNext();
}


void buildPlaylist(const char* path)
  {  
    songCount = 0;

    File root = SD.open(path);
    File file = root.openNextFile();

    while(file && songCount < MAX_SONGS)
    {
        String name = file.name();

        if(!file.isDirectory() && name.endsWith(".mp3"))
        {
            songs[songCount] = String(path) + "/" + name;
            songCount++;
        }

        file = root.openNextFile();
    }

    root.close();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // UART communication
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

  // Initialize SD card
  if(!SD.begin(SD_CS))
  {
    Serial.println("SD Card Mount Failed");
    while(true);
  }

  Serial.println("SD Card Ready");

  // Configure I2S output
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);

  // Volume range 0 - 21
  audio.setVolume(15);

  const char* path = "/music";

  
}

void loop() {
  // put your main code here, to run repeatedly:

  audio.loop();
  int potValue = analogRead(VOL_PIN);
  int volume = map(potValue, 0, 4095, 0, 21);

  audio.setVolume(volume);

  if(Serial2.available())
  {
    String command = Serial2.readStringUntil('\n');
    if(command == "PLAY")
  {
    playMusic();
  }
  if(command == "STOP")
  {
    audio.stopSong();
    isPlaying = false;
  }
  if(command == "PREV")
  {
    prevMusic();
  }
  if(command == "NEXT")
  {
    nextMusic();
  }
  }

  

}
