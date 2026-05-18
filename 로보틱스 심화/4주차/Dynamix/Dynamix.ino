#include <Dynamixel2Arduino.h>
#define DXL_SERIAL Serial1

const int DXL_DIR_PIN = 2;

const uint8_t DXL_ID =7;
const float DXL_PROTOCOL_VERSION = 2.0;

Dynamixel2Arduino dxl(DXL_SERIAL,DXL_DIR_PIN);

using namespace ControlTableItem;

void setup() {
  Serial.begin(115200);

  dxl.begin(57600);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
}

void loop() {
  Serial.print("PROTOCOL ");
  Serial.print(DXL_PROTOCOL_VERSION,1);
  Serial.print(", ID ");
  Serial.print(DXL_ID);
  Serial.print(": ");
  if(dxl.ping(DXL_ID)==true){
    Serial.print("ping succeeded!");
    Serial.print(", Model Number");
    Serial.print(dxl.getModelNumber(DXL_ID));

    if(dxl.readControlTableItem(DXL_LED,7==1)){
      dxl.writeControlTableItem(DXL_LED,7,0);
    }else{
      dxl.writeControlTableItem(DXL_LED,7,1);
    }
  }else{
    Serial.print("ping failed!, err code: ");
    Serial.println(dxl.getLastLibErrCode());
  }
  delay(1000);

  FindServos();
}

DYNAMIXEL::InfoFromPing_t ping_info[32];
void FindServos(void){
  Serial.println(" Try Protocol 2- broadcast ping: ");
  Serial.flush();

  if(uint8_t count_pinged = dxl.ping(DXL_BROADCAST_ID,ping_info, sizeof(ping_info)/sizeof(ping_info[0]),100)){
    Serial.print("pinged count: ");
    Serial.println(count_pinged);
    Serial.print("Detected Dynamixel : \n");
    for(int i = 0;i< count_pinged;i++){
    Serial.print("   ");
    Serial.print(ping_info[i].id,DEC);
    Serial.print(", Model:");
    Serial.print(ping_info[i].model_number);
    Serial.print(", Ver:");
    Serial.println(ping_info[i].firmware_version,DEC);
     }
  }else{
  Serial.print("Broadcast returned no items:");
  Serial.println(dxl.getLastLibErrCode());
}
}
