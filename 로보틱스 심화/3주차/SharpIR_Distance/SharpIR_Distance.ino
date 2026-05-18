#include <Arduino.h>
#include <SharpIR.h>

// 전방 좌측, 전방 우측, 측방 좌측, 측방 우측
const int PIN_NUM[4] = {A0,A2,A1,A3};

// SharpIR 객체 4개 (각 센서가 모두 같은 모델이라고 가정)
// 만약 모델이 서로 다르면 센서별로 다르게 지정
SharpIR irFL(SharpIR::GP2Y0A21YK0F,A0);
SharpIR irFR(SharpIR::GP2Y0A21YK0F,A2);
SharpIR irSL(SharpIR::GP2Y0A21YK0F,A1);
SharpIR irSR(SharpIR::GP2Y0A21YK0F,A3);

// 배열로 다루기 쉽게 포인터 배열 구성
SharpIR* irSensor[4] = {&irFL,&irFR,&irSL,&irSR};

// 첫번째 소스의 추세함수
float psd2Distance(int x, float d)
{
  float distance = 0.0;

// d가 0이면 powd(d, 음수)에서 문제가 나므로 예외처리
  if (d<=0.0) return 0.0;

  if(x == 0){
    distance = 13768 * pow(d,-1.183); //전방 좌측
  }
  else if(x == 1){
    distance = 15911 * pow(d,-1.2); //전방 우측
  }
  else if(x == 2){
    distance = 37406 * pow(d,-1.383); //측방 좌측
  }
  else if(x == 3){
    distance = 44932 * pow(d,-1.361); //측방 우측
  }
  else{
    distance = 0.0;
  }
  return distance;
}

// 아날로그 값 5회 평균
float readAnalogAverage5(int pin){
  long sum = 0;
  for(int n = 0; n<5; n++){
    sum+=analogRead(pin);
    delay(2);
  }
  return (float)sum/5.0;
}

// SharpIR 거리 5회 평균 (getDistance()는 보통 int cm 반환)
float readSharpIRDistanceAverage5(SharpIR* sensor){
  long sum=0;
  for(int n = 0; n<5; n++){
    sum+=sensor -> getDistance();
    delay(2);
  }
  return (float)sum/5.0;
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  float analogAvg[4] = {0, 0, 0, 0};
  float distTrend[4] = {0, 0, 0, 0};
  float distSharp[4] = {0, 0, 0, 0};

  // 1) 아날로그 평균(5회) 읽기 + 추세함수 거리 계산
  for (int i = 0;i<4;i++){
    analogAvg[i] = readAnalogAverage5(PIN_NUM[i]);
    distTrend[i]= psd2Distance(i,analogAvg[i]);
  }


  // 2) SharpIR 거리(5회) 평균
  for (int i = 0;i<4;i++){
    distSharp[i] = readSharpIRDistanceAverage5(irSensor[i]);
  }

  // 출력1) 아날로그 평균
  Serial.print("(Analog AVG(fl, fr, sl, sr)): (");
  for (int i = 0;i<4;i++){
    Serial.print(analogAvg[i],1);
    if(i<3) Serial.print(", ");
    else Serial.println(")");
  }

  // 출력2) 추세함수 거리
  Serial.print("[Dist Trend(cm)] (");
  for (int i = 0;i<4;i++){
    Serial.print(distTrend[i],1);
    if(i<3) Serial.print(" cm, ");
    else Serial.println(" cm)");
  }

  // 출력3) SharpIR 거리
  Serial.print("[Dist SharpIR (cm)] (");
  for (int i = 0;i<4;i++){
    Serial.print(distSharp[i],1);
    if(i<3) Serial.print(" cm, ");
    else Serial.println(" cm)");
  }

  Serial.println("--------------------------------------------------------------------");

  delay(500);
}
