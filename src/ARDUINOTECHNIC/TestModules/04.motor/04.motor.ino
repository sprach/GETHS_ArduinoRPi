//모터 테스트

#define MOTOR_A1  10
#define MOTOR_A2  11
#define MOTOR_B1  9
#define MOTOR_B2  3

void setup() {
    Serial.begin(115200);
}

void loop() {
    analogWrite(MOTOR_A1, 0);
    analogWrite(MOTOR_A2, 255);
    Serial.println("forward");
    delay(2000);
    
    analogWrite(MOTOR_A1, 255);
    analogWrite(MOTOR_A2, 0);
    Serial.println("backward");
    delay(2000);

    analogWrite(MOTOR_A1, 0);
    analogWrite(MOTOR_A2, 150);
    Serial.println("low speed forward");
    delay(2000);
    
    analogWrite(MOTOR_A1, 150);
    analogWrite(MOTOR_A2, 0);
    Serial.println("low speed backward");
    delay(2000);

}
