#define RED_LED_PIN 4

#define SW1_PIN 41
#define SW2_PIN 40

void setup() {
  Serial.begin(115200);

  pinMode(RED_LED_PIN, OUTPUT);

  pinMode(SW1_PIN, INPUT);
  pinMode(SW2_PIN, INPUT);
}

void loop() {
  // 스위치가 눌리면 1ㅡ 아니면 0이 출력되도록 digitalRead에 not 연산
  Serial.print("SW1 : ");
  Serial.print(!digitalRead(SW1_PIN));
  Serial.print(", SW2 : ");
  Serial.println(!digitalRead(SW2_PIN));

  digitalWrite(RED_LED_PIN, digitalRead(SW1_PIN) != digitalRead(SW2_PIN));

  delay(50);

}
