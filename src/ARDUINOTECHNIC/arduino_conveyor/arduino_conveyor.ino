// IR센서에서 물건을 감지하면 동작시작
// 빨강,파랑,녹색 중 빨간 색만 통과
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

Servo myservo;

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

#define SERVO_CLOSING_ANGLE   80    /* 서보의 암이 닫히는 각도 */
#define SERVO_OPENING_ANGLE   30    /* 서보의 암이 열리는 각도 */

unsigned long nowTime = 0;
unsigned long prevTime = 0;
unsigned long elapsedTime = 0;

int redCnt = 0;
int greenCnt = 0;
int blueCnt = 0;

int redProductCnt = 0;
int greenProductCnt = 0;
int blueProductCnt = 0;

uint8_t start_flag = 0;
uint8_t color_sensor_check_flag = 0;

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);


void setup() {
  Serial.begin(115200);
  pinMode(PIN_IR_SENSOR,INPUT);

  myservo.attach(PIN_SERVO);
  myservo.write(SERVO_CLOSING_ANGLE);

  pinMode(PIN_BUZZER,OUTPUT);
  pinMode(PIN_RED_LED,OUTPUT);
  pinMode(PIN_YELLOW_LED,OUTPUT);
  pinMode(PIN_GREEN_LED,OUTPUT);
  pinMode(PIN_SW,INPUT);

  // 버튼 스위치 인터럽트 정의
  attachInterrupt(digitalPinToInterrupt(PIN_SW), interrupted_sw, RISING);

  // initialize the lcd 
  lcd.init();

  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(4,0);
  lcd.print("conveyor");
  lcd.setCursor(4,1);
  lcd.print("GET HS");
  delay(1000);
  lcd_view();

  // 이전 시간 기억
  prevTime = millis();
}

void loop() {
  nowTime = millis();
  elapsedTime += nowTime - prevTime; //루틴이 한번동작할때마다 시간을 더한다, 색감지 센서가 50ms의 지연지연을 가짐
  prevTime = nowTime;
  
  if(digitalRead(PIN_IR_SENSOR) == 1) //IR센서가 감지가 되면 
  {
    start_flag = 1; //시작 플래그 1
    color_sensor_check_flag = 1; //컬러센서 체크 플래그 1
    elapsedTime = 0; //타이머를 0으로 초기화

    myservo.write(SERVO_CLOSING_ANGLE);

    digitalWrite(PIN_RED_LED,LOW);
    digitalWrite(PIN_YELLOW_LED,HIGH);
    digitalWrite(PIN_GREEN_LED,LOW);
  }

  if(start_flag == 1) //IR센서가 감지되면 지정한 시간만큼 동작하는 루틴
  {
    if(elapsedTime >= 5000) // 5초가 지나면
    {
      elapsedTime = 0; //타이머 카운터 초기화
      start_flag = 0; //start_flag 의 값을 0으로 바꿔 조건에 들어오지 못하게 한다
      myservo.write(80);  //서보모터 가림
      digitalWrite(PIN_RED_LED,LOW); 
      digitalWrite(PIN_YELLOW_LED,LOW);
      digitalWrite(PIN_GREEN_LED,LOW);
    }
    
    motor_A_set(200); //모터를 200의 속도로 회전

    if(elapsedTime >= 2000) //2초가 지나도
    {
      if(color_sensor_check_flag ==1) //RGB중 감지 되지 않았다면
      {
        color_sensor_check_flag = 0;
        digitalWrite(PIN_RED_LED,HIGH); //빨간색 에러 등을 표시
        digitalWrite(PIN_YELLOW_LED,LOW);
        digitalWrite(PIN_GREEN_LED,LOW);
        digitalWrite(PIN_BUZZER,HIGH);
        delay(100);
        digitalWrite(PIN_BUZZER,LOW);
        delay(100);
        digitalWrite(PIN_BUZZER,HIGH);
        delay(100);
        digitalWrite(PIN_BUZZER,LOW);
        delay(100);
      }
    }

    if(color_sensor_check_flag == 1)
    {
        //컬러센서 부분
        uint16_t r, g, b, c, colorTemp, lux;
        float average, red, green, blue;
        tcs.getRawData(&r, &g, &b, &c);
        
        average = (r+g+b)/3;
        red = r / average;
        green = g / average;
        blue = b / average;
        
        Serial.print("\tClear:"); Serial.print(c);
        Serial.print("\tRed:"); Serial.print(red);
        Serial.print("\tGreen:"); Serial.print(green);
        Serial.print("\tBlue:"); Serial.println(blue);
        
        if ((red > 1.4) && (green < 0.9) && (blue < 0.9)) //빨강
        {
          color_sensor_check_flag = 0;
          redProductCnt++;
          myservo.write(SERVO_OPENING_ANGLE);  //정상통과
          digitalWrite(PIN_RED_LED,LOW);
          digitalWrite(PIN_YELLOW_LED,LOW);
          digitalWrite(PIN_GREEN_LED,HIGH);
          lcd_view();
        }
        else if ((red < 0.95) && (green > 1.2) && (blue < 0.9)) //녹색
        {
          color_sensor_check_flag = 0;
          greenProductCnt++;
          myservo.write(SERVO_OPENING_ANGLE);  //정상통과
          digitalWrite(PIN_RED_LED,LOW);
          digitalWrite(PIN_YELLOW_LED,LOW);
          digitalWrite(PIN_GREEN_LED,HIGH);
          lcd_view();
        }
        else if ((red < 0.8) && (green < 1.2) && (blue > 1.2)) //파랑
        {
          color_sensor_check_flag = 0;
          blueProductCnt++;
          myservo.write(SERVO_OPENING_ANGLE);  //정상통과
          digitalWrite(PIN_RED_LED,LOW);
          digitalWrite(PIN_YELLOW_LED,LOW);
          digitalWrite(PIN_GREEN_LED,HIGH);
          lcd_view();
        }
    }
  }
  else
  {
    motor_A_set(0);
  }

}

// Motor A의 속도 설정
void motor_A_set(uint8_t motorSpeed)
{
  analogWrite(MOTOR_A1, 0);
  analogWrite(MOTOR_A2, motorSpeed);
}

// LCD View
void lcd_view()
{
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("RED:GREEN:BLUE");
  lcd.setCursor(2,1);
  lcd.print(redProductCnt); //빨간색의 제품이 지나간 숫자를 LCD에 표시
  lcd.setCursor(7,1);
  lcd.print(greenProductCnt); //
  lcd.setCursor(12,1);
  lcd.print(blueProductCnt); //
}

// 스위치 인터럽트
void interrupted_sw()
{ 
  //모터를 멈추고, 모든값을 초기화한다
  motor_A_set(0);
  elapsedTime = 0; //타이머 카운터 초기화
  start_flag = 0; //start_flag 의 값을 0으로 바꿔 조건에 들어오지 못하게 한다
  myservo.write(SERVO_CLOSING_ANGLE);  //서보모터 가림
}
