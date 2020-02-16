/**************************************************************************
 * 작성자: 김종렬 (sprach21@daum.net)
 * 작성일: 2020. 02. 16. (Sun)
 * 
 * 할당한 핀이 지정한 상태가 되면 지정한 콜백 함수를 호출한다.
 * - 조건: 콜백 함수는 리턴 값이 없다.
 * 
 * ARDUINO UNO는 인터럽트를 지원하는 핀은 2, 3번 핀만 지원한다.
 * - ex) attachInterrupt(digitalPinToInterrupt(PIN_SW), interrupted_sw, HIGH);
 * 그래서 2, 3번 핀 이외의 입력 신호는 별도로 처리를 해 주어야 한다. 
 * 이에 인터럽트는 아니지만, LOW, HIGH에 대한 신호 변화에 대한 처리를 콜백으로 지원하는 함수를 만들었다.
 * 
 * ex)
 * 1. 외부 선언
 *    void callback_ir_sensor(int);
 *    // 예시) 12번 핀 상태가 HIGH가 되면 callback_ir_sensor(int) 함수를 호출한다.
 *    //      콜백 함수의 인수에는 핀 번호가 전달된다.
 *    CheckPinStatus _chkIrSensor = CheckPinStatus(12, callback_ir_sensor, HIGH);
 * 
 * 2. setup() 함수
 *    void setup() {
 *      // put your setup code here, to run once:
 *      Serial.begin(115200);
 *      pinMode(12, INPUT);
 *      Serial.println("Ready...");
 *    }
 *
 * 3. loop() 함수
 *    void loop() {
 *        // put your main code here, to run repeatedly:
 *        _chkIrSensor.CheckPin();
 *    }
 * 
 * 4. callback_ir_sensor() 함수
 *    void callback_ir_sensor(int pinNo)
 *    {
 *        Serial.print("Interrupted pin no: ");
 *        Serial.println(pinNo);
 *    }
 **************************************************************************/
#include <inttypes.h>
#include <Arduino.h>
#include "CheckPinStatus.h"

// [0]: 핀번호
// [1]: Callback 함수
// [2]: Pin 상태 (LOW, HIGH)
CheckPinStatus::CheckPinStatus(uint8_t pinNo, void (*pf)(int), int pinStatus)
{
    __pinNo = pinNo;
    __pf = pf;
    __pinStatus = pinStatus;
    //
    __lastPinStatus = LOW;
}

void CheckPinStatus::CheckPin()
{
    int val = digitalRead(__pinNo);
    if (val != __lastPinStatus) {
        __lastPinStatus = val;
        if (val == __pinStatus) {
            if (__pf != NULL) __pf(__pinNo);
        }
    }
}
