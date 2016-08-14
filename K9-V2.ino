#include <SoftwareSerial.h>

#include <IRremote.h>
#include <Servo.h>

#define MaxQueueLength 25

#define EyeAction 1
#define NeckAction 2
#define EarAction 3
#define KeyAction 4
#define SoundAction 5
#define BackAction 6

// K9 - PINS
#define MP3_rx 2
#define MP3_tx 3
#define EyeDataPin 6
#define AudioPowerPin 7
#define BackLedPin 8
#define LeftEarPin 9
#define RightEarPin 10
#define NeckPin 11
#define IR_RECV_PIN 12
#define KeyPin A0
#define SoundBusyPin A1
#define SoundADCPin A2

// Back

// Back Connector
// IR Receiver
IRrecv irrecv(IR_RECV_PIN);
decode_results results;

// 2 - Switches + = Blauw/wit
// 1 - Switches - = Oranje/wit
// 3 - Switches C = Bruin
// 4 -            = 
// 6 - Lights +   = Groen
// 5 - Lights -   = Oranje
// 7 - Lightd Data= Bruin/wit
// 8 -            = 
//


unsigned long QueueTime[MaxQueueLength];
int QueueModule[MaxQueueLength];
int QueueAction[MaxQueueLength];
int QueueData[MaxQueueLength];
int QueueLength = 0;
int QueueChanged = false;


void setup() {
  Serial.begin(9600);
  randomSeed(5);
  Serial.println("Start Initialisation");
  Serial.println("init_back...");
  init_back();
  Backaction(10, 1);
  Serial.println("init_eyes...");
  init_eyes();
  Backaction(10, 2);
  Serial.println("init_neck...");
  init_neck();
  Backaction(10, 3);
  Serial.println("init_ears...");
  init_ears();
  Backaction(10, 4);
  Serial.println("init_keys...");
  init_keys();
  Backaction(10, 5);
  Serial.println("init_sounds...");
  init_sounds();
  Backaction(10, 6);

  Serial.println("Initialisation finished");
}

void loop() {
  //Serial.print(".");
  if (QueueChanged) {
    //Serial.print("QueueLength: ");
    //Serial.println(QueueLength);
    //DumpQueue();
    QueueChanged=false;
  }
  for (int i=0;i < QueueLength;i++) {

    if (QueueTime[i] <= millis()) {
      int QModule = QueueModule[i];
      int QAction = QueueAction[i];
      int QData = QueueData[i];
      for (int j=i;j < QueueLength;j++) {
        QueueTime[j] = QueueTime[j+1];
        QueueModule[j] = QueueModule[j+1];
        QueueAction[j] = QueueAction[j+1];        
        QueueData[j] = QueueData[j+1];
      }
      QueueLength--;
      QueueChanged=true; 
      Backaction(12,QModule);     
      switch (QModule) {
        case 0:
          // do nothing for debugging
          break;
        case EyeAction:
          Eyeyaction(QAction);
          break;
        case NeckAction:
          Neckaction(QAction);
          break;   
        case EarAction:
          Earaction(QAction);
          break;
        case KeyAction:
          Keyaction(QAction);
          break;
        case SoundAction:  
          Soundaction(QAction,QData);
          break;
        case BackAction:
          Backaction(QAction,QData);
          break;
      }
      break;
    }
  }
  //delay(10);
}

// Add event to comandqueue
void Queue(int delayms, int module, int action,int data = 0) {
  QueueTime[QueueLength] = millis() + delayms;
  QueueModule[QueueLength] = module;
  QueueAction[QueueLength] = action;
  QueueData[QueueLength] = data;
  QueueLength++;
  QueueChanged=true;
}

// Removel all scheduled events for one type
void QueueRemove(int module){
  //Serial.print("Remove:");
  //Serial.println(module);
  //DumpQueue();
  int i = 0;
  for (int j=0;j < QueueLength;j++){
    if (QueueModule[j] != module) {
      QueueTime[i] = QueueTime[j];
      QueueModule[i] = QueueModule[j];
      QueueAction[i] = QueueAction[j];
      QueueData[i] = QueueData[j];
      i++;
    }   
  }
  QueueLength = i;
  QueueChanged=true;
  //DumpQueue();
}

void DumpQueue(){    
  Serial.println("DumpQueue:");
  for (int i=0;i < QueueLength;i++){
    Serial.print(i);
    Serial.print(" - ");
    Serial.print(QueueTime[i]);
    Serial.print(" - ");
    Serial.print(QueueModule[i]);
    Serial.print(" - ");
    Serial.print(QueueAction[i]);
    Serial.print(" - ");
    Serial.print(QueueData[i]);
    Serial.println(".");
  }

  
}


