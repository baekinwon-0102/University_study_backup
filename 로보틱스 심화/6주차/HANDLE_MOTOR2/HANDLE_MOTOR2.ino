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
#define VELOCITY_BASED_PROFILE 0x00
#define TIME_BASED_PROFILE 0x04

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

const uint16_t SW_START_ADDR = 112;
const uint16_t SW_DATA_SIZE = 8;

typedef struct sw_data{
  int32_t profile_velocity;
  int32_t goal_position;
}__attribute__((packed))sw_data_t;
sw_data_t sw_data[ARM_DXL_ID_CNT];
DYNAMIXEL::InfoSyncWriteInst_t sw_infos; 
DYNAMIXEL::XELInfoSyncWrite_t info_xels_sw[ARM_DXL_ID_CNT];

void setup() {
  Serial.begin(115200);
  dxl.begin(57600);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  for(int i = 0;i<ARM_DXL_ID_CNT;i++){
    dxl.writeControlTableItem(TORQUE_ENABLE,ARM_DXL_IDS[i],0);
    dxl.writeControlTableItem(DRIVE_MODE,ARM_DXL_IDS[i],REVERSE_MODE+TIME_BASED_PROFILE);
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
  }
  sw_infos.packet.p_buf= nullptr;
  sw_infos.packet.is_completed = false;
  sw_infos.addr = SW_START_ADDR;
  sw_infos.addr_length = SW_DATA_SIZE;
  sw_infos.p_xels = info_xels_sw;
  sw_infos.xel_count =0;

  sw_data[0].profile_velocity = 1000;
  sw_data[0].goal_position = 2048;
  sw_data[1].profile_velocity = 1000;
  sw_data[1].goal_position = 2048;
  sw_data[2].profile_velocity = 1000;
  sw_data[2].goal_position = 2048;
  sw_data[3].profile_velocity = 1000;
  sw_data[3].goal_position = 2048;

  for(int i =0;i<ARM_DXL_ID_CNT;i++){
    info_xels_sw[i].id = ARM_DXL_IDS[i];
    info_xels_sw[i].p_data = (uint8_t*)&sw_data[i];
    sw_infos.xel_count++;
  }
  sw_infos.is_info_changed=true;
}

void loop() {
  for(int i = -4;i<=4;i++){
    SetManipulatorForwardMoveForSyncWrite(0,i*10,-2*(i*10),2*(i*10),200);
    while(dxl.syncWrite(&sw_infos)!=true){}
    delay(200);
  }
  delay(2000);
  for(int i = 4;i>=-4;i--){
    SetManipulatorForwardMoveForSyncWrite(0,i*10,-2*(i*10),2*(i*10),200);
    while(dxl.syncWrite(&sw_infos)!=true){}
    delay(200);
  }
  delay(5000);
}

int32_t GetArmServoGoalPositionWithAngle(float angle){
  if(!isnan(angle)){
    return (int32_t)map(constrain((int32_t)angle,-180,180), -180,180,0,4095);
  }else{
    return (int32_t)-1;
  }
}

void SetManipulatorForwardMoveForSyncWrite(float a1,float a2,float a3,float a4, int32_t operatingTime){
  int32_t motor1GoalPosition=GetArmServoGoalPositionWithAngle(a1);
  int32_t motor2GoalPosition=GetArmServoGoalPositionWithAngle(a2);
  int32_t motor3GoalPosition=GetArmServoGoalPositionWithAngle(a3);
  int32_t motor4GoalPosition=GetArmServoGoalPositionWithAngle(a4);

  if(motor1GoalPosition != -1){
    sw_data[0].goal_position = motor1GoalPosition;
    sw_data[0].profile_velocity = operatingTime;
  }
  if(motor2GoalPosition != -1){
    sw_data[1].goal_position = motor2GoalPosition;
    sw_data[1].profile_velocity = operatingTime;
  }
  if(motor3GoalPosition != -1){
    sw_data[2].goal_position = motor3GoalPosition;
    sw_data[2].profile_velocity = operatingTime;
  }
  if(motor4GoalPosition != -1){
    sw_data[3].goal_position = motor4GoalPosition;
    sw_data[3].profile_velocity = operatingTime;
  }

  sw_infos.is_info_changed = true;
}
