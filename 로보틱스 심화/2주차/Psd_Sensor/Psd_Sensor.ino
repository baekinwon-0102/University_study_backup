#define FIN_FRONT_LEFT_PSD A0  //왼쪽 A0번째 핀에 꽃혀있는 PSD센서
#define FIN_FRONT_RIGHT_PSD A2 //오른쪽 A2번쨰 핀에 꽃혀있는 PSD 센서

void setup() {
  Serial.begin( 115200 );

}

void loop() {
  int frontleftPSDValue = analogRead(FIN_FRONT_LEFT_PSD); //센서가 받아오는 값
  int frontrightPSDValue = analogRead(FIN_FRONT_RIGHT_PSD); // 센서가 받아오는 값
  // analogRead -> 아날로그 값 받아옴, digitalRead -> 디지털 값 가져옴

  Serial.print("front left : ");
  Serial.print(frontleftPSDValue);
  Serial.print(", front right : ");
  Serial.print(frontrightPSDValue);
  Serial.println();

  delay(500);
}
