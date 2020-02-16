// I2C LCD
// 스케치 > 라이브러리 포함하기 > 라이브러리 관리 에서
// 'LiquidCrystal I2C'(Frank de Brabander) 를 설치해야 함

#include <Wire.h> 
#include "LiquidCrystal_I2C.h"

// LCD 주소번지: 0x27 or 0x3F
// 동작하지 않을때는 주소를 변경한다.
#define ADDR_LCD  0x27
//#define ADDR_LCD  0x3F

LiquidCrystal_I2C lcd(ADDR_LCD, 20, 4); // LCD 주소

void setup()
{
    lcd.init();                      // initialize the lcd 

    // Print a message to the LCD.
    lcd.backlight();

    lcd.setCursor(1,0);
    lcd.print("Hello, world!");

    lcd.setCursor(3, 1);
    lcd.print("Get HS");
}


void loop()
{
}
