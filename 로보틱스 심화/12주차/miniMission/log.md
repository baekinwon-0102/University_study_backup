# miniMission 수정 기록

## 사용자 요청 내역

1. 예제 코드에서 바퀴 속도, 바퀴 이동 방향, 그리퍼 제어, 매니퓰레이터 관절 모터 제어를 담당하는 부분을 확인했다.
2. 블랙베리 모바일 매니퓰레이터가 영상처럼 블럭을 옮기는 미션을 수행할 수 있는지 설명했다.
3. Pixy 기준값이 어떤 역할을 하는지 설명했다.
4. 버튼 제어를 추가했다.
   - 왼쪽 버튼을 누르면 미션을 시작한다.
   - 오른쪽 버튼을 누르면 미션을 일시정지한다.
   - 일시정지 상태에서 왼쪽 버튼을 다시 누르면 이어서 진행한다.
5. 깨진 주석과 선언 때문에 발생한 컴파일 오류를 수정했다.
   - `pixy was not declared in this scope`
   - `INITIAL_AND_MISSION_INSTRUCTION does not name a type`
   - `yPosError was not declared in this scope`
6. 깨진 주석을 정리하고 파일을 UTF-8로 저장했다.
7. Pixy signature 인식 방식을 설명하고 수정했다.
   - signature 3을 추가했다.
   - signature map `{0x01, 0x02, 0x04}`를 사용한다.
8. signature 1 블럭을 잡기 전에 오른쪽 보정을 추가했다.
   - signature 1을 잡을 때 그리퍼가 약간 왼쪽으로 빗나갔다.
   - signature 1을 잡기 전에 모바일베이스가 오른쪽으로 0.8 cm 이동하도록 했다.
9. 시작 LED 피드백을 추가했다.
   - 왼쪽 버튼을 누르면 핵심 미션 로직이 시작되기 전에 LED가 3번 점등된다.
10. 업로드한 참고 영상의 미션 흐름을 확인했다.
11. 미션 시작 전 블럭 위치 스캔 로직을 추가했다.
   - 초기 직진과 왼쪽 이동 후 잠깐 멈춘다.
   - 카메라를 왼쪽으로 90도 회전한다.
   - 카메라로 보이는 블럭들의 위치를 왼쪽부터 A~H로 저장한다.
   - 카메라를 다시 오른쪽으로 90도 회전해 원위치한다.
   - 각 signature 블럭을 저장된 위치의 상자 칸에 넣는다.
12. 상자 배치를 확인했다.
   - 상자는 2행 4열이다.
   - A는 1행 1열이다.
   - H는 2행 4열이다.

## 현재 미션 로직

현재 `miniMission.ino`의 흐름은 다음과 같다.

1. 버튼, 디버그 시리얼, Dynamixel 통신, 매니퓰레이터, 모바일베이스, PSD 센서, Pixy, 그리퍼를 초기화한다.
2. 왼쪽 버튼 입력을 기다린다.
3. LED를 3번 점등한다.
4. 매니퓰레이터를 보관 자세로 이동한다.
5. 전방 PSD 센서가 장애물 기준값에 도달할 때까지 전진한다.
6. 좌측 PSD 센서가 장애물 기준값에 도달할 때까지 왼쪽으로 이동한다.
7. 정지 후 블럭 위치를 스캔한다.
   - 모바일베이스 속도를 0으로 만든다.
   - Pixy 카메라를 왼쪽으로 90도 회전한다.
   - Pixy 램프를 켠다.
   - Pixy가 인식한 블럭들을 읽는다.
   - 각 블럭의 signature와 A~H 상자 위치를 저장한다.
   - Pixy 램프를 끈다.
   - 카메라를 원위치로 돌린다.
8. 고정 거리 이동으로 미션 구역까지 이동한다.
9. 각 목표 signature에 대해 반복한다.
   - signature 1은 sigmap `0x01`을 사용한다.
   - signature 2는 sigmap `0x02`를 사용한다.
   - signature 3은 sigmap `0x04`를 사용한다.
10. Pixy의 x좌표와 PSD 거리 보정을 이용해 목표 블럭 위치를 맞춘다.
11. 현재 목표가 signature 1이면, 잡기 전에 오른쪽으로 8 mm 이동한다.
12. Pixy의 y좌표를 기준으로 위쪽 블럭 잡기 자세 또는 아래쪽 블럭 잡기 자세를 선택한다.
13. 그리퍼를 닫아 블럭을 잡는다.
14. 매니퓰레이터를 보관 자세로 되돌린다.
15. PSD 보정을 이용해 투입 구역으로 이동한다.
16. 현재 블럭 signature에 대해 저장해 둔 A~H 위치를 이용해 투입 pose를 선택한다.
17. 그리퍼를 열어 블럭을 놓는다.
18. 매니퓰레이터를 보관 자세로 되돌린다.
19. 모든 목표 signature에 대해 반복한다.
20. 후진해서 Finish 위치로 이동한다.

## 버튼 로직

버튼 핀은 `Pins.h`에 정의되어 있다.

```cpp
#define SW1_PIN 41
#define SW2_PIN 40
```

현재 코드는 `INPUT_PULLUP` 방식을 기준으로 한다. 따라서 버튼을 누르면 `LOW`가 읽힌다.

```cpp
const uint8_t BUTTON_PRESSED = LOW;
```

왼쪽 버튼 동작:

- 시작 전에는 왼쪽 버튼을 누를 때까지 대기한다.
- 일시정지 중에는 왼쪽 버튼을 누르면 미션을 재개한다.

오른쪽 버튼 동작:

- 오른쪽 버튼을 누르면 미션을 일시정지한다.
- 모바일베이스를 정지시킨다.
- 왼쪽 버튼을 다시 누를 때까지 대기한다.

## 시작 LED 점등 로직

핵심 미션 로직이 시작되기 전에 LED가 3번 점등된다.

```cpp
void BlinkStartLed() {
  for (uint8_t i = 0; i < 3; i++) {
    digitalWrite(RGB_LED_PIN, HIGH);
    DelayWithStopCheck(200);
    digitalWrite(RGB_LED_PIN, LOW);
    DelayWithStopCheck(200);
  }
}
```

호출 순서는 다음과 같다.

```cpp
WaitForStartButton();
BlinkStartLed();
```

즉, 왼쪽 버튼 입력 후 LED가 3번 점등되고 미션이 시작된다.

## Signature 설정

현재 목표 signature는 다음과 같다.

```cpp
#define SIGNATURE_1_SIGMAP 0x01
#define SIGNATURE_2_SIGMAP 0x02
#define SIGNATURE_3_SIGMAP 0x04

const uint8_t MISSION_BLOCK_CNT = 3;
uint8_t targetBlockSigmaps[MISSION_BLOCK_CNT] = {
  SIGNATURE_1_SIGMAP,
  SIGNATURE_2_SIGMAP,
  SIGNATURE_3_SIGMAP
};
```

signature 번호와 sigmap 값의 관계는 다음과 같다.

```text
signature 1 -> 0x01
signature 2 -> 0x02
signature 3 -> 0x04
signature 4 -> 0x08
signature 5 -> 0x10
signature 6 -> 0x20
signature 7 -> 0x40
```

## Signature 1 그립 보정

signature 1 블럭을 잡을 때 그리퍼가 목표보다 약 0.5 cm 왼쪽으로 빗나갔다. 그래서 signature 1을 잡기 직전에 모바일베이스가 오른쪽으로 8 mm 이동하도록 했다.

```cpp
#define SIGNATURE_1_GRIP_RIGHT_OFFSET_MM 8.0
```

이 보정은 현재 목표가 signature 1일 때만 적용된다.

```cpp
targetBlockSigmap == SIGNATURE_1_SIGMAP
```

## A~H 상자 위치 로직

상자는 2행 4열이다.

```text
A = 1행 1열
B = 1행 2열
C = 1행 3열
D = 1행 4열
E = 2행 1열
F = 2행 2열
G = 2행 3열
H = 2행 4열
```

카메라 스캔 시 Pixy의 x좌표를 A~H 위치로 변환한다.

```cpp
char GetBoxPositionFromPixyX(int16_t pixyX)
```

저장된 위치는 투입 위치 번호로 변환된다.

```text
'A' -> 1
'B' -> 2
'C' -> 3
'D' -> 4
'E' -> 5
'F' -> 6
'G' -> 7
'H' -> 8
```

최종 EEPROM pose ID는 다음 방식으로 계산된다.

```cpp
MANIPULATOR_MISSION_FULFILLMENT_POSE_START_ID + goalPosition
```

현재 `MANIPULATOR_MISSION_FULFILLMENT_POSE_START_ID`는 `6`이다. 따라서 실제 pose ID는 다음과 같다.

```text
A -> pose ID 7
B -> pose ID 8
C -> pose ID 9
D -> pose ID 10
E -> pose ID 11
F -> pose ID 12
G -> pose ID 13
H -> pose ID 14
```

이 pose들은 로봇의 EEPROM에 미리 저장되어 있어야 한다.

## 카메라 회전 로직

블럭 위치를 저장하기 전에 카메라를 왼쪽으로 90도 회전한다.

```cpp
RotateCameraLeft90();
```

블럭 위치를 저장한 후 카메라를 다시 원위치로 돌린다.

```cpp
RotateCameraToOrigin();
```

현재 카메라 서보 상수는 다음과 같다.

```cpp
#define CAMERA_ORIGIN_SERVO_VALUE  0
#define CAMERA_LEFT_90_SERVO_VALUE 500
#define CAMERA_ROTATION_DELAY_MS   700
```

카메라가 정확히 90도로 회전하지 않으면 `CAMERA_LEFT_90_SERVO_VALUE` 값을 조정해야 한다.

## 주의 사항

- 이 코드는 EEPROM에 저장된 매니퓰레이터 pose에 의존한다.
- A~H 위치 투입이 정상 동작하려면 pose ID 7~14가 올바르게 저장되어 있어야 한다.
- Pixy signature는 미리 정확히 학습되어 있어야 한다.
- 왼쪽 카메라 스캔 중 특정 signature가 인식되지 않으면 해당 signature는 기존 `goalPositions[missionIdx]` 값을 사용한다.
- 현재 기본 fallback 값은 다음과 같다.

```cpp
uint8_t goalPositions[MISSION_BLOCK_CNT] = {7, 8, 6};
```

