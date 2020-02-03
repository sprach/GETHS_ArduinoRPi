// 적외선 센서 테스트
// 감도는 센서모듈의 가변저항을 돌려 조절한다
// 왼쪽으로 돌림: 멀리까지 측정(민감해짐)
// 오른쪽으로 돌림: 가까이 측정(둔감해짐)

#define PIN_IRSENSOR  12

void setup() {
  Serial.begin(115200);
  pinMode(PIN_IRSENSOR, INPUT);
}

void loop() {
  int val = digitalRead(PIN_IRSENSOR);
  Serial.println(val);
  delay(100);
}
