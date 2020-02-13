// 컬러 센서로 원하는 칩의 색상 구별하기 튜닝
// IR센서에서 물건을 감지하면 동작시작
// 빨강, 파랑, 녹색 중 빨간 색만 통과
// 다른색이 투입이 되었을때는 서보모터를 이용하여 제품을 방출
// 다른색이 투입이 되었을때는 부저로 알림
// 빨간색이 투입이 되었을때는 - 녹색 LED로 정상임을 표시
// 다른색이 투입이 되었을대는 - 빨간색 LED로 에러 표시
// LCD에는 정상적인 제품 수량과, 비정상 제품수량을 카운터하여 표시

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
#define COLOR_SENSING_LIMIT_TIME    2000  /* 컬러 측정 한계 시간 */

// 시간 계산용
unsigned long _chipDetectedTime = 0;

// 색상별 카운트
int _redChipCount = 0;
int _greenChipCount = 0;
int _bludChipCount = 0;

// 칩이 감지되었는지 여부
// 칩이 감지되면서 컨베이어 구동 종료까지 플래그 상태 유지됨
boolean _isDetectedChip = false;
// 새 칩이 감지되었음 여부
// 새 칩이 감지되었다고 할 때 GREEN LED 켜고 모터 구동을 시작한 뒤에 false로 변경한다.
boolean _isNewDetectedChip = false;

// 컬러 센싱 상태 (0: 센싱 상태 아님, 1:센싱 필요함 또는 센싱 진행중)
uint8_t _color_sensing_status = 0;

// 컬러 센서
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);

//--------------------------------------------------------------[ setup() ]
void setup() {
    Serial.begin(115200);

    // 입력 핀 정의
    pinMode(PIN_SW, INPUT);
    pinMode(PIN_IR_SENSOR,INPUT);

    // 출력 핀 정의
    pinMode(PIN_BUZZER,OUTPUT);
    pinMode(PIN_RED_LED,OUTPUT);
    pinMode(PIN_YELLOW_LED,OUTPUT);
    pinMode(PIN_GREEN_LED,OUTPUT);

    // 모든 LED를 끈다.
    turnOffAllLeds();

    // 서보 암을 클리징으로 설정한다.
    _myservo.attach(PIN_SERVO);
    _myservo.write(SERVO_CLOSING_ANGLE);

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
    delay(1000);

    showDetectedChipCount();

    // 컨베이어가 구동중이 아니므로 RED LED를 켠다.
    turnOnSingleLed(PIN_RED_LED);

    // 모터를 정지한다.
    setSpeedMotorA(0);
}

//---------------------------------------------------------------[ loop() ]
void loop() {
    if (_isDetectedChip)         // 물체가 감지되어 있다.
    {
        procDetectedNewChip();

        if (millis() - _chipDetectedTime > CONVEYOR_DRIVING_LIMIT_TIME)     // 구동 시간 경과했다.
        {
          procConveyorDrivingTimeout();
        }
        else    // 컨베이어 구동 시간내
        {
            if(_color_sensing_status == 1)
            {
                //컬러센서 관련 변수
                uint16_t r, g, b, c, colorTemp, lux;
                float average, red, green, blue;
                bool isFoundColor = false;  // 컬러를 찾은 경우
                bool isTargetColr = false;  // 원하는 컬러인지 여부

                // 컬러값 읽기 (50ms의 지연시간 있음)
                tcs.getRawData(&r, &g, &b, &c);
                
                average = (r+g+b)/3;
                red = r / average;
                green = g / average;
                blue = b / average;
                
                Serial.print("\tClear:"); Serial.print(c);
                Serial.print("\tRed:");   Serial.print(red);
                Serial.print("\tGreen:"); Serial.print(green);
                Serial.print("\tBlue:");  Serial.println(blue);
                
                // 컬러 검사
                if ((red > 1.4) && (green < 0.9) && (blue < 0.9))     // 빨강
                {
                  isFoundColor = true;
                  isTargetColr = true;
                  _redChipCount++;
                }
                else if ((red < 0.95) && (green > 1.2) && (blue < 0.9)) // 녹색
                {
                  isFoundColor = true;
                  _greenChipCount++;
                }
                else if ((red < 0.8) && (green < 1.2) && (blue > 1.2))  // 파랑
                {
                  isFoundColor = true;
                  _bludChipCount++;
                }

                // 컬러를 찾았을 경우 처리
                if (isFoundColor)
                {
                    _color_sensing_status = 0;
                    showDetectedChipCount();

                    if (isTargetColr)
                    {
                      turnOnSingleLed(PIN_GREEN_LED);
                      _myservo.write(SERVO_OPENING_ANGLE);
                    }
                    else
                    {
                      turnOnSingleLed(PIN_RED_LED);
                      // 부저를 울린다.
                      soundBuzzer();
                    }
                }
                else if (millis() - _chipDetectedTime > COLOR_SENSING_LIMIT_TIME) // 컬러 센싱 가능 시간 초과
                {
                    _color_sensing_status = 0;
                    turnOnSingleLed(PIN_RED_LED);

                    // 부저를 울린다.
                    soundBuzzer();
                }
            }
        }
    }
}

//---------------------------------------------------------[ soundBuzzer() ]
// 부저 울리기
void soundBuzzer()
{
    digitalWrite(PIN_BUZZER,HIGH);
    delay(100);
    digitalWrite(PIN_BUZZER,LOW);
    delay(100);
    digitalWrite(PIN_BUZZER,HIGH);
    delay(100);
    digitalWrite(PIN_BUZZER,LOW);
    delay(100);
}

//-------------------------------------------------[ procDetectedNewChip() ]
// 새로운 칩인 경우의 처리
void procDetectedNewChip()
{
    if (_isNewDetectedChip)  // 새 물체 감지
    {
        _isNewDetectedChip = false;
        // 컬러 센싱이 필요함
        _color_sensing_status = 1;
        // 컨베이어가 구동중으로 YELLOW LED를 켠다.
        turnOnSingleLed(PIN_YELLOW_LED);
        // 모터를 구동한다.
        setSpeedMotorA(MOTOR_DRIVING_SPEED);
        // 서보 모터로 암을 가림
        _myservo.write(SERVO_CLOSING_ANGLE);
    }
}

//------------------------------------------[ procConveyorDrivingTimeout() ]
// 컨베이어 구동 시간 초과
void procConveyorDrivingTimeout()
{
    _isDetectedChip = false;
    // 컨베이어 구동이 중단되므로 RED LED를 켠다.
    turnOnSingleLed(PIN_RED_LED);
    // 서버 모터 암을 닫는다.
    _myservo.write(SERVO_CLOSING_ANGLE);
    // 모터 구동을 중지한다.
    setSpeedMotorA(0);
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
void setSpeedMotorA(uint8_t motorSpeed)
{
    analogWrite(MOTOR_A1, 0);
    analogWrite(MOTOR_A2, motorSpeed);
}

//----------------------------------------------[ showDetectedChipCount() ]
void showDetectedChipCount()
{
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("RED:GREEN:BLUE");
    lcd.setCursor(2,1);
    lcd.print(_redChipCount);   // 빨간칩 카운트 표시
    lcd.setCursor(7,1);
    lcd.print(_greenChipCount); //
    lcd.setCursor(12,1);
    lcd.print(_bludChipCount);  //
}

//-----------------------------------------------------[ interrupted_sw() ]
// 버튼 스위치 인터럽트
void interrupted_sw()
{ 
  // 모터를 멈추고, 모든값을 초기화한다
  setSpeedMotorA(0);
  _isDetectedChip = false;     // _isDetectedChip 의 값을 false로 바꿔 조건에 들어오지 못하게 한다
  _myservo.write(SERVO_CLOSING_ANGLE);  //서보모터 가림
}

//----------------------------------------------[ interrupted_ir_sensor() ]
// IR 센서 인터럽트
void interrupted_ir_sensor()
{
    _isDetectedChip = true;         // 물체 감지 플래그 설정
    _isNewDetectedChip = true;      // 새로운 물체 감지 설정
    _chipDetectedTime = millis();   // 물체가 감지된 시간
}