// MP3 Player
#include "DFPlayer_Mini_Mp3.h"


SoftwareSerial DfSerial(MP3_rx,MP3_tx);
unsigned long MP3Timer = 0;
int MP3Interval = 60000;

int MP3Volume = 23;
int MP3State = 0;
int MaxADC = 5;
int SoundADCValue = 0;
int SoundValue = 0;

void init_sounds() {
  DfSerial.begin(9600);
  mp3_set_serial(DfSerial);
  mp3_set_volume(MP3Volume);
  digitalWrite(SoundBusyPin,HIGH); 
  Queue(1,SoundAction,1,14);
}

void Soundaction(int action, int actiondata) {
  int mydelay;
  Serial.print("SoundAction: ");
  Serial.print(action);
  Serial.print(" - Actiondata: ");
  Serial.println(actiondata);
  switch (action) {
    case 0: // silence
      break;
    case 1: // PlaySound
      QueueRemove(SoundAction);
      mp3_play(actiondata);
      Queue(1000,SoundAction,2);
      break;
    case 2: // Wait for end
      // Check BusyPin
      int SoundBusy = analogRead(SoundBusyPin);
      Serial.print(" - SoundBusyPin: ");
      Serial.println(SoundBusy);
      if (SoundBusy < 800) { 
        Queue(20,SoundAction,2);
      } else {
        //Queue(60000,SoundAction,1,14);
      }
      // Update Eyes
      break;     
  }
}


