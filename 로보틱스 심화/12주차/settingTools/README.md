## Competetion Example

### 대회 예제 소스코드 업로드 절차
1. EEPROM에 매니퓰레이터 pose 데이터 쓰기
[Blackberry ManageManipulatorPose 사용 가이드.pdf]의 2~5페이지 참고하여 진행
- EEPROM 비우기 (2페이지)
- [writeManipulatorPoseSampleData.ino] 사용하여 EEPROM에 예제 포즈 저장하기 (3페이지)
- [manageManipulatorPose.ino] 를 업로드 후 list 명령어 사용하여 pose 데이터가 잘 저장되었는지 확인하기 (4, 5페이지)

2. 15차시 예제 또는 miniMission 업로드

### 소스코드 리스트 및 설명
- checkPSD : 시리얼 모니터를 통해 4개의 PSD 값을 확인하는 기능을 제공하는 코드
    - 업로드 시 시리얼모니터에 즉시 표시됨
- manageManipulatorPose : EEPROM에 저장된 매니퓰레이터 포즈 데이터를 관리하는 기능을 제공하는 코드
    - 매니퓰레이터의 자세를 수동으로 조작하여 해당 포즈를 저장시킬수 있음\
    수동으로 조작하기 전에는 torque를 off 해주어야 함
    - 저장된 매니퓰레이터의 자세를 동작시켜 볼 수 있음\
    자세를 동작시키기 전에는 torque를 on 해주어야 함
    - 업로드 후 사용법은 시리얼모니터로 확인 가능
    - operatingTime은 ms 단위로, 너무 짧은 시간을 주면 모터에 무리가 갈 수 있으므로\
    주의 (최소 1000을 권장)
    - 커맨드 입력 시 시리얼모니터의 line ending은 "새 줄"로 설정해야 함
- writeManipulatorPoseExampleData : 대회 코드를 실행하기 위한 매니퓰레이터 포즈 샘플 데이터를 EEPROM에 작성하는 코드
    - 업로드 후 시리얼 모니터를 확인하여 EEPROM write 진행도를 확인할 수 있음
- poseMonitor : 매니퓰레이터의 포즈를 손으로 조정하고 시리얼 모니터로 현재 매니퓰레이터 모터의 값, 각도 그리고 그리퍼의 위치를 모니터링 하는 기능을 제공하는 코드
  - 블랙베리에 있는 버튼을 사용해 매니퓰레이터의 토크 on/off를 전환하며 자세를 조정 및 고정 하고, 현재 자세에 대한 정보를 시리얼모니터에 출력함

