# 지원 라이브러리

## attachInterrupt()
1. 설명
   attachInterrupt(&lt;Interrupt No&gt;, &lt;ISR Function&gt;, &lt;Interrupt Status&gt;) 함수는 인터럽트 번호(Interrupt No)가 지정된 상태(Interrupt Status)가 되면 인터럽트를 발생시켜서 지정한 ISR 함수(ISR Function)를 콜백(Callback)한다.
 
2. 사용 방법
   <pre><code>// Parameters
   // - [0] Interrupt No
   // - [1] ISR: Interrupt Service Routine
   // - [2] Pin Mode: LOW, CHANGE, RISING, FALLING, HIGH
   attachInterrupt(digitalPinToInterrupt(PIN_SW), sw_interrupt, RISING);</code></pre>

3. 인터럽트 지원 핀
   * 인터럽트가 지원되는 번호는 아두이노 보드에 따라 다르다.

     |BOARD|DIGITAL PINS USABLE FOR INTERRUPTS|
     |-|-|
     |Uno, Nano, Mini, other 328-based|2, 3|
     |Uno WiFi Rev.2|all digital pins|
     |Mega, Mega2560, MegaADK|2, 3, 18, 19, 20, 21|
     |Micro, Leonardo, other 32u4-based|0, 1, 2, 3, 7|
     |Zero|all digital pins, except 4|
     |MKR Family boards|0, 1, 4, 5, 6, 7, 8, 9, A1, A2|
     |Due|all digital pins|
     |101|all digital pins (Only pins 2, 5, 7, 8, 10, 11, 12, 13 work with CHANGE)|

4. 지원되는 인터럽트 번호

   |BOARD|INT.0|INT.1|INT.2|INT.3|INT.4|INT.5|
   |-|:-:|:-:|:-:|:-:|:-:|:-:|
   |Uno, Ethernet|2|3| | | | |
   |Mega2560|2|3|21|20|19|18|
   |32u4 based (e.g Leonardo, Micro)|3|2|0|1|7||
