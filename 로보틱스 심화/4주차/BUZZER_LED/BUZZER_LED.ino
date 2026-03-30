#define LEFT_SWITCH_PIN 41
#define RIGHT_SWITCH_PIN 40
#define BUZZER_PIN 5

#include <Adafruit_NeoPixel.h>
#define RGB_LED_PIN 3
#define NUM_PIXELS 1
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS,RGB_LED_PIN,NEO_GRBW+NEO_KHZ800);

#define DO_3 131
#define RE_3 147
#define MI_3 165
#define FA_3 175
#define SOL_3 196
#define LA_3 220
#define TI_3 247
#define DO_4 262
#define RE_4 294
#define MI_4 330
#define FA_4 349

#define n4 1300
#define n2 n4/2
#define n1 n4/4
#define nd2 n4/8
#define SHORT_DELAY 10

int melody[] = {SOL_3,DO_4,DO_4,RE_4,DO_4,TI_3,LA_3,LA_3,
                LA_3,RE_4,RE_4,MI_4,RE_4,DO_4,TI_3,SOL_3,
                SOL_3,MI_4,MI_4,FA_4,MI_4,RE_4,DO_4,LA_3,
                SOL_3,SOL_3,LA_3,RE_4,TI_3,DO_4};
int note[] = {n1,n1,nd2,nd2,nd2,nd2,n1,n1,
              n1,n1,nd2,nd2,nd2,nd2,n1,n1,
              n1,n1,nd2,nd2,nd2,nd2,n1,n1,
              nd2,nd2,n1,n1,n1,n1};

int prevNote=0;

void setup() {
  if( sizeof(melody) != sizeof(note)){
    while(1){};
    pixels.begin();
    pinMode(LEFT_SWITCH_PIN,INPUT);
    pinMode(RIGHT_SWITCH_PIN,INPUT);
  }

}

void loop() {
  if(!digitalRead(LEFT_SWITCH_PIN)){
    for(int i = 0;i<sizeof(melody)/sizeof(int);i++){
      if(prevNote == melody[i]){
        noTone(BUZZER_PIN);
        pixels.setBrightness(0);
        pixels.show();
        delay(SHORT_DELAY);
      }

      uint32_t soundStartTime = millis();
      bool isWaiting = false;
      bool isStopButtonPressed = false;

      while(millis()-soundStartTime < note[i]){
        if(!digitalRead(RIGHT_SWITCH_PIN)){
          isStopButtonPressed = true;
          break;
        }
        if(!isWaiting){
          tone(BUZZER_PIN,melody[i]);
          pixels.setPixelColor(0,pixels.Color(random(1,256),random(1,256),random(1,256)));
          pixels.setBrightness(100);
          pixels.show();
          prevNote = melody[i];

          isWaiting = true;
        } else{
          delay(1);
        }
      }
    }
    noTone(BUZZER_PIN);
    pixels.setBrightness(0);
    pixels.show();
  }
}
