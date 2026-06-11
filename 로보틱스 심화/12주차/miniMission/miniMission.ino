
#include "Debug.h"
#include "Pixy.h"
#include "Manipulator.h"
#include "Mobilebase.h"
#include "PSD.h"
#include "Gripper.h"
#include "Pins.h"

#define PIXY2_X_SETPOINT                      172
#define PIXY2_Y_SETPOINT                      107
#define PIXY_TOLERANCE                        2
#define PSD_TOLERANCE                         2
#define PIXY_CONTROL_RATIO                    0.3
#define PSD_CONTROL_RATIO                     0.04

#define PSD_FL_CORRECTION                     -12
#define OBSTACLE_FRONT_PSD_SET_POINT          525
#define OBSTACLE_LEFT_PSD_SET_POINT           418
#define MISSION_FRONT_PSD_SET_POINT           310
#define MISSION_LEFT_PSD_SET_POINT            595
#define SIGNATURE_1_SIGMAP                    0x01
#define SIGNATURE_2_SIGMAP                    0x02
#define SIGNATURE_3_SIGMAP                    0x04
#define SIGNATURE_1_GRIP_RIGHT_OFFSET_MM      20.0
#define SIGNATURE_2_GRIP_RIGHT_OFFSET_MM      18.0
#define SIGNATURE_3_GRIP_RIGHT_OFFSET_MM      18.0
#define SIGNATURE_2_3_GRIP_FORWARD_OFFSET_MM  20.0
#define SIGNATURE_2_AFTER_GRIP_BACKWARD_MM    15.0
#define FINISH_BODY_CW_CORRECTION_VALUE       300
#define FINISH_BODY_CW_CORRECTION_TIME        700
#define SIGNATURE_MAX_COUNT                   7
#define BLOCK_POSITION_COUNT                  6
#define BOX_FIRST_POSITION                    'A'
#define BOX_LAST_POSITION                     'F'
#define UNKNOWN_BOX_POSITION                  '?'
#define CAMERA_ORIGIN_SERVO_VALUE             0
#define CAMERA_LEFT_90_SERVO_VALUE            1000
#define CAMERA_ROTATION_DELAY_MS              700

Pixy2SPI_SS pixy;

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

const uint8_t BUTTON_PRESSED = LOW;
bool isMobilebasePositionControlMode = false;
char savedBoxPositionBySignature[SIGNATURE_MAX_COUNT + 1];
int16_t savedBlockXBySignature[SIGNATURE_MAX_COUNT + 1];

bool IsStartButtonPressed() {
  return digitalRead(SW1_PIN) == BUTTON_PRESSED;
}

bool IsStopButtonPressed() {
  return digitalRead(SW2_PIN) == BUTTON_PRESSED;
}

void ChangeMobilebaseToVelocityMode() {
  ChangeMobilebaseMode2VelocityControlMode(dxl);
  isMobilebasePositionControlMode = false;
}

void ChangeMobilebaseToPositionMode() {
  ChangeMobilebaseMode2ExtendedPositionControlWithTimeBasedProfileMode(dxl);
  isMobilebasePositionControlMode = true;
}

void PauseMissionIfRequested() {
  if (IsStopButtonPressed()) {
    pixy.setLamp(0, 0);
    bool wasPositionControlMode = isMobilebasePositionControlMode;
    ChangeMobilebaseToVelocityMode();
    SetMobileGoalVelocityForSyncWrite(dxl, 0, 0, 0, 0);
    DEBUG_SERIAL.println("pause");
    delay(200);

    while (!IsStartButtonPressed()) {
      SetMobileGoalVelocityForSyncWrite(dxl, 0, 0, 0, 0);
      delay(20);
    }

    delay(200);
    if (wasPositionControlMode) {
      ChangeMobilebaseToPositionMode();
    } else {
      ChangeMobilebaseToVelocityMode();
    }
    DEBUG_SERIAL.println("resume");
  }
}

void WaitForStartButton() {
  DEBUG_SERIAL.println("wait start");
  while (!IsStartButtonPressed()) {
    PauseMissionIfRequested();
    delay(20);
  }
  delay(200);
  DEBUG_SERIAL.println("start");
}

void DelayWithStopCheck(uint32_t delayMillis) {
  uint32_t startMillis = millis();
  while (millis() - startMillis < delayMillis) {
    PauseMissionIfRequested();
    delay(10);
  }
}

void RotateCameraLeft90() {
  pixy.setServos(CAMERA_LEFT_90_SERVO_VALUE, GRIP_ANGLE_OPEN);
  DelayWithStopCheck(CAMERA_ROTATION_DELAY_MS);
}

void RotateCameraToOrigin() {
  pixy.setServos(CAMERA_ORIGIN_SERVO_VALUE, GRIP_ANGLE_OPEN);
  DelayWithStopCheck(CAMERA_ROTATION_DELAY_MS);
}

uint8_t GetSignatureFromSigmap(uint8_t sigmap) {
  for (uint8_t signature = 1; signature <= SIGNATURE_MAX_COUNT; signature++) {
    if (sigmap == (1 << (signature - 1))) {
      return signature;
    }
  }
  return 0;
}

char GetBoxPositionFromPixyX(int16_t pixyX) {
  int16_t x = constrain(pixyX, PIXY_CCC_X_MIN, PIXY_CCC_X_MAX);
  uint8_t positionIndex = ((int32_t)(x - PIXY_CCC_X_MIN) * BLOCK_POSITION_COUNT)
                          / (PIXY_CCC_X_MAX - PIXY_CCC_X_MIN + 1);
  if (positionIndex >= BLOCK_POSITION_COUNT) {
    positionIndex = BLOCK_POSITION_COUNT - 1;
  }
  return BOX_FIRST_POSITION + positionIndex;
}

uint8_t GetGoalPositionFromBoxPosition(char boxPosition, uint8_t defaultGoalPosition) {
  if (boxPosition >= BOX_FIRST_POSITION && boxPosition <= BOX_LAST_POSITION) {
    return boxPosition - BOX_FIRST_POSITION + 1;
  }
  return defaultGoalPosition;
}

void ResetSavedBlockPositions() {
  for (uint8_t signature = 0; signature <= SIGNATURE_MAX_COUNT; signature++) {
    savedBoxPositionBySignature[signature] = UNKNOWN_BOX_POSITION;
    savedBlockXBySignature[signature] = -1;
  }
}

void SaveBlockPositionsFromLeftCamera() {
  SetMobileGoalVelocityForSyncWrite(dxl, 0, 0, 0, 0);
  ResetSavedBlockPositions();
  RotateCameraLeft90();
  pixy.setLamp(1, 1);
  DelayWithStopCheck(500);

  pixy.ccc.getBlocks(true);

  for (uint8_t i = 0; i < pixy.ccc.numBlocks; i++) {
    uint8_t signature = pixy.ccc.blocks[i].m_signature;
    if (signature >= 1 && signature <= SIGNATURE_MAX_COUNT) {
      savedBlockXBySignature[signature] = pixy.ccc.blocks[i].m_x;
      savedBoxPositionBySignature[signature] = GetBoxPositionFromPixyX(pixy.ccc.blocks[i].m_x);

      DEBUG_SERIAL.print("signature ");
      DEBUG_SERIAL.print(signature);
      DEBUG_SERIAL.print(" position ");
      DEBUG_SERIAL.print(savedBoxPositionBySignature[signature]);
      DEBUG_SERIAL.print(" x ");
      DEBUG_SERIAL.println(savedBlockXBySignature[signature]);
    }
  }

  pixy.setLamp(0, 0);
  RotateCameraToOrigin();
}

bool NeedsGripRightOffset(uint8_t targetBlockSigmap) {
  return targetBlockSigmap == SIGNATURE_1_SIGMAP
         || targetBlockSigmap == SIGNATURE_2_SIGMAP
         || targetBlockSigmap == SIGNATURE_3_SIGMAP;
}

float GetGripRightOffsetMm(uint8_t targetBlockSigmap) {
  if (targetBlockSigmap == SIGNATURE_1_SIGMAP) {
    return SIGNATURE_1_GRIP_RIGHT_OFFSET_MM;
  }
  if (targetBlockSigmap == SIGNATURE_2_SIGMAP) {
    return SIGNATURE_2_GRIP_RIGHT_OFFSET_MM;
  }
  if (targetBlockSigmap == SIGNATURE_3_SIGMAP) {
    return SIGNATURE_3_GRIP_RIGHT_OFFSET_MM;
  }
  return 0.0;
}

void MoveRightBeforeGripIfNeeded(uint8_t targetBlockSigmap) {
  if (NeedsGripRightOffset(targetBlockSigmap)) {
    float rightOffsetMm = GetGripRightOffsetMm(targetBlockSigmap);
    SetMobileGoalVelocityForSyncWrite(dxl, 0, 0, 0, 0);
    ChangeMobilebaseToPositionMode();
    if (rightOffsetMm > 0.0) {
      DriveDistanceAndMmPerSecAndDirection(dxl, rightOffsetMm, DRIVE_DIRECTION_RIGHT);
      while(!CheckIfMobilebaseIsInPosition(dxl)) { PauseMissionIfRequested(); }
    }
    if (targetBlockSigmap == SIGNATURE_2_SIGMAP || targetBlockSigmap == SIGNATURE_3_SIGMAP) {
      DriveDistanceAndMmPerSecAndDirection(dxl, SIGNATURE_2_3_GRIP_FORWARD_OFFSET_MM, DRIVE_DIRECTION_FORWARD);
      while(!CheckIfMobilebaseIsInPosition(dxl)) { PauseMissionIfRequested(); }
    }
    ChangeMobilebaseToVelocityMode();
  }
}

void MoveBackwardAfterGripIfNeeded(uint8_t targetBlockSigmap) {
  if (targetBlockSigmap == SIGNATURE_2_SIGMAP) {
    SetMobileGoalVelocityForSyncWrite(dxl, 0, 0, 0, 0);
    ChangeMobilebaseToPositionMode();
    DriveDistanceAndMmPerSecAndDirection(dxl, SIGNATURE_2_AFTER_GRIP_BACKWARD_MM, DRIVE_DIRECTION_BACKWARD);
    while(!CheckIfMobilebaseIsInPosition(dxl)) { PauseMissionIfRequested(); }
    ChangeMobilebaseToVelocityMode();
  }
}

void RotateBodyClockwiseBeforeFinishLine() {
  SetMobileGoalVelocityForSyncWrite(dxl, 0, 0, 0, 0);
  ChangeMobilebaseToPositionMode();
  SetMobileRelativePositionForSyncWrite(dxl,
                                        -FINISH_BODY_CW_CORRECTION_VALUE,
                                        FINISH_BODY_CW_CORRECTION_VALUE,
                                        -FINISH_BODY_CW_CORRECTION_VALUE,
                                        FINISH_BODY_CW_CORRECTION_VALUE,
                                        FINISH_BODY_CW_CORRECTION_TIME);
  while(!CheckIfMobilebaseIsInPosition(dxl)) { PauseMissionIfRequested(); }
}

void PrintMissionTarget(uint8_t missionIdx, uint8_t targetBlockSigmap) {
  DEBUG_SERIAL.print("mission ");
  DEBUG_SERIAL.print(missionIdx + 1);
  DEBUG_SERIAL.print(" target sigmap 0x");
  DEBUG_SERIAL.println(targetBlockSigmap, HEX);
}

enum ManipulatorPoseID {
  INITIAL_AND_MISSION_INSTRUCTION = 1,
  STORAGE,
  PRE_GRIP_UPPER_BLOCK,
  GRIP_UPPER_BLOCK,
  PRE_GRIP_LOWER_BLOCK,
  GRIP_LOWER_BLOCK
};
#define MANIPULATOR_MISSION_FULFILLMENT_POSE_START_ID  6

bool haveFoundBlock = false;
const uint8_t MISSION_BLOCK_CNT = 3;

uint8_t targetBlockSigmaps[MISSION_BLOCK_CNT] = {SIGNATURE_1_SIGMAP, SIGNATURE_2_SIGMAP, SIGNATURE_3_SIGMAP};
uint8_t goalPositions[MISSION_BLOCK_CNT] = {2, 4, 6};

uint8_t GetGoalPositionForMission(uint8_t missionIdx) {
  uint8_t signature = GetSignatureFromSigmap(targetBlockSigmaps[missionIdx]);
  if (signature >= 1 && signature <= SIGNATURE_MAX_COUNT) {
    return GetGoalPositionFromBoxPosition(savedBoxPositionBySignature[signature], goalPositions[missionIdx]);
  }
  return goalPositions[missionIdx];
}

void setup() {
  pinMode(SW1_PIN, INPUT_PULLUP);
  pinMode(SW2_PIN, INPUT_PULLUP);

  InitDebug();
  InitMotorCommunication(dxl);
  while(!InitManipulator(dxl)) {}
  while(!InitMobilebase(dxl)) {}

  InitPSD();
  InitPixy(pixy);
  pixy.setLamp(0, 0);
  OpenGripper(pixy);

  DEBUG_SERIAL.println("run");
  WaitForStartButton();

  RunManipulatorPoseWithPoseDataInEEPROM(dxl, STORAGE, 1000, 0.0);
  SetMobileGoalVelocityForSyncWrite(dxl, 0, 0, 0, 0);
  DelayWithStopCheck(1000);

  int16_t flPSDValue1, frPSDValue1;
  while(1) {
    PauseMissionIfRequested();
    GetValueFromFrontPSDSensors(&flPSDValue1, &frPSDValue1);
    if (!DriveForwardUntilDistanceWithTwoSensors(dxl, flPSDValue1+PSD_FL_CORRECTION - OBSTACLE_FRONT_PSD_SET_POINT,
                                                 frPSDValue1 - OBSTACLE_FRONT_PSD_SET_POINT, PSD_TOLERANCE)) break;
  }

  int16_t slPSDValue2;
  while(1) {
    PauseMissionIfRequested();
    GetValueFromSideLeftPSDSensor(&slPSDValue2);
    if (!DriveUntilDistanceWithOneSensor(dxl, slPSDValue2 - OBSTACLE_LEFT_PSD_SET_POINT, PSD_TOLERANCE, DRIVE_DIRECTION_LEFT)) break;
  }

  SaveBlockPositionsFromLeftCamera();

  RunManipulatorPoseWithPoseDataInEEPROM(dxl, STORAGE, 1000, 0.0);

  ChangeMobilebaseToPositionMode();
  DriveDistanceAndMmPerSecAndDirection(dxl, 800.0);
  while(!CheckIfMobilebaseIsInPosition(dxl)) { PauseMissionIfRequested(); }

  DriveDistanceAndMmPerSecAndDirection(dxl, 30.0, DRIVE_DIRECTION_RIGHT);
  while(!CheckIfMobilebaseIsInPosition(dxl)) { PauseMissionIfRequested(); }

  ChangeMobilebaseToVelocityMode();

  for (int missionIdx = 0 ; missionIdx < MISSION_BLOCK_CNT ; missionIdx++) {
    haveFoundBlock = false;
    PrintMissionTarget(missionIdx, targetBlockSigmaps[missionIdx]);

    int16_t slPSDValue3, frPSDValue3;
    while(1) {
      PauseMissionIfRequested();
      GetValueFromSideLeftPSDSensor(&slPSDValue3);
      GetValueFromFrontRightPSDSensor(&frPSDValue3);
      if (!LocateWithTwoSensors(dxl, slPSDValue3 - MISSION_LEFT_PSD_SET_POINT, frPSDValue3 - MISSION_FRONT_PSD_SET_POINT,
                                PSD_TOLERANCE, PSD_TOLERANCE, PSD_CONTROL_RATIO, PSD_CONTROL_RATIO,
                                DRIVE_DIRECTION_LEFT)) break;
    }

    pixy.setLamp(1, 1);
    DelayWithStopCheck(500);

#ifdef STOP_TO_COLOR_CALIBRATION
    SetMobileGoalVelocityForSyncWrite(dxl, 0, 0, 0, 0);
    while(1) {delay(1);}
#endif

    int16_t slPSDValue4, flPSDValue4, frPSDValue4;
    while(!haveFoundBlock) {
      PauseMissionIfRequested();

      GetValueFromSideLeftPSDSensor(&slPSDValue4);
      if (slPSDValue4 < 160) {
        SetMobileGoalVelocityForSyncWrite(dxl, 0, 0, 0, 0);
        break;
      }

      GetValueFromFrontPSDSensors(&flPSDValue4, &frPSDValue4);

      pixy.ccc.getBlocks(true, targetBlockSigmaps[missionIdx]);
      int16_t blockXError = (pixy.ccc.numBlocks ? pixy.ccc.blocks[0].m_x : PIXY_CCC_X_MAX) - PIXY2_X_SETPOINT;
      int16_t yPosError, rotationError;
      bool inControl = true;

      if (slPSDValue4 < 190) {
        yPosError = flPSDValue4+PSD_FL_CORRECTION - MISSION_FRONT_PSD_SET_POINT;
        inControl = LocateWithTwoSensors(dxl,blockXError, yPosError,
                                         PIXY_TOLERANCE, PSD_TOLERANCE, PIXY_CONTROL_RATIO, PSD_CONTROL_RATIO,
                                         DRIVE_DIRECTION_LEFT);
      } else if (slPSDValue4 < 245) {

        yPosError = (flPSDValue4+PSD_FL_CORRECTION+frPSDValue4)/2 - MISSION_FRONT_PSD_SET_POINT;
        rotationError = frPSDValue4 - (flPSDValue4+PSD_FL_CORRECTION);
        inControl = DriveWithPositionAndRotationErrors(dxl, blockXError, yPosError, rotationError,
                                                       PIXY_TOLERANCE, PSD_TOLERANCE, PSD_TOLERANCE,
                                                       PIXY_CONTROL_RATIO, PSD_CONTROL_RATIO, PSD_CONTROL_RATIO,
                                                       DRIVE_DIRECTION_LEFT, DRIVE_DIRECTION_FORWARD, ROTATE_CCW);
      } else {
        yPosError = frPSDValue4 - MISSION_FRONT_PSD_SET_POINT;
        inControl = LocateWithTwoSensors(dxl, blockXError, yPosError,
                                         PIXY_TOLERANCE, PSD_TOLERANCE, PIXY_CONTROL_RATIO, PSD_CONTROL_RATIO,
                                         DRIVE_DIRECTION_LEFT);
      }

      if (!inControl) {
        haveFoundBlock = true;
        DEBUG_SERIAL.println("block found");
      }
    }

    while(!haveFoundBlock) {
      PauseMissionIfRequested();
      GetValueFromSideLeftPSDSensor(&slPSDValue4);
      if (slPSDValue4 > 635) {
        SetMobileGoalVelocityForSyncWrite(dxl, 0, 0, 0, 0);
        break;
      }

      GetValueFromFrontPSDSensors(&flPSDValue4, &frPSDValue4);
      pixy.ccc.getBlocks(true, targetBlockSigmaps[missionIdx]);
      int16_t blockXError = (pixy.ccc.numBlocks ? pixy.ccc.blocks[0].m_x : PIXY_CCC_X_MIN) - PIXY2_X_SETPOINT;
      int16_t yPosError, rotationError;
      bool inControl = true;

      if (slPSDValue4 < 190) {
        yPosError = flPSDValue4+PSD_FL_CORRECTION - MISSION_FRONT_PSD_SET_POINT;
        inControl = LocateWithTwoSensors(dxl, blockXError, yPosError,
                                         PIXY_TOLERANCE, PSD_TOLERANCE, PIXY_CONTROL_RATIO, PSD_CONTROL_RATIO,
                                         DRIVE_DIRECTION_LEFT);
      } else if (slPSDValue4 < 245) {

        yPosError = (flPSDValue4+PSD_FL_CORRECTION+frPSDValue4)/2 - MISSION_FRONT_PSD_SET_POINT;
        rotationError = frPSDValue4 - (flPSDValue4+PSD_FL_CORRECTION);
        inControl = DriveWithPositionAndRotationErrors(dxl, blockXError, yPosError, rotationError,
                                                       PIXY_TOLERANCE, PSD_TOLERANCE, PSD_TOLERANCE,
                                                       PIXY_CONTROL_RATIO, PSD_CONTROL_RATIO, PSD_CONTROL_RATIO,
                                                       DRIVE_DIRECTION_LEFT, DRIVE_DIRECTION_FORWARD, ROTATE_CCW);
      } else {
        yPosError = frPSDValue4 - MISSION_FRONT_PSD_SET_POINT;
        inControl = LocateWithTwoSensors(dxl, blockXError, yPosError,
                                         PIXY_TOLERANCE, PSD_TOLERANCE, PIXY_CONTROL_RATIO, PSD_CONTROL_RATIO,
                                         DRIVE_DIRECTION_LEFT);
      }

      if (!inControl) {
        haveFoundBlock = true;
        DEBUG_SERIAL.println("block found");
      }
    }

    if (haveFoundBlock) {
      MoveRightBeforeGripIfNeeded(targetBlockSigmaps[missionIdx]);

      if (pixy.ccc.blocks[0].m_y < PIXY2_Y_SETPOINT) {
        RunManipulatorPoseWithPoseDataInEEPROM(dxl, PRE_GRIP_UPPER_BLOCK, 1000, 0.0);
        DelayWithStopCheck(1200);
        RunManipulatorPoseWithPoseDataInEEPROM(dxl, GRIP_UPPER_BLOCK, 1000, 0.0);
        DelayWithStopCheck(1500);
      } else {
        RunManipulatorPoseWithPoseDataInEEPROM(dxl, PRE_GRIP_LOWER_BLOCK, 1000, 0.0);
        DelayWithStopCheck(1200);
        RunManipulatorPoseWithPoseDataInEEPROM(dxl, GRIP_LOWER_BLOCK, 1000, 0.0);
        DelayWithStopCheck(1500);
      }

      CloseGripper(pixy);
      DelayWithStopCheck(500);

      pixy.setLamp(0, 0);

      RunManipulatorPoseWithPoseDataInEEPROM(dxl, STORAGE, 1000, 0.0);
      DelayWithStopCheck(1500);
      MoveBackwardAfterGripIfNeeded(targetBlockSigmaps[missionIdx]);

      while(1) {
        PauseMissionIfRequested();
        GetValueFromSideLeftPSDSensor(&slPSDValue4);
        GetValueFromFrontPSDSensors(&flPSDValue4, &frPSDValue4);
        int16_t xPosError = slPSDValue4 - MISSION_LEFT_PSD_SET_POINT;
        int16_t yPosError, rotationError;
        bool inControl = true;

        if (slPSDValue4 < 190) {
          yPosError = flPSDValue4+PSD_FL_CORRECTION - MISSION_FRONT_PSD_SET_POINT;
          inControl = LocateWithTwoSensors(dxl, xPosError, yPosError,
                                           PSD_TOLERANCE, PSD_TOLERANCE, PSD_CONTROL_RATIO, PSD_CONTROL_RATIO,
                                           DRIVE_DIRECTION_LEFT);
        } else if (slPSDValue4 < 245) {

          yPosError = (flPSDValue4+PSD_FL_CORRECTION+frPSDValue4)/2 - MISSION_FRONT_PSD_SET_POINT;
          rotationError = frPSDValue4 - (flPSDValue4+PSD_FL_CORRECTION);
          inControl = DriveWithPositionAndRotationErrors(dxl, xPosError, yPosError, rotationError,
                                                         PSD_TOLERANCE, PSD_TOLERANCE, PSD_TOLERANCE,
                                                         PSD_CONTROL_RATIO, PSD_CONTROL_RATIO, PSD_CONTROL_RATIO,
                                                         DRIVE_DIRECTION_LEFT, DRIVE_DIRECTION_FORWARD, ROTATE_CCW);
        } else {
          yPosError = frPSDValue4 - MISSION_FRONT_PSD_SET_POINT;
          inControl = LocateWithTwoSensors(dxl, xPosError, yPosError,
                                           PSD_TOLERANCE, PSD_TOLERANCE, PSD_CONTROL_RATIO, PSD_CONTROL_RATIO,
                                           DRIVE_DIRECTION_LEFT);
        }

        if (!inControl) {
          break;
        }
      }

      RunManipulatorPoseWithPoseDataInEEPROM(dxl, STORAGE, 800, -90.0);
      DelayWithStopCheck(1000);
      uint8_t goalPosition = GetGoalPositionForMission(missionIdx);
      RunManipulatorPoseWithPoseDataInEEPROM(dxl, MANIPULATOR_MISSION_FULFILLMENT_POSE_START_ID + goalPosition, 1000);
      DelayWithStopCheck(1300);

      OpenGripper(pixy);
      DelayWithStopCheck(500);

      RunManipulatorPoseWithPoseDataInEEPROM(dxl, STORAGE, 1000, 0.0);
      DelayWithStopCheck(1500);

      haveFoundBlock = false;
    } else {
      DEBUG_SERIAL.println("block not found, retry");
      missionIdx--;
      DelayWithStopCheck(500);
    }
  }

  ChangeMobilebaseToPositionMode();
  RotateBodyClockwiseBeforeFinishLine();
  DriveDistanceAndMmPerSecAndDirection(dxl, 1280.0, DRIVE_DIRECTION_BACKWARD);

  while(1) {
    PauseMissionIfRequested();
    delay(1000);
  }
}

void loop() {
}
