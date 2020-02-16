// 컬러센서
// TCS34725 IC 사용
// 스케치 > 라이브러리 포함하기 > 라이브러리 관리 에서
// 'Adafruit TCS34725'를 설치해야 함

#include <Wire.h>
//#include "Adafruit_TCS34725.h"
#include <Adafruit_TCS34725.h>

// 2020.01.28
uint16_t _r, _g, _b, _c;

/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// https://github.com/adafruit/Adafruit_TCS34725

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 _tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_101MS, TCS34725_GAIN_1X);

void setup(void) {
    Serial.begin(115200);

    if (_tcs.begin()) {
      Serial.println("Found sensor");
    } else {
      Serial.println("No TCS34725 found ... check your connections");
      while (1);
    }

    // Set persistence filter to generate an interrupt for
    // every RGB Cycle, regardless of the integration limits
    _tcs.write8(TCS34725_PERS, TCS34725_PERS_NONE); 
    _tcs.setInterrupt(true);
    
    Serial.flush();
    
    // Now we're ready to get readings!
    _r = 0;
    _g = 0;
    _b = 0;
    _c = 0;
}

void loop(void) {
    uint16_t r, g, b, c, colorTemp, lux;

    // Turn on LED
    _tcs.setInterrupt(false);

    // Takes 50ms to read
    delay(60);
    
    _tcs.getRawData(&r, &g, &b, &c);

    // Turn off LED
    _tcs.setInterrupt(true);
    
    // 같은 값이면 skip
    if ( _r == r && _g == g && _b == b && _c == c ) return;

    // 새 값 저장
    _r = r;
    _g = g;
    _b = b;
    _c = c;

    // colorTemp = _tcs.calculateColorTemperature(r, g, b);
    colorTemp = _tcs.calculateColorTemperature_dn40(r, g, b, c);
    lux = _tcs.calculateLux(r, g, b);

    // Figure out some basic hex code for visualization
    uint32_t sum = c;
    float fr, fg, fb;

    fr = (float)r / sum * 50;
    fg = (float)g / sum * 50;
    fb = (float)b / sum * 50;
    
    Serial.print("Color Temp: "); Serial.print(colorTemp, DEC);
    Serial.print(" K - ");
    Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
    Serial.print("C: "); Serial.print(c, DEC);
    
    Serial.print(" [CNV] ");
    Serial.print("R: "); Serial.print((int)fr, DEC); Serial.print(" ");
    Serial.print("G: "); Serial.print((int)fg, DEC); Serial.print(" ");
    Serial.print("B: "); Serial.print((int)fb, DEC);
    
    Serial.print(" [ORG] ");
    Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
    Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
    Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
    Serial.println(" ");
}
