// 신호등 LED 테스트

#define PIN_RED_LED     4
#define PIN_YELLOW_LED  5
#define PIN_GREEN_LED   6

void setup() {
    pinMode(PIN_RED_LED, OUTPUT);
    pinMode(PIN_YELLOW_LED, OUTPUT);
    pinMode(PIN_GREEN_LED, OUTPUT);
}

void loop() {
    digitalWrite(PIN_RED_LED, HIGH);
    digitalWrite(PIN_YELLOW_LED, LOW);
    digitalWrite(PIN_GREEN_LED, LOW);
    delay(1000);

    digitalWrite(PIN_RED_LED, LOW);
    digitalWrite(PIN_YELLOW_LED, HIGH);
    digitalWrite(PIN_GREEN_LED, LOW);
    delay(1000);

    digitalWrite(PIN_RED_LED, LOW);
    digitalWrite(PIN_YELLOW_LED, LOW);
    digitalWrite(PIN_GREEN_LED, HIGH);
    delay(1000);
}
