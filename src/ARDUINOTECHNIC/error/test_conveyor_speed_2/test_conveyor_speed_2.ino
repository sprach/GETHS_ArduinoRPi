// 컨베이어 구동 시간 측정용
// - IR센서에서 물건을 감지하면 동작 시작하여 지정된 시간동안 컨베이어가 움직이도록 한다.
// - 모터 구동 속도가 조금씩 다르므로 물체가 첫부분부터 컨베이어 끝부분까지 이동하는 소요시간 측정용

#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);    //주소번지 0x27
//LiquidCrystal_I2C lcd(0x3F,20,4);  //주소번지 0x3F

Servo _myservo;

// 모터 채널 A
#define MOTOR_A1  10
#define MOTOR_A2  11
// (사용안함) 모터 채널 B
#define MOTOR_B1  9
#define MOTOR_B2  3

// 핀 번호 정의
#define PIN_SERVO       7
#define PIN_IR_SENSOR  12
#define PIN_SW          2
#define PIN_BUZZER      8
#define PIN_RED_LED     4
#define PIN_YELLOW_LED  5
#define PIN_GREEN_LED   6

#define SERVO_CLOSING_ANGLE   30    /* 서보의 암이 닫히는 각도 */
#define SERVO_OPENING_ANGLE   80    /* 서보의 암이 열리는 각도 */
#define MOTOR_DRIVING_SPEED   200   /* 모터의 구동 속도 */
#define CONVEYOR_DRIVING_LIMIT_TIME 5000  /* 컨베이어 구동 시간 */

// 시간 계산용
unsigned long _chipDetectedTime = 0;

// 색상별 카운트
int _redChipCount = 0;
int _greenChipCount = 0;
int _bludChipCount = 0;

boolean _isDetectedChip = false;
boolean _isNewDetectedChip = false;

int _motorDirection = 0;            // 0:순방향, 1:역방향
int _motorStatus = 1;               // 0:정지, 1:모터 순방향, 2:모터 역방향 
int _prevMotorStatus = 0;

// 컬러 센서
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);

//--------------------------------------------------------------[ setup() ]
void setup() {
    Serial.begin(115200);
    pinMode(PIN_IR_SENSOR,INPUT);

    // 서보 암(ARM)을 열림으로 설정해 놓는다. (테스트용이므로)
    _myservo.attach(PIN_SERVO);
    _myservo.write(SERVO_OPENING_ANGLE);

    pinMode(PIN_RED_LED, OUTPUT);
    pinMode(PIN_YELLOW_LED, OUTPUT);
    pinMode(PIN_GREEN_LED, OUTPUT);

    // 모든 LED를 끈다.
    turnOffAllLeds();

    // 버튼 스위치 인터럽트 정의
    attachInterrupt(digitalPinToInterrupt(PIN_SW), interrupted_sw, RISING);

    // IR 센서 인터럽트 정의
    attachInterrupt(digitalPinToInterrupt(PIN_IR_SENSOR), interrupted_ir_sensor, RISING);

    // initialize the lcd 
    lcd.init();

    // Print a message to the LCD.
    lcd.backlight();
    lcd.setCursor(4,0);
    lcd.print("conveyor");
    lcd.setCursor(4,1);
    lcd.print("GET HS");

    // 컨베이어가 구동중이 아니므로 RED LED를 켠다.
    turnOnSingleLed(PIN_RED_LED);
}

//---------------------------------------------------------------[ loop() ]
void loop() {
    if (_isDetectedChip)         // 물체가 감지되어 있다.
    {   
        if (_isNewDetectedChip)  // 새 물체 감지
        {
            _isNewDetectedChip = false;
            // 컨베이어가 구동중으로 GREEN LED를 켠다.
            turnOnSingleLed(PIN_GREEN_LED);
            // 모터를 구동한다.
            setSpeedMotorA(_motorDirection, MOTOR_DRIVING_SPEED);
        }

        if (_prevMotorStatus != _motorStatus)   // 모터 상태가 바뀌었다.
        {
            _prevMotorStatus = _motorStatus;
            if (_motorStatus == 0)
            {
                setSpeedMotorA(_motorDirection, 0);
            }
            else
            {
                setSpeedMotorA(_motorDirection, MOTOR_DRIVING_SPEED);
            }
        }

        if (millis() - _chipDetectedTime > CONVEYOR_DRIVING_LIMIT_TIME)     // 구동 시간 경과했다.
        {
            _isDetectedChip = false;
            // 컨베이어 구동이 중단되므로 RED LED를 켠다.
            turnOnSingleLed(PIN_RED_LED);
            // 모터 구동을 중지한다.
            setSpeedMotorA(_motorDirection, 0);
        }
    }
}

//-----------------------------------------------------[ turnOnSingleLed() ]
// 지정된 하나의 LED만 On 시키고, 나머지는 Off 시킨다.
void turnOnSingleLed(int pinNo)
{
    digitalWrite(PIN_RED_LED, pinNo == PIN_RED_LED ? HIGH : LOW);
    digitalWrite(PIN_YELLOW_LED, pinNo == PIN_YELLOW_LED ? HIGH : LOW);
    digitalWrite(PIN_GREEN_LED, pinNo == PIN_GREEN_LED ? HIGH : LOW);
}

//------------------------------------------------------[ turnOffAllLeds() ]
// 모든 LED를 끈다.
void turnOffAllLeds()
{
    digitalWrite(PIN_RED_LED, LOW);
    digitalWrite(PIN_YELLOW_LED, LOW);
    digitalWrite(PIN_GREEN_LED, LOW);
}

//-----------------------------------------------------[ setSpeedMotorA() ]
// Motor A의 속도 설정
void setSpeedMotorA(int motorDirection, uint8_t motorSpeed)
{
    if (motorDirection == 0)
    {   // 순방향
        analogWrite(MOTOR_A1, 0);
        analogWrite(MOTOR_A2, motorSpeed);
    }
    else                            
    {   // 역바향
        analogWrite(MOTOR_A1, motorSpeed);
        analogWrite(MOTOR_A2, 0);
    }
    
}

//-----------------------------------------------------[ interrupted_sw() ]
// 버튼 스위치 인터럽트
void interrupted_sw()
{
    _motorStatus++;
    if (_motorStatus > 2) _motorStatus = 0;
}

//----------------------------------------------[ interrupted_ir_sensor() ]
// IR 센서 인터럽트
void interrupted_ir_sensor()
{
    _isDetectedChip = true;          // 물체 감지 플래그 설정
    _isNewDetectedChip = true;       // 새로운 물체 감지 설정
    _chipDetectedTime = millis();    // 물체가 감지된 시간
}
