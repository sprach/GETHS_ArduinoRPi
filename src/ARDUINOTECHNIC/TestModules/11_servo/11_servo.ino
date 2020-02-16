// 서보모터
// 각도 조절은 70~90도의 각도가 되었을때 서보의 팔이 컨베이어를 막을 수 있으면 됨

#include <Servo.h>

Servo _myservo;

#define PIN_SERVO  7

void setup() {
    _myservo.attach(PIN_SERVO);
}

void loop() {
    _myservo.write(30);  // 30도로 조정
    delay(2000);

    _myservo.write(80);  // 80도로 조정
    delay(2000);
}
