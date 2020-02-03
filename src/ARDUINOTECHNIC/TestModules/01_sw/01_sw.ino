// 스위치 테스트

#define PIN_SW  2

void setup() {
    Serial.begin(115200);
    pinMode(PIN_SW, INPUT); // Pullup인 경우 'INPUT_PULLUP'
}

void loop() {
    int val = digitalRead(PIN_SW);
    Serial.println(val);
    delay(100);   // 100/1000초 딜레이 (0.1초)
}
