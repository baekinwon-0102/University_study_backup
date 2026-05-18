#include <Dynamixel2Arduino.h>

#define DXL_SERIAL Serial1
const int DXL_DIR_PIN = 2; // DIR PIN
const float DXL_PROTOCOL_VERSION = 2.0;

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

using namespace ControlTableItem;

#define ARM_DXL_ID_1 0x05
#define ARM_DXL_ID_2 0x06
#define ARM_DXL_ID_3 0x07
#define ARM_DXL_ID_4 0x08

#define NORMAL_MODE 0x00
#define REVERSE_MODE 0x01

#define ARM_DXL_1_POSITION_MIN 0
#define ARM_DXL_1_POSITION_MAX 4095
#define ARM_DXL_2_POSITION_MIN 1024
#define ARM_DXL_2_POSITION_MAX 3474
#define ARM_DXL_3_POSITION_MIN 211
#define ARM_DXL_3_POSITION_MAX 2640
#define ARM_DXL_4_POSITION_MIN 722
#define ARM_DXL_4_POSITION_MAX 3161

#define ARM_DXL_1_OFFSET 0
#define ARM_DXL_2_OFFSET 238
#define ARM_DXL_3_OFFSET 799
#define ARM_DXL_4_OFFSET 0

const uint8_t ARM_DXL_ID_CNT = 4;
const uint8_t ARM_DXL_IDS[ARM_DXL_ID_CNT] = {ARM_DXL_ID_1,ARM_DXL_ID_2,ARM_DXL_ID_3,ARM_DXL_ID_4};

void setup() {
  Serial.begin(115200);
  dxl.begin(57600);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  for(int i = 0;i<sizeof(ARM_DXL_IDS)/sizeof(uint8_t);i++){
    dxl.writeControlTableItem(TORQUE_ENABLE,ARM_DXL_IDS[i],0);
    dxl.writeControlTableItem(DRIVE_MODE,ARM_DXL_IDS[i],REVERSE_MODE);
    dxl.writeControlTableItem(OPERATING_MODE,ARM_DXL_IDS[i],3);
    switch(ARM_DXL_IDS[i]){
      case ARM_DXL_ID_1:
      dxl.writeControlTableItem(MIN_POSITION_LIMIT,ARM_DXL_IDS[i],ARM_DXL_1_POSITION_MIN);
      dxl.writeControlTableItem(MAX_POSITION_LIMIT,ARM_DXL_IDS[i],ARM_DXL_1_POSITION_MAX);
      dxl.writeControlTableItem(HOMING_OFFSET,ARM_DXL_IDS[i],ARM_DXL_1_OFFSET);
      break;
      case ARM_DXL_ID_2:
      dxl.writeControlTableItem(MIN_POSITION_LIMIT,ARM_DXL_IDS[i],ARM_DXL_2_POSITION_MIN);
      dxl.writeControlTableItem(MAX_POSITION_LIMIT,ARM_DXL_IDS[i],ARM_DXL_2_POSITION_MAX);
      dxl.writeControlTableItem(HOMING_OFFSET,ARM_DXL_IDS[i],ARM_DXL_2_OFFSET);
      break;
      case ARM_DXL_ID_3:
      dxl.writeControlTableItem(MIN_POSITION_LIMIT,ARM_DXL_IDS[i],ARM_DXL_3_POSITION_MIN);
      dxl.writeControlTableItem(MAX_POSITION_LIMIT,ARM_DXL_IDS[i],ARM_DXL_3_POSITION_MAX);
      dxl.writeControlTableItem(HOMING_OFFSET,ARM_DXL_IDS[i],ARM_DXL_3_OFFSET);
      break;
      case ARM_DXL_ID_4:
      dxl.writeControlTableItem(MIN_POSITION_LIMIT,ARM_DXL_IDS[i],ARM_DXL_4_POSITION_MIN);
      dxl.writeControlTableItem(MAX_POSITION_LIMIT,ARM_DXL_IDS[i],ARM_DXL_4_POSITION_MAX);
      dxl.writeControlTableItem(HOMING_OFFSET,ARM_DXL_IDS[i],ARM_DXL_4_OFFSET);
      break;
    }
    dxl.writeControlTableItem(TORQUE_ENABLE, ARM_DXL_IDS[i],1);
    dxl.writeControlTableItem(PROFILE_VELOCITY,ARM_DXL_IDS[i],44);
  }
}

void loop() {
  MoveArmServoWithAngle(ARM_DXL_ID_1,-90);
  delay(2000);
  MoveArmServoWithAngle(ARM_DXL_ID_1,0);
  delay(2000);
  MoveArmServoWithAngle(ARM_DXL_ID_1,90);
  delay(2000);
  MoveArmServoWithAngle(ARM_DXL_ID_1,0);
  delay(5000);
}

void MoveArmServoWithAngle(uint8_t motorID,float angle){
  if(!isnan(angle)){
    int32_t motorPosition=map(constrain((int32_t)angle,-180,180), -180,180,0,4095);
    dxl.writeControlTableItem(GOAL_POSITION, motorID,motorPosition);
  }
}
