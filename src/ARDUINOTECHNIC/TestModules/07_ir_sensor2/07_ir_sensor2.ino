#include "CheckPinStatus.h"

void callback_ir_sensor(int);

// 핀 번호 정의
#define PIN_IR_SENSOR  12

CheckPinStatus _chkIrSensor = CheckPinStatus(PIN_IR_SENSOR, callback_ir_sensor, HIGH);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  pinMode(PIN_IR_SENSOR, INPUT);

  Serial.println("Ready...");
}

void loop() {
  // put your main code here, to run repeatedly:
  _chkIrSensor.CheckPin();
}

//----------------------------------------------------[ callback_ir_sensor() ]
// IR 센서 신호 입력 상태 검사
// 인수에 핀번호가 들어온다.
void callback_ir_sensor(int pinNo)
{
  Serial.print("Interrupted pin no: ");
  Serial.println(pinNo);
}
