void setup() {
  Serial.begin( 115200 ); //연결된 COM 포트로 통신 시작(9600은 통신속도임,115200 도 자주 사용)
}

void loop() {
  unsigned long currentTime = millis(); //아두이노 부팅 후 지금까지 경과한 시간 변수에 저장

  Serial.print("Hello");
  Serial.print(", ");
  Serial.println("world");

  Serial.println("Hello, arduino");
  Serial.println();

  Serial.print("Current Time :");
  Serial.print(currentTime / 1000);
  Serial.println(" sec");
  //Serial.println(" ms");

  delay(5000);
}
