#include <Pixy2SPI_SS.h>
Pixy2SPI_SS pixy;

#define GRIP_ANGLE_CLOSE 650
#define GRIP_ANGLE_OPEN 100

int pos = 0;

void setup() {
  Serial.begin(1152000);

  pixy.init();
  pixy.setServos(1,GRIP_ANGLE_OPEN);
}

void loop() {
  for (pos = GRIP_ANGLE_OPEN; pos<= GRIP_ANGLE_CLOSE; pos+=2){
    pixy.setServos(0,pos);
    delay(25);
  }

  for (pos = GRIP_ANGLE_CLOSE; pos>= GRIP_ANGLE_OPEN; pos-=2){
    pixy.setServos(0,pos);
    delay(25);
  }

}
