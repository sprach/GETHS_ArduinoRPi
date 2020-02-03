// 부저

#define PIN_BUZZER  8

void setup() {
    pinMode(PIN_BUZZER, OUTPUT);
}

void loop() {
    digitalWrite(PIN_BUZZER, HIGH);
    delay(1000);

    digitalWrite(PIN_BUZZER, LOW);
    delay(1000);
}
