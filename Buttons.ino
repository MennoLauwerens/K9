#define KeyTimeout 10000
#define KeyScantime 100

byte LastKey = 999;
int KeyAD = 0;
int KeyValue = 0;
int KeyRepeat = 0;
int InputState = 0; // 0=idle // 1=set 1 / 2=set 2 .. enz tm 8

void init_keys() {
  digitalWrite(KeyPin, HIGH);
  Queue(KeyScantime,KeyAction,1);
}

void Keyaction(int action) { 
  //Serial.print("KeyAction: ");
  //Serial.println(action);
  switch (action) {
    case 1: // read
      KeyAD = analogRead(KeyPin);
      //Serial.println(KeyAD);
      if ( KeyAD < 100 ) KeyValue = 7;
      if ( KeyAD >= 100 && KeyAD < 220 ) KeyValue = 8;
      if ( KeyAD >= 220 && KeyAD < 340 ) KeyValue = 9;
      if ( KeyAD >= 340 && KeyAD < 450 ) KeyValue = 6;
      if ( KeyAD >= 450 && KeyAD < 550 ) KeyValue = 5;
      if ( KeyAD >= 550 && KeyAD < 660 ) KeyValue = 4;
      if ( KeyAD >= 660 && KeyAD < 760 ) KeyValue = 1;
      if ( KeyAD >= 760 && KeyAD < 860 ) KeyValue = 2;
      if ( KeyAD >= 860 && KeyAD < 960 ) KeyValue = 3;
      if ( KeyAD >= 960 )
      {
        KeyValue = 0;
        KeyRepeat = 0;
        if ( KeyValue != LastKey ) Queue(KeyTimeout,KeyAction,2); // Start timeout
        LastKey = KeyValue;
      } else {
        QueueRemove(KeyAction); // Remove timeout timer
        if ( KeyValue == LastKey ){ //key allready pressed
          Serial.print("Key: ");
          Serial.println(KeyValue);
          Serial.print(" - ");
          Serial.println(KeyRepeat);
          if (KeyRepeat++ == 2) ProcessKey(KeyValue);     //debounce & no repeat
        } else { // new key pressed
          LastKey = KeyValue;
          KeyRepeat = 0;
        }
      }
      
      break;
    case 2: // timeout
      //QueueRemove(KeyAction); // Avoid double scan
      InputState = 0;
      // Start IDLE lights
      Queue(250,BackAction,1);
      break;
  }
  Queue(KeyScantime,KeyAction,1);
}

void ProcessKey(int key) {
  Serial.print("ProcessKey: ");
  Serial.println(key);
  if (InputState == 0) { 
    InputState = key; 
    Queue(1,BackAction,2,InputState);
  }
  else {
     switch (InputState) {
       case 1: ProcessKey_1(key);
               break;
       case 2: ProcessKey_2(key);
               break;
       case 3: ProcessKey_3(key);
               break;
       case 4: ProcessKey_4(key);
               break;
       case 5: ProcessKey_5(key);
               break;
       case 6: ProcessKey_6(key);
               break;
       case 7: ProcessKey_7(key);
               break;
       case 8: ProcessKey_8(key);
               break;
       case 9: ProcessKey_9(key);
               break;
     }
  }
}

void ProcessKey_1(int key){ // Manual control
  Serial.print("ProcessKey_1 :");
  Serial.println(key);
}

void ProcessKey_2(int key){ // Sounds 1
  Serial.print("ProcessKey_2 :");
  Serial.println(key);
  Queue(10,SoundAction,1,key);
}

void ProcessKey_3(int key){ // Sounds 2
  Serial.print("ProcessKey_3 :");
  Serial.println(key);
  Queue(10,SoundAction,1,key + 10);
}

void ProcessKey_4(int key){ // Sounds 3 
  Serial.print("ProcessKey_4 :");
  Serial.println(key);
  Queue(10,SoundAction,1,key + 20);
}

void ProcessKey_5(int key){
  Serial.print("ProcessKey_5 :");
  Serial.println(key);
}

void ProcessKey_6(int key){
  Serial.print("ProcessKey_6 :");
  Serial.println(key);
}

void ProcessKey_7(int key){
  Serial.print("ProcessKey_7 :");
  Serial.println(key);
}

void ProcessKey_8(int key){
  Serial.print("ProcessKey_8 :");
  Serial.println(key);
}

void ProcessKey_9(int key){ // Shutdown + Startup codeslot
  Serial.print("ProcessKey_9 :");
  Serial.println(key);
}


