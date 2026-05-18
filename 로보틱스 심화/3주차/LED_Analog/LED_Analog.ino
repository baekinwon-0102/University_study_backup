#define RED_LED_PIN 4

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
}

void loop() {
  for(int i = 0;i<= 255; i++){
    analogWrite(RED_LED_PIN,i);
    delay(10);
  }
  delay(500);

  for(int i = 255;i>= 0; i--){
    analogWrite(RED_LED_PIN,i);
    delay(10);
  }
  delay(500);

  for(int i = 0;i<= 255; i++){
    analogWrite(RED_LED_PIN,i);
    delay(3);
  }
  delay(500);

  for(int i = 255;i>= 0; i--){
    analogWrite(RED_LED_PIN,i);
    delay(3);
  }
  delay(500);
}
