//#define NeckSpeed 80
#define NeckDelayMin 10000
#define NeckDelayMax 50000

// Neck
Servo ServoNeck; 
int NeckTarget = 90;
int NeckPos = 90;
int NeckStep = 10;
int NeckStepDelay = 100;


void init_neck() {
  ServoNeck.attach(NeckPin);  
  ServoNeck.write(90);
  delay(500);
  ServoNeck.write(110);
  delay(500);
  ServoNeck.write(70);
  delay(500);
  ServoNeck.write(90);
  delay(1000);
  ServoNeck.detach();
  Queue(5000,NeckAction,2);
}

void Neckaction(int action) {
  int mydelay;
  Serial.print("NeckAction: ");
  Serial.println(action);
  switch (action) {
    case 0: // detach
      ServoNeck.detach();
      break;
    case 1: // attach
      ServoNeck.attach(NeckPin);
      break;
    case 2: // Start Random sequence
      if (NeckTarget != 90) {
        NeckTarget = 90;
      } else {
        NeckTarget = random(180);
      }
      mydelay = NeckDelayMin + random(NeckDelayMax - NeckDelayMin);
      Queue(mydelay-500,NeckAction,1);
      Queue(mydelay,NeckAction,3);
      break;
    case 3: // Update position
      if (NeckPos < NeckTarget - NeckStep) {
        NeckPos += NeckStep;
        ServoNeck.write(NeckPos);
        Queue(NeckStepDelay,NeckAction,3);
      } 
      else if (NeckPos > NeckTarget + NeckStep) {
        NeckPos -= NeckStep;
        ServoNeck.write(NeckPos);
        Queue(NeckStepDelay,NeckAction,3);
      }
      else { // on position
        Queue(1,NeckAction,0);
        Queue(50,NeckAction,2); // Schedule next move
      }
      break;
  }
}


