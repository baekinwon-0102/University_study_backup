#define RED_LED_PIN 4

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(RED_LED_PIN, HIGH);
  delay(1000);
  digitalWrite(RED_LED_PIN,LOW);
  delay(1000);

  digitalWrite(RED_LED_PIN, HIGH);
  delay(500);
  digitalWrite(RED_LED_PIN,LOW);
  delay(1000);

  digitalWrite(RED_LED_PIN, HIGH);
  delay(100);
  digitalWrite(RED_LED_PIN,LOW);
  delay(1000);
}
