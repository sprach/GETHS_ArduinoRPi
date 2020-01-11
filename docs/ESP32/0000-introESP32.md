# About ESP32
[ESP32 Get Started](https://docs.espressif.com/projects/esp-idf/en/stable/get-started/index.html): https://docs.espressif.com/projects/esp-idf/en/stable/get-started/index.html

## ESP8266 vs ESP32

|         |ESP8266                          |ESP32                                   |
|--------:|:-------------------------------:|:--------------------------------------:|
|MCU      |Xtensa Single Core 32bit (80MHz) |Xtensa Dual Core 32bit (160MHz)         |
|Wireless |WiFi                             |WiFi / Bluetooth 4.2 / BLE              |
|RAM      |Instruction 32K + User Data 80K  |512KB SRAM, 16KB SRAM in RTC            |
|Flash    |Attachable Normal 512K, Max 16MB |O                                       |
|GPIO     |17                               |36                                      |
|PWM      |8 Channels                       |16 Channels                             |
|COMM     |2SPI, 1I2C, 2I2S, 2UART          |4SPI, 2I2C, 2I2S, 2UART, CAN            |
|MAC      |X                                |O                                       |
|ADC      |10bits (1,024)                   |12bits (4,096)                          |
|Sensors  |X                                |터치, 온도, 홀 (?)                       |

## ESP32 Modules
> Espressif

|Module            |Chip        |Flash|PSRAM|Ant.|
|------------------|------------|:---:|:---:|:--:|
|ESP32-WROOM-32    |ESP32-D0WDQ6|4MB  |–    |MIFA|
|ESP32-WROOM-32D   |ESP32-D0WD  |4MB  |–    |MIFA|
|ESP32-WROOM-32U   |ESP32-D0WD  |4MB  |–    |U.FL|
|ESP32-SOLO-1      |ESP32-S0WD  |4MB  |–    |MIFA|
|ESP32-WROVER      |ESP32-D0WDQ6|4MB  |8MB  |MIFA|
|ESP32-WROVER-I    |ESP32-D0WDQ6|4MB  |8MB  |U.FL|
|ESP32-WROVER-B    |ESP32-D0WD  |4MB  |8MB  |MIFA|
|ESP32-WROVER-IB   |ESP32-D0WD  |4MB  |8MB  |U.FL|

* ESP32-<i><b>D</b></i>: Dual Core, ESP32-<i><b>S</b></i>: Single Core
* MIFA: Meandered Inverted-F Antenna (PCB trace)
* U.FL: U.FL / IPEX antenna connector
* ESP32-WROOM-x and ESP32-WROVER-x modules are also available with custom flash sizes of 8MB or 16MB, see Espressif Products Ordering Information
* Memory
  * SRAM(Static RAM): 전기적 장치없이 임의 접근이 가능한 휘발성 메모리
  * DRAM(Daynamic RAM): 주기적으로 전하를 채워주어야 하는 휘발성 메모리. Precharge circuit 필요함.
  * PSRAM(Pseudo SRAM): Precharge 회로가 포함된 RAM으로 SRAM처럼 보이게 만든 DRAM.
  * 가격: SRAM > PSRAM > DRAM

> ESP32-WROOM032 시리즈별 특징

|Module            |Features                               |
|------------------|---------------------------------------|
|ESP32-WROOM-32    |PCB 안테나형 모듈                       |
|ESP32-WROOM-32D   |PCB 안테나형 모듈<br/>노이즈 필터        |
|ESP32-WROOM-32U   |외장 안테나형 모듈                      |
|ESP32-SOLO-1      |Single Core MCU형 WiFi+BT Combo module |


## ESP32 Pin map
