const int PIN_NUM[] = {A0, A2, A1, A3}; // 4개의 PSD 센서 핀 번호

void setup() {
 Serial.begin( 115200 ); 
}

void loop() {
  static int analogReadValue[5][4] = {0,}; // 배열 안을 0으로 채움
  static float analogReadValueAverage[4] = {0.0,};
  static float distanceValue[4] = {0.0,};

  for(int n=0; n<5; n++){
    for(int i=0; i<4; i++){
      analogReadValue[n][i] = analogRead(PIN_NUM[i]); // 값을 총 5번 읽으며 값을 읽을 때마다 핀 넘버의 아날로그 값을 가져옴
    }
  }

  for (int i =0; i<4; i++){
    analogReadValueAverage[i] = (analogReadValue[0][i] + 
                                analogReadValue[1][i] + 
                                analogReadValue[2][i] + 
                                analogReadValue[3][i] + 
                                analogReadValue[4][i]/5);   // 읽어온 값의 평균을 구함 

    distanceValue[i] = psd2Distance(i,analogReadValueAverage[i]); // 실제 거리 구하는 함수
  }

  Serial.print("[Analog Value(f1,fr,sl,sr)] : (");
  for(int i = 0;i<4;i++){
    Serial.print(analogReadValueAverage[i]);
    if(i<3){
      Serial.print(", ");
    }
    else{
      Serial.println(") ");
    }
  }

  Serial.print("[Distance(fl,fr,sl,sr)]: (");
  for(int i = 0;i<4;i++){
    Serial.print(distanceValue[i],1);
    if(i<3){
      Serial.print(" cm, ");
    }
    else{
      Serial.println("cm) ");
    }
  }

  delay(500);

}

float psd2Distance(int x, float d){
  float distance;

  if(x==0){
    distance = 13768 * pow(d,-1.183); //전방 좌측 거리 추세 함수
  }
  else if(x==1){
    distance = 15911 * pow(d,-1.2); //전방 우측 거리 추세 함수
  }
  else if(x==2){
    distance = 37406 * pow(d,-1.333); //측방 좌측 거리 추세 함수
  }
  else if(x==3){
    distance = 44932 * pow(d,-1.361); //측방 우측 거리 추세 함수
  }
  else{
    distance=0.0;
  }
  return distance;
}