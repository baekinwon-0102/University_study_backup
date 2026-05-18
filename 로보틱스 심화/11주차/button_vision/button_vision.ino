#include <SharpIR.h>
#include <Dynamixel2Arduino.h>

////////////// 버튼 & LED
#define RED_LED_PIN              4
#define SW1_PIN                  41
#define SW2_PIN                  40
#define BUTTON_DEBOUNCE_TIME     50

////////////// Dynamixel
#define DXL_SERIAL   Serial1
const int DXL_DIR_PIN = 2;
const float DXL_PROTOCOL_VERSION = 2.0;

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

const uint8_t DXL_ID[4] = {1, 2, 3, 4};

////////////// PSD 센서
SharpIR irFrontLeft (SharpIR::GP2Y0A21YK0F, A0);
SharpIR irFrontRight(SharpIR::GP2Y0A21YK0F, A2);
SharpIR irSideLeft  (SharpIR::GP2Y0A21YK0F, A1);
SharpIR irSideRight (SharpIR::GP2Y0A21YK0F, A3);

////////////// SyncWrite 구조체
DYNAMIXEL::InfoSyncWriteInst_t sw_mobile_infos;
DYNAMIXEL::XELInfoSyncWrite_t xels[4];

typedef struct sw_mobile_data_t {
  int32_t goal_velocity;
} __attribute__((packed)) sw_mobile_data_t;

sw_mobile_data_t sw_mobile_data[4];

////////////// 주행 상수
#define DRIVE_SPEED                 80
#define STRAFE_SPEED                80
#define STOP_DELAY_TIME            800
#define LOOP_DELAY_TIME             80

// 이미지 동작 순서 기준 거리 
// 멈추는 거리 설정하려면 아래 코드 3줄만 수정하셈
#define FIRST_FRONT_RIGHT_STOP_CM   10.0    
#define LEFT_SIDE_STOP_CM            9.0
#define FINAL_FRONT_RIGHT_STOP_CM   25.0

#define SENSOR_MARGIN_CM             1.0
#define CONDITION_COUNT_REQUIRED     3

////////////// 미션 상태
enum MissionState {
  STATE_WAIT_START = 0,
  STATE_FORWARD_TO_FRONT_RIGHT_18,
  STATE_STOP_AFTER_FIRST_FORWARD,
  STATE_STRAFE_LEFT_TO_SIDE_9,
  STATE_STOP_AFTER_LEFT,
  STATE_FORWARD_TO_FRONT_RIGHT_25,
  STATE_MISSION_FINISH
};

MissionState missionState = STATE_WAIT_START;

bool missionStarted = false;
bool lastSw1State = false;
bool lastSw2State = false;

unsigned long lastSw1Time = 0;
unsigned long lastSw2Time = 0;
unsigned long lastWaitPrintTime = 0;

uint8_t conditionCount = 0;

////////////// PSD 거리값
float distFrontLeft = 0;
float distFrontRight = 0;
float distSideLeft = 0;
float distSideRight = 0;

void setup() {
  Serial.begin(115200);

  dxl.begin(57600);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  InitDynamixelWheels();
  InitSyncWrite();

  pinMode(RED_LED_PIN, OUTPUT);

  // 버튼이 GND로 눌리는 구조라면 INPUT_PULLUP이 안정적입니다.
  pinMode(SW1_PIN, INPUT_PULLUP);
  pinMode(SW2_PIN, INPUT_PULLUP);

  digitalWrite(RED_LED_PIN, LOW);

  StopMobileBase();

  Serial.println("System Ready!");
  Serial.println("WAIT: Press LEFT button(SW1) to start.");
}

void loop() {
  CheckStartStopButtons();

  if (!missionStarted) {
    StopMobileBase();
    digitalWrite(RED_LED_PIN, LOW);

    if (millis() - lastWaitPrintTime > 1000) {
      lastWaitPrintTime = millis();
      Serial.println("WAIT: Press LEFT button(SW1) to start.");
    }

    delay(LOOP_DELAY_TIME);
    return;
  }

  digitalWrite(RED_LED_PIN, HIGH);

  ReadAllPsdSensors();
  PrintSensorValues();
  RunMissionStateMachine();

  delay(LOOP_DELAY_TIME);
}

////////////// Dynamixel 초기화
void InitDynamixelWheels() {
  for (int i = 0; i < 4; i++) {
    uint8_t id = DXL_ID[i];

    dxl.torqueOff(id);
    dxl.setOperatingMode(id, OP_VELOCITY);
    dxl.torqueOn(id);
  }
}

void InitSyncWrite() {
  sw_mobile_infos.packet.p_buf = nullptr;
  sw_mobile_infos.packet.is_completed = false;
  sw_mobile_infos.addr = 104;        // Goal Velocity
  sw_mobile_infos.addr_length = 4;
  sw_mobile_infos.p_xels = xels;
  sw_mobile_infos.xel_count = 4;
  sw_mobile_infos.is_info_changed = true;

  for (int i = 0; i < 4; i++) {
    xels[i].id = DXL_ID[i];
    xels[i].p_data = (uint8_t*)&sw_mobile_data[i].goal_velocity;
    sw_mobile_data[i].goal_velocity = 0;
  }
}

////////////// 버튼 처리
void CheckStartStopButtons() {
  bool sw1 = !digitalRead(SW1_PIN);
  bool sw2 = !digitalRead(SW2_PIN);

  if (sw1 != lastSw1State) {
    lastSw1Time = millis();
    lastSw1State = sw1;
  }

  if (sw1 && millis() - lastSw1Time > BUTTON_DEBOUNCE_TIME) {
    if (!missionStarted) {
      StartMission();
    }
  }

  if (sw2 != lastSw2State) {
    lastSw2Time = millis();
    lastSw2State = sw2;
  }

  if (sw2 && millis() - lastSw2Time > BUTTON_DEBOUNCE_TIME) {
    EmergencyStopAndReset();
  }
}

void StartMission() {
  missionStarted = true;
  missionState = STATE_FORWARD_TO_FRONT_RIGHT_18;
  conditionCount = 0;

  digitalWrite(RED_LED_PIN, HIGH);

  Serial.println("START: Mission start.");
  delay(300);
}

void EmergencyStopAndReset() {
  missionStarted = false;
  missionState = STATE_WAIT_START;
  conditionCount = 0;

  StopMobileBase();
  digitalWrite(RED_LED_PIN, LOW);

  Serial.println("STOP: Emergency stop and reset.");
  delay(300);
}

////////////// 미션 상태 머신
void RunMissionStateMachine() {
  switch (missionState) {
    case STATE_FORWARD_TO_FRONT_RIGHT_18:
      Serial.println("STATE 1: Forward until front right PSD <= 18cm");
      DriveForward(DRIVE_SPEED);

      if (IsFrontRightNear(FIRST_FRONT_RIGHT_STOP_CM)) {
        if (++conditionCount >= CONDITION_COUNT_REQUIRED) {
          StopMobileBase();
          conditionCount = 0;
          missionState = STATE_STOP_AFTER_FIRST_FORWARD;
        }
      } else {
        conditionCount = 0;
      }
      break;

    case STATE_STOP_AFTER_FIRST_FORWARD:
      Serial.println("STATE 2: Stop, then strafe left");
      StopMobileBase();
      delay(STOP_DELAY_TIME);
      missionState = STATE_STRAFE_LEFT_TO_SIDE_9;
      break;

    case STATE_STRAFE_LEFT_TO_SIDE_9:
      Serial.println("STATE 3: Strafe left until left PSD <= 9cm");
      DriveLeft(STRAFE_SPEED);

      if (IsSideLeftNear(LEFT_SIDE_STOP_CM)) {
        if (++conditionCount >= CONDITION_COUNT_REQUIRED) {
          StopMobileBase();
          conditionCount = 0;
          missionState = STATE_STOP_AFTER_LEFT;
        }
      } else {
        conditionCount = 0;
      }
      break;

    case STATE_STOP_AFTER_LEFT:
      Serial.println("STATE 4: Stop, then forward again");
      StopMobileBase();
      delay(STOP_DELAY_TIME);
      missionState = STATE_FORWARD_TO_FRONT_RIGHT_25;
      break;

    case STATE_FORWARD_TO_FRONT_RIGHT_25:
      Serial.println("STATE 5: Forward until front right PSD <= 25cm");
      DriveForward(DRIVE_SPEED);

      if (IsFrontRightNear(FINAL_FRONT_RIGHT_STOP_CM)) {
        if (++conditionCount >= CONDITION_COUNT_REQUIRED) {
          StopMobileBase();
          conditionCount = 0;
          missionState = STATE_MISSION_FINISH;
        }
      } else {
        conditionCount = 0;
      }
      break;

    case STATE_MISSION_FINISH:
      Serial.println("STATE 6: Mission finish.");
      StopMobileBase();
      digitalWrite(RED_LED_PIN, LOW);
      missionStarted = false;
      missionState = STATE_WAIT_START;
      break;

    case STATE_WAIT_START:
    default:
      StopMobileBase();
      break;
  }
}

////////////// PSD 센서 읽기
float ReadPsdAverage5(SharpIR* sensor) {
  long sum = 0;

  for (int i = 0; i < 5; i++) {
    sum += sensor->getDistance();
    delay(2);
  }

  return (float)sum / 5.0;
}

void ReadAllPsdSensors() {
  distFrontLeft  = ReadPsdAverage5(&irFrontLeft);
  distFrontRight = ReadPsdAverage5(&irFrontRight);
  distSideLeft   = ReadPsdAverage5(&irSideLeft);
  distSideRight  = ReadPsdAverage5(&irSideRight);
}

void PrintSensorValues() {
  Serial.print("PSD(cm) FL=");
  Serial.print(distFrontLeft, 1);
  Serial.print(" FR=");
  Serial.print(distFrontRight, 1);
  Serial.print(" SL=");
  Serial.print(distSideLeft, 1);
  Serial.print(" SR=");
  Serial.println(distSideRight, 1);
}

////////////// 조건 판단
bool IsFrontRightNear(float targetCm) {
  return distFrontRight <= targetCm + SENSOR_MARGIN_CM;
}

bool IsSideLeftNear(float targetCm) {
  return distSideLeft <= targetCm + SENSOR_MARGIN_CM;
}

////////////// 주행 함수
void DriveForward(int16_t speedValue) {
  speedValue = abs(speedValue);

  SetMobileGoalVelocityForSyncWrite(
    speedValue, speedValue,
    speedValue, speedValue
  );

  SyncWriteMobileVelocity();
}

void DriveBackward(int16_t speedValue) {
  speedValue = abs(speedValue);

  SetMobileGoalVelocityForSyncWrite(
    -speedValue, -speedValue,
    -speedValue, -speedValue
  );

  SyncWriteMobileVelocity();
}

// 매커넘 휠 좌측 평행 이동
void DriveLeft(int16_t speedValue) {
  speedValue = abs(speedValue);

  SetMobileGoalVelocityForSyncWrite(
    -speedValue,  speedValue,
     speedValue, -speedValue
  );

  SyncWriteMobileVelocity();
}

// 매커넘 휠 우측 평행 이동
void DriveRight(int16_t speedValue) {
  speedValue = abs(speedValue);

  SetMobileGoalVelocityForSyncWrite(
     speedValue, -speedValue,
    -speedValue,  speedValue
  );

  SyncWriteMobileVelocity();
}

void TurnLeft(int16_t speedValue) {
  speedValue = abs(speedValue);

  SetMobileGoalVelocityForSyncWrite(
    -speedValue,  speedValue,
    -speedValue,  speedValue
  );

  SyncWriteMobileVelocity();
}

void TurnRight(int16_t speedValue) {
  speedValue = abs(speedValue);

  SetMobileGoalVelocityForSyncWrite(
     speedValue, -speedValue,
     speedValue, -speedValue
  );

  SyncWriteMobileVelocity();
}

void StopMobileBase() {
  SetMobileGoalVelocityForSyncWrite(0, 0, 0, 0);
  SyncWriteMobileVelocity();
}

void SetMobileGoalVelocityForSyncWrite(int32_t v1, int32_t v2, int32_t v3, int32_t v4) {
  sw_mobile_infos.is_info_changed = true;

  sw_mobile_data[0].goal_velocity = v1;
  sw_mobile_data[1].goal_velocity = v2;
  sw_mobile_data[2].goal_velocity = v3;
  sw_mobile_data[3].goal_velocity = v4;
}

void SyncWriteMobileVelocity() {
  // 통신 실패 시 무한루프에 빠지지 않도록 재시도 횟수 제한
  for (int retry = 0; retry < 5; retry++) {
    if (dxl.syncWrite(&sw_mobile_infos)) {
      return;
    }
    delay(2);
  }

  Serial.println("WARN: Dynamixel syncWrite failed.");
}
