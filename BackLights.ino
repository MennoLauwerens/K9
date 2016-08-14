#define BackLedCount   19
#define Brightness 128

#include <Adafruit_NeoPixel.h>
unsigned long BackTimer = 0;
Adafruit_NeoPixel BackPixels = Adafruit_NeoPixel(BackLedCount, BackLedPin, NEO_GRB + NEO_KHZ800);

int LightMap[] = {0,10,11,12,15,14,13,16,17,18};
int BinCounter = 0;

void init_back() {
  BackPixels.begin();
  digitalWrite(KeyPin, HIGH);
  for(int i=0; i < BackLedCount; i++) {
    BackPixels.setPixelColor(i , 0x000000);
  }
  BackPixels.show();
  Queue(500,BackAction,1);
}

void Backaction(int action, int actiondata) {
  //Serial.print("BackAction: ");
  //Serial.println(action);
  switch (action) {
    case 0: // off
      QueueRemove(BackAction);
      for(int i=0; i < BackLedCount; i++) {
        BackPixels.setPixelColor(i , 0x000000);
      }
      BackPixels.show();
      break;
    case 1: // Random
      for (int i=10;i < 19; i++) {
        BackPixels.setPixelColor(i,random(2) * Brightness, random(2) * Brightness, random(2) * Brightness);
      }
      BackPixels.show();
      Queue(250,BackAction,1);
      break;
    case 2:
      for (int i=10;i < 19; i++)
      {  
          BackPixels.setPixelColor(i,(actiondata & 1) * Brightness, ((actiondata & 2) >> 1) * Brightness, ((actiondata & 4) >> 2) * Brightness);
      }
      QueueRemove(BackAction);
      BackPixels.show();
      break;  
    case 10: // SetDisplay On
      for (int i=0;i < 10; i++) {
          if (actiondata == i)
          {
              BackPixels.setPixelColor(i,Brightness,0,0);
              BackPixels.show();
              break;
          } 
      }
      BackPixels.show();
      break;
    case 11: // SetDisplay Off
      for (int i=0;i < 10; i++) {
          if (actiondata == i)
          {
              BackPixels.setPixelColor(i,Brightness,0,0);
              BackPixels.show();
              break;
          } 
      }
      break;
    case 12: // SetDisplay Toggle
      for (int i=0;i < 10; i++) {
          if (actiondata == i)
          {  
              if (BackPixels.getPixelColor(i) == 0) {
                 BackPixels.setPixelColor(i,Brightness,0,0);
              } else {
                 BackPixels.setPixelColor(i,0,0,0);
              }
              BackPixels.show();
              break;
          } 
      }
      break;
     
  }
}

