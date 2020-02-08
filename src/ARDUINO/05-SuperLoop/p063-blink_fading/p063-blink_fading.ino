#define PIN_LED_BLINK  13
#define PIN_LED_FADING 11

int brightness = 0;    // how bright the LED is

void setup()
{
  pinMode(PIN_LED_BLINK, OUTPUT);
  pinMode(PIN_LED_FADING, OUTPUT);
}

void loop()
{
  digitalWrite(PIN_LED_BLINK, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(PIN_LED_BLINK, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  
  for (brightness = 0; brightness <= 255; brightness += 5) {
    analogWrite(PIN_LED_FADING, brightness);
    delay(30); // Wait for 30 millisecond(s)
  }
  for (brightness = 255; brightness >= 0; brightness -= 5) {
    analogWrite(PIN_LED_FADING, brightness);
    delay(30); // Wait for 30 millisecond(s)
  }

}