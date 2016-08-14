#define EyesLedCount   30
#define BlinkSpeed 80
#define BlinkDelayMin 5000
#define BlinkDelayMax 15000

Adafruit_NeoPixel EyePixels = Adafruit_NeoPixel(EyesLedCount, EyeDataPin, NEO_GRB + NEO_KHZ800);

void init_eyes() {
  EyePixels.begin();
  for(int i=0; i<= EyesLedCount-1; i++) EyePixels.setPixelColor(i , 0);
  EyePixels.show();
  Queue(2000,EyeAction,20);
}

void Eyeyaction(int action) {
  int mydelay;
  Serial.print("EyeAction: ");
  Serial.println(action);
  switch (action) {
  case 0:  // Off
    for(int i=0; i<= EyesLedCount-1; i++) EyePixels.setPixelColor(i , 0); 
    break;
  case 10:  // Single eye start
    QueueRemove(EyeAction);
    mydelay = 0;
    Queue(mydelay,EyeAction,11);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,12);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,13);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,14);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,15);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,16);
    break;
  case 11: // onder half
    EyeSetRow(0,1 ,0x000000);
    EyeSetRow(1,1 ,0x000000);
    EyeSetRow(2,1 ,0x200000);
    break;
  case 12: // onder full
    EyeSetRow(0,1 ,0x000000);
    EyeSetRow(1,1 ,0x000000);
    EyeSetRow(2,1 ,0x800000);
    break;
  case 13: // onder full , middle half
    EyeSetRow(0,1 ,0x000000);
    EyeSetRow(1,1 ,0x200000);
    EyeSetRow(2,1 ,0x800000);
    break;
  case 14: // onder full , middle full
    EyeSetRow(0,1 ,0x000000);
    EyeSetRow(1,1 ,0x800000);
    EyeSetRow(2,1 ,0x800000);
    break;
  case 15: // onder full , middle full, top half
    EyeSetRow(0,1 ,0x200000);
    EyeSetRow(1,1 ,0x800000);
    EyeSetRow(2,1 ,0x800000);
    break;
  case 16: // onder full , middle full, top full
    EyeSetRow(0,1 ,0x800000);
    EyeSetRow(1,1 ,0x800000);
    EyeSetRow(2,1 ,0x800000);
    
    mydelay = BlinkDelayMin + random(BlinkDelayMax - BlinkDelayMin);
    Queue(mydelay,EyeAction,15);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,14);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,13);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,12);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,11);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,0);mydelay += 2 * BlinkSpeed;
    Queue(mydelay,EyeAction,11);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,12);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,13);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,14);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,15);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,16);
    DumpQueue();
    break;
  case 20:  // Double eye start
    QueueRemove(EyeAction);
    mydelay = 0;
    Queue(mydelay,EyeAction,21);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,22);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,23);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,24);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,25);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,26);
    break;
  case 21: // onder half
    EyeSetRow(0,2 ,0x000000);
    EyeSetRow(1,2 ,0x000000);
    EyeSetRow(2,2 ,0x200000);
    break;
  case 22: // onder full
    EyeSetRow(0,2 ,0x000000);
    EyeSetRow(1,2 ,0x000000);
    EyeSetRow(2,2 ,0x800000);
    break;
  case 23: // onder full , middle half
    EyeSetRow(0,2 ,0x000000);
    EyeSetRow(1,2 ,0x200000);
    EyeSetRow(2,2 ,0x800000);
    break;
  case 24: // onder full , middle full
    EyeSetRow(0,2 ,0x000000);
    EyeSetRow(1,2 ,0x800000);
    EyeSetRow(2,2 ,0x800000);
    break;
  case 25: // onder full , middle full, top half
    EyeSetRow(0,2 ,0x200000);
    EyeSetRow(1,2 ,0x800000);
    EyeSetRow(2,2 ,0x800000);
    break;
  case 26: // onder full , middle full, top full
    EyeSetRow(0,2 ,0x800000);
    EyeSetRow(1,2 ,0x800000);
    EyeSetRow(2,2 ,0x800000);
    
    mydelay = BlinkDelayMin + random(BlinkDelayMax - BlinkDelayMin);
    Queue(mydelay,EyeAction,25);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,24);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,23);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,22);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,21);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,0);mydelay += 2* BlinkSpeed;
    Queue(mydelay,EyeAction,21);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,22);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,23);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,24);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,25);mydelay += BlinkSpeed;
    Queue(mydelay,EyeAction,26);
    break;
  }
  EyePixels.show();
}

void EyeSetRow(int row,int type ,unsigned long value) {
  for(int x=0; x<= 9; x++) {
    switch (type) {
      case 1:
        if (x > 2 && x < 7) EyePixels.setPixelColor((row*10)+x , value); else EyePixels.setPixelColor((row*10)+x , 0);
        break;
      case 2:
        if (x < 3 || x > 6) EyePixels.setPixelColor((row*10)+x , value); else EyePixels.setPixelColor((row*10)+x , 0);
        break;
    }
  }

}


