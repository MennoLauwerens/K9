#include <Adafruit_NeoPixel.h>

#define EarDelayMin 5000
#define EarDelayMax 6000
#define EarStepDelay 50

Servo ServoEarLeft;  
int LeftEarTarget = 90;
int LeftEarPos = 90;
int LeftEarStep = 10;
boolean LeftEarFinished = true;

Servo ServoEarRight;
int RightEarTarget = 90;
int RightEarPos = 90;
int RightEarStep = 10;
boolean RightEarFinished = true;

void init_ears() {
  ServoEarLeft.attach(LeftEarPin);  
  ServoEarRight.attach(RightEarPin);
  ServoEarLeft.write(90);
  ServoEarRight.write(90);
  Queue(500,EarAction,0);
  Queue(3000,EarAction,2);
}

void Earaction(int action) {
  int mydelay;
  Serial.print("EarAction: ");
  Serial.println(action);
  switch (action) {
    case 0: // detach
      ServoEarLeft.detach();
      ServoEarRight.detach();
      break;
    case 1: // attach
      ServoEarLeft.attach(LeftEarPin);
      ServoEarRight.attach(RightEarPin);
      break;
    case 2: // start ears
      if (LeftEarTarget != 90) {
        LeftEarTarget = 90;
      } else {
        LeftEarTarget = random(180);
      }
      LeftEarStep = random(10);
      if (RightEarTarget != 90) {
        RightEarTarget = 90;
      } else {
        RightEarTarget = random(180);
      }
      RightEarStep = 5 + random(3) * 5;
      LeftEarStep = 5 + random(3) * 5;
      mydelay = EarDelayMin + random(EarDelayMax - EarDelayMin);
      Queue(mydelay-500,EarAction,1);
      Queue(mydelay,EarAction,3);
      break;
    case 3: // Update position
 //   Serial.println("Ears:");
 //   Serial.print("Left: ");
 //   Serial.print(LeftEarPos);
 //   Serial.print(" - ");
//    Serial.print(LeftEarTarget);
//    Serial.print(" - ");
//    Serial.print(LeftEarStep);
//    Serial.print(" - ");   
      // Left
      if (LeftEarPos < LeftEarTarget - LeftEarStep) {
        LeftEarPos += LeftEarStep;
        ServoEarLeft.write(LeftEarPos);
        LeftEarFinished = false;
      } 
      else if (LeftEarPos > LeftEarTarget + LeftEarStep) {
        LeftEarPos -= LeftEarStep;
        ServoEarLeft.write(LeftEarPos);
        LeftEarFinished = false;
      }
      else { // on position
        LeftEarFinished = true;
      }
      // Right
      if (RightEarPos < RightEarTarget - RightEarStep) {
        RightEarPos += RightEarStep;
        ServoEarRight.write(RightEarPos);
        RightEarFinished = false;
      } 
      else if (RightEarPos > RightEarTarget + RightEarStep) {
        RightEarPos -= RightEarStep;
        ServoEarRight.write(RightEarPos);
        RightEarFinished = false;
      }
      else { // on position
        RightEarFinished = true;
      }

      if ( LeftEarFinished && RightEarFinished ) { 
        Serial.println("On target");
        Queue(EarStepDelay,EarAction,0);
        Queue(EarStepDelay * 2,EarAction,2); // Schedule next move
      } else {
        Queue(EarStepDelay,EarAction,3);
      }
      break;
      
  }
}

