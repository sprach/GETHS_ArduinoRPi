# USB Serial 이용
> 예시의 USB Serial 디바이스는 <i><b>PL2303HX</b></i>이며, 다른 USB Serial 디바이스는 그에 맞는 드라이버를 다운로드 받아서 별도 설치해야 한다.
1. USB Serial Driver 설치
    * [Windows 10용 USB Serial device(PL2303HX) 드라이버 설치](./1111_install-Win10-Serial(PL2303HX).md)
    * [Windows 8 이하용 USB Serial device(PL2303HX) 드라이버 설치](./1112_install-Win8-Serial(PL2303HX).md)
    * [MacOS용 USB Serial device(PL2303HX) 드라이버 설치](./1113_install-Mac-Serial(PL2303HX).md)
2. Serial 프로그램 설치
    * [Windows Tera Term 설치](./1121_install-Win-TeraTerm.md)
3. MicroSD의 boot 에 있는 <i><b>config.txt</b></i>에 아래 내용 추가하여 저장
    <pre><code>enable_uart=1</code></pre>
4. USB Serial 디바이스의 핀을 라즈베리파이의 핀에 연결
    > *주의*) 작업시 전원은 반드시 Off로!

    | USB Serial | RasPi Pin No |
    |:----------:|:------------:|
    | GND        | 6 (GND)      |
    | Rx         | 8 (Tx)       |
    | Tx         | 10 (Rx)      |
    ![USB Serial과 라즈베리파이 핀 연결도](../images/RPi/pins-usbserial-raspi.jpg)
5. USB Serial 디바이스를 PC의 USB 포트에 연결
6. MicroSD를 라즈베리파이에 삽입
7. 라즈베리파이 전원 연결
