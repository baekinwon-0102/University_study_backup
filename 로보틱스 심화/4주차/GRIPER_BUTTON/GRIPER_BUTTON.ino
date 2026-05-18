#include <Pixy2SPI_SS.h>
Pixy2SPI_SS pixy;

#define GRIP_ANGLE_CLOSE 650
#define GRIP_ANGLE_OPEN 100

#define RED_LED_PIN 4
#define SW1_PIN 41
#define SW2_PIN 40

int pos = GRIP_ANGLE_OPEN;
int step = 2;

bool isRunning=false;
bool direction = true;

unsigned long lastMoveTime = 0;
const int moveinterval = 5;

void setup() {
  Serial.begin(115200);
  pixy.init();
  pixy.setServos(0,GRIP_ANGLE_OPEN);

  pinMode(RED_LED_PIN,OUTPUT);
  pinMode(SW1_PIN,INPUT);
  pinMode(SW2_PIN,INPUT);
}

void loop() {
  bool sw1 = !digitalRead(SW1_PIN);
  bool sw2 = !digitalRead(SW2_PIN);

  Serial.print("SW1: ");
  Serial.print(sw1);
  Serial.print("SW2: ");
  Serial.print(sw2);

  if (sw1){
    isRunning = true;
  }
  if(sw2){
    isRunning=false;
  }

  digitalWrite(RED_LED_PIN,isRunning);

  if(isRunning && millis()-lastMoveTime > moveinterval){
    lastMoveTime = millis();
    if(direction){
      pos+=step;
      if(pos>=GRIP_ANGLE_CLOSE){
        pos=GRIP_ANGLE_CLOSE;
        direction = false;
      }
    }
    else{
        pos-=step;
        if(pos<=GRIP_ANGLE_OPEN){
        pos=GRIP_ANGLE_OPEN;
        direction = true;
      }
      }
      pixy.setServos(0,pos);
  }
}
