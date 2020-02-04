//모터 + 스위치 테스트

#define PIN_SW    2
#define MOTOR_A1  10
#define MOTOR_A2  11
#define MOTOR_B1  9
#define MOTOR_B2  3

volatile byte _state = LOW;
volatile boolean _changed_state = false; // 모터 상태 변경 여부

void setup() {
    Serial.begin(115200);
    pinMode(PIN_SW, INPUT); // Pullup인 경우 'INPUT_PULLUP'
    // args
    // - [0] 인터럽트(인터럽트 번호)
    // - [1] ISR: Interrupt Service Routine
    // - [2] mode (LOW, CHANGE, RISING, FALLING, HIGH)
    attachInterrupt(digitalPinToInterrupt(PIN_SW), sw_interrupt, CHANGE);
}

void loop() {
    if (_changed_state) {
        _changed_state = false;
        if (_state != LOW) {
            analogWrite(MOTOR_A1, 0);
            analogWrite(MOTOR_A2, 150);
            Serial.println("low speed forward");
        }
        else
        {
            analogWrite(MOTOR_A1, 0);
            analogWrite(MOTOR_A2, 0);
            Serial.println("stop");
        }

        delay(100);     // 스위치 디바운스를 위해 기다림
    }
}

void sw_interrupt() {
    _state = digitalRead(PIN_SW);
    _changed_state = true;
}
