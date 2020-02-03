// 스위치 인터럽트 테스트

#define PIN_SW  2

void setup() {
    Serial.begin(115200);
    pinMode(PIN_SW, INPUT); // Pullup인 경우 'INPUT_PULLUP'
    // args
    // - [0] 인터럽트(인터럽트 번호)
    // - [1] ISR: Interrupt Service Routine
    // - [2] mode (LOW, CHANGE, RISING, FALLING, HIGH)
    attachInterrupt(digitalPinToInterrupt(PIN_SW), sw_interrupt, RISING);
}

void loop() {
    delay(1000);
}

void sw_interrupt() {
    Serial.println("interrupted");
}
