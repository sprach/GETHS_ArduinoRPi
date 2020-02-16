#include "CheckPinStatus.h"

void callback_check_pin(int);

// 핀 번호 정의
#define PIN_SW          2
#define PIN_IR_SENSOR  12

CheckPinStatus _chkSw = CheckPinStatus(PIN_SW, callback_check_pin, HIGH);
CheckPinStatus _chkIrSensor = CheckPinStatus(PIN_IR_SENSOR, callback_check_pin, HIGH);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  pinMode(PIN_SW, INPUT);
  pinMode(PIN_IR_SENSOR, INPUT);

  Serial.println("Ready...");
}

void loop() {
  // put your main code here, to run repeatedly:
  _chkSw.CheckPin();
  _chkIrSensor.CheckPin();
}

//----------------------------------------------------[ callback_check_pin() ]
// 입력 핀의 상태 검사
// 인수에 핀번호가 들어온다.
void callback_check_pin(int pinNo)
{
  Serial.print("Interrupted pin no: ");
  Serial.println(pinNo);
}
