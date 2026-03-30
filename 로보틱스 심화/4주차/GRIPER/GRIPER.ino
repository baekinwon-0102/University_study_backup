#include <Pixy2SPI_SS.h>
Pixy2SPI_SS pixy;

#define GRIP_ANGLE_CLOSE 650
#define GRIP_ANGLE_OPEN 100

void setup() {
  Serial.begin(1152000);

  pixy.init();
  pixy.setServos(1,GRIP_ANGLE_OPEN);
}

void loop() {
  pixy.setServos(1,GRIP_ANGLE_CLOSE);
  delay(800);

  pixy.setServos(1,GRIP_ANGLE_OPEN);
  delay(800);

  delay(5000);
}
